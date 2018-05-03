---
math: true
layout: default
---

{% include mathjax.html %}


# Hyperbolic PDEs with the Upwinding Method

*Routine Name:* upwinding

*Author:* Jack Kiefer

*Language:* C++

## Description

Use the Upwinding method to compute the solution to the PDE

\\[u_t + 2u_x = 0, u(x,y) = u_0\\]

## Input

* ``u0`` - The initial condition \\(u_0\\)

## Output 

Returns an function that is a solution

## Declaration

{% highlight C++ %}

template <typename T>
std::function<T(T)> upwinding(T u0);

{% endhighlight %}

## Example

{% highlight C++ %}

auto f = nde:upwinding(3)
std::cout << f(3) << std::endl;

{% endhighlight %}

## Result
```
12.186186186186
```
