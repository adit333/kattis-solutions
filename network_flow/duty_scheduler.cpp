/*
https://ualberta.kattis.com/sessions/v6p28m/problems/dutyscheduler
  Kattis example - dutyscheduler

  Idea:
  Binary search for the smallest value k such that there is an assignment
  using each RA at most k times.

  To check if a value of k is valid, we use flow.

  Built a (directed) flow network a node for each RA, a node for each day, and two
  special nodes s,t.

  Connect s to each RA with a capacity-k edge.
  Connect each RA to each day they can work with a capacity-1 edge.
  Connect each day to t with a capacity-2 edge.

  There is a solution if and only if the max flow is 2*(# days).

  To see this, if there is a solution then it spells out a flow:
    For an RA i, s-->i carries flow == # of times RA is used (<= k by assumption)
    For an RA i and a day j they can work, i-->j carries 1 flow if and only if i was assigned to j
    For a day j, j-->t carries flow exactly 2 since 2 RAs were assigned to it.
  The logic reverses: if there is a flow with value 2*(# days) then seeing
  which edges carry flow describes how to assign the RAs.

  This solution uses KACTL's Dinic implementation of max flow which is really fast.
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
  int m, n;
  cin >> m >> n;

  // the name of the RA and the days they are available
  // doing m+1 because 1-indexing is convenient for this problem
  vector<string> ra_name(m+1);
  vector<vector<int>> ra_avial(m+1);

  for (int i = 1; i <= m; ++i) {
    cin >> ra_name[i];
    int d;
    cin >> d;
    ra_avial[i].resize(d);
    for (int& x : ra_avial[i]) cin >> x;
  }

  // INVARIANT:
  // impossible if each RA is assigned <= "lo" times
  // possible if each RA is assigned <= "hi" times
  // uses n+1 instead of n to ensure the binary search sees it
  // (i.e. so variable "best" is actually filled out)
  int lo = 0, hi = n+1;

  // needed to print the actual assignment, will store the
  // flow for the best value of k we find
  Dinic best(0);

  while (lo+1 < hi) {
    // RA vertices are 1, 2, ..., m
    // Day vertices are m+1, m+2, ..., m+n
    // s = 0, t = m+n+1

    int k = (lo+hi)/2;

    Dinic flow(m+n+2);
    int s = 0, t = m+n+1;

    // add edges from s to each RA with capacity k (indicating each
    //  can be assigned to <= k days)
    for (int i = 1; i <= m; ++i)
      flow.addEdge(s, i, k);

    // add edges from each RA to each day they can work, the capacity is 1
    // indicating they can only be assigned there once
    for (int i = 1; i <= m; ++i)
      for (int j : ra_avial[i])
        flow.addEdge(i, m+j, 1);

    // add edges from each day to t indicating the day
    // can only be assigned 2 RAs
    for (int j = 1; j <= n; ++j)
      flow.addEdge(m+j, t, 2);

    // if we can cover the n days with 2 RAs each
    if (flow.calc(s, t) == 2*n) {
      hi = k;
      best = flow; // save for when we need to print the result
    }
    else {
      lo = k;
    }
  }

  // by the invariant, after the search "hi" is the smallest value of k
  // we also stored the flow calculation for this best value in the variable "best"

  cout << hi << endl;
  for (int j = 1; j <= n; ++j) {
    cout << "Day " << j << ":";

    // go through each RA and each edge exiting them in the flow network
    // if it carries flow, then the optimal solution assigned the RA to this day
    for (int i = 1; i <= m; ++i)
      for (auto e : best.adj[i])
        if (e.to == m+j && e.flow() == 1)
          cout << ' ' << ra_name[i];
    cout << endl;
  }

  return 0;
}