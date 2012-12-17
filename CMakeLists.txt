cmake_minimum_required(VERSION 2.8)
project(bprinter)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(bprinter STATIC
  include/bprinter/table_printer.h
  include/bprinter/impl/table_printer.tpp.h
  include/bprinter/PrintFormat.h
  src/PrintFormat.cpp
  src/table_printer.cpp
)

add_executable(bprinterTest src/test_main.cxx)
target_link_libraries(bprinterTest bprinter)
