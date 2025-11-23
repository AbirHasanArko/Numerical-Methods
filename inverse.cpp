#include <bits/stdc++.h>
using namespace std;

double determinant(const vector<vector<double>>& A);
vector<vector<double>> adjoint(const vector<vector<double>>& A);

/* ---------------------------
   Compute inverse by 1/det(A) * adj(A)
----------------------------*/
bool inverseByAdjoint(const vector<vector<double>>& A, vector<vector<double>>& inv) {
    int n = A.size();
    for (auto &r : A)
        if (r.size() != n) return false; // must be square

    double detA = determinant(A);
    if (fabs(detA) < 1e-12) return false; // non-invertible

    vector<vector<double>> adjA = adjoint(A);

    inv.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = adjA[i][j] / detA;

    return true;
}

/* ---------------------------
   Compute determinant using recursion (cofactor expansion)
----------------------------*/
double determinant(const vector<vector<double>>& A) {
    int n = A.size();
    if (n == 1) return A[0][0];

    if (n == 2)
        return A[0][0]*A[1][1] - A[0][1]*A[1][0];

    double det = 0;
    for (int col = 0; col < n; col++) {
        // build minor matrix
        vector<vector<double>> sub(n-1, vector<double>(n-1));
        for (int i = 1; i < n; i++) {
            int c2 = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                sub[i-1][c2++] = A[i][j];
            }
        }
        det += pow(-1, col) * A[0][col] * determinant(sub);
    }
    return det;
}

/* ---------------------------
   Compute adj(A) = transpose of cofactor matrix
----------------------------*/
vector<vector<double>> adjoint(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> adj(n, vector<double>(n));

    if (n == 1) {
        adj[0][0] = 1;
        return adj;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // build minor matrix
            vector<vector<double>> sub(n-1, vector<double>(n-1));
            int r2 = 0;
            for (int r = 0; r < n; r++) {
                if (r == i) continue;
                int c2 = 0;
                for (int c = 0; c < n; c++) {
                    if (c == j) continue;
                    sub[r2][c2++] = A[r][c];
                }
                r2++;
            }

            double cofactor = pow(-1, i + j) * determinant(sub);
            adj[j][i] = cofactor; // transpose while storing
        }
    }

    return adj;
}

/* ---------------------------
   Demo
----------------------------*/
int main() {
    vector<vector<double>> A = {
        {4, 7, 2},
        {3, 6, 1},
        {2, 5, 3}
    };

    vector<vector<double>> inv;
    if (!inverseByAdjoint(A, inv)) {
        cout << "Matrix is singular.\n";
        return 0;
    }

    cout << fixed << setprecision(6);
    cout << "Inverse using adj(A)/det(A):\n";
    for (auto &row : inv) {
        for (double x : row) cout << setw(12) << x;
        cout << "\n";
    }
}
