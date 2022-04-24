"""https://ualberta.kattis.com/sessions/zy3te5/problems/classpicture
"""

import itertools
import sys
from typing import Dict, List, Set, Tuple

def construct_enemies_map(enemy_pairs: List[Tuple[str]]) -> Dict[str, Set[str]]:
    enemies_map = {}
    for enemy_pair in enemy_pairs:
        enemy1, enemy2 = enemy_pair
        if enemy1 not in enemies_map:
            enemies_map[enemy1] = set()
        enemies_map[enemy1].add(enemy2)
        if enemy2 not in enemies_map:
            enemies_map[enemy2] = set()
        enemies_map[enemy2].add(enemy1)
    return enemies_map

def class_picture(class_students: List[str], enemy_pairs: List[Tuple[str]]) -> None:
    enemies_map = construct_enemies_map(enemy_pairs)
    possible_orderings = list(itertools.permutations(sorted(class_students)))
    for possible_ordering in possible_orderings:
        found = True
        for i in range(1, len(possible_ordering)):
            person1 = possible_ordering[i-1]
            person2 = possible_ordering[i]
            if person1 in enemies_map.get(person2, set()):
                found = False
                break
        if found:
            print(' '.join(possible_ordering))
            return
    print('You all need therapy.')

def main():
    input_lines = sys.stdin.read().splitlines()
    i = 0
    while i < len(input_lines):
        class_students = []
        num_students = int(input_lines[i])
        i += 1
        start = i
        while i < num_students + start:
            class_students.append(input_lines[i])
            i += 1
        num_of_enemy_pairs = int(input_lines[i])
        i += 1
        enemy_pairs = []
        start = i
        while i < num_of_enemy_pairs + start:
            enemy_pairs.append(tuple(input_lines[i].split()))
            i += 1
        class_picture(class_students, enemy_pairs)

    # class_picture(['Ron', 'George', 'Bill', 'Fred', 'Jenny'],
    #     [('Fred', 'Jenny'), ('Bill', 'Ron'), ('George', 'Jenny')]
    # )
    # class_picture(['Alice', 'Bob'], [('Alice', 'Bob')])

if __name__ == '__main__':
    main()