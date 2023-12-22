#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>

class FileReader {
public:
    FileReader(std::filesystem::path path) {
        in_.open(path);
        if (!in_.is_open()) {
            std::cerr << "Unable to open file!\n";
        }
    }
    char GetByte() {
        char c;
        in_.get(c);

        return c;
    }
    ~FileReader() {
        in_.close();
    }
private:
    std::ifstream in_;
};