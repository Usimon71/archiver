#include "archiver.h"

void Archiver::Run() {
    if (opt_.create) {
        if (opt_.k == 7) {
            bool first_create = false;
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<7> aw(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                if (!first_create) {
                    aw.Write(false);
                    first_create = true;
                } else {
                    aw.Write(true);
                }
                
            }
        } else if (opt_.k == 15) {
            bool first_create = false;
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<15> aw(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                if (!first_create) {
                    aw.Write(false);
                    first_create = true;
                } else {
                    aw.Write(true);
                }
            }
        }
    }
    if (opt_.extract) {
        if (opt_.k == 7) {
            if (opt_.filenames.size() == 0) {
                ArchReader<7> ar(opt_.archive_filename, opt_.base_dir);
                ar.ReadAll();
            } else {
                for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                    ArchReader<7> ar(opt_.archive_filename, opt_.filenames[i], opt_.base_dir);
                    ar.Read();
                }
            }
            
        } else if (opt_.k == 15) {
            if (opt_.filenames.size() == 0) {
                ArchReader<15> ar(opt_.archive_filename, opt_.base_dir);
                ar.ReadAll();
            } else {
                for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                    ArchReader<15> ar(opt_.archive_filename, opt_.filenames[i], opt_.base_dir);
                    ar.Read();
                }
            }
        }
    }
    if (opt_.append) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<7> aw(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                aw.Write(true);
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchWriter<15> aw(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                aw.Write(true);
            }
        }
    }
    if (opt_.list) {
        if (opt_.k == 7) {
            ArchReader<7> ar(opt_.archive_filename, opt_.base_dir);
            ar.ListFiles();
        } else if (opt_.k == 15) {
            ArchReader<15> ar(opt_.archive_filename, opt_.base_dir);
            ar.ListFiles();
        }
    }
    if (opt_.concatenate) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<7> ar(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                ar.CopyFile();
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<15> ar(opt_.filenames[i], opt_.archive_filename, opt_.base_dir);
                ar.CopyFile();
            }
        }
    }
    if (opt_.del) {
        if (opt_.k == 7) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<7> ar(opt_.archive_filename, opt_.base_dir);
                ar.Delete(opt_.filenames[i]);
            }
        } else if (opt_.k == 15) {
            for (size_t i = 0; i != opt_.filenames.size(); ++i) {
                ArchReader<15> ar(opt_.archive_filename, opt_.base_dir);
                ar.Delete(opt_.filenames[i]);
            }
        }
    }
}