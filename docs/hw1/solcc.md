# Second-order linear constant-coefficient ODE
*Routine Name:* solcc
*Author:* Jack Kiefer
*Language:* C++

## Description

Solves a **s**econd-**o**rder, **l**inear, **c**onstant-**c**oefficient equation of the form:

\\[ ay^{\prime \prime} + by^{\prime} + cy = f(t) \\]

The function will correctly account for all cases of characteristic roots.

## Input

* ``y0`` - The initial condition \\(y(0)\\)
* ``v0`` - The initial condition \\(y^{\prime}(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)
* ``c`` - The scalar \\(c\\)

## Output 

Returns a ``std::function<Num(Time)>``, where the ``Time`` type must be explicitly declared at the call site and ``Num`` is deduced to be the same type as the initial conditions. See the example below.

## Code
## Example

Compute the solution to the equation \\[ 2y^{\prime \prime} + 3y^{\prime} - 2y = 0 \\] at time \\(t=4\\) with initial conditions \\(y(0) = 1\\) and \\(y^{\prime}(0) = 0 \\).

{% highlight C++ %}
/* Solve the equation */
auto const y = nde::solcc<double>(1.0,0.0,2.0,3.0,-2.0);

/* Print the output at time t=4 */
std::cout << y(4.0) << std::endl;

{% endhighlight %}

## Result
