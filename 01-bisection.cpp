#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
    return 3*x - cos(x) - 1;
    // return x*x - 4*x - 10; 
}

int main()
{
    double x1, x2, x0, E;

    cout << "Enter first guess x1: ";
    cin >> x1;

    cout << "Enter second guess x2: ";
    cin >> x2;

    cout << "Enter stopping criterion E: ";
    cin >> E;

    if (f(x1) * f(x2) >= 0) {
        cout << "Invalid initial guesses. f(x1) * f(x2) must be less than 0." << endl;
        return 1;
    }

    do {
        x0 = (x1 + x2) / 2.0;

        double f0 = f(x0);

        if (f0 == 0) {
            cout << "root = " << x0 << endl;
            break;
        } else if (f0 * f(x1) < 0) {
            x2 = x0;
        } else {
            x1 = x0;
        }
    } while (fabs((x2 - x1) / x2) >= E);

    cout << "approximate root = " << x0 << endl;

    return 0;
}