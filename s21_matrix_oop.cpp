//
// Created by Глеб Писарев on 23.08.2023.
//

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::DeleteMatrix() {
  for (size_t i = 0; i < rows_; ++i) delete[] matrix_[i];
  delete[] matrix_;
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  for (size_t i = 0; i < rows_; ++i) matrix_[i] = new double[cols_];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("different matrix dimensions");
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("different matrix dimensions");
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::runtime_error(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  auto **result_matrix = new double *[rows_];
  for (size_t i = 0; i < rows_; ++i) result_matrix[i] = new double[other.cols_];
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.cols_; ++j)
      result_matrix[i][j] = MulRowOnCol(other, i, j);
}

double S21Matrix::MulRowOnCol(const S21Matrix &other, int row, int col) {
  double result = 0;
  for (size_t i = 0; i < cols_; ++i)
    result += matrix_[row][i] * other.matrix_[i][col];
  return 0;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transpose_matrix(cols_, rows_);
  for (size_t i = 0; i < cols_; ++i)
    for (size_t j = 0; j < rows_; ++j)
      transpose_matrix.matrix_[i][j] = matrix_[j][i];
  return transpose_matrix;
}

int sign(size_t i) { return i % 2 == 0 ? 1 : -1; }

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::runtime_error("the matrix is not square");
  S21Matrix compliments(rows_, cols_);
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j)
      compliments.matrix_[i][j] =
          sign(i + j) * GetMinor(matrix_, (int)i, (int)j, rows_);
  return compliments;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::runtime_error("the matrix is not square");
  if (rows_ == 1) return matrix_[0][0];
  double result = 0;
  for (size_t i = 0; i < rows_; ++i)
    result += sign(i) * matrix_[0][i] * GetMinor(matrix_, 0, (int)i, rows_);
  return result;
}

double **S21Matrix::CreateSubMatrix(double **matrix, int len, int row,
                                    int col) {
  int n = len - 1;
  int sub_j = 0, sub_i = 0;
  auto **sub_matrix = new double *[n];
  for (size_t i = 0; i < n; ++i) sub_matrix[i] = new double[n];
  for (int i = 0; i < len && i != row; ++i) {
    for (int j = 0; j < len; ++j) {
      if (j != col) {
        sub_matrix[sub_i][sub_j] = matrix[i][j];
        ++sub_j;
      }
    }
    ++sub_i;
  }
  return sub_matrix;
}

double S21Matrix::GetMinor(double **matrix, int row, int col, int n) {
  if (n == 1) return matrix[0][0];
  double res = 0;
  auto **sub_matrix = CreateSubMatrix(matrix, n, row, col);
  if ((n - 1) == 1) {
    res = sub_matrix[0][0];
  } else {
    for (int i = 0; i < n - 1; ++i) {
      res += sign(i) * sub_matrix[0][i] * GetMinor(sub_matrix, 0, i, n - 1);
    }
  }
  for (int i = 0; i < n - 1; ++i) delete[] sub_matrix[i];
  delete[] sub_matrix;
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) throw std::runtime_error("matrix determinant is 0");
  S21Matrix inverse = CalcComplements().Transpose();
  inverse.MulNumber(1 / det);
  return inverse;
}

std::unique_ptr<S21Matrix> S21Matrix::operator+(const S21Matrix &other) {
  auto result = std::make_unique<S21Matrix>(*this);
  result->SumMatrix(other);
  return result;
}

std::unique_ptr<S21Matrix> S21Matrix::operator-(const S21Matrix &other) {
  auto result = std::make_unique<S21Matrix>(*this);
  result->SubMatrix(other);
  return result;
}

std::unique_ptr<S21Matrix> S21Matrix::operator*(double num) {
  auto result = std::make_unique<S21Matrix>(*this);
  result->MulNumber(num);
  return result;
}

std::unique_ptr<S21Matrix> S21Matrix::operator*(const S21Matrix &other) {
  auto result = std::make_unique<S21Matrix>(*this);
  result->MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || i < 0 || j >= cols_ || j < 0)
    throw std::runtime_error("index is outside the matrix");
  return matrix_[i][j];
}
