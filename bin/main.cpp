#include <iostream>
#include <ios>
#include <include/hamming.h>
#include <fstream>
#include <filesystem>
int main() {
    std::ifstream in;
    std::ofstream out;
    std::filesystem::path path_in = "in";
    in.open(path_in, std::ios::binary);
    if (in.is_open()) {
        std::cout << "open!\n";
    }
    std::filesystem::path path_out = "out";
    out.open(path_out, std::ios::binary);
    HamArc::HammingCode code(in, out);
    code.CodeMsg();
    in.close();
    out.close();
    return 0;
}