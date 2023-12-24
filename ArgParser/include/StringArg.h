#pragma once

#include <vector>
#include <string>
#include <cinttypes>

class StringArg {
public:
    StringArg(const std::string& long_name)
        :long_name_(long_name)
        {}
    StringArg(char short_name, const std::string& long_name)
        : short_name_(short_name)
        , long_name_(long_name)
        {
            has_short_name_ = true;
        }
    StringArg(char short_name, const std::string& long_name, const std::string& description)
        : short_name_(short_name)
        , long_name_(long_name)
        , description_(description)
        {
            has_description_ = true;
            has_short_name_ = true;
        }
    StringArg() = default;

    
    bool GetHasLongName() const {
        return (long_name_ != "");
    }
    bool GetHasShortName() const {
        return has_short_name_;
    }
    bool GetHasDescription() const {
        return has_description_;
    }
    bool GetIsMultValue() const {
        return is_mult_value_;
    }
    bool GetIsPositional() const {
        return is_positional_;
    }
    bool GetHasStoreValue() const {
        return has_store_value_;
    }
    bool GetHasValue() const {
        return has_value_;
    }
    

    const std::string& GetLongName() const {
        return long_name_;
    }
    char GetShortName() const {
        return short_name_;
    }
    const std::string& GetDescription() const {
        return description_;
    }
    const std::string& GetValue() const {
        return single_value_;
    }
    const std::vector<std::string>& GetMultValues() const {
        return mult_values_;
    }
    const std::string GetMultValue(int ind) const;
    uint16_t GetMinMultValues() const {
        return min_mult_value_;
    }
    std::string* GetStoreValue() const {
        return store_value_;
    }
    std::vector<std::string>* GetStoreValues() const {
        return store_values_;
    }
    
    void PushMultVal(std::string arg);  
    void SetSingleValue(const std::string& val) {
        single_value_ = val;
        has_value_= true;
    }

    StringArg& MultiValue();
    StringArg& MultiValue(uint16_t value);
    
    StringArg& StoreValues(std::vector<std::string>& values);
    StringArg& StoreValue(std::string& value);
    
    StringArg& Positional();
    
    StringArg& Default(const std::string& default_val);
    StringArg& Default(const std::vector<std::string>& default_val);
    
private:
    char short_name_;
    std::string long_name_;
    std::string description_;
    uint16_t min_mult_value_ = 0;
    std::vector<std::string> mult_values_;
    std::vector<std::string>* store_values_ = nullptr;
    std::string* store_value_ = nullptr;
    std::string single_value_;

    bool has_value_ = false;
    bool has_short_name_ = false;
    bool has_description_ = false;
    bool is_mult_value_ = false;
    bool has_store_value_ = false;
    bool is_positional_ = false;
};