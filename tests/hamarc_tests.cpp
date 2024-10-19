#include <gtest/gtest.h>
#include <lib/include/arch_rw.h>

TEST(ArchiveTestSuite, SingleMistakeCase) {
    ArchWriter<7> aw("test1", "test1.haf", "data/");
    aw.Write(false, true);
    ArchReader<7> ar("test1.haf", "test1", "data/");
    ar.Read();
}
TEST(ArchiveTestSuite, DoubleMistakeCase) {
    ArchWriter<7> aw("test1", "test1.haf", "data/");
    aw.Write(false, false, true);
    ArchReader<7> ar("test1.haf", "test1", "data/");
    ar.Read();
}