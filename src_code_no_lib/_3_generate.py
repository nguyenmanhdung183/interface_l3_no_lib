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
                    )
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
# HARDCODE
# =========================================================

def emit_struct_wrapper(
    struct_name,
    registry
):

    root = remove_trailing_t(
        struct_name
    )

    return f"""
xnap_return_et assign_hardcode_value_{struct_name}
(
    {struct_name} *p_{root}
)
{{
    return XNAP_SUCCESS;
}}
"""


# =========================================================
# TRACE
# =========================================================

def get_struct_wrapper(
    struct_name,
    registry
):

    root = remove_trailing_t(
        struct_name
    )

    return f"""
#include <stdio.h>

void trace_{struct_name}
(
    {struct_name} *p_{root}
)
{{
}}
"""


# =========================================================
# MAIN
# =========================================================

def main():

    remove_all_data_structs()

    grouped = load_csv_data(
        DATA_EXCEL_PATH
    )

    validate_data(
        grouped
    )

    gen_data(
        grouped
    )

    hc = emit_struct_wrapper(
        ROOT_STRUCT,
        HARDCODE_REGISTRY
    )

    with open(
        f"{RESULT_FOLDER}/HARD_CODE.c",
        "w",
        encoding="utf-8"
    ) as f:

        f.write(
            hc
        )

    trace = get_struct_wrapper(
        ROOT_STRUCT,
        HARDCODE_REGISTRY
    )

    with open(
        f"{RESULT_FOLDER}/GET_DATA.c",
        "w",
        encoding="utf-8"
    ) as f:

        f.write(
            trace
        )


if __name__ == "__main__":

    main()