#include "ArgParser.h"

#include <iostream>
#include <cctype>
#include <charconv>

using namespace ArgumentParser;

void ArgParser::AddHelp(char short_par, const std::string& long_par, const std::string& description) {
    HelpClass* help = new HelpClass{short_par, long_par, description};
    help_ = help;
    has_help_ = true;
}
bool ArgParser::Help() {
    return was_help_;
}
std::string ArgParser::HelpDescription() {
    std::string result;
    result += GetName() + "\n";
    if (Help()) {
        result += help_->GetDescription() + "\n";
    }
    result += "\n";
    const std::vector<IntArg*> int_args = GetIntArgs();
    for (IntArg* arg : int_args) {
        if (arg->GetHasShortName()) {
            result += "-" + std::string{arg->GetShortName()} + ",\t";
        }
        if (arg->GetHasLongName()) {
            result += "--" + arg->GetLongName() + "=<int>, ";
        }
        if (arg->GetHasDescription()) {
            result += arg->GetDescription() + " ";
        }
        result += "[";
        if (arg->GetIsMultValue()) {
            result += "repeated, min args = " + std::to_string(arg->GetMinMultValues());
        } else if (arg->GetHasValue()){
            result += "default = " + std::to_string(arg->GetValue());
        }
        if (arg->GetIsPositional()) {
            result += ", positional";
        }
        if (arg->GetHasStoreValue()) {
            result += ", stores value to a variable";
        }
        result += "]";

    }   
    result += "\n";
    const std::vector<StringArg*> string_args = GetStringArgs();
    for (StringArg* arg : string_args) {
        if (arg->GetHasShortName()) {
            result += "-" + std::string{arg->GetShortName()} + ",\t";
        }
        if (arg->GetHasLongName()) {
            result += "--" + arg->GetLongName() + "=<string>, ";
        }
        if (arg->GetHasDescription()) {
            result += arg->GetDescription() + " ";
        }
        result += "[";
        if (arg->GetIsMultValue()) {
            result += "repeated, min args = " + std::to_string(arg->GetMinMultValues());
        } else if (arg->GetHasValue()){
            result += "default = " + arg->GetValue();
        }
        if (arg->GetIsPositional()) {
            result += ", positional";
        }
        if (arg->GetHasStoreValue()) {
            result += ", stores value to a variable";
        }
        result += "]\n  ";
    }
    const std::vector<BoolArg*> bool_args = GetBoolArgs();
    for (BoolArg* arg : bool_args) {
        if (arg->GetHasShortFlag()) {
            result += "-" + std::string{arg->GetShortFlag()} + ",\t";
        }
        if (arg->GetHasLongFlag()) {
            result += "--" + arg->GetLongFlag() + ", ";
        }
        if (arg->GetHasDescription()) {
            result += arg->GetDescription() + " ";
        }
        result += "[";
        if (arg->GetHasValue()){
            result += "default = " + std::to_string(arg->GetValue());
        }
        if (arg->GetHasStoreValue()) {
            result += ", stores value to a variable";
        }
        result += "]";
        result += "\n";
    }
    result += "\n-h , --help Display this help and exit\n\n";

    return result;
}

StringArg& ArgParser::AddStringArgument(const std::string& long_par) {
    StringArg* arg = new StringArg{long_par};
    string_args_.push_back(arg);
    
    return *arg;
}
StringArg& ArgParser::AddStringArgument(char short_par, const std::string& long_par) {
    StringArg* arg = new StringArg{short_par, long_par};
    string_args_.push_back(arg);
    
    return *arg;
}
StringArg& ArgParser::AddStringArgument(char short_par, const std::string& long_par, const std::string& description){
    StringArg* arg = new StringArg{short_par, long_par, description};
    string_args_.push_back(arg);
    
    return *arg;
}
std::string ArgParser::GetStringValue(const std::string& param) {
    const std::vector<StringArg*>& args = ArgParser::GetStringArgs();
    for (size_t i = 0; i != args.size(); ++i) {
        if (args[i]->GetLongName() == param) {
            return args[i]->GetValue();
        }
    }
    std::cout << "No such parameter!\n";
    exit(1);
}

