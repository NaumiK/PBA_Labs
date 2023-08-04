#include "dialog.h"
#include "MIO.h"
#include "MLL.h"
#include <vector>

namespace LabsDialogs {
    void cntD(MLL *mll, Ioeqpp &iqp) {
        if (iqp.printQst) iqp.qout << "Write string, which ends by \'$\' sign:" << endl;
        string str;
        getline(iqp.in, str, '$');
        iqp.in.ignore();
        vector<FuncWithDesc<uint64_t(MLL *, string &)>> options = {
                {"same full name", [](MLL *mll, string &str) { return mll->cnt(str, 0); }},
                {"same job",       [](MLL *mll, string &str) { return mll->cnt(str, 1); }},
                {"same place",     [](MLL *mll, string &str) { return mll->cnt(str, 2); }},
        };
        iqp.out << options[optionD<uint64_t(MLL *, string &)>(options, iqp)].func(mll, str) << endl;
    }

    void ioXY(Ioeqpp &iqp) {
        auto *mll = new MLL;
        vector<FuncWithDesc<bool(MLL *, Ioeqpp &)>> options = {
                {"print elements",     [](MLL *mll, Ioeqpp &iqp) {
                    mll->print(iqp.out);
                    iqp.qout << endl;
                    return true;
                }},
                {"print table",        [](MLL *mll, Ioeqpp &iqp) {
                    mll->printT(iqp.out);
                    return true;
                }},
                {"count coincidences", [](MLL *mll, Ioeqpp &iqp) {
                    cntD(mll, iqp);
                    return true;
                }},
                {"reset",              [](MLL *mll, Ioeqpp &iqp) {
                    mll->clean();
                    return true;
                }},
                {"read file",          [](MLL *mll, Ioeqpp &iqp) {
                    auto fin = fileD<ifstream>(iqp);
                    while (!fin.eof()) fin >> *mll;
                    fin.close();
                    return true;
                }},
                {"write to file",      [](MLL *mll, Ioeqpp &iqp) {
                    auto fout = fileD<ofstream>(iqp);
                    fout << *mll;
                    fout.close();
                    return true;
                }},
                {"exit",               [](MLL *mll, Ioeqpp &iqp) { return false; }}
        };

        bool f = true;
        while (f) f = options[optionD<bool(MLL *, Ioeqpp &)>(options, iqp)].func(mll, iqp);

        delete mll;
    }

    void consoleI(ostream &out) {
        Ioeqpp iqp = {cin, out, cerr, cout, true, true};
        ioXY(iqp);
    }


    void fileI(ostream &out) {
        Ioeqpp iqp1 = {cin, out, cerr, cout, true, true};
        ifstream fin = fileD(iqp1);
        Ioeqpp iqp2 = {fin, out, cerr, out, false, false};
        while (!fin.eof())
            ioXY(iqp2);
    }


    int step() {
        Ioeqpp iqp1 = {cin, cout, cerr, cout, true, true};
        bool cI, cO;
        iqp1.qout << "What would you use for input? 1 - Console, 0 - file: " << endl;
        MIO::inputBool(cI, iqp1.in, iqp1.eout, true);
        iqp1.qout << "What would you use for output? 1 - Console, 0 - file: " << endl;
        MIO::inputBool(cO, iqp1.in, iqp1.eout, true);

        ofstream file;
        if (!cO) file = fileD<std::ofstream>(iqp1);
        std::ostream &out = (cO ? cout : file);

        if (cI) {
            consoleI(out);
            return 1;
        } else fileI(out);
        return 0;
    }
}