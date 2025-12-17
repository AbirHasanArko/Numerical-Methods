#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

/* ---------------------------
   Utility: factorial
*/
double factorial(int n) {
    double f = 1.0;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

/* ---------------------------
   Utility: Forward Difference Table
*/
vector<vector<double>> forwardDiff(const vector<double>& y) {
    int n = y.size();
    vector<vector<double>> d(n, vector<double>(n));

    for (int i = 0; i < n; i++)
        d[i][0] = y[i];

    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            d[i][j] = d[i + 1][j - 1] - d[i][j - 1];

    return d;
}

/* ---------------------------
   Utility: Backward Difference Table
*/
vector<vector<double>> backwardDiff(const vector<double>& y) {
    int n = y.size();
    vector<vector<double>> b(n, vector<double>(n));

    for (int i = 0; i < n; i++)
        b[i][0] = y[i];

    for (int j = 1; j < n; j++)
        for (int i = n - 1; i >= j; i--)
            b[i][j] = b[i][j - 1] - b[i - 1][j - 1];

    return b;
}

/* ===========================
   FORWARD INTERPOLATION
=========================== */
double newtonForward(const vector<double>& x,
                     const vector<double>& y,
                     double xp) {
    int n = x.size();
    double h = x[1] - x[0];
    auto d = forwardDiff(y);

    double u = (xp - x[0]) / h;
    double sum = d[0][0], p = 1.0;

    for (int k = 1; k < n; k++) {
        p *= (u - (k - 1));
        sum += (p / factorial(k)) * d[0][k];
    }
    return sum;
}

/* ---------------------------
   Forward First Derivative
*/
double forwardFirstDerivative(const vector<double>& x,
                              const vector<double>& y,
                              double xp) {
    double h = x[1] - x[0];
    auto d = forwardDiff(y);
    double u = (xp - x[0]) / h;

    double res = d[0][1];
    if (x.size() >= 3)
        res += ((2*u - 1)/2.0) * d[0][2];
    if (x.size() >= 4)
        res += ((3*u*u - 6*u + 2)/6.0) * d[0][3];

    return res / h;
}

/* ---------------------------
   Forward Second Derivative
*/
double forwardSecondDerivative(const vector<double>& x,
                               const vector<double>& y,
                               double xp) {
    double h = x[1] - x[0];
    auto d = forwardDiff(y);
    double u = (xp - x[0]) / h;

    double res = d[0][2];
    if (x.size() >= 4)
        res += (u - 1) * d[0][3];
    if (x.size() >= 5)
        res += ((6*u*u - 18*u + 11)/12.0) * d[0][4];

    return res / (h*h);
}

/* ===========================
   BACKWARD INTERPOLATION
=========================== */
double newtonBackward(const vector<double>& x,
                      const vector<double>& y,
                      double xp) {
    int n = x.size();
    double h = x[1] - x[0];
    auto b = backwardDiff(y);

    double v = (xp - x[n-1]) / h;
    double sum = b[n-1][0], p = 1.0;

    for (int k = 1; k < n; k++) {
        p *= (v + (k - 1));
        sum += (p / factorial(k)) * b[n-1][k];
    }
    return sum;
}

/* ---------------------------
   Backward First Derivative
*/
double backwardFirstDerivative(const vector<double>& x,
                               const vector<double>& y,
                               double xp) {
    int n = x.size();
    double h = x[1] - x[0];
    auto b = backwardDiff(y);
    double v = (xp - x[n-1]) / h;

    double res = b[n-1][1];
    if (n >= 3)
        res += ((2*v + 1)/2.0) * b[n-1][2];
    if (n >= 4)
        res += ((3*v*v + 6*v + 2)/6.0) * b[n-1][3];

    return res / h;
}

/* ---------------------------
   Backward Second Derivative
*/
double backwardSecondDerivative(const vector<double>& x,
                                const vector<double>& y,
                                double xp) {
    int n = x.size();
    double h = x[1] - x[0];
    auto b = backwardDiff(y);
    double v = (xp - x[n-1]) / h;

    double res = b[n-1][2];
    if (n >= 4)
        res += (v + 1) * b[n-1][3];
    if (n >= 5)
        res += ((6*v*v + 18*v + 11)/12.0) * b[n-1][4];

    return res / (h*h);
}

/* ===========================
   MAIN
=========================== */
int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter x and y values:\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    cout << "\n1. Forward Interpolation";
    cout << "\n2. Backward Interpolation";
    cout << "\n3. Forward First Derivative";
    cout << "\n4. Forward Second Derivative";
    cout << "\n5. Backward First Derivative";
    cout << "\n6. Backward Second Derivative";
    cout << "\nChoose option: ";

    int ch;
    cin >> ch;

    double xp;
    cout << "Enter x (point): ";
    cin >> xp;

    switch (ch) {
        case 1: cout << newtonForward(x,y,xp); break;
        case 2: cout << newtonBackward(x,y,xp); break;
        case 3: cout << forwardFirstDerivative(x,y,xp); break;
        case 4: cout << forwardSecondDerivative(x,y,xp); break;
        case 5: cout << backwardFirstDerivative(x,y,xp); break;
        case 6: cout << backwardSecondDerivative(x,y,xp); break;
        default: cout << "Invalid choice";
    }

    return 0;
}
