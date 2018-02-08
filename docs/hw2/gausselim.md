# Gaussian Elimination via LU factorization
*Routine Name:* ``gaussElim``
*Author:* Jack Kiefer
*Language:* C++

## Description

Utilizes LU factorization followed by forward and back substitution to compute to the solution to the matrix equation \\(Ax = b\\) where \\(A\\) can be any square matrix.

## Input

* ``a`` - The matrix \\(a\\)
* ``b`` - The column vector \\(b\\)

## Output 

Returns a ``nde::Matrix<T>`` that is the solution vector.

## Code

{% highlight C++ %}
template <typename T>
nde::Matrix<T> gaussElim(nde::Matrix<T> a, nde::Matrix<T> b)
{
  auto m = a.size() - 1; // Largest index
  auto u = a; 
  auto l = nde::identityMatrix<T>(m + 1);
  auto p = l;

  for (auto k = 0u; k <= m - 1; ++k)
  {
    auto pivotRow = nde::colMax(u, k + 1); 
    u = nde::rowSwap(u,pivotRow,k);
    l = nde::rowSwap(l,(int)k,(int)pivotRow,0,(int)k-1);
    p = nde::rowSwap(p,pivotRow,k);
    for (auto elimRow = k + 1; elimRow <= m; ++elimRow)
    {
      l[elimRow][k] = u[elimRow][k]/u[k][k];
      u = nde::rowEliminate(u, k, k, elimRow);
    }
  }

  auto y = forwardSub(p * b, l);
  return backSub(y,u);
}
{% endhighlight %}

## Example

## Result
