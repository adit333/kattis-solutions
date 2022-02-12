"""https://ualberta.kattis.com/sessions/of28kb/problems/candydistribution

Idea:
Kx + 1 = Cy
Cy - Kx = 1
Cy + Kx = 1

So, use Extended Eucledian Algorithm
So, the problem esentially is about finding C^-1 (mod K)
"""

import sys

def mod(a, m):
  return ((a % m) + m) % m


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
  return mod(x, m)


def candy_distr(K: int, C: int) -> None:
    if K == 1:        # If there is only 1 kid, he is guaranteed to lose 1 candy
        if C == 1:      # If candy bag capacity is 1, we have to buy 2 bags, for a total of 2 candies
            print(2)
        else:           # C > 1
            print(1)
        return

    if C == 1:        # If candy bag capacity is 1, then simnply buy k+1 bags
        print(K+1)
        return

    result = modInverse(C, K)
    if result == -1:
        print("IMPOSSIBLE")
    else:
        print(result)


def main():
    input_lines = sys.stdin.read().splitlines()
    for i in range(1, len(input_lines)):
        K, C = list((map(int, input_lines[i].split())))
        candy_distr(K, C)

if __name__ == '__main__':
    main()
