import os
import re
import csv
import math
from textwrap import indent

from _2_make_excel import *


# =========================================================
# CONFIG
# =========================================================

TEMPLATES_DIR = os.path.join(BASE_DIR, "..", "templates_txt")

HARDCODE_REGISTRY = {
    "primitive_hc": {},
    "struct_hc": {},
    "sequence_of_item": {}
}

generated_files = set()


# =========================================================
# COMMON
# =========================================================

def clean_str(val):
    if val is None:
        return ""
    return str(val).strip().upper()


def remove_trailing_t(s):
    if s.endswith("_t"):
        return s[:-2]
    return s


def safe_write(path, content):

    if path in generated_files:
        return

    with open(path, "w", encoding="utf-8") as f:
        f.write(content)

    generated_files.add(path)

    print("Generated:", path)


def remove_all_data_structs():

    for folder in [
        HEADER_FOLDER,
        EN_FOLDER,
        DEC_FOLDER,
        HEADER_P_FOLDER,
        RESULT_FOLDER
    ]:

        for filename in os.listdir(folder):

            if filename.endswith(".h") or filename.endswith(".c"):

                os.remove(
                    os.path.join(folder, filename)
                )


# =========================================================
# FILTER
# =========================================================

def ceil_to_standard_bits(type_str):

    mapping = {
        "UI8": "UInt8",
        "UI16": "UInt16",
        "UI32": "UInt32",
        "UI64": "UInt64",

        "I8": "Int8",
        "I16": "Int16",
        "I32": "Int32",
        "I64": "Int64",

        "SI8": "SInt8",
        "SI16": "SInt16",
        "SI32": "SInt32",
        "SI64": "SInt64"
    }

    return mapping.get(type_str, type_str)


# =========================================================
# TEMPLATE ENGINE
# =========================================================

def apply_filter(value, filter_name):

    if filter_name == "upcase":
        return str(value).upper()

    if filter_name == "stdbit":
        return ceil_to_standard_bits(value)

    return value


def resolve_var(expr, context):

    expr = expr.strip()

    if "|" in expr:

        var_part, filter_part = [
            x.strip()
            for x in expr.split("|", 1)
        ]

        val = resolve_var(
            var_part,
            context
        )

        return apply_filter(
            val,
            filter_part
        )

    if expr.startswith('"') and expr.endswith('"'):
        return expr.strip('"')

    if expr.isdigit():
        return int(expr)

    parts = expr.split(".")

    val = context.get(parts[0], "")

    for p in parts[1:]:

        if isinstance(val, dict):
            val = val.get(p, "")
        else:
            val = getattr(val, p, "")

    return val

def eval_condition(cond, context):

    keywords = {
        "and",
        "or",
        "not",
        "True",
        "False",
        "None"
    }

    string_placeholders = []

    # protect "...."
    def protect_string(m):

        string_placeholders.append(
            m.group(0)
        )

        return f"__STR{len(string_placeholders)-1}__"

    cond2 = re.sub(
        r'"[^"]*"',
        protect_string,
        cond
    )

    def replace_var(match):

        expr = match.group(0)

        if expr in keywords:
            return expr

        if expr.startswith("__STR"):
            return expr

        val = resolve_var(
            expr,
            context
        )

        return repr(val)

    cond2 = re.sub(
        r'\b[a-zA-Z_][\w\.|]*\b',
        replace_var,
        cond2
    )

    # restore string
    for i, s in enumerate(string_placeholders):

        cond2 = cond2.replace(
            f"__STR{i}__",
            s
        )

    try:

        return eval(
            cond2,
            {"__builtins__": {}},
            {}
        )

    except Exception:

        print(
            "\n[EVAL ERROR]"
        )

        print(
            "original:",
            cond
        )

        print(
            "parsed  :",
            cond2
        )

        raise
    
    
def find_block_end(lines, start, block_type):

    depth = 1

    i = start + 1

    while i < len(lines):

        if f"{{% {block_type}" in lines[i]:
            depth += 1

        elif f"{{% end{block_type} %}}" in lines[i]:

            depth -= 1

            if depth == 0:
                return i

        i += 1

    return len(lines) - 1


