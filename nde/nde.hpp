#ifndef NUMERICAL_DIFFEQ
#define NUMERICAL_DIFFEQ

#include <cmath>
#include <complex>
#include <functional>
#include <optional>

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

double const h_DIF = 0.00001;

template <typename F, typename T>
auto firstFiniteDif(F const& y, T t)
{
  return (y(t + h_DIF) - y(t - h_DIF)) / (2.0 * h_DIF);
}

template <typename F, typename T>
auto secondFiniteDif(F const& y, T t)
{
  return (y(t + h_DIF) - 2.0 * y(t) + y(t - h_DIF)) / (h_DIF * h_DIF);
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

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2>
std::function<Num(Time)> logistic(
    Num const& p0,
    Param1 const& a, 
    Param2 const& b)
{
  return [=](Time t) {
    return (a / (((a / p0) - b) * exp((-a) * t) + b));
  };
}

/* Second-Order, Linear, Constant Coefficient:
 * ay'' + by' + cy = f(t) */
template <typename Time,
          typename Num,
          typename Param1,
          typename Param2,
          typename Param3>
std::function<Num(Time)> solcc(
    Num const& y0,
    Num const& v0,
    Param1 const& a,
    Param2 const& b,
    Param3 const& c)
{
  /* Characteristic roots from quadratic formula */
  std::complex<Num> const radical = (b * b) - (4.0 * a * c);
  auto const r1 = (-b + sqrt(radical)) / (2.0 * a);
  auto const r2 = (-b - sqrt(radical)) / (2.0 * a);

  /* Separate solutions if roots are the same */
  if (r1 == r2)
  {
    auto const c = v0 - (r1 * y0);
    return [=](Time t) {
      return (y0 * exp(r1 * t) + (c * t * exp(r1 * t))).real();
    };
  }
  else
  {
    auto const c1 = (v0 - (r2 * y0)) / (r1 - r2);
    auto const c2 = ((r1 * y0) - v0) / (r1 - r2);
    return [=](Time t) {
      return (c1 * exp(r1 * t) + c2 * exp(r2 * t)).real();
    };
  }
}

} // namespace nde

#endif
