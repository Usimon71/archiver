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
    std::filesystem::path path_out = "out";
    out.open(path_out, std::ios::binary);
    char byte;
    while (in.get(byte)) {
        //std::cout << "byte " << std::bitset<8>(byte).to_string() << '\n';
        HamArc::HammingCode code(byte, 0, out);
        code.CodeMsg();

        HamArc::HammingCode code2(byte, 4, out);
        code2.CodeMsg();
    }
    
    in.close();
    out.close();
    return 0;
}