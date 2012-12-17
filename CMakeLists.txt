cmake_minimum_required(VERSION 2.8)
project(bprinter)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(bprinter STATIC
  include/bprinter/TablePrinter.h
  src/TablePrinter.cpp
  include/bprinter/PrintFormat.h
  src/PrintFormat.cpp
)

add_executable(bprinterTest src/test_main.cpp)
target_link_libraries(bprinterTest bprinter)
