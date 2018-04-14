---
math: true
layout: default
---

{% include mathjax.html %}


# Predictor-Corrector Method 

*Routine Name:* predictorCorrector

*Author:* Jack Kiefer

*Language:* C++

## Description

Use the Predictor-Corrector method to compute the solution to the general initial value problem of the form

\\[y' = f(t,y), y(t_0) = y_0\\]

## Input

* ``func`` - The function \\(f\\)
* ``t0`` - The initial value \\(t_0\\)

## Output 

Returns an function that is a solution

## Declaration

{% highlight C++ %}

template <typename T, typename F>
std::function<T(T)> predictorCorrector(F func, T t0);

{% endhighlight %}

## Example

{% highlight C++ %}

auto f = nde::predictorCorrector(farg(std::sin), 1);
std::cout << f(0) << std::endl;

{% endhighlight %}

## Result
```
1
```
