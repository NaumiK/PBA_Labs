#include "dialog.h"
#include "MIO.h"
#include <bitset>
#include <string>

namespace LabsDialogs {
    pair<uint64_t, uint64_t> iXY(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        if (printQst) qout << "Unsigned integer: " << endl;
        uint64_t n;
        MIO::inputULL(n, in, eout, printErr);
        bitset<sizeof(n)*8> bits;
        if (printQst) qout << "Binary subsequence: " << endl;
        MIO::inputBS<sizeof(n)*8>(bits, in, eout, printErr);
        return {n, bits.to_ullong()};
    }

    void ioXY(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        auto [x, y] = iXY(in, out, eout, qout, printErr, printQst);
        bitset<sizeof(x)*8> bb(x);
        out << bb << "\n";
        bb = y;
        out << bb << endl;
        size_t msb, sz = sizeof(x)*8;
        for (msb = 0; (y >> msb) != 0; ++msb);

        bool f = false;
        for (size_t i = 0; i < sz - msb; ++i) {
            f = f || (((x << (sz - msb - i)) >> (sz - msb)) == y);
        }
        out << (f ? "There is the subsequence" : "There isn't the subsequence") << endl;
    }

    void consoleI(ostream &out) {
        ioXY(cin, out, cerr, cout, true, true);
    }

    ifstream fileD(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        bool f = true;
        ifstream fin;
        if (printQst) qout << "Write name of file (in.txt as default):" << endl;
        do {
            try {
                string name;
                getline(in, name);
                if (name.empty())
                    name = "in.txt";
                fin.open(name);
                if (fin.fail()) throw MExc::ThereIsNothing();
                f = false;
            } catch (exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write name of file, please" << endl;
            }
        } while (f);
        return fin;
    }

    void fileI(ostream &out) {
        ifstream fin = fileD(cin, out, cerr, cout, true, true);
        while (!fin.eof())
            ioXY(fin, out, cerr, out, false, false);
    }

    int step() {
        bool cI, cO;
        cout << "What would you use for input? 1 - Console, 0 - file: " << endl;
        MIO::inputBool(cI, cin, cerr, true);
        cout << "What would you use for output? 1 - Console, 0 - file: " << endl;
        MIO::inputBool(cO, cin, cerr, true);

        ofstream file;
        if (!cO) file = fileD<std::ofstream>(cin, cout, cerr, cout, true, true);
        std::ostream &out = (cO ? cout : file);

        if (cI) {
            consoleI(out);
            return 1;
        } else fileI(out);
        return 0;
    }
}
