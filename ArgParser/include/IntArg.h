#pragma once

#include <vector>
#include <string>
#include <cinttypes>

class IntArg {
public:
    IntArg(const std::string& long_name)
        :long_name_(long_name)
        {}
    IntArg(char short_name, const std::string& long_name)
        : short_name_(short_name)
        , long_name_(long_name)
        {
            has_short_name_ = true;
        }
    IntArg(char short_name, const std::string& long_name, const std::string& description)
        : short_name_(short_name)
        , long_name_(long_name)
        , description_(description)
        {
            has_short_name_ = true;
            has_description_ = true;
        }
    IntArg(const std::string& long_name, const std::string& description)
        : long_name_(long_name)
        , description_(description)
        {
            has_description_ = true;
        }
    IntArg() = default;

    bool GetIsMultValue() const {
        return is_mult_value_;
    }
    bool GetHasShortName() const {
        return has_short_name_;
    }
    bool GetHasLongName() const {
       return (long_name_ != "");
    }
    bool GetHasDescription() const {
        return has_description_;
    }
    bool GetIsPositional() const {
        return is_positional_;
    }
    bool GetHasValue() const {
        return has_value_;
    }
    bool GetHasStoreValue() const {
        return has_store_value_;
    }

    const std::string& GetDescription() const {
        return description_;
    }
    const std::string& GetLongName() const {
        return long_name_;
    }
    char GetShortName() const {
        return short_name_;
    }
    
    int GetValue() const {
        return single_value_;
    }
    const std::vector<int>& GetMultValues() const {
        return mult_values_;
    }
    int GetMultValue(int ind) const;
    uint16_t GetMinMultValues() const {
        return min_mult_value_;
    }
    
    int* GetStoreValue() const {
        return store_value_;
    }
    std::vector<int>* GetStoreValues() const {
        return store_values_;
    }

    void PushMultVal(int arg);  

    void SetSingleValue(int val) {
        single_value_ = val;
        has_value_ = true;
    }

    IntArg& MultiValue();
    IntArg& MultiValue(uint16_t value);
    
    IntArg& StoreValues(std::vector<int>& values);
    IntArg& StoreValue(int& value);
    
    IntArg& Positional();
    
    IntArg& Default(int default_val);
    IntArg& Default(const std::vector<int>& default_val);
private:
    char short_name_;
    std::string long_name_;
    std::string description_;
    uint16_t min_mult_value_ = 0;
    std::vector<int> mult_values_;
    int single_value_;
    std::vector<int>* store_values_ = nullptr;
    int* store_value_ = nullptr;
    
    bool has_description_ = false;
    bool has_short_name_ = false;
    bool has_value_ = false;
    bool is_mult_value_ = false;
    bool has_default_ = false;
    bool has_store_value_ = false;
    bool is_positional_ = false;
};