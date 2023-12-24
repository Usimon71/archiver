#include <include/arch_writer.h>
#include <include/arch_reader.h>
#include <include/ArgParser.h>

int main() {
    ArgumentParser::ArgParser parser("ArgParser");
    parser.AddFlag('c', "create");
    return 0;
}