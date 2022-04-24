"""https://ualberta.kattis.com/sessions/x2xwog/problems/tetration

Approach: simply compute a ^ (1/a)
"""

import sys

def main():
    input_lines = sys.stdin.read().splitlines()
    num = float(input_lines[0])
    print(f'{pow(num, 1/num):.6f}')


if __name__ == '__main__':
    main()
