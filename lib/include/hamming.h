#pragma once

#include <bitset>
#include <fstream>
#include <cmath>
#include <cinttypes>

#include "file_rw.h"

namespace HamArc {
    
template <size_t K>   
class HammingCode {
public:
    HammingCode(FileReader& file_in, FileWriter& file_out)
        : file_in_(file_in)
        , file_out_(file_out)
        {}
    bool CodeMsg();
    void DeCodeMsg(bool last_block = false);
    bool single_mistake = false;
    bool double_mistake = false;
private:
    FileReader& file_in_;
    FileWriter& file_out_;
    std::bitset<(1 << K)> bs_;
    char byte_ = 0;
    const size_t kContrBits = K;
    const size_t kBlockLen = (1 << K);
    void XorContrBits(size_t i, std::bitset<(1 << K)>& bs_xor);
    void ProcessBytes(bool& ans);
    void CalcZeroBit();
    void WriteToFileCode();
    void WriteToFileDecode(bool last_block);
    void CopyBytesToBs();
    void ReCalcParity(uint64_t& sum_contr, uint64_t& sum_all);
};

} // namespace HamArc