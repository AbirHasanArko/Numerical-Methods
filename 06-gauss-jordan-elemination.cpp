#include <bits/stdc++.h>
using namespace std;

void printMatrix(const vector<vector<double>>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(10) << fixed << setprecision(4) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of unknowns: ";
    cin >> n;

    vector<vector<double>> a(n, vector<double>(n + 1));

    cout << "Enter coefficients of the augmented matrix (A|B):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    // Gauss–Jordan Elimination
    for (int i = 0; i < n; i++) {
        // Step 1: Make diagonal element 1
        if (a[i][i] == 0) {
            cout << "Mathematical Error: Zero pivot element!\n";
            return 0;
        }

        double diag = a[i][i];
        for (int j = 0; j <= n; j++) {
            a[i][j] /= diag;
        }

        // Step 2: Make other elements in column 0
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double ratio = a[k][i];

                for (int j = 0; j <= n; j++) {
                    a[k][j] -= ratio * a[i][j];
                }
            }
        }

        // Print Intermediate Matrix
        cout << "After operating on row " << i+1 << "\n";
        printMatrix(a);
    }

    cout << "Final Solutions:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << a[i][n] << endl;
    }
    
    return 0;
}