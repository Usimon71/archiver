#pragma once

#include <string>
#include <vector>

#include "StringArg.h"
#include "IntArg.h"
#include "BoolArg.h"
#include "Help.h"

namespace ArgumentParser {

class ArgParser {
public:
    ArgParser(const std::string& name)
        :name_(name)
        {}
    ArgParser() = default;
    ~ArgParser() {
        for (size_t i = 0; i != int_args_.size(); ++i) {
            delete int_args_[i];
        }
        for (size_t i = 0; i != string_args_.size(); ++i) {
            delete string_args_[i];
        }
        for (size_t i = 0; i != bool_args_.size(); ++i) {
            delete bool_args_[i];
        }
        if (has_help_) {
            delete help_;
        }
    }

    struct ParseItem {
        std::string param;
        std::string value;
    };
    
    std::string GetName() const {
        return name_;
    }
    
    bool Parse(int argc, char** argv);
    bool Parse(const std::vector<std::string>& args);

    bool Help();
    std::string HelpDescription();
    void AddHelp(char short_par, const std::string& long_par, const std::string& description);

    StringArg& AddStringArgument(const std::string& long_par);
    StringArg& AddStringArgument(char short_par, const std::string& long_par);
    StringArg& AddStringArgument(char short_par, const std::string& long_par, const std::string& def_val);
    std::string GetStringValue(const std::string& param);

    IntArg& AddIntArgument(const std::string& long_par);
    IntArg& AddIntArgument(char short_par, const std::string& long_par);
    IntArg& AddIntArgument(char short_par, const std::string& long_par, const std::string& description);
    IntArg& AddIntArgument(const std::string& long_par, const std::string& description);
    int GetIntValue(const std::string& param, int = -1);

    BoolArg& AddFlag(const std::string& long_par);
    BoolArg& AddFlag(char short_par, const std::string& long_par);
    BoolArg& AddFlag(char short_par, const std::string& long_par, const std::string& description);
    BoolArg& AddFlag(const std::string long_name, const std::string& description); 
    bool GetFlag(const std::string& param);

private:
    std::string name_ = "Some Parser";
    std::vector<StringArg*> string_args_;
    std::vector<IntArg*> int_args_;
    std::vector<BoolArg*> bool_args_;
    HelpClass* help_;

    bool has_help_ = false;
    bool was_help_ = false;

    std::vector<StringArg*>& GetStringArgs() {
        return string_args_;
    }
    std::vector<IntArg*>& GetIntArgs() {
        return int_args_;
    }
    std::vector<BoolArg*>& GetBoolArgs() {
        return bool_args_;
    }

    void PushPositionalInt(int num);
    bool PushPositionalString(const std::string& num);

    bool AllHaveValues();
    void UpdateStoreValues();
    bool CheckMinCountMultVal();

    void SetIntLongArg(const std::string& param, int value);
    void SetStringLongArg(const std::string& param, std::string value);
    void RaiseLongFlag(const std::string_view& arg_sv);
    void RaiseShortFlag(char short_flag);
    void RaiseShortFlags(const std::string_view& arg_sv);
    void SetIntShortArg(char param, int value);
    void SetStringShortArg(char param, std::string value);

    bool IsShortStringArg(char arg);
    bool IsShortIntArg(char arg);
    
};
} // namespace ArgumentParser