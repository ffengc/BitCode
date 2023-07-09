import os
import shutil

def delete_git_files(directory):
    for root, dirs, files in os.walk(directory, topdown=False):
        for file in files:
            if "ab" in file.lower():
                file_path = os.path.join(root, file)
                os.remove(file_path)
                print(f"Deleted file: {file_path}")

        for dir in dirs:
            if "ab" in dir.lower():
                dir_path = os.path.join(root, dir)
                delete_git_files(dir_path)  # 递归进入子目录并删除
                if os.path.isdir(dir_path) and not os.listdir(dir_path):
                    os.rmdir(dir_path)
                    print(f"Deleted empty directory: {dir_path}")
                else:
                    shutil.rmtree(dir_path)
                    print(f"Deleted directory: {dir_path}")

if __name__ == "__main__":
    target_directory = "/Users/demac/MyFiles/Bit/C++"  # 指定目标目录，这里使用当前目录
    delete_git_files(target_directory)
