#ifndef BPRINTER_PRINTFORMAT_H
#define BPRINTER_PRINTFORMAT_H

#include <string>

namespace bprinter {

enum PrintColor {c_none,
                 c_black,
                 c_red,
		 c_green,
		 c_yellow,
		 c_blue,
		 c_orange,
		 c_white };

class PrintFormat {
public:
  PrintFormat(PrintColor color = c_black, bool bold = false) :
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
  PrintColor _color;
  bool _bold;
};

namespace format {
  const PrintFormat none = PrintFormat(c_none);
  const PrintFormat black = PrintFormat(c_black);
  const PrintFormat red = PrintFormat(c_red);
  const PrintFormat yellow = PrintFormat(c_yellow);
} //namespace format

} //namespace bprinter


#endif //BPRINTER_PRINTFORMAT_H

