//
// Created by Глеб Писарев on 17.09.2023.
//

#include "test.h"

#include <stdexcept>

#include "s21_matrix_oop.h"

namespace {
TEST(ModelTest, init_matrix_test_0) {
  S21Matrix matrix = S21Matrix();
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetCols(); ++j) EXPECT_FLOAT_EQ(matrix(i, j), 0);
}

TEST(ModelTest, init_matrix_test_1) {
  S21Matrix matrix = S21Matrix(2, 7);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 7);
  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetCols(); ++j) EXPECT_FLOAT_EQ(matrix(i, j), 0);
}

TEST(ModelTest, init_matrix_test_2) {
  S21Matrix src = S21Matrix();
  for (int i = 0; i < src.GetRows(); ++i)
    for (int j = 0; j < src.GetRows(); ++j) src(i, j) = 100619;
  S21Matrix dst = S21Matrix(src);
  EXPECT_EQ(dst.GetRows(), src.GetRows());
  EXPECT_EQ(dst.GetCols(), src.GetCols());
  EXPECT_TRUE(dst == src);
}

TEST(ModelTest, eq_test_0) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  EXPECT_TRUE(left == right);
}

TEST(ModelTest, eq_test_1) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = 3;

  EXPECT_FALSE(left == right);
}

TEST(ModelTest, move_test_0) {
  S21Matrix right = S21Matrix();
  S21Matrix check = S21Matrix();
  for (int i = 0; i < right.GetRows(); ++i) {
    {
      for (int j = 0; j < right.GetCols(); ++j) {
        right(i, j) = i + j;
        check(i, j) = i + j;
      }
    }
  }
  S21Matrix left = S21Matrix();
  left = right;
  EXPECT_TRUE(left == check);
}

TEST(ModelTest, sum_move_test_0) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 4692.192383;
  left(0, 1) = -5.991882;
  left(0, 2) = 121347;

  left(1, 0) = -629918.12398412;
  left(1, 1) = 313441;
  left(1, 2) = 10565.85;

  left(2, 0) = 51261;
  left(2, 1) = -298084;
  left(2, 2) = -31253.87231111;

  S21Matrix right = S21Matrix();

  right(0, 0) = 21984.811421244;
  right(0, 1) = 51244;
  right(0, 2) = 312;

  right(1, 0) = 6;
  right(1, 1) = -37.92998822;
  right(1, 2) = 4;

  right(2, 0) = 512442;
  right(2, 1) = -2.09921;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = 26677.003804244;
  result(0, 1) = 51238.008118;
  result(0, 2) = 121659;

  result(1, 0) = -629912.12398412;
  result(1, 1) = 313403.07001178;
  result(1, 2) = 10569.85;

  result(2, 0) = 563703;
  result(2, 1) = -298086.09921;
  result(2, 2) = -31256.87231111;

  EXPECT_TRUE((left += right) == result);
}

TEST(ModelTest, sub_move_test_0) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 4692.192383;
  left(0, 1) = -5.991882;
  left(0, 2) = 121347;

  left(1, 0) = -629918.12398412;
  left(1, 1) = 313441;
  left(1, 2) = 10565.85;

  left(2, 0) = 51261;
  left(2, 1) = -298084;
  left(2, 2) = -31253.87231111;

  S21Matrix right = S21Matrix();

  right(0, 0) = 21984.811421244;
  right(0, 1) = 51244;
  right(0, 2) = 312;

  right(1, 0) = 6;
  right(1, 1) = -37.92998822;
  right(1, 2) = 4;

  right(2, 0) = 512442;
  right(2, 1) = -2.09921;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = -17292.619038244;
  result(0, 1) = -51249.991882;
  result(0, 2) = 121035;

  result(1, 0) = -629924.12398412;
  result(1, 1) = 313478.92998822;
  result(1, 2) = 10561.85;

  result(2, 0) = -461181;
  result(2, 1) = -298081.90079;
  result(2, 2) = -31250.87231111;

  EXPECT_TRUE((left -= right) == result);
}

