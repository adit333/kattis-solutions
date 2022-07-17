"""https://open.kattis.com/problems/goodmorning"""


import sys
from typing import Set


number_grid = {'1': [0, 0], '2': [1, 0], '3': [2, 0],
               '4': [0, 1], '5': [1, 1], '6': [2, 1],
               '7': [0, 2], '8': [1, 2], '9': [2, 2],
                            '0': [1, 3]
}


def generate_all_possible_valid_nums(max_k: int) -> Set:
    valid_nums = set()

    for num in range(1, max_k):
        num = str(num)
        valid = True
        for i in range(1, len(num)):
            if not(number_grid[num[i]][0] >= number_grid[num[i-1]][0] and   # the x-coord should be to the right
                   number_grid[num[i]][1] >= number_grid[num[i-1]][1]):     # the y-coord should be to the right
                valid = False
                break
        if valid:
            valid_nums.add(int(num))
    
    return valid_nums

def good_morning(k: int, valid_nums) -> None:
    delta = 1
    while k not in valid_nums:
        if k - delta in valid_nums:
            k -= delta
            break
        elif k + delta in valid_nums:
            k += delta
            break
        delta += 1
    print(k)    


def main():
    valid_nums = generate_all_possible_valid_nums(max_k=201)
    input_lines = sys.stdin.read().splitlines()
    for input_line in input_lines[1:]:
        good_morning(int(input_line), valid_nums)


if __name__ == '__main__':
    main()
