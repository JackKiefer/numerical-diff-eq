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

} // namespace nde


#endif
