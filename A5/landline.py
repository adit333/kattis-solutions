"""https://ualberta.kattis.com/sessions/deivji/problems/landline
Find MST only for secure buildings then use cheapes edge to connect insecure
buildings ensuring they remain as leaves.
"""

import sys
from typing import List, Set

# Union-Find Disjoint Sets Library written in OOP manner
# using both path compression and union by rank heuristics
class UnionFind:                                # OOP style
    def __init__(self, N):
        self.p = [i for i in range(N)]
        self.rank = [0 for i in range(N)]
        self.setSize = [1 for i in range(N)]
        self.numSets = N

    def findSet(self, i):
        if (self.p[i] == i):
            return i
        else:
            self.p[i] = self.findSet(self.p[i])
            return self.p[i]

    def isSameSet(self, i, j):
        return self.findSet(i) == self.findSet(j)

    def unionSet(self, i, j):
        if (not self.isSameSet(i, j)):
            self.numSets -= 1
            x = self.findSet(i)
            y = self.findSet(j)
        # rank is used to keep the tree short
        if (self.rank[x] > self.rank[y]):
            self.p[y] = x
            self.setSize[x] += self.setSize[y]
        else:
            self.p[x] = y
            self.setSize[y] += self.setSize[x]
            if (self.rank[x] == self.rank[y]):
                self.rank[y] += 1

    def numDisjointSets(self):
        return self.numSets

    def sizeOfSet(self, i):
        return self.setSize[self.findSet(i)]


def landline(num_vertices: int, num_insecure_buildings: int,
        insecure_buildings: Set[int], edge_list: List[int], adjacency_list) -> None:
    edge_list.sort()
    mst_cost = 0
    num_edges_taken = 0
    num_secure_buildings = num_vertices - num_insecure_buildings

    # Construct an MST only for secure building first
    UF = UnionFind(num_vertices)
    for edge in edge_list:
        if num_edges_taken == num_secure_buildings - 1:
            break
        w, u, v, = edge
        if u in insecure_buildings or v in insecure_buildings:
            continue
        if not UF.isSameSet(u, v):
            num_edges_taken += 1
            mst_cost += w
            UF.unionSet(u, v)

    # Now add insecure buildings as leaves only connecting them with the cheapest edge
    for u in insecure_buildings:
        cheapest_edge = float('inf')
        for v, w in adjacency_list[u]:
            if v not in insecure_buildings and w < cheapest_edge:
                cheapest_edge = w
        if cheapest_edge < float('inf'):
            num_edges_taken += 1
            mst_cost += cheapest_edge
    
    if num_edges_taken == num_vertices - 1:
        print(mst_cost)
    elif num_edges_taken == 0 and num_insecure_buildings == 2:      # TODO: rectify this hack for special case of just 2 insecure buildings
        print(edge_list[0][2])
    else:
        print("impossible")


def main():
    input_lines = sys.stdin.read().splitlines()
    num_vertices, num_edges, num_insecure_buildings = list(map(int, input_lines[0].split()))
    insecure_buildings = set(u-1 for u in list(map(int, input_lines[1].split())))
    edge_list = []
    adjacency_list = [[] for _ in range(num_vertices)]
    for i in range(2, len(input_lines)):
        u, v, w = list(map(int, input_lines[i].split()))
        edge_list.append((w, u-1, v-1))
        adjacency_list[u-1].append((v-1, w))
        adjacency_list[v-1].append((u-1, w))
    landline(num_vertices, num_insecure_buildings, insecure_buildings, edge_list, adjacency_list)


if __name__ == '__main__':
    main()
