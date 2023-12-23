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
    void HammingCode<K>::XorContrBits(size_t i) {
        for (int j = 0; j != sizeof(i) * 8; ++j) {
            if (BitGet(i, j)) {
                bs_[(1 << j)].flip();
            }
        }
        bs_.set(i);
    }

    template <size_t K>
    bool HammingCode<K>::CodeMsg() {
        bs_.reset();
        bool ans = true;
        size_t cur_contr_bit_pos = 1;
        char bit_count = 0;
        int counter = 0;
        for (size_t i = 1; i != kBlockLen; ++i) {
            if (i != cur_contr_bit_pos) {
                if ((bit_count % 8) == 0) {
                    byte_ = file_in_.GetByte();
                    if (byte_ == 0) {
                        ans = false ;
                        break;
                    }
                    bit_count = 0;
                }
                char bit = BitGet(byte_, bit_count);
                if (bit) {
                    XorContrBits(i);
                }
                ++counter;
                ++bit_count;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
        uint64_t sum = 0;
        for (size_t i = 0; i != kBlockLen; ++i) {
            sum += bs_[i];
        }
        if ((sum % 2) != 0) {
            bs_[0].flip();
        }
        byte_ = 0;
        for (size_t i = 0; i < kBlockLen; ++i) {
            if (i % 8 == 0) {
                file_out_.PutByte(byte_);
                byte_ = 0;
            }
            if (bs_[i]) {
                BitSet(byte_, (i % 8));
            }
            std::cout << static_cast<int>(bs_[i]);
        }
        return ans;
    }
    template <size_t K>
    bool HammingCode<K>::DeCodeMsg() {
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
        uint64_t sum = 0;
        for (size_t i = 0; i != kBlockLen; ++i) {
            sum += bs_[i];
        }
        if (sum % 2 == 0) {
            std::cout << "No errors detected\n";
            
        } else {
            std::cout << "Error detected!\n";
            std::bitset<(1 << K)> result;

        }
    }
    
    template class HammingCode<7>;
}
