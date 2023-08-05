#include "MyString.h"
#include <sstream>

MyString::MyString() : size_(0), capacity_(64) {
    buffer_ = new char[capacity_];
}

size_t MyString::size() const {
    return size_;
}

const char *MyString::c_str() const {
    return buffer_;
}

void MyString::readStr(std::istream &in) {
    char buffer[4096];
    while (in.get(buffer, 4096)) {
        size_t size = in.gcount();
        if (size_ + size >= capacity_) strExt();
        memcpy(buffer_ + size_, buffer, size);
        size_ += size;
        if (size != 4095 || in.peek() == '\n') {
            buffer_[size_] = '\0';
            in.ignore();
            break;
        }
    }
}

MyString::~MyString() {
    delete[] buffer_;
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    os << "size_: " << string.size_ << " capacity_: " << string.capacity_ << " buffer_: " << string.buffer_;
    return os;
}

void MyString::f(MyString &x) {
    reset();
    const char *str = x.c_str();
    for (size_t i = 0; i < x.size(); ++i) {
        if (str[i] != '*') {
            if (size_ + 2 >= capacity_) strExt();
            buffer_[size_++] = str[i];
            buffer_[size_++] = str[i];
        }
    }
    buffer_[size_] = '\0';
}

void MyString::strExt() {
    capacity_ *= 2;
    char *tmp = new char[capacity_];
    memcpy(tmp, buffer_, size_);
    delete[] buffer_;
    buffer_ = tmp;
}

MyString::MyString(MyString &x) : size_(0), capacity_(64), buffer_(nullptr)  {
    this->f(x);
}

std::istream &operator>>(std::istream &in, MyString &string) {
    string.readStr(in);
    return in;
}

MyString operator+(const MyString& a, const MyString& b) {
    MyString x;
    x.size_ = a.size_ + b.size_;
    x.capacity_ = std::max(a.capacity_, b.capacity_);
    if (x.size_ >= x.capacity_) x.strExt();
    memcpy(x.buffer_, a.buffer_, a.size_);
    memcpy(x.buffer_ + a.size_, b.buffer_, b.size_);
    x.buffer_[x.size_] = '\0';
    return x;
}

MyString::MyString(const char *x) : size_(0), capacity_(64), buffer_(nullptr) {
    (*this) = x;
}


MyString& MyString::operator=(const char *x) {
    reset();
    std::stringstream ss;
    ss << x;
    ss >> (*this);
    return *this;
}

void MyString::reset() {
    size_ = 0;
    capacity_ = 64;
    delete []buffer_;
    buffer_ = new char[capacity_];
}

const char *MyString::begin() {
    return buffer_;
}

const char *MyString::end() {
    return buffer_ + size_;
}

char MyString::operator[](size_t i) {
    if (i >= size_) throw std::out_of_range("MyStr");
    return buffer_[i];
}
