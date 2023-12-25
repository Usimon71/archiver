#include "archiver.h"

void Archiver::Run() {
    if (opt_.create) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<7> aw(opt_.filenames[i], opt_.archive_filename);
                aw.Write();
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<15> aw(opt_.filenames[i], opt_.archive_filename);
                aw.Write();
            }
        }
    }
    if (opt_.extract) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<7> ar(opt_.archive_filename, opt_.filenames[i]);
                ar.Read();
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<15> ar(opt_.archive_filename, opt_.filenames[i]);
                ar.Read();
            }
        }
    }
}