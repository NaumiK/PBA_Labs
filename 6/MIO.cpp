#include "MIO.h"
#include "MExc.h"
#include <string>

uint8_t MIO::inputStreamLL(int64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true;
    do {
        try {
            if (in.eof()) return 1;
            int64_t tmp;
            if ((in >> tmp).fail()) throw MExc::NotThatType();
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

uint8_t MIO::inputULL(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true;
    std::string s;
    do {
        try {
            if (in.eof()) return 1;
            getline(in, s);
            if (s.find('-') != std::string::npos) throw MExc::NotThatType();
            x = stoul(s);
            f = false;
        } catch (std::exception &err) {
            if (printErr) eout << err.what() << "\n" << "Write an unsigned integer, please" << std::endl;
        }
    } while (f);
    return 0;
}

uint8_t MIO::inputNatural(uint64_t &x, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true;
    std::string s;
    do {
        try {
            uint64_t tmp;
            if (MIO::inputULL(tmp, in, eout, printErr)) return 1;
            if (tmp == 0) throw MExc::NotThatType();
            x = tmp;
            f = false;
        } catch (std::exception &err) {
            if (printErr) eout << err.what() << "\n" << "Write a natural number, please" << std::endl;
        }
    } while (f);
    return 0;
}

uint8_t MIO::inputBool(bool &b, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true;
    std::string s;
    do {
        try {
            if (in.eof()) return 1;
            getline(in, s);
            s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
            if (!(s == "1" || s == "0")) throw MExc::NotThatType();
            b = (s == "1");
            f = false;
        } catch (std::exception &err) {
            if (printErr && !s.empty())
                eout << err.what() << "\n" << "Write a boolean value (0, 1), please" << std::endl;
        }
    } while (f);
    return 0;
}

uint8_t MIO::chooseVariant(uint64_t &x, uint64_t border, std::istream &in, std::ostream &eout, bool printErr) {
    bool f = true;
    std::string s;
    do {
        try {
            uint64_t tmp;
            if (MIO::inputNatural(tmp, in, eout, printErr)) return 1;
            if (tmp > border) throw MExc::NotThatType();
            x = tmp;
            f = false;
        } catch (std::exception &err) {
            if (printErr)
                eout << err.what() << "\n" << "Write a natural number not greater than " << border << std::endl;
        }
    } while (f);
    return 0;
}
