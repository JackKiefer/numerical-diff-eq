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

### logistic

Computes the solution the logistic equation of the form:
\\[ \frac{dP}{dt} = aP + bP^2 \\]

#### Definition
{% highlight C++ %}

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2>
std::function<Num(Time)> logistic(
    Num const& p0,
    Param1 const& a, 
    Param2 const& b)

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
{% highlight C++ %}

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2,
          typename Param3>
std::function<Num(Time)> solcc(
    Num const& y0,
    Num const& v0,
    Param1 const& a,
    Param2 const& b,
    Param3 const& c)

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

