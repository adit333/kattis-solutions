"""https://ualberta.kattis.com/sessions/deivji/problems/conquest
"""

import sys
from typing import List
from heapq import heappush, heappop


def process(u: int, taken: List[bool], pq: List[int], adjacency_list: List[List[int]],
        island_army_size: List[int], army_size: int) -> int:
    taken[u] = True
    for v in adjacency_list[u]:
        if not taken[v]:
            heappush(pq, (island_army_size[v], v))
    return army_size + island_army_size[u]

def conquest(num_islands: int, adjacency_list: List[List[int]], island_army_size: List[int]) -> None:
    pq = []
    taken = [False for _ in range(num_islands)]
    army_size = 0
    army_size = process(0, taken, pq, adjacency_list, island_army_size, army_size)
    while len(pq) > 0 and army_size > pq[0][0]:
        w, u = heappop(pq)
        if not taken[u]:
            army_size = process(u, taken, pq, adjacency_list, island_army_size, army_size)
    print(army_size)

def main():
    input_lines = sys.stdin.read().splitlines()
    num_islands, num_bridges = list(map(int, input_lines[0].split()))
    adjacency_list = [[] for _ in range(num_islands)]
    for i in range(1, num_bridges + 1):
        u, v = list(map(int, input_lines[i].split()))
        adjacency_list[u-1].append(v-1)
        adjacency_list[v-1].append(u-1)
    island_army_size = []
    for i in range(num_bridges + 1, len(input_lines)):
        island_army_size.append(int(input_lines[i]))
    conquest(num_islands, adjacency_list, island_army_size)

if __name__ == '__main__':
    main()
