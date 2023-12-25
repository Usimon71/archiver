add_library(hamarc include/hamming.h src/hamming.cpp
                    include/file_rw.h src/file_rw.cpp
                    include/arch_rw.h src/arch_rw.cpp
                    include/archiver.h src/archiver.cpp)   
target_include_directories(hamarc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)