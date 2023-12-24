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
    HammingCode(FileReader& file_in, FileWriter& file_out)
        : file_in_(file_in)
        , file_out_(file_out)
        {}
    bool CodeMsg();
    void DeCodeMsg();
private:
    FileReader& file_in_;
    FileWriter& file_out_;
    std::bitset<(1 << K)> bs_;
    char byte_;
    const size_t kContrBits = K;
    const size_t kBlockLen = (1 << K);
    void XorContrBits(size_t i, std::bitset<(1 << K)>& bs_xor);
    void WriteToFile();
};

} // namespace HamArc