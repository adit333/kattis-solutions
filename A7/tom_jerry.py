"""https://ualberta.kattis.com/sessions/hgwror/problems/tomjerry

References: pg 299 CP4 book
Use inclusing exclusion principle and combinatorics
"""

import sys
from typing import List, Tuple
from itertools import combinations, permutations


MAX_N = 100010
p = 10**9+7
fact = []
invFact = []

def mod(a, m):
  return ((a % m) + m) % m


def modPow(b, p, m):
  if p == 0:
    return 1
  ans = modPow(b, p//2, m)
  ans = mod(ans*ans, m)
  if p % 2 == 1:
    ans = mod(ans*b, m)
  return ans


def inv(a):
  return modPow(a, p-2, p)


def C(n, k):
  global fact, invFact

  if n < k:
    return 0
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p


def is_subset_valid(subset_of_cheeses: List[Tuple[int, int]]) -> bool:
    # Here we check if we can reach from one cheese to next by only going right and down
    for i in range(len(subset_of_cheeses) - 1):
        first = subset_of_cheeses[i]
        second = subset_of_cheeses[i + 1]
        if first[0] > second[0] or first[1] > second[1]: # do we have to go left or up?
            return False
    return True


def num_of_paths(cheeses: List[Tuple[int, int]], width: int, height: int) -> int:
    paths = 1
    previous = (1, 1)
    for cheese in cheeses:
        delta_x = cheese[0] - previous[0]
        delta_y = cheese[1] - previous[1]
        paths *= C(delta_x + delta_y, delta_x)
        paths %= p
        previous = cheese

    delta_x = width - previous[0]
    delta_y = height - previous[1]
    paths *= C(delta_x + delta_y, delta_x)
    paths %= p
    return paths


def tom_jerry(width: int, height: int, cheeses: List[Tuple[int, int]]) -> None:
    cheeses.sort()
    total_paths = 0
    sign = 1   # for inclusion exclusion principle; we will alternate btw. 1 and -1
    for num_of_cheeses in range(1, len(cheeses)+1):
        subsets_of_cheeses = permutations(cheeses, num_of_cheeses)
        for subset in subsets_of_cheeses:
            if is_subset_valid(subset):
                temp = sign * num_of_paths(subset, width, height)
                temp = mod(temp + p, p) # to fdeal with the case temp is negative
                total_paths += temp
                total_paths = mod(total_paths, p)
        sign *= -1
    print(total_paths)


def main():
    global fact, invFact

    # Precompute factorials
    fact = [0] * MAX_N
    invFact = [0] * MAX_N

    fact[0] = 1
    for i in range(1, MAX_N):
        fact[i] = (fact[i-1]*i)% p


    # Read input
    input_lines = sys.stdin.read().splitlines()
    width, height = list(map(int, input_lines[0].split()))
    cheeses = []
    for pos in input_lines[2:]:
        x, y = list(map(int, pos.split()))
        cheeses.append((x, y))
    tom_jerry(width, height, cheeses)


if __name__ == '__main__':
    main()
