#pragma once

#include "file_rw.h"
#include "hamming.h"


template <size_t K>
class ArchRW {
    ArchRW(std::filesystem::path in_path, std::filesystem::path out_path)
        : in_path_(in_path)
        , out_path_(out_path)
        {}
protected:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
};

template <size_t K>
class ArchWriter : public ArchRW {
public:
    void Write();
    uint64_t GetFileSize(std::filesystem::path path);
private:
    std::filesystem::path base_path_ = "/home/don_simon/Документы/lab6_prog/labwork6-Usimon71/labwork6-Usimon71/data/";
};

template <size_t K>
class ArchReader : public ArchRW {
public:
    void Read();
    uint64_t SearchFile(FileReader& file, std::filesystem::path& path_out);
};