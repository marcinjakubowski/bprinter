#include "bprinter/PrintFormat.h"

namespace bprinter{

std::string PrintFormat::formatString() const {
  std::string format("\033[");
  switch(color()){
    case red: format += "31"; break;
    case green: format += "30"; break; //TODO
    case yellow: format += "33"; break;
    case blue: format += "30"; break; //TODO
    case white: format += "30"; break; //TODO
    case orange: format += "30"; break; //TODO
    case black:
    default: format += "30";
    
  }
  format += ";";
  if (bold())
    format += "1";
  else
    format += "0";

  return format;
}

std::string PrintFormat::unformatString() const {
  return std::string("\033[0");
}

} //namespace bprinter
