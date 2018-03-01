---
math: true
layout: default
---

{% include mathjax.html %}


# Inverse Iteration

*Routine Name:* inverseIterate

*Author:* Jack Kiefer

*Language:* C++

## Description

Compute the smallest eigenvalue of a matrix using the inverse power iteration method.

## Input

* ``a`` - The matrix \\(A\\) to take the eigenvalue of
* ``MAX_ITERS`` - The number of times to iterate to converge on the eigenvalue

## Output 

Returns an eigenvalue of type ``T``

## Code

{% highlight C++ %}

template <typename T>
T inverseIterate(nde::Matrix<T> a, luint const & MAX_ITERS)
{
  T mu = nde::getRand(2,50);
  auto b_k = nde::randMatrix<T>(a.size(), 1, 2, 50);
  auto moda = nde::inverse(a - (nde::identityMatrix<T>(a.size()) * mu));
  for (auto i = 0u; i < MAX_ITERS; ++i)
  {
    auto mb = moda*b_k;
    auto c_k = nde::pNorm(nde::rowVector(mb),2);
    b_k = mb/c_k;
  }

  return b_k[0][0];
}

{% endhighlight %}

## Example

{% highlight C++ %}

auto a = nde::hilbert<double>(5);
std::cout << nde::inverseIterate(a, 10) << std::endl;

{% endhighlight %}

## Result
```
3.28793e-6
```
