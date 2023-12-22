add_library(hamarc include/hamming.h src/hamming.cpp include/file_reader.h)   
target_include_directories(hamarc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)