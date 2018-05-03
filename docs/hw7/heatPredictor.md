---
math: true
layout: default
---

{% include mathjax.html %}


# Heat Equation with Predictor-Corrector Method 

*Routine Name:* heatPredictorCorrector

*Author:* Jack Kiefer

*Language:* C++

## Description

Use the Predictor-corrector method to compute the solution to the heat equation

\\[\frac{\partial u}{\partial t} - \alpha \Big( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} + \frac{\partial^2 u}{\partial z^2} \Big) = 0, u(x, 0) = f(x)\\]

## Input

* ``func`` - The function \\(u\\)
* ``init`` - The initial condition function \\(f(x)\\)

## Output 

Returns an function that is a (approximate) solution

## Declaration

{% highlight C++ %}

template <typename T, typename F>
std::function<T(T)> heatRungeKutta(F func, T t0);

{% endhighlight %}

## Example

{% highlight C++ %}

auto f = nde:heatRungeKutta(farg(myfunc),[=](int x){ return 0; });
std::cout << f(3, 4, 5) << std::endl;

{% endhighlight %}

## Result
```
2.33333333333334
```
