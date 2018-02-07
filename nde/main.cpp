#include "nde.hpp"
#include <iostream>

int main()
{
  nde::Matrix<double> a { 
    { 1, 1, 1 },
    { 2, 3, 7 },
    { 1, 3, -2}
  };

  nde::Matrix<double> b { {3}, {0}, {17} };

  std::cout << nde::gaussElim(a, b) << std::endl;

  



  /*
  auto const y = nde::logistic<double>(2.0, 1.4, 2.0);
  auto const f = nde::solcc<double>(1.0, 0.0, 2.0, 3.0, -2.0);

  std::cout << y(10.0) << std::endl;
  std::cout << f(3.0) << std::endl;
  std::cout << nde::factorial<int>(4) << std::endl;

  nde::Matrix<int> m { 
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 } 
  };

  nde::Matrix<int> a { 
     { 2, 2, 2 },
     { 2, 2, 2 },
     { 2, 2, 2 } 
  };

  std::cout << (m + a) << std::endl;
  std::cout << (m - m) << std::endl;

  nde::Matrix<int> p { 
     { 1, 2, 3 },
     { 1, 2, 3 } 
  };

  nde::Matrix<int> q { 
     { 4, 5, 6 },
     { 4, 5, 6 },
     { 4, 5, 6 } 
  };

  std::cout << (p * q) << std::endl;
  */



}
