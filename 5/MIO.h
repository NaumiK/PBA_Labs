#ifndef LABS_MIO_H
#define LABS_MIO_H

#include <iostream>
#include <bitset>
#include "MExc.h"

namespace MIO {
    uint8_t
    inputStreamLL(int64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputBool(bool &b, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputULL(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputNatural(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);

    template<size_t T> uint8_t inputBS(std::bitset<T> &x, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true;
        std::bitset<T> y;
        do {
            try {
                if (in.eof()) return 1;
                if ((in >> y).fail()) throw MExc::NotThatType();
                x = y;
                f = false;
            } catch (std::exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write bit sequence, please" << std::endl;
                in.clear();
                if (in.eof()) return 1;
                std::string tmp;
                in >> tmp;
            }
        } while (f);
        return 0;
    }
}

#endif //LABS_MIO_H
