/* This class computes the LU factorization of an n * n square matrix
*/

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-4;

class LUFactorizer {
    public:
    LUFactorizer() { }

    bool fit(vector<vector<double>> &A) {
        int n = A.size();
        for (int k = 0; k < n-1; ++k) {         // Loop over columns
            if (A[k][k] == 0)                   // Pivot is zero
                return false;
            
            for (int i = k+1; i < n; ++i)
                A[i][k] = A[i][k] / A[k][k];    // Compute the multiplier

            for (int j = k+1; j < n; ++j)
                for (int i = k+1; i < n; ++i)   // Apply transformation to the remaining sub-matrix
                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
        }
        return true;
    }

    bool solve_for_b(vector<vector<double>> &A, vector<double> &b, vector<double> &x) {
        int n = A.size();
        vector<double> y(n, 0);
        forward_substitution(A, b, y);          // Solve Ly = b by forward substitution
        backward_substitution(A, y, x);         // Solve Ux = y by backward substitution
        return true;
    }

    double determinant(vector<vector<double>> &A) {
        double det = 1;
        int n = A.size();
        for (int i = 0; i < n; ++i)
            det *= A[i][i];
        return det;
    }

    void print_lu(vector<vector<double>> &A) {
        int n = A.size();

        // Print L
        cout << "L:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    cout << 1 << "    ";
                else if (i < j)
                    cout << 0 << "    ";
                else
                    cout << A[i][j] << "    ";
            }
            cout << endl;
        }

        // Print U
        cout << "U:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i > j)
                    cout << 0 << "    ";
                else
                    cout << A[i][j] << "    ";
            }
            cout << endl;
        }
    }

    void print_vector(vector<double> &x) {
        for (int i = 0; i < x.size(); ++i)
            cout << x[i] << "  ";
        cout << endl;
    }

    private:
    bool forward_substitution(vector<vector<double>> &A, vector<double> &b, vector<double> &y) {
        int n = A.size();
        for (int j = 0; j < n; ++j) {       // Loop over the columns
            // Compute the solution component.
            // This is always divided by 1 as diagnols of L are 1
            y[j] = b[j];

            for (int i = j+1; i < n; ++i)   // Update the RHS
                b[i] = b[i] - A[i][j] * y[j];
        }
        return true;
    }

    bool backward_substitution(vector<vector<double>> &A, vector<double> &y, vector<double> &x) {
        int n = A.size();

        for (int j = n-1; j >=0; --j) {     // Loop backward over columns
            x[j] = y[j] / A[j][j];          // Compute the solution component

            for (int i = 0; i < j; ++i)   // Update RHS
                y[i] = y[i] - A[i][j] * x[j];
        }
        return true;
    }
};

bool approximatelyEqual(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
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
            if (fabs(A[i][j] - B[i][j]) > EPS) {
                double k = abs(A[i][j] - B[i][j]);
                cout << "Not the same matrix." << i << j << endl;
                return false;
            }
        }
    }
    return true;
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
    return true;
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
    vector<vector<double>> A2 = {{1, 2, 2}, {4, 4, 2}, {4, 6, 4}};
    vector<vector<double>> A_expected2 = {{1, 2, 2}, {4, -4, -6}, {4, 0.5, -1}};
    luf.fit(A2);
    assert(assert_same_matrix(A2, A_expected2) == true);

    vector<double> b2 = {3, 6, 10};
    vector<double> x2(3);
    vector<double> expected_x2 = {-1, 3, -1};
    luf.solve_for_b(A2, b2, x2);
    assert(assert_same_vector(x2, expected_x2) == true);

    // Test case 3: 3 x 3 identity matrix
    vector<vector<double>> A3 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<vector<double>> A_expected3 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    luf.fit(A3);
    assert(assert_same_matrix(A3, A_expected3) == true);

    vector<double> b3 = {3, 6, 10};
    vector<double> x3(3);
    vector<double> expected_x3 = {3, 6, 10};
    luf.solve_for_b(A3, b3, x3);
    assert(assert_same_vector(x3, expected_x3) == true);


    // Test case 4: 5 x 5 matrix
    vector<vector<double>> A4 = {{8, 8, 9, 5, 5}, {8, 1, 7, 4, 5}, {4, 3, 4, 8, 7},
                                {7, 1, 10, 8, 8}, {2, 1, 1, 2, 8}};
    vector<vector<double>> A_expected4 = {{8, 8, 9, 5, 5}, {1, -7, -2, -1, 0},
                                         {0.5, 0.142857142857, -0.214285714, 5.642857, 4.5},
                                         {0.8750, 0.8571428571, -17.9167, 105.5833, 84.25},
                                         {0.25, 0.142857142857, 4.5, -0.2320, 6.0497}};
    luf.fit(A4);
    assert(assert_same_matrix(A4, A_expected4) == true);

    vector<double> b4 = {3, 7, 7, 2, 2};
    vector<double> x4(5);
    vector<double> expected_x4 = {2.3037, -0.1555, -1.9833, 1.0552, -0.3224};
    luf.solve_for_b(A4, b4, x4);
    assert(assert_same_vector(x4, expected_x4) == true);

    cout << "Tests for nonsingular matrices passed!" << endl;
}

void test_singular_matrices() {
    LUFactorizer luf;
    // Test case 1: 3 x 3 matrix
    vector<vector<double>> A = {{1, 2, 2}, {1, 2, 2}, {4, 4, 2}};
    assert(luf.fit(A) == false);
    cout << "Tests for singular matrices passed!" << endl;
}

void test_rectangular_matrices() {
    LUFactorizer luf;
    // Test case 1: 3 x 3 matrix
    vector<vector<double>> A = {{1, 2, 2}, {4, 4, 2}, {4, 9, 2}, {2, 4, 2}};
    bool result = luf.fit(A);
    assert(result == false);
}

int main() {
    test_nonsingular_square_matrices();
    test_singular_matrices();
    //test_rectangular_matrices();    
}
