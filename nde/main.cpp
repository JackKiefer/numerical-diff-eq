#include <iostream>
#include "nde.hpp"

int main()
{
#if 1
  std::cout << "Problem 1\n";
  /* Problem 1 */
  nde::Matrix<double> b {
    {3, 9, 5},
    {7, 2, 4},
    {6, 8, 1}
  };

  std::cout << nde::matrix1Norm(b) << std::endl;
  std::cout << nde::matrixInfNorm(b) << std::endl;

  std::cout << "Problem 2\n";
  /* Problem 2 */
  auto a = nde::hilbert<double>(5);
  std::cout << nde::powerIterate(a, 10) << std::endl;

  std::cout << "Problem 3\n";
  /* Problem 3 */
  for (luint i = 10; i <= 10000; i *= 10)
  {
   auto c = nde::tridiagonal<double>(3, 1, -2, 1);
   std::cout << nde::powerIterate(c, 10) << std::endl;
  }


  std::cout << "Problem 4\n";
  /* Problem 4 */
  auto d = nde::tridiagonal<double>(3, 1, -2, 1);
  std::cout << nde::inverseIterate(d, 10) << std::endl;
#endif

  /* Params */
  unsigned long n = 5;
  double Te = 100;

  /* Function */
  auto nblock = n - 2;
  auto b = nde::tridiagonal<double>(nblock, 1.0, -4.0, 1.0);
  auto i = nde::identityMatrix<double>(nblock);
  auto z = nde::zeroes<double>(nblock,nblock);
  auto a = nde::blockDiagram(nde::tridiagonal<nde::Matrix<double>>(nblock, i, b, i, z)) * -1.0;
  auto bs = nde::zeroes<double>(nblock*nblock,1);
  for (auto i = 0u; i < nblock; ++i)
  {
    bs[i][0] = Te;
  }

  auto u = nde::gaussElim(a, bs);
  return u;

  quickprint(u)

  


}
