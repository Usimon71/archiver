#pragma once

#include <bitset>
#include <fstream>
#include <cmath>
#include <cinttypes>

namespace HamArc {
    
// template <size_t K, size_t N>   
class HammingCode {
public:
    HammingCode(std::ifstream& in, std::ofstream& out);
    void CodeMsg();
    std::bitset<8> code_;
private:
    
    size_t block_len_ = 8;
    std::ifstream& in_;
    std::ofstream& out_;
    char byte_;
    char bit_count_;
    //size_t GetBlockLen();

    
    void XorContrBits(size_t i);
};

} // namespace HamArc