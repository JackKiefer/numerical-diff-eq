# fdcoeffV
*Routine Name:* fdcoeffV
*Author:* Jack Kiefer
*Language:* C++

## Description

Computes coefficients for finite difference approximations of an arbitrary oder of accuracy for a given derivative. 

## Input

* ``k`` - Specifies coefficients for the _k_th-order derivative
* ``xbar`` - The point to evaluate at
* ``x`` - A row vector (_n_ x 1 matrix) of stencil points

## Output 

Returns a row vector of coefficients.

## Code

## Example

{% highlight C++ %}
/* Generate a row vector of stencil points */
nde::Matrix<double> stencils { { 0, 1, 2, 3, 4 } };

/* Calculate the coefficients */
auto coeffs = nde::fdcoeffV(2, 1.0, stencils);
{% endhighlight %}

## Result
