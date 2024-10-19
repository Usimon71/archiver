add_library(argparser   src/ArgParser.cpp   include/ArgParser.h
                        src/IntArg.cpp      include/IntArg.h
                        src/StringArg.cpp   include/StringArg.h
                        src/BoolArg.cpp     include/BoolArg.h
                        include/Help.h)   
target_include_directories(argparser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)