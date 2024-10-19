#include "StringArg.h"

#include <iostream>
#include <cinttypes>

const std::string StringArg::GetMultValue(int ind) const {
    std::vector<std::string> mult_values = GetMultValues();
    size_t size = mult_values.size();
    if (ind < 0 || (size - 1 < static_cast<size_t>(ind))){
        std::cout << "Wrong argument!";
        exit(1);
    }
    
    return mult_values[ind];
}

StringArg& StringArg::MultiValue() {
    is_mult_value_ = true;
    return *this;
}

StringArg& StringArg::MultiValue(uint16_t value) {
    is_mult_value_ = true;
    min_mult_value_ = value;
    return *this;
}

StringArg& StringArg::StoreValues(std::vector<std::string>& values) {
    if (is_mult_value_) {
        store_values_ = &values;
        has_store_value_ = true;

        return *this;
    }
    std::cout << "IntArg is not MultiValue!\n";
    exit(1);
}
StringArg& StringArg::StoreValue(std::string& value) {
    if (is_mult_value_) {
        std::cout << "IntArg is MultiValue!\n";
        exit(1);
    }
    store_value_ = &value;
    has_store_value_ = true;
    
    return *this;
}

StringArg& StringArg::Positional() {
    is_positional_ = true;
    is_mult_value_ = true;
    return *this;
}

StringArg& StringArg::Default(const std::string& default_val) {
    if (is_mult_value_) {
        std::cout << "StringArg is MultiValue!\n";
        exit(1);
    }
    single_value_ = default_val;
    has_value_ = true;
    if (has_store_value_) {
        std::string* store_value = GetStoreValue();
        *store_value = default_val;
    }
    return *this;
}
StringArg& StringArg::Default(const std::vector<std::string>& default_val) {
    if (is_mult_value_) {
        mult_values_ = default_val;
        has_value_ = true;
        if (has_store_value_) {
            std::vector<std::string>* store_values = GetStoreValues();
            *store_values = default_val;
        }
        return *this;
    }
    std::cout << "StringArg is not MultiValue!\n";
    exit(1);
}
void StringArg::PushMultVal(std::string arg) {
    if(!is_mult_value_) {
        std::cout << "StringArg is MultiValue!\n";
        exit(1);
    }
    mult_values_.push_back(arg);
    has_value_ = true;
}