
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, num_of_queries;
    cin >> N >> num_of_queries;

    int sqrt_n = sqrt(N) + 1;

    vector<vector<int>> bucket(sqrt_n+1, vector<int>(N+1, 0));
    vector<int> array(N+1);

    for (int i = 0; i < num_of_queries; ++i) {
        int query_type, A, B, C, D;
        cin >> query_type;

        if (query_type == 1) {
            cin >> A >> B >> C;
            if (B <= sqrt_n)
                bucket[B][A] += C;
            else 
                for (int j = A; j < N + 1; j += B)
                    array[j] += C;
        } else if (query_type == 2) {
            cin >> D;
            long long result = array[D];
            for (int B = 1; B < sqrt_n + 1; ++B) {
                int z = bucket[B][D%B];
                result += z;
            }
            cout << result << endl;
        }
    }
}
