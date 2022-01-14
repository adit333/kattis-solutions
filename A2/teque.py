"""https://ualberta.kattis.com/sessions/jot9wq/problems/teque
"""

import sys
from collections import deque
from typing import Deque, List


def balance(teque_ds_left: Deque, teque_ds_right: Deque) -> None:
    if (len(teque_ds_left) == len(teque_ds_right))  \
        or (len(teque_ds_left) == len(teque_ds_right) + 1):
        return
    # If we are here, this means that there are odd no. of elements
    # and either the left deque has 1 more element than it should
    # or the right deque has one or more element than it should
    if len(teque_ds_left) == len(teque_ds_right) + 2:   # Left deque has 1 extra element
        teque_ds_right.appendleft(teque_ds_left.pop())
    else:
        teque_ds_left.append(teque_ds_right.popleft())


def teque(operations: List[str]) -> None:
    result = []     # Used to store the output so we can print it all at once
    teque_ds_left = deque()
    teque_ds_right = deque()
    for operation in operations:
        opcode, value = operation.split()
        if opcode == 'push_back':
            teque_ds_right.append(value)
            balance(teque_ds_left, teque_ds_right)
        elif opcode == 'push_front':
            teque_ds_left.appendleft(value)
            balance(teque_ds_left, teque_ds_right)
        elif opcode == 'push_middle':
            teque_ds_left.append(value)
            balance(teque_ds_left, teque_ds_right)
        elif opcode == 'get':
            if int(value)  < len(teque_ds_left):
                result.append(teque_ds_left[int(value)])
            else:
                right_index = int(value) - len(teque_ds_left)
                result.append(teque_ds_right[right_index])
    sys.stdout.write('\n'.join(result))


def main():
    # input_lines = sys.stdin.read().splitlines()
    # teque(input_lines[1:])
    teque([
        'push_back 9',
        'push_front 3',
        'push_middle 5',
        'get 0',
        'get 1',
        'get 2',
        'push_middle 1',
        'get 1',
        'get 2',
    ]
    )

if __name__ == '__main__':
    main()