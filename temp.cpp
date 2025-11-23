#include <bits/stdc++.h>
using namespace std;

/* ---------------------------
   1) Matrix inversion
   Gaussian elimination with partial pivoting.
   Returns true if invertible; inverse written into 'inv'.
*/
bool invertMatrix(const vector<vector<double>>& A, vector<vector<double>>& inv) {
    int n = (int)A.size();
    for (auto &r : A) if ((int)r.size() != n) return false;
    // create augmented matrix [A | I]
    vector<vector<double>> aug(n, vector<double>(2*n));
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++) aug[i][j] = A[i][j];
        aug[i][n+i] = 1.0;
    }

    const double EPS = 1e-12;
    for (int col = 0; col < n; ++col) {
        // partial pivoting: find row with max abs in column col
        int pivot = col;
        for (int r = col+1; r < n; ++r)
            if (fabs(aug[r][col]) > fabs(aug[pivot][col])) pivot = r;
        if (fabs(aug[pivot][col]) < EPS) return false; // singular

        if (pivot != col) swap(aug[pivot], aug[col]);

        // normalize pivot row
        double dv = aug[col][col];
        for (int j = 0; j < 2*n; ++j) aug[col][j] /= dv;

        // eliminate other rows
        for (int r = 0; r < n; ++r) {
            if (r == col) continue;
            double factor = aug[r][col];
            if (fabs(factor) < 1e-15) continue;
            for (int j = col; j < 2*n; ++j) aug[r][j] -= factor * aug[col][j];
        }
    }
    // extract inverse
    inv.assign(n, vector<double>(n));
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) inv[i][j] = aug[i][n+j];
    return true;
}

/* ---------------------------
   Utility: factorial up to n (double)
*/
double factorial(int n){
    double f = 1.0;
    for (int i=2;i<=n;i++) f *= i;
    return f;
}

/* ---------------------------
   2) Newton's Forward Interpolation
   - xs must be equally spaced, size n >= 1
   - ys same size
   - returns interpolated value at x
*/
double newtonForward(const vector<double>& xs, const vector<double>& ys, double x) {
    int n = (int)xs.size();
    if (n == 0) throw runtime_error("empty data");
    if ((int)ys.size() != n) throw runtime_error("size mismatch");

    if (n == 1) return ys[0];
    double h = xs[1] - xs[0];
    if (fabs(h) < 1e-15) throw runtime_error("zero spacing");

    // Build forward-difference table (triangular)
    vector<vector<double>> diff(n, vector<double>(n));
    for (int i=0;i<n;i++) diff[i][0] = ys[i];
    for (int j=1;j<n;j++){
        for (int i=0;i<n-j;i++){
            diff[i][j] = diff[i+1][j-1] - diff[i][j-1];
        }
    }

    double u = (x - xs[0]) / h;
    double result = diff[0][0];
    double u_prod = 1.0;
    for (int k=1;k<n;k++){
        u_prod *= (u - (k-1));
        result += (u_prod / factorial(k)) * diff[0][k];
    }
    return result;
}

/* ---------------------------
   3) Newton's Backward Interpolation
   - xs equally spaced.
   - uses backward difference table (from end).
   - returns interpolated value at x
*/
double newtonBackward(const vector<double>& xs, const vector<double>& ys, double x) {
    int n = (int)xs.size();
    if (n == 0) throw runtime_error("empty data");
    if ((int)ys.size() != n) throw runtime_error("size mismatch");

    if (n == 1) return ys[0];
    double h = xs[1] - xs[0];
    if (fabs(h) < 1e-15) throw runtime_error("zero spacing");

    // backward difference table: we'll store diffs such that b[i][0] = ys[i]
    vector<vector<double>> b(n, vector<double>(n));
    for (int i=0;i<n;i++) b[i][0] = ys[i];
    for (int j=1;j<n;j++){
        for (int i=n-1; i>=j; --i){
            b[i][j] = b[i][j-1] - b[i-1][j-1];
        }
    }

    double v = (x - xs[n-1]) / h; // v = (x - x_n)/h
    double result = b[n-1][0];
    double v_prod = 1.0;
    for (int k=1;k<n;k++){
        // term uses v*(v+1)*(v+2)*... up to k terms-1
        v_prod *= (v + (k-1));
        result += (v_prod / factorial(k)) * b[n-1][k];
    }
    return result;
}

/* ---------------------------
   4) Newton's Divided Difference Interpolation
   - works for arbitrary (x_i, y_i)
   - constructs table of divided differences and evaluates Newton form
*/
double newtonDividedDifference(const vector<double>& xs, const vector<double>& ys, double x) {
    int n = (int)xs.size();
    if (n == 0) throw runtime_error("empty data");
    if ((int)ys.size() != n) throw runtime_error("size mismatch");
    // Build table f[i][j] where f[i][0] = ys[i], f[i][j] = (f[i+1][j-1] - f[i][j-1])/(x[i+j] - x[i])
    vector<vector<double>> f(n, vector<double>(n));
    for (int i=0;i<n;i++) f[i][0] = ys[i];
    for (int j=1;j<n;j++){
        for (int i=0;i<n-j;i++){
            double denom = xs[i+j] - xs[i];
            if (fabs(denom) < 1e-15) throw runtime_error("duplicate x-values encountered");
            f[i][j] = (f[i+1][j-1] - f[i][j-1]) / denom;
        }
    }
    // Evaluate using Newton form: P(x) = f[0][0] + f[0][1]*(x-x0) + f[0][2]*(x-x0)*(x-x1) + ...
    double result = f[0][0];
    double term = 1.0;
    for (int j=1;j<n;j++){
        term *= (x - xs[j-1]);
        result += f[0][j] * term;
    }
    return result;
}

/* ---------------------------
   Small demonstration in main()
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Matrix inversion demo
    vector<vector<double>> A = {
        {4, 7, 2},
        {3, 6, 1},
        {2, 5, 3}
    };
    vector<vector<double>> inv;
    cout << "Matrix inversion demo:\n";
    if (invertMatrix(A, inv)) {
        for (auto &r : inv) {
            for (double v : r) cout << setw(12) << setprecision(8) << v;
            cout << "\n";
        }
    } else {
        cout << "Matrix is singular or not square\n";
    }
    cout << "\n";

    // 2) Newton forward & backward demo (equal spacing)
    vector<double> xs = {0, 1, 2, 3};
    vector<double> ys;
    // example function y = x^3 (for demonstration)
    for (double xi : xs) ys.push_back(xi*xi*xi);

    double xq = 1.5;
    cout << fixed << setprecision(6);
    cout << "Newton Forward at x=" << xq << " -> " << newtonForward(xs, ys, xq) << "\n";
    cout << "Newton Backward at x=" << xq << " -> " << newtonBackward(xs, ys, xq) << "\n";

    // 3) Divided difference demo (non-uniform nodes)
    vector<double> xu = {0.0, 0.7, 1.3, 2.0};
    vector<double> yu;
    for (double xi : xu) yu.push_back(sin(xi)); // example y = sin(x)
    double xq2 = 1.0;
    cout << "Newton Divided Difference at x=" << xq2 << " -> " << newtonDividedDifference(xu, yu, xq2) << "\n";

    return 0;
}