TEST(ModelTest, mul_move_test_0) {
  S21Matrix left = S21Matrix(4, 3);

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  left(3, 0) = 5;
  left(3, 1) = -2;
  left(3, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix(4, 3);

  result(0, 0) = 69;
  result(0, 1) = 11;
  result(0, 2) = 13;

  result(1, 0) = 50;
  result(1, 1) = 31;
  result(1, 2) = 42;

  result(2, 0) = -17;
  result(2, 1) = 25;
  result(2, 2) = 36;

  result(3, 0) = -17;
  result(3, 1) = 25;
  result(3, 2) = 36;

  EXPECT_TRUE((left *= right) == result);
}

TEST(ModelTest, mul_move_test_1) {
  S21Matrix test_matrix = S21Matrix();

  test_matrix(0, 0) = 10;
  test_matrix(0, 1) = 9;
  test_matrix(0, 2) = 19;

  test_matrix(1, 0) = 5;
  test_matrix(1, 1) = 8;
  test_matrix(1, 2) = 23;

  test_matrix(2, 0) = 6;
  test_matrix(2, 1) = 2;
  test_matrix(2, 2) = 1;

  S21Matrix result = S21Matrix();

  result(0, 0) = 100;
  result(0, 1) = 90;
  result(0, 2) = 190;

  result(1, 0) = 50;
  result(1, 1) = 80;
  result(1, 2) = 230;

  result(2, 0) = 60;
  result(2, 1) = 20;
  result(2, 2) = 10;

  EXPECT_TRUE((test_matrix *= 10) == result);
}

TEST(ModelTest, sum_test_0) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 4692.192383;
  left(0, 1) = -5.991882;
  left(0, 2) = 121347;

  left(1, 0) = -629918.12398412;
  left(1, 1) = 313441;
  left(1, 2) = 10565.85;

  left(2, 0) = 51261;
  left(2, 1) = -298084;
  left(2, 2) = -31253.87231111;

  S21Matrix right = S21Matrix();

  right(0, 0) = 21984.811421244;
  right(0, 1) = 51244;
  right(0, 2) = 312;

  right(1, 0) = 6;
  right(1, 1) = -37.92998822;
  right(1, 2) = 4;

  right(2, 0) = 512442;
  right(2, 1) = -2.09921;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = 26677.003804244;
  result(0, 1) = 51238.008118;
  result(0, 2) = 121659;

  result(1, 0) = -629912.12398412;
  result(1, 1) = 313403.07001178;
  result(1, 2) = 10569.85;

  result(2, 0) = 563703;
  result(2, 1) = -298086.09921;
  result(2, 2) = -31256.87231111;

  EXPECT_TRUE((left + right) == result);
}

TEST(ModelTest, sum_test_1) {
  S21Matrix left = S21Matrix(4, 3);

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  left(3, 0) = 5;
  left(3, 1) = -2;
  left(3, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  EXPECT_THROW(left + right, std::invalid_argument);
}

TEST(ModelTest, sub_test_0) {
  S21Matrix left = S21Matrix();

  left(0, 0) = 4692.192383;
  left(0, 1) = -5.991882;
  left(0, 2) = 121347;

  left(1, 0) = -629918.12398412;
  left(1, 1) = 313441;
  left(1, 2) = 10565.85;

  left(2, 0) = 51261;
  left(2, 1) = -298084;
  left(2, 2) = -31253.87231111;

  S21Matrix right = S21Matrix();

  right(0, 0) = 21984.811421244;
  right(0, 1) = 51244;
  right(0, 2) = 312;

  right(1, 0) = 6;
  right(1, 1) = -37.92998822;
  right(1, 2) = 4;

  right(2, 0) = 512442;
  right(2, 1) = -2.09921;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = -17292.619038244;
  result(0, 1) = -51249.991882;
  result(0, 2) = 121035;

  result(1, 0) = -629924.12398412;
  result(1, 1) = 313478.92998822;
  result(1, 2) = 10561.85;

  result(2, 0) = -461181;
  result(2, 1) = -298081.90079;
  result(2, 2) = -31250.87231111;

  EXPECT_TRUE((left - right) == result);
}

TEST(ModelTest, sub_test_1) {
  S21Matrix left = S21Matrix(4, 3);

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  left(3, 0) = 5;
  left(3, 1) = -2;
  left(3, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  EXPECT_THROW(left - right, std::invalid_argument);
}

TEST(ModelTest, mul_test_0) {
  S21Matrix left = S21Matrix(4, 3);

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  left(3, 0) = 5;
  left(3, 1) = -2;
  left(3, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  S21Matrix result = S21Matrix(4, 3);

  result(0, 0) = 69;
  result(0, 1) = 11;
  result(0, 2) = 13;

  result(1, 0) = 50;
  result(1, 1) = 31;
  result(1, 2) = 42;

  result(2, 0) = -17;
  result(2, 1) = 25;
  result(2, 2) = 36;

  result(3, 0) = -17;
  result(3, 1) = 25;
  result(3, 2) = 36;

  EXPECT_TRUE((left * right) == result);
}

TEST(ModelTest, mul_test_1) {
  S21Matrix test_matrix = S21Matrix();

  test_matrix(0, 0) = 10;
  test_matrix(0, 1) = 9;
  test_matrix(0, 2) = 19;

  test_matrix(1, 0) = 5;
  test_matrix(1, 1) = 8;
  test_matrix(1, 2) = 23;

  test_matrix(2, 0) = 6;
  test_matrix(2, 1) = 2;
  test_matrix(2, 2) = 1;

  S21Matrix result = S21Matrix();

  result(0, 0) = 100;
  result(0, 1) = 90;
  result(0, 2) = 190;

  result(1, 0) = 50;
  result(1, 1) = 80;
  result(1, 2) = 230;

  result(2, 0) = 60;
  result(2, 1) = 20;
  result(2, 2) = 10;

  EXPECT_TRUE((test_matrix * 10) == result);
}

TEST(ModelTest, mul_test_2) {
  S21Matrix left = S21Matrix(4, 3);

  left(0, 0) = 2;
  left(0, 1) = 5;
  left(0, 2) = 7;

  left(1, 0) = 6;
  left(1, 1) = 3;
  left(1, 2) = 4;

  left(2, 0) = 5;
  left(2, 1) = -2;
  left(2, 2) = -3;

  left(3, 0) = 5;
  left(3, 1) = -2;
  left(3, 2) = -3;

  S21Matrix right = S21Matrix();

  right(0, 0) = 2;
  right(0, 1) = 5;
  right(0, 2) = 7;

  right(1, 0) = 6;
  right(1, 1) = 3;
  right(1, 2) = 4;

  right(2, 0) = 5;
  right(2, 1) = -2;
  right(2, 2) = -3;

  EXPECT_THROW(right * left, std::invalid_argument);
}

TEST(ModelTest, determinate_test_0) {
  S21Matrix matrix = S21Matrix();

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), -1);
}

TEST(ModelTest, determinate_test_1) {
  S21Matrix matrix = S21Matrix();

  matrix(0, 0) = 4692.192383;
  matrix(0, 1) = -5.991882;
  matrix(0, 2) = 121347;

  matrix(1, 0) = -629918.12398412;
  matrix(1, 1) = 313441;
  matrix(1, 2) = 10565.85;

  matrix(2, 0) = 51261;
  matrix(2, 1) = -298084;
  matrix(2, 2) = -31253.87231111;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), 20804354296571035.477);
}

