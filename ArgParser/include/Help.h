#pragma once

#include <string>

class HelpClass {
public:
    HelpClass(char short_name, const std::string& long_name, const std::string& description)
        : short_name_(short_name)
        , long_name_(long_name)
        , description_(description)
        {}
    HelpClass() = default;

    std::string GetDescription() const {
        return description_;
    }
private:
    char short_name_;
    std::string long_name_;
    std::string description_;
};