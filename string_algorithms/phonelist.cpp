/*
Kattis example - phonelist

Idea: Use a Trie

Insert the words one at a time. When inserting str, if
we ever traverse a Trie node that ends
a previously-inserted word, then it is a prefix of str.

Finally, when we are done inserting str, check if
it is a leaf node. If not, then it is a prefix of a previously-inserted word.

Running time: linear in the total number of characters of the words.
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode {
  bool end;
  unordered_map<char, TrieNode*> ch;

  TrieNode() : end(false) {}
  ~TrieNode() { for (auto p : ch) delete p.second; }
};

bool addWord(const string& str, TrieNode* node) {
    // ok: indicates no string already stored is a prefix of the new string s
    bool ok = !(node->end);

    for (char c : str) {
    if (node->ch.find(c) == node->ch.end())
        node->ch[c] = new TrieNode;

        node = node->ch[c];
        if (node->end)
            ok = false;
    }

    // this node ends the string str
    node->end = true;

    // finally, also check that this is a leaf node (i.e. no children)
    return ok && (node->ch.size() == 0);
}

void solve() {
    bool ok = true;
    TrieNode root;

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        if (!addWord(s, &root))
            ok = false;
    }

    cout << (ok ? "YES" : "NO") << endl;
}

int main() {
    int cases;
    cin >> cases;
    while (cases--)
        solve();
}