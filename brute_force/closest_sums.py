"""https://open.kattis.com/problems/closestsums"""

import sys
from typing import List


def closest_sums(nums: List[int], queries: List[int]) -> None:
    sums = []

    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            sums.append(nums[i] + nums[j])
    
    sums.sort()
    for query in queries:
        i = 0
        while i < len(sums) - 1 and query >= sums[i]:
            i += 1
        if i != 0 and abs(sums[i-1]-query) < abs(sums[i]-query):
            print(f'Closest sum to {query} is {sums[i-1]}.')
        else:
            print(f'Closest sum to {query} is {sums[i]}.')


def main():
    input_lines = sys.stdin.read().splitlines()

    case = 1
    i = 0
    while i < len(input_lines):
        n = int(input_lines[i])
        i += 1
        nums = []
        while n:
            nums.append(int(input_lines[i]))
            n -= 1
            i += 1
        m = int(input_lines[i])
        i += 1
        queries = []
        while m:
            queries.append(int(input_lines[i]))
            m -= 1
            i += 1
        print(f'Case {case}:')
        case += 1
        closest_sums(nums, queries)


if __name__ == '__main__':
    main()