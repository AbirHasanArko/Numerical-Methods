#include <bits/stdc++.h>
using namespace std;

// Example ODE: dy/dx = f(x, y) = x + y
double f(double x, double y) {
    return x + y;
}

int main() {
    double x0, y0, x_target, h;
    cout << "Enter initial x0: ";
    cin >> x0;
    cout << "Enter initial y0: ";
    cin >> y0;
    cout << "Enter target x: ";
    cin >> x_target;
    cout << "Enter step size h: ";
    cin >> h;

    double x = x0, y = y0;

    cout << fixed << setprecision(6);
    cout << "Step-by-step RK4 results:\n";
    cout << "x = " << x << "   y = " << y << endl;

    while (x < x_target) {
        // Adjust final step to reach target exactly
        if (x + h > x_target) {
            h = x_target - x;
        }

        double k1 = h * f(x, y);
        double k2 = h * f(x + h/2.0, y + k1/2.0);
        double k3 = h * f(x + h/2.0, y + k2/2.0);
        double k4 = h * f(x + h, y + k3);
        double k = (k1 + 2*k2 + 2*k3 + k4)/6.0;

        cout << "k = " << k << endl;

        y = y + k;
        x = x + h;

        cout << "x = " << x << "   y = " << y << endl;
    }

    cout << "\nApproximate solution at x = " << x_target 
         << " is y = " << y << endl;

    return 0;
}
