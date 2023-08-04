#ifndef LABS_MYFUNCS_H
#define LABS_MYFUNCS_H

#include <iostream>
#include <cmath>
#include <fstream>

namespace LabsExceptions {
    class NotThatType : public std::exception {
    public:
        const char *what() const noexcept override {
            return "The type of input is not correct.";
        }
    };

    class ThereIsNothing : public std::exception {
    public:
        const char *what() const noexcept override {
            return "There is nothing";
        }
    };
}

namespace LabsInputFunctions {
    uint8_t inputULL(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputNatural(uint64_t &x, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
    uint8_t inputBool(bool &b, std::istream &in = std::cin, std::ostream &eout = std::cerr, bool printErr = true);
}

namespace LabsDialogs {
    int step();
}
#endif //LABS_MYFUNCS_H