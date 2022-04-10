"""https://ualberta.kattis.com/sessions/vg7m4t/problems/interviewqueue
"""

import sys
from typing import List


def interview_queue(num_of_candidates: int, candidate_ratings: List[int]) -> None:
    results = []

    someone_left = True    

    prev_rating = -1
    next_idx = -1
    while someone_left:
        current = 0
        someone_left = False
        candidates_who_left = []
        while current < len(candidate_ratings):
            if candidate_ratings[current] != -1:
                next_idx = current + 1
                while next_idx < num_of_candidates and candidate_ratings[next_idx] == -1:
                    next_idx += 1

                if prev_rating > candidate_ratings[current]:
                    prev_rating = candidate_ratings[current]
                    candidates_who_left.append(candidate_ratings[current])
                    candidate_ratings[current] = -1
                    someone_left = True
                else:
                    prev_rating = candidate_ratings[current]
                
                if candidate_ratings[current] != -1:    # Killed in prev check, so no need to check.
                    if next_idx < num_of_candidates and candidate_ratings[current] < candidate_ratings[next_idx]:
                        prev_rating = candidate_ratings[current]
                        candidates_who_left.append(candidate_ratings[current])
                        candidate_ratings[current] = -1
                        someone_left = True

                current = next_idx
            
            else:
                current += 1

        if candidates_who_left:
            results.append(candidates_who_left)

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