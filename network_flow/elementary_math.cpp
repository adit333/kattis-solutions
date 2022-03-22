/*
  Kattis solution - elementarymath

  Idea:
  Create a bipartite graph where the nodes on the left side represent
  the input pairs of numbers (i.e. expressions to form) and the right side
  represents possible answers. Each input expression has <= 3 different possible
  answers. Put an edge between an expression and a possible answer if that
  answer would be valid for one of +, -, or * for that expression.

  Compute a maximum matching. If its size is < # expressions, "impossible".

  Else use the matching to decide what values should be taken by the expressions.

  Slightly tricky: the RHS values could be huge integers but we want them
  to be indexed from 0 to # possible answers (at most 3*n). So we also map
  the possible answers to indices. See how it is done in the code.

  If one used the simple matching algorithm discussed in the meetings,
  this would run in O(n^2) time since the number of edges is <= 3n
  and the number of nodes in total is <= 4n.

  I am showing how to use a faster algorithm from KACTL: hopcroftKarp
  The running time in general is O(sqrt(|V|) * |E|). In this case,
  the running time is O(n^{1.5}). But the slower O(n^2) algorithm is
  more than enough, so you don't need hopcroftKarp.
*/

#include <bits/stdc++.h>

using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pii = pair<int, int>;


// Start of KACTL matching algorithm

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

// End of KACTL matching algorithm

int main() {
  int n;
  cin >> n;

  // maps numbers to a unique values to index the RHS of the bipartite graph
  unordered_map<ll, int> id;

  vector<pii> inp(n); // inp[i] is the two LHS values in expression i

  // the bipartite graph: LHS are expressions, RHS are possible values
  // they could take
  vvi g(n);

  // if x is not in the map "id", add it with the next available index
  // then push id[x] to g[i] indicating the RHS node representing x is a
  // neighbour of expression i
  auto update = [&](int i, ll x) {
    if (id.find(x) == id.end()) id[x] = id.size();
    g[i].push_back(id[x]);
  };

  // read in an expression,
  for (int i = 0; i < n; ++i) {
    ll a, b;
    cin >> a >> b;
    inp[i].first = a;
    inp[i].second = b;

    // try all valid answers and build the graph
    update(i, a+b);
    update(i, a*b);
    update(i, a-b);
  }

  // required for the KACTL matching algorithm
  vi btoa(id.size(), -1);

  // match expressions to possible answers, check that we matched enough
  if (hopcroftKarp(g, btoa) != n) {
    cout << "impossible" << endl;
    return 0;
  }

  // associate each index with the value it should take
  // so assoc[i] is the answer we should provide for expression i
  vector<ll> assoc(n);
  for (auto p : id)
    if (btoa[p.second] != -1)
      assoc[btoa[p.second]] = p.first;

  // finally, go through each expression and print the answer
  for (int i = 0; i < n; ++i) {
    // just so the variable names are short
    ll a = inp[i].first, b = inp[i].second, c = assoc[i];

    // determine which character to print
    char oper;
    if (a*b == c) oper = '*';
    else if (a+b == c) oper = '+';
    else if (a-b == c) oper = '-';
    else assert(false); // should never fire, this is just a check


    cout << a << ' ' << oper << ' ' << b << " = " << c << endl;
  }

  return 0;
}