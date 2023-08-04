#include "dialog.h"
#include "MyString.h"
#include "MIO.h"

namespace LabsDialogs {
    MyString iXY(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        if (printQst) qout << "Write your string, please" << endl;
        MyString str;
        in >> str;
        return str;
    }

    void oXY(MyString &str, ostream &out) {
        out << str.c_str() << endl;
    }

    void ioXY(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        MyString x = iXY(in, out, eout, qout, printErr, printQst);
        MyString y(x);
        oXY(y, out);
    }

    void consoleI(ostream &out) {
        ioXY(cin, out, cerr, cout, true, true);
    }


    void fileI(ostream &out) {
        auto fin = fileD<ifstream>(cin, out, cerr, cout, true, true);
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
