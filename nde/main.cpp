#include <iostream>
#include "nde.hpp"

int main()
{
//  std::cout << "Problem 1\n";
//  /* Problem 1 */
//  nde::Matrix<double> b {
//    {3, 9, 5},
//    {7, 2, 4},
//    {6, 8, 1}
//  };
//
//  std::cout << nde::matrix1Norm(b) << std::endl;
//  std::cout << nde::matrixInfNorm(b) << std::endl;
//
//  std::cout << "Problem 2\n";
//  /* Problem 2 */
//  auto a = nde::hilbert<double>(5);
//  std::cout << nde::powerIterate(a, 10) << std::endl;
//
//  std::cout << "Problem 3\n";
//  /* Problem 3 */
///*  for (*/luint i = 10; /*i <= 10000; i *= 10)*/
//  {
//    auto c = nde::tridiagonal<double>(i, 1, -2, 1);
//    std::cout << nde::powerIterate(a, 10) << std::endl;
//  }
//
//
  std::cout << "Problem 4\n";
  /* Problem 4 */
  auto d = nde::tridiagonal<double>(3, 1, -2, 1);
  std::cout << nde::inverseIterate(d, 1) << std::endl;

}
