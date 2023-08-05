#include "myfuncs.h"

int main() {
    MDialog dialog{};
    bool DS = true;
    while (DS) {
        if (!dialog.step()) break;
        std::cout << "Repeat? 1 - Yes, 0 - No: " << std::endl;
        MIO::inputBool(DS, std::cin, std::cerr);
    }
    return 0;
}