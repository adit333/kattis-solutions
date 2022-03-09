/* https://ualberta.kattis.com/sessions/vk6fb6/problems/typo

Approach:
Compute word hash: X^0 * s[0] + X^1 * s[1] + ... + X^n * s[n] for all words
Then, for each word, try delete a letter and check if resultant hash is present
*/

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll X = 130941;      // Just a random number
ll X_INV = 111699163;
ll MOD = 1e9+7;

ll compute_word_hash(string word) {
    ll hash = 0;
    // Horner's Rule
    for (int i = word.size()-1; i > -1; --i) {
        char letter = word[i];
        hash = letter + (X * hash);
        hash %= MOD;
    }
    return hash;
}

void compute_word_hashes(vector<string>& words, unordered_map<string, ll>& word_to_hash,
        unordered_map<ll, vector<ll>>& hash_to_words) {
    for (int i = 0; i < words.size(); ++i)         {
        ll hash = compute_word_hash(words[i]);
        word_to_hash[words[i]] = hash;
        hash_to_words[hash].push_back(i);
    }
}

bool is_present(ll hash_without_letter, string word_without_letter,
        unordered_map<ll, vector<ll>>& hash_to_words, vector<string>& words) {
    if (hash_to_words.find(hash_without_letter) == hash_to_words.end())
        return false;
    
    for (int word_index : hash_to_words[hash_without_letter]) {
        if (word_without_letter == words[word_index])
            return true;
    }
    return false;
}

void typo(vector<string>& words) {
    unordered_map<string, ll> word_to_hash;
    unordered_map<ll, vector<ll>> hash_to_words;

    compute_word_hashes(words, word_to_hash, hash_to_words);
    bool typos = false;

    for (string word: words) {
        ll word_hash = word_to_hash[word];
        ll partial_hash = 0;
        ll X_power = 1;

        for (int i = 0; i < word.size(); ++i) {
            char letter = word[i];

            // e.g. if i=2, next_partial_hash = partial_hash + X^2 * s[2]
            ll next_partial_hash = partial_hash + (letter * X_power);
            next_partial_hash %= MOD;

            // hash_without_letter = X^3 * s[3] + ... + X^n * s[n]
            ll hash_without_letter = (word_hash - next_partial_hash + MOD) % MOD;
            // hash_without_letter = X^2 * s[3] + ... + X^n-1 * s[n]
            hash_without_letter *= X_INV;
            // hash_without_letter = X^0 * s[0] + X^1 * s[1] + X^2 * s[3] + ... + X^n-1 * s[n]
            hash_without_letter += partial_hash;
            hash_without_letter %= MOD;

            string word_without_letter = word.substr(0, i) + word.substr(i+1, word.length());
            if (is_present(hash_without_letter, word_without_letter, hash_to_words, words)) {
                cout << word << endl;
                typos = true;
                break;
            }

            partial_hash = next_partial_hash;
            X_power = (X_power * X) % MOD;
        }
    }
    if (!typos) {
        cout << "NO TYPOS" << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<string> words;

    words.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> words[i];
    typo(words);

}
