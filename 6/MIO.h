#ifndef LABS_MIO_H
#define LABS_MIO_H

#include <iostream>

namespace MIO {
    uint8_t inputStreamLL(int64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputBool(bool &b, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputULL(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputNatural(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t chooseVariant(uint64_t &x, uint64_t border, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
}
#endif //LABS_MIO_H
