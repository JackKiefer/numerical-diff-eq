#ifndef NUMERICAL_DIFFEQ
#define NUMERICAL_DIFFEQ

#include <cmath>
#include <complex>
#include <optional>

namespace nde {

double maceps()
{
  typedef union
  {
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
auto firstFiniteDif(F const & y, T t)
{
  return ( y(t+h_DIF) - y(t-h_DIF) ) / (2.0*h_DIF);
}

template <typename F, typename T>
auto secondFiniteDif(F const & y, T t)
{
  return ( y(t+h_DIF) - 2.0*y(t) + y(t-h_DIF) ) / (h_DIF * h_DIF);
}

template <typename T>
T absoluteError(T const & expectedVal, T const & measuredVal)
{
  return expectedVal - measuredVal;
}

template <typename T>
T relativeError(T const & expectedVal, T const & measuredVal)
{
  return absoluteError(expectedVal, measuredVal) / expectedVal;
}

template 
< typename Time, 
  typename Num, 
  typename Param1, 
  typename Param2
  >
Num logistic(Num const & p0, Param1 const & a, Param2 const & b, Time const & t)
{
  return a / ( ( (a/p0) - b ) * exp((-a)*t) + b );
}

/* Second-Order, Linear, Constant Coefficient:
 * ay'' + by' + cy = f(t) */
template
< typename Time,
  typename Num,
  typename Param1,
  typename Param2,
  typename Param3
  >
std::optional<std::complex<Num>> solcc(Num y0, Num v0, Param1 a, Param2 b, Param3 c, Time t)
{
  /* Characteristic roots from quadratic formula */
  std::complex<Num> const radical = (b*b)-(4.0*a*c);
  auto const r1 = (-b + sqrt(radical))/(2.0*a);
  auto const r2 = (-b - sqrt(radical))/(2.0*a);

  /* No solution if roots are the same */
  if (r1 == r2)
  {
    return {};
  }

  auto const c1 = ( v0-(r2*y0) ) / ( r1-r2 );
  auto const c2 = ( (r1*y0)-v0 ) / ( r1-r2 );
  return c1*exp(r1*t) + c2*exp(r2*t);
}

} // namespace nde

#endif
