#include <bits/stdc++.h>

using namespace std;

void findRoots() {
    vector<double> coefs;
    vector<double> roots;
    double posXmax, negXmax, a, b;
    int rootCount = 0, iterCount = 0;

    // Function to evaluate polynomial at x
    auto eval = [](const vector<double>& eqn, double x) {
        double res = 0.0;
        for (int i = eqn.size() - 1; i >= 0; i--)
            res += eqn[i] * pow(x, i);
        return res;
    };

    // Function to compute the derivative
    auto evalDerivative = [](const vector<double>& eqn, double x) {
        double res = 0.0;
        for (int i = eqn.size() - 1; i > 0; i--)
            res += eqn[i] * i * pow(x, i - 1);
        return res;
    };

    // Root range calculator
    auto calcRange = [](const vector<double>& eqn) {
        int n = eqn.size() - 1;
        double x0 = eqn[n - 1] / eqn[n];
        double x1 = pow(x0, 2) - 2 * (eqn[n - 2] / eqn[n]);
        if (x1 >= 0)
            return sqrt(x1);
        throw runtime_error("Invalid range: sqrt of negative.");
    };

    // Bracket generator for bisection
    auto generateBracket = [&](const vector<double>& eqn) {
        for (double x = negXmax; x <= posXmax; x++) {
            double fA = eval(eqn, x), fB = eval(eqn, x + 1);

            if (abs(fA) < 1e-9) {
                roots.push_back(x);
                rootCount++;
                negXmax = x + 1;
                return true;
            }
            if (abs(fB) < 1e-9) {
                roots.push_back(x + 1);
                rootCount++;
                negXmax = x + 2;
                return true;
            }
            if (fA * fB < 0) {
                a = x;
                b = x + 1;
                negXmax = x + 1;
                return false;
            }
        }
        return false;
    };

    // Newton-Raphson method for finding root
    auto newtonRaphson = [&](const vector<double>& eqn) {
        double x0 = (a + b) / 2; // Initial guess
        int maxIters = 100;

        while (maxIters--) {
            iterCount++;
            double fx0 = eval(eqn, x0);
            double fPrimeX0 = evalDerivative(eqn, x0);
            if (abs(fPrimeX0) < 1e-9) {
                cerr << "Derivative is too small at x = " << x0 << endl;
                return;
            }
            double xNext = x0 - (fx0 / fPrimeX0);

            if (abs(eval(eqn, xNext)) < 1e-9) {
                roots.push_back(xNext);
                rootCount++;
                return;
            }
            x0 = xNext;
        }
    };

    // Input for polynomial equation
    int degree;
    cout << "Enter degree of polynomial: ";
    cin >> degree;
    coefs.resize(degree + 1);
    cout << "Enter coefficients from highest degree to constant: ";
    for (int i = degree; i >= 0; i--)
        cin >> coefs[i];

    // Calculate search range
    try {
        posXmax = calcRange(coefs);
        negXmax = -posXmax;
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }

    // Finding roots
    while (rootCount < degree) {
        if (generateBracket(coefs)) continue;
        newtonRaphson(coefs);
    }

    // Display results
    cout << "Roots found: ";
    for (const auto& root : roots)
        cout << root << " ";
    cout << "\nTotal iterations: " << iterCount << endl;
}

int main() {
    findRoots();
    return 0;
}
