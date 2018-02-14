#include <iostream>
#include "nde.hpp"

int main()
{
  /* Problem 1 */
  nde::Matrix<double> b {
    {3, 9, 5},
    {7, 2, 4},
    {6, 8, 1}
  };

  std::cout << nde::matrix1Norm(b) << std::endl;
  std::cout << nde::matrixInfNorm(b) << std::endl;

  /* Problem 2 */

  auto a = nde::hilbert<double>(5);
  std::cout << nde::powerIterate(a, 10) << std::endl;

  /* Problem 3 */

}
