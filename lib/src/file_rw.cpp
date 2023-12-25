#include "file_rw.h"

bool FileReader::ReadMeta(std::filesystem::path& path, uint64_t& size) {
    if(in_.peek() == EOF) {
        return false;
    }
    char* path_chr = new char[kFileNameSize];
    in_.read(path_chr, kFileNameSize);
    std::filesystem::path path_comp(path_chr);
    path = path_comp;
    
    size_t sizeof_size = sizeof(uint64_t);
    char* size_chr = new char[sizeof_size];
    in_.read(size_chr, sizeof_size);
    uint64_t res = 0;
    for (size_t i = 0; i != sizeof_size; ++i) {
        res += (static_cast<uint64_t>(size_chr[i]) << (i * 8));
    }
    size = res;

    delete [] path_chr; delete [] size_chr;

    return true;
}

void FileWriter::WriteMeta(const std::filesystem::path& path, uint64_t file_size) {
    const char* cpath = path.c_str();
    size_t path_len = std::strlen(cpath);
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
    out_.write(file_size_char, sizeof(uint64_t));
}