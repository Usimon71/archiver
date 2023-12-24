#include <arch_reader.h>

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

template class ArchReader<7>;