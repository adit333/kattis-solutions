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
            switch (ch) {
                case '<':
                    if (iter != result.begin())
                        iter = result.erase(--iter);
                    break;
                case '[':
                    iter = result.begin();
                    break;
                case ']':
                    iter = result.end();
                    break;
                default:
                    iter = result.insert(iter, ch);
                    iter++;
                    break;
            }
        }
        for (char ch : result)
            cout << ch;
        cout << endl;
    }
}
