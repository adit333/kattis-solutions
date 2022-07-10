"""https://open.kattis.com/problems/golombrulers"""

import sys
from typing import List


def golumb_rulers(marks: List[int]) -> None:
    len_set = set()
    marks.sort()
    n = marks[-1]

    for i in range(len(marks)):
        for j in range(i+1, len(marks)):
            dist = marks[j] - marks[i]
            if dist in len_set:
                print('not a ruler')
                return
            else:
                len_set.add(dist)
    
    missing = []
    for i in range(1, n+1):
        if i not in len_set:
            missing.append(i)
    
    if missing:
        print(f'missing', end=' ')
        print(*missing)
    else:
        print('perfect')



def main():
    input_lines = sys.stdin.read().splitlines()
    for input_line in input_lines:
        golumb_rulers(list(map(int, input_line.split())))


if __name__ == '__main__':
    main()