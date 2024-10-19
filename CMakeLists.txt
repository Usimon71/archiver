cmake_minimum_required(VERSION 3.12)

project(
    archiver
    VERSION 1.0
    DESCRIPTION "Hamming code archiver"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(ArgParser)

enable_testing()
add_subdirectory(tests)