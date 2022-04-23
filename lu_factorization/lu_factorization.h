#ifndef LU_FACTORIZER_H
#define LU_FACTORIZER_H

#include <bits/stdc++.h>

using namespace std;

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

#endif  // LU_FACTORIZER_H