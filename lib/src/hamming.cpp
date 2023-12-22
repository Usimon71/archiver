#include <hamming.h>
#include <iostream>
#include <string>
#include <algorithm>


namespace HamArc{

    template <size_t K>
    HammingCode<K>::HammingCode(FileReader& file)
        : file_(file)
        {}
    
    uint8_t BitGet(size_t num, size_t bit_number) {
        return ((num >> bit_number) & 1);
    }

    template <size_t K>
    void HammingCode<K>::XorContrBits(size_t i) {
        for (int j = 0; j != 8; ++j) {
            if (BitGet(i, j)) {
                bs_[(1 << j)].flip();
            }
        }
        bs_.set(i);
    }

    template <size_t K>
    void HammingCode<K>::CodeMsg() {
        size_t cur_contr_bit_pos = 1;
        char bit_count = 0;
        for (size_t i = 0; i != KBlockLen; ++i) {
            if ((bit_count % 8) == 0) {
                byte_ = file_.GetByte();
                bit_count = 0;
            }
            if (i != cur_contr_bit_pos) {
                char bit = BitGet(byte_, bit_count);
                if (bit) {
                    XorContrBits(i);
                }
                ++bit_count;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
        uint64_t sum = 0;
        for (size_t i = 0; i != KBlockLen; ++i) {
            sum += bs_[i];
        }
        if ((sum % 2) != 0) {
            bs_[0].flop();
        }
    }
    
    // void HammingCode::DecodeMsg() {
    //     std::bitset<4> contr_bits;
    //     for (size_t i = 0; i < block_len_; ++i) {
    //         if (BitGet(byte_, i)) {
    //             contr_bits[0].flip();
    //         }
    //     }
    //     for (size_t i = 1; i < block_len_; i += 2) {
    //         if (BitGet(byte_, i)) {
    //             contr_bits[1].flip();
    //         }
    //     }
    //     for (size_t i = 2; i < block_len_; i += 2) {
    //         if (BitGet(byte_, i)) {
    //             contr_bits[1].flip();
    //         }
    //     }
    // }
}
