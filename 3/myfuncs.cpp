#include "myfuncs.h"
#include <typeinfo>
#include <string>

namespace LabsInputFunctions {
    uint8_t inputStreamLL(int64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true;
        do {
            try {
                if (in.eof()) return 1;
                int64_t tmp;
                if (!(in >> tmp)) throw LabsExceptions::NotThatType();
                x = tmp;
                f = false;
            } catch (std::exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write an integer, please\n" << std::endl;
                in.clear();
                if (in.eof()) return 1;
                std::string tmp;
                in >> tmp;
            }
        } while (f);
        return 0;
    }

    uint8_t inputULL(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true;
        std::string s;
        do {
            try {
                if (in.eof()) return 1;
                getline(in, s);
                if (s.find('-') != std::string::npos) throw LabsExceptions::NotThatType();
                x = stoul(s);
                f = false;
            } catch (std::exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write an unsigned integer, please" << std::endl;
            }
        } while (f);
        return 0;
    }

    uint8_t inputNatural(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true;
        std::string s;
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

    uint8_t inputBool(bool &b, std::istream &in, std::ostream &eout, bool printErr) {
        bool f = true;
        std::string s;
        do {
            try {
                if (in.eof()) return 1;
                getline(in, s);
                s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
                if (!(s == "1" || s == "0")) throw LabsExceptions::NotThatType();
                b = (s == "1");
                f = false;
            } catch (std::exception &err) {
                if (printErr && !s.empty()) eout << err.what() << "\n" << "Write a boolean value (0, 1), please" << std::endl;
            }
        } while (f);
        return 0;
    }
}
namespace {
    std::pair<int64_t *, size_t> iXY(std::istream &in, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        size_t n = 0;
        int64_t *mrx = nullptr;
        if (printQst) qout << "n" << std::endl;

        try {
            if (LabsInputFunctions::inputULL(n, in, eout, printErr) != 0) throw LabsExceptions::ThereIsNothing();
            mrx = new int64_t[n * n];
            if (printQst) qout << "Matrix nxn:" << std::endl;
            for (size_t i = 0; i < n * n; ++i)
                if (LabsInputFunctions::inputStreamLL(mrx[i], in, eout, printErr) != 0)
                    throw LabsExceptions::ThereIsNothing();
        } catch (std::exception &err) {
            eout << err.what() << std::endl;
            delete[] mrx;
            return {nullptr, 0};
        }
        return {mrx, n};
    }

    void oXY(const uint32_t *inp, size_t n, const std::string &exs, std::ostream &out) {
        out << exs << ") ";
        for (int i = 1; i <= n; ++i) {
            bool f = false;
            for (int j = 0; j < n; ++j) {
                if (inp[j] == i) {
                    out << j + 1 << " ";
                    f = true;
                }
            }
            if (f) out << "\t";
        }
        out << std::endl;
    }
}

namespace LabsDialogs {
    void ioXY(std::istream &in, std::ostream &out, std::ostream &eout, std::ostream &qout, bool printErr, bool printQst) {
        auto [mrx, n] = iXY(in, eout, qout, printErr, printQst);
        if (mrx == nullptr) return;
        auto *ans = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            ans[i] = 1;
            for (size_t j = 0; j < n; ++j) {
                ans[i] = ans[i] && (mrx[i * n + j] == 0);
            }
        }
        oXY(ans, n, "a", out);
        delete[] ans;

        ans = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            ans[i] = 0;
            for (size_t j = 0; j < n; ++j) {
                bool f = true;
                for (size_t k = 0; k < n; ++k) {
                    f = f && (mrx[i * n + k] == mrx[j * n + k]);
                }
                if (f) ans[j] = i + 1;
            }
        }
        oXY(ans, n, "b", out);
        delete[] ans;

        ans = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            ans[i] = 1;
            for (size_t j = 0; j < n; ++j) {
                ans[i] = ans[i] && (mrx[i * n + j] % 2 == 0);
            }
        }
        oXY(ans, n, "c", out);
        delete[] ans;

        ans = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            ans[i] = 1;
            for (size_t j = 1; j < n; ++j) {
                ans[i] = ans[i] && ((mrx[i * n] < mrx[(i + 1) * n - 1] && mrx[i * n + j - 1] < mrx[i * n + j]) ||
                                    (mrx[i * n] > mrx[(i + 1) * n - 1] && mrx[i * n + j - 1] > mrx[i * n + j]));
            }
        }
        oXY(ans, n, "d", out);
        delete[] ans;

        ans = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            ans[i] = 1;
            for (size_t j = 0; j < n; ++j) {
                ans[i] = ans[i] && (mrx[i * n + j] == mrx[(i + 1) * n - 1 - j]);
            }
        }
        oXY(ans, n, "e", out);
        delete[] ans;
        delete[] mrx;
    }

    void consoleI(std::ostream &out) {
        ioXY(std::cin, out, std::cerr, std::cout, true, true);
    }

    void fileI(std::ostream &out) {
        std::ifstream fin("in.txt");
        while (!fin.eof())
            ioXY(fin, out, std::cerr, out, false, false);
    }

    int step() {
        bool cI, cO;
        std::cout << "What would you use for input? 1 - Console, 0 - file: " << std::endl;
        LabsInputFunctions::inputBool(cI, std::cin, std::cerr, true);
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
}