---
math: true
layout: default
---

{% include mathjax.html %}


# Power Iteration

*Routine Name:* powerIterate

*Author:* Jack Kiefer

*Language:* C++

## Description

Compute the largest eigenvalue of a matrix using the power iteration method.

## Input

* ``a`` - The matrix \\(A\\) to take the eigenvalue of
* ``MAX_ITERS`` - The number of times to iterate to converge on the eigenvalue

## Output 

Returns an eigenvalue of type ``T``

## Code

{% highlight C++ %}

template <typename T>
T powerIterate(nde::Matrix<T> a, luint const & MAX_ITERS)
{
  auto b_k = nde::randMatrix<T>(a[0].size(), 1, 2, 50);
  for (auto i = 0u; i < MAX_ITERS; ++i)
  {
    auto b_k1 = a * b_k;
    auto b_k1_norm = nde::pNorm(nde::rowVector(b_k1), 2);
    b_k = b_k1 / b_k1_norm;
  }
  nde::Matrix<T> transpose { nde::rowVector(b_k) };
  return ((transpose*(a*b_k))/(transpose*b_k))[0][0];
}

{% endhighlight %}

## Example

{% highlight C++ %}

auto a = nde::hilbert<double>(5);
std::cout << nde::powerIterate(a, 10) << std::endl;

{% endhighlight %}

## Result
```
1.56705
```
