#pragma once
#include "file_rw.h"
#include "hamming.h"

template <size_t K>
class ArchReader {
public:
    ArchReader(std::filesystem::path in_path, std::filesystem::path out_path)
        : in_path_(in_path)
        , out_path_(out_path)
        {}
    void Read();
    uint64_t SearchFile(FileReader& file, std::filesystem::path& path_out);
private:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
};