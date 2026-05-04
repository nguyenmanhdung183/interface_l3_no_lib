import json
import os
import re

#=======================================================================
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

DATA_C_PATH = os.path.join(BASE_DIR, "..", "struct_input", "data.c")
OTHER_C_PATH = os.path.join(BASE_DIR, "..", "struct_input", "other.c")
STRUCT_LIST_PATH = os.path.join(BASE_DIR, "..", "data", "struct_list.txt")
MSG_CONFIG_PATH = os.path.join(BASE_DIR, "..", "msg_config.cfg")

EXISTED_STRUCTS_PATH = os.path.join(BASE_DIR, "..", "existed.txt")

EN_FOLDER = os.path.join(BASE_DIR, "..", "output", "en")
DEC_FOLDER = os.path.join(BASE_DIR, "..", "output", "dec")
GET_DATA_FOLDER = os.path.join(BASE_DIR, "..", "output", "get_data")
HEADER_FOLDER = os.path.join(BASE_DIR, "..", "output", "header")
HEADER_P_FOLDER = os.path.join(BASE_DIR, "..", "output", "header_parser")


TEMPLATES_DIR = os.path.join(BASE_DIR, "..", "templates")
DEC_TEMPLATE_PATH = os.path.join(TEMPLATES_DIR, "dec_template.j2")
EN_TEMPLATE_PATH = os.path.join(TEMPLATES_DIR, "en_template.j2")
GET_DATA_TEMPLATE_PATH = os.path.join(TEMPLATES_DIR, "get_data_template.j2")
HEADER_TEMPLATE_PATH = os.path.join(TEMPLATES_DIR, "header_template.j2")
HEADER_PARSER_TEMPLATE_PATH = os.path.join(TEMPLATES_DIR, "header_parser_template.j2")

RESULT_FOLDER = os.path.join(BASE_DIR, "..", "1.RESULTS")

ROOT_STRUCT = None

with open (MSG_CONFIG_PATH, "r") as f:
    #root_struct = f.read().strip()
    ROOT_STRUCT = f.readline().strip()  # đọc dòng 1

#=======================================================================
PRIMITIVE_LIST = {
    "UI8": ["uint8_t", "UInt8", "uint8_t"],
    "UI16": ["uint16_t", "UInt16", "ue_index_t"],
    "UI32": ["uint32_t", "UInt32", "uint32_t"],
    "UI64": ["uint64_t", "UInt64", "uint64_t"],
    "I8": ["int8_t", "Int8", "int8_t"],
    "I16": ["int16_t", "Int16", "int16_t"],
    "I32": ["int32_t", "Int32", "int32_t"],
    "I64": ["int64_t", "Int64", "int64_t"],
    "SI8": ["signed char", "SInt8", "sint8_t"],
    "SI16": ["signed short", "SInt16", "sint16_t"],
    "SI32": ["signed int", "SInt32", "sint32_t"],
    "SI64": ["signed long", "SInt64", "sint64_t"],
}




PRIMITIVES = set(sum(PRIMITIVE_LIST.values(), []))

def read_file(path):
    with open(path, "r") as f:
        return f.read()

def clear_log():
    log_path = os.path.join(RESULT_FOLDER, "log.txt")
    if os.path.exists(log_path):
        os.remove(log_path)

def print_log_info(message):
    print(f"[INFO] {message}")
    with open(os.path.join(RESULT_FOLDER, "log.txt"), "a") as f:
        f.write(f"[INFO] {message}\n")

def extract_structs(code):
    """
    Extract typedef struct blocks
    """
    # pattern = re.compile(
    #     r"typedef\s+struct\s*\{(.*?)\}\s*(\w+)\s*;",
    #     re.S
    # )
    pattern = re.compile(
        r"typedef\s+struct\s+(?:\w+\s*)?\{(.*?)\}\s*(\w+)\s*;",
        re.S
    )
    structs = {}

    for body, name in pattern.findall(code):
        structs[name] = body.strip()

    return structs


def parse_fields(struct_body):
    """
    Parse fields inside struct
    """
    fields = []
    lines = struct_body.split("\n")

    for line in lines:
        line = line.strip()
        if not line or line.startswith("//"):
            continue

        # remove comments /**^ ... ^*/
        line = re.sub(r"/\*\*.*?\*/", "", line)

        # match: type name or type name[...]
        match = re.match(r"(\w+)\s+(\w+)", line)
        if match:
            field_type = match.group(1)
            field_name = match.group(2)
            fields.append((field_type, field_name))

    return fields


