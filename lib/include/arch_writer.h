#pragma once

#include "file_rw.h"
//#include "hamming.h"

template <size_t K>
class ArchWriter{
public:
    ArchWriter(std::filesystem::path in_path, std::filesystem::path out_path)
        : in_path_(in_path)
        , out_path_(out_path)
        {}
    void Write();
    uint64_t GetFileSize(std::filesystem::path path);
private:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
};