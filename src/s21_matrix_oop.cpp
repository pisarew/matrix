//
// Created by Глеб Писарев on 23.08.2023.
//

#include "s21_matrix_oop.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

S21Matrix::S21Matrix() : rows_(3), cols_(3) { CreateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; ++i)
    std::copy_n(other.matrix_[i], cols_, matrix_[i]);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::DeleteMatrix() {
  for (int i = 0; i < rows_; ++i) delete[] matrix_[i];
  delete[] matrix_;
}

void S21Matrix::CreateMatrix() {
  if (rows_ < 0 || cols_ < 0) throw std::invalid_argument("error");
  matrix_ = new double *[rows_] {};
  try {
    for (int i = 0; i < rows_; ++i) matrix_[i] = new double[cols_]{};
  } catch (...) {
    if (matrix_) DeleteMatrix();
    throw;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (round(matrix_[i][j] * 1000) / 1000 !=
          round(other.matrix_[i][j] * 1000) / 1000)
        return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("different matrix dimensions");
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("different matrix dimensions");
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  auto result_matrix = S21Matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.cols_; ++j)
      result_matrix.matrix_[i][j] = MulRowOnCol(other, i, j);
  *this = result_matrix;
}

double S21Matrix::MulRowOnCol(const S21Matrix &other, int row,
                              int col) noexcept {
  double result = 0;
  for (int i = 0; i < cols_; ++i)
    result += matrix_[row][i] * other.matrix_[i][col];
  return result;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix transpose_matrix{cols_, rows_};
  for (int i = 0; i < cols_; ++i)
    for (int j = 0; j < rows_; ++j)
      transpose_matrix.matrix_[i][j] = matrix_[j][i];
  return transpose_matrix;
}

int sign(int i) noexcept { return i % 2 == 0 ? 1 : -1; }

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::runtime_error("the matrix is not square");
  S21Matrix compliments(rows_, cols_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      compliments.matrix_[i][j] = sign(i + j) * GetMinor(*this, (int)i, (int)j);
  return compliments;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::runtime_error("the matrix is not square");
  if (rows_ == 1) return matrix_[0][0];
  double result = 0;
  for (int i = 0; i < rows_; ++i)
    result += sign(i) * matrix_[0][i] * GetMinor(*this, 0, (int)i);
  return result;
}

S21Matrix S21Matrix::CreateSubMatrix(S21Matrix matrix, int row, int col) {
  int n = matrix.rows_ - 1;
  int sub_j, sub_i = 0;
  auto sub_matrix = S21Matrix(n, n);
  for (int i = 0; i < matrix.rows_; ++i) {
    if (i == row) continue;
    sub_j = 0;
    for (int j = 0; j < matrix.rows_; ++j) {
      if (j != col) {
        sub_matrix.matrix_[sub_i][sub_j] = matrix.matrix_[i][j];
        ++sub_j;
      }
    }
    ++sub_i;
  }
  return sub_matrix;
}

double S21Matrix::GetMinor(S21Matrix matrix, int row, int col) {
  if (matrix.rows_ == 1) return matrix.matrix_[0][0];
  double res = 0;
  auto sub_matrix = CreateSubMatrix(matrix, row, col);
  if (sub_matrix.rows_ == 1) return sub_matrix.matrix_[0][0];
  for (int i = 0; i < matrix.rows_ - 1; ++i)
    res += sign(i) * sub_matrix.matrix_[0][i] * GetMinor(sub_matrix, 0, i);
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) throw std::runtime_error("matrix determinant is 0");
  return CalcComplements().Transpose() * (1 / det);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  auto result = S21Matrix(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  auto result = S21Matrix(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const noexcept {
  auto result = S21Matrix(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  auto result = S21Matrix(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) &noexcept {
  if (this == &other) return *this;
  S21Matrix tmp = other;
  *this = std::move(tmp);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) &noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  std::swap(matrix_, other.matrix_);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) & {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) & {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) & {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) & {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || i < 0 || j >= cols_ || j < 0)
    throw std::invalid_argument("index is outside the matrix");
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || i < 0 || j >= cols_ || j < 0)
    throw std::invalid_argument("index is outside the matrix");
  return matrix_[i][j];
}

double S21Matrix::GetRows() const { return rows_; }

double S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 0) throw std::invalid_argument("incorrect rows");
  if (rows == rows_) return;
  auto new_matrix = S21Matrix(rows, cols_);
  if (rows > rows_) {
    for (int i = 0; i < rows_; ++i)
      std::copy_n(matrix_[i], cols_, new_matrix.matrix_[i]);
  } else {
    for (int i = 0; i < rows; ++i)
      std::copy_n(matrix_[i], cols_, new_matrix.matrix_[i]);
  }
  *this = new_matrix;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) throw std::invalid_argument("incorrect cols");
  if (cols == cols_) return;
  auto new_matrix = S21Matrix(rows_, cols);
  if (cols > cols_) {
    for (int i = 0; i < rows_; ++i)
      std::copy_n(matrix_[i], cols_, new_matrix.matrix_[i]);
  } else {
    for (int i = 0; i < rows_; ++i)
      std::copy_n(matrix_[i], cols, new_matrix.matrix_[i]);
  }
  *this = new_matrix;
}
