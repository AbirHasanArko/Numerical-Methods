#include <bits/stdc++.h>
using namespace std;


// Define your function here (you can modify this part)
double f(double x) {
    // Example: sin(x) + x^2
    return sin(x) + x*x;
}

// Simpson's 3/8th Rule
double simpsonThreeEighth(double a, double b, int n, double (*func)(double)) {

    if (n <= 0) {
        throw invalid_argument("Number of intervals must be positive.");
    }

    if (n % 3 != 0) {
        throw invalid_argument("Simpson's 3/8th Rule requires number of intervals to be a MULTIPLE of 3.");
    }

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;

        if (i % 3 == 0)
            sum += 2 * func(x);   // coefficient 2 for multiples of 3
        else
            sum += 3 * func(x);   // coefficient 3 for others
    }

    return (3.0 * h / 8.0) * sum;
}

int main() {
    double a, b;
    int n;

    cout << "Enter lower limit a: ";
    cin >> a;
    cout << "Enter upper limit b: ";
    cin >> b;
    cout << "Enter number of intervals n (MULTIPLE OF 3): ";
    cin >> n;

    try {
        double result = simpsonThreeEighth(a, b, n, f);
        cout << "\nApproximate Integral = " << result << endl;
    }
    catch (const exception &ex) {
        cout << "\nError: " << ex.what() << endl;
    }

    return 0;
}
