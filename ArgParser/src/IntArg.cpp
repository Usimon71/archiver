#include "IntArg.h"

#include <iostream>
#include <cinttypes>

int IntArg::GetMultValue(int ind) const {
    std::vector<int> mult_values = GetMultValues();
    size_t size = mult_values.size();
    if (ind < 0 || (size - 1 < static_cast<size_t>(ind))){
        std::cout << "Wrong argument!";
        exit(1);
    }
    
    return mult_values[ind];
}

IntArg& IntArg::MultiValue() {
    is_mult_value_ = true;
    return *this;
}
IntArg& IntArg::MultiValue(uint16_t value) {
    is_mult_value_ = true;
    min_mult_value_ = value;
    
    return *this;
}

IntArg& IntArg::StoreValues(std::vector<int>& values) { 
    if (is_mult_value_) {
        store_values_ = &values;
        has_store_value_ = true;

        return *this;
    }
    std::cout << "IntArg is not MultiValue!\n";
    exit(1);
}

IntArg& IntArg::StoreValue(int& value) {
    if (is_mult_value_) {
        std::cout << "IntArg is MultiValue!\n";
        exit(1);
    }
    store_value_ = &value;
    has_store_value_ = true;

    return *this;
}

IntArg& IntArg::Positional() {
    is_positional_ = true;
    is_mult_value_ = true;
    
    return *this;
}

IntArg& IntArg::Default(int default_val) {
    if (is_mult_value_) {
        std::cout << "IntArg is MultiValue!\n";
        exit(1);
    }
    single_value_ = default_val;
    has_value_ = true;

    if (has_store_value_) {
        int* store_values = GetStoreValue();
        *store_values = default_val;
    }

    return *this;
}

IntArg& IntArg::Default(const std::vector<int>& default_val) {
    if (is_mult_value_) {
        mult_values_ = default_val;
        has_value_ = true;
        if (has_store_value_) {
            std::vector<int>* store_values = GetStoreValues();
            *store_values = default_val;
        }
        
        return *this;
    }
    std::cout << "IntArg is not MultiValue!\n";
    exit(1);
}

void IntArg::PushMultVal(int arg) {
    if(!is_mult_value_) {
        std::cout << "IntArg is MultiValue!\n";
        exit(1);
    }
    mult_values_.push_back(arg);
    has_value_ = true;
}