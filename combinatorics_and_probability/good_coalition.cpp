/*
  Kattis solution: goodcoalition

  Idea: DP

  Let f(i,j) be the maximum possible probability some coalition of size j
  survives that is formed using only parties 0, ..., i

  Either party i is in such a coalition, or it is not. So the recurrence is:

  f(i,j) = max(f(i-1, j), f(i-1, j - size[i]) * prob[i])
  where size[i] is the size of party i and prob[i] is the probability they
  stay in the coalition.

  The base case of "no coalitions" is i == -1, so the probability is 1.0 (100%)
  if j == 0, otherwise it is 0.0.
*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// dp[i][j] is the maximum probability of a coalition of size j
// surviving using only parties from 0, ..., i
vector<vector<double>> dp;
vector<int> party_size, prob;

double max_probability(int parties, int seats) {
  if (seats < 0)
    return 0.0; // can't form a coalition with negative members

  if (parties < 0) {
    // no parties
    return seats == 0; // returns 1.0 if j == 0, 0.0 if j != 0
  }

  if (dp[parties][seats] < -0.5) { // if not computed yet
    dp[parties][seats] = max(max_probability(parties-1, seats), 
        max_probability(parties-1, seats-party_size[parties])*(prob[parties]*0.01));
  }

  return dp[parties][seats];
}

double solve() {
  int n;
  cin >> n;
  dp.assign(n, vector<double>(151, -1.0));
  party_size.resize(n);
  prob.resize(n);

  for (int i = 0; i < n; ++i)
    cin >> party_size[i] >> prob[i];

  double best = 0.0;
  for (int j = 76; j <= 150; ++j)
    best = max(best, max_probability(n-1, j));

  return best*100;
}

int main() {
  cout.setf(ios::fixed);
  cout.precision(10);

  int t;
  cin >> t;

  for (int i = 0; i < t; ++i)
    cout << solve() << endl;
}