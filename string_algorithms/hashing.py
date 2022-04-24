"""https://ualberta.kattis.com/sessions/c2gb3k/problems/hashing
"""


import sys


MAX_N = 200010
p = 131
M = 10**9+7
Pow = [0] * MAX_N
h = [0] * MAX_N


p = 131
M = 10**9+7
Pow = [0] * MAX_N
h = [0] * MAX_N

def computeRollingHash(T):
  n = len(T)

  Pow[0] = 1
  for i in range(1, n):
    Pow[i] = (Pow[i-1]*p) % M
  h[0] = 0
  for i in range(n):
    if i != 0:
      h[i] = h[i-1]
    h[i] = (h[i] + (ord(T[i])*Pow[i]) % M) % M


def extEuclid(a, b):
  xx, yy = 0, 1
  x, y = 1, 0
  while b != 0:
    q = a//b
    a, b = b, a%b
    x, xx = xx, x-q*xx
    y, yy = yy, y-q*yy
  return a, x, y


def modInverse(b, m):
  d, x, y = extEuclid(b, m)
  if d != 1:
    return -1
  return (x+m)%m


def hash_fast(L, R):
  if L == 0:
    return h[R]
  ans = ((h[R] - h[L-1]) % M + M) % M
  ans = (ans * modInverse(Pow[L], M)) % M
  return ans


def main():
    input_lines = sys.stdin.read().splitlines()

    text = input_lines[0]
    computeRollingHash(text)

    for input_line in input_lines[2:]:
        l, r = list(map(int, input_line.split()))
        print(hash_fast(l, max(0, r-1)))

if __name__ == '__main__':
    main()
