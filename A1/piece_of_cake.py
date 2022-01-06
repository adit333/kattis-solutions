"""
https://ualberta.kattis.com/sessions/xq7r95/problems/integerdivision
Algorithm:
- Find the larger of the 2 horizontal side, and the larger of the 2 vertical sides.
- Multiply them together with the height and return the volume calculated as the anwser.
"""

from typing import List


def piece_of_cake(dimensions: List[int]):
    height = 4
    horizontal1, horizontal2 = dimensions[1], dimensions[0]-dimensions[1]
    vertical1, vertical2 = dimensions[2], dimensions[0]-dimensions[2]
    max_horizontal = max(horizontal1, horizontal2)
    max_vertical = max(vertical1, vertical2)
    print(max_horizontal * max_vertical * height)

def main():
    # print(piece_of_cake([10, 4, 7]))
    # print(piece_of_cake([5, 2, 2]))
    # print(piece_of_cake([4, 2, 1]))
    dimensions = list(map(int, input().split()))
    piece_of_cake(dimensions)


if __name__ == '__main__':
    main()
