# Elliptic ODE
*Routine Name:* ``elliptic``
*Author:* Jack Kiefer
*Language:* C++

## Description

Numerically computes solutions to the elliptic ordinary differential equation
\\[ u'' = f(x) \\]

for an arbitray user-defined \\( f(x) \\) on the interval \\( \[a, b\] \\) with known conditions \\( u(a) = u_a \\) and \\( u(b) = u_b \\).

## Input

* ``f`` - The function \\( f(x) \\)
* ``a`` - The interval start \\(a\\)
* ``b`` - The interval end \\(b\\)
* ``ua`` - The known condition \\(u(a)\\)
* ``ub`` - The known condition \\(u(b)\\)


## Output 

Returns a row vector of the solutions.

## Code

## Example

{% highlight C++ %}
auto const PI = 3.14159;
auto solutions = nde::elliptic(
         /* f  */  [=](double x) { return std::sin(PI*x); },
         /* a  */  0.0,
         /* b  */  1.0,
         /* ua */  2.5,
         /* ub */  5.0
                 );
{% endhighlight %}

## Result
