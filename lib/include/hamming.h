#pragma once

#include <bitset>
#include <fstream>
#include <cmath>
#include <cinttypes>

#include "arch_writer.h"

namespace HamArc {
    
template <size_t K>   
class HammingCode {
public:
    HammingCode(FileReader& file);
    void CodeMsg();
    void DecodeMsg();
private:
    FileReader& file_;
    std::bitset<(1 << K)> bs_;
    char byte_;
    const size_t kContrBits = K;
    const size_t KBlockLen = (1 << K);
    void XorContrBits(size_t i);
};

} // namespace HamArc