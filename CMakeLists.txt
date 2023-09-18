cmake_minimum_required(VERSION 3.25)
project(CPP1_s21_matrixplus_1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

include_directories(src/include)

add_executable(model_test
        src/include/s21_matrix_oop.h src/s21_matrix_oop.сpp
        src/tests/test.cpp src/include/test.h)

target_link_libraries(model_test GTest::gtest_main)
