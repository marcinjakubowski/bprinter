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
    case c_green: format += "32"; break;
    case c_yellow: format += "33"; break;
    case c_blue: format += "34"; break;
    case c_magenta: format += "35"; break;
    case c_cyan: format += "36"; break;
    case c_white: format += "37"; break;
    //default
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
