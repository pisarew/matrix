CFLAGS := -Wall -Wextra -Werror -std=c++17 -I ./include/
OS := $(shell uname -s)
LIB_SOURCE_FILES := s21_matrix_oop.cpp
TESTS_SOURCE_FILES := ./tests/test.cpp
CC := g++

ifeq ($(OS), Darwin)
	TEST_FLAGS = -lgtest_main -lgtest
else
	TEST_FLAGS = -lgtest_main -lgtest -lgmock -pthread
endif

all: test

test: clean build
	./test

build: s21_matrix_oop.a
	${CC} ${CFLAGS} -o test ${TESTS_SOURCE_FILES} ${TEST_FLAGS} s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c $(LIB_SOURCE_FILES)
	ar rcs $@ s21_matrix_oop.o

clean:
	rm -rf test *.html *.css *.gcno *.gcda *.o *.a

gcov_report: clean test
	g++ $(CFLAGS) --coverage ${LIB_SOURCE_FILES} ${TESTS_SOURCE_FILES} -o test $(TEST_FLAGS)
	./test
	gcovr -r . --html --html-details -o coverage_report.html
	open coverage_report.html

linter:
	cp ../materials/linters/.clang-format .
	cp ../materials/linters/.clang-format tests/.
	cp ../materials/linters/.clang-format include/.
	clang-format -n *.cpp
	clang-format -n include/*.h
	clang-format -n tests/*.*
	rm -rf .clang-format
	rm -rf tests/.clang-format
	rm -rf include/.clang-format

vg: clean build
	 leaks --atExit -- ./test
