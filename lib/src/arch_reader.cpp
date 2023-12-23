#include <arch_reader.h>

std::filesystem::path GetPath(FileReader& file) {
    size_t sizeof_path = 30;
    std::cout << "size_path " << sizeof_path << '\n';
    char* path = new char[sizeof_path];
    for (size_t i = 0; i != sizeof_path; ++i) {
        path[i] = file.GetByte();;
    }
    std::filesystem::path path_comp(path);
    delete [] path;
    return path_comp;
}
uint64_t GetFileSize(FileReader& file) {
    std::cout << "pos " << file.TellG() << '\n';
    char* size = new char[8];
    for (size_t i = 0; i != 8; ++i) {
        size[i] = file.GetByte();
    }
    uint64_t res = 0;
    for (size_t i = 0; i != 8; ++i) {
        std::cout << static_cast<int>(size[i]) << ' ';
        res += (static_cast<uint64_t>(size[i]) << (i * 8));
    }
    delete [] size;
    return res;
}

template <size_t K>
bool ArchReader<K>::SearchFile(FileReader& file, std::filesystem::path& path_out) {
    std::filesystem::path path_comp = GetPath(file);
    uint64_t file_size = GetFileSize(file);
    if (path_comp == path_out) {
        std::cout << path_comp << " " << file_size << '\n';
        return true;
    }

    return false;
}

template <size_t K>
void ArchReader<K>::Read() {
    FileReader file_in(in_path_);
    FileWriter file_out(out_path_);

    SearchFile(file_in, out_path_);
}

template class ArchReader<7>;