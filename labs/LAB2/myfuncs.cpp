#include "myfuncs.h"
#include "constants.h"
#include "MExc.h"
#include "MIO.h"
#include <string>
#include "dialog.h"


namespace {
    std::pair<uint64_t *, uint64_t> iXY(Dialog::Ioeqpp &iqp) {
        uint64_t n = -1, kd = 0;
        static uint64_t arr[arrsize];
        if (iqp.printQst) iqp.qout << "n" << std::endl;
        if (MIO::inputNatural(n, iqp.in, iqp.eout, iqp.printErr) == 0) {
            for (int i = 1; i <= n; ++i) {
                if (n % i == 0) arr[kd++] = i;
            }
        } else {
            iqp.eout << "There is nothing" << std::endl;
        }
        return {arr, kd};
    }

    void oXY(uint64_t *inp, uint64_t n, std::ostream &out) {
        out << "Natural divisors of a number " << inp[n - 1] << " are:\n";
        for (int i = 0; i < n; ++i) {
            out << inp[i] << " ";
        }
        out << std::endl;
    }
}

void MDialog::ioXY(Ioeqpp &iqp) {
    auto [arr, n] = iXY(iqp);
    if (n != 0) oXY(arr, n, iqp.out);
}