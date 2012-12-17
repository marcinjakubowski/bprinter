#ifndef BPRINTER_TABLE_PRINTER_H_
#define BPRINTER_TABLE_PRINTER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

namespace bprinter {
class endl{};
/** \class TablePrinter

  Print a pretty table into your output of choice.

  Usage:
    TablePrinter tp(&std::cout);
    tp.AddColumn("Name", 25);
    tp.AddColumn("Age", 3);
    tp.AddColumn("Position", 30);

    tp.PrintHeader();
    tp << "Dat Chu" << 25 << "Research Assistant";
    tp << "John Doe" << 26 << "Professional Anonymity";
    tp << "Jane Doe" << tp.SkipToNextLine();
    tp << "Tom Doe" << 7 << "Student";
    tp.PrintFooter();

  \todo Add support for padding in each table cell
  */
class TablePrinter{
public:
  TablePrinter(std::ostream* output = &std::cout, const std::string& separator = "|", const std::string& lineEnding = "");
  ~TablePrinter();

  unsigned int numberOfColumns() const;
  unsigned int tableWidth() const;
  std::string separator() const;
  std::string columnName(const unsigned int i) const;
  unsigned int columnWidth(const unsigned int i) const;

  void addColumn(const std::string& name, const unsigned int width);

  void printHeader();
  void printFooter();


  TablePrinter& operator<<(endl input);
  TablePrinter& operator<<(float input);
  TablePrinter& operator<<(double input);

  //can't this be somewhere else? :/
  template<typename T> TablePrinter& operator<<(T input) {
    if (_col == 0)
      *_outStream << separator();

    // Leave 3 extra space: One for negative sign, one for zero, one for decimal
    *_outStream << std::setw(columnWidth(_col))
                 << input;

    if (_col == numberOfColumns() - 1) {
      *_outStream << separator();
      printEndl();
      _row++;
      _col = 0;
    }
    else {
      *_outStream << separator();
      _col++;
    }
    return *this;
  }

private:
  void printHorizontalLine();
  void printEndl();

  template<typename T> void printDecimalNumber(T input);

  std::ostream* _outStream;
  std::vector<std::string> _columnNames;
  std::vector<unsigned int> _columnWidths;
  std::string _separator;
  std::string _lineEnding;

  unsigned int _row;
  unsigned int _col;
};

}// namespace bprinter

#endif //BPRINTER_TABLE_PRINTER_H_
