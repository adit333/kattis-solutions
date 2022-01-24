/*https://ualberta.kattis.com/sessions/zy3te5/problems/classpicture
*/


#include <bits/stdc++.h>

using namespace std;

bool works(vector<int>& permutation, vector<vector<bool>>& conflicts) {
    for(int i = 1; i < permutation.size(); i++)
        if(conflicts[permutation[i-1]][permutation[i]])
            return false;
    return true;
}

void class_picture(vector<string>& names, vector<vector<bool>>& conflicts) {
  vector<int> permutation;
  for(int i = 0; i < names.size(); i++) {
      permutation.push_back(i);
  }

  do {
      if(works(permutation, conflicts)) {
        for(int i : permutation) 
          cout << names[i] << " ";
        cout << endl;
        return;
      }
  } while(next_permutation(permutation.begin(), permutation.end()));

  cout << "You all need therapy." << endl;
}

int main() {
  int n;
  while (cin >> n) {
    vector<string> names;
    for(int i = 0; i < n; i++) {
      string s;
      cin >> s;
      names.push_back(s);
    }
    sort(names.begin(), names.end());

    vector<vector<bool>> conflicts;
    conflicts.resize(n, vector<bool>(n, false));

    int m;
    cin >> m;
    while(m--) {
      string s1, s2;
      cin >> s1 >> s2;
      int index1 = find(names.begin(), names.end(), s1) - names.begin();
      int index2 = find(names.begin(), names.end(), s2) - names.begin();
      conflicts[index1][index2] = true;
      conflicts[index2][index1] = true;
    }
    class_picture(names, conflicts);
  }
}
