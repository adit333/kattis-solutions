"""https://ualberta.kattis.com/sessions/wuuqfx/problems/molecules

Approach: Form a linear system of equations
For each unknown molecule, we form 2 equations: one for the x and on for the y coordinate.
x = sum(x_i) / k
    where x_i are the molecules connected to molecule x
          k is the number of molecules connected to x
Similarly, for y
We will form 2 n*n matrices, one for the x and one for the y coordniates.
"""

import sys
from typing import List


def GaussianElimination(N, mat):
  for i in range(N-1):
    l = i
    for j in range(i+1, N):
      if abs(mat[j][i]) > abs(mat[l][i]):
        l = j
    for k in range(i, N+1):
      mat[i][k], mat[l][k] = mat[l][k], mat[i][k]
    for j in range(i+1, N):
      for k in range(N, i-1, -1):
        mat[j][k] -= mat[i][k] * mat[j][i] / mat[i][i]

    ans = [0] * N
  for j in range(N-1, -1, -1):
    t = 0.0
    for k in range(j+1, N):
      t += mat[j][k] * ans[k]
    ans[j] = (mat[j][N]-t) / mat[j][j]

  return ans


def molecules(num_of_atoms: int, num_of_connections: int,
        coordinates: List[List[int]], known: List[bool],
        atom_connections: List[List[int]], num_of_atom_connections: List[List[int]]) -> None:
    A_x = [[0 for _ in range(num_of_atoms+1)] for _ in range(num_of_atoms)]  # Augmented matrix for x
    A_y = [[0 for _ in range(num_of_atoms+1)] for _ in range(num_of_atoms)]  # Augmented matrix for y

    for i, coord in enumerate(coordinates):
        if known[i]:
            A_x[i][i] = 1
            A_y[i][i] = 1
            A_x[i][num_of_atoms] = coord[0]
            A_y[i][num_of_atoms] = coord[1]
        else:
            A_x[i][i] = num_of_atom_connections[i]
            A_y[i][i] = num_of_atom_connections[i]
            for connection in atom_connections[i]:
                A_x[i][connection] = -1
                A_y[i][connection] = -1
    
    X =  GaussianElimination(num_of_atoms, A_x)
    Y =  GaussianElimination(num_of_atoms, A_y)
    
    for i in range(num_of_atoms):
        if known[i]:
            print(*coordinates[i])
        else:
            print(X[i], Y[i])


def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_atoms, num_of_connections = list(map(int, input_lines[0].split()))

    coordinates = []
    known = [True for _ in range(num_of_atoms)]
    i = 0
    for line in input_lines[1:num_of_atoms+1]:
        coord = list(map(int, line.split()))
        coordinates.append(coord)
        if coord == [-1, -1]:
            known[i] = False
        i += 1
    
    connections = [[] for _ in range(num_of_atoms)]
    num_of_atom_connections = [0 for _ in range(num_of_atoms)]  # no. of atoms an atom is connected to
    for line in input_lines[num_of_atoms+1:]:
        u, v = list(map(int, line.split()))
        num_of_atom_connections[u-1] += 1
        num_of_atom_connections[v-1] += 1
        connections[u-1].append(v-1)
        connections[v-1].append(u-1)
    
    molecules(num_of_atoms, num_of_connections, coordinates, known, connections, num_of_atom_connections)


if __name__ == '__main__':
    main()