IntArg& ArgParser::AddIntArgument(const std::string& long_par) {
    IntArg* arg  = new IntArg{long_par};
    int_args_.push_back(arg);
    
    return *arg;
}
IntArg& ArgParser::AddIntArgument(char short_par, const std::string& long_par) {
    IntArg* arg = new IntArg{short_par, long_par};
    int_args_.push_back(arg);
    
    return *arg;
}
IntArg& ArgParser::AddIntArgument(char short_par, const std::string& long_par, const std::string& description) {
    IntArg* arg = new IntArg{short_par, long_par, description};
    int_args_.push_back(arg);
    
    return *arg;
}
IntArg& ArgParser::AddIntArgument(const std::string& long_par, const std::string& description) {
    IntArg* arg = new IntArg{long_par, description};
    int_args_.push_back(arg);
    
    return *arg;
}
int ArgParser::GetIntValue(const std::string& param, int pos) {
    if (pos < -1) {
        std::cout << "Invalid position parameter!\n";
        exit(1);
    }
    const std::vector<IntArg*>& args = this->GetIntArgs();
    for (size_t i = 0; i != args.size(); ++i) {
        if (args[i]->GetLongName() == param) {
            if (pos == -1) {
                return args[i]->GetValue();
            } else {
                return args[i]->GetMultValue(pos);
            }
        }
    }
    std::cout << "No such parameter!\n";
    exit(1);
}

BoolArg& ArgParser::AddFlag(const std::string& long_par) {
    BoolArg* arg = new BoolArg{long_par};
    bool_args_.push_back(arg);
    
    return *arg;
}
BoolArg& ArgParser::AddFlag(char short_par, const std::string& long_par) {
    BoolArg* arg = new BoolArg{short_par, long_par};
    bool_args_.push_back(arg);
    
    return *arg;
}
BoolArg& ArgParser::AddFlag(char short_par, const std::string& long_par, const std::string& description) {
    BoolArg* arg = new BoolArg{short_par, long_par, description};
    bool_args_.push_back(arg);
    return *arg;
}
BoolArg& ArgParser::AddFlag(const std::string long_par, const std::string& description) {
    BoolArg* arg = new  BoolArg{long_par, description};
    bool_args_.push_back(arg);
    
    return *arg;
}
bool ArgParser::GetFlag(const std::string& param) {
    const std::vector<BoolArg*>& args = this->GetBoolArgs();
    for (size_t i = 0; i != args.size(); ++i) {
        if (args[i]->GetLongFlag() == param) {
            return args[i]->GetValue();
        }
    }
    std::cout << "No such parameter!\n";
    exit(1);
}

ArgParser::ParseItem SplitItem(const std::string_view& arg_sv) {
    ArgParser::ParseItem res;
    for (size_t i = 0; i != arg_sv.size(); ++i) {
        if (arg_sv[i] == '=') {
            res.param = arg_sv.substr(0, i);
            res.value = arg_sv.substr(i + 1);
            return res;
        }
    }
    std::cout << "Invalid argument!";
    exit(1);
}

bool IsInt(const std::string_view& arg_sv) {
    if (arg_sv.size() > 1) {
        if (arg_sv[0] != '-' && !std::isdigit(arg_sv[0])) {
            return false;
        }
        for (size_t i = 1; i != arg_sv.size(); ++i) {
            if (!std::isdigit(arg_sv[i])) {
                return false;
            }
        }
    } else {
        if (!std::isdigit(arg_sv[0])) {
            return false;
        }
    }
    
    return true;
}

bool IsNotFlag(const std::string_view& arg_sv) {
    for (int i = 0; i != arg_sv.size(); ++i) {
        if (arg_sv[i] == '=') {
            return true;
        }
    }

    return false;
}

bool ArgParser::AllHaveValues() {
    const std::vector<IntArg*>& int_args = GetIntArgs();
    for (IntArg* int_arg : int_args) {
        if (!int_arg->GetHasValue()) {
            return false;
        }
    }
    const std::vector<StringArg*>& string_args = GetStringArgs();
    for (StringArg* string_arg : string_args) {
        if (!string_arg->GetHasValue()) {
            return false;
        }
    }

    return true;
}

void ArgParser::PushPositionalInt(int num) {
    std::vector<IntArg*>& int_args = GetIntArgs();
    for (size_t i = 0; i != int_args.size(); ++i) {
        if (int_args[i]->GetIsPositional()) {
            int_args[i]->PushMultVal(num);
            return;
        }
    }
    std::cout << "No positional arguments given!\n";
    exit(1);
}
bool ArgParser::PushPositionalString(const std::string& num) {
    std::vector<StringArg*>& int_args = GetStringArgs();
    for (size_t i = 0; i != int_args.size(); ++i) {
        if (int_args[i]->GetIsPositional()) {
            int_args[i]->PushMultVal(num);
            return true;
        }
    }
    std::cout << "No positional arguments given!\n";
    return false;
}

