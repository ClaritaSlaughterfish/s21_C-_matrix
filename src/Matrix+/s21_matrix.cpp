#include "s21_matrix.h"

// Методы

// Конструктор по умолчанию
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_() {}

// Конструктор по измерениям
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Matrix dimensions must be greater than 0.");
  }
  matrix_ =
      std::vector<std::vector<double>>(rows_, std::vector<double>(cols, 0.0));
}

// Коструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  other.rows_ = 0;
  other.cols_ = 0;
}

// Деструктор
S21Matrix::~S21Matrix() {}

// Аксессоры

// Для строк
int S21Matrix::getRows() const noexcept { return rows_; }

// Для столбцов
int S21Matrix::getCols() const noexcept { return cols_; }

// Для элементов
double S21Matrix::getElement(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range.");
  }
  return matrix_[row][col];
}

// Мутаторы

// Для строк
void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Matrix dimensions must be greater than 0.");
  }
  if (rows != rows_) {
    S21Matrix tmp(rows, cols_);
    for (int i = 0; i < std::min(rows_, rows); ++i) {
      std::copy(matrix_[i].begin(), matrix_[i].begin() + cols_,
                tmp.matrix_[i].begin());
    }
    matrix_ = std::move(tmp.matrix_);
    rows_ = rows;
  }
}

// Для столбцов
void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument("Matrix dimensions must be greater than 0.");
  }
  if (cols != cols_) {
    S21Matrix tmp(rows_, cols);
    for (int i = 0; i < rows_; ++i) {
      std::copy(matrix_[i].begin(), matrix_[i].begin() + std::min(cols_, cols),
                tmp.matrix_[i].begin());
    }
    matrix_ = std::move(tmp.matrix_);
    cols_ = cols;
  }
}

// Изменение  двух измерений одновременно
void S21Matrix::SetDimensions(int rows, int cols) {
  SetRows(rows);
  SetCols(cols);
}

// Изменение значения элемента
void S21Matrix::SetElement(int row, int col, double value) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range.");
  }
  matrix_[row][col] = value;
}

// Операции

// Проверка равенства матриц
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool status = true;
  if (rows_ != other.rows_ || cols_ != other.cols_)
    status = false;
  else {
    for (int i = 0; i < rows_; ++i) {
      if (status == false) break;
      for (int j = 0; j < cols_; ++j) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          status = false;
          break;
        }
      }
    }
  }
  return status;
}

// Прибавление к матрице
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions are not equal.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Вычитание из матрицы
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions are not equal.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Умножение на число
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

// Умножение на матрицу
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Matrix dimensions are not comparable.");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

// Создание транспонированной матрицы
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

// Вычисление матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements.");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix submatrix = minor(i, j);
      double sub_det = determinantRecursive(submatrix);
      result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * sub_det;
    }
  }
  return result;
}

// Вычисление детерминанта
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate determinant.");
  }
  return determinantRecursive(*this);
}

// Вычисление обратной матрицы
S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) {
    throw std::runtime_error("Matrix is singular and cannot be inverted.");
  }
  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  transposed.MulNumber(1.0 / det);
  return transposed;
}

// Операторы

// Перегрузка оператора сложения (+)
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// Перегрузка оператора вычитания (-)
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// Перегрузка оператора умножения на матрицу (*)
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// Перегрузка оператора умножения на число (*)
S21Matrix S21Matrix::operator*(const double num) const noexcept {
  S21Matrix result{*this};
  result.MulNumber(num);
  return result;
}

// Перегрузка оператора сравнения (==)
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

// Перегрузка оператора присваивания (=)
// Копированием
S21Matrix& S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
  }
  return *this;
}

// Перемещением
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = std::move(other.matrix_);
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

// Перегрузка оператора += (присвоение сложения)
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

// Перегрузка оператора -= (присвоение разности)
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

// Перегрузка оператора *= (присвоение умножения на матрицу)
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

// Перегрузка оператора *= (присвоение умножения на число)
S21Matrix& S21Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

// Перегрузка оператора индексации ()
double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[i][j];
}

// Перегрузка оператора индексации () для const объектов
const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[i][j];
}

// Приватные вспомогательные функции

// Рекурсивное вычисление детерминанта
// Calculate matrix determinant (recursive method)
double S21Matrix::determinantRecursive(const S21Matrix& other) const {
  if (other.rows_ == 1) return other.matrix_[0][0];
  if (other.rows_ == 2) {
    return other.matrix_[0][0] * other.matrix_[1][1] -
           other.matrix_[0][1] * other.matrix_[1][0];
  }
  double det = 0.0;
  for (int i = 0; i < other.cols_; ++i) {
    S21Matrix submatrix = other.minor(0, i);
    det += ((i % 2 == 0 ? 1 : -1) * other.matrix_[0][i] *
            determinantRecursive(submatrix));
  }
  return det;
}

// Calculate matrix minor
S21Matrix S21Matrix::minor(int row, int col) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, m = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, n = 0; j < cols_; ++j) {
      if (j == col) continue;
      result.matrix_[m][n] = matrix_[i][j];
      ++n;
    }
    ++m;
  }
  return result;
}
