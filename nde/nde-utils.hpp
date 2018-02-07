#ifndef NDE_UTILS
#define NDE_UTILS

#include <vector>
#include <cmath>

namespace nde
{

double maceps()
{
  typedef union {
    long long ll;
    double d;
  } data;

  data s;
  s.d = 1.0;
  s.ll++;
  return s.d - 1.0;
}

template <typename T>
T absoluteError(T const& expectedVal, T const& measuredVal)
{
  return expectedVal - measuredVal;
}

template <typename T>
T relativeError(T const& expectedVal, T const& measuredVal)
{
  return absoluteError(expectedVal, measuredVal) / expectedVal;
}

template <typename T>
bool allclose(std::vector<T> const & a, std::vector<T> const & b, T tolerance)
{
  for (auto i = 0u; i < a.size(); ++i)
  {
    if (std::abs(a[i]-b[i]) > tolerance)
    {
      return false;
    }
  }
  return true;
}

template <typename Num, typename T>
Num factorial(T n)
{
  std::vector<Num> v(n);
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.begin(), v.end(), 1, std::multiplies<Num>());
}

template <typename T>
T binomial(T const & n, T const & k)
{
  return factorial(n)/(factorial(k)*factorial(n-k));
}


} // namespace nde


#endif
