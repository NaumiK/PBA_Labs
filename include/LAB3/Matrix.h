#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdint>

class Matrix final {
private:
  size_t rows_, cols_;
  int64_t *data_;

  class ProxyRow {
  private:
    int64_t *rowStart_;
    size_t cols_;

  public:
    ProxyRow(int64_t *rowStart, size_t cols);

    int64_t &operator[](size_t col);
    const int64_t &operator[](size_t col) const;
  };

public:
  size_t rows() const;
  size_t cols() const;

  Matrix(size_t _rows, size_t _cols);
  ~Matrix();

  ProxyRow operator[](size_t row);
  const ProxyRow operator[](size_t row) const;

  Matrix(const Matrix &other);

  Matrix &operator=(const Matrix &other);

  Matrix(Matrix &&other) noexcept;

  Matrix &operator=(Matrix &&other) noexcept;
};

#endif // LAB3_MATRIX_H