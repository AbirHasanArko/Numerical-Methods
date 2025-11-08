#include <bits/stdc++.h>
using namespace std;

void printMatrix(const vector<vector<double>> &mat, string name) {
    cout << "\nCurrent state of " << name << " matrix:\n";
    for (auto &row : mat) {
        for (auto val : row)
            cout << setw(10) << fixed << setprecision(4) << val << " ";
        cout << "\n";
    }
    cout << "---------------------------------------------\n";
}

int main() {
    int n;
    cout << "Enter number of unknowns: ";
    cin >> n;

    vector<vector<double>> aug(n, vector<double>(n + 1));
    cout << "Enter the augmented matrix (coefficients + constants):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> aug[i][j];

    // Separate A and b from augmented matrix
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            A[i][j] = aug[i][j];
        b[i] = aug[i][n];
    }

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    cout << "\nPerforming LU Decomposition...\n";

    for (int i = 0; i < n; i++) {
        // Upper Triangular Matrix U
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        // Lower Triangular Matrix L
        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1; // diagonal element 1
            else {
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum += L[k][j] * U[j][i];

                if (fabs(U[i][i]) < 1e-9) {
                    cout << "\nZero pivot encountered — system may have no or infinite solutions.\n";
                    return 0;
                }

                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }

        printMatrix(L, "L");
        printMatrix(U, "U");
    }

    // Check determinant (product of diagonal of U)
    double detU = 1;
    for (int i = 0; i < n; i++)
        detU *= U[i][i];

    if (fabs(detU) < 1e-9) {
        cout << "\nDeterminant = 0 → No unique solution (infinite or none).\n";
        return 0;
    }

    cout << "\nLU Decomposition completed successfully!\n";
    printMatrix(L, "Final L");
    printMatrix(U, "Final U");

    // Forward substitution to solve L*y = b
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }

    cout << "\nForward Substitution (L*y = b):\n";
    for (int i = 0; i < n; i++)
        cout << "y" << i + 1 << " = " << y[i] << "\n";

    // Back substitution to solve U*x = y
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }

    cout << "\nBack Substitution (U*x = y):\n";
    cout << "Solution Vector (x):\n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << x[i] << "\n";

    return 0;
}

