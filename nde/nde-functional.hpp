#ifndef NDE_FUNCTIONAL
#define NDE_FUNCTIONAL

#include <vector>
#include "nde-matrix.hpp"
#include "nde-solve.hpp"
#include "nde-utils.hpp"

#define farg(x) [=](T t){ return x(t); }

namespace nde {

template <typename T, typename F>
std::vector<T> map(F const & f, std::vector<T> v);

template <typename T>
T sum(std::vector<T> const & v);

template <typename T>
T max(std::vector<T> const & v);

} // namespace nde


#endif
