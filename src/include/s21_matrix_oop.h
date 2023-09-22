//
// Created by Глеб Писарев on 23.08.2023.
//

#ifndef CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(double num) const noexcept;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other) & noexcept;
  S21Matrix& operator=(S21Matrix&& other) & noexcept;
  S21Matrix& operator+=(const S21Matrix& other) &;
  S21Matrix& operator-=(const S21Matrix& other) &;
  S21Matrix& operator*=(double num) &;
  S21Matrix& operator*=(const S21Matrix& other) &;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

  ~S21Matrix();

  [[nodiscard]] bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  [[nodiscard]] S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  [[nodiscard]] double GetRows() const;
  [[nodiscard]] double GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_, cols_;
  double** matrix_ = nullptr;
  void CreateMatrix();
  void DeleteMatrix();
  double MulRowOnCol(const S21Matrix& other, int row, int col) noexcept;
  static double GetMinor(S21Matrix matrix, int row, int col);
  static S21Matrix CreateSubMatrix(S21Matrix matrix, int row, int col);
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H