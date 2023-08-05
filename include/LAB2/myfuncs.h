#ifndef LAB2_MYFUNCS_H
#define LAB2_MYFUNCS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include "dialog.h"

struct MDialog : public Dialog {
    void ioXY(Ioeqpp &iqp) override;
};

#endif//LAB2_MYFUNCS_H
