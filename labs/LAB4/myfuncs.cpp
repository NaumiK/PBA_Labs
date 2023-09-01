#include "myfuncs.h"
#include "MyString.h"

namespace {
MyString iXY(Dialog::Ioeqpp &iqp) {
  if (iqp.printQst)
    iqp.qout << "Write your string, please" << std::endl;
  MyString str;
  iqp.in >> str;
  return str;
}

void oXY(MyString &str, std::ostream &out) { out << str.c_str() << std::endl; }
} // namespace

void MDialog::ioXY(Ioeqpp &iqp) {
  MyString x = iXY(iqp);
  MyString y(x);
  oXY(y, iqp.out);
}
