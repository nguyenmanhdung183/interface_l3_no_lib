from _3_generate import *
import glob
import os




def get_list_of_files():
    with open(STRUCT_LIST_PATH, "r") as f:
        return [line.strip() for line in f if line.strip()]
    

def remove_all_tab_inside_brace(file_path):
    """
    Xóa tất cả tab nằm bên trong các block {} trong file,
    giữ nguyên tab ngoài block.
    """
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()

    result = []
    stack = []  # stack lưu vị trí brace mở
    i = 0
    while i < len(content):
        char = content[i]
        if char == '{':
            stack.append(len(result))
            result.append(char)
        elif char == '}':
            if stack:
                start = stack.pop()
                # Xóa tab bên trong từ start+1 đến len(result)
                for j in range(start + 1, len(result)):
                    if result[j] == '\t':
                        result[j] = ''
            result.append(char)
        else:
            # nếu trong block, xóa tab
            if stack and char == '\t':
                # bỏ tab
                pass
            else:
                result.append(char)
        i += 1

    # chuyển list về string
    new_content = ''.join(result)

    with open(file_path, "w", encoding="utf-8") as f:
        f.write(new_content)

def indent_c_code(file_path, tab_size=1):
    """
    Chỉ indent các dòng nằm trong {} bằng tab,
    giữ nguyên các dòng ngoài block và các dòng đã đúng indent.
    """
    #remove_all_tab_inside_brace(file_path)  # đảm bảo không có tab nào trong {}
    
    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    new_lines = []
    indent_level = 0
    inside_block = False

    for line in lines:
        stripped_line = line.rstrip("\n")

        # đếm tab hiện tại
        current_indent = 0
        while current_indent < len(stripped_line) and stripped_line[current_indent] == "\t":
            current_indent += 1
        content = stripped_line[current_indent:]  # nội dung thực tế
        
        
        
        #nếu xuất hiện { vaf } trên cùng dòng thì không đọc đó vào indent mà chỉ tab đúng số lần indent hiện tại
        if "{" in content and "}" in content:
            brace_pos = content.find("{")
            if "=" in content[:brace_pos]:
                new_lines.append("\t"* tab_size + content)
                continue
            
            
            
        # Nếu có mở brace trên dòng, indent dòng đó
        if "{" in content:
            target_indent = indent_level * tab_size
            if current_indent != target_indent:
                new_lines.append("\t" * target_indent + content)
            else:
                new_lines.append(stripped_line)
            indent_level += 1
            inside_block = True
            continue

        # Nếu có đóng brace trên dòng, giảm indent trước khi viết
        if "}" in content:
            indent_level = max(indent_level - 1, 0)
            target_indent = indent_level * tab_size
            if current_indent != target_indent:
                new_lines.append("\t" * target_indent + content)
            else:
                new_lines.append(stripped_line)
            if indent_level == 0:
                inside_block = False
            continue

        # Nếu đang trong block {}, indent nếu chưa đúng
        if inside_block:
            target_indent = indent_level * tab_size
            if current_indent != target_indent:
                new_lines.append("\t" * target_indent + content)
            else:
                new_lines.append(stripped_line)
        else:
            # ngoài block giữ nguyên
            new_lines.append(stripped_line)

    # ghi đè file
    with open(file_path, "w", encoding="utf-8") as f:
        f.write("\n".join(new_lines) + "\n")

    #print(f"Formatted: {file_path}")


        
def update_existed_structs(existed_structs, code):
    print_log_info(f"Updating existed 5G structs: {existed_structs}")

    # =========================
    # 1 + 2. typedef struct {...} A;
    # hỗ trợ xuống dòng + space + tab
    # =========================
    struct_pattern = re.findall(
        r"typedef\s+struct\s+(?:\w+\s*)?\s*\{[\s\S]*?\}\s*(\w+)\s*;",
        code
    )

    for name in struct_pattern:
        existed_structs.append(name)

    # =========================
    # 3. typedef B A;
    # =========================
    alias_pattern = re.findall(
        r"typedef\s+([\w_]+)\s+(\w+)\s*;",
        code
    )

    # resolve chain typedef
    updated = True
    while updated:
        updated = False
        for base, alias in alias_pattern:
            if base in existed_structs and alias not in existed_structs:
                existed_structs.append(alias)
                updated = True

    print_log_info(f"Updated existed 5G structs: {existed_structs}")
    return existed_structs



