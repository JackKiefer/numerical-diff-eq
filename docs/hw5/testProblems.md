---
math: true
layout: default
---

{% include mathjax.html %}


# Test Problems

*Routine Name:* hw5TestProblems

*Author:* Jack Kiefer

*Language:* C++

## Description

A nifty function to automatically compute the solution to the initial value problem

\\[u' = \lambda u\\]

and the logisitc model

\\[P' = \gamma P - \Beta P\\]

for problem 1 on homework 5.

## Input

* ``a`` - The initial confition \\(u_0\\)
* ``p`` - The initial confition \\(P_0\\)

## Output 

Returns a pair of functions that solve the test problems

## Declaration

{% highlight C++ %}
template <typename T, typename F>
std::pair<std::function<F(T)>,std::function<F(T)>> hw5TestProblems(T a, T p);

{% endhighlight %}

## Example

{% highlight C++ %}

int main()
{
    auto p = nde::hw5TestProblems(1, 1);
    std::cout << p.first(0) << std::endl;
    std::cout << p.second(0) << std::endl;
}

{% endhighlight %}

## Result
```
0
0
```
