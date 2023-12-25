#include "file_rw.h"

bool FileReader::ReadMeta(std::filesystem::path& path, uint64_t& size) {
    if(in_.peek() == EOF) {
        return false;
    }
    char* path_chr = new char[kFileNameSize];
    in_.read(path_chr, kFileNameSize);
    std::filesystem::path path_comp(path_chr);
    path = path_comp;
    
    uint64_t res;
    in_.read(reinterpret_cast<char*>(&res), sizeof(res));
    size = res;

    delete [] path_chr;

    return true;
}

void FileWriter::WriteMeta(const std::filesystem::path& path, uint64_t file_size) {
    const char* cpath = path.c_str();
    size_t path_len = std::strlen(cpath);
    std::cout << "path_len: " << path_len << '\n';
    if (path_len > kFileNameSize) {
        std::cerr << "too long filename!\n";
    }
    for (size_t i = 0; i != path_len; ++i) {
        out_.put(cpath[i]);
    }
    
    if (path_len < kFileNameSize) {
        for (size_t i = 0; i != kFileNameSize - path_len; ++i) {
            out_.put(0);
        }
    }

    const char* file_size_char = reinterpret_cast<char*>(&file_size);
    for(size_t i = 0; i != 8; ++i) {
        out_.put(file_size_char[i]);
    }
}