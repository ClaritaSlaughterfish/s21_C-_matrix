#include <gtest/gtest.h>

#include "./Matrix+/s21_matrix.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
}

TEST(S21MatrixTest, ConstructorWithDimensions) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
}

TEST(S21MatrixTest, ConstructorWithNegativeDimensions) {
  bool exceptionThrown = false;
  try {
    S21Matrix matrix(-1, 2);
  } catch (const std::invalid_argument& e) {
    EXPECT_STREQ("Matrix dimensions must be greater than 0.", e.what());
    exceptionThrown = true;
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }

  EXPECT_TRUE(exceptionThrown) << "Expected std::invalid_argument";

  exceptionThrown = false;
  try {
    S21Matrix matrix(2, -1);
  } catch (const std::invalid_argument& e) {
    EXPECT_STREQ("Matrix dimensions must be greater than 0.", e.what());
    exceptionThrown = true;
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }

  EXPECT_TRUE(exceptionThrown) << "Expected std::invalid_argument";
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(1, 1, 2.0);
  S21Matrix matrix2(matrix1);
  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(1, 1), 2.0);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  S21Matrix matrix2(std::move(matrix1));
  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 0), 1.0);
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getCols(), 0);
}

TEST(S21MatrixTest, GetElementOutOfRange) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.getElement(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix.getElement(0, -1), std::out_of_range);
  EXPECT_THROW(matrix.getElement(2, 0), std::out_of_range);
  EXPECT_THROW(matrix.getElement(0, 2), std::out_of_range);
}

TEST(S21MatrixTest, SetRowsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(1, 1, 2.0);
  matrix.SetRows(3);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 2.0);
}

TEST(S21MatrixTest, SetRowsDecrease) {
  S21Matrix matrix(3, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(1, 1, 2.0);
  matrix.SetRows(2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 2.0);
}

TEST(S21MatrixTest, SetRowsInvalid) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetRows(-1), std::invalid_argument);
}

TEST(S21MatrixTest, SetColsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(1, 1, 2.0);
  matrix.SetCols(3);
  EXPECT_EQ(matrix.getCols(), 3);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 2.0);
}

TEST(S21MatrixTest, SetColsDecrease) {
  S21Matrix matrix(2, 3);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(1, 2, 2.0);
  matrix.SetCols(2);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 0.0);
}

TEST(S21MatrixTest, SetColsInvalid) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetCols(-1), std::invalid_argument);
}

TEST(S21MatrixTest, SetDimensionsValid) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.SetElement(1, 0, 3.0);
  matrix.SetElement(1, 1, 4.0);

  matrix.SetDimensions(3, 4);

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);

  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(2, 3), 0.0);
}

TEST(S21MatrixTest, SetDimensionsDecrease) {
  S21Matrix matrix(3, 4);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(1, 1, 2.0);
  matrix.SetElement(2, 2, 3.0);

  matrix.SetDimensions(2, 2);

  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 1), 0.0);
}

TEST(S21MatrixTest, SetDimensionsInvalid) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetDimensions(-1, 2), std::invalid_argument);
  EXPECT_THROW(matrix.SetDimensions(2, -1), std::invalid_argument);
  EXPECT_THROW(matrix.SetDimensions(-1, -1), std::invalid_argument);
}

TEST(S21MatrixTest, SetElement) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
}

TEST(S21MatrixTest, SetElementOutOfRange) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetElement(-1, 0, 1.0), std::out_of_range);
  EXPECT_THROW(matrix.SetElement(0, -1, 1.0), std::out_of_range);
  EXPECT_THROW(matrix.SetElement(2, 0, 1.0), std::out_of_range);
  EXPECT_THROW(matrix.SetElement(0, 2, 1.0), std::out_of_range);
}

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 3.0);
  matrix2.SetElement(0, 1, 4.0);

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 1), 6.0);
}

TEST(S21MatrixTest, SubMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 5.0);
  matrix1.SetElement(0, 1, 6.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 3.0);
  matrix2.SetElement(0, 1, 4.0);

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 1), 2.0);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 1), 4.0);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  matrix2.SetElement(0, 1, 0.0);
  matrix2.SetElement(1, 0, 1.0);
  matrix2.SetElement(1, 1, 2.0);

  matrix1.MulMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(1, 1), 8.0);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix matrix(2, 3);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.SetElement(0, 2, 3.0);
  matrix.SetElement(1, 0, 4.0);
  matrix.SetElement(1, 1, 5.0);
  matrix.SetElement(1, 2, 6.0);

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed.getElement(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed.getElement(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed.getElement(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed.getElement(2, 1), 6.0);
}

TEST(S21MatrixTest, Determinant2x2) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.SetElement(1, 0, 3.0);
  matrix.SetElement(1, 1, 4.0);

  double det = matrix.Determinant();
  EXPECT_DOUBLE_EQ(det, -2.0);
}

