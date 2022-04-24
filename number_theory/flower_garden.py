"""https://ualberta.kattis.com/sessions/vg7m4t/problems/flowergarden
"""

import math
import sys
from typing import List

_sieve_size = 0
bs = []
primes = []


def sieve(upperbound):
  global _sieve_size, bs, primes

  _sieve_size = upperbound+1
  bs = [True] * 10000010
  bs[0] = bs[1] = False
  for i in range(2, _sieve_size):
    if bs[i]:
      for j in range(i*i, _sieve_size, i):
        bs[j] = False
      primes.append(i)


def isPrime(N):
  global _sieve_size, primes
  if N <= _sieve_size:
    return bs[N]
  for p in primes:
    if p * p > N:
      break
    if N % p == 0:
      return False
  return True


def get_dist(c1: List[int], c2: List[int]) -> float:
    dx = c1[0] - c2[0]
    dy = c1[1] - c2[1]
    return math.sqrt(dx**2 + dy**2)


def flower_garden(num_flowers: int, max_dist: int, coordinates: List[List[int]]) -> None:
    dist_covered = 0
    best_num_flowers = 0
    current_num_flowers = 0
    current_pos = [0, 0]

    for coord in coordinates:
        dist = get_dist(current_pos, coord)
        dist_covered += dist
        current_num_flowers += 1
        current_pos = coord

        if dist_covered <= max_dist and isPrime(current_num_flowers):
            best_num_flowers = current_num_flowers
        
        if dist_covered >= max_dist:
            break

    print(best_num_flowers)



def main():
    sieve(10000000)

    input_lines = sys.stdin.read().splitlines()
    test_cases = int(input_lines[0])
    i = 1
    while test_cases:
        num_flowers, dist = list(map(int, input_lines[i].split()))
        i += 1
        coordinates = []
        while num_flowers:
            coordinates.append(list(map(int, input_lines[i].split())))
            i += 1
            num_flowers -= 1
        flower_garden(num_flowers, dist, coordinates)
        test_cases -= 1


if __name__ == '__main__':
    main()
