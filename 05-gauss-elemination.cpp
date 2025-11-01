#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of unknowns: ";
    cin >> n;

    vector<vector<double>> a(n, vector<double>(n + 1));
    vector<double> x(n);

    cout << "Enter the augmented matrix (coefficients + constants):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> a[i][j];

    cout << fixed << setprecision(6);

    // Forward Elimination
    for (int i = 0; i < n - 1; i++)
    {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(a[k][i]) > fabs(a[maxRow][i]))
                maxRow = k;
        swap(a[i], a[maxRow]); // <-- safe swap for vectors

        // Elimination
        for (int k = i + 1; k < n; k++)
        {
            double factor = a[k][i] / a[i][i];
            for (int j = i; j <= n; j++)
                a[k][j] -= factor * a[i][j];
        }

        // Print intermediate matrix
        cout << "\nAfter step " << i + 1 << ":\n";
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c <= n; c++)
                cout << a[r][c] << "\t";
            cout << endl;
        }
    }

    // Back Substitution
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++)
            x[i] -= a[i][j] * x[j];
        x[i] /= a[i][i];
    }

    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << x[i] << endl;

    return 0;
}
