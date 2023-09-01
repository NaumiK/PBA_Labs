#include "myfuncs.h"
#include "MIO.h"

namespace {
std::pair<uint64_t, uint64_t> iXY(Dialog::Ioeqpp &iqp) {
  if (iqp.printQst)
    iqp.qout << "Unsigned integer: " << std::endl;
  uint64_t n;
  MIO::inputULL(n, iqp.in, iqp.eout, iqp.printErr);
  std::bitset<sizeof(n) * 8> bits;
  if (iqp.printQst)
    iqp.qout << "Binary subsequence: " << std::endl;
  MIO::inputBS<sizeof(n) * 8>(bits, iqp.in, iqp.eout, iqp.printErr);
  return {n, bits.to_ullong()};
}
} // namespace

void MDialog::ioXY(Ioeqpp &iqp) {
  auto [x, y] = iXY(iqp);
  std::bitset<sizeof(x) * 8> bb(x);
  iqp.out << bb << "\n";
  bb = y;
  iqp.out << bb << std::endl;
  size_t msb, sz = sizeof(x) * 8;
  for (msb = 0; (y >> msb) != 0; ++msb)
    ;

  bool f = false;
  for (size_t i = 0; i < sz - msb; ++i) {
    f = f || (((x << (sz - msb - i)) >> (sz - msb)) == y);
  }
  iqp.out << (f ? "There is the subsequence" : "There isn't the subsequence")
          << std::endl;
}
