#ifndef BPRINTER_PRINTFORMAT_H
#define BPRINTER_PRINTFORMAT_H

#include <string>

namespace bprinter{

enum PrintColor {black, red, green, yellow, blue, orange, white};

class PrintFormat{
public:
  PrintFormat(PrintColor color = black, bool bold = false) :
    _color(color),
    _bold(bold) {}
  ~PrintFormat() {}

  inline PrintColor color() const {
    return _color;
  }
  inline bool bold() const {
    return _bold;
  }

  std::string formatString() const;
  std::string unformatString() const;

private:
  const PrintColor _color;
  const bool _bold;
};


} //namespace bprinter


#endif //BPRINTER_PRINTFORMAT_H

