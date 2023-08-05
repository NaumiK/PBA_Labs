#ifndef LAB4_MYFUNCS_H
#define LAB4_MYFUNCS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include "dialog.h"

struct MDialog : public Dialog {
    void ioXY(Ioeqpp &iqp) override;
};

#endif//LAB4_MYFUNCS_H