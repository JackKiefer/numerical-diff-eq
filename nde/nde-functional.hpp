#ifndef NDE_FUNCTIONAL
#define NDE_FUNCTIONAL
#include <vector>

namespace nde {

template <typename T, typename F>
std::vector<T> map(F const & f, std::vector<T> v)
{
  std::vector<T> ret;
  std::transform(v.begin(), v.end(), std::back_inserter(ret), f);
  return ret;
}

template <typename T>
T sum(std::vector<T> const & v)
{
  return std::accumulate(v.begin(), v.end(), 0.0);
}

template <typename T>
T max(std::vector<T> const & v)
{
  return *std::max_element(v.begin(), v.end());  
}

} // namespace nde


#endif
