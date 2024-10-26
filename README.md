This C++ program finds the roots of a polynomial equation using four 
different numerical methods:
1.	False Position Method
2.	Bisection Method
3.	Newton-Raphson Method
4.	Secant Method
Additionally, the program includes a Bracket Generator feature that
helps identify appropriate intervals where the roots may exist.
This program finds the roots of a polynomial equation based on user
 input. The user specifies the degree of the polynomial and its coefficients,
and the program applies the chosen numerical methods to calculate the roots.
The program is designed to work with polynomials of any degree.
Features:
•	Multiple Numerical Methods: Includes False Position, Bisection, Newton-Raphson,
and Secant methods for finding polynomial roots.
•	Bracket Generator: Automatically identifies intervals in which roots may lie.
•	Iteration Count Display: Shows the total number of iterations used for each method.
•	Error Tolerance Control: Includes a small tolerance value to determine when a root
 is found.
Methods Used
False Position Method:
The False Position Method is a root-finding technique that leverages linear
interpolation between two points on the polynomial curve. This method starts
 with two points a and b such that f(a) and f(b) have opposite signs,
indicating a root between them. The formula:
x₀ = (a * f(b) - b * f(a)) / (f(b) - f(a))
is used iteratively to refine the root estimate. This method converges quickly for
 well-behaved polynomials.
Bisection Method:
The Bisection Method is a straightforward root-finding technique that repeatedly
 divides an interval in half. It requires an interval [a, b] such that f(a) and f(b)
 have opposite signs. The midpoint x_mid = (a + b) / 2 is computed,
 and the interval is reduced by selecting the sub-interval that contains the root.
This method is simple but reliable, converging steadily towards the root.
Newton-Raphson Method:
The Newton-Raphson Method uses a combination of polynomial values and their derivatives
 to quickly find roots. Starting with an initial guess x0, the method refines
 the guess using:
xₙₑₓₜ = x₀ - (f(x₀) / f'(x₀))
This method converges rapidly but requires the calculation of the
 polynomial’s derivative. It works best with good initial guesses and for polynomials
without inflection points near the root.
Secant Method:
The Secant Method is similar to Newton-Raphson but does not require the derivative
 of the polynomial. Instead, it approximates the derivative using the two most
recent estimates x1 and x2 :
xₙₑₓₜ = x₂ - (f(x₂) * (x₂ - x₁)) / (f(x₂) - f(x₁))
This method is slightly less accurate than Newton-Raphson but more versatile as
 it only requires polynomial evaluations.
Bracket Generator:
The program includes a Bracket Generator feature that helps
 find the appropriate intervals [a, b] in which a root exists.
It systematically checks for changes in the sign of the polynomial values over a
specified range. When a sign change is detected between two points,
 it indicates the presence of a root, and the program refines the interval
 using the chosen numerical method.

