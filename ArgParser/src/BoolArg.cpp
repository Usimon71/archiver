#include "BoolArg.h"

#include <iostream>
#include <cinttypes>

BoolArg& BoolArg::Default(bool default_val) {
    value_ = default_val;
    has_value_ = true;
    if(has_store_value_) {
        bool* store_value = GetStoreValue();
        *store_value = default_val;
    }

    return *this;
}

BoolArg& BoolArg::StoreValue(bool& value) {
    store_value_ = &value;
    has_store_value_ = true;
    
    return *this;
}