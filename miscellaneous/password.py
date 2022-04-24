"""https://ualberta.kattis.com/sessions/x2xwog/problems/password
"""

import sys
from typing import List


def expected_num_of_tries(passwords: List[int]) -> None:
    passwords.sort(reverse=True)
    expected_num = 0
    for i in range(len(passwords)):
        expected_num += (i+1) * passwords[i]
    print('{:.4f}'.format(expected_num))

def main():
    input_lines = sys.stdin.read().splitlines()
    passwords = []
    for input_line in input_lines[1:]:
        passwords.append(float(input_line.split()[1]))
    expected_num_of_tries(passwords)

if __name__ == '__main__':
    main()
