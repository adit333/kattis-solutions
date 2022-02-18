"""https://ualberta.kattis.com/sessions/hgwror/problems/porpoises
Approach: use fast matrix power exponentiation
Use matrix A = [1 1; 1 0] for the fibonacci matrix.
"""

import sys

MOD = 10**9

def mod(a, m):
    return (a%m+m)%m

def matMul(a, b):
    global MOD

    ans = [[0, 0], [0, 0]]
    for i in range(2):
        for k in range(2):
            if a[i][k] == 0:
                continue
            for j in range(2):
                ans[i][j] += mod(a[i][k], MOD) * mod(b[k][j], MOD)
                ans[i][j] = mod(ans[i][j], MOD)
    return ans

def matPow(base, p):
    ans = [[1, 0], [0, 1]]
    while p != 0:
        if p&1 != 0:
            ans = matMul(ans, base)
        base = matMul(base, base)
        p >>= 1
    return ans

def porpoises(n: int) -> int:
    ans = matPow([[1, 1], [1, 0]], n)
    return ans[0][1]

def main():
    input_lines = sys.stdin.read().splitlines()
    for input_line in input_lines[1:]:
        i, n = list(map(int, input_line.split()))
        print(f'{i} {porpoises(n)}')

if __name__ == '__main__':
    main()
