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

    // Root range calculator
    auto calcRange = [](const vector<double>& eqn) {
        int n = eqn.size() - 1;
        double x0 = eqn[n - 1] / eqn[n];
        double x1 = pow(x0, 2) - 2 * (eqn[n - 2] / eqn[n]);
        if (x1 >= 0)
            return sqrt(x1);
        throw runtime_error("Invalid range: sqrt of negative.");
    };

    // Bracket generator for Secant method
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

    // Secant method for finding root
    auto secantMethod = [&](const vector<double>& eqn) {
        double x1 = a, x2 = b; // Initial guesses
        int maxIters = 100;

        while (maxIters--) {
            iterCount++;
            double fx1 = eval(eqn, x1);
            double fx2 = eval(eqn, x2);

            // Check for division by zero
            if (fx2 - fx1 == 0) {
                cerr << "Division by zero in secant method." << endl;
                return;
            }

            double xNext = x2 - (fx2 * (x2 - x1)) / (fx2 - fx1);

            if (abs(eval(eqn, xNext)) < 1e-9) {
                roots.push_back(xNext);
                rootCount++;
                return;
            }

            // Update for the next iteration
            x1 = x2;
            x2 = xNext;
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
        secantMethod(coefs);
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
