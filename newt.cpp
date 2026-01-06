#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Function to evaluate polynomial f(x)
double f(const vector<double> &coeff, double x) {
    double result = 0;
    int n = coeff.size();
    for (int i = 0; i < n; i++) {
        result += coeff[i] * pow(x, n - i - 1);
    }
    return result;
}

// Function to evaluate derivative f'(x)
double fprime(const vector<double> &coeff, double x) {
    double result = 0;
    int n = coeff.size();
    for (int i = 0; i < n - 1; i++) {
        result += (n - i - 1) * coeff[i] * pow(x, n - i - 2);
    }
    return result;
}

int main() {
    int degree;
    cout << "Enter degree of equation: ";
    cin >> degree;

    vector<double> coeff(degree + 1);
    cout << "Enter coefficients from highest degree to constant term (a_n ... a_0):\n";
    for (int i = 0; i <= degree; i++)
        cin >> coeff[i];

    double x0;
    cout << "Enter initial guess: ";
    cin >> x0;

    const double EPS = 1e-5;
    double x1;
    int iter = 0;

    cout << fixed << setprecision(6);

    while (true) {
        double fx = f(coeff, x0);
        double fpx = fprime(coeff, x0);

        if (fabs(fpx) < 1e-10) {
            cout << "Derivative too small — method fails.\n";
            return 1;
        }

        x1 = x0 - fx / fpx;
        iter++;

        if (fabs((x1 - x0) / x1) < EPS)
            break;

        x0 = x1;

        if (iter > 1000) {
            cout << "Method did not converge.\n";
            return 1;
        }
    }

    // Print function
    cout << "\nFunction: ";
    for (int i = 0; i <= degree; i++) {
        cout << coeff[i];
        if (degree - i > 0) cout << "x^" << (degree - i);
        if (i < degree) cout << " + ";
    }
    cout << " = 0\n";

    cout << "Root: " << x1 << endl;
    cout << "Initial guess: " << x0 << endl;
    cout << "Iterations needed: " << iter << endl;

    return 0;
}
