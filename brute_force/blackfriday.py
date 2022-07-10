"""https://open.kattis.com/problems/blackfriday"""

import sys
from typing import Counter, List

def blackfriday(dice_rolls: List[int]) -> None:
    rolls_count = Counter(dice_rolls)
    rolls_count = list(rolls_count.items())
    rolls_count.sort(key=lambda x: x[0], reverse=True)
    
    for roll, count in rolls_count:
        if count == 1:
            print(dice_rolls.index(roll)+1)
            return
    
    print('none')

def main():
    input_lines = sys.stdin.read().splitlines()
    n = int(input_lines[0])
    dice_rolls = list(map(int, input_lines[1].split()))
    blackfriday(dice_rolls)

if __name__ == '__main__':
    main()