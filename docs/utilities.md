# Utilities

| Routine | Description |
|---------|-------------|
| [maceps](#maceps)  | Calculate [machine epsilon](https://en.wikipedia.org/wiki/Machine_epsilon) |
| [absoluteError](#absoluteError) | Calculate absolute error between two numbers |
| [relativeError](#relativeError) | Calculate relative error between two numbers |

### maceps

**Definition:**
{% highlight C++ %}
double maceps()
{% endhighlight %}

**Description:**
Calculates machine epsilon

### absoluteError

**Definition:**
{% highlight C++ %}
template <typename T>
T absoluteError(T const & expectedVal, T const & measuredVal)
{% endhighlight %}

**Description:**
Calculates absolute error between the expected value and the measured value


### relativeError

**Definition:**
{% highlight C++ %}
template <typename T>
T relativeError(T const & expectedVal, T const & measuredVal)
{% endhighlight %}

**Description:**
Calculates relative error between the expected value and the measured value