def main():
    struct_names = get_list_of_files()
    existed_struct = []
    with open(EXISTED_STRUCTS_PATH, "r") as existed_struct_file:
        existed_structs = [line.strip() for line in existed_struct_file if line.strip()]
        print_log_info(f"Existed structs: {existed_structs}")
        for struct in existed_structs:
            if struct in struct_names:
                existed_struct.append(struct)
                
                
    code_5G = ""
    for filename in os.listdir(os.path.join(BASE_DIR, "..", "code_5G_header")):
        if filename.endswith(".c") or filename.endswith(".h"):
            code_5G += "\n" + read_file(os.path.join(BASE_DIR, "..", "code_5G_header", filename))
          
    update_existed_structs(existed_struct, code_5G)           
                
    print(f"Found {struct_names} structs to format and merge.")
    content = ""
    
    
    path_dest_header = f"{RESULT_FOLDER}/HEADER_COMPOSER.h"
    for struct_name in struct_names:
        if struct_name in existed_struct:
            print(f"Skip (already existed): {struct_name}")
            continue
        path = f"{HEADER_FOLDER}/header_il_{struct_name}.h"
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                content += f.read()
            #make file if not exist
            os.makedirs(os.path.dirname(path_dest_header), exist_ok=True)
    with open(path_dest_header, "w", encoding="utf-8") as f:
        f.write(content)

    
    
    path_dest_en = f"{RESULT_FOLDER}/EN.c"
    content = ""
    for struct_name in struct_names:
        if struct_name in existed_struct:
            print(f"Skip (already existed): {struct_name}")
            continue
        path = f"{EN_FOLDER}/en_il_{struct_name}.c"
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                content += f.read()
    with open(path_dest_en, "w", encoding="utf-8") as f:
        f.write(content)
        
    path_dest_dec = f"{RESULT_FOLDER}/DEC.c"
    content = ""
    for struct_name in struct_names:
        if struct_name in existed_struct:
            print(f"Skip (already existed): {struct_name}")
            continue
        path = f"{DEC_FOLDER}/dec_il_{struct_name}.c"
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                content += f.read()
    with open(path_dest_dec, "w", encoding="utf-8") as f:
        f.write(content)
        
    # path_dest_get_data = f"{RESULT_FOLDER}/GET_DATA.c"
    # content = ""
    # for struct_name in struct_names:
    #     if struct_name in existed_struct:
    #         print(f"Skip (already existed): {struct_name}")
    #         continue
    #     path = f"{GET_DATA_FOLDER}/get_data_il_{struct_name}.c"
    #     if os.path.exists(path):
    #         with open(path, "r", encoding="utf-8") as f:
    #             content += f.read()
    # with open(path_dest_get_data, "w", encoding="utf-8") as f:
    #     f.write(content)
        
        
    path_dest_header_parser = f"{RESULT_FOLDER}/HEADER_PARSER.h"
    content = ""
    for struct_name in struct_names:
        if struct_name in existed_struct:
            print(f"Skip (already existed): {struct_name}")
            continue
        path = f"{HEADER_P_FOLDER}/header_parser_il_{struct_name}.h"
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                content += f.read()
    with open(path_dest_header_parser, "w", encoding="utf-8") as f:
        f.write(content)
        
    #folder = "."  # folder hiện tại, đổi nếu cần
    folder = RESULT_FOLDER
    for file in glob.glob(os.path.join(folder, "*.c")) + glob.glob(os.path.join(folder, "*.h")):
        indent_c_code(file)
        print(f"Formatted: {file}")
            
        
if __name__ == "__main__":
    main()