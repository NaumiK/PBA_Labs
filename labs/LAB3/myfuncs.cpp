#include "myfuncs.h"
#include "constants.h"
#include "MExc.h"
#include "MIO.h"
#include <string>
#include "dialog.h"


namespace {
    std::pair<int64_t *, size_t> iXY(Dialog::Ioeqpp &iqp) {
        size_t n = 0;
        int64_t *mrx = nullptr;
        if (iqp.printQst) iqp.qout << "n" << std::endl;

        try {
            if (MIO::inputULL(n, iqp.in, iqp.eout, iqp.printErr) != 0) throw MExc::ThereIsNothing();
            mrx = new int64_t[n * n];
            if (iqp.printQst) iqp.qout << "Matrix nxn:" << std::endl;
            for (size_t i = 0; i < n * n; ++i)
                if (MIO::inputStreamLL(mrx[i], iqp.in, iqp.eout, iqp.printErr) != 0)
                    throw MExc::ThereIsNothing();
        } catch (std::exception &err) {
            iqp.eout << err.what() << std::endl;
            delete[] mrx;
            return {nullptr, 0};
        }
        return {mrx, n};
    }

    void oXY(const uint32_t *inp, size_t n, const std::string &exs, std::ostream &out) {
        out << exs << ") ";
        for (int i = 1; i <= n; ++i) {
            bool f = false;
            for (int j = 0; j < n; ++j) {
                if (inp[j] == i) {
                    out << j + 1 << " ";
                    f = true;
                }
            }
            if (f) out << "\t";
        }
        out << std::endl;
    }
}

void MDialog::ioXY(Ioeqpp &iqp) {
    auto [mrx, n] = iXY(iqp);
    if (mrx == nullptr) return;
    auto *ans = new uint32_t[n];
    for (size_t i = 0; i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i * n + j] == 0);
        }
    }
    oXY(ans, n, "a", iqp.out);
    delete[] ans;

    ans = new uint32_t[n];
    for (size_t i = 0; i < n; ++i) {
        ans[i] = 0;
        for (size_t j = 0; j < n; ++j) {
            bool f = true;
            for (size_t k = 0; k < n; ++k) {
                f = f && (mrx[i * n + k] == mrx[j * n + k]);
            }
            if (f) ans[j] = i + 1;
        }
    }
    oXY(ans, n, "b", iqp.out);
    delete[] ans;

    ans = new uint32_t[n];
    for (size_t i = 0; i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i * n + j] % 2 == 0);
        }
    }
    oXY(ans, n, "c", iqp.out);
    delete[] ans;

    ans = new uint32_t[n];
    for (size_t i = 0; i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 1; j < n; ++j) {
            ans[i] = ans[i] && ((mrx[i * n] < mrx[(i + 1) * n - 1] && mrx[i * n + j - 1] < mrx[i * n + j]) ||
                                (mrx[i * n] > mrx[(i + 1) * n - 1] && mrx[i * n + j - 1] > mrx[i * n + j]));
        }
    }
    oXY(ans, n, "d", iqp.out);
    delete[] ans;

    ans = new uint32_t[n];
    for (size_t i = 0; i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i * n + j] == mrx[(i + 1) * n - 1 - j]);
        }
    }
    oXY(ans, n, "e", iqp.out);
    delete[] ans;
    delete[] mrx;
}
