"""https://ualberta.kattis.com/sessions/jot9wq/problems/addingwords
"""

import sys
import operator
from typing import Dict, List

def adding_words(input_lines: List[str]) -> None:
    variables = {}
    for input_line in input_lines:
        tokens = input_line.split()
        if tokens[0] == 'def':
            variables[tokens[1]] = int(tokens[2])
        elif tokens[0] ==  'calc':
            print(' '.join(tokens[1:]), end=' ')
            operand1 = int(variables.get(tokens[1], False))
            operand2 = int(variables.get(tokens[3], False))
            if operand1 and operand2:
                if tokens[2] == '+':
                    result = operand1 + operand2
                elif tokens[2] == '-':
                    result = operand1 + operand2
                if result in variables.values():
                    print(list(variables.keys())[list(variables.values()).index(result)])
                else:
                    print('unknown')
            else:
                print('unknown')
        elif tokens[0] ==  'clear':
            variables = {}
        
def get_result(tokens: List[str], variables: Dict[str, int]):
    result = 0
    i = 0
    operators = {'+': operator.add, '-': operator.sub}
    while i < len(tokens):
        if tokens[i] in operators:
            operation = operators.get(tokens[i])
            operand = int(variables.get(tokens[i+1], False))
            if operand:
                result = result + operation(result, tokens[i+1])
                i += 2
            else:
                return False
        else:
            operand = int(variables.get(tokens[i+1], False))
            if operand:
                result = result + operand
                i += 1
            else:
                return False
    return result


def main():
    #input_lines = sys.stdin.read().splitlines()
    input_lines = ['def foo 3',
                    'calc foo + bar = ',
                    'def bar 7', 
                    'def programming 10', 
                    'calc foo + bar = ',
    ]
    adding_words(input_lines)

if __name__ == '__main__':
    main()
