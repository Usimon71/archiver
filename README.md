# Archiver

## Description

A noise-resistant file archiver without compression that combines several files into one archive. For noise-resistant coding, [Hamming Codes](https://en.wikipedia.org/wiki/Hamming_code) was used.

## Functionality

* Merge multiple files ( >= 1) into one archive in .haf format (Hamming Archive File)
* Extract all or individual files from an archive
* Combining several archives into one
* Deleting specific files from archive
* Restoring an archive in case of damage or a message about the impossibility of recovery
* Return a list of files in the archive

## Implementation

Console application that supports the following command line arguments:

**-c, --create** - creating a new archive

**-f, --file=[ARHCNAME]** - name of the archive file

**-l, --list** - display a list of files in the archive

**-x, --extract** - extract files from the archive (if not specified, then all files)

**-a, --append** - add a file to the archive

**-d, --delete** - delete a file from the archive

**-A, --concatenate** - merge two archives

**-p, --parity** - number of parity bits in hamming encoding

**-b, --basedir** - set basedir for data (default is "data/")

**--help** - for help

**File names are passed as free arguments**

**Arguments for encoding and decoding are also passed via the command line** (Names and types of arguments are part of the task)

### Startup examples

*hamarc --create --file=ARCHIVE FILE1 FILE2 FILE3*

*hamarc -l -f ARCHIVE*

*hamarc --contenate ARCHIVE1 ARCHIVE2 -f ARCHIVE3*