def process_if_block(block_lines, context):

    sections = []

    current_cond = None

    current_block = []

    for line in block_lines:

        line_strip = line.strip()

        if line_strip.startswith("{% if"):

            cond = re.match(
                r"{% if (.+) %}",
                line_strip
            ).group(1)

            current_cond = cond

            current_block = []

        elif line_strip.startswith("{% elif"):

            sections.append(
                (
                    current_cond,
                    current_block
                )
            )

            cond = re.match(
                r"{% elif (.+) %}",
                line_strip
            ).group(1)

            current_cond = cond

            current_block = []

        elif line_strip.startswith("{% else %}"):

            sections.append(
                (
                    current_cond,
                    current_block
                )
            )

            current_cond = "ELSE"

            current_block = []

        elif line_strip.startswith("{% endif %}"):

            sections.append(
                (
                    current_cond,
                    current_block
                )
            )

            break

        else:

            current_block.append(
                line
            )

    for cond, block in sections:

        if cond == "ELSE":

            return _render_block(
                block,
                context
            )

        if eval_condition(
            cond,
            context
        ):

            return _render_block(
                block,
                context
            )

    return []


def _render_block(lines, context):

    output = []

    i = 0

    while i < len(lines):

        line = lines[i].strip()

        if line.startswith("{% for"):

            m = re.match(
                r"{% for (\w+) in ([\w\.]+) %}",
                line
            )

            var_name, list_name = m.groups()

            end = find_block_end(
                lines,
                i,
                "for"
            )

            block = lines[i+1:end]

            iterable = resolve_var(
                list_name,
                context
            )

            if iterable:

                for item in iterable:

                    new_ctx = context.copy()

                    new_ctx[var_name] = item

                    output.extend(
                        _render_block(
                            block,
                            new_ctx
                        )
                    )

            i = end + 1

            continue

        elif line.startswith("{% if"):

            end = find_block_end(
                lines,
                i,
                "if"
            )

            block = lines[i:end+1]

            output.extend(
                process_if_block(
                    block,
                    context
                )
            )

            i = end + 1

            continue

        else:

            def replace_var(m):

                expr = m.group(1)

                return str(
                    resolve_var(
                        expr,
                        context
                    )
                )

            new_line = re.sub(
                r"{{(.*?)}}",
                replace_var,
                lines[i]
            )

            output.append(
                new_line
            )

        i += 1

    return output


def render_file(path, data):

    with open(
        path,
        "r",
        encoding="utf-8"
    ) as f:

        tpl = f.read()

    tpl = re.sub(
        r"\{#.*?#\}",
        "",
        tpl,
        flags=re.DOTALL
    )

    lines = tpl.split("\n")

    return "\n".join(
        _render_block(
            lines,
            data
        )
    )


# =========================================================
# CSV
# =========================================================

def load_csv_data(file_path):

    grouped = {}

    with open(
        file_path,
        newline="",
        encoding="utf-8"
    ) as f:

        reader = csv.DictReader(f)

        for row in reader:

            parent = row["parent"]

            if parent not in grouped:

                grouped[parent] = {
                    "parent": parent,
                    "parent_stripped":
                        remove_trailing_t(parent),
                    "fields": []
                }

            field = {

                "name":
                    row["child_name"],

                "type":
                    row["child_type"],

                "child_type":
                    row["child_type"],

                "child_name":
                    row["child_name"],

                "child_type_stripped":
                    remove_trailing_t(
                        row["child_type"]
                    ),

                "is_array":
                    clean_str(
                        row["is_array"]
                    ) == "TRUE",

                "array_size":
                    row["array_size"],

                "data_type":
                    clean_str(
                        row["data_type"]
                    ),

                "key":
                    clean_str(
                        row["key"]
                    ),

                "length_ref":
                    row["length_ref"],

                "present":
                    clean_str(
                        row["present"]
                    ),

                "bitmask":
                    row["bitmask"],

                "range_check":
                    clean_str(
                        row["range_check"]
                    ),

                "min":
                    row["min"],

                "max":
                    row["max"],

                "description":
                    clean_str(
                        row["description"]
                    ),
                "bitmask_name":
                       row["bitmask_name"]
            }

            grouped[parent]["fields"].append(
                field
            )

    return grouped


