//
// Created by Глеб Писарев on 17.09.2023.
//

#include "test.h"
#include "s21_matrix_oop.h"

namespace {
    TEST(ModelTest, init_matrix_test_0) {
        S21Matrix matrix = S21Matrix();
        EXPECT_EQ(matrix.GetRows(), 3);
        EXPECT_EQ(matrix.GetCols(), 3);
        for (int i = 0; i < matrix.GetRows(); ++i)
            for (int j = 0; j < matrix.GetCols(); ++j)
                EXPECT_FLOAT_EQ(matrix(i, j), 0);
    }

    TEST(ModelTest, init_matrix_test_1) {
        S21Matrix matrix = S21Matrix(2, 7);
        EXPECT_EQ(matrix.GetRows(), 3);
        EXPECT_EQ(matrix.GetCols(), 3);
        for (int i = 0; i < matrix.GetRows(); ++i)
            for (int j = 0; j < matrix.GetCols(); ++j)
                EXPECT_FLOAT_EQ(matrix(i, j), 0);
    }

    TEST(ModelTest, init_matrix_test_2) {
        S21Matrix src = S21Matrix();
        for (int i = 0; i < src.GetRows(); ++i)
            for (int j = 0; j < src.GetRows(); ++j)
                src(i, j) = 100619;
        S21Matrix dst = S21Matrix(src);
        EXPECT_EQ(dst.GetRows(), src.GetRows());
        EXPECT_EQ(dst.GetCols(), src.GetCols());
        EXPECT_TRUE(dst == src);
    }

    TEST(ModelTest, arithmetic_test_0) {
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

    TEST(ModelTest, arithmetic_test_1) {
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
}