---
math: true
layout: default
---

{% include mathjax.html %}


# Gauss-Seidel

*Routine Name:* gaussSeidel

*Author:* Jack Kiefer

*Language:* C++

## Description

Computer the solution of a linear system of equations using the Gauss-Seidel method.

## Input

* ``a`` - The coefficient matrix \\(A\\)
* ``b`` - The right-hand vector \\(b\\)

## Output 

Returns a solution vector

## Declaration

{% highlight C++ %}

template <typename T>
nde::Matrix<T> gaussSeidel(nde::Matrix<T> a, nde::Matrix<T> b);

{% endhighlight %}

## Example

{% highlight C++ %}

nde::Matrix<double> a {
  {  2,  1, -1 },
  { -3, -1,  2 },
  { -2,  1,  2 }
};

nde::Matrix<double> b { {8}, {-11}, {3} };

std::cout << nde::gaussSeidel(a, b) << std::endl;

{% endhighlight %}

## Result
```
|           2 |
|           3 |
|          -1 |
```
