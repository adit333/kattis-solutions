"""https://ualberta.kattis.com/sessions/c2gb3k/problems/junk

Approach:
    -Simply form a parmaterized vector equation:
        r = r0 + t*r1
        where r0 = starting vector
            r1 = direction vector
        
    -Then, caluclate the l2 norm of (r1 - r2)
        where r1, r2 are the vector equations of spacecraft and junk respectively
    - Equate the quadratic equation to the combined radius of the two to get:
        A * t^2 + B * t + C = 0
    - Compute and return the smalles root
"""

import sys
from typing import List
import math


EPS = 10**-8


class equation_of_line_3d:
    def __init__(self, s, g, r):
        self.start = s       # starting point of the circle
        self.gradient = g   # direction the circle is moving in
        self.radius = r             # radius of the circle


def dot_product(u: List[int], v: List[int]) -> int:
    result = 0
    for i in range(len(u)):
        result += u[i] * v[i]
    return result


def vector_diff(u: List[int], v: List[int]) -> List[int]:
    """Return u - v"""
    result = []
    for i in range(len(u)):
        result.append(u[i] - v[i])
    return result


def space_junk(spacecraft: equation_of_line_3d, junk: equation_of_line_3d) -> None:
    delta_r0 = vector_diff(spacecraft.start, junk.start)
    delta_r1 = vector_diff(spacecraft.gradient, junk.gradient)
    radius = spacecraft.radius + junk.radius

    A = dot_product(delta_r1, delta_r1)
    B = dot_product(delta_r0, delta_r1) * 2
    C = dot_product(delta_r0, delta_r0) - radius*radius

    if abs(A) < EPS:
        print("No collision")
        return

    if B*B < 4*A*C:
        print("No collision")
        return
    
    t = (-B - math.sqrt(B*B - 4*A*C)) / (2*A)

    if t < 0:
        print("No collision")
        return

    print("{:0.3f}".format(t))

def main():
    input_lines = sys.stdin.read().splitlines()
    test_cases = int(input_lines[0])

    line = 1
    for i in range(test_cases):
        input_line = list(map(int, input_lines[line].split()))
        spacecraft = equation_of_line_3d(input_line[:3], input_line[-3:], input_line[3])

        input_line = list(map(int, input_lines[line+1].split()))
        junk = equation_of_line_3d(input_line[:3], input_line[-3:], input_line[3])

        line += 2

        space_junk(spacecraft, junk)


if __name__ == '__main__':
    main()
