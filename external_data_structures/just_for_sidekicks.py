"""https://ualberta.kattis.com/sessions/wrky5n/problems/justforsidekicks

CP book 1 - pg 107

Approach:
- Maintain a Fenwick tree for each gem, with 1 for the index indicating that
the gem of that type is present in the list of gems; 0 elsewhere.
- For query type 1, delete an entry for the Fenwick tree that has been replaced
and add an entry for the Fenwick tree correspoding the the gem that has been added.
- For query type 3, use rsq(i, j) for each gem to find out how many gemsof that type are present in the
range and simply multiply by the value of that gem to a running sum.

Note: In this implementation of Fenwick, we completely ignore index 0 and never touch it.
"""

import sys
from typing import List

class FTree:
    def __init__(self, f):
        self.n = len(f)
        self.ft = [0] * (self.n + 1)

    def lsone(self, s):
        return s & (-s)

    def query(self, i, j):
        if i > 1:
            return self.query(1, j) - self.query(1, i - 1)

        s = 0
        while j > 0:
            s += self.ft[j]
            j -= self.lsone(j)

        return s

    def update(self, i, v):
        while i <= self.n:
            self.ft[i] += v
            i += self.lsone(i)


def just_for_sidekicks(num_of_gems: int, gem_values: List[int],
        gems: List[str], queries: List[str]) -> None:
    temp = [0] * num_of_gems    # 0 at index i indicates there is no gem of this type at index i
    gem_fenwicks  = [FTree(temp) for _ in range(6)]    # Fenwick tree for each of the 6 gems

    # Construct the Fenwick trees
    for i, gem_type in enumerate(gems):
        gem_fenwicks[gem_type-1].update(i+1, +1)     # Gem of this type is present at index i so update by +1 (0 to 1)

    # Answer the queries
    for query in queries:
        query_type, a, b = list(map(int, query.split()))

        if query_type == 1:
            gem_index, new_gem_type = a, b
            gem_fenwicks[gems[gem_index-1]-1].update(gem_index, -1)
            gems[gem_index-1] = new_gem_type
            gem_fenwicks[gems[gem_index-1]-1].update(gem_index, +1)
        
        elif query_type == 2:
            gem_type, new_gem_value = a, b
            gem_values[gem_type-1] = new_gem_value
        
        elif query_type == 3:
            left, right = a, b
            result = 0
            for gem_type in range(6):
                result += gem_fenwicks[gem_type].query(left, right) * gem_values[gem_type]
            print(result)


def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_gems, num_of_queries = list(map(int, input_lines[0].split()))
    gem_values = list(map(int, input_lines[1].split()))
    gems = list(map(int, list(input_lines[2])))
    
    queries  = input_lines[3:]

    just_for_sidekicks(num_of_gems, gem_values, gems, queries)
    


if __name__ == '__main__':
    main()
