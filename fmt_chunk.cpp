//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// fmt_chunk.cpp: 
//

#include <iostream>
#include <iomanip>
#include "fmt_chunk.h"
#include "wav_file_analyzer.h"

void fmt_chunk::read_file(const uint_le32 len)
{
    if (len != 16 && len != 18 && len != 40) {          // len must be 16, 18, or 40 bytes
        cout << "ckSize length errror." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&wFormatTag), sizeof(wFormatTag));
    if (!riff_file.good()) {
        cout << "wFormatTag read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&nChannels), sizeof(nChannels));
    if (!riff_file.good()) {
        cout << "nChannels read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&nSamplesPerSec), sizeof(nSamplesPerSec));
    if (!riff_file.good()) {
        cout << "nSamplesPerSec read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&nAvgBytesPerSec), sizeof(nAvgBytesPerSec));
    if (!riff_file.good()) {
        cout << "nAvgBytesPerSec read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&nBlockAlign), sizeof(nBlockAlign));
    if (!riff_file.good()) {
        cout << "nBlockAlign read error." << endl;
        riff_file.close();
        exit(-1);
    }
    riff_file.read(reinterpret_cast<char*>(&wBitsPerSample), sizeof(wBitsPerSample));
    if (!riff_file.good()) {
        cout << "wBitsPerSample read error." << endl;
        riff_file.close();
        exit(-1);
    }
    if (len == 18 || len == 40) {
        riff_file.read(reinterpret_cast<char*>(&cbSize), sizeof(cbSize));
        if (!riff_file.good()) {
            cout << "cbSize read error." << endl;
            riff_file.close();
            exit(-1);
        }
        if ((cbSize != 0 && cbSize != 22) || (len == 18 && cbSize == 22)) { // cbSize must be 0 or 22 bytes
            cout << "cbSize length errror." << endl;
            riff_file.close();
            exit(-1);
        }
        if (len == 40) {
            riff_file.read(reinterpret_cast<char*>(&wValidBitsPerSample), sizeof(wValidBitsPerSample));
            if (!riff_file.good()) {
                cout << "wValidBitsPerSample read error." << endl;
                riff_file.close();
                exit(-1);
            }
            riff_file.read(reinterpret_cast<char*>(&dwChannelMask), sizeof(dwChannelMask));
            if (!riff_file.good()) {
                cout << "dwChannelMask read error." << endl;
                riff_file.close();
                exit(-1);
            }
            riff_file.read(reinterpret_cast<char*>(&GUID), sizeof(GUID));
            if (!riff_file.good()) {
                cout << "GUID read error." << endl;
                riff_file.close();
                exit(-1);
            }
        }
    }
}

void fmt_chunk::print_fmt(const uint_le32 len) const
{
    cout << "  Format category\t\t";
    switch (wFormatTag) {
        case WAVE_FORMAT_PCM:
            cout << "PCM" << endl;
            break;
        case WAVE_FORMAT_IEEE_FLOAT:
            cout << "IEEE FLOAT" << endl;
            break;
        case WAVE_FORMAT_EXTENSIBLE:
            cout << "EXTENSIBLE" << endl;
            break;
        default:
            cout << "unknown" << endl;
            break;
    }
    cout << "  Number of channels\t\t" << nChannels << endl;

    cout << "  Sampling rate (Hz)\t\t" << nSamplesPerSec << endl;
 
    cout << "  Rate x Data block sies\t"<< nAvgBytesPerSec;
    if (nAvgBytesPerSec == nSamplesPerSec * nBlockAlign)
        cout << "\t(consistent)" << endl;
    else
        cout << "\t(inconsistent)" << endl;

    cout << "  Data block size (Byte/sample)\t" << nBlockAlign << endl;

    cout << "  Sample size par channel (bit)\t" << wBitsPerSample << endl;

    if (len == 18 || len == 40) {
        cout << "  Extra size\t\t\t" << cbSize << endl;
    }
    if (len == 40 && cbSize == 22) {
        // Some fmt chunk implementation uses 40 bytes fmt chunk while cbSize == 0.
        // Therefore extended fmt chunk fields are valid in case of cbSize == 22.
        cout << "  Valid bits par channel (bit)\t" << wValidBitsPerSample << endl;
        cout << "  Speaker position mask\t\t" << dwChannelMask << endl;
        cout << "  GUID\t\t\t\t" << hex << uppercase << setfill('0') << "{"
            << setw(8) << GUID.Data1 << "-"
            << setw(4) << GUID.Data2 << "-"
            << setw(4) << GUID.Data3 << "-"
            // Data 4 filed is represented in big endian format, therefore print each char in sequence.
            << setw(2) << static_cast<unsigned int>(GUID.Data4[0])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[1])
            << "-"
            << setw(2) << static_cast<unsigned int>(GUID.Data4[2])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[3])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[4])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[5])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[6])
            << setw(2) << static_cast<unsigned int>(GUID.Data4[7])
            << "}" << endl;
    }
}
