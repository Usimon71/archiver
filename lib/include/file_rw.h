#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cstring>

class FileReader {
public:
    FileReader(std::filesystem::path path) {
        std::filesystem::path result_path(base_path_.string() + path.string());
        in_.open(result_path, std::ios::binary);
        if (!in_.is_open()) {
            std::cerr << "Unable to open file!\n";
            std::cout << result_path << "\n";
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
    bool EndOfFile() {
        if (in_.peek() == EOF) {
            return true;
        }
        return false;
    }
    bool ReadMeta(std::filesystem::path& path, uint64_t& size);
    uint64_t TellG() {
        return in_.tellg();
    }
    void OffsetPtr(uint64_t n) {
        in_.seekg(n, std::ios_base::cur);
    }
    void DeleteMe(std::filesystem::path to_del) {
        std::filesystem::path result_path(base_path_.string() + to_del.string());
        remove(result_path);
    }
    ~FileReader() {
        in_.close();
    }
private:
    std::ifstream in_;
    std::filesystem::path base_path_ = "/home/don_simon/Документы/ITMO_IS_1semester/proga/labwork6-Usimon71/data/";
    const uint8_t kFileNameSize = 30;
};

class FileWriter {
public:
    FileWriter(std::filesystem::path path, bool app = false) {
        std::filesystem::path result_path(base_path_.string() + path.string());
        if (app) {
            out_.open(result_path, std::ios::binary | std::ios::app);
        } else {
            out_.open(result_path, std::ios::binary);
        }
        if (!out_.is_open()) {
            
            std::cerr << "Unable to open file!\n";
        }
    }
    void PutByte (char byte) {
        out_.put(byte);
    }
    void WriteMeta(const std::filesystem::path& path, uint64_t file_size);
    ~FileWriter() {
        out_.close();
    }
private:
    std::ofstream out_;
    std::filesystem::path base_path_ = "/home/don_simon/Документы/ITMO_IS_1semester/proga/labwork6-Usimon71/data/";
    const uint8_t kFileNameSize = 30;
};