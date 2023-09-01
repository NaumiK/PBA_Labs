#ifndef LABS_DIALOG_H
#define LABS_DIALOG_H

#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "MExc.h"
#include "MIO.h"

struct Dialog {
    struct Ioeqpp {
        std::istream &in;
        std::ostream &out, &eout, &qout;
        bool printErr, printQst;
    };

    virtual void ioXY(Ioeqpp &iqp) = 0;

    void consoleI(std::ostream &out);

    void fileI(std::ostream &out);

    int step();

    template <typename T = std::ifstream>
    static T fileD(Ioeqpp &iqp) {
        bool f = true;
        T fio;
        std::string name =
            ((typeid(T) == typeid(std::ifstream)) ? "in.txt" : "out.txt");
        if (typeid(T) != typeid(std::ifstream) &&
            typeid(T) != typeid(std::ofstream))
            throw MExc::NotThatType();
        if (iqp.printQst)
            iqp.qout << "Write name of file "
                     << "(" << name << " as default"
                     << ")"
                     << ":" << std::endl;
        do {
            try {
                std::getline(iqp.in, name);
                if (name.empty())
                    name = ((typeid(T) == typeid(std::ifstream)) ? "in.txt"
                                                                 : "out.txt");
                fio.open(name);
                if (fio.fail()) throw MExc::ThereIsNothing();
                f = false;
            } catch (std::exception &err) {
                if (iqp.printErr)
                    iqp.eout << err.what() << "\n"
                             << "Write name of file, please" << std::endl;
            }
        } while (f);
        return fio;
    }

    template <class T>
    struct FuncWithDesc {
        std::string desc;
        std::function<T> func;
    };

    template <class T>
    static uint64_t optionD(std::vector<FuncWithDesc<T>> &options,
                            Ioeqpp &iqp) {
        if (iqp.printQst) {
            iqp.qout << "Choose an option:\n";
            for (int i = 0; i < options.size(); ++i) {
                iqp.qout << i + 1 << " - " << options[i].desc << ";\n";
            }
        }
        uint64_t option;
        MIO::chooseVariant(option, options.size(), iqp.in, iqp.eout,
                           iqp.printErr);
        return option - 1;
    }

    virtual ~Dialog() = default;
};

#endif  // LABS_DIALOG_H
