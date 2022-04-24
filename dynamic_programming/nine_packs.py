"""https://ualberta.kattis.com/sessions/k4m3s3/problems/ninepacks
"""
import sys
from typing import List

MAX = 100000
INF = 1 << 29

def nine_packs(hotdog_packs: List[int], bun_packs: List[int]) -> None:
    # Each cell represents the weight, i.e. index 10 represents no. of hotdog packs with weight 10
    # index 20 = 2 might mean there is one hotdog pack with 20 hotdogs or 2 hotdog packs with weight 10 each.
    all_possible_hotdog_combinations = [INF] * MAX      
    all_possible_bun_combinations = [INF] * MAX
    all_possible_hotdog_combinations[0] = 0
    all_possible_bun_combinations[0] = 0

    for hotdog_pack in hotdog_packs:
        for j in range(len(all_possible_hotdog_combinations)-hotdog_pack-1, -1, -1):
            if all_possible_hotdog_combinations[j] < all_possible_hotdog_combinations[j+hotdog_pack]:
                all_possible_hotdog_combinations[j+hotdog_pack] = all_possible_hotdog_combinations[j] + 1

    for bun_pack in bun_packs:
        for j in range(len(all_possible_bun_combinations)-bun_pack-1, -1, -1):
            if all_possible_bun_combinations[j] < all_possible_bun_combinations[j+bun_pack]:
                all_possible_bun_combinations[j+bun_pack] = all_possible_bun_combinations[j] + 1

    min_possible_packs = INF
    for i in range(1, len(all_possible_hotdog_combinations)):
        if all_possible_hotdog_combinations[i] + all_possible_bun_combinations[i] < min_possible_packs:
            min_possible_packs = all_possible_hotdog_combinations[i] + all_possible_bun_combinations[i]
    
    if min_possible_packs < INF/2:
        print(min_possible_packs)
    else:
        print('impossible')


def main():
    input_lines = sys.stdin.read().splitlines()
    hotdogs = list(map(int, input_lines[0].split()[1:]))
    buns = list(map(int, input_lines[1].split()[1:]))
    nine_packs(hotdogs, buns)

if __name__ == '__main__':
    main()