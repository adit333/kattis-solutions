"""https://ualberta.kattis.com/sessions/of28kb/problems/farey
Calculate EulerPhi(i) for each i in [1, N]
Do prefix sum on the array
Retrun eulerphi_prefix_sum[i] + 1
"""

import sys

_sieve_size = 0
bs = []
primes = []
MAXN = 10001

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


def EulerPhi(N):
    global primes

    ans = N
    for p in primes:
        if p * p > N:
            break
        if N % p == 0:
            ans -= ans // p
        while N % p == 0:
            N //= p

    if N != 1:
        ans -= ans // N

    return ans


def main():
    sieve(MAXN)
    n = MAXN
    eulerphi_prefix_sum = [0] * n
    for num in range(1, n):
        eulerphi_prefix_sum[num] = EulerPhi(num) + eulerphi_prefix_sum[num-1]

    input_lines = sys.stdin.read().splitlines()
    for i in range(1, len(input_lines)):
        k, n = list(map(int, input_lines[i].split()))
        print(k, " " , eulerphi_prefix_sum[n]+1)


if __name__ == '__main__':
    main()