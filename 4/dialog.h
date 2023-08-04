#ifndef LABS_MYFUNCS_H
#define LABS_MYFUNCS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include "MExc.h"
#include <string>

using namespace std;

namespace LabsDialogs {
    void ioXY(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst);
    void consoleI(ostream &out);
    void fileI(ostream &out);
    int step();

    template<typename T>
    T fileD(istream &in, ostream &out, ostream &eout, ostream &qout, bool printErr, bool printQst) {
        bool f = true;
        T fio;
        string name = ((typeid(T) == typeid(ifstream)) ? "in.txt" : "out.txt");
        if (typeid(T) != typeid(ifstream) && typeid(T) != typeid(ofstream)) throw MExc::NotThatType();
        if (printQst)
            qout << "Write name of file " << "(" << name << " as default" << ")" << ":" << endl;
        do {
            try {
                getline(in, name);
                if (name.empty())
                    name = ((typeid(T) == typeid(ifstream)) ? "in.txt" : "out.txt");
                fio.open(name);
                if (fio.fail()) throw MExc::ThereIsNothing();
                f = false;
            } catch (exception &err) {
                if (printErr) eout << err.what() << "\n" << "Write name of file, please" << endl;

            }
        } while (f);
        return fio;
    }
}
#endif //LABS_MYFUNCS_H
