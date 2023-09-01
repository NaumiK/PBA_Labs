#ifndef LABS_MEXC_H
#define LABS_MEXC_H

#include <exception>

namespace MExc {
class NotThatType : public std::exception {
public:
  [[nodiscard]] const char *what() const noexcept override;
};

class ThereIsNothing : public std::exception {
public:
  [[nodiscard]] const char *what() const noexcept override;
};
} // namespace MExc

#endif // LABS_MEXC_H
