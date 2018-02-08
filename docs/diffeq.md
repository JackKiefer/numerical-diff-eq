---
math: true
layout: default
---

{% include mathjax.html %}


# Differential equations

| Routine | Description |
|---------|-------------|
| [logistic](#logistic)  | Logistic equation |
| [solcc](#solcc) | Second-order, linear, constant-coefficient equation |
| [fdcoeffV](#fdcoeffV) | Finite difference approximation coefficients |
| [elliptic](#elliptic) | Elliptic equation with arbitrary forcing function |

### logistic

Computes the solution the logistic equation of the form:
\\[ \frac{dP}{dt} = aP + bP^2 \\]

#### Definition
The function definition is equivalent to:

{% highlight C++ %}
template <typename Time,
          typename Num,
          typename Param1,
          typename Param2>
std::function<Num(Time)> logistic(
    Num p0,
    Param1 a, 
    Param2 b)

{% endhighlight %}

#### Parameters

* ``p0`` - The initial condition \\(P(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)

Returns a ``std::function<Num(Time)>``, where the ``Time`` type must be explicitly declared at the call site and ``Num`` is deduced to be the same type as the initial conditions. See the example below.

#### Example

Compute the solution to the equation \\[ \frac{dP}{dt} = 1.4P + 2P^2 \\] with initial condition \\(P(0) = 2.6\\) and find the output at time \\(t = 10\\)

{% highlight C++ %}
/* Solve the equation */
auto const p = nde::logistic<double>(2.6,1.4,2.0);

/* Print the output at time t=10 */
std::cout << p(10.0) << std::endl;

{% endhighlight %}

### solcc

Solves a **s**econd-**o**rder, **l**inear, **c**onstant-**c**oefficient equation of the form:

\\[ ay^{\prime \prime} + by^{\prime} + cy = f(t) \\]

The function will correctly account for all cases of characteristic roots.

#### Definition

The function definition is equivalent to:

{% highlight C++ %}

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2,
          typename Param3>
std::function<Num(Time)> solcc(
    Num y0,
    Num v0,
    Param1 a,
    Param2 b,
    Param3 c)

{% endhighlight %}

#### Parameters

* ``y0`` - The initial condition \\(y(0)\\)
* ``v0`` - The initial condition \\(y^{\prime}(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)
* ``c`` - The scalar \\(c\\)

Returns a ``std::function<Num(Time)>``, where the ``Time`` type must be explicitly declared at the call site and ``Num`` is deduced to be the same type as the initial conditions. See the example below.

#### Example

Compute the solution to the equation \\[ 2y^{\prime \prime} + 3y^{\prime} - 2y = 0 \\] at time \\(t=4\\) with initial conditions \\(y(0) = 1\\) and \\(y^{\prime}(0) = 0 \\).

{% highlight C++ %}
/* Solve the equation */
auto const y = nde::solcc<double>(1.0,0.0,2.0,3.0,-2.0);

/* Print the output at time t=4 */
std::cout << y(4.0) << std::endl;

{% endhighlight %}

### fdcoeffV

Computes coefficients for finite difference approximations of an arbitrary oder of accuracy for a given derivative. Returns a row vector of coefficients. 

#### Definition

The function definition is equivalent to:

{% highlight C++ %}
template <typename T, typename Num>
nde::Matrix<Num> fdcoeffV(long unsigned k, T xbar, nde::Matrix<Num> x)
{% endhighlight %}

#### Parameters

* ``k`` - Specifies coefficients for the _k_th-order derivative
* ``xbar`` - The point to evaluate at
* ``x`` - A row vector (_n_ x 1 matrix) of stencil points

#### Example

{% highlight C++ %}
/* Generate a row vector of stencil points */
nde::Matrix<double> stencils { { 0, 1, 2, 3, 4 } };

/* Calculate the coefficients */
auto coeffs = nde::fdcoeffV(2, 1.0, stencils);
{% endhighlight %}


### elliptic

Numerically computes solutions to the elliptic ordinary differential equation
\\[ u'' = f(x) \\]

for an arbitray user-defined \\( f(x) \\) on the interval \\( \[a, b\] \\) with known conditions \\( u(a) = u_a \\) and \\( u(b) = u_b \\). Returns a row vector of the solutions.

#### Definition

The function definition is equivalent to:

{% highlight C++ %}
template <typename T, typename F>
nde::Matrix<T> elliptic(F f, T a, T b, T ua, T ub)
{% endhighlight %}

#### Parameters

* ``f`` - The function \\( f(x) \\)
* ``a`` - The interval start \\(a\\)
* ``b`` - The interval end \\(b\\)
* ``ua`` - The known condition \\(u(a)\\)
* ``ub`` - The known condition \\(u(b)\\)

#### Example

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

