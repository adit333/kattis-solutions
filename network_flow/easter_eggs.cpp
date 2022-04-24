/* https://ualberta.kattis.com/sessions/v6p28m/problems/eastereggs

Approach: 
- Binary Search on the distance D.
- Each iteration we ask, is it possible to place eggs such that the distance
    between red eggs and blue eggs is at least D.
- To anwser this question, we construct a bipartite graph with blue on left and red on right;
    there will be an edge between a red and blue vertex is the distance between then is less than D.
- Now, we want the maximum independent subset of this graph (the MIS is where we will place the eggs.)
- If the size of this MIS is greater than or equal to N, then this distance is feasible, and the answer
    to the decision problem is yes. Since we want as high a distance as possible, we shift our search
    direction to the right, else to the left.
- For a bipartite graph, the size of the MIS is the same as the size of the complement of
    Min Vertex Cover, whch is the sizeof the matching.
*/

#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

ld EPS = 1e-9;

bool match(int curr, vector<vector<int>>& adj, vector<int>& l, vector<int>& r, vector<int>& vis) {
    if(vis[curr]) return false;
    vis[curr] = true;

    for(auto next : adj[curr]) {
        if(r[next] == -1 || match(r[next], adj, l, r, vis)) {
            l[curr] = next;
            r[next] = curr;
            return true;
        }
    }
    return false;
}

int bipartite_graph_matching(vector<vector<int>>& adj, int n, int m) {
    vector<int> l, r, vis;
    l.resize(n, -1);
    r.resize(m, -1);
    vis.resize(n);

    bool works = true;
    while(works) {
        works = false;
        fill(vis.begin(), vis.end(), 0);
        for(int i = 0; i < n; i++) {
            if(l[i] == -1) {
                works |= match(i, adj, l, r, vis);
            }
        }
    }

    int ret = 0;
    for(int i = 0; i < n; i++) {
        ret += (l[i] != -1);
    }
    return ret;
}

ld get_dist(pair<ld,ld> p1, pair<ld,ld> p2) {
    ld d1 = pow(p1.first-p2.first,2);
    ld d2 = pow(p1.second-p2.second,2);
    return sqrt(d1+d2);
}


bool is_possible_to_place_red_and_blue_eggs_dist_apart(int num_of_eggs_to_hide, int num_of_blue_bushes, int num_of_red_bushes,
        vector<vector<ld>> dist_btw_points, ld dist) {
    vvi bipartite_graph(num_of_blue_bushes);
    for (int i = 0; i < num_of_blue_bushes; ++i)
        for (int j = 0; j < num_of_red_bushes; ++j)
            if (dist_btw_points[i][j] < dist) {
                bipartite_graph[i].push_back(j);

    int size_of_mathcing = bipartite_graph_matching(bipartite_graph, num_of_blue_bushes, num_of_red_bushes);
    int size_of_max_independent_set = num_of_blue_bushes + num_of_red_bushes - size_of_mathcing;
    return size_of_max_independent_set >= num_of_eggs_to_hide;  
}


void easter_eggs(int num_of_eggs_to_hide, int num_of_blue_bushes, int num_of_red_bushes,
        vector<pair<ld,ld>> &blue_bushes, vector<pair<ld,ld>> &red_bushes) {
    vector<vector<ld>> dist_btw_points(num_of_blue_bushes, vector<ld>(num_of_red_bushes));
    for (int i = 0; i < num_of_blue_bushes; ++i)
        for (int j = 0; j < num_of_red_bushes; ++j)
            dist_btw_points[i][j] = get_dist(blue_bushes[i], red_bushes[j]);

    ld low = 0;
    ld high = 1e19;
    while (high - low > EPS) {
        ld mid = low + ((high - low) / 2);
        if (is_possible_to_place_red_and_blue_eggs_dist_apart(num_of_eggs_to_hide,
                num_of_blue_bushes, num_of_red_bushes, dist_btw_points, mid))
            low = mid;
        else
            high = mid;
    }
    cout << fixed;
    cout.precision(8);
    cout << low << endl;
}

int main() {
    int num_of_eggs_to_hide, num_of_blue_bushes, num_of_red_bushes;
    cin >> num_of_eggs_to_hide >> num_of_blue_bushes >> num_of_red_bushes;

    vector<pair<ld,ld>> blue_bushes(num_of_blue_bushes);
    vector<pair<ld,ld>> red_bushes(num_of_red_bushes);

    for (auto& i : blue_bushes)
        cin >> i.first >> i.second;

    for (auto& i : red_bushes)
        cin >> i.first >> i.second;

    easter_eggs(num_of_eggs_to_hide, num_of_blue_bushes, num_of_red_bushes,
        blue_bushes, red_bushes);
}
