#include "dialog.h"
 
void Dialog::consoleI(std::ostream &out) {
    Ioeqpp iqp = {std::cin, out, std::cerr, std::cout, true, true};
    ioXY(iqp);
}


void Dialog::fileI(std::ostream &out) {
    Ioeqpp iqp1 = {std::cin, out, std::cerr, std::cout, true, true};
    std::ifstream fin = fileD(iqp1);
    Ioeqpp iqp2 = {fin, out, std::cerr, out, false, false};
    while (!fin.eof())
        ioXY(iqp2);
}


int Dialog::step() {
    Ioeqpp iqp1 = {std::cin, std::cout, std::cerr, std::cout, true, true};
    bool cI, cO;
    iqp1.qout << "What would you use for input? 1 - Console, 0 - file: " << std::endl;
    MIO::inputBool(cI, iqp1.in, iqp1.eout, true);
    iqp1.qout << "What would you use for output? 1 - Console, 0 - file: " << std::endl;
    MIO::inputBool(cO, iqp1.in, iqp1.eout, true);

    std::ofstream file;
    if (!cO) file = fileD<std::ofstream>(iqp1);
    std::ostream &out = (cO ? std::cout : file);

    if (cI) {
        consoleI(out);
        return 1;
    } else fileI(out);
    return 0;
}