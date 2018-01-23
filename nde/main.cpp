#include "nde.hpp"
#include <iostream>

int main()
{
  std::cout << nde::logistic(2.0, 1.4, 2.0, 10.0) << std::endl;
  std::cout << nde::solcc(1.0, 0.0, 2.0, 3.0, -2.0, 3.0).value() << std::endl;
}
