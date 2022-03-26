/*
  https://ualberta.kattis.com/sessions/v6p28m/problems/landscaping
  Kattis solution - landscaping

  Idea:
  For each square p, think we have a variable X[p] that will be either
  "low" or "high" indicating the final configuration of that square.

  If X[p] == "low" yet the square was initially '#', or if X[p] == "high"
  yet the square was initially '.', we pay B for the elevation change.

  For adjacent squares p,q, if X[p] != X[q] we pay A because the tractor
  changes elevation.

  This can be modelled as a min-cut problem. Consider the undirected
  graph whose vertices are all squares in the grid and two special
  vertices we call S and T.

  Think, S means "high" and T means "low". Connect S to every vertex
  represention a '.' vertex and set the capacity to B. Connect T to
  every vertex representing a '#' and set the capacity to B.

  Finally, for each pair of adjacent squares add an edge with capacity A.

  Now, an S-T cut corresponds to decisions as to the final elevation
  of each square of terrain. That is, the S-side is all squares that
  should end up "high" and the T-side is all squares that should end up "low".

  The edges jumping between the S-side and T-side are the decisions we pay for:
  each square that we changed the elevation for and each pair of adjacent squares
  that differ in elevation.

  Uses KACTL's Dinic, which is for a directed graph. So we have to add
  both directions of every undirected edge (see the lambda in the code).
*/

#include <bits/stdc++.h>

using namespace std;

// BEGIN KACTL MACROS AND CODE

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

using ll = long long;
using vi = vector<int>;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

// END KACTL MACROS AND CODE

int main() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;

  int s = n*m, t = n*m+1;
  vector<string> grid(n);
  for (auto& row : grid) cin >> row;

  Dinic flow(n*m+2);

  // models an undirected edge in the flow network by
  // adding both directions of the edge
  auto add_undir_edge = [&](int u, int v, int b) {
    flow.addEdge(u, v, b);
    flow.addEdge(v, u, b);
  };

  for (int r = 0; r < n; ++r)
    for (int c = 0; c < m; ++c) {
      // add edges of cost b to model elevation changes
      if (grid[r][c] == '.') add_undir_edge(s, r*m+c, b);
      else add_undir_edge(t, r*m+c, b);

      // add edges of cost a to model adjacent squares with different costs
      if (r > 0) add_undir_edge((r-1)*m+c, r*m+c, a);
      if (c > 0) add_undir_edge(r*m+c-1, r*m+c, a);
    }

  cout << flow.calc(s, t) << endl;

  return 0;
}