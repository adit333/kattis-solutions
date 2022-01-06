"""
https://ualberta.kattis.com/sessions/xq7r95/problems/lostlineup
Algorithm:
- Iterate over the array, giving person (i+1) position array[i]+2
"""

from typing import List

def lost_lineup(n: int, spacings: List[int]) -> List[int]:
    lineup = [None] * n
    lineup[0] = 1
    
    for i in range(len(spacings)):
        person = i + 2
        position = spacings[i] + 1
        lineup[position] = person
    for num in lineup:
        print(num, end=' ')


def main():
    #lost_lineup(4, [1, 2, 0])
    n = int(input())
    spacings = list(map(int, input().split()))
    lost_lineup(n, spacings)


if __name__ == '__main__':
    main()

