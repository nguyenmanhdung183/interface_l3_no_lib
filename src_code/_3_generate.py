import math
from textwrap import indent

#from attrs import field

from _2_make_excel import *
import pandas as pd
from collections import defaultdict
from jinja2 import Environment, FileSystemLoader
import os


wb = pd.read_excel(DATA_EXCEL_PATH, sheet_name=None)
types_df = wb.get("Struct Tree", pd.DataFrame())

HARDCODE_REGISTRY = {
    "primitive_hc": {},
    "struct_hc": {},
    "sequence_of_item":{}

}

env = Environment(loader=FileSystemLoader(TEMPLATES_DIR), trim_blocks=True, lstrip_blocks=True)



def ceil_to_standard_bits(type_str):
    data = None
    for key, values in PRIMITIVE_LIST.items():
        if type_str in values:
            data = key
            break
        if type_str in key:
            data = key
            break
            #return key
        
    match data:
        case "UI8":
            return "UInt8"
        case "UI16":
            return "UInt16"
        case "UI32":
            return "UInt32"
        case "UI64":
            return "UInt64"
        case "I8":
            return "Int8"
        case "I16":
            return "Int16"
        case "I32":
            return "Int32"
        case "I64":
            return "Int64"
        case "SI8":
            return "SInt8"
        case "SI16":
            return "SInt16"
        case "SI32":
            return "SInt32"
        case "SI64":
            return "SInt64"
    raise ValueError(f"Type '{type_str}' not found in PRIMITIVE_LIST")    
    #return type_str



env.filters['stdbit'] = ceil_to_standard_bits

def upcase_text(text):
    return text.upper()

env.filters['upcase'] = upcase_text

def validate_data():
    df = types_df

    if df.empty:
        raise ValueError("Excel is empty. No data to process.")

    required_columns = [
        "parent", "child_name", "child_type", "is_array",
        "array_size", "data_type", "key", "length_ref",
        "present", "bitmask", "range_check", "min", "max", "description"
    ]

    missing_columns = [col for col in required_columns if col not in df.columns]
    if missing_columns:
        raise ValueError(f"Missing columns in Excel: {missing_columns}")

    # Rule: present = O thì bitmask phải có
    invalid_bitmask = df[
        (df["present"].astype(str).str.strip().str.upper() == "O") &
        (
            df["bitmask"].isnull() |
            (df["bitmask"].astype(str).str.strip().isin(["", "0", "0.0"]))
        )
    ]
    if not invalid_bitmask.empty:
        raise ValueError(
            "Rows with present='O' must have 'bitmask' value:\n\n\n\n"
            f"{invalid_bitmask[['parent','child_name','bitmask',"present"]]}"
        )
    # RULE nếu present = M thì bitmask phải null hoặc 0
    invalid_bitmask_m = df[
        (df["present"].astype(str).str.strip().str.upper() == "M") &
        (
            df["bitmask"].notnull() &
            ~df["bitmask"].astype(str).str.strip().isin(["", "0", "0.0"])
        )
    ]
    if not invalid_bitmask_m.empty:
        raise ValueError(
            "Rows with present='M' must have 'bitmask' value null or 0:\n"
            f"{invalid_bitmask_m[['parent','child_name','bitmask',"present"]]}"
        )
    # RULE nếu là octet string VARIABLE thì phải có length_ref
    invalid_octet_string = df[
        (df["range_check"].astype(str).str.strip().str.upper() == "OCTET_STRING") &
        (df["description"].astype(str).str.strip().str.upper() == "VARIABLE") &
        (
            df["length_ref"].isnull() |
            (df["length_ref"].astype(str).str.strip() == "")
        ) 
    ]
    if not invalid_octet_string.empty:
        raise ValueError(
            "Rows with range_check='OCTET_STRING' must have a valid 'length_ref' value:\n"
            f"{invalid_octet_string[['parent','child_name','length_ref']]}"
        )

    return True

generated_files = set()
def safe_write(path, content):
    if path in generated_files:
        #print(f"Skip (already generated): {path}")
        return
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)
    generated_files.add(path)
    print(f"Generated: {path}")


def remove_all_data_structs():
    for folder in [HEADER_FOLDER, EN_FOLDER, DEC_FOLDER, GET_DATA_FOLDER]:
        for filename in os.listdir(folder):
            if (filename.endswith(".h") or filename.endswith(".c")):
                os.remove(os.path.join(folder, filename))
                print(f"Removed: {os.path.join(folder, filename)}")
                
