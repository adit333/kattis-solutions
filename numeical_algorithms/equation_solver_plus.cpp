/*
  Kattis example: equationsolverplus
  https://ualberta.kattis.com/sessions/wuuqfx/problems/equationsolverplus

  Idea: Just use row reduction to reduce the augmented matrix representing the
  system of equations to RREF. Read off the answer like you were taught
  in basic linear algebral.

  Running time: O(m * n^2) where m = # equations, n = # variables
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
const double EPS = 1e-8;
using vd = vector<double>;
using vvd = vector<vd>;

// Reduces m to RREF
// Assumes all rows have the same length.
void rref(vvd& m) {
  int nr = m.size(), nc = m[0].size();

  for (int r = 0, c = 0; c < nc; ++c) {
    // Find a row to pivot on, choose the one with smallest absolute value for the pivot entry
    int p = -1;
    for (int i = r; i < nr; ++i)
      if (fabs(m[i][c]) > EPS && (p == -1 || fabs(m[i][c]) < fabs(m[p][c])))
        p = i;

    if (p == -1) continue; // no pivot for this column

    // swap the pivot row into row r
    swap(m[p], m[r]);

    // normalize pivot row (now at row r) so the leading coefficient is 1
    for (int tc = nc-1; tc >= c; --tc) m[r][tc] /= m[r][c];

    // use row operations to clear all remaining nonzeros in this column
    for (int tr = 0; tr < nr; ++tr) {
      if (tr == r || fabs(m[tr][c]) < EPS) continue; // don't bother if it is already 0
      for (int tc = nc-1; tc >= c; --tc)
        m[tr][tc] -= m[r][tc]*m[tr][c];
    }

    ++r;
  }
}

int main() {
  int n;
  cout.setf(ios::fixed);
  cout.precision(10);
  while (true) {
    cin >> n;
    if (n == 0) break;

    // read in the matrix "m"
    vvd m(n, vd(n+1));
    for (auto& row : m)
      for (int i = 0; i < n; ++i)
        cin >> row[i];
    for (int i = 0; i < n; ++i)
      cin >> m[i][n];

    // reduce it to RREF
    rref(m);

    // the value a variable should take
    vd x(n);

    // flags if the variable depends on a free variable or not
    // assumes it is dependent on a free variable (unless proven otherwise)
    vector<bool> determined(n, false);

    // flags that we have not seen an inconsistent system
    bool consistent = true;

    // scan each row
    for (int i = 0; i < n; ++i) {

      // find the leading 1
      int j = 0;
      while (j <= n && fabs(m[i][j]) < EPS) ++j;

      // if no leading 1, the row is a zero row so we are done scanning the RREF matrix
      if (j > n) break;

      // if the leading 1 is in the final column, the system is inconsistent
      if (j == n) {
        consistent = false;
        break;
      }

      // check all columns after j but before the final column
      // if any are nonzero, j depends on a free variable
      determined[j] = true;
      for (int jj = j+1; jj < n; ++jj)
        determined[j] = determined[j]&&(fabs(m[i][jj]) < EPS);

      // if j does not depend on a free variable, record its value
      if (determined[j]) x[j] = m[i][n];

    }

    if (!consistent) {
      cout << "inconsistent" << endl;
    }
    else {
      for (int i = 0; i < n; ++i) {
        if (determined[i]) cout << x[i];
        else cout << '?';
        cout << (i+1==n?'\n':' ');
      }
    }
  }


  return 0;
}