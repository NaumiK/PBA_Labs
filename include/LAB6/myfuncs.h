#ifndef LAB6_MYFUNCS_H
#define LAB6_MYFUNCS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include "dialog.h"

struct MDialog : public Dialog {
    void ioXY(Ioeqpp &iqp) override;
};

#endif//LAB6_MYFUNCS_H