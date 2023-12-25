#include "include/archiver.h"

#include <include/ArgParser.h>
#include <iostream>


int main(int argc, char** argv) {
    Options opt;

    ArgumentParser::ArgParser parser("HamArc");
    parser.AddFlag('c', "create", "Create new archive").StoreValue(opt.create).Default(false);
    parser.AddFlag('l', "list", "List files from archive").StoreValue(opt.list).Default(false);
    parser.AddFlag('x', "extract", "Extract files from archive").StoreValue(opt.extract).Default(false);
    parser.AddFlag('a', "append", "Add file to archive").StoreValue(opt.append).Default(false);
    parser.AddFlag('d', "delete", "Delete file from archive").StoreValue(opt.del).Default(false);
    parser.AddFlag('A', "concatenate", "Merge two archives to third archive").StoreValue(opt.concatenate);
    parser.AddStringArgument('f', "file", "ArchiveWriter file").StoreValue(opt.archive_filename).Default("out.haf");
    std::vector<std::string> empty_v;
    parser.AddStringArgument("files").MultiValue().Positional().StoreValues(opt.filenames).Default(empty_v);
    parser.AddIntArgument('p', "parity", "Number of parity bits in block (7/15)").StoreValue(opt.k).Default(7);
    parser.AddHelp('h', "help", "help");
    
    if (!parser.Parse(argc, argv)) {
        std::cout << "list: " << opt.list << '\n';
        std::cerr << "Wrong arguments\n";
        std::cout << parser.HelpDescription();
    } else {
        // std::cout << opt.archive_filename <<'\n';
        // for (int i = 0; i != opt.filenames.size(); ++i) {
        //     std::cout << opt.filenames[i] << '\n';
        // }
        Archiver arch(opt);
        arch.Run();
    }
    return 0;
}