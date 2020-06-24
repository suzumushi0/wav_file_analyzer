//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// riff_header.cpp: 
//

#include <iostream>
#include "riff_header.h"
#include "wav_file_analyzer.h"

using namespace std;

// Definitions of ckID (Chunk type identifier)
const char* riff_header::ckID_RIFF {"RIFF"};
const char* riff_header::ckID_fmt  {"fmt "};
const char* riff_header::ckID_fact {"fact"};
const char* riff_header::ckID_data {"data"};

void riff_header::read_file()
{
    riff_file.read(ckID, sizeof(ckID));
    if (!riff_file.good()) {
        cout << "ckID read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&ckSize), sizeof(ckSize));
    if (!riff_file.good()) {
        cout << "ckSize read error." << endl;
        riff_file.close();
        exit(-1);
    }
}

void riff_header::print_header() const
{
    cout << "ckID\t\t\t\t" << string {ckID, sizeof(ckID)} << endl;
    cout << "ckSize (Byte)\t\t\t" << ckSize << endl;
}

void riff_header::skip_data() const
{
    riff_file.seekg(ck_length(), ios_base::cur);
    if (!riff_file.good()) {
        cout << "data skip error." << endl;
        riff_file.close();
        exit(-1);
    }
}

