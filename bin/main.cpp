#include <include/arch_writer.h>
#include <fstream>
#include <string>
int main() {
    // ArchWriter<7> aw("data/in", "data/out.haf");
    // aw.Write();
    uint64_t size = 1024;
    const char* chr_size = reinterpret_cast<char*>(&size);
    uint64_t res = 0;
    for (int i = 0; i < 8; ++i) {
        res += (static_cast<uint64_t>(chr_size[i]) << (i * 8));
    }
    std::cout << res;
    return 0;
}