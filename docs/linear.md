---
math: true
layout: default
---

{% include mathjax.html %}


# Linear algebra  

| Routine | Description |
|---------|-------------|
| [thomasSolve](#thomassolve)  | Thomas tridiagonal matrix algorithm |
| [gaussElim](#gausselim) | LU factorization / Gaussian Elimination |
| [jacobiIterate](#jacobiiterate) | Jacobi iteration |

### thomasSolve

Uses the thomas algorithm to solve the equation \\(Ax = b \\) where \\(A\\) is a tridiagonal matrix. Returns a column vector \\(x\\).

#### Definition

The function definition is equivalent to:

{% highlight C++ %}
template <typename T>
nde::Matrix<T> thomasSolve(nde::Matrix<T> a, nde::Matrix<T> b)
{% endhighlight %}

#### Parameters

* ``a`` - The tridiagonal matrix \\(A\\)
* ``b`` - The column vector \\(b\\)

Returns a ``nde::Matrix<T>`` that is a column vector of the solutions. 

### gaussElim

Utilizes LU factorization followed by forward and back substitution to compute to the solution to the matrix equation \\(Ax = b\\) where \\(A\\) can be any square matrix.

#### Definition

The function definition is equivalent to:

{% highlight C++ %}
template <typename T>
nde::Matrix<T> gaussElim(nde::Matrix<T> a, nde::Matrix<T> b)
{% endhighlight %}

#### Parameters

* ``a`` - The matrix \\(a\\)
* ``b`` - The column vector \\(b\\)

Returns a ``nde::Matrix<T>`` that is the solution vector.

### jacobiIterate

Uses Jacobi Iteration to solve a diagonally dominant linear system of equations. 

#### Definition

The function definition is equivalent to:

{% highlight C++ %}
template <typename T>
std::vector<T> jacobiIterate(nde::Matrix<T> a, std::vector<T> b, std::vector<T> x, T tolerance)
{% endhighlight %}

#### Parameters

* ``a`` - Specifies coefficients for the _k_th-order derivative
* ``xbar`` - The point to evaluate at
* ``x`` - A row vector (_n_ x 1 matrix) of stencil points

#### Example

{% highlight C++ %}
/* Generate a row vector of stencil points */
nde::Matrix<double> stencils { { 0, 1, 2, 3, 4 } };

/* Calculate the coefficients */
auto coeffs = nde::fdcoeffV(2, 1.0, stencils);
{% endhighlight %}


