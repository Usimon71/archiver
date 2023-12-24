#include <arch_writer.h>
#include <hamming.h>

template <size_t K>
uint64_t ArchWriter<K>::GetFileSize(std::filesystem::path path) {
    uint64_t msg_size = ((1 << K) - K - 1) / 8;
    uint64_t num_of_blocks = (static_cast<uint64_t>(std::ifstream(path, std::ios::ate).tellg()) + msg_size - 1) / msg_size;
    uint64_t ans = num_of_blocks * (msg_size + ((K + 1) / 8));
    // std::cout << "file size " << ans << '\n';
    return ans;
}

template <size_t K>
void ArchWriter<K>::Write() {
    FileReader file_in(in_path_);
    FileWriter file_out(out_path_, true);
    
    uint64_t file_sz = GetFileSize(in_path_);
    std::cout << "file size: " << file_sz << '\n';
    file_out.WriteMeta(in_path_, file_sz);
    
    HamArc::HammingCode<K> ham_code(file_in, file_out);
    while (ham_code.CodeMsg()) {
        std::cout << "code!\n";
    }
}

template class ArchWriter<7>;
