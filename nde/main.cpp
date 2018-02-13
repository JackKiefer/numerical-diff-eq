#include <iostream>
#include "nde.hpp"

int main()
{
  auto a = nde::hilbert<double>(5);
  std::cout << a << std::endl;
  std::cout << a[0][1] << std::endl;

}
