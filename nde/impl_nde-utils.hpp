#ifndef NDE_UTILL_IMPL
#define NDE_UTILL_IMPL

#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <iterator>
#include <iostream>
#include <random>
#include <climits>
#include "nde-solve.hpp"
#include "nde-matrix.hpp"
#include "nde-functional.hpp"

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
T getRand(T s, T e)
{
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_int_distribution<T> dist(s,e);
  return dist(engine);
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

template <typename T, typename P>
T pNorm(std::vector<T> const & x, P const & p)
{
  return std::pow(nde::sum(nde::map( [=](T xi){return std::pow(std::abs(xi), p);}, x)), 1.0/p );
}
 
template <typename T>
T infNorm(std::vector<T> const & v)
{
  return nde::max(nde::map(farg(std::abs), v));
}


} // namespace nde


#endif
