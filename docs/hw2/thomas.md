# Thomas algorithm
*Routine Name:* thomasSolve
*Author:* Jack Kiefer
*Language:* C++

## Description

Uses the thomas algorithm to solve the equation \\(Ax = b \\) where \\(A\\) is a tridiagonal matrix. Returns a column vector \\(x\\).


## Input

* ``a`` - The tridiagonal matrix \\(A\\)
* ``b`` - The column vector \\(b\\)

## Output 

Returns a ``nde::Matrix<T>`` that is a column vector of the solutions. 

## Code

{% highlight C++ %}
template <typename T>
nde::Matrix<T> thomasSolve(nde::Matrix<T> a, nde::Matrix<T> b)
{
  a[0][1] = a[0][1] / a[0][0];
  for (auto i = 1u; i < a.size() - 1; ++i)
  {
    auto ai = a[i][i-1];
    auto bi = a[i][i];
    auto ci = a[i][i+1];
    a[i][i+1] = ci/(bi-(ai*a[i-1][i]));
  }

  b[0][0] = b[0][0] / a[0][0];
  for (auto i = 1u; i < b.size(); ++i)
  {
    auto ai = a[i][i-1];
    auto bi = a[i][i];
    auto ci1 = a[i-1][i];
    b[i][0] = (b[i][0] - (ai*b[i-1][0]))/(bi - (ai*ci1));
  }
  return backSub(b, a); 
}
{% endhighlight %}

## Example

## Result
