#include <iostream>
#include <sstream>
#include "LAB4/myfuncs.h"
#include "dialog.h"
#include "MIO.h"
#include "version.h"


int main(int argc, char **argv) {
    #ifdef PRINT_VERSION_INFO
    std::cout << "Currently you use the " << LABS_VERSION << " version of the Labs.\n" << "Git commit hash: " << GIT_COMMIT_HASH << "." << std::endl;
    #endif
    MDialog dialog{};
    try {
        if (argc < 3) throw MExc::ThereIsNothing();
        std::stringstream sst;
        for (int i = 1; i < argc; ++i) sst << argv[i] << "\n";
        Dialog::Ioeqpp iqp{sst, std::cout, std::cerr, std::cout, false, false};
        dialog.ioXY(iqp);
    } catch (std::exception &err) {
        std::cerr << err.what() << "\n" << "Give me the number and some sequence, please" << std::endl;
    }
    return 0;
}