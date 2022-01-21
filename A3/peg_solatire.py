"""https://ualberta.kattis.com/sessions/zy3te5/problems/solitaire
"""

import sys 
from collections import deque
from typing import Deque, FrozenSet, Set, Tuple

INVALID_POSITIONS = {
    (0,0),(0,1),(0,2),(0,6),(0,7),(0,8),    # No hole postions of top
    (4,0),(4,1),(4,2),(4,6),(4,7),(4,8),    # No hole positions on bottom
    (-1,3),(-1,4),(-1,5),                   # Top out-of-position
    (5,3),(5,4),(5,5),                      # Bottom out-of-position
    (1,-1),(2,-1),(3,-1),                   # Left out-of-position
    (1,9),(2,9),(3,9)                       # Right out-of-position
}

MAX = 100                                   # A large number above the input upper-bound

def solve_peg_solatire(pegs_state):
    visited_states = {frozenset(pegs_state)}
    queue_of_states = deque()
    queue_of_states.append((0, pegs_state))
    return do_bfs(visited_states, queue_of_states)

def do_bfs(visited_states: Set[FrozenSet[Tuple[int]]], queue_of_states: Deque) -> Tuple[int, int]:
    min_num_pegs_left, min_moves = MAX, MAX
    while queue_of_states:
        num_of_moves, pegs_state = queue_of_states.popleft()
        if len(pegs_state) < min_num_pegs_left or (min_num_pegs_left == len(pegs_state) and num_of_moves < min_moves):
            min_num_pegs_left = len(pegs_state)
            min_moves = num_of_moves
        for new_state in state_after_a_legal_move(pegs_state):
            if new_state not in visited_states:
                if len(new_state) <= 1:
                    return len(new_state), num_of_moves + 1
                visited_states.add(frozenset(new_state))
                queue_of_states.append((num_of_moves+1, new_state))
    return min_num_pegs_left, min_moves

def state_after_a_legal_move(pegs_state: Set[Tuple[int]]) -> Set[Tuple[int]]:
        for row,col in pegs_state:
            if (row-1,col) in pegs_state and (row-2,col) not in pegs_state and (row-2,col) not in INVALID_POSITIONS:
                new_pegs_state =  pegs_state - {(row-1,col),(row,col)}
                new_pegs_state.add((row-2,col))
                yield new_pegs_state
            if (row+1,col) in pegs_state and (row+2,col) not in pegs_state and (row+2,col) not in INVALID_POSITIONS:
                new_pegs_state =  pegs_state - {(row+1,col),(row,col)}
                new_pegs_state.add((row+2,col))
                yield new_pegs_state
            if (row,col-1) in pegs_state and (row,col-2) not in pegs_state and (row,col-2) not in INVALID_POSITIONS:
                new_pegs_state = pegs_state - {(row,col-1),(row,col)}
                new_pegs_state.add((row,col-2))
                yield new_pegs_state
            if (row,col+1) in pegs_state and (row,col+2) not in pegs_state and (row,col+2) not in INVALID_POSITIONS:
                new_pegs_state = pegs_state - {(row,col+1),(row,col)}
                new_pegs_state.add((row,col+2))
                yield new_pegs_state

def main():
    for i in range(int(input())):
        if i != 0:
            input()
        initial_pegs_state = {(row,col) for row in range(5) for col,x in enumerate(input()) if x == 'o'}
        min_num_pegs_left, min_moves = solve_peg_solatire(initial_pegs_state)
        print(min_num_pegs_left, min_moves)

if __name__ == "__main__":
    main()