#include <include/arch_writer.h>
#include <include/arch_reader.h>
#include <fstream>
#include <string>
int main() {
    ArchWriter<7> aw("data/in2", "data/out.haf");
    aw.Write();
    ArchReader<7> ar("data/out.haf", "data/in2");
    ar.Read();
    return 0;
}