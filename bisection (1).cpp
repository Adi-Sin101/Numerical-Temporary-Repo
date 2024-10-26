#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

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

    // Bisection method for finding root
    auto bisection = [&](const vector<double>& eqn) {
        double xMid, prevXMid = (a + b) / 2;
        int maxIters = 100;

        while (maxIters--) {
            iterCount++;
            xMid = (a + b) / 2;
            if (abs(prevXMid - xMid) < 1e-5 && abs(eval(eqn, xMid)) < 1e-5) {
                roots.push_back(xMid);
                rootCount++;
                return;
            }
            if (abs(eval(eqn, xMid)) < 1e-9) {
                roots.push_back(xMid);
                rootCount++;
                return;
            }
            if ((eval(eqn, xMid) * eval(eqn, a)) < 0) b = xMid;
            else a = xMid;
            prevXMid = xMid;
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
        bisection(coefs);
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

