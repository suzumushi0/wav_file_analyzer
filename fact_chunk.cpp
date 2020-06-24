//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// fact_chunk.cpp: 
//

#include <iostream>
#include "fact_chunk.h"
#include "wav_file_analyzer.h"

void fact_chunk::read_file(const uint_le32 len)
{
    if (len != sizeof(dwFileSize)) {
        cout << "ckSize length errror." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&dwFileSize), sizeof(dwFileSize));
    if (!riff_file.good()) {
        cout << "dwFileSize read error." << endl;
        riff_file.close();
        exit(-1);
    }
}

void fact_chunk::print_fact() const
{
    cout << "  Number of samples\t\t" << dwFileSize << endl;
}
