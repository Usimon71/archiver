#pragma once

#include <bitset>
#include <fstream>
#include <cmath>
#include <cinttypes>

namespace HamArc {
    
template <size_t K, size_t N>   
class HammingCode {
public:
    HammingCode(std::ifstream& in, std::ofstream& out);
private:
    std::bitset<N> code_;
    size_t block_len_;
    std::ifstream& in_;
    std::ofstream& out_;

    //size_t GetBlockLen();

    void CodeMsg();
    void XorContrBits(size_t i);
};

} // namespace HamArc