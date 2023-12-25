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
    if (opt_.append) {
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
    if (opt_.list) {
        if (opt_.k == 7) {
            ArchReader<7> ar(opt_.archive_filename);
            ar.ListFiles();
        } else if (opt_.k == 15) {
            ArchReader<15> ar(opt_.archive_filename);
            ar.ListFiles();
        }
    }
    if (opt_.concatenate) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<7> ar(opt_.filenames[i], opt_.archive_filename);
                ar.CopyFile();
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<15> ar(opt_.filenames[i], opt_.archive_filename);
                ar.CopyFile();
            }
        }
    }
    if (opt_.del) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<7> ar(opt_.archive_filename);
                ar.RemoveExcept(opt_.filenames[i]);
                ar.WriteExcept();
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<15> ar(opt_.archive_filename);
                ar.RemoveExcept(opt_.filenames[i]);
                ar.WriteExcept();
            }
        }
    }
}