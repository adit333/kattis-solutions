"""https://ualberta.kattis.com/sessions/hgwror/problems/odds

Approach: brute force
"""

import sys
from fractions import Fraction

def odds(s0: str, s1: str, r0: str, r1: str) -> None:
    total_games_count, games_won_count = 0, 0
    for num_s0 in range(1, 7):  # Dice rool possibilities are from 1 to 6
        if s0 != '*' and num_s0 != int(s0):
            continue

        for num_s1 in range(1, 7):
            if s1 != '*' and num_s1 != int(s1):
                continue

            for num_r0 in range(1, 7):
                if r0 != '*' and num_r0 != int(r0):
                    continue

                for num_r1 in range(1, 7):
                    if r1 != '*' and num_r1 != int(r1):
                        continue

                    s_score = dice_roll_score(num_s0, num_s1)
                    r_score = dice_roll_score(num_r0, num_r1)

                    total_games_count += 1
                    if s_score > r_score:
                        games_won_count += 1
    
    if games_won_count == 0:
        print(0)
    elif total_games_count == games_won_count:
        print(1)
    else:
        print(Fraction(games_won_count, total_games_count))


def dice_roll_score(dice1: int, dice2: int) -> int:
    small_dice = min(dice1, dice2)
    large_dice = max(dice1, dice2)

    # Mia
    if small_dice == 1 and large_dice == 2:
        return float('inf')
    
    # Doubles
    if small_dice == large_dice:
        # 100 is just a random large no. in order to make sure doubles 
        # are just larger than max possible other roll which is 65
        return 100 * small_dice

    # Only other possibility
    return (10 * large_dice) + small_dice

def main():
    input_lines = sys.stdin.read().splitlines()
    for input_line in input_lines[:-1]:
        s0, s1, r0, r1 = input_line.split()
        odds(s0, s1, r0, r1)

if __name__ == '__main__':
    main()