TEST(S21MatrixTest, Determinant3x3) {
  S21Matrix matrix(3, 3);
  matrix.SetElement(0, 0, 6);
  matrix.SetElement(0, 1, 1);
  matrix.SetElement(0, 2, 1);
  matrix.SetElement(1, 0, 4);
  matrix.SetElement(1, 1, -2);
  matrix.SetElement(1, 2, 5);
  matrix.SetElement(2, 0, 2);
  matrix.SetElement(2, 1, 8);
  matrix.SetElement(2, 2, 7);

  double det = matrix.Determinant();
  EXPECT_DOUBLE_EQ(det, -306);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 4.0);
  matrix.SetElement(0, 1, 7.0);
  matrix.SetElement(1, 0, 2.0);
  matrix.SetElement(1, 1, 6.0);

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_NEAR(inverse.getElement(0, 0), 0.6, 1e-9);
  EXPECT_NEAR(inverse.getElement(0, 1), -0.7, 1e-9);
  EXPECT_NEAR(inverse.getElement(1, 0), -0.2, 1e-9);
  EXPECT_NEAR(inverse.getElement(1, 1), 0.4, 1e-9);
}

TEST(S21MatrixTest, OperatorAssign) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  S21Matrix matrix2 = matrix1;
  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 0), 1.0);
}

TEST(S21MatrixTest, OperatorAssignCopy) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(3, 3);
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorAssignSelf) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.SetElement(1, 0, 3.0);
  matrix.SetElement(1, 1, 4.0);

  matrix = matrix;

  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix.getElement(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorAssignDifferentSize) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(3, 3);
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix2.getElement(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorAdd) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 5.0);
  matrix2.SetElement(0, 1, 6.0);
  matrix2.SetElement(1, 0, 7.0);
  matrix2.SetElement(1, 1, 8.0);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result.getElement(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result.getElement(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 1), 12.0);
}

TEST(S21MatrixTest, OperatorSub) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 5.0);
  matrix1.SetElement(0, 1, 6.0);
  matrix1.SetElement(1, 0, 7.0);
  matrix1.SetElement(1, 1, 8.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 1.0);
  matrix2.SetElement(0, 1, 2.0);
  matrix2.SetElement(1, 0, 3.0);
  matrix2.SetElement(1, 1, 4.0);

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result.getElement(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorMulMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  matrix2.SetElement(0, 1, 0.0);
  matrix2.SetElement(1, 0, 1.0);
  matrix2.SetElement(1, 1, 2.0);

  S21Matrix result = matrix1 * matrix2;

  EXPECT_DOUBLE_EQ(result.getElement(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 1), 8.0);
}

TEST(S21MatrixTest, OperatorMulNumber) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 1.0);
  matrix.SetElement(0, 1, 2.0);
  matrix.SetElement(1, 0, 3.0);
  matrix.SetElement(1, 1, 4.0);

  S21Matrix result = matrix * 2.0;

  EXPECT_DOUBLE_EQ(result.getElement(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result.getElement(1, 1), 8.0);
}

TEST(S21MatrixTest, OperatorAddAssign) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  matrix1 += matrix2;
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 3.0);
}

TEST(S21MatrixTest, OperatorSubAssign) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 3.0);
  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  matrix1 -= matrix2;
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 1.0);
}

TEST(S21MatrixTest, OperatorMulAssignNumber) {
  S21Matrix matrix(2, 2);
  matrix.SetElement(0, 0, 2.0);
  matrix *= 3.0;
  EXPECT_DOUBLE_EQ(matrix.getElement(0, 0), 6.0);
}

TEST(S21MatrixTest, OperatorMulAssignMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  matrix2.SetElement(1, 0, 1.0);
  matrix2.SetElement(0, 1, 0.0);
  matrix2.SetElement(1, 1, 2.0);

  matrix1 *= matrix2;

  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1.getElement(1, 1), 8.0);
}

TEST(S21MatrixTest, OperatorEquality) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 1.0);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorInequality) {
  S21Matrix matrix1(2, 2);
  matrix1.SetElement(0, 0, 1.0);
  S21Matrix matrix2(2, 2);
  matrix2.SetElement(0, 0, 2.0);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorParenthesisNonConst) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;
  matrix(2, 2) = 3.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(2, 2), 3.0);
}

TEST(S21MatrixTest, OperatorParenthesisConst) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;
  matrix(2, 2) = 3.0;

  const S21Matrix constMatrix = matrix;

  EXPECT_DOUBLE_EQ(constMatrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(constMatrix(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(constMatrix(2, 2), 3.0);
}

TEST(S21MatrixTest, OperatorParenthesisOutOfRangeNonConst) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix(3, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 3), std::out_of_range);
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
}

TEST(S21MatrixTest, OperatorParenthesisOutOfRangeConst) {
  S21Matrix matrix(3, 3);
  const S21Matrix constMatrix = matrix;
  EXPECT_THROW(constMatrix(3, 0), std::out_of_range);
  EXPECT_THROW(constMatrix(0, 3), std::out_of_range);
  EXPECT_THROW(constMatrix(-1, 0), std::out_of_range);
  EXPECT_THROW(constMatrix(0, -1), std::out_of_range);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}