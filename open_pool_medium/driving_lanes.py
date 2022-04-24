"""https://ualberta.kattis.com/sessions/vg7m4t/problems/drivinglanes

We will solve it by Dynamic Programming.

Let f(i, l) = shortest distance to reach the end and end up in lane 0
              when starting from straightway i and lane l.
Therefore, we want f(0, 0)

A few observations:
- The distance to move p lanes in the sam straightway is (k + r)*p
- We can only move to a lane in  a straightway if, k < len of that straightway.
  For example, if we want to move from lane 1 to 4, we can only move if
  k * (4-1) < len of that straightway.
  We will call all such lanes we can reach in a straightway 'attainable'.

Now, we are ready to describe the recursive formula:
Let S = all attainable lanes starting from lane l

f(i, l) = (r * l) + len(straightway i)           // if (i = n-1) [we have reached end]
                                                    and (k * l) <= len(straightway i)
f(i, l) = min(f(i, l),                           // if (i < n-1)
              r * abs(ll-l) + len(straightway i) +              // for ll in S
              curve_strech[curve i] + curve_curvature[curve i] * (ll + 1) +
              f(i+1, ll)
        )

f(i+1, ll) is the min dist to reach end when starting from straightway i+1 and lane ll
To reach that state from our current state, we have to travel a distance of:
    r * abs(ll-l) +                                             // cost for switching lanes
    len(straightway i) +                                        // cost for moving across current straightway
    curve_strech[curve i] + curve_curvature[curve i] * (ll + 1) // cost for moving across curve

That's it! :)
"""

import sys
from typing import List


num_of_straightways: int
num_of_lanes: int
k: int
r: int
straightway_lentghs: List[int]
curve_strech: List[int]
curve_curvature: List[int]
memo: List[List[int]]


def driving_lanes(i: int, l: int) -> None:
    global num_of_straightways, num_of_lanes, k, r
    global straightway_lentghs, curve_strech, curve_curvature, memo

    if (memo[i][l] != -1):
        return memo[i][l]
    
    memo[i][l] = float('inf')
    if (i == num_of_straightways-1) and ((k * l) <= straightway_lentghs[i]):    # If we have reached the end
        memo[i][l] = (r * l) + straightway_lentghs[i]   # Note that (r * l) will be 0 if we are already in lane 0

    elif i < num_of_straightways - 1:
        for ll in range(num_of_lanes):
            if k * abs(ll-l) <= straightway_lentghs[i]:   # if lane ll is attainable
                memo[i][l] = min(memo[i][l],
                            r*abs(ll-l) + straightway_lentghs[i] + \
                            curve_strech[i] + curve_curvature[i]*(ll+1) + \
                            driving_lanes(i+1, ll)
                )
    return memo[i][l]


def main():
    global num_of_straightways, num_of_lanes, k, r
    global straightway_lentghs, curve_strech, curve_curvature, memo

    input_lines = sys.stdin.read().splitlines()
    num_of_straightways, num_of_lanes = list(map(int, input_lines[0].split()))
    k, r = list(map(int, input_lines[1].split()))

    straightway_lentghs = list(map(int, input_lines[2:2+num_of_straightways]))
    
    curve_strech = []
    curve_curvature = []
    for line in input_lines[2+num_of_straightways:]:
        s, c = list(map(int, line.split()))
        curve_strech.append(s)
        curve_curvature.append(c)

    memo = [[-1 for _ in range(num_of_lanes+5)] for _ in range(num_of_straightways+5)]

    print(driving_lanes(0, 0))


if __name__ == '__main__':
    main()