# =========================================================
# VALIDATE
# =========================================================

def validate_data(grouped):

    for parent, data in grouped.items():

        for field in data["fields"]:

            present = field["present"]

            bitmask = str(
                field["bitmask"]
            ).strip()

            if present == "O":

                if bitmask in [
                    "",
                    "0",
                    "0.0"
                ]:

                    raise ValueError(
                        f"{parent}.{field['name']} "
                        f"missing bitmask"
                    )

            if present == "M":

                if bitmask not in [
                    "",
                    "0",
                    "0.0"
                ]:

                    raise ValueError(
                        f"{parent}.{field['name']} "
                        f"must not have bitmask"
                    )

            if (
                field["range_check"]
                == "OCTET_STRING"
                and
                field["description"]
                == "VARIABLE"
                and
                not field["length_ref"]
            ):

                raise ValueError(
                    f"{parent}.{field['name']} "
                    f"missing length_ref"
                )


# =========================================================
# GENERATE
# =========================================================

def gen_data(grouped):

    for parent, data in grouped.items():

        HARDCODE_REGISTRY[
            "struct_hc"
        ][parent] = data

        safe_write(
            f"{HEADER_FOLDER}/header_il_{parent}.h",

            render_file(
                f"{TEMPLATES_DIR}/head.txt",
                data
            )
        )

        safe_write(
            f"{EN_FOLDER}/en_il_{parent}.c",

            render_file(
                f"{TEMPLATES_DIR}/en.txt",
                data
            )
        )

        safe_write(
            f"{DEC_FOLDER}/dec_il_{parent}.c",

            render_file(
                f"{TEMPLATES_DIR}/dec.txt",
                data
            )
        )

        safe_write(
            f"{HEADER_P_FOLDER}/header_parser_il_{parent}.h",

            render_file(
                f"{TEMPLATES_DIR}/head_p.txt",
                data
            )
        )

    root_data = {

        "parent":
            ROOT_STRUCT,

        "parent_stripped":
            remove_trailing_t(
                ROOT_STRUCT
            )
    }

    safe_write(
        f"{RESULT_FOLDER}/FUNCTION.c",

        render_file(
            f"{TEMPLATES_DIR}/function.txt",
            root_data
        )
    )


# =========================================================
# HARDCODE START
# =========================================================


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
        lines.extend(emit_primitive(field, field_path, indent_lv, idx_gen))

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

# for sheet_name, df in wb.items():
#     df.columns = df.columns.str.strip()
#     for row in df.itertuples(index=False):
#         if isinstance(row.length_ref, str) and row.length_ref != "":
#             length_ref_map.append((row.length_ref))



