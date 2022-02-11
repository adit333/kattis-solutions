/*
  Kattis solution - divisors
  Zachary Friggstad, 2022
  For CMPUT 403

  Idea:
  n is small enough that we can completely factor n! by simply factoring
    2, 3, 4, 5, 6, ..., n-1, n
  using simple trial division.

  Using this, we can compute the complete factorization of
    (n choose k) = n! / (k! * (n-k)!)
  That is, for each prime p count the number of times it divides
  n!, then subtract the number of times it divides k! and (n-k)!

  Finally recall the number of divisors of a number
    X = p1^(a1) * p2^(a2) * ... * pk^(ak)
  is
    (a1 + 1) * (a2 + 1) * ... * (ak + 1)

  Running time: O(n^{1.5}).

  Can improve to O(n * loglog n) by using a sieve and the "tip" from the slides.
    - That is, get all primes <= n using a sieve in O(n * loglog n) time.
    - Then for each prime p figure out how many times it divides the
    numerator and denominator in O(log_p n) time (worst case, O(log n)).
    - Since there are only O(n / log n) primes at most n, the logarithms cancel
      so the work done after the sieve takes O(n) time.
*/

#include <bits/stdc++.h>

using namespace std;

using umii = unordered_map<int, int>;

// factor n and accumulate the prime divisors in the map
// we do not reset the map because we actually want to build
// it up in the function factorfact
// running time: O(sqrt n)
void factor(int n, umii& f) {
  for (int i = 2; i*i <= n; ++i) {
    while (n%i == 0) {
      ++f[i];
      n /= i;
    }
  }
  if (n > 1) ++f[n];
}

// get the complete factorization of n! (n factorial)
// running time: O(n^{1.5}) (O(n) calls to factor)
umii factorfact(int n) {
  umii f;

  // factor each value from 2 to n and accumulate them
  // in the map
  for (int i = 2; i <= n; ++i) factor(i, f);

  return f;
}

int main() {
  int n, k, p;
  while (cin >> n >> k) {
    // get the complete factoriations of n!, k!, and (n-k)!
    umii num = factorfact(n);
    umii den1 = factorfact(k);
    umii den2 = factorfact(n-k);

    // the number of times a prime p divides (n choose k)
    // is the the number of times it divides n!, minus the total number of times
    // it divides k! and (n-k)!

    long long ans = 1;
    for(auto [p, k] : num) ans *= (k - den1[p] - den2[p] + 1);

    cout << ans << endl;
  }

  return 0;
}