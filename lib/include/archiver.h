#pragma once

#include <vector>
#include <string>

#include "arch_rw.h"

struct Options {
    bool create{};
    bool list{};
    bool extract{};
    bool append{};
    bool del{};
    bool concatenate{};
    std::string archive_filename{};
    std::string base_dir{};
    std::vector<std::string> filenames{};
    int k{};
};

class Archiver {
public:
    Archiver(const Options& opt)
        : opt_(opt)
        {}
    void Run();
private:
    Options opt_;
};