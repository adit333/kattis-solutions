"""https://ualberta.kattis.com/sessions/vg7m4t/problems/interviewqueue
"""

import sys
from typing import List


def interview_queue(num_of_candidates: int, candidate_ratings: List[int]) -> None:
    results = []

    someone_left = True    
    while someone_left:
        left = [False] * len(candidate_ratings)
        for i in range(len(candidate_ratings)):
            if i != 0:
                if candidate_ratings[i-1] > candidate_ratings[i]:
                    left[i] = True
            if i != len(candidate_ratings)-1:
                if candidate_ratings[i+1] > candidate_ratings[i]:
                    left[i] = True

        someone_left = False
        j = 0
        candidates_who_left = []
        for pos in range(len(left)):
            if left[pos]:
                candidates_who_left.append(candidate_ratings[pos-j])
                candidate_ratings.pop(pos-j)
                j += 1
                someone_left = True
        if candidates_who_left:
            results.append(candidates_who_left)

    print(len(results))
    for l in results:
        print(*l)
    print(*candidate_ratings)


def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_candidates = int(input_lines[0])
    candidate_ratings = list(map(int, input_lines[1].split()))
    interview_queue(num_of_candidates, candidate_ratings)


if __name__ == '__main__':
    main()