with open(DATA_EXCEL_PATH, newline="", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    reader.fieldnames = [name.strip() for name in reader.fieldnames]

    length_ref_map = [
        row["length_ref"].strip()
        for row in reader
        if row.get("length_ref") and row["length_ref"].strip() != ""
    ]

# ================= PRIMITIVE =================
def emit_primitive(field, field_path, indent_lv, idx_gen):
    lines = []
    name = field["name"]
    is_array = field["is_array"]
    idx = next(idx_gen)

    hc_value = simple_hc_value(field.get("min"), field.get("max"))
    indent = "\t" * indent_lv

    if is_array: # octet string
        lines.append(f"\n{indent}/*idx{idx} {name} S*/")
        if field.get("range_check") == "OCTET_STRING" and field.get("description").upper() == "VARIABLE":
            if field.get("length_ref") == "numbits":
                lines.append(
                f"""{indent}//memcpy({field_path}, (uint8_t[]){{0x01, 0x02}}, 2); /* example for octet string array  */
                for (int i = 0; i < {field_path.rsplit(".", 1)[0]}.{field.get("length_ref")}/8; i++) {{
                {field_path}[i] = 0x01 + i; /* hardcode for variable array */
                }}
                """)
                
                
            else:    
                # lines.append(f"{indent}/* {field_path} is an array primitive, assigning variale values */")
                # lines.append(f"{indent}{field_path}[0] = {hc_value};")
                # lines.append(f"{indent}{field_path}[1] = {hc_value};")
                # lines.append(f"\n.....................\n")
                # lines.append(f"{indent}{field_path}[max] = {hc_value};")
                # lines.append(f"{indent}{field_path} = {{0x01, 0x02}}; /* example for octet string array */")
                #lines.append(f"{indent}     //memcpy({field_path}, (uint8_t[]){{0x01, 0x02}}, 2); /* example for octet string array  */")
                lines.append(
                f"""{indent}//memcpy({field_path}, (uint8_t[]){{0x01, 0x02}}, 2); /* example for octet string array  */
                for (int i = 0; i < {field_path.rsplit(".", 1)[0]}.{field.get("length_ref")}; i++) {{
                {field_path}[i] = 0x01 + i; /* hardcode for variable array */
                }}
                """)

        elif field.get("range_check") == "OCTET_STRING" and field.get("description").upper() == "FIXED":
            #lines.append(f"{indent}/* {field_path} is an array primitive, assigning fixed values */")
            #lines.append(f"{indent}{field_path} = {{0x01, 0x02}}; /* example for octet string array */")
            lines.append(
            f"""{indent}//memcpy({field_path}, (uint8_t[]){{0x01,...}}, {field.get("array_size")}); /* example for octet string array fixed */
            for (int i = 0; i <  {field.get("array_size")}; i++) {{
            {field_path}[i] = 0x01 + i; /* hardcode for fixed array */
            }}""")
        lines.append(f"{indent}/*idx{idx} {name} E*/\n")

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
# def emit_octet_string(field, field_path, indent_lv):
#     lines = []
#     indent = "\t" * indent_lv

#     desc = str(field.get("description")).upper()
#     is_array = field["is_array"]

#     targets = [field_path]

#     if is_array:
#         targets = [f"{field_path}[0]", f"{field_path}[1]"]

#     for t in targets:
#         if desc == "FIXED":
#             lines.append(f"{indent}{t}.length = sizeof({t}.data);")
#         else:  # VARIABLE
#             lines.append(f"{indent}{t}.length = 2;")

#         lines.append(f"{indent}{t}.data[0] = 0x01;")
#         lines.append(f"{indent}{t}.data[1] = 0x02;")

#     return lines


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
        bitmask_name = field.get("bitmask_name")

        if present == "O":
            lines.append(f"\n{indent}#if 1 /*idx{idx}: {name} S */")
            # lines.append(f"{indent}\tif ({path}.bitmask |= {bitmask})")
            lines.append(f"{indent}\t{path}.{bitmask_name} |= {bitmask};")
            #lines.append(f"{indent}\t{{")
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
            #lines.append(f"{indent}\t}}")
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

# =========================================================
# TRACE START
# =========================================================



IDX = 0

def gen_desc(start):
    i = start
    while True:
        yield i
        i -= 1
        
        
        
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
def emit_get_primitive(field, field_path, indent_lv, idx_gen):
    indent = "\t" * indent_lv
    lines = []
    global IDX
    

    key = field.get("key", "UI32")
    fmt = get_printf_format(key)

    is_array = field["is_array"]
    range_check = str(field.get("range_check")).upper()
    desc = str(field.get("description")).upper()
    field_path = f"{field_path}.{field['name']}"
    # ===== OCTET STRING =====
    if range_check == "OCTET_STRING":
        idx = next(idx_gen)
        IDX +=1
        if desc == "FIXED":
            lines.append(f"{indent}/* {field_path} is an array primitive, fixed length */")
            lines.append(f"{indent}fprintf(stderr, \"[TRACE -O-F] {field_path}\\n\");")
            lines.append(f"{indent}for (int j{IDX} = 0; j{IDX} < {field.get('array_size')}; j{IDX}++)")
            lines.append(f"{indent}{{")
            lines.append(f'{indent}\tfprintf(stderr, "{field_path}[%d] = 0x%02X\\n", j{IDX}, {field_path}[j{IDX}]);')
            lines.append(f"{indent}}}")
        elif desc == "VARIABLE":
            if field.get("length_ref") == "numbits":
                lines.append(f"{indent}/* {field_path} is an array primitive, variable length in bits */")
                lines.append(f'{indent}fprintf(stderr, "[TRACE -O-V] {field_path} \\n\");')
                lines.append(f"{indent}for (int j{IDX} = 0; j{IDX} < {field_path.rsplit('.', 1)[0]}.{field.get('length_ref')}/8; j{IDX}++)")
                lines.append(f"{indent}{{")
                lines.append(f'{indent}\tfprintf(stderr, "{field_path}[%d] = 0x%02X\\n", j{IDX}, {field_path}[j{IDX}]);')
                lines.append(f"{indent}}}")
            else:
                lines.append(f"{indent}/* {field_path} is an array primitive, variable length */")
                lines.append(f'{indent}fprintf(stderr, "[TRACE -O-V] {field_path} \\n\");')
                lines.append(f"{indent}for (int j{IDX} = 0; j{IDX} < {field_path.rsplit(".", 1)[0]}.{field.get("length_ref")}; j{IDX}++)")
                lines.append(f"{indent}{{")
                lines.append(f'{indent}\tfprintf(stderr, "{field_path}[%d] = 0x%02X\\n", j{IDX}, {field_path}[j{IDX}]);')
                lines.append(f"{indent}}}")
        #idx_gen = gen_desc(idx_gen)
        IDX -= 1
        return lines

    # ===== ARRAY =====
    if is_array:
        size = 0
        size = field.get("array_size", 2)

        lines.append(f"{indent}for (int k{IDX} = 0; k{IDX} < {size}; k{IDX}++)")
        lines.append(f"{indent}{{")
        lines.append(f'{indent}\tfprintf(stderr, "[TRACE-ARR-????] {field_path}[%d] = {fmt}\\n", k{IDX}, {field_path}[k{IDX}]);')
        lines.append(f"{indent}}}")
    else:
        lines.append(f'{indent}fprintf(stderr, "[TRACE] {field_path} = {fmt}\\n", {field_path});')

    return lines


# ================= STRUCT =================
def emit_get_struct(field, field_path, registry, idx_gen, indent_lv):
    lines = []
    indent = "\t" * indent_lv

    #idx = next(idx_gen)
    global IDX

    child = field["child_type"]
    child_def = registry["struct_hc"][child]
    
    present = field.get("present")
    bitmask = field.get("bitmask")
    bimask_name = field.get("bitmask_name")
    
    if present == "O":
        lines.append(f"\n{indent}if ({field_path}.{bimask_name} & {bitmask})")
        lines.append(f"{indent}{{")
        
    field_path = f"{field_path}.{field['name']}"
    
    if field["is_array"]:
        
        #size = field.get("array_size", 2)
        size = 0
        if field.get("range_check") == "OCTET_STRING" and field.get("description").upper() == "VARIABLE":
            size = f"{field_path.rsplit('.', 1)[0]}.{field.get('length_ref')}"
        elif field.get("array_size"):
            size = field.get("array_size")

        idx = next(idx_gen)
        
        
        IDX += 1
        
        lines.append(f"{indent}for (int i{IDX} = 0; i{IDX} < {size}; i{IDX}++)")
        lines.append(f"{indent}{{")

        sub_path = f"{field_path}[i{IDX}]"

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
        IDX -= 1
        
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
    #next(idx_gen)

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
        lines.extend(emit_get_primitive(field, field_path, inner_lv, idx_gen))

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
void trace_{struct_name}({struct_name} *{root})
{{
{indent(body, " " * 4)}
}}
"""



#======================== PRINT STRUCTURE =================
def print_struct_tree(struct_name, registry, indent=0, visited=None, is_root=True):
    if visited is None:
        visited = set()

    prefix = "│   " * indent

    # ✅ chỉ in root
    if is_root:
        print(struct_name)

    # tránh loop
    if struct_name in visited:
        print(f"{prefix}(recursive)")
        return
    visited.add(struct_name)

    struct_def = registry["struct_hc"].get(struct_name)
    if not struct_def:
        return

    for field in struct_def["fields"]:
        field_name = field["name"]
        field_type = field["data_type"]
        child_type = field["child_type"]
        is_array = field["is_array"]

        arr = "[]" if is_array else ""
        line_prefix = "│   " * indent + "├── "

        if field_type == "PRIMITIVE":
            print(f"{line_prefix}{field_name} : {child_type}{arr}")

        elif field_type == "STRUCT":
            print(f"{line_prefix}{field_name} : {child_type}{arr}")

            # 👇 đệ quy nhưng KHÔNG in lại struct name
            print_struct_tree(
                child_type,
                registry,
                indent + 1,
                visited.copy(),
                is_root=False
            )
            
def write_struct_tree(struct_name, registry, file, indent=0, visited=None, is_root=True):
    if visited is None:
        visited = set()

    prefix = "│   " * indent
    branch = "├── " if indent > 0 else ""

    if is_root:
        file.write(f"{struct_name}\n")

    if struct_name in visited:
        file.write(f"{prefix}(recursive)\n")
        return
    visited.add(struct_name)

    struct_def = registry["struct_hc"].get(struct_name)
    if not struct_def:
        return

    for field in struct_def["fields"]:
        field_name = field["name"]
        field_type = field["data_type"]
        child_type = field["child_type"]
        is_array = field["is_array"]

        prefix_child = "│   " * indent

        if field_type == "PRIMITIVE":
            arr = "[]" if is_array else ""
            file.write(f"{prefix_child}├── {field_name} : {child_type}{arr}\n")

        elif field_type == "STRUCT":
            arr = "[]" if is_array else ""
            file.write(f"{prefix_child}├── {field_name} : {child_type}{arr}\n")

            # 👇 KHÔNG in lại struct_name nữa
            write_struct_tree(
                child_type,
                registry,
                file,
                indent + 1,
                visited.copy(),
                is_root=False
            )


#=====================NEW LOG TRACE ========================

def get_tree_helper_code():
    return r"""
static void trace_indent(int level)
{
    for (int i = 0; i < level; i++)
    {
        fprintf(stderr, "│   ");
    }
}

static void trace_node(int level, const char *name)
{
    trace_indent(level);
    fprintf(stderr, "%s\n", name);
}

static void trace_field_u32(int level, const char *name, unsigned int val)
{
    trace_indent(level);
    fprintf(stderr, "├── %s = %u\n", name, val);
}

static void trace_field_hex(int level, const char *name, unsigned char val)
{
    trace_indent(level);
    fprintf(stderr, "├── %s = 0x%02X\n", name, val);
}
"""

def emit_tree_primitive(field, field_path, indent_lv):
    lines = []
    name = field["name"]
    is_array = field["is_array"]

    indent = "\t" * indent_lv

    if is_array:
        size = field.get("array_size", 2)

        lines.append(f'{indent}trace_indent({indent_lv});')
        lines.append(f'{indent}fprintf(stderr, "├── {name}[]\\n");')

        lines.append(f"{indent}for (int i = 0; i < {size}; i++)")
        lines.append(f"{indent}{{")
        #lines.append(f'{indent}\ttrace_field_hex({indent_lv+1}, "{name}[i]", {field_path}[i]);')
        lines.append(f'{indent}\ttrace_indent({indent_lv+1});')
        lines.append(f'{indent}\tfprintf(stderr, "├── {name}[%d] = 0x%02X\\n", i, {field_path}[i]);')
        lines.append(f"{indent}}}")
    else:
        lines.append(f'{indent}trace_field_u32({indent_lv}, "{name}", {field_path});')

    return lines


def emit_tree_struct(field, field_path, registry, indent_lv):
    lines = []
    name = field["name"]
    child = field["child_type"]

    indent = "\t" * indent_lv

    lines.append(f'{indent}trace_indent({indent_lv});')
    lines.append(f'{indent}fprintf(stderr, "├── {name} : {child}\\n");')

    if field["is_array"]:
        size = field.get("array_size", 2)

        lines.append(f"{indent}for (int i = 0; i < {size}; i++)")
        lines.append(f"{indent}{{")

        lines.append(f'{indent}\ttrace_indent({indent_lv+1});')
        lines.append(f'{indent}\tfprintf(stderr, "├── {name}[%d]\\n", i);')

        sub_path = f"{field_path}[i]"

        lines.extend(
            emit_tree_struct_body(child, registry, sub_path, indent_lv + 2)
        )

        lines.append(f"{indent}}}")
    else:
        lines.extend(
            emit_tree_struct_body(child, registry, field_path, indent_lv + 1)
        )

    return lines

def emit_tree_struct_body(struct_name, registry, path, indent_lv):
    lines = []

    struct_def = registry["struct_hc"][struct_name]

    for field in struct_def["fields"]:
        field_path = f"{path}.{field['name']}"

        if field["data_type"] == "PRIMITIVE":
            lines.extend(
                emit_tree_primitive(field, field_path, indent_lv)
            )

        elif field["data_type"] == "STRUCT":
            lines.extend(
                emit_tree_struct(field, field_path, registry, indent_lv)
            )

    return lines


def get_struct_tree_wrapper(struct_name, registry):
    body_lines = []

    body_lines.append(f'trace_node(0, "{struct_name}");')

    root = f"p_{struct_name.replace('_t','')}"

    body_lines.extend(
        emit_tree_struct_body(
            struct_name,
            registry,
            root,
            1
        )
    )

    body = "\n".join(body_lines)

    # convert . -> ->
    body = body.replace(f"{root}.", f"{root}->")

    return f"""
/* helper start */

{get_tree_helper_code()}

/* helper end */

void trace_{struct_name}_tree({struct_name} *{root})
{{
{indent(body, " " * 4)}
}}
"""

# =========================================================
# MAIN
# =========================================================

def main():

    remove_all_data_structs()

    grouped = load_csv_data(DATA_EXCEL_PATH)

    validate_data(grouped)

    gen_data(grouped)

    hc = emit_struct_wrapper(ROOT_STRUCT, HARDCODE_REGISTRY )
    hc = replace_root_struct(hc, ROOT_STRUCT)

    with open( f"{RESULT_FOLDER}/HARD_CODE.c", "w",encoding="utf-8") as f:
        f.write(hc)

    trace = get_struct_wrapper( ROOT_STRUCT,HARDCODE_REGISTRY)

    with open( f"{RESULT_FOLDER}/GET_DATA.c",  "w",  encoding="utf-8" ) as f:
        f.write(trace)
        
        
        
    # trace tree
    tree_code = get_struct_tree_wrapper(ROOT_STRUCT, HARDCODE_REGISTRY)

    with open(f"{RESULT_FOLDER}/GET_DATA_TREE.c", "w", encoding="utf-8") as f:
        f.write(tree_code)

    print("Generated: GET_DATA_TREE.c")


    print("\n===== STRUCT TREE =====\n")
    print_struct_tree(ROOT_STRUCT, HARDCODE_REGISTRY)
    with open(f"{RESULT_FOLDER}/STRUCT_TREE.txt", "w", encoding="utf-8") as f:
        write_struct_tree(ROOT_STRUCT, HARDCODE_REGISTRY, f)

if __name__ == "__main__":

    main()