"""https://ualberta.kattis.com/sessions/jot9wq/problems/sim
"""

import sys
from typing import List


def sim(input: str) -> None:
    result = []
    cursor = 0  # The last vacant position, i.e. the position in which the next char would go
    for char in input:
        if char == '<':
            if cursor > 0:
                result.pop(cursor-1)
                cursor -= 1
        elif char == ']':
            cursor = len(result)
        elif char == '[':
            cursor = 0
        else:
            result.insert(cursor, char)
            cursor += 1
    print(''.join(result))

def main():
    # input_lines = sys.stdin.read().splitlines()
    # num_of_cases = input_lines[0]
    # for input in input_lines[1:]:
    #     sim(input)
    sim('my ]]name]] is]] steva<en]<n halim]]]]]')
    sim('<<hate<<<<loves[steva<en ] cs2040c< and also cs2040c')

if __name__ == '__main__':
    main()