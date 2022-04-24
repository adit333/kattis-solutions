"""https://ualberta.kattis.com/sessions/k4m3s3/problems/narrowartgallery"""

import sys
from typing import List
from functools import lru_cache

room_values: List[List[int]]

@lru_cache(maxsize=None)
def narrow_art_gallery(row: int, k: int) -> int:
    return min(narrow_art_gallery_helper(row, k, 0),
               narrow_art_gallery_helper(row, k, 1)
    )

@lru_cache(maxsize=None)
def narrow_art_gallery_helper(row: int, k: int, column: int) -> int:
    if k == 0:
        return 0
    if row < 0:
        return float('inf')
    current_room_value = room_values[row][column]
    return min(narrow_art_gallery_helper(row - 1, k - 1, column) + current_room_value,
               narrow_art_gallery(row - 1, k)
        )

def main():
    global room_values
    input_lines = sys.stdin.read().splitlines()
    i = 0
    while i < len(input_lines):
        n, k = map(int, input_lines[i].split())
        i += 1

        if n == 0 and k == 0:
            break

        # Read room values
        room_values = []
        total_value = 0
        start  = i
        while i < n + start:
            row = list(map(int, input_lines[i].split()))
            room_values.append(row)
            total_value += sum(row)
            i += 1
        print(total_value - narrow_art_gallery(n-1, k))

    # # Test case 1
    # n, k = 6, 4
    # room_values = [[3, 1],
    #                [2, 1],
    #                [1, 2],
    #                [1, 3],
    #                [3, 3],
    #                [0, 0],
    # ]

    # # Test case 2
    # n, k = 4, 3
    # room_values = [[3, 4],
    #                [1, 1],
    #                [1, 1],
    #                [5, 6],
    # ]

    # # Test case 3
    # n, k = 10, 5
    # room_values = [[7, 8],
    #                [4, 9],
    #                [3, 7],
    #                [5, 9],
    #                [7, 2],
    #                [10, 3],
    #                [0, 10],
    #                [3, 2],
    #                [6, 3],
    #                [7, 9],
    # ]
    # print(narrow_art_gallery(n-1, k))

if __name__ == '__main__':
    main()