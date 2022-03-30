/*
  Kattis example - roadtimes

  For full usage information for the simplex algorithm included here, see
  https://github.com/UAPSPC/Code-Archive/blob/master/optimization/simplex.cpp

  Idea
  For each source/destination pair (s,t), find the shortest s-t path
  using any shortest path algorithm (Floyd-Warshall suffices).
  Call this path P(s,t) (the statement guarantees it is unique).

  Let x_e denote the time it takes to traverse edge e.

  Add constraints d_e <= x_e and d_e <= 2*x_e for every edge.

  For every s_i-t_i query pair, add the constraint \sum_{e \in P(s,t)} = a_i.

  Solve the LP to minimize \sum_{e \in P(s,t)} x_e and then solve the LP to
  maximize \sum_{e \in P(s,t)} x_e.


  NOTES:
  * The LP solver assumes we are maximizing, so when we want to
  minimize \sum_{e \in P(s,t)} x_e we just maximize \sum_{e \in P(s,t)} -x_e.

  * The LP solver assumes constraints are of the form A*x <= b.
  So for a >= constraint, just negate both sides.
  For an equality constraint, add both <= versions (i.e. if a*x == b is the constraint
  then a*x <= b and -a*x <= -b).

  Running time: 2*q calls to simplex on a system with O(n^2) equations and variables.
  But n is small and simplex runs very fast.
*/

#include <bits/stdc++.h>

#define MAXN 150
#define MAXC 2500
#define EPS 1e-9

using namespace std;

typedef pair<int, int> pii;

// my matrices (not used in simplex)
double AA[MAXC+1][MAXN+1], bb[MAXC], cc[MAXN];

// ****** START OF SIMPLEX CODE ********

// used by simplex, don't change!
double A[MAXC+1][MAXN+1], b[MAXC], c[MAXN], x[MAXN], val;
int xB[MAXC], xN[MAXN];

//variable xB[r] exits the basis, xN[c] enters the basis
void pivot(int n, int m, int r, int c) {
  for (int j = 0; j <= n; ++j)
    if (j != c)
      A[r][j] /= A[r][c];

  for (int i = 0; i <= m; ++i)
    if (i != r)// && fabs(A[i][c]) > EPS) //maybe saves time in sparse instances
      for (int j = 0; j <= n; ++j)
        if (j != c)
          A[i][j] -= A[r][j]*A[i][c];

  for (int i = 0; i <= m; ++i)
    if (i != r)
      A[i][c] = -A[i][c]/A[r][c];

  A[r][c] = 1/A[r][c];

  swap(xB[r], xN[c]);
}

// Bland's rule: if two indices are valid choices for the pivot, choose the
//               one with the lexicographically smallest variable
void bland(int a, int& b, int* v) {
  if (b < 0 || v[a] < v[b]) b = a;
}

// returns true if a feasible basis is found, false if LP is infeasible
bool phase1(int n, int m) {
  while (true) {
    int r = -1, c = -1;

    for (int i = 0; i < m; ++i)
      if (A[i][n] < -EPS)
        bland(i, r, xB);

    if (r == -1) return true;

    for (int j = 0; j < n; ++j)
      if (A[r][j] < -EPS)
        bland(j, c, xN);

    if (c == -1) return false;

    pivot(n, m, r, c);
  }
}

// Assumes A[i][n] >= 0 for all 0 <= i < m (i.e. current basis is feasible)
// Returns true if an optimum is found, false if the LP is unbounded
bool phase2(int n, int m) {
  // pivot until no improvement
  while (true) {
    int r = -1, c = -1;

    // find a column with negative c-coefficient
    for (int j = 0; j < n; ++j)
      if (A[m][j] > EPS)
        bland(j, c, xN);

    if (c == -1) return true;

    for (int i = 0; i < m; ++i)
      if (A[i][c] > EPS) {
        if (r == -1) r = i;
        else {
          double lhs = A[i][c]*A[r][n], rhs = A[r][c]*A[i][n];
          if (lhs > rhs + EPS) r = i;
          else if (fabs(lhs-rhs) < EPS) bland(i, r, xB);
        }
      }

    if (r == -1) return false;

    pivot(n, m, r, c);
  }
}


