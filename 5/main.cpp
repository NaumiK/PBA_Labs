#include <iostream>
#include <sstream>
#include "dialog.h"
#include "MIO.h"

using namespace std;

int main(int argc, char **argv) {
    try {
        if (argc < 3) throw MExc::ThereIsNothing();
        stringstream sst;
        for (int i = 1; i < argc; ++i) sst << argv[i] << "\n";
        LabsDialogs::ioXY(sst, cout, cerr, cout, false, false);
    } catch (exception &err) {
        cerr << err.what() << "\n" << "Give me the number and some sequence, please" << endl;
    }
    return 0;
}