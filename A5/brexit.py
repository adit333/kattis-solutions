"""https://ualberta.kattis.com/sessions/deivji/problems/brexit

Use modified Kahn's Algorithm
"""

import copy
import sys
from typing import List


def brexit(adjacency_list: List[List[int]], original_degree: List[int],
        home: int, first_to_leave: int) -> None:
    queue = [first_to_leave]       # Contains countries that are set to leave
    left_the_block = [False] * len(original_degree)
    current_degree = copy.deepcopy(original_degree)
    while queue:
        u = queue.pop(0)
        if left_the_block[u]: continue
        if u == home:
            print("leave")
            return

        for v in adjacency_list[u]:
            current_degree[v] -= 1
            if current_degree[v] <= original_degree[v] / 2:
                queue.append(v)     # v will also leave now
        left_the_block[u] = True
    print("stay")


def main():
    input_lines = sys.stdin.read().splitlines()

    # Read C, P, X, L
    num_countries, num_partnerships, home, first_to_leave = list(map(int, input_lines[0].split()))

    # Read the graph
    adjacency_list = [[] for _ in range(num_countries)]
    degree = [0 for _ in range(num_countries)]
    for partnership in input_lines[1:]:
        u, v = list(map(int, partnership.split()))
        adjacency_list[u-1].append(v-1)
        adjacency_list[v-1].append(u-1)
        degree[u-1] += 1
        degree[v-1] += 1
    brexit(adjacency_list, degree, home-1, first_to_leave-1)

if __name__ == '__main__':
    main()
