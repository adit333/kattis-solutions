/* https://ualberta.kattis.com/sessions/wuuqfx/problems/kinversions
*/


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

const ld  pi   = 4.0*atanl(1.0);
const int iinf = 1e9 + 10;
const ll  inf  = 1e18 + 10;
const int mod  = 1000000007;
const ld  prec = .000001;

#define enld endl
#define endl '\n'
#define pb push_back
#define debug(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define rep1(i, n) for (ll i = 1; i <= (ll)(n); ++i)
#define umap unordered_map
#define uset unordered_set

template<class TIn>
using indexed_set = tree<
        TIn, null_type, less<TIn>,
        rb_tree_tag, tree_order_statistics_node_update>;

void nextpow(ll& n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
}

void fft(valarray<complex<double>>& x) {
    ll s = x.size();

    if (s <= 1) {
        return;
    }

    valarray<complex<double>> even = x[slice(0, s/2, 2)];
    valarray<complex<double>> odd  = x[slice(1, s/2, 2)];

    fft(even);
    fft(odd);

    for(ll i = 0; i < s/2; i++) {
        complex<double> t = polar(1.0, -2.0 * M_PI * i / s) * odd[i];
        x[i]     = even[i] + t;
        x[i+s/2] = even[i] - t;
    }
}

void inverse_fft(valarray<complex<double>>& x) {
    x = x.apply(conj);
    fft(x);
    x = x.apply(conj);
    x /= x.size();
}

void k_inversions(string &s) {
    ll size = s.size();
    size++;
    nextpow(size);
    size++;
    nextpow(size);

    valarray<complex<double>> poly1(size);
    valarray<complex<double>> poly2(size);

    for (ll i = 0; i < s.size(); i++) {
        poly1[i] = (s[i] - 'A')^1;
        poly2[size-i-1] = (s[i] - 'A');
    }

    fft(poly1);
    fft(poly2);

    for (ll i = 0; i < size; i++)
        poly1[i] *= poly2[i];
    inverse_fft(poly1);

    for (int i = 0; i < s.size()-1; i++)
        cout << (int)(poly1[i].real()+0.1) << endl;
}


int main() {
  string s;
  cin >> s;

  k_inversions(s);
}
