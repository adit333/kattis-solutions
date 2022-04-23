"""https://ualberta.kattis.com/sessions/vg7m4t/problems/interviewqueue

It is too solw to update the queue every iteration.
It is also too slow to check only over alive positions every iteration; e.g. if only one candidate leaves every iteration
Thus, we only check neighboring positions of a candidate who has left.
"""

import sys
from typing import List

def find_neighbor(pos: int, step: List[int], num_of_candidates: int):
    pv = pos
    while pv != -1 and pv != num_of_candidates and step[pv] != pv:
        pv = step[pv]
    while pv != -1 and pv != num_of_candidates and pos != pv:
        pos, step[pos] = step[pos], pv
    return pv

def interview_queue(num_of_candidates: int, candidate_ratings: List[int]) -> None:
    results = []

    someone_left = True
    candidate_left = [False for _ in range(num_of_candidates)]
    step_left = [i for i in range(num_of_candidates)]
    step_right = [i for i in range(num_of_candidates)]

    check_pos = set(range(num_of_candidates))

    while someone_left:
        check_pos_next_iter = set()
        candidates_who_left = set()
        for pos in check_pos:
            if candidate_left[pos]:
                continue
            l = find_neighbor(pos-1, step_left, num_of_candidates)
            r = find_neighbor(pos+1, step_right, num_of_candidates)
            if l == -1:
                l = pos
            if r == num_of_candidates:
                r = pos
            if candidate_ratings[l] > candidate_ratings[pos] or candidate_ratings[r] > candidate_ratings[pos]:
                candidates_who_left.add(pos)
                check_pos_next_iter.add(l)
                check_pos_next_iter.add(r)

        if candidates_who_left:
            for pos in candidates_who_left:
                candidate_left[pos] = True
                step_left[pos] = pos - 1
                step_right[pos] = pos + 1
            results.append(candidates_who_left)
            check_pos = check_pos_next_iter

        else:
            candidates_who_left = set(i for i in range(num_of_candidates) if not candidate_left[i])
            results.append(candidates_who_left)
            someone_left = False

    print(len(results)-1)
    for result in results:
        print(*[candidate_ratings[i] for i in sorted(result)])

def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_candidates = int(input_lines[0])
    candidate_ratings = list(map(int, input_lines[1].split()))
    interview_queue(num_of_candidates, candidate_ratings)


if __name__ == '__main__':
    main()
