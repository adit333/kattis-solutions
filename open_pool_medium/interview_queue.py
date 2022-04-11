"""https://ualberta.kattis.com/sessions/vg7m4t/problems/interviewqueue
"""

import sys
from typing import List


def interview_queue(num_of_candidates: int, candidate_ratings: List[int]) -> None:
    results = []  
    someone_left = True
    prev_rating = -1
    alive_positions = [i for i in range(num_of_candidates)]
    while someone_left:
        someone_left = False
        alive_positions_next_iter = []
        candidates_who_left = []
        for i, current in enumerate(alive_positions):
            if prev_rating > candidate_ratings[current]:
                prev_rating = candidate_ratings[current]
                candidates_who_left.append(candidate_ratings[current])
                candidate_ratings[current] = -1
                someone_left = True
            else:
                prev_rating = candidate_ratings[current]
            
            if candidate_ratings[current] != -1:    # Killed in prev check, so no need to check.
                if i + 1 < len(alive_positions) and \
                        candidate_ratings[current] < candidate_ratings[alive_positions[i+1]]:
                    prev_rating = candidate_ratings[current]
                    candidates_who_left.append(candidate_ratings[current])
                    candidate_ratings[current] = -1
                    someone_left = True

            if candidate_ratings[current] != -1:
                alive_positions_next_iter.append(current)


        if candidates_who_left:
            results.append(candidates_who_left)
        alive_positions = alive_positions_next_iter


    print(len(results))
    for l in results:
        print(*l)
    left = []
    for c in candidate_ratings:
        if c != -1:
            left.append(c)
    print(*left)


def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_candidates = int(input_lines[0])
    candidate_ratings = list(map(int, input_lines[1].split()))
    interview_queue(num_of_candidates, candidate_ratings)


if __name__ == '__main__':
    main()
