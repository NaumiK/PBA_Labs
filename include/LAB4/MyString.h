#ifndef LAB4_MYSTRING_H
#define LAB4_MYSTRING_H

#include <iostream>

class MyString {
  size_t size_;
  size_t capacity_;
  char *buffer_;

  void strExt();
  void reset();

public:
  MyString();
  MyString(MyString &x);
  explicit MyString(const char *x);
  [[nodiscard]] size_t size() const;
  [[nodiscard]] const char *c_str() const;
  void readStr(std::istream &in);
  ~MyString();
  void f(MyString &x);
  MyString &operator=(const char *x);
  char operator[](size_t i);
  friend std::istream &operator>>(std::istream &in, MyString &string);
  friend std::ostream &operator<<(std::ostream &os, const MyString &string);
  friend MyString operator+(const MyString &a, const MyString &b);
  const char *begin();
  const char *end();
};

#endif // LAB4_MYSTRING_H
