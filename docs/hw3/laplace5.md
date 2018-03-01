---
math: true
layout: default
---

{% include mathjax.html %}


# Power Iteration

*Routine Name:* laplace5

*Author:* Jack Kiefer

*Language:* C++

## Description

Compute the solution to the Laplace equation on a 5x5 grid using a 5-point stencil 

## Input

* ``func`` - The forcing function \\(f\\)

## Output 

Returns an function that is a solution

## Code

{% highlight C++ %}

template <typename T, typename F>
std::function<T(T)> laplace5(F func)
{
  unsigned long n = 5;
  auto nblock = n - 2;
  auto b = nde::tridiagonal<double>(nblock, 1.0, -4.0, 1.0);
  auto i = nde::identityMatrix<double>(nblock);
  auto z = nde::zeroes<double>(nblock,nblock);
  auto a = nde::blockDiagram(nde::tridiagonal<nde::Matrix<double>>(nblock, i, b, i, z)) * -1.0;
  auto bs = nde::zeroes<double>(nblock*nblock,1);
  for (auto i = 0u; i < nblock; ++i)
  {
    for (auto j = 0u; j < nblock; ++j)
    bs[i][j] = func(i*j);
  }

  auto u = nde::gaussElim(a, bs);
  return nde::mapToFunc(u);
}

{% endhighlight %}

## Example

{% highlight C++ %}

auto f = nde::laplace5(farg(std::sin));
std::cout << f(0) << std::endl;

{% endhighlight %}

## Result
```
0
```