def is_primitive(type_name):
    return type_name in PRIMITIVES


def build_tree(struct_name, structs, visited=None):
    if visited is None:
        visited = set()

    if struct_name in visited:
        return {"type": struct_name, "recursive": True}

    visited.add(struct_name)

    if struct_name not in structs:
        return {"type": struct_name, "unknown": True}

    tree = {"type": struct_name, "fields": []}

    fields = parse_fields(structs[struct_name])

    for f_type, f_name in fields:
        if is_primitive(f_type):
            tree["fields"].append({
                "name": f_name,
                "type": f_type,
                "primitive": True
            })
        else:
            subtree = build_tree(f_type, structs, visited.copy())
            tree["fields"].append({
                "name": f_name,
                "type": f_type,
                "primitive": False,
                "children": subtree
            })

    return tree
def topo_sort_structs(structs, root):
    def get_deps(struct_name):
        body = structs[struct_name]
        deps = set()

        for f_type, _ in parse_fields(body):
            if not is_primitive(f_type) and f_type in structs:
                deps.add(f_type)

        return deps

    visited = set()
    result = []

    def dfs(node):
        if node in visited:
            return

        visited.add(node)

        for dep in get_deps(node):
            dfs(dep)

        result.append(node)

    dfs(root)
    return result

def make_struct_list(structs):
    sorted_structs = topo_sort_structs(structs, ROOT_STRUCT)
    with open(STRUCT_LIST_PATH, "w") as f:
        for struct_name in sorted_structs:
            f.write(struct_name + "\n")
           
           
# def append_to_primitive_list(code):
#     pattern = re.compile(r"typedef\s+(\w[\w\s\*]+)\s+(\w+);")
#     for type_def, type_name in pattern.findall(code):
#         type_name = type_name.strip()
#         if type_name not in PRIMITIVE_LIST:
#             PRIMITIVE_LIST[type_name] = [type_def.strip()]
#             PRIMITIVES.add(type_def.strip())
                
                
import re

PRIMITIVES = set()

import re

PRIMITIVES = set()

def append_to_primitive_list(code):
    """
    Quét tất cả typedef trong code C và cập nhật PRIMITIVE_LIST,
    hỗ trợ typedef chain (typedef từ typedef khác)
    """
    pattern = re.compile(r"typedef\s+([\w\d_\*\s]+?)\s+(\w+)\s*;")   
    typedefs = pattern.findall(code)

    updated = True
    while updated:
        updated = False
        for type_def, type_name in typedefs:
            type_def = type_def.strip()
            type_name = type_name.strip()
            
            # Kiểm tra tất cả key trong PRIMITIVE_LIST
            for key, values in PRIMITIVE_LIST.items():
                if type_def in values or type_def in PRIMITIVES:
                    if type_name not in PRIMITIVE_LIST[key]:
                        PRIMITIVE_LIST[key].append(type_name)
                        PRIMITIVES.add(type_name)
                        updated = True
                    break
                
                
#===============================MAIN============================================
def main():
    #code = read_file(DATA_C_PATH) + "\n" + read_file(OTHER_C_PATH)
    clear_log()
    #read all .c .h in STRUCT_INPUT folder
    code = ""
    for filename in os.listdir(os.path.join(BASE_DIR, "..", "struct_input")):
        if filename.endswith(".c") or filename.endswith(".h"):
            code += "\n" + read_file(os.path.join(BASE_DIR, "..", "struct_input", filename))

    for filename in os.listdir(os.path.join(BASE_DIR, "..", "code_5G_header")):
        if filename.endswith(".c") or filename.endswith(".h"):
            code += "\n" + read_file(os.path.join(BASE_DIR, "..", "code_5G_header", filename))
    
    structs = extract_structs(code)
    append_to_primitive_list(code)

    for key, types in PRIMITIVE_LIST.items():
        #print(f"{key:4} => {', '.join(types)}")
        print_log_info(f"{key:4} => {', '.join(types)}")
    
    # build tree từ struct top
    tree = build_tree(ROOT_STRUCT, structs)
    make_struct_list(structs)
    print(json.dumps(tree, indent=2))


if __name__ == "__main__":
    main()