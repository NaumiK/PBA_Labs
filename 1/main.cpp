#include <iostream>
#include <cmath>
#include <fstream>
#include "myfuncs.h"
#include <vector>
#include "constants.h"

int main() {
    bool DS = true;
    while (DS) {
        if (!LabsDialogs::step()) break;
        std::cout << "Repeat? 1 - Yes, 0 - No: " << std::endl;
        LabsInputFunctions::inputBool(DS, std::cin, std::cerr);
    }
    return 0;
}