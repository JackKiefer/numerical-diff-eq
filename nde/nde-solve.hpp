#ifndef NDE_SOLVE
#define NDE_SOLVE

#include <cmath>
#include <complex>
#include <functional>
#include <numeric>
#include <iostream>
#include "nde-matrix.hpp"

namespace nde
{

template <typename Num, typename T>
Num factorial(T n)
{
  std::vector<Num> v(n);
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.begin(), v.end(), 1, std::multiplies<Num>());
}

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2>
std::function<Num(Time)> logistic(
    Num    const& p0,
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
    Num    const& y0,
    Num    const& v0,
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
auto colMax(nde::Matrix<T> u, unsigned int columnIndex)
{
  std::vector<T> p(0);
  for (auto i = columnIndex; i < u.size(); ++i)
  {
    p.push_back(u[i][columnIndex]);
  }
  return std::max_element(p.begin(), p.end()) - p.begin() + columnIndex;
}

template <typename T>
void gaussElim(nde::Matrix<T> a)
{
  auto m = a.size() - 1; // Largest index
  auto u = a; 
  auto l = nde::identityMatrix<T>(m + 1);
  auto p = l;

  for (auto k = 0u; k <= m - 1; ++k)
  {
    auto pivotRow = nde::colMax(u, k + 1); 
    u = nde::rowSwap(u,pivotRow,k);
    l = nde::rowSwap(l,k,pivotRow,0,k-1);
    p = nde::rowSwap(p,pivotRow,k);
    for (auto elimRow = k + 1; elimRow <= m; ++elimRow)
    {
      l[elimRow][k] = u[elimRow][k]/u[k][k];
      u = nde::rowEliminate(u, k, k, elimRow);
    }
  }


  /*
  for (auto k = 0u; k <= m - 1; ++k)
  {
    auto i = nde::colMax(u, k);
    u = nde::rowSwap(u,k,i,k,m);
    l = nde::rowSwap(l,k,i,0,k-1);
    p = nde::rowSwap(p,k,i);
    for (auto j = k + 1; j <= m; ++j)
    {
      l[j][k] = u[j][k]/u[k][k];
      for (auto z = k; z <= m; ++z)
      {
        u[j][z] = u[j][z] - l[j][k]*u[k][z];
      }
    }
  }
  */
  
  std::cout << "P: \n" << p << "\n";
  std::cout << "A: \n" << a << "\n";
  std::cout << "L: \n" << l << "\n";
  std::cout << "U: \n" << u << "\n";
}

} // namespace nde

#endif
