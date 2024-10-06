#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

class S21Matrix {
 private:
  int rows_;
  int cols_;
  std::vector<std::vector<double>> matrix_;

 public:
  // Methods
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();
  // Operations
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  // Operators
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const noexcept;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num) noexcept;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
  // Getters
  int getRows() const noexcept;
  int getCols() const noexcept;
  double getElement(int row, int col) const;
  // Setters
  void SetRows(int rows);
  void SetCols(int cols);
  void SetDimensions(int rows, int cols);
  void SetElement(int row, int col, double value);

 private:
  S21Matrix minor(int row, int col) const;
  double determinantRecursive(const S21Matrix& other) const;
};

#endif