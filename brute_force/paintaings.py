"""https://open.kattis.com/problems/paintings"""

import sys
from typing import Dict, List


def painings_recurse(hideous_pairs: Dict[str, str], remaining_colors: List[str],
                     current_colors: List[str], valid_paintings: List[List[str]]) -> None:
    if len(remaining_colors) == 0:
        valid_paintings.append(list(current_colors))
        return
    
    for i, color in enumerate(remaining_colors):
        if len(current_colors) == 0 or color not in hideous_pairs[current_colors[-1]]:
            current_colors.append(color)
            painings_recurse(hideous_pairs, remaining_colors[:i]+remaining_colors[i+1:],
                current_colors, valid_paintings)
            current_colors.pop()


def paintings(colors: List[str], hideous_pairs: Dict[str, str]) -> None:
    valid_paintings = []
    current_colors = []
    painings_recurse(hideous_pairs, colors, current_colors, valid_paintings)

    print(len(valid_paintings))
    print(*valid_paintings[0])


def main():
    input_lines = sys.stdin.read().splitlines()
    test_cases = int(input_lines[0])
    i = 1
    while test_cases:
        num_colors = int(input_lines[i])
        i += 1
        colors = input_lines[i].split()
        i += 1
        num_pairs = int(input_lines[i])
        i += 1
        hideous_pairs = {color: [] for color in colors}
        while num_pairs:
            c1, c2 = input_lines[i].split()
            hideous_pairs[c1].append(c2)
            hideous_pairs[c2].append(c1)
            i += 1
            num_pairs -= 1
        
        paintings(colors, hideous_pairs)

        test_cases -= 1

if __name__ == '__main__':
    main()
