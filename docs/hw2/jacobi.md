---
math: true
layout: default
---

{% include mathjax.html %}


# Jacobi Iteration

*Routine Name:* jacobiIterate

*Author:* Jack Kiefer

*Language:* C++

## Description

Uses Jacobi Iteration to solve a diagonally dominant linear system of equations \\(Ax = b \\)

## Input

* ``a`` - The matrix \\(A\\)
* ``b`` - The column vector \\(b\\)
* ``x`` - Initial guesses for the solutions \\(x\\)
* ``tolerance`` - An acceptable error tolerance

## Output 

Returns a vector containing the solutions (x).

## Code

{% highlight C++ %}
template <typename T>
std::vector<T> jacobiIterate(nde::Matrix<T> a, std::vector<T> b, std::vector<T> x, T tolerance)
{
  const auto MAX_ITERS = 1000;
  auto origX = x;

  for (auto k = 0; k < MAX_ITERS; ++k)
  {
    for (auto i = 0u; i < a.size(); ++i)
    {
      auto sigma = 0;
      for (auto j = 0u; j < a.size(); ++j)
      {
        if (j != i)
        {
          sigma += a[i][j]*x[j];
        }
      }
      x[i] = (b[i]-sigma)/a[i][i];
    }
    if (nde::allclose(origX, x, tolerance))
    {
      break;
    }
  }
  return x;
}
{% endhighlight %}

## Example

{% highlight C++ %}
nde::Matrix<double> a {
  {10, -1,  2,  0},
  {-1, 11, -1,  3},
  { 2, -1, 10, -1},
  { 0 , 3, -1,  8} 
};

std::vector<double> b { 6,25,-11,15 };
std::vector<double> x { 1,1,1,1 };

std::cout << jacobiIterate(a, b, c, 0.0000001) << std::endl;
{% endhighlight %}

## Result
```
[    1    2    -1    1 ]
```
