""" https://ualberta.kattis.com/sessions/xq7r95/problems/ants
Algorithm:

"""

from typing import List


def ants(length_of_pole: int, num_of_ants: int, ant_positions_from_left: List[int]) -> None:
    earliest, latest = 0, 0
    for ant_pos_from_left in ant_positions_from_left:
        if ant_pos_from_left > latest:
            latest = ant_pos_from_left
        if length_of_pole - ant_pos_from_left > latest:
            latest = length_of_pole - ant_pos_from_left
        
        if ant_pos_from_left > length_of_pole - ant_pos_from_left:
            ant_pos_from_left = length_of_pole - ant_pos_from_left
        if ant_pos_from_left > earliest:
            earliest = ant_pos_from_left
    print(earliest, latest)

def main():
    # ants(10, 3, [2, 6, 7])
    # ants(214, 7, [11, 12, 7, 13, 176, 23, 191])
    num_of_cases = int(input())
    for i in range(num_of_cases):
        length_of_pole, num_of_ants = list(map(int, input().split()))
        ant_positions_from_left = []
        while len(ant_positions_from_left) < num_of_ants:
            ant_positions_from_left += list(map(int, input().split()))
        ants(length_of_pole, num_of_ants, ant_positions_from_left)


if __name__ == '__main__':
    main()
