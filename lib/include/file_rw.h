#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cstring>

class FileReader {
public:
    FileReader(std::filesystem::path path) {
        in_.open(path, std::ios::binary);
        if (!in_.is_open()) {
            std::cerr << "Unable to open file!\n";
        }
    }
    char GetByte() {
        char c;
        if(in_.peek() != EOF){
            in_.get(c);
            return c;
        }
        return 0;
    }
    bool ReadMeta(std::filesystem::path& path, uint64_t& size) {
        if(in_.peek() == EOF) {
            return false;
        }
        size_t sizeof_path = sizeof(std::filesystem::path);
        char* path_chr = new char[sizeof_path];
        in_.read(path_chr, sizeof_path);
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
    uint64_t TellG() {
        return in_.tellg();
    }
    void OffsetPtr(uint64_t n) {
        in_.seekg(n, std::ios_base::cur);
    }
    ~FileReader() {
        in_.close();
    }
private:
    std::ifstream in_;
};

class FileWriter {
public:
    FileWriter(std::filesystem::path path, bool app = false) {
        if (app) {
            out_.open(path, std::ios::binary | std::ios::app);
        } else {
            out_.open(path, std::ios::binary);
        }
        if (!out_.is_open()) {
            std::cerr << "Unable to open file!\n";
        }
    }
    void PutByte (char byte) {
        out_.put(byte);
    }
    void WriteMeta(const std::filesystem::path& path, uint64_t file_size) {
        const char* cpath = path.c_str();
        out_.write(cpath, sizeof(path));

        const char* file_size_char = reinterpret_cast<char*>(&file_size);
        out_.write(file_size_char, sizeof(file_size));
    }
    ~FileWriter() {
        out_.close();
    }
private:
    std::ofstream out_;
};