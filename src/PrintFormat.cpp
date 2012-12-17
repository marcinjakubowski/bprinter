#include "bprinter/PrintFormat.h"

namespace bprinter{

std::string PrintFormat::formatString() const {
  if (color() == c_none)
    return "";


  std::string format("\033[");
  if (bold())
    format += "1";
  else
    format += "0";

  format += ";";

  switch(color()){
    case c_red: format += "31"; break;
    case c_green: format += "30"; break; //TODO
    case c_yellow: format += "33"; break;
    case c_blue: format += "30"; break; //TODO
    case c_white: format += "30"; break; //TODO
    case c_orange: format += "30"; break; //TODO
    case c_black:
    default: format += "30";
    
  }

  format += "m";

  return format;
}

std::string PrintFormat::unformatString() const {
  if (color() == c_none)
    return "";
  return std::string("\033[0m");
}

} //namespace bprinter
