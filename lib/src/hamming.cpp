#include <hamming.h>

namespace HamArc{

    template <size_t K, size_t N>
    HammingCode<K, N>::HammingCode(std::ifstream& in, std::ofstream& out)
        : in_(in)
        , out_(out)
    {}

    // template <size_t K, size_t N>
    // size_t HammingCode<K, N>::GetBlockLen() {
    //     size_t ans = std::pow(2, K) - K - 1;
    //     while (ans % 8 != 0) {
    //         --ans;
    //     }

    //     return ans;
    // }
    uint8_t BitGet(uint8_t num, size_t bit_number) {
        return ((num >> bit_number) & 1);
    }

    template <size_t K, size_t N>
    void HammingCode<K, N>::XorContrBits(size_t i) {
        size_t pos = i;
        uint64_t pow = floor(std::log2(pos));
        size_t contr_bit_change_pos = std::pow(2, pow);
        while (contr_bit_change_pos > 0) {
            code_[contr_bit_change_pos].flip();
            contr_bit_change_pos /= 2;
        }
    }

    template <size_t K, size_t N>
    void HammingCode<K, N>::CodeMsg() {
        size_t cur_contr_bit_pos = 1;
        size_t num_of_bytes = N - K;
        char byte;
        uint8_t count_bits = 0;
        for (size_t i = 1; i != block_len_; ++i) {
            if (count_bits % 8 == 0) {
                count_bits = 0;
                in_.get(byte);
            }
            if (i != cur_contr_bit_pos) {
                uint8_t bit = BitGet(byte, count_bits);
                if (bit) {
                    XorContrBits(i);
                }
                ++count_bits;
            } else {
                cur_contr_bit_pos *= 2;
            }
        }
    }
}
