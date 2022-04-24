"""https://ualberta.kattis.com/sessions/vg7m4t/problems/daceydice

Approach: Do a DFS to check whether the dice can end up at door with
    the correct orientation.
"""

import sys
from typing import List, Set, Tuple
from collections import deque


class Dice:
    LEFT, RIGHT, FORWARD, BACKWARD, TOP, BOTTOM = range(6)  # Directions of the five

    def __init__(self, row, col, five_direction) -> None:
        self.row = row
        self.col = col
        self.five_direction = five_direction      # Initially the dice's five is facing left

    def get_neighbors(self, num_sides, board) -> List:
        neighbors = []      # Contains coordinates of where we can go next

        if self.col > 0 and board[self.row][self.col-1] != '*':
            neighbors.append(self.roll_left())

        if self.col < num_sides-1 and board[self.row][self.col+1] != '*':
            neighbors.append(self.roll_right())

        if self.row > 0 and board[self.row-1][self.col] != '*':
            neighbors.append(self.roll_backward())

        if self.row < num_sides-1 and board[self.row+1][self.col] != '*':
            neighbors.append(self.roll_forward())

        return neighbors

    def roll_left(self):
        if self.five_direction == self.LEFT:
            return Dice(self.row, self.col-1, self.BOTTOM)

        elif self.five_direction == self.BOTTOM:
            return Dice(self.row, self.col-1, self.RIGHT) 

        elif self.five_direction == self.RIGHT:
            return Dice(self.row, self.col-1, self.TOP) 

        elif self.five_direction == self.TOP:
            return Dice(self.row, self.col-1, self.LEFT) 

        elif self.five_direction == self.FORWARD:
            return Dice(self.row, self.col-1, self.FORWARD) 

        elif self.five_direction == self.BACKWARD:
            return Dice(self.row, self.col-1, self.BACKWARD)

    def roll_right(self):
        if self.five_direction == self.LEFT:
            return Dice(self.row, self.col+1, self.TOP)

        elif self.five_direction == self.BOTTOM:
            return Dice(self.row, self.col+1, self.LEFT) 

        elif self.five_direction == self.RIGHT:
            return Dice(self.row, self.col+1, self.BOTTOM) 

        elif self.five_direction == self.TOP:
            return Dice(self.row, self.col+1, self.RIGHT) 

        elif self.five_direction == self.FORWARD:
            return Dice(self.row, self.col+1, self.FORWARD) 

        elif self.five_direction == self.BACKWARD:
            return Dice(self.row, self.col+1, self.BACKWARD) 

    def roll_forward(self):
        if self.five_direction == self.LEFT:
            return Dice(self.row+1, self.col, self.LEFT)

        elif self.five_direction == self.BOTTOM:
            return Dice(self.row+1, self.col, self.BACKWARD) 

        elif self.five_direction == self.RIGHT:
            return Dice(self.row+1, self.col, self.RIGHT) 

        elif self.five_direction == self.TOP:
            return Dice(self.row+1, self.col, self.FORWARD)

        elif self.five_direction == self.FORWARD:
            return Dice(self.row+1, self.col, self.BOTTOM) 

        elif self.five_direction == self.BACKWARD:
            return Dice(self.row+1, self.col, self.TOP) 

    def roll_backward(self):
        if self.five_direction == self.LEFT:
            return Dice(self.row-1, self.col, self.LEFT)

        elif self.five_direction == self.BOTTOM:
            return Dice(self.row-1, self.col, self.FORWARD) 

        elif self.five_direction == self.RIGHT:
            return Dice(self.row-1, self.col, self.RIGHT) 

        elif self.five_direction == self.TOP:
            return Dice(self.row-1, self.col, self.BACKWARD) 

        elif self.five_direction == self.FORWARD:
            return Dice(self.row-1, self.col, self.TOP) 

        elif self.five_direction == self.BACKWARD:
            return Dice(self.row-1, self.col, self.BOTTOM)


def dfs(start: Dice, end: Tuple[int, int], num_sides: int,
        board: List[str], visited: List[List[bool]]) -> bool:
    stack = deque()
    stack.append(start)
    visited = {(start.row, start.col, start.five_direction)}
    while stack:
        curr = stack.pop()
        if (curr.row, curr.col) == end and curr.five_direction == Dice.BOTTOM:
            return True
        for neighbor in curr.get_neighbors(num_sides, board):
            if (neighbor.row, neighbor.col, neighbor.five_direction) not in visited:
                visited.add((neighbor.row, neighbor.col, neighbor.five_direction))
                stack.append(neighbor)
    return False


def dacey_dice(num_sides: int, board: List[str]) -> None:
    start, end = None, None

    visited = set()
    # Find starting and ending coordinates
    for row in range(num_sides):
        for col in range(num_sides):
            if board[row][col] == 'S':
                start = Dice(row, col, Dice.LEFT)
            elif board[row][col] == 'H':
                end = (row, col)
    
    if dfs(start, end, num_sides, board, visited):
        print("Yes")
    else:
        print("No")


def main():
    input_lines = sys.stdin.read().splitlines()
    test_cases = int(input_lines[0])
    i = 1
    while test_cases:
        num_sides = int(input_lines[i])
        n = num_sides
        i += 1
        board = []
        while n:
            board.append(input_lines[i])
            i += 1
            n -= 1
        dacey_dice(num_sides, board)
        test_cases -= 1


if __name__ == '__main__':
    main()
