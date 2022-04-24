"""https://ualberta.kattis.com/sessions/vk6fb6/problems/bing

Approach: Use a Trie.
    During every insertion record the no. of words below the node.
    Simply print no. of words below after insertion is done.
"""

import sys
from typing import List


class vertex:
  def __init__(self, chr: str):
    self.alphabet = chr
    self.exist = False
    self.child = [None] * 26
    self.num_words_below = 0

class Trie:
    def __init__(self):
        self.root = vertex('!')

    def insert(self, word):
        cur = self.root
        for w in word:
            alphaNum = ord(w)-ord('a')
            if cur.child[alphaNum] == None:
                cur.child[alphaNum] = vertex(w)
            cur = cur.child[alphaNum]
            cur.num_words_below += 1
        cur.exist = True
        return cur.num_words_below - 1


def bing_it_on(words: List[str]) -> None:
    T = Trie()
    for word in words:
        print(T.insert(word))


def main():
    input_lines = sys.stdin.read().splitlines()
    bing_it_on(input_lines[1:])


if __name__ == '__main__':
    main()