void ArgParser::RaiseShortFlag(char short_flag) {
    std::vector<BoolArg*>& bool_args = GetBoolArgs();
    for (size_t i = 0; i != bool_args.size(); ++i) {
        if (bool_args[i]->GetShortFlag() == short_flag) {
            bool_args[i]->RaiseFlag();
            return;
        }
    }
    std::cout << "Invalid flag!\n";
    exit(1);
}
void ArgParser::RaiseShortFlags(const std::string_view& arg_sv) {
    std::vector<BoolArg*>& bool_args = GetBoolArgs();
    for (char short_flag : arg_sv) {
        bool found = false;
        for (BoolArg* bool_arg : bool_args) {
            if (bool_arg->GetShortFlag() == short_flag) {
                bool_arg->RaiseFlag();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Invalid flag!\n";
            exit(1);
        }
    }
}
void ArgParser::RaiseLongFlag(const std::string_view& arg_sv) {
    std::vector<BoolArg*>& bool_args = GetBoolArgs();
    for (size_t i = 0; i != bool_args.size(); ++i) {
        if (bool_args[i]->GetLongFlag() == arg_sv) {
            bool_args[i]->RaiseFlag();
            return;
        }
    }
    std::cout <<"Invalid flag!\n";
    exit(1);
}

void ArgParser::SetIntLongArg(const std::string& param, int value) {
    std::vector<IntArg*>& int_args = GetIntArgs();
    for (size_t i = 0; i != int_args.size(); ++i) {
        if (int_args[i]->GetLongName() == param) {
            if (int_args[i]->GetIsMultValue()) {
                int_args[i]->PushMultVal(value);
            } else {
                int_args[i]->SetSingleValue(value);
            }
            return;
        }
    }

    std::cout <<"Invalid long int argument!\n";
    exit(1);
}
void ArgParser::SetIntShortArg(char param, int value) {
    std::vector<IntArg*>& int_args = GetIntArgs();
    for (size_t i = 0; i != int_args.size(); ++i) {
        if (int_args[i]->GetShortName() == param) {
            if (int_args[i]->GetIsMultValue()) {
                int_args[i]->PushMultVal(value);
            } else {
                int_args[i]->SetSingleValue(value);
            }
            return;
        }
    }

    std::cout <<"Invalid int short argument!\n";
    exit(1);
}

void ArgParser::SetStringLongArg(const std::string& param, std::string value) {
    std::vector<StringArg*>& string_args = this->GetStringArgs();
    for (size_t i = 0; i != string_args.size(); ++i) {
        if (string_args[i]->GetLongName() == param) {
            if (string_args[i]->GetIsMultValue()) {
                string_args[i]->PushMultVal(value);
            } else {
                string_args[i]->SetSingleValue(value);
            }
            return;
        }
    }

    std::cout <<"Invalid string long argument!\n";
    exit(1);
}
void ArgParser::SetStringShortArg(char param, std::string value) {
    std::vector<StringArg*>& string_args = GetStringArgs();
    for (size_t i = 0; i != string_args.size(); ++i) {
        if (string_args[i]->GetShortName() == param) {
            if (string_args[i]->GetIsMultValue()) {
                string_args[i]->PushMultVal(value);
                
            } else {
                string_args[i]->SetSingleValue(value);
            }
            return;
        }
    }

    std::cout <<"Invalid int argument!\n";
    exit(1);
}

void ArgParser::UpdateStoreValues() {
    const std::vector<IntArg*>& int_args = GetIntArgs();
    for (IntArg* int_arg : int_args) {
        if (int_arg->GetHasStoreValue()) {
            if (int_arg->GetIsMultValue()) {
                std::vector<int>* store_values = int_arg->GetStoreValues();
                *store_values = int_arg->GetMultValues();
            } else {
                int* store_value = int_arg->GetStoreValue();
                *store_value = int_arg->GetValue();
            }
        }
    }
    const std::vector<StringArg*>& string_args = GetStringArgs();
    for (StringArg* string_arg : string_args) {
        if (string_arg->GetHasStoreValue()) {
            if (string_arg->GetIsMultValue()) {
                std::vector<std::string>* store_values = string_arg->GetStoreValues();
                *store_values = string_arg->GetMultValues();
            } else {
                std::string* store_value = string_arg->GetStoreValue();
                *store_value = string_arg->GetValue();
            }
        }
    }
    const std::vector<BoolArg*>& bool_args = GetBoolArgs();
    for (BoolArg* bool_arg : bool_args) {
        if (bool_arg->GetHasStoreValue()) {
            bool* store_value = bool_arg->GetStoreValue();
            *store_value = bool_arg->GetValue();
        }
    }
}

bool ArgParser::CheckMinCountMultVal() {
    const std::vector<IntArg*>& int_args = GetIntArgs();
    for (IntArg* int_arg : int_args) {
        if (int_arg->GetIsMultValue() && (int_arg->GetMultValues().size() < int_arg->GetMinMultValues())) {
            return false;
        }
    }
    const std::vector<StringArg*>& string_args = GetStringArgs();
    for (StringArg* string_arg : string_args) {
        if (string_arg->GetIsMultValue() && (string_arg->GetMultValues().size() < string_arg->GetMinMultValues())) {
            return false;
        }
    }

    return true;
}

bool ArgParser::IsShortStringArg(char arg) {
    const std::vector<StringArg*> str_args = GetStringArgs();
    for (StringArg* str_arg : str_args) {
        if (str_arg->GetShortName() == arg) {
            return true;
        }
    }

    return false;
}
bool ArgParser::IsShortIntArg(char arg) {
    const std::vector<IntArg*> int_args = GetIntArgs();
    for (IntArg* int_arg : int_args) {
        if (int_arg->GetShortName() == arg) {
            return true;
        }
    }

    return false;
}

bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> args;
    for (int i = 0; i != argc; ++i) {
        std::string str = argv[i];
        args.push_back(str);
    }

    return Parse(args);
}
bool ArgParser::Parse(const std::vector<std::string>& args) {
    if (args.size() == 0) {
        return false;
    }
    if (args.size() == 1) {
        if (!AllHaveValues()) {
            return false;
        }

        return true;
    }
    std::string_view arg_sv;
    for (size_t i = 1; i != args.size(); ++i) {
        arg_sv = args[i];
        if (arg_sv[0] == '-') {
            if (arg_sv.size() < 2) {
                std::cout << "Invalid parameter!\n";
                return false;
            }
            if (IsInt(arg_sv.substr(1))) {
                PushPositionalInt(std::stoi(args[i]));
                continue;
            }
            
            if (arg_sv[1] == '-') {
                if (arg_sv == "--help") {
                    was_help_ = true;
                    std::cout << HelpDescription();
                    return true;
                }
                if (IsNotFlag(arg_sv)){
                    ArgParser::ParseItem item = SplitItem(arg_sv.substr(2));
                    if (IsInt(item.value)) {
                        SetIntLongArg(item.param, std::stoi(item.value));
                    } else {
                        SetStringLongArg(item.param, item.value);
                    }
                } else {
                    RaiseLongFlag(arg_sv.substr(2));
                }
            } else {
                if (arg_sv.size() == 2) {
                    if (IsShortStringArg(arg_sv[1])) {
                        SetStringShortArg(arg_sv[1], args[i + 1]);
                        ++i;
                        continue;
                    }
                    if (IsShortIntArg(arg_sv[1])) {
                        SetIntShortArg(arg_sv[1], std::stoi(args[i + 1]));
                        ++i;
                        continue;
                    }
                    RaiseShortFlag(arg_sv[1]);
                    continue;
                }
                if (IsNotFlag(arg_sv)){
                    ArgParser::ParseItem item = SplitItem(arg_sv.substr(1));
                    if (IsInt(item.value)) {
                        SetIntShortArg(item.param[0], std::stoi(item.value));
                    } else {
                        SetStringShortArg(item.param[0], item.value);
                    }
                } else {
                    RaiseShortFlags(arg_sv.substr(1));
                }
            }
        } else if (IsInt(arg_sv)){
            PushPositionalInt(std::stoi(args[i]));
        } else if (PushPositionalString(args[i])){}
        else {
            return false;
        }
    }
    if (!AllHaveValues()) {
        return false;
    }
    if (!CheckMinCountMultVal()) {
        return false;
    }
    UpdateStoreValues();

    return true;
}