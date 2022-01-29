"""https://ualberta.kattis.com/sessions/k4m3s3/problems/coloring
"""

import sys
import math
from typing import List

edges: List[List[bool]]

def LSOne(S: int) -> int:
    """returns the least significant 1 bit"""
    return ((S) & -(S))

def is_independent_subset(subset: int) -> bool:
    remaining_subset = subset   # remaining_subset contains the remaining vertices we have to go over
    while remaining_subset:
        two_pow_v = LSOne(remaining_subset)
        v = int(math.log2(two_pow_v))
        remaining_subset -= two_pow_v
        if not is_v_adjacent_to_subset(v, subset):
            return False
    return True

def is_v_adjacent_to_subset(v: int, subset: int) -> bool:
    two_pow_u = 1
    while two_pow_u <= subset:
        if (two_pow_u & subset):
            u = int(math.log2(two_pow_u))
            if is_adjacent(u, v):
                return False
        two_pow_u <<= 1
    return True

def is_adjacent(u: int, v: int) -> bool:
    if edges[u][v]:
        return True
    return False

def coloring_graphs(n: int) -> int:
    set_of_vertices = (1<<n)-1
    num_colors = [float('inf')] * (1<<n)
    num_colors[0] = 0     # 0 colors needed to color a graph of 0 vertices

    subset = 1
    while subset <= set_of_vertices:    # for subset S in set_of_vertices
        num_colors[subset] = bin(subset).count("1")
        s = subset
        while s > 0:              # for each s in S
            if is_independent_subset(s):
              num_colors[subset] = min(num_colors[subset], num_colors[subset-s] + 1)
            s = (s-1)&subset
        subset += 1
    print(num_colors[set_of_vertices])

def main():
    global edges
    input_lines = sys.stdin.read().splitlines()
    n = int(input_lines[0])
    edges = [[False for _ in range(n)] for _ in range(n)]
    v = 0
    for i in range(1, len(input_lines)):
        adjacent_vertices = list(map(int, input_lines[i].split()))
        for u in adjacent_vertices:
            edges[v][u] = True
        v += 1
    coloring_graphs(n)
    
    # Test Case 1; Ans- 3
    # edges = [[False, True, True, False],
    #          [True, False, True, True],
    #          [True, True, False, False],
    #          [False, True, False, False],
    # ]
    # # 3, 7, 11, 13-F; 9, 12-T
    

    # Test Case 2; Ans - 2
    # edges = [[False, False, True, True, True],
    #          [False, False, True, True, True],
    #          [True, True, False, False, False],
    #          [True, True, False, False, False],
    #          [True, True, False, False, False],
    # ]
    # # 31, 7, 13, 15, 18 - F; 3, 28 - T

    # Test Case 3; Ans - 2
    # edges = [[False, True, False, True, False, False],
    #          [True, False, True, False, True, False],
    #          [False, True, False, False, False, True],
    #          [True, False, False, False, True, False],
    #          [False, True, False, True, False, True],
    #          [False, False, True, False, True, False],
    # ]
    
    # Test Case 4; Ans - 4
    # edges = [[False, True, True, True],
    #          [True, False, True, True],
    #          [True, True, False, True],
    #          [True, True, True, False],
    # ]

    # Test Case 5; Ans - 3
    # edges = [[False, True, True, False, False],
    #          [True, False, True, True, False],
    #          [True, True, False, False, True],
    #          [False, True, False, False, True],
    #          [False, False, True, True, False],
    # ]
    # # 3, 7, 20, 24, 25, 14 - F; 9, 18, 12, 17 - T
    # print(is_independent_subset(16))
    # coloring_graphs(4)


if __name__ == '__main__':
    main()