TEST(ModelTest, determinate_test_2) {
  S21Matrix matrix = S21Matrix(4, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  matrix(3, 0) = 5;
  matrix(3, 1) = -2;
  matrix(3, 2) = -3;

  EXPECT_THROW(matrix.Determinant(), std::runtime_error);
}

TEST(ModelTest, complements_test_0) {
  S21Matrix matrix = S21Matrix();

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = -1;
  result(0, 1) = 38;
  result(0, 2) = -27;

  result(1, 0) = 1;
  result(1, 1) = -41;
  result(1, 2) = 29;

  result(2, 0) = -1;
  result(2, 1) = 34;
  result(2, 2) = -24;

  EXPECT_TRUE(matrix.CalcComplements() == result);
}

TEST(ModelTest, complements_test_1) {
  S21Matrix matrix = S21Matrix(4, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  matrix(3, 0) = 5;
  matrix(3, 1) = -2;
  matrix(3, 2) = -3;

  EXPECT_THROW(matrix.CalcComplements(), std::runtime_error);
}

TEST(ModelTest, inverse_test_0) {
  S21Matrix matrix = S21Matrix();

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;

  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;

  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  EXPECT_TRUE(matrix.InverseMatrix() == result);
}

TEST(ModelTest, inverse_test_1) {
  S21Matrix matrix = S21Matrix();

  EXPECT_THROW(matrix.InverseMatrix(), std::runtime_error);
}

TEST(ModelMatrix, transpose_test_0) {
  S21Matrix matrix = S21Matrix();

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  S21Matrix result = S21Matrix();

  result(0, 0) = 2;
  result(0, 1) = 6;
  result(0, 2) = 5;

  result(1, 0) = 5;
  result(1, 1) = 3;
  result(1, 2) = -2;

  result(2, 0) = 7;
  result(2, 1) = 4;
  result(2, 2) = -3;

  EXPECT_TRUE(matrix.Transpose() == result);
}

TEST(ModelTest, geter_test_0) {
  S21Matrix matrix = S21Matrix();
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(ModelTest, seter_test_0) {
  S21Matrix matrix = S21Matrix();
  matrix.SetRows(2);
  matrix.SetCols(2);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 2);
}

}  // namespace