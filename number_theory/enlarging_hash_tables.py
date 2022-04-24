"""https://ualberta.kattis.com/sessions/of28kb/problems/enlarginghashtables

Run sieve, then simply check if 2n is a prime or not.
"""

import sys

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


def enlarging_hash_table(n: int) -> None:
    num = 2*n
    while not isPrime(num):
        num += 1

    if isPrime(n):
        print(num)
    else:
        print(f'{num} ({n} is not prime)')


def main():
    sieve(40000)
    input_lines = sys.stdin.read().splitlines()
    for i in range(len(input_lines) - 1):
        enlarging_hash_table(int(input_lines[i]))


if __name__ == '__main__':
    main()
