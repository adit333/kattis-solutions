"""https://ualberta.kattis.com/sessions/xq7r95/problems/evenup
Algorithm:
- Iterate over the cards left to right, popping if 2 adjacent ones sum up to even, else pushing.
- Return the len of the stack at the end.
"""

from typing import List

def evenup(n: int, cards: List[int]) -> int:
    stack  = []
    last = -1
    for i in range(n):
        if (len(stack) != 0) and ((stack[last] + cards[i]) % 2 == 0):
            stack.pop()
            last -= 1
        else:
            stack.append(cards[i])
            last += 1
    print(len(stack))

def main():
    # evenup(10, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    # evenup(10, [1, 3, 3, 4, 2, 4, 1, 3, 7, 1])
    n = int(input())
    cards = list(map(int, input().split()))
    evenup(n, cards)


if __name__ == '__main__':
    main()