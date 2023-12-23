#include <arch_reader.h>

template <size_t K>
bool ArchReader<K>::SearchFile(FileReader& file, std::filesystem::path& path_out) {
    std::filesystem::path path_comp;
    uint64_t file_size;
    while(file.ReadMeta(path_comp, file_size)){
        if (path_comp == path_out) {
            return true;
        }
        file.OffsetPtr(file_size);
    }
    std::cerr << "File not found!\n";
    return false;
}

template <size_t K>
void ArchReader<K>::Read() {
    FileReader file_in(in_path_);
    FileWriter file_out(out_path_);
    SearchFile(file_in, out_path_);
    
}

template class ArchReader<7>;