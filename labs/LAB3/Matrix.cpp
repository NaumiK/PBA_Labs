#include "Matrix.h"
#include <memory>

Matrix::ProxyRow::ProxyRow(int64_t *rowStart, size_t cols)
    : rowStart_(rowStart), cols_(cols) {}

int64_t &Matrix::ProxyRow::operator[](size_t col) { return rowStart_[col]; }

const int64_t &Matrix::ProxyRow::operator[](size_t col) const {
  return rowStart_[col];
}

size_t Matrix::rows() const { return rows_; }

size_t Matrix::cols() const { return cols_; }

Matrix::Matrix(size_t _rows, size_t _cols) : rows_(_rows), cols_(_cols) {
  data_ = new int64_t[rows_ * cols_];
}

Matrix::~Matrix() { delete[] data_; }

Matrix::ProxyRow Matrix::operator[](size_t row) {
  return ProxyRow(data_ + row * cols_, cols_);
}

const Matrix::ProxyRow Matrix::operator[](size_t row) const {
  return ProxyRow(data_ + row * cols_, cols_);
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  data_ = new int64_t[rows_ * cols_];
  std::copy(other.data_, other.data_ + (rows_ * cols_), data_);
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    delete[] data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = new int64_t[rows_ * cols_];
    std::copy(other.data_, other.data_ + (rows_ * cols_), data_);
  }
  return *this;
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.data_ = nullptr;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
  }
  return *this;
}