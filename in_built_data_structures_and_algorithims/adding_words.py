"""https://ualberta.kattis.com/sessions/jot9wq/problems/addingwords
"""

import sys
from typing import List


def adding_words(input_lines: List[str]) -> None:
    variables = {}
    for input_line in input_lines:
        tokens = input_line.split()
        if tokens[0] == 'def':
            variables[tokens[1]] = tokens[2]

        elif tokens[0] ==  'calc':
            print(' '.join(tokens[1:]), end=' ')
            statement = []
            unknown = False
            for token in tokens[1:-1]:
                if token in variables:
                    statement.append(variables[token])
                elif token == '+':
                    statement.append('+')
                elif token == '-':
                    statement.append('-')
                else:
                    unknown = True
                    print('unknown')
                    break

            if not unknown:
                result = str(eval(''.join(statement)))
                if result in variables.values():
                    print(list(variables.keys())[list(variables.values()).index(result)])
                else:
                    print('unknown')

        elif tokens[0] ==  'clear':
            variables = {}


def main():
    #input_lines = sys.stdin.read().splitlines()
    input_lines = ['def foo 3',
                    'calc foo + bar = ',
                    'def bar 7', 
                    'def programming 10', 
                    'calc foo + bar = ',
                    'def is 4',
                    'def fun 8',
                    'calc programming - is + fun =',
                    'def fun 1',
                    'calc programming - is + fun =',
                    'clear',
    ]
    adding_words(input_lines)

if __name__ == '__main__':
    main()
