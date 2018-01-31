#ifndef NDE_UTILS
#define NDE_UTILS

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
} // namespace nde


#endif
