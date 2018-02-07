#ifndef NDE_MATRIX
#define NDE_MATRIX

#include <vector>
#include <iomanip>
#include <string>
#include <exception>

namespace nde {

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
nde::Matrix<T> identityMatrix(unsigned int m)
{
  nde::Matrix<T> a(m, std::vector<T>(m, 0));
  for (auto i = 0u; i < m; ++i)
  {
    a[i][i] = 1;
  }
  return a;
}

template <typename T>
nde::Matrix<T> rowSwap(nde::Matrix<T> u, int rowa, int rowb, int colstart, int colend)
{
  auto temp = u[rowa];
  for (auto i = colstart; i <= colend; ++i)
  {
    u[rowa][i] = u[rowb][i];
    u[rowb][i] = temp[i];
  }
  return u;
}

template <typename T>
nde::Matrix<T> rowSwap(nde::Matrix<T> u, int rowa, int rowb)
{
  return rowSwap(u, rowa, rowb, 0, u[0].size() - 1);
}

template <typename T>
nde::Matrix<T> rowScalarAdd(nde::Matrix<T> u, T scalar, int scalarRow, int addendRow)
{
  for (auto col = 0u; col < u[0].size(); ++col)
  {
    u[addendRow][col] += (scalar * u[scalarRow][col]);
  }
  return u;
}

template <typename T>
nde::Matrix<T> rowEliminate(nde::Matrix<T> u, int pivotRow, int pivotCol, int elimRow)
{
  auto scalar = -u[elimRow][pivotCol] / u[pivotRow][pivotCol];
  return rowScalarAdd(u, scalar, pivotRow, elimRow);
}

template <typename T>
nde::Matrix<T> columnVector(std::vector<T> const & x)
{
  nde::Matrix<T> a;
  for (auto && e : x)
  {
    a.push_back(std::vector<T>(1,e));
  }
  return a;
}

} // namespace nde

#define EXCEPT_MATRIX_SIZE throw std::out_of_range("Matrix sizes must agree");

#define BinaryOp(opname, OP)\
template <typename T>\
nde::Matrix<T> opname(nde::Matrix<T> const & a, nde::Matrix<T> const & b)\
{\
  if (a.size() != b.size())\
  {\
      EXCEPT_MATRIX_SIZE\
  }\
  nde::Matrix<T> c(a.size(), std::vector<T>(a[0].size()));\
  for (auto i = 0u; i < a.size(); ++i)\
  {\
    if (a[i].size() != b[i].size())\
    {\
      EXCEPT_MATRIX_SIZE\
    }\
    for (auto j = 0u; j < a[i].size(); ++j)\
    {\
      auto x = a[i][j] OP b[i][j];\
      c[i][j] = x;\
    }\
  }\
  return c;\
}\

BinaryOp(operator+, +)
BinaryOp(operator-, -)

template <typename T>
T componentMul(nde::Matrix<T> const & a, nde::Matrix<T> const & b, int i, int j)
{
  T sum = 0;
  for (auto k = 0u; k < b.size(); ++k)
  {
    sum += a[i][k] * b[k][j]; 
  }
  return sum;
}

template <typename T>
nde::Matrix<T> operator*(nde::Matrix<T> const & a, nde::Matrix<T> const & b)
{
  auto m = a[0].size();
  auto n = a.size();
  auto p = b[0].size();

  if (m != b.size())
  {
    EXCEPT_MATRIX_SIZE
  }

  nde::Matrix<T> c(n, std::vector<T>(p));

  for (auto i = 0u; i < n; ++i)
  {
    for (auto j = 0u; j < m; ++j)
    {
      c[i][j] = componentMul(a, b, i, j);
    }
  }
  return c;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, nde::Matrix<T> const & m)
{
  for (auto i = 0u; i < m.size(); ++i)
  {
    for (auto j = 0u; j < m[i].size(); ++j)
    {
      o << std::setw(11) << std::setprecision(4) << (m[i][j]);
    }
    if (i < m.size() - 1)
    {
      o << std::endl;
    }
  }
  return o;
}


#endif
