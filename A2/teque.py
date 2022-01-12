"""https://ualberta.kattis.com/sessions/jot9wq/problems/teque
"""

import math
import sys
from typing import List

def teque(operations: List[str]) -> None:
    teque_ds = []
    result = []
    for operation in operations:
        opcode, value = operation.split()
        if opcode == 'push_back':
            teque_ds.append(value)
        elif opcode == 'push_front':
            teque_ds.insert(0, value)
        elif opcode == 'push_middle':
            mid_pos = math.ceil(len(teque_ds) / 2)
            teque_ds.insert(mid_pos, value)
        elif opcode == 'get':
            result.append(teque_ds[int(value)])
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