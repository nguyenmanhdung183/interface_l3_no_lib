import re
import json
import os
import csv

from _1_prepare_struct import *

DATA_EXCEL_PATH = os.path.join(BASE_DIR, "..", "data", "data.csv")

HANDLED_STRUCTS = set()


# =============================
# DATA TYPE
# =============================
def get_data_type(type_str):
    for key, values in PRIMITIVE_LIST.items():
        if type_str in values:
            return {
                "kind": "PRIMITIVE",
                "detail": key
            }
    return {
        "kind": "STRUCT",
        "detail": None
    }


# =============================
# PARSE FIELD
# =============================
def parse_fields_with_meta(struct_body):
    fields = []

    for line in struct_body.split("\n"):
        line = line.strip()
        if not line:
            continue

        comment_matches = re.findall(r"/\*\^(.*?)\^\*/", line)
        metadata = {}

        if comment_matches:
            parts = [x.strip() for x in comment_matches[0].split(",")]

            if len(parts) >= 1:
                metadata["present"] = parts[0]
            if len(parts) >= 2:
                metadata["bitmask"] = parts[1]
            if len(parts) >= 3:
                metadata["range_check"] = parts[2]

            if metadata.get("range_check") == "OCTET_STRING":
                if len(parts) >= 4:
                    metadata["description"] = parts[3]
            if len(parts) >= 4:
                metadata["min"] = parts[3]
            if len(parts) >= 5:
                metadata["max"] = parts[4]

            if len(comment_matches) >= 2:
                metadata["length_ref"] = comment_matches[1].strip()

        if metadata.get("range_check") == "OCTET_STRING":
            metadata["description"] = parts[3] if len(parts) >= 4 else ""
            metadata["min"] = ""
            metadata["max"] = ""

        line = re.sub(r"/\*.*?\*/", "", line)
        line = re.sub(r"//.*", "", line)

        match = re.match(r"([\w_]+)\s+([\w_]+)(\[(.*?)\])?", line)
        if match:
            fields.append({
                "type": match.group(1),
                "name": match.group(2),
                "data_type": get_data_type(match.group(1))["kind"],
                "key": get_data_type(match.group(1))["detail"],
                "is_array": match.group(3) is not None,
                "array_size": match.group(4) if match.group(4) else None,
                "meta": metadata
            })

    return fields


# =============================
# BUILD TREE
# =============================
def build_tree_with_meta(struct_name, structs, visited=None):
    if visited is None:
        visited = set()

    if struct_name in visited:
        return {"type": struct_name, "fields": []}

    visited.add(struct_name)

    if struct_name not in structs:
        return {"type": struct_name, "fields": []}

    tree = {"type": struct_name, "fields": []}
    fields = parse_fields_with_meta(structs[struct_name])

    for f in fields:
        node = {
            "name": f["name"],
            "type": f["type"],
            "is_array": f["is_array"],
            "data_type": f["data_type"],
            "key": f["key"],
            "array_size": f["array_size"],
            "meta": f["meta"]
        }

        if f["type"] not in PRIMITIVES and f["type"] in structs:
            node["primitive"] = False
            node["children"] = build_tree_with_meta(f["type"], structs, visited.copy())
        else:
            node["primitive"] = True

        tree["fields"].append(node)

    return tree


