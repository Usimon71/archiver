add_library(hamarc include/hamming.h src/hamming.cpp
                    include/arch_writer.h src/arch_writer.cpp 
                    include/file_rw.h
                    include/arch_reader.h src/arch_reader.cpp)   
target_include_directories(hamarc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)