/* Test for lu_factorization */

#include <bits/stdc++.h>
#include "lu_factorization.h"

using namespace std;

const double EPS = 1e-9;

void test_nonsingular_square_matrices();
void test_singular_matrices();
void test_rectangular_matrices();
bool assert_same_matrix(vector<vector<double>> &A, vector<vector<double>> &B);

int main() {
    test_nonsingular_square_matrices();
    test_singular_matrices();
    //test_rectangular_matrices();    
}

void test_nonsingular_square_matrices() {
    LUFactorizer luf;
    // Test case 1: 2 x 2 matrix
    vector<vector<double>> A = {{4, 4}, {12, 7}};
    vector<vector<double>> A_expected = {{4, 4}, {3, -5}};
    luf.fit(A);
    assert(assert_same_matrix(A, A_expected) == true);

    vector<double> b = {20, 50};
    vector<double> x(2);
    vector<double> expected_x = {3, 2};
    luf.solve_for_b(A, b, x);
    assert(assert_same_vector(x, expected_x) == true);


    // Test case 2: 3 x 3 matrix
    vector<vector<double>> A = {{1, 2, 2}, {4, 4, 2}, {4, 6, 4}};
    vector<vector<double>> A_expected = {{1, 2, 2}, {4, -4, -6}, {4, 0.5, -1}};
    luf.fit(A);
    assert(assert_same_matrix(A, A_expected) == true);

    vector<double> b = {3, 6, 10};
    vector<double> x(3);
    vector<double> expected_x = {-1, 3, -1};
    luf.solve_for_b(A, b, x);
    assert(assert_same_vector(x, expected_x) == true);

    // Test case 3: 3 x 3 identity matrix
    vector<vector<double>> A = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<vector<double>> A_expected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    luf.fit(A);
    assert(assert_same_matrix(A, A_expected) == true);

    vector<double> b = {3, 6, 10};
    vector<double> x(3);
    vector<double> expected_x = {3, 6, 10};
    luf.solve_for_b(A, b, x);
    assert(assert_same_vector(x, expected_x) == true);


    // Test case 4: 5 x 5 matrix
    vector<vector<double>> A = {{8, 8, 9, 5, 5}, {8, 1, 7, 4, 5}, {4, 3, 4, 8, 7},
                                {7, 1, 10, 8, 8}, {2, 1, 1, 2, 8}};
    vector<vector<double>> A_expected = {{8, 8, 9, 5, 5}, {1, -7, -2, -1, 0},
                                         {0.8750, 0.8751, 3.8393, 4.4821, 3.6250},
                                         {0.5, 0.1429, -0.0558, 5.8930, 4.7023},
                                         {0.25, 0.1429, -0.2512, 0.3425, 6.0497}};
    luf.fit(A);
    assert(assert_same_matrix(A, A_expected) == true);

    vector<double> b = {3, 7, 7, 2, 2};
    vector<double> x(5);
    vector<double> expected_x = {2.3037, -0.1555, -1.9833, 1.0552, -0.3224};
    luf.solve_for_b(A, b, x);
    assert(assert_same_vector(x, expected_x) == true);
}

void test_singular_matrices() {
    LUFactorizer luf;
    // Test case 1: 3 x 3 matrix
    vector<vector<double>> A = {{1, 2, 2}, {4, 4, 2}, {4, 4, 2}};
    assert(luf.fit(A) == false);
}

void test_rectangular_matrices() {
    LUFactorizer luf;
    // Test case 1: 3 x 3 matrix
    vector<vector<double>> A = {{1, 2, 2}, {4, 4, 2}, {4, 9, 2}, {2, 4, 2}};
    bool result = luf.fit(A);
    assert(result == false);
}

bool assert_same_matrix(vector<vector<double>> &A, vector<vector<double>> &B) {
    int m1 = A[0].size();
    int n1 = A.size();
    int m2 = B[0].size();
    int n2 = B.size();

    if (m1 != m2 | n1 != n2) {
        cout << "Incompatible dimensions," << endl;
        return false;
    }

    for (int i = 0; i < m1; ++i) {
        for (int j = 0;  j < n1; ++j) {
            if (abs(A[i][j] - B[i][j]) > EPS) {
                cout << "Not the same matrix." << endl;
                return false;
            }
        }
    }  
}

bool assert_same_vector(vector<double> &u, vector<double> &v) {
    int n1 = u.size();
    int n2 = v.size();

    if (n1 != n2) {
        cout << "Incompatible dimensions," << endl;
        return false;
    }

    for (int i = 0; i < n1; ++i) {
        if (abs(u[i] - v[i]) > EPS) {
            cout << "Not the same vector." << endl;
            return false;
        }
    }
}
