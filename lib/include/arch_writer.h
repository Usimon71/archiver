#pragma once

#include "file_reader.h"

class ArchWriter{
public:
    ArchWriter(std::filesystem::path in_path, std::filesystem::path out_path, size_t k)
        : in_path_(in_path)
        , out_path_(out_path)
        , k_(k)
        {}
    void Write();
private:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
    size_t k_;
};