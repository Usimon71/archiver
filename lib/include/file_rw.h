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
        std::cerr << "EOF!\n";
        return 0;
    }
    ~FileReader() {
        in_.close();
    }
private:
    std::ifstream in_;
};

class FileWriter {
public:
    FileWriter(std::filesystem::path path) {
        out_.open(path, std::ios::binary | std::ios::app);
        if (!out_.is_open()) {
            std::cerr << "Unable to open file!\n";
        }
    }
    void PutByte (char byte) {
        out_.put(byte);
    }
    void WriteMeta(std::filesystem::path path, uint64_t file_size) {
        const char* cpath = path.c_str();
        size_t path_len = std::strlen(cpath);
        for (size_t i = 0; i != 30; ++i) {
            if (i < path_len) {
                out_.put(cpath[i]);
            } else {
                out_.put(0);
            }
        }
        const char* file_size_char = reinterpret_cast<char*>(&file_size);
        for (size_t i = 0; i != 8; ++i) {
            out_.put(file_size_char[i]);
        }
    }
    ~FileWriter() {
        out_.close();
    }
private:
    std::ofstream out_;
};