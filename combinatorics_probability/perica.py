"""https://ualberta.kattis.com/sessions/hgwror/problems/perica

Approach: Sort the list, then the num at pos j is maximum
  the no. of times to choose k-1 items of all the no. to the left of j and j i.e. f(j, k-1). 
Add to an accumulating sum: f(j, k-1) * num[j]
Then return ans % prime.
"""

import sys
from typing import List


MAX_N = 100010
p = 10**9+7
fact = []


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
  global fact

  if n < k:
    return 0
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p


def perica(n: int, k: int, keys: List[int]) -> None:
    keys.sort()
    result = 0
    for i in range(len(keys)):
        result += C(i, k-1) * keys[i]
        result %= p
    print(result)


def main():
    global fact

    # Precompute factorials
    fact = [0] * MAX_N

    fact[0] = 1
    for i in range(1, MAX_N):
        fact[i] = (fact[i-1]*i)% p

    # Read input
    input_lines = sys.stdin.read().splitlines()
    n, k = list(map(int, input_lines[0].split()))
    keys = list(map(int, input_lines[1].split()))
    perica(n, k, keys)


if __name__ == '__main__':
    main()
