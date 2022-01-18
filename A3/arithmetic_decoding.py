"""https://ualberta.kattis.com/sessions/zy3te5/problems/arithmeticdecoding
"""

from typing import Tuple
import sys

def parse_bin(s: str) -> float:   # Converts binary repr of a float to a float
    t = s.split('.')
    return int(t[0], 2) + int(t[1], 2) / 2.**len(t[1])

def get_encoding(message: int, len_of_msg: int, p_a: float) -> Tuple[float, str]:
    # Message is an int which we consider in binary
    # 1 -> A, 0 -> B; so 1101 -> AABA
    # n is the length of the message
    lower = 0
    upper = 1
    string_message = []
    for i in range(len_of_msg-1, -1, -1):
        c = lower + (p_a * (upper - lower))
        if (message & (1<<i)):  # char at pos i is an A
            upper = c
            string_message.append('A')
        else:                   # char at pos i is an B
            lower = c
            string_message.append('B')
    return (lower, ''.join(string_message))


def arithmetic_encoding(encoding: float, len_of_msg: int, p_a: float) -> None:
    for possible_msg in range(1<<len_of_msg):
        possible_encoding, string_message = get_encoding(possible_msg, len_of_msg, p_a)
        if (possible_encoding == encoding):
            print(string_message)
            return


def main():
    input_lines = sys.stdin.read().splitlines()
    len_of_msg = int(input_lines[0])
    p_a = int(input_lines[1]) / 8
    encoding = parse_bin(input_lines[2])
    arithmetic_encoding(encoding, len_of_msg, p_a)
    #arithmetic_encoding(0.3125, 4, 0.5)
    #arithmetic_encoding(0.571441650390625, 6, 0.625)

if __name__ == '__main__':
    main()