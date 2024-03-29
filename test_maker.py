from olympics import *
from random import randrange
import os


'''
functions to test:
1. StatusType add_team(int teamId)
2. StatusType remove_team(int teamId)
3. StatusType add_player(int teamId, int playerStrength)
4. StatusType remove_newest_player(int teamId)
5. output_t<int> play_match(int teamId1, int teamId2)
6. output_t<int> num_wins_for_team(int teamId)
7. output_t<int> get_highest_ranked_team()
8. StatusType unite_teams(int teamId1, int teamId2)
9. output_t<int> play_tournament(int lowPower, int highPower)
'''

def write_to_file(type, test_num, lines_arr):
    file_name = ""
    if type == "in":
        file_name = f"test{str(test_num)}.in"

    elif type == "out":
        file_name = f"test{str(test_num)}.out"

    elif type == "border":
        file_name = f"test{str(test_num)}.z---------------------"

    with open(f"./python_tester/tests/{file_name}", 'w') as f:
        for line in lines_arr:
            f.write(f"{line}\n")

def make_test(test_num, test_len, command_arr):
    print(f"[+] Making test {test_num}...")
    input_file_commands = []
    output_file_commands = []

    command_arr_len = len(command_arr)

    paris24 = Olympics()
    
    # If you want specific commands to run less often, put them here
    throttle_commands = ["unite_teams", "play_tournament", "remove_newest_player", "remove_team"]

    # And choose how often you want them to run:
    throttle_amount = 100 # 100% = no throttle effect
    
    i = 0
    while(i<test_len):
         # Change ranges as you see fit
        team1_id = randrange(-2, 30)
        team2_id = randrange(-2, 30)
        player_strength = randrange(10000, 50000)
        tournament_low = randrange(800, 3500)
        tournament_high = randrange(5000, 8000)

        random_command = command_arr[randrange(0, command_arr_len)]

        if random_command in throttle_commands :
            percent = randrange(1, 100)
            if percent > throttle_amount:
                continue
        
        if random_command in ["add_team", "remove_team", "remove_newest_player", "num_wins_for_team"]:
            args = [team1_id]
        
        elif random_command in ["add_player"]:
            args = [team1_id, player_strength]

        elif random_command in ["play_match", "unite_teams"]:
            args = [team1_id, team2_id]

        elif random_command in ["get_highest_ranked_team"]:
            args = []

        elif random_command in ["play_tournament"]:
            args = [tournament_low, tournament_high]
        
        method_to_call = getattr(paris24, random_command)
        result = method_to_call(*args)
        
        if type(result) == list:
            result = ", ".join(str(x) for x in result)
        input_file_commands.append(f"{random_command} {' '.join(str(x) for x in args)}")
        output_file_commands.append(f"{random_command}: {result}")

        write_to_file("in", test_num, input_file_commands)
        write_to_file("out", test_num, output_file_commands)
        write_to_file("border", test_num, [])

        i+=1

def make_tests(num_tests_to_make):
    default_tests_length = 5000

    make_test(1, default_tests_length, ["add_team"])
    make_test(2, default_tests_length, ["add_team", "remove_team"])
    make_test(3, default_tests_length, ["add_team", "remove_team", "add_player"])
    make_test(4, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player"])
    make_test(5, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match"])
    make_test(6, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team"])
    make_test(7, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "get_highest_ranked_team"])
    
    # Unite tests
    make_test(8, default_tests_length, ["add_team", "unite_teams"])
    make_test(9, default_tests_length, ["add_team", "remove_team", "unite_teams"])
    make_test(9, default_tests_length, ["add_team", "remove_team", "add_player", "unite_teams"])
    make_test(10, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "unite_teams"])
    make_test(11, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "unite_teams"])
    make_test(12, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "unite_teams"])
    make_test(13, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "get_highest_ranked_team", "unite_teams"])

    # Tournament tests
    make_test(14, default_tests_length, ["add_team", "unite_teams", "play_tournament"])
    make_test(15, default_tests_length, ["add_team", "remove_team", "unite_teams", "play_tournament"])
    make_test(16, default_tests_length, ["add_team", "remove_team", "add_player", "unite_teams", "play_tournament"])
    make_test(17, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "unite_teams", "play_tournament"])
    make_test(18, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "unite_teams", "play_tournament"])
    make_test(19, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "unite_teams", "play_tournament"])
    
    # All commands
    make_test(20, default_tests_length, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "get_highest_ranked_team", "unite_teams", "play_tournament"])

    # Mega test
    make_test(21, default_tests_length*5, ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "get_highest_ranked_team", "unite_teams", "play_tournament"])

    commands = ["add_team", "remove_team", "add_player", "remove_newest_player", "play_match", "num_wins_for_team", "get_highest_ranked_team", "unite_teams", "play_tournament"]
    for i in range(22, num_tests_to_make+1):
        random_commands = []
        num_commands_to_run = randrange(1, 9)
        for j in range(num_commands_to_run): 
            random_command_num = randrange(1, 9)
            random_commands.append(commands[random_command_num])
        make_test(i, default_tests_length, random_commands)

def run_tests(num_tests):
    print("Running tests:")
    for i in range(1, num_tests+1):
        terminal_command = f"./a.out < python_tester/tests/test{i}.in > python_tester/tests/test{i}.us"
        print(terminal_command)
        os.system(terminal_command)

    print("\nChecking diffs:")
    for i in range(1, num_tests+1):
        terminal_command = f"diff -w -q ./python_tester/tests/test{i}.out ./python_tester/tests/test{i}.us"
        # print(terminal_command)
        os.system(terminal_command)

    print("\nRunning valgrind: ")
    success_msg = "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
    for i in range(1, num_tests+1):
        valgrind_command = f"valgrind --leak-check=full --track-origins=yes ./olympics.out < python_tester/tests/test{i}.in 1> /dev/null 2> ./python_tester/tests/test{i}.val"
        print(valgrind_command)
        os.system(valgrind_command)

    print("\nChecking valgrind outputs: ")
    success_msg = "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
    for i in range(1, num_tests+1):
        grep_command = f"grep -L '{success_msg}' ./python_tester/tests/test{i}.val"
        # print(grep_command)
        os.system(grep_command)

def main():
    num_tests_to_make = 50
    make_tests(num_tests_to_make)
    run_tests(num_tests_to_make)

main()