/*
Kattis solution - String Hashing

See CP4-2 pg 359

Idea: Use a rolling hash. See the eClass notes
for a longer discussion as to why this works.

This is implementing exactly this approach.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

// Yes, gcc has 128-bit integers as of C++11. But you can't cin or cout them.
using ulll = __uint128_t;
using ull = uint64_t;

const ulll X = 8675309;     // our "random" X, it usually suffices to pick one
const ull P = 9223372036854775783; // a large prime

// ipython: pow(X, P-2, P) to compute the inverse of X mod P
// uses Fermat's little theorem: X^{P-1} == 1 mod P, so X^{P-2} is the inverse
const ulll INV_X = 8261199684264045559;

int main() {
  // make sure our choice of X and INV_X are correct
    assert((X*INV_X)%P == 1);

    string str;
    cin >> str;

    // compute the polynomial for the various prefixes iteratively
    // (and the various powers of x and inv_x)
    vector<ulll> poly(1, 0), xp(1, 1), inv_xp(1, 1);
    for (char c : str) {
        poly.push_back((poly.back() + xp.back()*c) % P);
        xp.push_back((xp.back() * X) % P);
        inv_xp.push_back((inv_xp.back() * INV_X) % P);
    }
    // now poly[i] is the hash for the substring s[0..i-1]


    // finally, answer the queries
    int q, l, r;
    cin >> q;
    while (q--) {
        cin >> l >> r;

        // P is added so the term does not go negative
        cout << ull(((P + poly[r] - poly[l])*inv_xp[l]) % P) << endl;
    }

    return 0;
}