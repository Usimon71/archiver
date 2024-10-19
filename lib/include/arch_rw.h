#pragma once

#include "file_rw.h"
#include "hamming.h"

template <size_t K>
class ArchWriter{
public:
    ArchWriter(std::filesystem::path in_path, std::filesystem::path out_path, std::filesystem::path base_dir)
        : in_path_(in_path)
        , out_path_(out_path)
        , base_dir_(base_dir)
        {}
    void Write(bool app, bool single_mistake = false, bool double_mistake = false);
    uint64_t GetFileSize(std::filesystem::path path);
private:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
    std::filesystem::path base_dir_ = "data/";
};

template <size_t K>
class ArchReader {
public:
    ArchReader(std::filesystem::path in_path, std::filesystem::path out_path, std::filesystem::path base_dir)
        : in_path_(in_path)
        , out_path_(out_path)
        , base_dir_(base_dir)
        {}
    ArchReader(std::filesystem::path in_path, std::filesystem::path base_dir)
        : in_path_(in_path)
        , base_dir_(base_dir)
        {}
    void Read();
    void ReadAll();
    void ListFiles();
    void CopyFile();
    void Delete(std::filesystem::path to_del);
    void RemoveExcept(std::filesystem::path to_del);
    void WriteExcept();
    uint64_t SearchFile(FileReader& file, std::filesystem::path& path_out);
private:
    std::filesystem::path in_path_;
    std::filesystem::path out_path_;
    std::filesystem::path base_dir_ = "data/";
};