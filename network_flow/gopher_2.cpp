/*
  Kattis solution: gopher2

  Idea:
  Consider the bipartite graph between gophers and holes. An edge means
  that gopher can reach that hole in time.

  Then compute a maximum matching in this graph, this indicates the maximum
  number of gophers that can reach holes safely. So the final answer is:
    (# gophers) - (max matching size)
*/

#include <iostream>
#include <vector>
#include <complex>

using namespace std;

typedef complex<double> point;
typedef vector<int> vi;

// Think: the bipartite graph is from L to R
// For a vertex u in L, g[u] is the vector of neighbours in R.
// Here we think L is indexed from 0 to n-1 and R from 0 to m-1.
vector<vi> g;

// for an index i of a node in L, ml[i] is the index of the node in R
// it is matched to (using -1 if i is not matched). Similarly, for an index
// of a node j in R, mr[j] is the index of a node in L that j is matched to.
vi ml, mr;

/*
  u - index of a vertex in L
  iter - which iteration are we on?
  seen[v] - the most recent iteration we saw v, so seen[v] == iter if and only
     if we have seen v in this augmenting path search
*/
bool augment(int u, int iter, vi& seen) {
  if (seen[u] == iter) return false;

  seen[u] = iter;

  for (auto v : g[u])
    if (mr[v] == -1 || augment(mr[v], iter, seen)) {
      ml[u] = v;
      mr[v] = u;
      return true;
    }
  return false;
}

int match(int n, int m) {
  ml.assign(n, -1);
  mr.assign(m, -1);

  vi seen(n, -1);

  int tot = 0;
  // go through each vertex in L and see if it can match into R
  // via some augmenting path
  for (int u = 0; u < n; ++u)
    if (ml[u] == -1 && augment(u, u, seen))
      ++tot;
  return tot;
}

int main() {
  int n, m, s, v;

  while (cin >> n >> m >> s >> v) {
    g.assign(n, vi());
    vector<point> gopher(n);

    for (int i = 0; i < n; ++i) {
      double x, y;
      cin >> x >> y;
      gopher[i] = point(x, y);
    }

    // read in each hole and check which gophers can reach the hole
    for (int j = 0; j < m; ++j) {
      double x, y;
      cin >> x >> y;
      point hole(x, y);
      for (int i = 0; i < n; ++i)
        if (abs(hole-gopher[i]) <= v*s + 1e-8)
          g[i].push_back(j);
    }

    cout << n-match(n, m) << endl;
  }

  return 0;
}