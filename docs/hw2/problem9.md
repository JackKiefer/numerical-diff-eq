---
math: true
layout: default
---

{% include mathjax.html %}


# Name

*Routine Name:* Elliptic ODE with k(x)

*Author:* Jack Kiefer

*Language:* C++

## Description

Solves the elliptic ODE 

\\[ \frac{d}{dx} k(x) \frac{du}{dx} = f(x) \\]

for an arbitrary user-defined \\(f(x)\\) and a \\(k(x)\\) filled with randomly generated values between 10 and 50. 

## Input

A function \\(f\\), an initial interval point a, an initial interval point b, an intitial known point ua and initial known point ub. 

## Output 

The finite difference solutions in the form of a row vector. 

## Code

{% highlight C++ %}
template <typename T, typename F>
nde::Matrix<T> ellipticKx(F const & f, T a, T b, T ua)
{
  auto k = nde::map([=](T t){ return rand(10,50); }, std::vector<T>(10,0)); 
  auto v = nde::zeroes<T>(n,1);

  v[0][0] = f(a) - ua;
  for (auto i = 1u; i < n - 1; ++i)
  {
    v[i][0] = h_DIF * h_DIF * f(a + i) * k[i];
  }
  v[n - 1][0] = f(b) - ub;
  return nde::thomasSolve(nde::tridiagonal(n, 1.0, -2.0, 1.0), v);
}
{% endhighlight %}


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

```
|     -1.0042 |
|     -3.0148 |
|     -1.0030 |
|     -2.0232 |
|     -3.0803 |
```
