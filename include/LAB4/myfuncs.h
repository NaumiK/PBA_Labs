#ifndef LAB4_MYFUNCS_H
#define LAB4_MYFUNCS_H

#include "dialog.h"
#include <cmath>
#include <fstream>
#include <iostream>

struct MDialog : public Dialog {
  void ioXY(Ioeqpp &iqp) override;
};

#endif // LAB4_MYFUNCS_H