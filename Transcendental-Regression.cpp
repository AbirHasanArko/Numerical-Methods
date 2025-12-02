#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    double x[100], y[100], Y[100];
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    cout << "Enter data points (x y):\n";
    for(int i=0; i<n; i++) {
        cin >> x[i] >> y[i];
        Y[i] = log(y[i]);
        sumX += x[i];
        sumY += Y[i];
        sumXY += x[i] * Y[i];
        sumX2 += x[i] * x[i];
    }

    double b = (n*sumXY - sumX*sumY) / (n*sumX2 - sumX*sumX);
    double A = (sumY - b*sumX) / n;
    double a = exp(A);

    cout << "\nExponential Regression:\n";
    cout << "y = " << a << " * e^(" << b << "x)\n";

    return 0;
}
