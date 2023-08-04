#ifndef LABS_DIALOG_H
#define LABS_DIALOG_H

#include <iostream>
#include <fstream>
#include <functional>
#include "MExc.h"
#include "MIO.h"

using namespace std;

namespace LabsDialogs {
    struct Ioeqpp {
        istream &in;
        ostream &out, &eout, &qout;
        bool printErr, printQst;
    };

    void ioXY(Ioeqpp &iqp);

    void consoleI(ostream &out);

    void fileI(ostream &out);

    int step();

    template<typename T=ifstream>
    T fileD(Ioeqpp &iqp);

    template<typename T>
    T fileD(Ioeqpp &iqp) {
        bool f = true;
        T fio;
        string name = ((typeid(T) == typeid(ifstream)) ? "in.txt" : "out.txt");
        if (typeid(T) != typeid(ifstream) && typeid(T) != typeid(ofstream)) throw MExc::NotThatType();
        if (iqp.printQst)
            iqp.qout << "Write name of file " << "(" << name << " as default" << ")" << ":" << endl;
        do {
            try {
                getline(iqp.in, name);
                if (name.empty())
                    name = ((typeid(T) == typeid(ifstream)) ? "in.txt" : "out.txt");
                fio.open(name);
                if (fio.fail()) throw MExc::ThereIsNothing();
                f = false;
            } catch (exception &err) {
                if (iqp.printErr) iqp.eout << err.what() << "\n" << "Write name of file, please" << endl;

            }
        } while (f);
        return fio;
    }

    template<class T>
    struct FuncWithDesc {
        std::string desc;
        std::function<T> func;
    };

    template<class T>
    uint64_t optionD(vector<FuncWithDesc<T>> &options, Ioeqpp &iqp) {
        if (iqp.printQst) {
            iqp.qout << "Choose an option:\n";
            for (int i = 0; i < options.size(); ++i) {
                iqp.qout << i + 1 << " - " << options[i].desc << ";\n";
            }
        }
        uint64_t option;
        MIO::chooseVariant(option, options.size(), iqp.in, iqp.eout, iqp.printErr);
        return option - 1;
    }
}

#endif //LABS_DIALOG_H
