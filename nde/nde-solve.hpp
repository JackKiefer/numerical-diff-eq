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

double const h_DIF = 0.000001;

template <typename Num, typename T, typename N, typename F>
std::function<Num(T)> nthOrderFiniteDif(F const& f, N const & n)
{
  return [=](T x){
    Num sum = 0.0;
    Num sign = 1.0;
    for (double i = 0.0; i <= n; ++i)
    {
      sum += sign * binomial(n,i) * f(x+(n/2 - 1)*h_DIF);
      sign *= -1.0;
    }
    return sum;
  };
}

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
auto colMax(nde::Matrix<T> u, luint columnIndex)
{
  std::vector<T> p(0);
  for (auto i = columnIndex; i < u.size(); ++i)
  {
    p.push_back(u[i][columnIndex]);
  }
  return std::max_element(p.begin(), p.end()) - p.begin() + columnIndex;
}


template <typename T>
std::vector<T> jacobiIterate(nde::Matrix<T> a, std::vector<T> b, std::vector<T> x, T tolerance)
{
  const auto MAX_ITERS = 1000;
  auto origX = x;

  for (auto k = 0; k < MAX_ITERS; ++k)
  {
    for (auto i = 0u; i < a.size(); ++i)
    {
      auto sigma = 0;
      for (auto j = 0u; j < a.size(); ++j)
      {
        if (j != i)
        {
          sigma += a[i][j]*x[j];
        }
      }
      x[i] = (b[i]-sigma)/a[i][i];
    }
    if (nde::allclose(origX, x, tolerance))
    {
      break;
    }
  }
  return x;
}

template <typename T>
nde::Matrix<T> forwardSub(nde::Matrix<T> b, nde::Matrix<T> l)
{
  auto y = nde::zeroes<T>(b.size(), b[0].size());

  y[0][0] = b[0][0]/l[0][0];

  for (auto m = 1u; m < y.size(); ++m)
  {
    auto sum = 0.0;
    for (auto i = 0u; i < m; ++i)
    {
      sum += l[m][i]*y[i][0];
    }
    y[m][0] = (b[m][0] - sum)/l[m][m];
  }
  return y;
}

template <typename T>
nde::Matrix<T> backSub(nde::Matrix<T> y, nde::Matrix<T> u)
{
  std::reverse(y.begin(), y.end());
  std::reverse(u.begin(), u.end());
  for (auto && e : u)
  {
    std::reverse(e.begin(), e.end());
  }
  auto res = forwardSub(y,u);
  std::reverse(res.begin(), res.end());
  return res;
}

#define thomasSolve tridiagonalSolve

template <typename T>
nde::Matrix<T> tridiagonalSolve(nde::Matrix<T> a, nde::Matrix<T> b)
{
  a[0][1] = a[0][1] / a[0][0];
  for (auto i = 1u; i < a.size() - 1; ++i)
  {
    auto ai = a[i][i-1];
    auto bi = a[i][i];
    auto ci = a[i][i+1];
    a[i][i+1] = ci/(bi-(ai*a[i-1][i]));
  }

  b[0][0] = b[0][0] / a[0][0];
  for (auto i = 1u; i < b.size(); ++i)
  {
    auto ai = a[i][i-1];
    auto bi = a[i][i];
    auto ci1 = a[i-1][i];
    b[i][0] = (b[i][0] - (ai*b[i-1][0]))/(bi - (ai*ci1));
  }
  return backSub(b, a); 
}

template <typename T>
nde::Matrix<T> gaussElim(nde::Matrix<T> a, nde::Matrix<T> b)
{
  auto m = a.size() - 1; // Largest index
  auto u = a; 
  auto l = nde::identityMatrix<T>(m + 1);
  auto p = l;

  for (auto k = 0u; k <= m - 1; ++k)
  {
    auto pivotRow = nde::colMax(u, k + 1); 
    u = nde::rowSwap(u,pivotRow,k);
    l = nde::rowSwap(l,(int)k,(int)pivotRow,0,(int)k-1);
    p = nde::rowSwap(p,pivotRow,k);
    for (auto elimRow = k + 1; elimRow <= m; ++elimRow)
    {
      l[elimRow][k] = u[elimRow][k]/u[k][k];
      u = nde::rowEliminate(u, k, k, elimRow);
    }
  }

  auto y = forwardSub(p * b, l);
  return backSub(y,u);
}

template <typename T, typename Num>
nde::Matrix<Num> fdcoeffV(luint k, T xbar, nde::Matrix<Num> x)
{
  auto n = x.size();
  auto a = nde::ones<T>(n,n);
  auto xrow = x - xbar;
  for (auto i = 1u; i < n; ++i)
  {
    a[i] = nde::map([=](T t){ return std::pow(t,i-1)/nde::factorial<T>(i-1); }, xrow)[0];
  }
  auto b = zeroes<T>(n,1);
  b[k+1] = b[k+1] + 1;

  return nde::gaussElim(a,b);
}

template <typename T, typename F>
nde::Matrix<T> elliptic(F const & f, T a, T b, T ua, T ub)
{
  auto n = b - a + 1;
  auto v = nde::zeroes<T>(n,1);

  v[0][0] = f(a) - ua;
  for (auto i = 1u; i < n - 1; ++i)
  {
    v[i][0] = h_DIF * h_DIF * f(a + i);
  }
  v[n - 1][0] = f(b) - ub;
  return nde::thomasSolve(nde::tridiagonal(n, 1.0, -2.0, 1.0), v);
}

} // namespace nde

#endif
