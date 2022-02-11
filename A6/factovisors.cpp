/* https://ualberta.kattis.com/problems/factovisors
*/
#include <bits/stdc++.h>

using namespace std;

using umii = unordered_map<int, int>;


int legendre(int prime, int n) {                           // Legendre's formula
  int ans = 0;
  for (int prime_to_the_i = prime; prime_to_the_i <= n; prime_to_the_i *= prime)
    ans += n/prime_to_the_i;                                 // floor by default
  return ans;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    int n, m, prime_factor, power;
    while (scanf("%d %d", &n, &m) != EOF) {
        bool m_divides_n_fact = true;
        if (m == 0) {
            m_divides_n_fact = false;
        } else if (m <= n) {
            m_divides_n_fact = true;
        } else {
            umii prime_factors_of_m;
            int temp = m;
            int prime_factor = 2;
            while ((temp > 1) && ((long long)prime_factor*prime_factor <= m)) {
                int freq = 0;
                while (temp%prime_factor == 0) {                   // take out this factor
                ++freq;
                temp /= prime_factor;
                }
                if (freq > 0) prime_factors_of_m[prime_factor] = freq;
                ++prime_factor;                                    // next factor
            }
            if (temp > 1) prime_factors_of_m[temp] = 1;

            // Uncomment this before running, for some reason vs code thinks this is an error
            // for (auto [prime_factor, power] : prime_factors_of_m) {
            //     if (legendre(prime_factor, n) < power) {
            //         m_divides_n_fact = false;
            //         break;
            //     }
            // }
        }
    if (m_divides_n_fact)
        printf("%d %s %d!\n", m, "divides", n);
    else 
        printf("%d %s %d!\n", m,"does not divide", n);
    }
}