def remove_trailing_t(s: str) -> str:
    """
    Trả về chuỗi s, nhưng loại bỏ '_t' nếu nó nằm ở cuối.
    Giữ nguyên nếu '_t' không ở cuối.
    """
    suffix = "_t"
    if s.endswith(suffix):
        return s[:-len(suffix)]
    return s


def gen_data():
    df = types_df
    if df.empty:
        print("Excel is empty. No data to process.")
        return {}

    # fix lỗi space từ Excel
    df.columns = df.columns.str.strip()

    grouped = {}
    
    for parent, group in df.groupby("parent"):
        fields = []

        for _, row in group.iterrows():
            field = {
                "name": row["child_name"],
                "type": row["child_type"],
                "child_type": row["child_type"],
                "child_name": row["child_name"],
                "child_type_stripped": row["child_type"].replace("_t", ""),
                "is_array": str(row["is_array"]).upper() == "TRUE",
                "array_size": row["array_size"],
                "data_type": row["data_type"], # PRIMITIVE / STRUCT
                "key": row["key"], #UI8, UI16,...
                "length_ref": row["length_ref"],#count, length,..
                "present": row["present"],
                "bitmask": row["bitmask"],
                "range_check": row["range_check"],
                "min": row["min"],
                "max": row["max"],
                "description": row["description"]
            }
            fields.append(field)

        data = {
            "parent": parent,
            "parent_stripped": remove_trailing_t(parent),
            "fields": fields
        }

        grouped[parent] = data
        HARDCODE_REGISTRY["struct_hc"][parent] = data
        try:
            safe_write(f"{HEADER_FOLDER}/header_il_{parent}.h", env.get_template("head.j2").render(data))
            safe_write(f"{EN_FOLDER}/en_il_{parent}.c", env.get_template("en.j2").render(data))
            safe_write(f"{DEC_FOLDER}/dec_il_{parent}.c", env.get_template("dec.j2").render(data))
            safe_write(f"{HEADER_P_FOLDER}/header_parser_il_{parent}.h", env.get_template("head_p.j2").render(data))

            print(f"Generated struct: {parent}")

        except Exception as e:
            print(f"[WARN] template failed for {parent}: {e}")
            
    data = {
        "parent": ROOT_STRUCT,
        "parent_stripped": remove_trailing_t(ROOT_STRUCT),
    }
    try: 
        safe_write(f"{RESULT_FOLDER}/FUNCTION.c", env.get_template("function.j2").render(data))
    except Exception as e:
        print(f"[WARN] template failed for {parent}: {e}")
        
    return grouped

def replace_root_struct(content, root_struct):
    root_struct_stripped = remove_trailing_t(root_struct)
    return content.replace(f"p_{root_struct_stripped}.", f"p_{root_struct_stripped}->")
    
def is_valid_number(val):
    if val is None:
        return False
    if isinstance(val, float) and math.isnan(val):
        return False
    if isinstance(val, str) and not val.isdigit():
        return False
    return True


def to_number(val, default=0):
    try:
        if val is None or val == "":
            return default
        num = float(val)
        if math.isnan(num) or math.isinf(num):
            return default
        return num
    except (ValueError, TypeError):
        return default
    
def is_numeric(val):
    try:
        if val is None or val == "":
            return False
        return True
    except (ValueError, TypeError):
        return False


# ========================= NEW ======================

# ================= DISPATCH =================
def handle_emit(field, field_path, registry, idx_gen, indent_lv):
    data_type = field["data_type"]
    range_check = str(field.get("range_check")).upper()
    idx = next(idx_gen)
    present = field.get("present")
    bitmask = field.get("bitmask")
    name = field["name"]
    indent = "\t" * indent_lv
    lines = []
    # # ===== START BLOCK =====
    # if present == "O":
    #     lines.append(f"{indent}#if 1 /*idx{idx}: {name} - {data_type} - {range_check} --> S */")
    #     #lines.append(f"{indent}{{")
    #     #lines.append(f"{indent}\tif ({field_path}.bitmask & {bitmask})")
    #     lines.append(f"{indent}\t{field_path}.bitmask |= {bitmask}")
    #     lines.append(f"{indent}\t{{")
    #     inner_lv = indent_lv + 2
    # else:
    #     print_log_info(f"Processing mandatory field: {field_path}")
    #     #lines.append(f"{indent}/* idx{idx}: {name} S */")
    #     #lines.append(f"{indent}{{")
    #     inner_lv = indent_lv + 1
        
        
        
        
    # ưu tiên OCTET STRING trước
    # if range_check == "OCTET_STRING":
    #     return emit_octet_string(field, field_path, indent_lv)

    if data_type == "PRIMITIVE":
        lines.extend(emit_primitive(field, field_path, indent_lv))

    if data_type == "STRUCT":
        lines.extend(emit_struct(field, field_path, registry, idx_gen, indent_lv))


    # ===== CLOSE =====
    # if present == "O":
    #     lines.append(f"{indent}\t}}")
    #     #lines.append(f"{indent}}}")
    #     lines.append(f"{indent}#endif /* idx{idx}: {name} E */\n")
    # else:
    #     print_log_info(f"Finished processing mandatory field: {field_path}")
    #     #lines.append(f"{indent}}}")
    #     #lines.append(f"{indent}/* idx{idx}: {name} E */\n")
    
    return lines
    
    return [f"\t// [WARN] unknown type: {field_path}"]



