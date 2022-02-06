/*https://ualberta.kattis.com/sessions/deivji/problems/equivalences
*/

using namespace std;

#include <bits/stdc++.h>


int N, M;
vector<int> visited, vertices_visit_order;
vector<vector<int>> AL, AL_T;

void dfs_run1 (int u) {
  if (visited[u])
    return;
  visited[u]=-1;
  for (int i=0; i<AL[u].size(); i++) 
    dfs_run1(AL[u][i]);
vertices_visit_order.push_back(u);
}

void dfs_run2 (int n, int num_scc) {
  if (visited[n]!=-1) 
    return;
  visited[n]=num_scc;
  for (int i=0; i<AL_T[n].size(); i++)
    dfs_run2(AL_T[n][i],num_scc);
}

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    cin>>N>>M;
    AL=AL_T=vector<vector<int> >(N);

    for (int i=0; i<M; i++) {
      int u, v;
      cin >> u >> v;
      u--; v--;
      AL[u].push_back(v);
      AL_T[v].push_back(u);
    }

    vertices_visit_order.clear();
    
    int num_scc = 0;
    visited = vector<int>(N,0);
    for (int i = 0; i<N; i++)
        dfs_run1(i);
    for (int i = N-1; i >= 0; i--)
        if (visited[vertices_visit_order[i]] == -1)
            dfs_run2(vertices_visit_order[i], num_scc++);

    if (num_scc == 1) {
      cout << 0 << endl;
      continue;
    }
    
    vector<int> deg_in(num_scc,0), deg_out(num_scc,0);

    for (int u = 0; u < N; u++)
        for (int v: AL[u])
            if (visited[u] != visited[v]) {
                deg_out[visited[u]]++;
                deg_in[visited[v]]++;
        }

    int num_of_zero_in_deg_scc=0, num_of_zero_out_deg_scc=0;
    for (int i=0; i<num_scc; i++) {
      if (deg_in[i] == 0) num_of_zero_in_deg_scc++;
      if (deg_out[i] == 0) num_of_zero_out_deg_scc++;
    }

    cout << max(num_of_zero_in_deg_scc, num_of_zero_out_deg_scc) << endl;
  }
  
  return 0;
}
