#include <iostream>
#include "dialog.h"
#include "MIO.h"

using namespace std;

int main() {
    bool DS = true;
    while (DS) {
        if (!LabsDialogs::step()) break;
        cout << "Repeat? 1 - Yes, 0 - No: " << endl;
        MIO::inputBool(DS, cin, cerr);
    }
    return 0;
}