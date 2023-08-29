//
// Created by Глеб Писарев on 23.08.2023.
//

#ifndef CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H

#include <memory>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void CreateMatrix();
  void DeleteMatrix();
  double MulRowOnCol(const S21Matrix &other, int row, int col);
  static double GetMinor(double** matrix, int row, int col, int n);
  static double** CreateSubMatrix(double** matrix, int len, int row, int col);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  std::unique_ptr<S21Matrix> operator+(const S21Matrix& other);
  std::unique_ptr<S21Matrix> operator-(const S21Matrix& other);
  std::unique_ptr<S21Matrix> operator*(double num);
  std::unique_ptr<S21Matrix> operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int i, int j);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
