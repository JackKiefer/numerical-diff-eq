# Utilities

| Routine | Description |
|---------|-------------|
| [maceps](#maceps)  | Calculate [machine epsilon](https://en.wikipedia.org/wiki/Machine_epsilon) |
| [absoluteError](#absoluteerror) | Absolute error between two numbers |
| [relativeError](#relativeerror) | Relative error between two numbers |

### maceps

**Definition:**
{% highlight C++ %}
double maceps()
{% endhighlight %}


### absoluteError

Returns the absolute error between the expected value and the measured value.

**Definition:**
{% highlight C++ %}
template <typename T>
T absoluteError(T const & expectedVal, T const & measuredVal)
{% endhighlight %}


### relativeError

Returns the relative error between the expected value and the measured value.

**Definition:**
{% highlight C++ %}
template <typename T>
T relativeError(T const & expectedVal, T const & measuredVal)
{% endhighlight %}
