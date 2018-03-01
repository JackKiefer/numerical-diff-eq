---
math: true
layout: default
---

{% include mathjax.html %}


# Matrix Norms

*Routine Name:* matrix1Norm / matrixInfNorm

*Author:* Jack Kiefer

*Language:* C++

## Description

Compute either the 1 norm of the infinity norm of a matrix.

## Input

* ``a`` - The matrix \\(A\\) to take the norm of

## Output 

Returns a norm of type ``T``

## Code

{% highlight C++ %}

template <typename T>
T matrixInfNorm(nde::Matrix<T> a)
{
  T maxSum = 0.0;
  for (auto && row : a)
  {
    T rowSum = nde::pNorm(row,1);
    if (rowSum > maxSum)
    {
      maxSum = rowSum;
    }
  }
  return maxSum;
}

template <typename T>
T matrix1Norm(nde::Matrix<T> a)
{
  T maxSum = 0.0;
  /* For each column */
  for (auto j = 0u; j < a[0].size(); ++j)
  {
    T colSum = 0.0;
    /* For each entry in column */
    for (auto i = 0u; i < a.size(); ++i)
    {
      colSum += a[i][j];
    }
    if (colSum > maxSum)
    {
      maxSum = colSum;
    }
  }
  return maxSum;
}

{% endhighlight %}

## Example

{% highlight C++ %}

nde::Matrix<double> b {
  {3, 9, 5},
  {7, 2, 4},
  {6, 8, 1}
};

std::cout << nde::matrix1Norm(b) << std::endl;
std::cout << nde::matrixInfNorm(b) << std::endl;

{% endhighlight %}

## Result
```
19
17
```
