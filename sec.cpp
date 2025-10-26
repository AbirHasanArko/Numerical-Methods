#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Function to evaluate polynomial value for x
double f(const vector<double> &coeff, double x) {
    double result = 0;
    int n = coeff.size();
    for (int i = 0; i < n; i++) {
        result += coeff[i] * pow(x, n - i - 1);
    }
    return result;
}

int main() {
    int degree;
    cout << "Enter degree of equation: ";
    cin >> degree;

    vector<double> coeff(degree + 1);
    cout << "Enter coefficients from highest to constant term (a_n ... a_0):\n";
    for (int i = 0; i <= degree; i++)
        cin >> coeff[i];

    double x0, x1;
    cout << "Enter two initial guesses (x0 and x1): ";
    cin >> x0 >> x1;

    const double EPS = 1e-5;
    double x2;
    int iter = 0;

    cout << fixed << setprecision(6);

    // Secant Method Iteration
    do {
        double f0 = f(coeff, x0);
        double f1 = f(coeff, x1);

        if (fabs(f1 - f0) < 1e-10) {
            cout << "Division by zero or very small difference in function values.\n";
            return 1;
        }

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        iter++;

        if (fabs((x2 - x1) / x2) < EPS)
            break;

        x0 = x1;
        x1 = x2;

    } while (iter < 1000);

    // Print function in readable form
    cout << "\nFunction: ";
    for (int i = 0; i <= degree; i++) {
        cout << coeff[i];
        if (degree - i > 0) cout << "x^" << (degree - i);
        if (i < degree) cout << " + ";
    }
    cout << " = 0\n";

    cout << "Root: " << x2 << endl;
    cout << "Search interval for the root: [" << x0 << ", " << x1 << "]" << endl;
    cout << "Iterations needed: " << iter << endl;

    return 0;
}