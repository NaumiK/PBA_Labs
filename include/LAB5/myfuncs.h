#ifndef LAB5_MYFUNCS_H
#define LAB5_MYFUNCS_H

#include "dialog.h"
#include <cmath>
#include <fstream>
#include <iostream>

struct MDialog : public Dialog {
  void ioXY(Ioeqpp &iqp) override;
};

#endif // LAB5_MYFUNCS_H