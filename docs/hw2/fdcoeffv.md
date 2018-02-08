---
math: true
layout: default
---

{% include mathjax.html %}


# fdcoeffV

*Routine Name:* fdcoeffV

*Author:* Jack Kiefer

*Language:* C++

## Description

Computes coefficients for finite difference approximations of an arbitrary oder of accuracy for a given derivative. 

## Input

* ``k`` - Specifies coefficients for the _k_th-order derivative
* ``xbar`` - The point to evaluate at
* ``x`` - A row vector (_n_ x 1 matrix) of stencil points

## Output 

Returns a row vector of coefficients.

## Code

{% highlight C++ %}
template <typename T, typename Num>
nde::Matrix<Num> fdcoeffV(luint k, T xbar, nde::Matrix<Num> x)
{
  auto n = x.size();
  auto a = nde::ones(n,n);
  auto xrow = x - xbar;
  for (auto i = 1u; i < n; ++i)
  {
    a[i] = nde::map([=](T t){ return std::pow(t,i-1)/nde::factorial<T>(i-1); }, xrow);
  }
  auto b = zeroes(n,1);
  b[k+1] = b[k+1] + 1;

  return nde::gaussElim(a,b);
}
{% endhighlight %}

## Example

{% highlight C++ %}
/* Generate a row vector of stencil points */
nde::Matrix<double> stencils { { 0, 1, 2, 3, 4 } };

/* Calculate the coefficients */
auto coeffs = nde::fdcoeffV(2, 1.0, stencils);
{% endhighlight %}

## Result
```
|       1        -2       1 |
```
