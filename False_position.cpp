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

    // Bracket generator for false position
    auto generateBracket = [&](const vector<double>& eqn) {
        for (double x = negXmax; x <= posXmax; x++) {
            double fA = eval(eqn, x);
            double fB = eval(eqn, x + 1);

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

    // False position method for finding root
    auto falsePosition = [&](const vector<double>& eqn) {
        const double epsilon = 1e-9; // Tolerance for root detection
        double prevX0 = a;

        while (true) {
            iterCount++;
            double fA = eval(eqn, a);
            double fB = eval(eqn, b);
            double x0 = (a * fB - b * fA) / (fB - fA); // False Position formula

            // Check if x0 is already a root
            if (abs(eval(eqn, x0)) < epsilon || abs(prevX0 - x0) < epsilon) {
                roots.push_back(x0);
                rootCount++;
                return;
            }

            // Update interval based on the sign of function at x0
            if ((eval(eqn, x0) * fA) < 0) {
                b = x0; // Root is in [a, x0]
            } else {
                a = x0; // Root is in [x0, b]
            }

            prevX0 = x0; // Update previous x0 for the next iteration
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
        falsePosition(coefs);
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


