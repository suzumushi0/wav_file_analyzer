//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// fmt_chunk.h: 
//

#pragma once

#include "riff_int.h"

class fmt_chunk
{
public:
	void		read_file(const uint_le32 len);			// read len bytes fmt information 
	void		print_fmt(const uint_le32 len) const;	// print len bytes fmt chunk contents
private:
	uint_le16	wFormatTag;					// Format category
	uint_le16	nChannels; 					// Number of channels
	uint_le32	nSamplesPerSec; 			// Sampling rate (Hz)
	uint_le32	nAvgBytesPerSec;			// For buffer estimation (informative field)
	uint_le16	nBlockAlign;				// Data block size (Byte/sample)
	uint_le16	wBitsPerSample;				// Sample size/channel (bit)
	uint_le16	cbSize;						// Extra field size (opt.)
	uint_le16	wValidBitsPerSample;		// Valid bits/channel (bit)
	uint_le32	dwChannelMask;				// Speaker position mask
	struct {
		uint_le32		Data1;				// time low
		uint_le16		Data2;				// time mid
		uint_le16		Data3;				// time high and version
		unsigned char	Data4[8];			// seq and node (GUID Data 4 filed is represented in big endian format)
	} GUID;
};

// Definitions of wFormatTag
constexpr uint_le16 WAVE_FORMAT_PCM {0x0001};
constexpr uint_le16 WAVE_FORMAT_IEEE_FLOAT {0x0003};
constexpr uint_le16 WAVE_FORMAT_EXTENSIBLE {0xFFFE};
