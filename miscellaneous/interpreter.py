"""https://ualberta.kattis.com/problems/interpreter
Algorithm: Simply iterate over the instructions in RAM one at a time, doing the appropriate action.
"""

import sys
from typing import List

RAM_SIZE = 1000
NUM_REGISTERS = 10

def interpreter(ram: List[str]) -> int:
    registers = [0] * NUM_REGISTERS
    count = 0
    program_conuter = 0
    while True:
        opcode = ord(ram[program_conuter][0]) - 48
        a, b = ord(ram[program_conuter][1]) - 48, ord(ram[program_conuter][2]) - 48
        count += 1
        program_conuter += 1

        if opcode == 1:
            break
        elif opcode == 2:
            registers[a] = b
        elif opcode == 3:
            registers[a] = (registers[a] + b) % 1000
        elif opcode == 4:
            registers[a] = (registers[a] * b) % 1000
        elif opcode == 5:
            registers[a] = registers[b]
        elif opcode == 6:
            registers[a] = (registers[a] + registers[b]) % 1000
        elif opcode == 7:
            registers[a] = (registers[a] * registers[b]) % 1000
        elif opcode == 8:
            registers[a] = int(ram[registers[b]])
        elif opcode == 9:
            if registers[a] < 10:
                ram[registers[b]] = f'00{registers[a]}'
            elif registers[a] < 100:
                ram[registers[b]] = f'0{registers[a]}'
            else:
                ram[registers[b]] = str(registers[a])
        elif opcode == 0:
            if registers[b] != 0:
                program_conuter = int(registers[a])

        

    print(count)

def main():
    ram = ['299', '492', '495', '399', '492', '495', '399',
                '283', '279', '689', '078', '100', '000', '000', '000',] + ['000' for i in range(985)]
    interpreter(ram)
    # ram = ['000'] * RAM_SIZE
    # for i, instruction in enumerate(sys.stdin):
    #     ram[i] = instruction
    # interpreter(ram)

if __name__ == '__main__':
    main()