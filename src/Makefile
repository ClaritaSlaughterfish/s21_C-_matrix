CPP = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage

LIB = ./Matrix+/*.cpp 
OBJECTS = *.o 
TEST = test_s21matrix.cpp 

CLANG_PATH = ../materials/linters/
CLANG_COPY = cp $(CLANG_PATH).clang-format .clang-format 

all: rebuild

test: s21_matrix_oop.a
	$(CPP) $(CPPFLAGS) -o tests test_s21matrix.cpp s21_matrix_oop.a -lgtest -lpthread
	./tests 

gcov_report: s21_matrix_oop.a
	$(CPP) $(CPPFLAGS) -fprofile-arcs -ftest-coverage -o tests test_s21matrix.cpp s21_matrix_oop.a -lgtest -lpthread
	./tests
	gcov *.cpp
	lcov -t "s21_matrix" -o coverage.info -c -d . --no-external
	genhtml -o coverage coverage.info

valgrind: s21_matrix_oop.a
	$(CPP) $(CPPFLAGS) -o tests test_s21matrix.cpp s21_matrix_oop.a -lgtest -lpthread
	valgrind --leak-check=full --show-reachable=yes ./tests

s21_matrix_oop.a: 
	$(CPP) $(CPPFLAGS) -Iinclude -c $(LIB)
	ar rc s21_matrix_oop.a *.o 
	ranlib s21_matrix_oop.a 

clean:
	rm -rf $(OBJECTS) *.a *.gch *.gcda *.gcno *.info tests .clang-format coverage

clang:
	$(CLANG_COPY) && clang-format -n ./Matrix+/* *.cpp 
	$(CLANG_COPY) && clang-format -i ./Matrix+/* *.cpp 

rebuild: clean s21_matrix_oop.a test