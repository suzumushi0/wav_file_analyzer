//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// wav_file_analyzer.cpp: 
//

// References 
//
// [1] Peter Kabal, "Audio File Format Specifications," May., 2017.
// http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
// [2] IBM and Microsoft, "Multimedia Programming Interface and Data Specifications 1.0," pp. 56-65, Aug., 1991.
// [3] Microsoft, "New Multimedia Data Types and Data Techniques Rev. 3.0," pp. 12-22, Apl., 1994.
// [4] Microsoft, "Multiple Channel Audio Data and WAVE Files," Dec. 2001.
// https ://docs.microsoft.com/en-us/previous-versions/windows/hardware/design/dn653308(v=vs.85)?redirectedfrom=MSDN
// [5] GUID format https://en.wikipedia.org/wiki/Universally_unique_identifier
//

// Note:
// All integer fields in Resource Interchange File Format (RIFF) are represented in little endian format.
// This program depends on Intel CPU architecture and Microsoft C++ compiler.


#include <iostream>
#include <fstream>

#include "riff_header.h"
#include "riff_form.h"
#include "fmt_chunk.h"
#include "fact_chunk.h"

using namespace std;

ifstream    riff_file;            // input file

int main(const int argc, const char* argv[])
{
    // argument check
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " wav_file_name" << endl;
        exit(-1);
    }

    // file open
    riff_file.open(argv[1], ios_base::binary);
    if (!riff_file.good()) {
        cout << "Can't open " << argv[1] << endl;
        exit(-1);
    }

    // read and check riff file main chunk header
    riff_header main_header;
    main_header.read_file();
    if (main_header.is_RIFF()) {
        main_header.print_header();
    } else {
        cout << "Not a RIFF file." << endl;
        riff_file.close();
        exit(-1);
    }
    uint_le32 remain = main_header.ck_length();

    // read and check WAVE file form
    riff_form form;
    form.read_file();
    if (form.is_WAVE()) {
        form.print_form();
    } else {
        cout << "Not a WAVE file." << endl;
        riff_file.close();
        exit(-1);
    }
    remain -= form.form_length();

    // read and check nested chunk headers and bodies
    while (remain > 0) {
        riff_header nested_header;
        nested_header.read_file();
        nested_header.print_header();
        remain -= nested_header.header_length();

        if (nested_header.is_fmt()) {
            fmt_chunk fmt_body;
            fmt_body.read_file(nested_header.ck_size());
            fmt_body.print_fmt(nested_header.ck_size());
            remain -= nested_header.ck_length();
            continue;
        }
        if (nested_header.is_fact()) {
            fact_chunk fact_body;
            fact_body.read_file(nested_header.ck_size());
            fact_body.print_fact();
            remain -= nested_header.ck_length();
            continue;
        }
        nested_header.skip_data();
        remain -= nested_header.ck_length();
    }
    riff_file.close();
}
