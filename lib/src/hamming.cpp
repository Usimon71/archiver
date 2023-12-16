#include <hamming.h>
#include <iostream>
#include <string>
#include <algorithm>
namespace HamArc{

    //template <size_t K, size_t N>
    HammingCode::HammingCode(std::ifstream& in, std::ofstream& out)
        : in_(in)
        , out_(out)
        {}
    uint8_t BitGet(char num, size_t bit_number) {
        size_t bit_n = 7 - bit_number;
        return ((num >> bit_n) & 1)
;
    }

    //template <size_t K, size_t N>
    void HammingCode::XorContrBits(size_t i) {
        char pos = i;
        //code_[0].flip();
        std::cout << "i " << i << '\n';

        for (int j = 0; j != 8; ++j) {
            if (BitGet(pos, j)) {
                code_[std::pow(2, (7 - j))].flip();
                std::string str = code_.to_string();
                std::cout << str << '\n';
                std::cout << "j " <<  7 - j << '\n';
            }
            
        }
        // while () {
        //     contr_bit_change_pos /= 2;
        // }
        code_.set(i);
        std::string str = code_.to_string();
        std::cout << str << '\n';
        
    }

    //template <size_t K, size_t N>
    void HammingCode::CodeMsg() {
        size_t cur_contr_bit_pos = 1;
        //size_t num_of_bytes = 4;
        bit_count_ = 0;
        for (size_t i = 1; i != block_len_; ++i) {
            if (i != cur_contr_bit_pos) {
                if (bit_count_ % 8 == 0) {
                    bit_count_ = 0;
                    in_.get(byte_);
                }
                // std::cout << std::bitset<8>(byte_).to_string() << '\n';
                char bit = BitGet(byte_, bit_count_);

                // std::cout << static_cast<int>(bit_count_) << " " << static_cast<int>(bit) << '\n';
                if (bit) {
                    std::cout << "bit! " << static_cast<int>(bit) << "\n";
                    XorContrBits(i);
                }
                ++bit_count_;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
        for (int j = 1; j != 8; ++j) {
            if (code_[j]) {
                code_[0].flip();
            }
        }
        uint64_t code_long = code_.to_ulong();
        char msg = static_cast<char>(code_long);
        std::cout << code_.to_string() << '\n';
        out_.put(msg);
    }
}
