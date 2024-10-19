#pragma once

#include <string>
#include <cinttypes>

class BoolArg {
public:
    BoolArg(const std::string& long_name)
        : long_flag_(long_name)
        {}
    BoolArg(char short_name, const std::string& long_name)
        : short_flag_(short_name)
        , long_flag_(long_name)
        {
            has_short_name_ = true;
        }
    BoolArg(char short_name, const std::string& long_name, const std::string& description)
        : short_flag_(short_name)
        , long_flag_(long_name)
        , description_(description)
        {
            has_short_name_ = true;
            has_description_ = true;
        }
    BoolArg(const std::string& long_name, const std::string& description)
        : long_flag_(long_name)
        , description_(description)
        {
            has_description_ = true;
        }
    BoolArg() = default;

    bool GetHasDescription() const {
        return has_description_;
    }
    const std::string& GetDescription() const {
        return description_;
    }
    char GetShortFlag() const {
        return short_flag_;
    }
    std::string GetLongFlag() const {
        return long_flag_;
    }
    bool GetHasShortFlag() const {
        return has_short_name_;
    }
    bool GetHasLongFlag() const {
        return (long_flag_ != "");
    }
    bool GetHasValue() const {
        return has_value_;
    }
    
    void RaiseFlag() {
        value_ = true;
        has_value_ = true;
    }
    bool GetValue() const {
        return value_;
    }
    bool GetHasStoreValue() const {
        return has_store_value_;
    }

    bool* GetStoreValue() const {
        return store_value_;
    }

    BoolArg& Default(bool default_value);
    BoolArg& StoreValue(bool& value);
private:
    std::string long_flag_;
    char short_flag_;
    std::string description_;
    
    bool has_short_name_ = false;
    bool has_description_ = false;
    bool value_ = false;
    bool has_value_ = false;
    bool* store_value_ = nullptr;
    bool has_store_value_ = false;
};