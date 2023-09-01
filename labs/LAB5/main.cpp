#include "LAB4/myfuncs.h"
#include "MIO.h"
#include "dialog.h"
#include "version.h"
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
  std::cout << "Currently you use the " << LABS_VERSION
            << " version of the Labs.\n"
            << "Git commit hash: " << GIT_COMMIT_HASH << "." << std::endl;
  MDialog dialog{};
  try {
    if (argc < 3)
      throw MExc::ThereIsNothing();
    std::stringstream sst;
    for (int i = 1; i < argc; ++i)
      sst << argv[i] << "\n";
    Dialog::Ioeqpp iqp{sst, std::cout, std::cerr, std::cout, false, false};
    dialog.ioXY(iqp);
  } catch (std::exception &err) {
    std::cerr << err.what() << "\n"
              << "Give me the number and some sequence, please" << std::endl;
  }
  return 0;
}