// Returns: 1 - opt found (x is this opt and val is its value)
//          0 - infeasible, -1 - unbounded
int simplex(int n, int m) {
  assert(n < MAXN);
  assert(m < MAXC);

  //add b to the end of A and c to the bottom of A
  for (int j = 0; j < n; ++j) {
    A[m][j] = c[j];
    xN[j] = j;
  }

  // prepare initial (possibly infeasible) basis
  for (int i = 0; i < m; ++i) {
    A[i][n] = b[i];
    xB[i] = i+n;
  }

  A[m][n] = 0; //this will be -(value of x)

  // now pivot to a feasible basis
  if (!phase1(n, m)) return 0;

  // and then pivot to an optimum basis
  if (!phase2(n, m)) return -1;

  // recover x and val
  val = -A[m][n];
  for (int i = 0; i < n; ++i) x[i] = 0;
  for (int i = 0; i < m; ++i)
    if (xB[i] < n)
      x[xB[i]] = A[i][n];

  return 1;
}

// ******* END OF SIMPLEX PART

int main() {
  cout.setf(ios::fixed);
  cout.precision(9);

  int n;

  // orig[][] - input distance matrix
  // dist[][] - will be the shortest-path cost matrix
  int dist[50][50], orig[50][50];

  // nxt[u][v] is the node w just after u on the shortest u-v path in the graph
  int nxt[50][50];

  // mp[{u,v}] will be a unique index for edge {u,v}
  // the edges will be indexed consecutively this way
  // useful to build the linear program
  map<pii, int> mp;

  // Read the input
  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      cin >> dist[i][j];
      if (i != j && dist[i][j] >= -0.5) {
        int at = mp.size();
        mp[pii(i,j)] = at;
      }
      orig[i][j] = dist[i][j];

      if (dist[i][j] < -0.5) dist[i][j] = 1000000; // infinity, to model "no edge"
      nxt[i][j] = j;
    }

  // Floyd-Warshall algorithm to compute all-pairs shortest path distances
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          nxt[i][j] = nxt[i][k];
        }

  // set up inequalities involving the given routes
  int r, nc = 0; // nc counts the # of constraints we have added so far
  cin >> r;
  for (int i = 0; i < r; ++i) {
    int sr, er, lr;
    cin >> sr >> er >> lr;
    // nc and nc+1 index the two <= inequalities modelling this equality

    // set up the RHS of these constraints
    bb[nc] = lr; // dist[sr][er];
    bb[nc+1] = -lr; // -dist[sr][er];

    // get the shortest sr-er path from the Floyd-Warshall table
    while (sr != er) {
      int suc = nxt[sr][er];
      int eid = mp[pii(sr, suc)];

      // set the coefficients for this edge
      AA[nc][eid] = 1;
      AA[nc+1][eid] = -1;
      sr = suc;
    }
    nc += 2;
  }

  // now set up the d_e <= x_e <= 2*d_e constraints
  for (auto it : mp) {
    int dd = orig[it.first.first][it.first.second];
    AA[nc][it.second] = 1;
    bb[nc] = 2*dd;
    AA[nc+1][it.second] = -1;
    bb[nc+1] = -dd;
    nc += 2;
  }

  int vars = mp.size();

  // process the queries
  int q;
  cin >> q;
  while (q--) {
    int vs, ve;
    cin >> vs >> ve;

    cout << vs << ' ' << ve << ' ';

    // NOTE: A, b, c are the matrices/vectors used by simplex()
    // AA, bb, cc are backups since A, b, c will be destroyed by simples()

    // get the edges on the shortest vs - ve path and set their objective
    // function coefficient to 1 since we want the minimum/maximum estimated time
    memset(cc, 0, sizeof(cc));
    while (vs != ve) {
      int vnxt = nxt[vs][ve];
      assert(mp[pii(vs, vnxt)] < vars);
      cc[mp[pii(vs, vnxt)]] = 1;
      vs = vnxt;
    }

    // get the minimum estimated time by maximizing the negation of the objective
    // function (and reporting the absolute value of the answer)
    memcpy(A, AA, sizeof(AA));
    memcpy(b, bb, sizeof(bb));
    memcpy(c, cc, sizeof(cc));
    for (int i = 0; i < vars; ++i) c[i] = -c[i];

    assert(simplex(vars, nc) == 1);
    cout << fabs(-val) << ' ';

    // now get the maximum estimated time
    memcpy(A, AA, sizeof(AA));
    memcpy(b, bb, sizeof(bb));
    memcpy(c, cc, sizeof(cc));

    assert(simplex(vars, nc) == 1);
    cout << val << endl;
  }

  return 0;
}