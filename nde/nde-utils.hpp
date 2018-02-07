#ifndef NDE_UTILS
#define NDE_UTILS

#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <iterator>

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
Num factorial(T const & n)
{
  std::vector<Num> v(n);
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.begin(), v.end(), 1, std::multiplies<Num>());
}

template <typename T, typename U>
T binomial(T const & n, U const & k)
{
  return factorial<T>(n)/(factorial<T>(k)*factorial<T>(n-k));
}

template <typename T, typename F>
std::vector<T> map(F const & f, std::vector<T> v)
{
  std::vector<T> ret;
  std::transform(v.begin(), v.end(), std::back_inserter(ret), f);
  return ret;
}


} // namespace nde


#endif
