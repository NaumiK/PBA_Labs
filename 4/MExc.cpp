#include "MExc.h"

const char *MExc::NotThatType::what() const noexcept {
    return "The type of input is not correct.";
}

const char *MExc::ThereIsNothing::what() const noexcept {
    return "There is nothing";
}

