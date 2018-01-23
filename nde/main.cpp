#include "nde.hpp"
#include <iostream>

int main()
{
  auto const y = nde::logistic<double>(2.0, 1.4, 2.0);
  auto const f = nde::solcc<double>(1.0, 0.0, 2.0, 3.0, -2.0);

  std::cout << y(10.0) << std::endl;
  std::cout << f(3.0) << std::endl;
}
