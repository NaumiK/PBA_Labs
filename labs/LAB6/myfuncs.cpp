#include "myfuncs.h"
#include "MLL.h"

namespace {
    void cntD(MLL *mll, Dialog::Ioeqpp &iqp) {
        if (iqp.printQst) iqp.qout << "Write string, which ends by \'$\' sign:" << std::endl;
        std::string str;
        getline(iqp.in, str, '$');
        iqp.in.ignore();
        std::vector<Dialog::FuncWithDesc<uint64_t(MLL *, std::string &)>> options = {
                {"same full name", [](MLL *mll, std::string &str) { return MLL_cnt_coincidences(*mll, str, 0); }},
                {"same job",       [](MLL *mll, std::string &str) { return MLL_cnt_coincidences(*mll, str, 1); }},
                {"same place",     [](MLL *mll, std::string &str) { return MLL_cnt_coincidences(*mll, str, 2); }},
        };
        iqp.out << options[Dialog::optionD<uint64_t(MLL *, std::string &)>(options, iqp)].func(mll, str) << std::endl;
    }
}
} // namespace

void MDialog::ioXY(Ioeqpp &iqp) {
    auto *mll = new MLL;
    std::vector<Dialog::FuncWithDesc<bool(MLL *, Dialog::Ioeqpp &)>> options = {
            {"print elements",     [](MLL *mll, Dialog::Ioeqpp &iqp) {
                MLL_print(*mll, iqp.out);
                iqp.qout << std::endl;
                return true;
            }},
            {"print table",        [](MLL *mll, Dialog::Ioeqpp &iqp) {
                MLL_printT(*mll, iqp.out);
                return true;
            }},
            {"count coincidences", [](MLL *mll, Dialog::Ioeqpp &iqp) {
                cntD(mll, iqp);
                return true;
            }},
            {"reset",              [](MLL *mll, Dialog::Ioeqpp &iqp) {
                mll->clean();
                return true;
            }},
            {"read file",          [](MLL *mll, Dialog::Ioeqpp &iqp) {
                auto fin = Dialog::fileD<std::ifstream>(iqp);
                while (!fin.eof()) fin >> *mll;
                fin.close();
                return true;
            }},
            {"write to file",      [](MLL *mll, Dialog::Ioeqpp &iqp) {
                auto fout = Dialog::fileD<std::ofstream>(iqp);
                fout << *mll;
                fout.close();
                return true;
            }},
            {"exit",               [](MLL *mll, Dialog::Ioeqpp &iqp) { return false; }}
    };

  bool f = true;
  while (f)
    f = options[Dialog::optionD<bool(MLL *, Dialog::Ioeqpp &)>(options, iqp)]
            .func(mll, iqp);

  delete mll;
}
