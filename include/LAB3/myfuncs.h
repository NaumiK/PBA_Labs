#ifndef LAB3_MYFUNCS_H
#define LAB3_MYFUNCS_H

#include <cmath>
#include <fstream>
#include <iostream>

#include "dialog.h"

struct MDialog : public Dialog {
  void ioXY(Ioeqpp &iqp) override;
};

#endif // LAB3_MYFUNCS_H