#include "myfuncs.h"
#include "constants.h"
#include "MExc.h"
#include "MIO.h"
#include <stdint.h>
#include <string>
#include <vcruntime.h>
#include "dialog.h"

#if defined USE_VECTOR
#include "Matrix.h"
#include <vector>
namespace {
    Matrix iXY(Dialog::Ioeqpp &iqp) {
        try {
            if (iqp.printQst) iqp.qout << "n" << std::endl;
            size_t n;
            if (MIO::inputULL(n, iqp.in, iqp.eout, iqp.printErr) != 0) throw MExc::ThereIsNothing();
            Matrix mrx{n, n};
            if (iqp.printQst) iqp.qout << "Matrix nxn" << std::endl;
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (MIO::inputStreamLL(mrx[i][j], iqp.in, iqp.eout, iqp.printErr) != 0)
                        throw MExc::ThereIsNothing();
                }
            }
            return mrx;
        } catch (std::exception &err) {
            iqp.eout << err.what() << std::endl;
        }
        return {0, 0};
    }

    void oXY(const std::vector<int64_t> &vr, const std::string &exc, std::ostream &out) {
        out << exc << ") ";
        for (size_t i = 1, endi = vr.size(); i <= endi; ++i) {
            bool f = false;
            for (size_t j = 0, endj = vr.size(); j < endj; ++j) {
                if (vr[j] == i) {
                    out << j + 1 << " ";
                    f = true;
                }
            }
            if (f) out << "\t";
        }
        out << std::endl;
    }
}
void MDialog::ioXY(Dialog::Ioeqpp &iqp) {
    Matrix mrx = iXY(iqp);

    auto ans = std::vector<int64_t>(mrx.cols());
    for (size_t i = 0, n = ans.size(); i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i][j] == 0);
        }
    }
    oXY(ans, "a", iqp.out);

    ans = std::vector<int64_t>(mrx.cols());
    for (size_t i = 0, n = ans.size(); i < n; ++i) {
        ans[i] = 0;
        for (size_t j = 0; j < n; ++j) {
            bool f = true;
            for (size_t k = 0; k < n; ++k) {
                f = f && (mrx[i][k] == mrx[j][k]);
            }
            if (f) ans[j] = i + 1;
        }
    }
    oXY(ans, "b", iqp.out);

    ans = std::vector<int64_t>(mrx.cols());
    for (size_t i = 0, n = ans.size(); i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i][j] % 2 == 0);
        }
    }
    oXY(ans, "c", iqp.out);

    ans = std::vector<int64_t>(mrx.cols());
    for (size_t i = 0, n = ans.size(); i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 1; j < n; ++j) {
            ans[i] = ans[i] && ((mrx[i][0] < mrx[i][n - 1] && mrx[i][j - 1] < mrx[i][j]) ||
                                (mrx[i][0] > mrx[i][n - 1] && mrx[i][j - 1] > mrx[i][j]));
        }
    }
    oXY(ans, "d", iqp.out);

    ans = std::vector<int64_t>(mrx.cols());
    for (size_t i = 0, n = ans.size(); i < n; ++i) {
        ans[i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[i] = ans[i] && (mrx[i][j] == mrx[i][n - j - 1]);
        }
    }
    oXY(ans, "e", iqp.out);
}

#elif defined USE_ONLY_MATRIX
#include "Matrix.h"
namespace {
    Matrix iXY(Dialog::Ioeqpp &iqp) {
        try {
            if (iqp.printQst) iqp.qout << "n" << std::endl;
            size_t n;
            if (MIO::inputULL(n, iqp.in, iqp.eout, iqp.printErr) != 0) throw MExc::ThereIsNothing();
            Matrix mrx{n, n};
            if (iqp.printQst) iqp.qout << "Matrix nxn" << std::endl;
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (MIO::inputStreamLL(mrx[i][j], iqp.in, iqp.eout, iqp.printErr) != 0)
                        throw MExc::ThereIsNothing();
                }
            }
            return mrx;
        } catch (std::exception &err) {
            iqp.eout << err.what() << std::endl;
        }
        return {0, 0};
    }

    void oXY(const Matrix &mrx, const std::string &exc, std::ostream &out) {
        out << exc << ") ";
        for (size_t i = 1, endi = mrx.cols(); i <= endi; ++i) {
            bool f = false;
            for (size_t j = 0, endj = mrx.cols(); j < endj; ++j) {
                if (mrx[0][j] == i) {
                    out << j + 1 << " ";
                    f = true;
                }
            }
            if (f) out << "\t";
        }
        out << std::endl;
    }
} 
void MDialog::ioXY(Dialog::Ioeqpp &iqp) {
    Matrix mrx = iXY(iqp);
    auto ans = Matrix(1, mrx.cols());
    for (size_t i = 0, n = mrx.cols(); i < n; ++i) {
        ans[0][i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[0][i] = ans[0][i] && (mrx[i][j] == 0);
        }
    }
    oXY(ans, "a", iqp.out);

    ans = {1, mrx.cols()};
    for (size_t i = 0, n = ans.cols(); i < n; ++i) {
        ans[0][i] = 0;
        for (size_t j = 0; j < n; ++j) {
            bool f = true;
            for (size_t k = 0; k < n; ++k) {
                f = f && (mrx[i][k] == mrx[j][k]);
            }
            if (f) ans[0][j] = i + 1;
        }
    }
    oXY(ans, "b", iqp.out);

    ans = {1, mrx.cols()};
    for (size_t i = 0, n = ans.cols(); i < n; ++i) {
        ans[0][i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[0][i] = ans[0][i] && (mrx[i][j] % 2 == 0);
        }
    }
    oXY(ans, "c", iqp.out);

    ans = {1, mrx.cols()};
    for (size_t i = 0, n = ans.cols(); i < n; ++i) {
        ans[0][i] = 1;
        for (size_t j = 1; j < n; ++j) {
            ans[0][i] = ans[0][i] && ((mrx[i][0] < mrx[i][n - 1] && mrx[i][j - 1] < mrx[i][j]) ||
                                (mrx[i][0] > mrx[i][n - 1] && mrx[i][j - 1] > mrx[i][j]));
        }
    }
    oXY(ans, "d", iqp.out);

    ans = {1, mrx.cols()};
    for (size_t i = 0, n = ans.cols(); i < n; ++i) {
        ans[0][i] = 1;
        for (size_t j = 0; j < n; ++j) {
            ans[0][i] = ans[0][i] && (mrx[i][j] == mrx[i][n - j - 1]);
        }
    }
    oXY(ans, "e", iqp.out);
}

#else
namespace {
    std::pair<int64_t *, size_t> iXY(Dialog::Ioeqpp &iqp) {
        size_t n = 0;
        int64_t *mrx = nullptr;

        try {
            if (iqp.printQst) iqp.qout << "n" << std::endl;
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
#endif
