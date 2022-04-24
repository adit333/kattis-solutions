"""https://ualberta.kattis.com/sessions/vg7m4t/problems/plowking

Approach:
- We must take edge labels 1, and 2, so we will have 3 vertices now
- When it comes to edge label 3, we can connect vertex 3 to vertex 1
    and give it edge label 3.
- Then, we must take edge label 4 and we land at vertex 4.
- Then, we can vertex 4 to vertex 1 and 2, with edge labels 5, 6.
    It is already connected to vertex 3
- Then, we must take edge label 7 and land a vertex 5,
    we can connect vertex 5 to each ov vertex 1, 2, 3 and give those edges labels 8, 9, 10.
- Then we must take edge label 11 and go to vertex 6 and so on.

Notice a pattern? Everytime we land at a vertex, we can connect it with edges to k-1 vertices we
have already visited, leaving the higg value edges to connect tree components.
Thus, the small values edges are used to form connected components, and high vcalue edge is used
to connect two different components.
"""

import sys


def plow_king(num_cities: int, num_roads_to_upgrade: int) -> None:
    # num_cities-1 edges required to connect all cities
    num_of_excess_edges = num_roads_to_upgrade - (num_cities-1)

    total_cost = 0
    label_plow_king_will_choose_next = 1
    num_of_roads_chosen_to_plow = 1

    while label_plow_king_will_choose_next <= num_roads_to_upgrade:
        total_cost += label_plow_king_will_choose_next

        if num_of_excess_edges > 0: # Then we can use small edges to connect to already connected component
            label_plow_king_will_choose_next += min(num_of_excess_edges,
                num_of_roads_chosen_to_plow-1)
            num_of_excess_edges -= num_of_roads_chosen_to_plow-1
        
        label_plow_king_will_choose_next += 1
        num_of_roads_chosen_to_plow += 1
        
    print(total_cost)



def main():
    input_lines = sys.stdin.read().splitlines()
    num_cities, num_roads_to_upgrade = list(map(int, input_lines[0].split()))
    plow_king(num_cities, num_roads_to_upgrade)


if __name__ == '__main__':
    main()
