#include <iostream>
#include <sstream>
#include "LAB4/myfuncs.h"
#include "dialog.h"
#include "MIO.h"

using namespace std;

int main(int argc, char **argv) {
    MDialog dialog{};
    try {
        if (argc < 3) throw MExc::ThereIsNothing();
        stringstream sst;
        for (int i = 1; i < argc; ++i) sst << argv[i] << "\n";
        Dialog::Ioeqpp iqp{sst, cout, cerr, cout, false, false};
        dialog.ioXY(iqp);
    } catch (exception &err) {
        cerr << err.what() << "\n" << "Give me the number and some sequence, please" << endl;
    }
    return 0;
}