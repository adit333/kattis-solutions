"""https://ualberta.kattis.com/sessions/vk6fb6/problems/typo

Approach:
Compute word hash: X^0 * s[0] + X^1 * s[1] + ... + X^n * s[n] for all words
Then, for each word, try delete a letter and check if resultant hash is present
"""

import sys
from typing import Dict, List

X = 130941      # Just a random number
X_INV = None
MOD = 10**9+7


def compute_word_hash(word: str) -> int:
    hash = 0
    # Honer's Rule
    for i in range(len(word)-1, -1, -1):
        hash = ord(word[i]) + (X * hash)
        hash = hash % MOD
    return hash


def compute_word_hashes(words: List[str], word_to_hash: Dict[str, int],
        hash_to_words: Dict[int, List[int]]) -> None:
    for i, word in enumerate(words):
        hash = compute_word_hash(word)
        word_to_hash[word] = hash
        if hash in hash_to_words:
            hash_to_words[hash].append(i)
        else:
            hash_to_words[hash] = [i]


def is_present(hash_without_letter: int, word_without_letter: str,
        hash_to_words: Dict[int, List[int]], words: List[str]) -> False:
    if hash_without_letter not in hash_to_words:
        return False

    for word_index in hash_to_words[hash_without_letter]:
        if word_without_letter == words[word_index]:
            return True

    return False


def typo(words: List[str]) -> None:
    word_to_hash = {}       # Dict of {'word': hash}
    hash_to_words = {}      # Dict of {hash: [word_indicies]}
    compute_word_hashes(words, word_to_hash, hash_to_words)
    typos = False

    for word in words:
        word_hash = word_to_hash[word]
        partial_hash = 0    # This will contain the hash val of all the letters we have processes so far
                            # e.g. if i=2 next below, it means i=0 and i=1 have been processed.
                            # partial_hash = X^0 * s[0] + X^1 * s[1]
        X_power = 1     # Contains X^i after iteration i of the below loop

        # Now we try delete each letter one at a time
        for i, letter in enumerate(word):
            # e.g. if i=2, next_partial_hash = partial_hash + X^2 * s[2]
            next_partial_hash = partial_hash + (ord(letter) * X_power)
            next_partial_hash %= MOD

            # hash_without_letter = X^3 * s[3] + ... + X^n * s[n]
            hash_without_letter = (word_hash - next_partial_hash + MOD) % MOD
            # hash_without_letter = X^2 * s[3] + ... + X^n-1 * s[n]
            hash_without_letter *= X_INV
            # hash_without_letter = X^0 * s[0] + X^1 * s[1] + X^2 * s[3] + ... + X^n-1 * s[n]
            hash_without_letter += partial_hash
            hash_without_letter %= MOD

            word_without_letter = word[:i] + word[i+1:]
            if is_present(hash_without_letter, word_without_letter, hash_to_words, words):
                print(word)
                typos = True
                break

            partial_hash = next_partial_hash
            X_power = (X_power * X) % MOD

    if not typos:
        print("NO TYPOS")

def main():
    global X, X_INV
    X_INV = pow(X, -1, MOD)

    input_lines = sys.stdin.read().splitlines()
    words = input_lines[1:]
    typo(words)

if __name__ == '__main__':
    main()
