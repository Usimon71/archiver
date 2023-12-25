#include <include/arch_rw.h>
#include <include/ArgParser.h>

int main() {
    // ArchWriter<7> aw("in", "out.haf");
    // aw.Write();
    // ArchWriter<7> aw2("in2", "out.haf");
    // aw2.Write();
    // ArchWriter<7> aw3("in3", "out.haf");
    // aw3.Write();
    ArchReader<7> ar("out.haf", "in3");
    ar.Read();
    return 0;
}