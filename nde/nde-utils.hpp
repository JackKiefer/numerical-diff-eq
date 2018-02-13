#ifndef NDE_UTILS
#define NDE_UTILS

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

double maceps();

template <typename T>
T getRand(T s, T e);

template <typename T>
T absoluteError(T const& expectedVal, T const& measuredVal);

template <typename T>
T relativeError(T const& expectedVal, T const& measuredVal);

template <typename T>
bool allclose(std::vector<T> const & a, std::vector<T> const & b, T tolerance);

template <typename Num, typename T>
Num factorial(T const & n);

template <typename T, typename U>
T binomial(T const & n, U const & k);

template <typename T, typename P>
T pNorm(std::vector<T> const & x, P const & p);
 
template <typename T>
T infNorm(std::vector<T> const & v);


} // namespace nde


#endif
