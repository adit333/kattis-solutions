"""https://ualberta.kattis.com/sessions/vk6fb6/problems/burrowswheeler
"""

import sys

def sort_cyclic_shifts(s):
    s = [*map(ord, s)]
    n = len(s)
    alphabet = 256
    p = [0] * n
    c = [0] * n
    cnt = [0] * max(alphabet, n)
    for i in range(n):
        cnt[s[i]] += 1
    for i in range(1, alphabet):
        cnt[i] += cnt[i-1]
    for i in range(n):
        cnt[s[i]] -= 1
        p[cnt[s[i]]] = i
    c[p[0]] = 0
    classes = 1
    for i in range(1, n):
        if s[p[i]] != s[p[i-1]]:
            classes += 1
        c[p[i]] = classes - 1
    pn = [0] * n
    cn = [0] * n
    h = 0
    while (1 << h) < n:
        for i in range(n):
            pn[i] = p[i] - (1 << h)
            if pn[i] < 0:
                pn[i] += n
        for i in range(classes):
            cnt[i] = 0
        for i in range(n):
            cnt[c[pn[i]]] += 1
        for i in range(1, classes):
            cnt[i] += cnt[i-1]
        for i in range(n-1, -1, -1):
            cnt[c[pn[i]]] -= 1
            p[cnt[c[pn[i]]]] = pn[i]
        cn[p[0]] = 0
        classes = 1
        for i in range(1, n):
            cur = (c[p[i]], c[(p[i] + (1 << h)) % n])
            prev = (c[p[i-1]], c[(p[i-1] + (1 << h)) % n])
            if cur != prev:
                classes += 1
            cn[p[i]] = classes - 1
        c, cn = cn, c
        h += 1
    return p

# returns the suffix array of s
def suffix_array_construction(s):
    return sort_cyclic_shifts(s+'\0')[1:]


def burrows_wheeler(s: str) -> None:
    n = len(s)
    s = s + s[:-1] + str(9)
    sa = suffix_array_construction(s)
    
    res = []
    for num in sa:
        if num >= n:
            continue
        res.append(s[num + n - 1])
    print("".join(res))

def main():
    input_lines = sys.stdin.read().splitlines()
    for s in input_lines:
        burrows_wheeler(s)

if __name__ == '__main__':
    main()
