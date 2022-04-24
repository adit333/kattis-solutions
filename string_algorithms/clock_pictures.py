"""https://ualberta.kattis.com/sessions/vk6fb6/problems/clockpictures

Approach: Sort the angles in order to orient in one direction.
          Find the differences between the angles, use modulo in case the difference is negative.
            We find the differences to get relative angles between the angles.
          Concatenate a clock angle difference with itself (as clock2 may be a rotation of clock1)
          Use KMP to find if clock2 is a substring of clock1.
"""

import sys
from typing import List

MAX_ANGLE = 360000

MAX_N = 200010
pi = None

def kmpPreprocess(P):
    global pi

    m = len(P)
    pi = [0] * m
    i, j = 0, -1
    pi[0] = -1
    while i < m:
        while j >= 0 and P[i] != P[j]:
            j = pi[j]
        i += 1
        j += 1
        pi[i] = j

def kmpSearch(T, P):
    global pi

    n = len(T)
    m = len(P)

    occurences = []
    i, j = 0, 0
    while i < n:
        while j >= 0 and T[i] != P[j]:
            j = pi[j]
        i += 1
        j += 1
        if j == m:
            occurences.append(i-m)
            j = pi[j]
    return occurences


def compute_clock_angle_differences(clock: List[int]) -> List[int]:
    clock_angle_diferences = []
    previous_clock_hand = clock[-1]
    for i in range(len(clock)):
        clock_angle_difference  = (clock[i] - previous_clock_hand) % MAX_ANGLE
        clock_angle_diferences.append(clock_angle_difference)
        previous_clock_hand = clock[i]
    return clock_angle_diferences

def clock_pictures(clock1: List[int], clock2: List[int]) -> None:
    clock1.sort()
    clock2.sort()

    # Compute differences in angles between 2 clock hands
    clock1_angle_differences = compute_clock_angle_differences(clock1)
    clock2_angle_differences = compute_clock_angle_differences(clock2)

    text = ','.join(list(map(str, clock1_angle_differences+clock1_angle_differences)))
    pattern = ','.join(list(map(str, clock2_angle_differences)))

    kmpPreprocess(pattern)
    occurences = kmpSearch(text, pattern)
    if len(occurences) == 0:
        print('impossible')
    else:
        print('possible')


def main():
    input_lines = sys.stdin.read().splitlines()
    clock1 = list(map(int, input_lines[1].split()))
    clock2 = list(map(int, input_lines[2].split()))
    clock_pictures(clock1, clock2)

if __name__ == '__main__':
    main()
