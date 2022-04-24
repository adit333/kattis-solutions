/*https://ualberta.kattis.com/sessions/deivji/problems/equivalences
*/

#include <bits/stdc++.h>

#define MAXN 20000

using namespace std;

using VI = vector<int>;

VI g[MAXN], curr;
vector< VI > scc;
int dfsnum[MAXN], low[MAXN], id;
char done[MAXN];

void visit(int x){
  curr.push_back(x);
  dfsnum[x] = low[x] = id++;
  for(size_t i = 0; i < g[x].size(); i++)
    if(dfsnum[g[x][i]] == -1){
      visit(g[x][i]);
      low[x] = min(low[x], low[g[x][i]]);
    } else if(!done[g[x][i]])
      low[x] = min(low[x], dfsnum[g[x][i]]);

  if(low[x] == dfsnum[x]){
    VI c; int y;
    do{
      done[y = curr[curr.size()-1]] = 1;
      c.push_back(y);
      curr.pop_back();
    } while(y != x);
    scc.push_back(c);
  }
}

void strong_conn(int n){
  memset(dfsnum, -1, n*sizeof(int));
  memset(done, 0, sizeof(done));
  scc.clear(); curr.clear();
  for(int i = id = 0; i < n; i++)
    if(dfsnum[i] == -1) visit(i);
}

int main() {
    int num_test_cases;
    cin >> num_test_cases;
    while (num_test_cases--) {
        int n, m;
        cin >> n >> m;
        // need to clear out the old adjacency list
        for (int v = 0; v < n; ++v)
            g[v].clear();

        vector<pair<int,int>> edges(m);
        for (auto& e : edges) {
            cin >> e.first >> e.second;
            g[e.first-1].push_back(e.second-1);
        }
        
        // get the strongly connected components
        strong_conn(n);

        // if there is only one component, 0 implications needed
        if (scc.size() == 1) {
            cout << 0 << endl;
            continue;
        }

        // record the scc for each original vertex
        vector<int> scc_num(n);
        for (int i = 0; i < scc.size(); ++i)
            for (int v : scc[i])
                scc_num[v] = i;

        // count the number of edges exiting and entering each scc
        vector<int> indeg(scc.size(), 0), outdeg(scc.size());
        for (int v = 0; v < n; ++v)
            for (int w : g[v])
                if (scc_num[v] != scc_num[w]) {
                    ++outdeg[scc_num[v]];
                    ++indeg[scc_num[w]];
                }

        int num_of_zero_in_deg_scc = 0, num_of_zero_out_deg_scc = 0;
        for (int scc_num = 0; scc_num < scc.size(); ++scc_num) {
            if (indeg[scc_num] == 0)
                ++num_of_zero_in_deg_scc;
            if (outdeg[scc_num] == 0)
                ++num_of_zero_out_deg_scc;
        }
        cout << max(num_of_zero_in_deg_scc, num_of_zero_out_deg_scc) << endl;
    }
}