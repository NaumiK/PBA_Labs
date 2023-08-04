#include "myfuncs.h"
#include "constants.h"
#include <iostream>
#include <string>

namespace {
    double y(double x) {
        return (x * x - 3 * x + 2) / (sqrt(2 * x * x * x - 1));
    }

    std::pair<double *, size_t> iXY(std::istream &in, std::ostream &out, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        size_t n = 0;
        static double arr[arrsize];
        if (printQst) qout << "n" << std::endl;
        try {
            if (LabsInputFunctions::inputNatural(n, in, eout, printErr) != 0) throw LabsExceptions::ThereIsNothing();
            for (int i = 0; i <= n; ++i) {
                arr[i] = y(1 + 0.1 * i);
            }
        } catch (std::exception &err) {
            if (printErr) eout << err.what() << std::endl;
        }
        return {arr, n};
    }

    void oXY(double inp[], size_t n, std::ostream &out) {
        out << "x\ty" << std::endl;
        for (uint64_t i = 0; i <= n; ++i) {
            out << 1 + 0.1 * (double)i << "\t" << inp[i] << std::endl;
        }
    }

    void ioXY(std::istream &in, std::ostream &out, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        auto [arr, n] = iXY(in, out, eout, qout, printErr, printQst);
        if (n != 0) oXY(arr, n, out);
    }

    void consoleI(std::ostream &out) {
        ioXY(std::cin, out, std::cerr, std::cout, true, true);
    }

    void fileI(std::ostream &out) {
        std::ifstream fin("in.txt");
        if (fin.fail()) throw LabsExceptions::ThereIsNothing{};
        while (!fin.eof())
            ioXY(fin, out, std::cerr, out, false, false);
    }
}

uint8_t LabsInputFunctions::inputULL(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true; std::string s;
    do {
        try {
            if (in.eof()) return 1;
            std::getline(in, s);
            if (s.find('-') != std::string::npos) throw LabsExceptions::NotThatType();
            x = std::stoul(s);
            f = false;
        } catch (std::exception &err) {
            if (printErr) eout << err.what() << "\n" << "Write an unsigned integer, please" << std::endl;
        }
    } while (f);
    return 0;
}

uint8_t LabsInputFunctions::inputNatural(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true; std::string s;
    do {
        try {
            uint64_t tmp;
            if (inputULL(tmp, in, eout, printErr)) return 1;
            if (tmp == 0) throw LabsExceptions::NotThatType();
            x = tmp;
            f = false;
        } catch (std::exception &err) {
            if (printErr) eout << err.what() << "\n" << "Write a natural number, please" << std::endl;
        }
    } while (f);
    return 0;
}

uint8_t LabsInputFunctions::inputBool(bool &b, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true; std::string s;
    do {
        try {
            if (in.eof()) return 1;
            getline(in, s);
            s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
            if (!(s == "1" || s == "0")) throw LabsExceptions::NotThatType();
            b = (s == "1");
            f = false;
        } catch(std::exception &err) {
            if (printErr) eout << err.what() << "\n" << "Write a boolean value (0, 1), please" << std::endl;
        }
    } while(f);
    return 0;
}

int LabsDialogs::step() {
    bool cI, cO;
    std::cout << "What would you use for input? 1 - Console, 0 - file: " << std::endl;
    LabsInputFunctions::inputBool(cI,std::cin, std::cerr, true);
    std::cout << "What would you use for output? 1 - Console, 0 - file: " << std::endl;
    LabsInputFunctions::inputBool(cO, std::cin, std::cerr, true);

    std::ofstream file("out.txt");
    auto &out = (cO ? std::cout : file);

    if (cI) {
        consoleI(out);
        return 1;
    } else fileI(out);
    return 0;
}
