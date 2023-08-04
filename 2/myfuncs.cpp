#include "myfuncs.h"
#include <string>
#include "constants.h"

namespace {
    std::pair<uint64_t *, uint64_t> iXY(std::istream &in, std::ostream &out, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        uint64_t n = -1, kd = 0;
        static uint64_t arr[arrsize];
        if (printQst) qout << "n" << std::endl;
        if (LabsInputFunctions::inputNatural(n, in, eout, printErr) == 0) {
            for (int i = 1; i <= n; ++i) {
                if (n % i == 0) arr[kd++] = i;
            }
        } else {
            eout << "There is nothing" << std::endl;
        }
        return {arr, kd};
    }

    void oXY(uint64_t *inp, uint64_t n, std::ostream &out) {
        out << "Natural divisors of a number " << inp[n - 1] << " are:\n";
        for (int i = 0; i < n; ++i) {
            out << inp[i] << " ";
        }
        out << std::endl;
    }

    void ioXY(std::istream &in, std::ostream &out, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        auto [arr, kd] = iXY(in, out, eout, qout, printErr, printQst);
        if (kd != 0) oXY(arr, kd, out);
    }

    void consoleI(std::ostream &out) {
        ioXY(std::cin, out, std::cerr, std::cout, true, true);
    }

    void fileI(std::ostream &out) {
        std::ifstream fin("in.txt");
        if (fin.fail()) throw LabsExceptions::ThereIsNothing();
        while (!fin.eof())
            ioXY(fin, out, std::cerr, out, false, false);
    }
}

namespace LabsInputFunctions {
    uint8_t inputULL(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
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

    uint8_t inputNatural(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true; std::string s;
        do {
            try {
                uint64_t tmp;
                if (LabsInputFunctions::inputULL(tmp, in, eout, printErr)) return 1;
                if (tmp == 0) throw LabsExceptions::NotThatType();
                x = tmp;
                f = false;
            } catch (std::exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write a natural number, please" << std::endl;
            }
        } while (f);
        return 0;
    }

    uint8_t inputBool(bool &b, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true; std::string s;
        do {
            try {
                if (in.eof()) return 1;
                std::getline(in, s);
                s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
                if (!(s == "1" || s == "0")) throw LabsExceptions::NotThatType();
                b = (s == "1");
                f = false;
            } catch(std::exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write a boolean value (0, 1), please" << std::endl;
            }
        } while(f);
        return 0;
    }
}


int LabsDialogs::step() {
    bool cI, cO;
    std::cout << "What would you use for input? 1 - Console, 0 - file: " << std::endl;
    LabsInputFunctions::inputBool(cI, std::cin, std::cerr, true);
    std::cout << "What would you use for output? 1 - Console, 0 - file: " << std::endl;
    LabsInputFunctions::inputBool(cO, std::cin, std::cerr, true);

    std::ofstream file{"out.txt"};
    auto &out = (cO ? std::cout : file);

    if (cI) {
        consoleI(out);
        return 1;
    } else fileI(out);
    return 0;
}
