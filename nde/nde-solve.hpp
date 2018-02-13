#ifndef NDE_SOLVE
#define NDE_SOLVE

#include <cmath>
#include <complex>
#include <functional>
#include <numeric>
#include <iostream>
#include "nde-utils.hpp"
#include "nde-matrix.hpp"
#include "nde-functional.hpp"

namespace nde
{

template <typename Time,
          typename Num,
          typename Param1,
          typename Param2>
std::function<Num(Time)> logistic(
    Num    const& p0,
    Param1 const& a, 
    Param2 const& b);

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
    Param3 const& c);

double const h_DIF = 0.000001;

template <typename Num, typename T, typename N, typename F>
std::function<Num(T)> nthOrderFiniteDif(F const& f, N const & n);

template <typename F, typename T>
auto firstFiniteDif(F const& y, T t);

template <typename F, typename T>
auto secondFiniteDif(F const& y, T t);

template <typename T>
auto colMax(nde::Matrix<T> u, luint columnIndex);

template <typename T>
std::vector<T> jacobiIterate(nde::Matrix<T> a, std::vector<T> b, std::vector<T> x, T tolerance);

template <typename T>
nde::Matrix<T> forwardSub(nde::Matrix<T> b, nde::Matrix<T> l);

template <typename T>
nde::Matrix<T> backSub(nde::Matrix<T> y, nde::Matrix<T> u);

#define thomasSolve tridiagonalSolve

template <typename T>
nde::Matrix<T> tridiagonalSolve(nde::Matrix<T> a, nde::Matrix<T> b);

template <typename T>
nde::Matrix<T> gaussElim(nde::Matrix<T> a, nde::Matrix<T> b);

template <typename T, typename Num>
nde::Matrix<Num> fdcoeffV(luint k, T xbar, nde::Matrix<Num> x);

template <typename T, typename F>
nde::Matrix<T> elliptic(F const & f, T a, T b, T ua, T ub);

template <typename T, typename F>
nde::Matrix<T> ellipticKx(F const & f, T a, T b, T ua, T ub);

/*
template <typename T>
T powerIterate(nde::Matrix<T> a, luint const & MAX_ITERS)
{

}
*/

} // namespace nde

#endif
