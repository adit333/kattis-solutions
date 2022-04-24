"""https://ualberta.kattis.com/sessions/x2xwog/problems/election

We use binomial distribution: 
    If we have R renmaining votes to count:
    Let X be the no. of votes won by us
    X ~ Bin(R, 0.5)
    If we need k votes to win, we will decalre victory if P(X > k) > W
    P(X > k) = RCk * 0.5^k * 0.5^k + RCk+1 * 0.5^(k+1) * 0.5^(k-1) + RCR * 0.5^R * 0.5^0
"""

import sys
from typing import List

C: List[List[int]] # Store binomial coefficients
 
def binomialCoef(n, k):
    global C
    # Calculate value of Binomial
    # Coefficient in bottom up manner
    for i in range(n+1):
        for j in range(min(i, k)+1):
            if j == 0 or j == i:    # Base Cases
                C[i][j] = 1
            else:
                C[i][j] = C[i-1][j-1] + C[i-1][j]

    return C[n][k]

def election(num_voters: int, v1_voters: int, v2_voters: int,
        win_percent_threshould: int) -> None:
    num_of_remaining_votes = num_voters - v1_voters - v2_voters
    if num_of_remaining_votes + v1_voters <= v2_voters:  # There is no chance we will win
        print('RECOUNT!')
        return
    if num_of_remaining_votes + v2_voters < v1_voters:  # We have surely won
        print('GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!')
        return

    votes_needed_for_a_majority = (num_voters//2) + 1
    votes_needed_to_win = votes_needed_for_a_majority - v1_voters
    sum_of_bin_coeff = 0
    for i in range(votes_needed_to_win, num_of_remaining_votes + 1):
        sum_of_bin_coeff += C[num_of_remaining_votes][i]
    probability_of_win = 100 * (sum_of_bin_coeff * pow(0.5, num_of_remaining_votes))
    if probability_of_win > win_percent_threshould:
        print('GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!')
    else:
        print('PATIENCE, EVERYONE!')


def main():
    # Precompute binomial coefficients
    global C
    n, k = 100, 100     # max values as guaranteed by the input
    C = [[0 for x in range(k+1)] for x in range(n+1)]
    binomialCoef(n, k)

    input_lines = sys.stdin.read().splitlines()
    for input_line in input_lines[1:]:
        num_voters, v1_voters, v2_voters, win_percent_threshould = list(map(int, input_line.split()))
        election(num_voters, v1_voters, v2_voters, win_percent_threshould)


if __name__ == '__main__':
    main()
