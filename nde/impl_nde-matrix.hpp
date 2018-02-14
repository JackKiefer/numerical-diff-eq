#ifndef NDE_MATRIL_IMPL
#define NDE_MATRIL_IMPL

#include <vector>
#include <iomanip>
#include <string>
#include <exception>
#include "nde-utils.hpp"
#include "nde-solve.hpp"
#include "nde-functional.hpp"

typedef unsigned long luint;

namespace nde 
{

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Matrix = std::vector<nde::Vector<T>>;

template <typename T>
nde::Matrix<T> identityMatrix(luint m)
{
  nde::Matrix<T> a(m, std::vector<T>(m, 0));
  for (auto i = 0u; i < m; ++i)
  {
    a[i][i] = 1;
  }
  return a;
}

template <typename T>
nde::Matrix<T> nMatrix(luint rows, luint cols, T n)
{
  return nde::Matrix<T>(rows, std::vector<T>(cols, n));
}

template <typename T>
nde::Matrix<T> zeroes(luint rows, luint cols)
{
  return nMatrix<T>(rows, cols, 0.0);
}

template <typename T>
nde::Matrix<T> ones(luint rows, luint cols)
{
  return nMatrix<T>(rows, cols, 1.0);
}

template <typename T>
nde::Matrix<T> randMatrix(luint rows, luint cols, int b, int e)
{
  return nMatrix<T>(rows, cols, getRand<int>(b,e));
}

template <typename T>
nde::Matrix<T> hilbert(luint size)
{
  return nde::matrixMap([](T i, T j){ return 1.0/(i+j+1.0); }, zeroes<T>(size,size));
}

template <typename T>
nde::Matrix<T> tridiagonal(luint n, T subdiag, T diag, T superdiag)
{
  auto a = zeroes<T>(n,n);
  a[0][0] = diag;
  a[0][1] = superdiag;
  for (auto i = 1u; i < n - 1; ++i)
  {
    a[i][i-1] = subdiag;
    a[i][i]   = diag;
    a[i][i+1] = superdiag;
  }
  a[n-1][n-1] = diag;
  a[n-1][n-2] = subdiag;
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
nde::Matrix<T> rowSwap(nde::Matrix<T> u, luint rowa, luint rowb)
{
  return rowSwap(u, (int)rowa, (int)rowb, 0, (int)u[0].size() - 1);
}

template <typename T>
nde::Matrix<T> rowScalarAdd(nde::Matrix<T> u, T scalar, luint scalarRow, luint addendRow)
{
  for (auto col = 0u; col < u[0].size(); ++col)
  {
    u[addendRow][col] += (scalar * u[scalarRow][col]);
  }
  return u;
}

template <typename T>
nde::Matrix<T> rowEliminate(nde::Matrix<T> u, luint pivotRow, luint pivotCol, luint elimRow)
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

template <typename T>
nde::Vector<T> rowVector(nde::Matrix<T> a)
{
  nde::Vector<T> v;
  v.reserve(a.size());
  for (auto && e : a)
  {
    v.push_back(e[0]);
  }
  return v;
}

template <typename T, typename F>
nde::Matrix<T> matrixMap(F const & f, nde::Matrix<T> m)
{
  for (T i = 0; i < T(m.size()); ++i)
  {
    for (T j = 0; j < T(m[0].size()); ++j)
    {
      m[luint(i)][luint(j)] = (T)(f(i,j));
    }
  }
  return m;
}

template <typename T>
T matrixInfNorm(nde::Matrix<T> a)
{
  T maxSum = 0.0;
  for (auto && row : a)
  {
    T rowSum = nde::pNorm(row,1);
    if (rowSum > maxSum)
    {
      maxSum = rowSum;
    }
  }
  return maxSum;
}

template <typename T>
T matrix1Norm(nde::Matrix<T> a)
{
  T maxSum = 0.0;
  /* For each column */
  for (auto j = 0u; j < a[0].size(); ++j)
  {
    T colSum = 0.0;
    /* For each entry in column */
    for (auto i = 0u; i < a.size(); ++i)
    {
      colSum += a[i][j];
    }
    if (colSum > maxSum)
    {
      maxSum = colSum;
    }
  }
  return maxSum;
}

} // namespace nde

#define EXCEPT_SIZE(type) throw std::out_of_range("type sizes must agree");

#define BinaryMatrixOp(OP)\
template <typename T>\
nde::Matrix<T> operator OP (nde::Matrix<T> const & a, nde::Matrix<T> const & b)\
{\
  if (a.size() != b.size())\
  {\
      EXCEPT_SIZE(Matrix)\
  }\
  nde::Matrix<T> c(a.size(), std::vector<T>(a[0].size()));\
  for (auto i = 0u; i < a.size(); ++i)\
  {\
    if (a[i].size() != b[i].size())\
    {\
      EXCEPT_SIZE(Matrix)\
    }\
    for (auto j = 0u; j < a[i].size(); ++j)\
    {\
      auto x = a[i][j] OP b[i][j];\
      c[i][j] = x;\
    }\
  }\
  return c;\
}\

BinaryMatrixOp(+)
BinaryMatrixOp(-)
BinaryMatrixOp(/)

#define BinaryVectorOp(OP)\
template <typename T>\
nde::Vector<T> operator OP (nde::Vector<T> a, nde::Vector<T> const & b)\
{\
  if (a.size() != b.size())\
  {\
    EXCEPT_SIZE(Vector)\
  }\
  for (auto i = 0u; i < a.size(); ++i)\
  {\
    a[i] = a[i] OP b[i];\
  }\
  return a;\
}\

BinaryVectorOp(+)
BinaryVectorOp(-)

#define ConstantVectorOp(OP)\
template <typename T, typename U>\
nde::Vector<T> operator OP (nde::Vector<T> a, U const & c)\
{\
  for (auto&& e : a)\
  {\
    e = e OP c;\
  }\
  return a;\
}\

ConstantVectorOp(*)
ConstantVectorOp(+)
ConstantVectorOp(-)
ConstantVectorOp(/)

#define ConstantMatrixOp(OP)\
template <typename T, typename U>\
nde::Matrix<T> operator OP (nde::Matrix<T> a, U const & c)\
{\
  for (auto&& row : a)\
  {\
    row = row OP c;\
  }\
  return a;\
}\

ConstantMatrixOp(*)
ConstantMatrixOp(+)
ConstantMatrixOp(-)
ConstantMatrixOp(/)


template <typename T>
T componentMul(nde::Matrix<T> const & a, nde::Matrix<T> const & b, luint i, luint j)
{
  T sum = 0.0;
  for (auto k = 0u; k < b.size(); ++k)
  {
    sum += (a[i][k] * b[k][j]); 
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
    EXCEPT_SIZE(Matrix)
  }

  auto c = nde::zeroes<T>(n,p);

  for (auto i = 0u; i < n; ++i)
  {
    for (auto j = 0u; j < p; ++j)
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
    o << "| ";
    for (auto j = 0u; j < m[i].size(); ++j)
    {
      o << std::setw(11) << std::setprecision(4) << (m[i][j]);
    }
    o << " |";
    if (i < m.size() - 1)
    {
      o << std::endl;
    }
  }
  return o;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, nde::Vector<T> const & v)
{
  o << "[ ";
  for (auto&& e : v)
  {
    o << std::setw(11) << std::setprecision(4) << e;
  }
  o << " ] \n";
  return o;
}


#endif
