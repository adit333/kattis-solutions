/*https://ualberta.kattis.com/sessions/vg7m4t/problems/drivinglanes

We will solve it by Dynamic Programming.

Let f(i, l) = shortest distance to reach the end and end up in lane 0
              when starting from straightway i and lane l.
Therefore, we want f(0, 0)

A few observations:
- The distance to move p lanes in the sam straightway is (k + r)*p
- We can only move to a lane in  a straightway if, k < len of that straightway.
  For example, if we want to move from lane 1 to 4, we can only move if
  k * (4-1) < len of that straightway.
  We will call all such lanes we can reach in a straightway 'attainable'.

Now, we are ready to describe the recursive formula:
Let S = all attainable lanes starting from lane l

f(i, l) = (r * l) + len(straightway i)           // if (i = n-1) [we have reached end]
                                                    and (k * l) <= len(straightway i)
f(i, l) = min(f(i, l),                           // if (i < n-1)
              r * abs(ll-l) + len(straightway i) +              // for ll in S
              curve_strech[curve i] + curve_curvature[curve i] * (ll + 1) +
              f(i+1, ll)
        )

f(i+1, ll) is the min dist to reach end when starting from straightway i+1 and lane ll
To reach that state from our current state, we have to travel a distance of:
    r * abs(ll-l) +                                             // cost for switching lanes
    len(straightway i) +                                        // cost for moving across current straightway
    curve_strech[curve i] + curve_curvature[curve i] * (ll + 1) // cost for moving across curve

That's it! :)*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 260

const ll INF = (1ll<<60);

ll num_of_straight_ways, num_of_lanes, k, r;
ll straightway_lengths[MAX], curve_strech[MAX], curve_curvature[MAX];
ll memo[MAX][MAX];


ll driving_lanes(int i, int l) {
    ll& min_dist = memo[i][l];
    if (memo[i][l] != -1) 
        return memo[i][l];
    
    min_dist = INF;
    if ((i == num_of_straight_ways - 1) && ((k * l) <= straightway_lengths[i])) {
        min_dist = (r * l) + straightway_lengths[i];

    } else if (i < num_of_straight_ways - 1) {
        for (int ll = 0; ll < num_of_lanes; ++ll)
            if (k * abs(ll - l) <= straightway_lengths[i])
                min_dist = min(min_dist,
                            r * abs(ll - l) + straightway_lengths[i] + 
                            curve_curvature[i]*(ll+1) + curve_strech[i] + 
                            driving_lanes(i + 1, ll)
                );
    }
    return min_dist;
}


int main() {
    cin >> num_of_straight_ways >> num_of_lanes >> k >> r;
    for (int i = 0; i < num_of_straight_ways; ++i)
        cin >> straightway_lengths[i];
    for (int i = 0; i < num_of_straight_ways-1; ++i)
        cin >> curve_strech[i] >> curve_curvature[i];

    memset(memo, -1, sizeof(memo));

    cout << driving_lanes(0, 0) << endl;
}
