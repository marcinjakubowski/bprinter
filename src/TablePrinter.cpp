#include "bprinter/TablePrinter.h"

#include <stdexcept>
#include <iomanip>
#include <stdexcept>

namespace bprinter {
TablePrinter::TablePrinter(std::ostream* output, const std::string& separator, const std::string& lineEnding) :
  _outStream(output),
  _row(0),
  _col(0),
  _separator(separator),
  _lineEnding(lineEnding) {}

TablePrinter::~TablePrinter() {}

unsigned int TablePrinter::numberOfColumns() const {
  return _columnNames.size();
}

unsigned int TablePrinter::tableWidth() const {
  unsigned int tableWidth = separator().size();
  for (unsigned int i = 0; i < numberOfColumns(); ++i)
    tableWidth += columnWidth(i) + separator().size();
  return tableWidth;
}

std::string TablePrinter::separator() const {
  return _separator;
}
std::string TablePrinter::columnName(unsigned int i) const {
  return _columnNames[i];
}
unsigned int TablePrinter::columnWidth(unsigned int i) const {
  return _columnWidths[i];
}

/** \brief Add a column to our table
 ** 
 ** \param headerName Name to be print for the header
 ** \param width the width of the column (has to be >=5)
 ** */
void TablePrinter::addColumn(const std::string& name, unsigned int width){
  if (width < 4)
    throw std::invalid_argument("Column width has to be >= 4");
  if (name.size() == 0)
    throw std::invalid_argument("Column name cannot be \"\"");

  _columnNames.push_back(name);
  _columnWidths.push_back(width);
}

void TablePrinter::printHorizontalLine() {
  *_outStream << "+"; // the left bar

  for (int i = 0; i < tableWidth() - 2; ++i)
    *_outStream << "-";

  *_outStream << "+"; // the right bar
  printEndl();
}

void TablePrinter::printEndl() {
  if (_lineEnding.size() != 0)
    *_outStream << _lineEnding;
  else
    *_outStream << std::endl;
}

void TablePrinter::printHeader(){
  printHorizontalLine();
  *_outStream << separator();

  for (unsigned int i = 0; i < numberOfColumns(); ++i) {
    *_outStream << std::setw(columnWidth(i)) << columnName(i).substr(0, columnWidth(i));
    if (i < numberOfColumns()){
      *_outStream << separator();
    }
  }

  //*_outStream << separator();
  printEndl();
  printHorizontalLine();
}

void TablePrinter::printFooter(){
  printHorizontalLine();
}

TablePrinter& TablePrinter::operator<<(endl input) {
  while (_col > 0){
    *this << "";
  }
  return *this;
}

TablePrinter& TablePrinter::operator<<(float input) {
  printDecimalNumber<float>(input);
  return *this;
}
TablePrinter& TablePrinter::operator<<(double input) {
  printDecimalNumber<double>(input);
  return *this;
}

template<typename T>
void TablePrinter::printDecimalNumber(T input) {
  // If we cannot handle this number, indicate so
  if (input < 10 * (columnWidth(_col) - 1) || input > 10 * columnWidth(_col)) {
    std::stringstream string_out;
    string_out << std::setiosflags(std::ios::fixed)
               << std::setprecision(columnWidth(_col))
               << std::setw(columnWidth(_col))
               << input;

    std::string string_rep_of_number = string_out.str();

    string_rep_of_number[columnWidth(_col) - 1] = '*';
    std::string string_to_print = string_rep_of_number.substr(0, columnWidth(_col));
    *_outStream << string_to_print;
  }
  else {
    // determine what precision we need
    int precision = columnWidth(_col) - 1; // leave room for the decimal point
    if (input < 0)
      --precision; // leave room for the minus sign

    // leave room for digits before the decimal?
    if (input <= -1 || input >= 1){
      int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
      precision -= num_digits_before_decimal;
    }
    else
      precision --; // e.g. 0.12345 or -0.1234

    if (precision < 0)
      precision = 0; // don't go negative with precision

    *_outStream << std::setiosflags(std::ios::fixed)
                << std::setprecision(precision)
                << std::setw(columnWidth(_col))
                << input;
  }

  if (_col >= numberOfColumns() - 1) {
    *_outStream << separator();
    printEndl();
    _row++;
    _col = 0;
  }
  else {
    *_outStream << separator();
    _col++;
  }
}

} //namespace bprinter

