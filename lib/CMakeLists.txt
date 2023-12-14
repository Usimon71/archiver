add_library(hamarc include/hamming.h src/hamming.cpp)   
target_include_directories(hamarc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})