def simple_hc_value(min_val, max_val):
    min_val = to_number(min_val)
    max_val = to_number(max_val)
    return int((min_val + max_val) // 2)



length_ref_map = []

for sheet_name, df in wb.items():
    df.columns = df.columns.str.strip()
    for row in df.itertuples(index=False):
        if isinstance(row.length_ref, str) and row.length_ref != "":
            length_ref_map.append((row.length_ref))

# ================= PRIMITIVE =================
def emit_primitive(field, field_path, indent_lv):
    lines = []
    name = field["name"]
    is_array = field["is_array"]

    hc_value = simple_hc_value(field.get("min"), field.get("max"))
    indent = "\t" * indent_lv

    if is_array: # octet string
        if field.get("range_check") == "OCTET_STRING" and field.get("description").upper() == "VARIABLE":
            lines.append(f"{indent}/* {field_path} is an array primitive, assigning variale values */")
            # lines.append(f"{indent}{field_path}[0] = {hc_value};")
            # lines.append(f"{indent}{field_path}[1] = {hc_value};")
            # lines.append(f"\n.....................\n")
            # lines.append(f"{indent}{field_path}[max] = {hc_value};")
            lines.append(f"{indent}{field_path} = {{0x01, 0x02}}; /* example for octet string array */")

        elif field.get("range_check") == "OCTET_STRING" and field.get("description").upper() == "FIXED":
            lines.append(f"{indent}/* {field_path} is an array primitive, assigning fixed values */")
            lines.append(f"{indent}{field_path} = {{0x01, 0x02}}; /* example for octet string array */")

    else:
        # for row in (wb.itertuples()):
        #     if type(field.get("length_ref")) == str:
        #         if name == field.get("length_ref"):
        #             hc_value = row
        
        if name in length_ref_map:
            print_log_info(f"Field {field_path} is a length reference, assigning 0")
            hc_value = 2

        lines.append(f"{indent}{field_path} = {hc_value};")
        

    return lines


# ================= OCTET STRING =================
def emit_octet_string(field, field_path, indent_lv):
    lines = []
    indent = "\t" * indent_lv

    desc = str(field.get("description")).upper()
    is_array = field["is_array"]

    targets = [field_path]

    if is_array:
        targets = [f"{field_path}[0]", f"{field_path}[1]"]

    for t in targets:
        if desc == "FIXED":
            lines.append(f"{indent}{t}.length = sizeof({t}.data);")
        else:  # VARIABLE
            lines.append(f"{indent}{t}.length = 2;")

        lines.append(f"{indent}{t}.data[0] = 0x01;")
        lines.append(f"{indent}{t}.data[1] = 0x02;")

    return lines


# ================= STRUCT =================
def emit_struct(field, field_path, registry, idx_gen, indent_lv):
    lines = []
    indent = "\t" * indent_lv

    child = field["child_type"]
    child_def = registry["struct_hc"][child]
    is_array = field["is_array"]

    targets = [field_path]

    if is_array:
        #targets = [f"{field_path}[0]"]
        targets = [f"{field_path}[0]", f"{field_path}[1]"]

    for t in targets:
        sub = emit_struct_hardcode(
            child,
            child_def,
            registry,
            t,
            idx_gen,
            indent_lv
        )
        lines.extend(sub)

    return lines


# ================= MAIN STRUCT =================
def emit_struct_hardcode(struct_name, struct_def, registry, path, idx_gen, indent_lv=1):
    lines = []

    for field in struct_def["fields"]:
        idx = next(idx_gen)

        name = field["name"]
        present = field.get("present")
        bitmask = field.get("bitmask")

        if present == "O":
            lines.append(f"\n{indent}#if 1 /*idx{idx}: {name} S */")
            lines.append(f"{indent}\tif ({path}.bitmask & {bitmask})")
            lines.append(f"{indent}\t{{")
            #inner_lv = indent_lv + 2

        field_path = f"{path}.{name}"
        indent = "\t" * indent_lv
        inner_lv = indent_lv + 1
        
        # # ===== START BLOCK =====
        # if present == "O":
        #     lines.append(f"{indent}#if 1 /*idx{idx}: {name} S */")
        #     lines.append(f"{indent}{{")
        #     lines.append(f"{indent}\tif ({path}.bitmask & {bitmask})")
        #     lines.append(f"{indent}\t{{")
        #     inner_lv = indent_lv + 2
        # else:
        #     lines.append(f"{indent}/* idx{idx}: {name} S */")
        #     lines.append(f"{indent}{{")
        #     inner_lv = indent_lv + 1

        # ===== HANDLE =====
        body = handle_emit(field, field_path, registry, idx_gen, inner_lv)
        lines.extend(body)

        if present == "O":
            lines.append(f"{indent}\t}}")
            lines.append(f"{indent}#endif /* idx{idx}: {name} E */\n")
        
        # # ===== CLOSE =====
        # if present == "O":
        #     lines.append(f"{indent}\t}}")
        #     lines.append(f"{indent}}}")
        #     lines.append(f"{indent}#endif /* idx{idx}: {name} E */\n")
        # else:
        #     lines.append(f"{indent}}}")
        #     lines.append(f"{indent}/* idx{idx}: {name} E */\n")

    return lines


# ================= WRAPPER =================
def emit_struct_wrapper(struct_name, registry):
    idx_gen = iter(range(10000))

    struct_def = registry["struct_hc"][struct_name]

    body_lines = emit_struct_hardcode(
        struct_name,
        struct_def,
        registry,
        f"p_{struct_name.replace('_t','')}",
        idx_gen
    )

    body = "\n".join(body_lines)

    # convert . -> ->
    root = f"p_{struct_name.replace('_t','')}"
    body = body.replace(f"{root}.", f"{root}->")

    return f"""
xnap_return_et assign_hardcode_value_{struct_name}( {struct_name} *{root} )
{{
{indent(body, " " * 4)}
    return XNAP_SUCCESS;
}}
"""


#========================GET====================## ================= TRACE VALUE FULL =================

def get_printf_format(key):
    if key in ["UI8", "UI16", "UI32"]:
        return "%u"
    if key in ["I8", "I16", "I32"]:
        return "%d"
    if key in ["UI64"]:
        return "%llu"
    if key in ["I64"]:
        return "%lld"
    return "%u"


# ================= PRIMITIVE =================
def emit_get_primitive(field, field_path, indent_lv):
    indent = "\t" * indent_lv
    lines = []

    key = field.get("key", "UI32")
    fmt = get_printf_format(key)

    is_array = field["is_array"]
    range_check = str(field.get("range_check")).upper()
    desc = str(field.get("description")).upper()
    field_path = f"{field_path}.{field['name']}"
    # ===== OCTET STRING =====
    if range_check == "OCTET_STRING":
        if desc == "FIXED":
            lines.append(f"{indent}/* {field_path} is an array primitive, fixed length */")
            #lines.append(f"{indent}fprintf(stderr, \"[TRACE] {field_path}. = %u\\n\", {field_path}.length);")
            lines.append(f"{indent}for (int i = 0; i < {field_path}.; i++)")
            lines.append(f"{indent}{{")
            lines.append(f'{indent}\tfprintf(stderr, "[TRACE] {field_path}.[%d] = 0x%02X\\n", i, {field_path}.data[i]);')
            lines.append(f"{indent}}}")
        elif desc == "VARIABLE":
            lines.append(f"{indent}/* {field_path} is an array primitive, variable length */")
            #lines.append(f'{indent}fprintf(stderr, "[TRACE] {field_path} = %u\\n", {field_path}.length);')
            lines.append(f"{indent}for (int i = 0; i < {field_path}; i++)")
            lines.append(f"{indent}{{")
            lines.append(f'{indent}\tfprintf(stderr, "[TRACE] {field_path}[%d] = 0x%02X\\n", i, {field_path}.data[i]);')
            lines.append(f"{indent}}}")

        return lines

    # ===== ARRAY =====
    if is_array:
        size = field.get("array_size", 2)

        lines.append(f"{indent}for (int i = 0; i < {size}; i++)")
        lines.append(f"{indent}{{")
        lines.append(f'{indent}\tfprintf(stderr, "[TRACE] {field_path}[%d] = {fmt}\\n", i, {field_path}[i]);')
        lines.append(f"{indent}}}")
    else:
        lines.append(f'{indent}fprintf(stderr, "[TRACE] {field_path} = {fmt}\\n", {field_path});')

    return lines


# ================= STRUCT =================
def emit_get_struct(field, field_path, registry, idx_gen, indent_lv):
    lines = []
    indent = "\t" * indent_lv

    child = field["child_type"]
    child_def = registry["struct_hc"][child]
    
    present = field.get("present")
    bitmask = field.get("bitmask")
    
    if present == "O":
        lines.append(f"\n{indent}if ({field_path}.bitmask & {bitmask})")
        lines.append(f"{indent}{{")
        
    field_path = f"{field_path}.{field['name']}"
    
    if field["is_array"]:
        size = field.get("array_size", 2)

        lines.append(f"{indent}for (int i = 0; i < {size}; i++)")
        lines.append(f"{indent}{{")

        sub_path = f"{field_path}[i]"

        lines.extend(
            emit_struct_trace(
                child,
                child_def,
                registry,
                sub_path,
                idx_gen,
                indent_lv + 1
            )
        )

        lines.append(f"{indent}}}")
    else:
        lines.extend(
            emit_struct_trace(
                child,
                child_def,
                registry,
                field_path,
                idx_gen,
                indent_lv
            )
        )
    if present == "O":
         lines.append(f"{indent}}}")
    return lines


# ================= HANDLE =================
def handle_get(field, field_path, registry, idx_gen, indent_lv):
    data_type = field["data_type"]
    present = field.get("present")
    bitmask = field.get("bitmask")
    
    indent = "\t" * indent_lv
    next(idx_gen)

    lines = []
    
    inner_lv = indent_lv

    # ===== OPTIONAL =====
    # if present == "O":
    #     lines.append(f"{indent}if ({field_path}.bitmask & {bitmask})")
    #     lines.append(f"{indent}{{")
    #     inner_lv = indent_lv + 1
    # else:
    #     inner_lv = indent_lv

    # ===== DISPATCH =====
    if data_type == "PRIMITIVE":
        lines.extend(emit_get_primitive(field, field_path, inner_lv))

    elif data_type == "STRUCT":
        lines.extend(emit_get_struct(field, field_path, registry, idx_gen, inner_lv))

    else:
        lines.append(f'{indent}fprintf(stderr, "[TRACE] UNKNOWN: {field_path}\\n");')

    # ===== CLOSE OPTIONAL =====
    # if present == "O":
    #     lines.append(f"{indent}}}")

    return lines


# ================= RECURSION =================
def emit_struct_trace(struct_name, struct_def, registry, path, idx_gen, indent_lv):
    lines = []
    indent = "\t" * indent_lv

    lines.append(f'{indent}fprintf(stderr, "\\n[TRACE] ===== {struct_name} =====\\n");')

    for field in struct_def["fields"]:
        #field_path = f"{path}.{field['name']}"
        field_path = f"{path}"
        lines.extend(handle_get(field, field_path, registry, idx_gen, indent_lv))

    return lines


# ================= WRAPPER =================
def get_struct_wrapper(struct_name, registry):
    idx_gen = iter(range(10000))

    struct_def = registry["struct_hc"][struct_name]

    body_lines = emit_struct_trace(
        struct_name,
        struct_def,
        registry,
        f"p_{struct_name.replace('_t','')}",
        idx_gen,
        1
    )

    body = "\n".join(body_lines)

    root = f"p_{struct_name.replace('_t','')}"
    body = body.replace(f"{root}.", f"{root}->")

    return f"""
#include <stdio.h>

void trace_{struct_name}({struct_name} *{root})
{{
{indent(body, " " * 4)}
}}
"""

#===============================MAIN============================================
def main():
    remove_all_data_structs()
    validate_data()
    grouped_structs = gen_data()
    #gen_hardcode_output()
    get_data = get_struct_wrapper(ROOT_STRUCT, HARDCODE_REGISTRY)
    get_data = replace_root_struct(get_data, ROOT_STRUCT)
    with open(f"{RESULT_FOLDER}/GET_DATA.c", "w", encoding="utf-8") as f:
        f.write(get_data)
    
    hc = emit_struct_wrapper(ROOT_STRUCT, HARDCODE_REGISTRY)
    hc = replace_root_struct(hc, ROOT_STRUCT)
    with open(f"{RESULT_FOLDER}/HARD_CODE.c", "w", encoding="utf-8") as f:
        f.write(hc)
    #print(json.dumps(grouped_structs, indent=2))


if __name__ == "__main__":
    main()