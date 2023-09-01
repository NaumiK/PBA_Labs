#include "myfuncs.h"
#include "version.h"

int t();

int main() {
  std::cout << "Currently you use the " << LABS_VERSION
            << " version of the Labs.\n"
            << "Git commit hash: " << GIT_COMMIT_HASH << "." << std::endl;
  MDialog dialog{};
  bool DS = true;
  while (DS) {
    if (!dialog.step())
      break;
    std::cout << "Repeat? 1 - Yes, 0 - No: " << std::endl;
    MIO::inputBool(DS, std::cin, std::cerr);
  }
  return 0;
}