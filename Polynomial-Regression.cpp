#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    double x[100], y[100];
    double sumX=0, sumX2=0, sumX3=0, sumX4=0;
    double sumY=0, sumXY=0, sumX2Y=0;

    cout << "Enter data points (x y):\n";
    for(int i=0; i<n; i++) {
        cin >> x[i] >> y[i];

        sumX += x[i];
        sumX2 += x[i]*x[i];
        sumX3 += x[i]*x[i]*x[i];
        sumX4 += x[i]*x[i]*x[i]*x[i];

        sumY += y[i];
        sumXY += x[i]*y[i];
        sumX2Y += x[i]*x[i]*y[i];
    }

    // Solve using Cramer's Rule
    double D = n*(sumX2*sumX4 - sumX3*sumX3)
             - sumX*(sumX*sumX4 - sumX2*sumX3)
             + sumX2*(sumX*sumX3 - sumX2*sumX2);

    double Da = sumY*(sumX2*sumX4 - sumX3*sumX3)
              - sumX*(sumXY*sumX4 - sumX2Y*sumX3)
              + sumX2*(sumXY*sumX3 - sumX2*sumX2Y);

    double Db = n*(sumXY*sumX4 - sumX2Y*sumX3)
              - sumY*(sumX*sumX4 - sumX2*sumX3)
              + sumX2*(sumX*sumX2Y - sumXY*sumX2);

    double Dc = n*(sumX2*sumX2Y - sumXY*sumX3)
              - sumX*(sumX*sumX2Y - sumXY*sumX2)
              + sumY*(sumX*sumX3 - sumX2*sumX2);

    double a = Da / D;
    double b = Db / D;
    double c = Dc / D;

    cout << "\nQuadratic Regression Equation:\n";
    cout << "y = " << a << " + " << b << "x + " << c << "x^2\n";

    return 0;
}
