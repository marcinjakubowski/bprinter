#include "bprinter/TablePrinter.h"

#include "bprinter/PrintFormat.h"

#define _USE_MATH_DEFINES
#include <math.h>

using bprinter::TablePrinter;

int main(int argc, char** argv){
  TablePrinter tp;
  tp.addColumn("Name", 25);
  tp.addColumn("Age", 5);
  tp.addColumn("Position", 30);
  tp.addColumn("Allowance", 9);

  tp.printHeader();
  tp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
  tp << "John Doe" << 26 << "Too much float" << 125456789.123456789;
  tp << "John Doe" << 26 << "Typical Int" << 1254;
  tp << "John Doe" << 26 << "Typical float" << 1254.36;
  tp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
  tp << "John Doe" << 26 << "Exact size int" << 125456789;
  tp << "John Doe" << 26 << "Exact size int" << -12545678;
  tp << "John Doe" << 26 << "Exact size int" << -125456789;
  tp << "John Doe" << 26 << "Exact size float" << -1254567.8f;
  tp << "John Doe" << 26 << "Negative Int" << -1254;
  tp << "Jane Doe" << bprinter::endl();
  tp << "Tom Doe" << 7 << "Student" << -M_PI;
  tp.printFooter();


  TablePrinter tp2;
  tp2.addColumn("red", 8, bprinter::format::red);
  tp2.addColumn("green", 8, bprinter::format::green);
  tp2.addColumn("yellow", 8, bprinter::format::yellow);
  tp2.addColumn("blue", 8, bprinter::format::blue);
  tp2.addColumn("cyan", 8, bprinter::format::cyan);
  tp2.addColumn("magenta", 8, bprinter::format::magenta);
  tp2.addColumn("white", 8, bprinter::format::white);
  tp2.addColumn("black", 8, bprinter::format::black);
  tp2.addColumn("nothing", 8, bprinter::format::none);

  tp2.printHeader();
  
  tp2 << "asdfsdf" << bprinter::format::red << 2 << 3 << 4 << 5 << bprinter::endl();
  tp2 << bprinter::format::blue << 6 << 7 << bprinter::endl();
  tp2 << bprinter::format::red << 1
      << bprinter::format::blue << 2
      <<bprinter::format::red << 3
      << bprinter::format::blue << 4
      <<bprinter::format::red << 5
      << bprinter::format::blue << 6
      <<bprinter::format::red << 7
      << bprinter::format::blue << 8
      <<bprinter::format::green << 9;
  tp2.printHeader();


  return 0;
}
