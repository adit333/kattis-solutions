/*
  Kattis example: hnumbers

  Idea:
  First modify a sieve to identify all h-primes and h-composites.
  Note an h-prime divisor of each h-composite.

  Then for each h-composite n that is divisible by an hprime p,
  check if h/p is an h-prime (to see if h is the product of exactly
  two primes).
*/

#include <bits/stdc++.h>

const int MAXN = 1000001;

using namespace std;

int main() {
  vector<int> pdiv(MAXN+1), semihp_nums(MAXN+1);
  iota(pdiv.begin(), pdiv.end(), 0);

  semihp_nums[1] = 0;
  // iterate from 5 upwards over numbers that are 1 mod 4
  for (int i = 5; i < MAXN; i += 4) {
      // if this is a semi-hprime (we haven't marked it off yet)
      if (pdiv[i] == i)
          // mark off all multiples that are 1 mod 4 and note they
          // are h-composite with i as an h-prime divisor
          for (int j = 5*i; j < MAXN; j += 4*i)
              pdiv[j] = i;

      // get all h-semi-primes < i
      semihp_nums[i] = semihp_nums[i-4];

      // then check if is is an h-semi-prime:
      // it cannot be an h-prime (i.e. i != pdiv[i])
      // but i/pdiv[i] must be an h-prime
      if (i != pdiv[i] && pdiv[i/pdiv[i]] == i/pdiv[i]) ++semihp_nums[i];
  }

  // read in the queries one at a time until you see 0
  // simply print the output!
  int n;
  while ((cin >> n) && n) cout << n << ' ' << semihp_nums[n] << endl;

  return 0;
}