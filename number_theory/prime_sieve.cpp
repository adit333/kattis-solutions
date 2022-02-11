/*
  Kattis solution - primesieve

  Idea:
  Just use a plain sieve, it is fast enough.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q, num_of_primes = 0;
  cin >> n >> q;

  // we don't need to record prime divisors of each number,
  // so we just "cross out" the composite numbers

  vector<bool> is_prime(n+1, true);
  is_prime[0] = is_prime[1] = false;
  for(int i = 2; i <= n; ++i)
    if (is_prime[i]) {
      ++num_of_primes;
      for (int j = 2*i; j <= n; j += i)
        is_prime[j] = false;
    }

  cout << num_of_primes << endl;
  while (q--) {
    int x;
    cin >> x;
    cout << is_prime[x] << endl; // bools are output as 0 or 1
  }
  return 0;
}