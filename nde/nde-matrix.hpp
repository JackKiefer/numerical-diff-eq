#ifndef NDE_MATRIX
#define NDE_MATRIX

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
nde::Matrix<T> identityMatrix(luint m);

template <typename T>
nde::Matrix<T> nMatrix(luint rows, luint cols, T n);

template <typename T>
nde::Matrix<T> zeroes(luint rows, luint cols);

template <typename T>
nde::Matrix<T> ones(luint rows, luint cols);

template <typename T>
nde::Matrix<T> randMatrix(luint, luint, int, int);

template <typename T>
nde::Matrix<T> hilbert(luint size);

template <typename T>
nde::Matrix<T> tridiagonal(luint n, T subdiag, T diag, T superdiag, T nondiag);

template <typename T>
nde::Matrix<T> tridiagonal(luint n, T subdiag, T diag, T superdiag);

template <typename T>
nde::Matrix<T> rowSwap(nde::Matrix<T> u, int rowa, int rowb, int colstart, int colend);

template <typename T>
nde::Matrix<T> rowSwap(nde::Matrix<T> u, luint rowa, luint rowb);

template <typename T>
nde::Matrix<T> rowScalarAdd(nde::Matrix<T> u, T scalar, luint scalarRow, luint addendRow);

template <typename T>
nde::Matrix<T> rowEliminate(nde::Matrix<T> u, luint pivotRow, luint pivotCol, luint elimRow);

template <typename T>
nde::Matrix<T> columnVector(std::vector<T> const & x);

template <typename T>
nde::Vector<T> rowVector(nde::Matrix<T> a);

template <typename T, typename F>
nde::Matrix<T> matrixMap(F const & f, nde::Matrix<T> m);

template <typename T>
T matrixInfNorm(nde::Matrix<T> a);

template <typename T>
T matrix1Norm(nde::Matrix<T> a);

template <typename T>
nde::Matrix<T> inverse(nde::Matrix<T> a);

template <typename T>
nde::Matrix<T> linspace(T xmin, T xmax, luint size);

template <typename T>
nde::Matrix<T> meshgridX(nde::Matrix<T> lin);

template <typename T>
nde::Matrix<T> blockDiagram(nde::Matrix<nde::Matrix<T>> pattern);
} // namespace nde
#endif
