---
math: true
layout: default
---

{% include mathjax.html %}


# Vector Norms

*Routine Name:* pNorm, infNorm

*Author:* Jack Kiefer

*Language:* C++

## Description

Compute the p-norm or the infinity norm of a given vector.

## Input

The vector `v`.
If p-norm, the _p_th norm as well.

## Output 

The norm of the vector. 

## Code

{% highlight C++ %}
template <typename T, typename P>
T pNorm(std::vector<T> const & x, P const & p)
{
  return std::pow(nde::sum(nde::map( [=](T xi){return std::pow(std::abs(xi), p);}, x)), 1.0/p );
}
 
template <typename T>
T infNorm(std::vector<T> const & v)
{
  return nde::max(nde::map(farg(std::abs), v));
}
{% endhighlight %}


## Example
{% highlight C++ %}
std::vector<double> v { 1, 2, 3, 4 };
std::cout << "2-norm: \n" << nde::pNorm(v, 2) << std::endl;
std::cout << "infinity norm: \n" << nde::infNorm(v) << std::endl;
{% endhighlight %}

## Result
```
2-norm: 
5.47723
infinity norm: 
4
```
