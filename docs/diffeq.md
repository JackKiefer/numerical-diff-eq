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

Computes the solution at time \\(t\\) to the logistic equation of the form:
\\[ \frac{dP}{dt} = aP + bP^2 \\]

#### Definition
{% highlight C++ %}
template 
< typename Time, 
  typename Num, 
  typename Param1, 
  typename Param2
  >
Num logistic(Num const & p0, Param1 const & a, Param2 const & b, Time const & t)
{% endhighlight %}

#### Parameters

* ``p0`` - The initial condition \\(P(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)
* ``t`` - The point in time \\(t\\)

Returns a solution that is of the same data type as the initial condition.

#### Example

Compute the solution to the equation \\[ \frac{dP}{dt} = 1.4P + 2P^2 \\] at time \\[t=10\\] with initial condition \\[P(0) = 2.6\\] and store the answer in ``result``.

{% highlight C++ %}
auto result = nde::logistic(2.6,1.4,2.0,10.0);
{% endhighlight %}

### solcc

Computes the solution at time \\(t\\) to the **s**econd-**o**rder, **l**inear, **c**onstant-**c**oefficient equation of the form:
\\[ ay^{\prime \prime} + by^{\prime} + cy = f(t) \\]

#### Definition
{% highlight C++ %}

template
< typename Time,
  typename Num,
  typename Param1,
  typename Param2,
  typename Param3
  >
std::optional<std::complex<Num>> solcc(Num y0, Num v0, Param1 a, Param2 b, Param3 c, Time t)

{% endhighlight %}

#### Parameters

* ``y0`` - The initial condition \\(y(0)\\)
* ``v0`` - The initial condition \\(y^{\prime}(0)\\)
* ``a`` - The scalar \\(a\\)
* ``b`` - The scalar \\(b\\)
* ``c`` - The scalar \\(c\\)
* ``t`` - The point in time \\(t\\)

Returns a ``std::optional`` containing a ``std::complex`` solution of the same data type as the initial conditions. The functional will fail and the optional will contain nothing if the characteristic roots are equal to each other.

#### Example

Compute the solution to the equation \\[ 2y^{\prime \prime} + 3y^{\prime} - 2y = 0 \\] at time \\(t=4\\) with initial conditions \\(y(0) = 1\\) and \\(y^{\prime}(0) = 0 \\). Store the answer in ``result``.

{% highlight C++ %}
auto result = nde::solcc(1.0,0.0,2.0,3.0,-2.0,4.0).value();
{% endhighlight %}

