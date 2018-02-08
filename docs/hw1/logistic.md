# Logistic Equation
*Routine Name:* logistic
*Author:* Jack Kiefer
*Language:* C++

## Description

Computes the solution the logistic equation of the form:
\\[ \frac{dP}{dt} = aP + bP^2 \\]

## Input

* ``p0`` - The initial condition \\(P(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)

## Output 

Returns a ``std::function<Num(Time)>``, where the ``Time`` type must be explicitly declared at the call site and ``Num`` is deduced to be the same type as the initial conditions. See the example below.


## Code

## Example

Compute the solution to the equation \\[ \frac{dP}{dt} = 1.4P + 2P^2 \\] with initial condition \\(P(0) = 2.6\\) and find the output at time \\(t = 10\\)

{% highlight C++ %}
/* Solve the equation */
auto const p = nde::logistic<double>(2.6,1.4,2.0);

/* Print the output at time t=10 */
std::cout << p(10.0) << std::endl;

{% endhighlight %}


## Result
