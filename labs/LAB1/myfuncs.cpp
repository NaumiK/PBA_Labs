#include "myfuncs.h"
#include "constants.h"
#include "MExc.h"
#include "MIO.h"
#include <iostream>
#include <string>
#include "dialog.h"

namespace {
    double y(double x) {
        return (x * x - 3 * x + 2) / (sqrt(2 * x * x * x - 1));
    }

    std::pair<double *, size_t> iXY(Dialog::Ioeqpp &iqp) {
        size_t n = 0;
        static double arr[arrsize];
        if (iqp.printQst) iqp.qout << "n" << std::endl;
        try {
            if (MIO::inputNatural(n, iqp.in, iqp.eout, iqp.printErr) != 0) throw MExc::ThereIsNothing();
            for (int i = 0; i <= n; ++i) {
                arr[i] = y(1 + 0.1 * i);
            }
        } catch (std::exception &err) {
            if (iqp.printErr) iqp.eout << err.what() << std::endl;
        }
        return {arr, n};
    }

    void oXY(double inp[], size_t n, std::ostream &out) {
        out << "x\ty" << std::endl;
        for (uint64_t i = 0; i <= n; ++i) {
            out << 1 + 0.1 * (double)i << "\t" << inp[i] << std::endl;
        }
    }
}

void MDialog::ioXY(Ioeqpp &iqp) {
    auto [arr, n] = iXY(iqp);
    if (n != 0) oXY(arr, n, iqp.out);
}