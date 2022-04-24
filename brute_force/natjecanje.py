"""https://ualberta.kattis.com/sessions/zy3te5/problems/natjecanje
"""

import sys
from typing import List, Set


def natjecanje(n: int, reserve_kayaks: Set[int], damaged_kayaks: Set[int]) -> None:
    for i in range(1, n+1):
        if i in damaged_kayaks:
            if i > 1 and i - 1 in reserve_kayaks:
                damaged_kayaks.remove(i)
                reserve_kayaks.remove(i-1)
            elif i < n and i + 1 in reserve_kayaks:
                damaged_kayaks.remove(i)
                reserve_kayaks.remove(i+1)
    print(len(damaged_kayaks))

def main():
    input_lines = sys.stdin.read().splitlines()
    n, s, r = list(map(int, input_lines[0].split()))
    damaged_kayaka = set(map(int, input_lines[1].split()))
    reserve_kayaks = set(map(int, input_lines[2].split()))
    natjecanje(n, reserve_kayaks, damaged_kayaka)


if __name__ == '__main__':
    main()