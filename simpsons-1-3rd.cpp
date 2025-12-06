#include <bits/stdc++.h>
using namespace std;

// Define your function here (you can modify this part)
double f(double x) {
    // Example function: sin(x) + x^2
    return sin(x) + x*x;
}

// Simpson's 1/3rd Rule
double simpsonOneThird(double a, double b, int n, double (*func)(double)) {

    if (n <= 0) {
        throw invalid_argument("Number of intervals must be positive.");
    }

    if (n % 2 != 0) {
        throw invalid_argument("Simpson's 1/3rd Rule requires an EVEN number of intervals.");
    }

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * func(x);  // even index coefficient
        else
            sum += 4 * func(x);  // odd index coefficient
    }

    return (h / 3.0) * sum;
}

int main() {
    double a, b;
    int n;

    cout << "Enter lower limit a: ";
    cin >> a;
    cout << "Enter upper limit b: ";
    cin >> b;
    cout << "Enter number of intervals n (EVEN): ";
    cin >> n;

    try {
        double result = simpsonOneThird(a, b, n, f);
        cout << "\nApproximate Integral = " << result << endl;
    }
    catch (const exception &ex) {
        cout << "\nError: " << ex.what() << endl;
    }

    return 0;
}
