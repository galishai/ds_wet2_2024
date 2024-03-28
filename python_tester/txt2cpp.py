import sys

test_num = 13
in_file_path = f'./python_tester/tests/test{test_num}.in'
out_file_path = f'./test{test_num}.cpp'

with open(out_file_path, 'w') as o:
    pre = '''#include <iostream>
#include "olympics24a2.h"

int main() {
    olympics_t paris24;
'''
    o.writelines(pre)

with open(in_file_path, 'r') as f:
    data = f.readlines()

for line in data:
    new_line = ""
    command = [arg.strip() for arg in line.split(' ')]
    if len(command) == 1:
        new_line = f"paris24.{command[0]}()"

    elif len(command) == 2:
        new_line = f"paris24.{command[0]}({command[1]})"
    
    elif len(command) == 3:
        new_line = f"paris24.{command[0]}({command[1]}, {command[2]})"

    else:
        print("[!] Format error: {line}")
        sys.exit()

    if command[0] in ["get_highest_ranked_team", "num_wins_for_team", "play_match", "play_tournament"]:
        new_line = f"\tstd::cout << (int){new_line}.ans() << std::endl;"
    else:
        new_line = f"\tstd::cout << (int){new_line} << std::endl;"
    
    with open(out_file_path, 'a') as o:
        o.write(new_line)
        o.write('\n')

with open(out_file_path, 'a') as o:
    post = '}'
    o.writelines(post)