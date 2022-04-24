"""https://ualberta.kattis.com/sessions/wrky5n/problems/modulodatastructures
"""

from math import sqrt
import sys
from typing import List


def modulo_data_structures(N: int, queries: List[str]) -> None:
    results = []
    sqrt_n = int(sqrt(N)) + 1
    bucket = [[0 for _ in range(sqrt_n+1)] for _ in range(N+1)]  # an N + 1 by N + 1 matrix
    array = [0 for _ in range(N+1)]     # We start with index 1, ignoring index 0

    for query in queries:
        query = list(map(int, query.split()))
        query_type = query[0]

        if query_type == 1:
            A, B, C = query[1:]
            if B <= sqrt_n:
                bucket[B][A] += C
            else:
                for j in range(A, N+1, B):
                    array[j] += C
        
        if query_type == 2:
            D = query[1]
            result = array[D]
            for B in range(1, sqrt_n + 1):
                result += bucket[B][D%B]
            results.append(str(result))

    sys.stdout.write("\n".join(results))

def main():
    input_lines = sys.stdin.read().splitlines()
    N, num_of_queries = list(map(int, input_lines[0].split()))
    queries  = input_lines[1:]
    modulo_data_structures(N, queries)


if __name__ == '__main__':
    main()
