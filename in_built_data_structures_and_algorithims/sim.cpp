/* https://ualberta.kattis.com/sessions/jot9wq/problems/sim
*/

#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    int num_of_test_cases;
    cin >> num_of_test_cases;
    cin.ignore();

    while (num_of_test_cases--) {
        string input;
        list<char> result;
        getline(std::cin, input);

        list<char>::iterator iter = result.begin();
        for (char ch : input) {
            if (ch == '<') {
                if (iter != result.begin())
                    iter = result.erase(--iter);
            } else if (ch =='[') {
                iter = result.begin();
            } else if (ch == ']') {
                 iter = result.end();
            } else {
                iter = result.insert(iter, ch);
                iter++;
            }
        }
        for (char ch : result)
            cout << ch;
        cout << endl;
    }
}
