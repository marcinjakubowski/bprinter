#include "bprinter/TablePrinter.h"

#include <stdexcept>
#include <iomanip>
#include <stdexcept>

namespace bprinter {
TablePrinter::TablePrinter(std::ostream* output, const std::string& separator) {
  out_stream_ = output;
  i_ = 0;
  j_ = 0;
  separator_ = separator;
  table_width_ = 0;
}

TablePrinter::~TablePrinter() {}

int TablePrinter::get_num_columns() const {
  return column_headers_.size();
}

int TablePrinter::get_table_width() const {
  return table_width_;
}

void TablePrinter::set_separator(const std::string &separator){
  separator_ = separator;
}

/** \brief Add a column to our table
 ** 
 ** \param header_name Name to be print for the header
 ** \param column_width the width of the column (has to be >=5)
 ** */
void TablePrinter::AddColumn(const std::string & header_name, int column_width){
  if (column_width < 4){
    throw std::invalid_argument("Column size has to be >= 4");
  }

  column_headers_.push_back(header_name);
  column_widths_.push_back(column_width);
  table_width_ += column_width + separator_.size(); // for the separator  
}

void TablePrinter::PrintHorizontalLine() {
  *out_stream_ << "+"; // the left bar

  for (int i=0; i<table_width_-1; ++i)
    *out_stream_ << "-";

  *out_stream_ << "+"; // the right bar
  *out_stream_ << "\n";
}

void TablePrinter::PrintHeader(){
  PrintHorizontalLine();
  *out_stream_ << "|";

  for (int i=0; i<get_num_columns(); ++i){
    *out_stream_ << std::setw(column_widths_.at(i)) << column_headers_.at(i).substr(0, column_widths_.at(i));
    if (i != get_num_columns()-1){
      *out_stream_ << separator_;
    }
  }

  *out_stream_ << "|\n";
  PrintHorizontalLine();
}

void TablePrinter::PrintFooter(){
  PrintHorizontalLine();
}

TablePrinter& TablePrinter::operator<<(float input){
  OutputDecimalNumber<float>(input);
  return *this;
}

TablePrinter& TablePrinter::operator<<(double input){
  OutputDecimalNumber<double>(input);
  return *this;
}

template<typename T>
void TablePrinter::OutputDecimalNumber(T input) {
  // If we cannot handle this number, indicate so
  if (input < 10*(column_widths_.at(j_)-1) || input > 10*column_widths_.at(j_)) {
    std::stringstream string_out;
    string_out << std::setiosflags(std::ios::fixed)
               << std::setprecision(column_widths_.at(j_))
               << std::setw(column_widths_.at(j_))
               << input;

    std::string string_rep_of_number = string_out.str();

    string_rep_of_number[column_widths_.at(j_)-1] = '*';
    std::string string_to_print = string_rep_of_number.substr(0, column_widths_.at(j_));
    *out_stream_ << string_to_print;
  }
  else {
    // determine what precision we need
    int precision = column_widths_.at(j_) - 1; // leave room for the decimal point
    if (input < 0)
      --precision; // leave room for the minus sign

    // leave room for digits before the decimal?
    if (input < -1 || input > 1){
      int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
      precision -= num_digits_before_decimal;
    }
    else
      precision --; // e.g. 0.12345 or -0.1234

    if (precision < 0)
      precision = 0; // don't go negative with precision

    *out_stream_ << std::setiosflags(std::ios::fixed)
                 << std::setprecision(precision)
                 << std::setw(column_widths_.at(j_))
                 << input;
  }

  if (j_ == get_num_columns()-1) {
    *out_stream_ << "|\n";
    i_ = i_ + 1;
    j_ = 0;
  }
  else {
    *out_stream_ << separator_;
    j_ = j_ + 1;
  }
}

} //namespace bprinter
