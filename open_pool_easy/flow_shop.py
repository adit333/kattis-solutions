"""https://ualberta.kattis.com/sessions/x2xwog/problems/flowshop

Approach: stage j of item i can only start after stage j of item i-1
Use the recurrence: ans[i, j] = p[i,j] + max(ans[i, j-1], ans[i-1, j])
where ans[i,j] is completion time of item i stage j
"""

import sys
from typing import List


def flow_shop(num_swathers: int, num_stages: int, costs: List[List[int]]) -> None:
    finish_times = [[0 for _ in range(num_stages + 1)] for _ in range(num_swathers + 1)]
    result = [] # Store finish times for each swather
    for swather in range(1, num_swathers+1):
        for stage in range(1, num_stages+1):
            m = max(finish_times[swather][stage-1], finish_times[swather-1][stage])
            finish_times[swather][stage] = costs[swather][stage] + m
        result.append(finish_times[swather][stage])
    print(*result)


def main():
    input_lines = sys.stdin.read().splitlines()
    num_swathers, num_stages = list(map(int, input_lines[0].split()))
    costs = [[0 for _ in range(num_stages + 1)]]
    for input_line in input_lines[1:]:
        swather_stage_costs = [0] + list(map(int, input_line.split()))
        costs.append(swather_stage_costs)
    flow_shop(num_swathers, num_stages, costs)


if __name__ == '__main__':
    main()