# =============================
# EXPORT CSV (THAY EXCEL)
# =============================
def export_to_csv(tree, output_file):
    header = [
        "parent", "child_type", "child_name", "data_type", "key",
        "is_array", "array_size", "length_ref",
        "present", "bitmask", "range_check", "min", "max", "description", "bitmask_name"
    ]

    def flatten_tree(tree, rows=None):
        if rows is None:
            rows = []

        parent = tree.get("type")

        if parent in HANDLED_STRUCTS:
            return rows
        HANDLED_STRUCTS.add(parent)

        for field in tree.get("fields", []):
            meta = field.get("meta", {})

            rows.append([
                parent,
                field.get("type"),
                field.get("name"),
                field.get("data_type", ""),
                field.get("key", ""),
                field.get("is_array", False),
                field.get("array_size", ""),
                meta.get("length_ref", ""),
                meta.get("present", ""),
                meta.get("bitmask", ""),
                meta.get("range_check", ""),
                meta.get("min", ""),
                meta.get("max", ""),
                meta.get("description", ""),
                ""
            ])

            if not field.get("primitive") and "children" in field:
                flatten_tree(field["children"], rows)

        return rows

    rows = flatten_tree(tree)
    rows.sort(key=lambda r: r[0])

    with open(output_file, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(header)
        writer.writerows(rows)

    print("Exported to CSV:", output_file)


# =============================
# STRUCT EXTRACT
# =============================
def extract_structs(code):
    structs = {}

    struct_blocks = re.findall(
        r"typedef\s+struct\s+(?:\w+\s*)?\{(.*?)\}\s*(\w+)\s*;",
        code,
        re.DOTALL
    )

    for body, name in struct_blocks:
        structs[name] = body

    return structs

#============================ fill missing data in CSV ============================
def fill_missing_data_in_csv(file_path):
    """
    Fill missing length_ref trong CSV:
    - Nếu range_check=OCTET_STRING và description=VARIABLE
    - Lấy child_name của field khác cùng parent nếu parent có <= 2 fields
    """

    # đọc csv
    with open(file_path, "r", encoding="utf-8-sig", newline="") as f:
        rows = list(csv.DictReader(f))

    if not rows:
        return

    headers = rows[0].keys()

    required_columns = [
        "parent",
        "child_name",
        "length_ref",
        "range_check",
        "description"
    ]

    for col in required_columns:
        if col not in headers:
            raise ValueError(f"Missing column: {col}")

    # parent -> rows
    parent_map = {}

    for row in rows:
        parent = row["parent"]
        parent_map.setdefault(parent, []).append(row)

    # fill
    for parent, child_rows in parent_map.items():

        for row in child_rows:

            range_check = row["range_check"]
            description = row["description"]
            length_ref = row["length_ref"]
            child_name = row["child_name"]

            if (
                range_check == "OCTET_STRING"
                and description == "VARIABLE"
                and not length_ref
            ):

                other_names = [
                    r["child_name"]
                    for r in child_rows
                    if r["child_name"] != child_name
                ]

                if len(other_names) == 0:
                    continue

                elif len(other_names) > 1:
                    raise ValueError(
                        f"Parent '{parent}' has more than 2 child fields, "
                        f"cannot determine length_ref for '{child_name}'"
                    )

                else:
                    row["length_ref"] = other_names[0]

    # ghi lại csv
    with open(file_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=headers
        )

        writer.writeheader()
        writer.writerows(rows)

    print(f"[INFO] Filled missing length_ref in CSV: {file_path}")

def fill_bitmask_name(file_path):
    with open(file_path, "r", encoding="utf-8-sig", newline="") as f:
        rows = list(csv.DictReader(f))

    if not rows:
        return

    headers = rows[0].keys()

    parent_map = {}

    # group by parent
    for row in rows:
        parent = row["parent"]
        parent_map.setdefault(parent, []).append(row)

    for parent, child_rows in parent_map.items():

        # tìm field BITMASK
        bitmask_field = None

        for r in child_rows:
            if r["present"] == "BITMASK":
                bitmask_field = r["child_name"]
                break

        if not bitmask_field:
            continue

        # fill toàn bộ row trong parent
        for r in child_rows:
            r["bitmask_name"] = bitmask_field

    # write back
    with open(file_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=headers)
        writer.writeheader()
        writer.writerows(rows)

    print(f"[INFO] Filled bitmask_name in CSV: {file_path}")
    
# =============================
# MAIN
# =============================
def main():
    code = ""

    for filename in os.listdir(os.path.join(BASE_DIR, "..", "struct_input")):
        if filename.endswith(".c") or filename.endswith(".h"):
            code += "\n" + read_file(os.path.join(BASE_DIR, "..", "struct_input", filename))

    append_to_primitive_list(code)

    structs = extract_structs(code)
    tree = build_tree_with_meta(ROOT_STRUCT, structs)

    print(json.dumps(tree, indent=2))

    export_to_csv(tree, DATA_EXCEL_PATH)
    fill_missing_data_in_csv(DATA_EXCEL_PATH)
    fill_bitmask_name(DATA_EXCEL_PATH)
    
    


if __name__ == "__main__":
    main()