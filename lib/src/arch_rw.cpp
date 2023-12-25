#include "arch_rw.h"

template <size_t K>
uint64_t ArchWriter<K>::GetFileSize(std::filesystem::path path) {
    uint64_t msg_size = ((1 << K) - K - 1) / 8;
    std::filesystem::path result_path(base_path_.string() + path.string());
    uint64_t num_of_blocks = (static_cast<uint64_t>(std::ifstream(result_path, std::ios::ate).tellg()) + msg_size - 1) / msg_size;
    uint64_t ans = num_of_blocks * (msg_size + ((K + 1) / 8));
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
    while (ham_code.CodeMsg());
}

template class ArchWriter<7>;
template class ArchWriter<15>;

template <size_t K>
uint64_t ArchReader<K>::SearchFile(FileReader& file, std::filesystem::path& path_out) {
    std::filesystem::path path_comp;
    uint64_t file_size;
    while(file.ReadMeta(path_comp, file_size)){
        std::cout << "file name: " << path_comp << ", file_size: " << file_size << '\n';
        if (path_comp == path_out) {
            return file_size;
        }
        
        file.OffsetPtr(file_size);
    }
    std::cerr << "File not found!\n";
    return 0;
}

template <size_t K>
void ArchReader<K>::Read() {
    FileReader file_in(in_path_);
    FileWriter file_out(out_path_, false);
    uint64_t code_size = SearchFile(file_in, out_path_);
    HamArc::HammingCode<K> ham_code(file_in, file_out);
    size_t block_size = (1 << K) / 8;
    uint64_t num_of_blocks = code_size / block_size;
    std::cout << "code size: " << code_size << '\n';
    std::cout << "num of blocks: " << num_of_blocks <<'\n';
    for (size_t i = 0; i != num_of_blocks; ++i) {
        ham_code.DeCodeMsg();
    }
}

template <size_t K>
void ArchReader<K>::ListFiles() {
    FileReader file_in(in_path_);
    std::filesystem::path path;
    uint64_t file_size;
    uint64_t count = 1;
    std::cout << "Files in archive " << in_path_ << ":\n";
    while (file_in.ReadMeta(path, file_size)) {
        std::cout << count << ". " << path << '\n';
        file_in.OffsetPtr(file_size);
        ++count;
    }
}

template class ArchReader<7>;
template class ArchReader<15>;