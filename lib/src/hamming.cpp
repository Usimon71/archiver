#include <hamming.h>
#include <iostream>
#include <string>
#include <algorithm>


namespace HamArc{
    uint8_t BitGet(size_t num, size_t bit_number) {
        return ((num >> bit_number) & 1);
    }
    void BitSet(char& num, char bit_number) {
        num |= (1 << bit_number);
    }

    template <size_t K>
    void HammingCode<K>::XorContrBits(size_t i, std::bitset<(1 << K)>& bs_xor) {
        for (int j = 0; j != sizeof(i) * 8; ++j) {
            if (BitGet(i, j)) {
                bs_xor[(1 << j)].flip();
            }
        }
        bs_xor.set(i);
    }

    template <size_t K>
    void HammingCode<K>::ProcessBytes(bool& ans) {
        size_t cur_contr_bit_pos = 1;
        char bit_count = 0;
        for (size_t i = 1; i != kBlockLen; ++i) {
            if (i != cur_contr_bit_pos) {
                if ((bit_count % 8) == 0) {
                    if (file_in_.EndOfFile()) {
                        ans = false;
                        break;
                    }
                    byte_ = file_in_.GetByte();
                    bit_count = 0;
                }
                char bit = BitGet(byte_, bit_count);
                if (bit) {
                    XorContrBits(i, bs_);
                }
                ++bit_count;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
    }

    template <size_t K>
    void HammingCode<K>::CalcZeroBit() {
        uint64_t sum = 0;
        for (size_t i = 1; i != kBlockLen; ++i) {
            sum += bs_[i];
        }
        if ((sum % 2) != 0) {
            bs_[0].flip();
        }
    }

    template <size_t K>
    void HammingCode<K>::WriteToFileCode() {
        byte_ = 0;
        uint8_t count_mistakes = 0;
        for (size_t i = 0; i < kBlockLen; ++i) {
            if (i % 8 == 0 && i != 0) {
                file_out_.PutByte(byte_);
                byte_ = 0;
            }
            if (bs_[i]) {
                if (single_mistake && count_mistakes == 0) {
                    std::cout << "Let single mistake\n";
                    ++count_mistakes;
                } else if (double_mistake && count_mistakes < 2) {
                    std::cout << "Let single mistake(double in general)\n";
                    ++count_mistakes;
                }
                else {
                    BitSet(byte_, (i % 8));
                }
                
            }
        }
        file_out_.PutByte(byte_);
        byte_ = 0;
    }

    template <size_t K>
    bool HammingCode<K>::CodeMsg() {
        bs_.reset();
        bool ans = true;
        ProcessBytes(ans);
        CalcZeroBit();
        WriteToFileCode();
        
        return ans;
    }

    template <size_t K>
    void HammingCode<K>::WriteToFileDecode(bool last_block) {
        size_t cur_contr_bit_pos = 1;
        char bit_count = 0;
        byte_ = 0;
        for (size_t i = 1; i != kBlockLen; ++i) {
            if (i != cur_contr_bit_pos) {
                if (bit_count % 8 == 0 && i > 4) {
                    if(!(last_block && byte_ == 0)){
                        file_out_.PutByte(byte_);
                    }
                    
                    bit_count = 0;
                    byte_ = 0;
                }
                if (bs_[i]) {
                    BitSet(byte_, bit_count);
                }
                ++bit_count;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
        if(!(last_block && byte_ == 0)){
            file_out_.PutByte(byte_);
        }
        byte_ = 0;
    }

    template <size_t K>
    void HammingCode<K>::CopyBytesToBs() {
        bs_.reset();
        char bit_count = 0;
        for (size_t i = 0; i != kBlockLen; ++i) {
            if (i % 8 == 0) {
                byte_ = file_in_.GetByte();
                bit_count = 0;
            }
            if (BitGet(byte_, bit_count)) {
                bs_.set(i);
            }
            ++bit_count;
        }
    }

    template <size_t K>
    void HammingCode<K>::ReCalcParity(uint64_t& sum_contr, uint64_t& sum_all) {
        std::bitset<(1 << K)> result;
        for (size_t i = 1; i != kBlockLen; ++i) {
            if (bs_[i]) {
                XorContrBits(i, result);
            }
        }

        for (size_t i = 1; i < kBlockLen; i *= 2) {
            if(result[i]) {
                sum_contr += i;
            }
        }

        for (size_t i = 0; i != kBlockLen; ++i) {
            sum_all += bs_[i];
        }
    }

    template <size_t K>
    void HammingCode<K>::DeCodeMsg(bool last_block) {
        CopyBytesToBs();
        uint64_t sum_contr = 0;
        uint64_t sum_all = 0;
        ReCalcParity(sum_contr, sum_all);
        if (sum_all % 2 == 0) {
            if (sum_contr == 0) {
                WriteToFileDecode(last_block);
            } else {
                std::cerr << "More than one error in block!\nUnable to extract!\n";
            }
        } else {
            std::cout << "Error detected!\n";
            std::cout << "Error in " << sum_contr << " bit\n";
            bs_[sum_contr].flip();
            std::cout << "Error fixed!\n";
            WriteToFileDecode(last_block);
        }
    }
    
    template class HammingCode<7>;
    template class HammingCode<15>;
}
