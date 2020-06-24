//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// riff_header.h: 
//

#pragma once

#include <cstring>
#include "riff_int.h"

class riff_header {
public:
	void		read_file();				// read header information from file
	bool		is_RIFF() const;			// true if ckID indicates RIFF chunk
	bool		is_fmt() const;				// true if ckID indicates fmt chunk
	bool		is_fact() const;			// true if ckID indicates fact chunk
	void		print_header() const;		// print header information
	uint_le32	header_length() const;		// return riff_header size
	uint_le32	ck_size() const;			// return ckSize
	uint_le32	ck_length() const;			// return ckSize + pdding size
	void		skip_data() const;			// skip body part
private:
	char		ckID[4];					// Chunk type identifier
	uint_le32	ckSize;						// Chunk size field 
	// For definitions of ckID (Chunk type identifier)
	static const char* ckID_RIFF;
	static const char* ckID_fmt;
	static const char* ckID_fact;
	static const char* ckID_data;
};

inline bool riff_header::is_RIFF() const
{
	return (strncmp(ckID, ckID_RIFF, sizeof(ckID)) == 0);
}

inline bool riff_header::is_fmt() const
{
	return (strncmp(ckID, ckID_fmt, sizeof(ckID)) == 0);
}

inline bool riff_header::is_fact() const
{
	return (strncmp(ckID, ckID_fact, sizeof(ckID)) == 0);
}

inline uint_le32 riff_header::header_length() const
{
	return (sizeof(ckID) + sizeof(ckSize));
}

inline uint_le32 riff_header::ck_size() const
{
	return (ckSize);
}

inline uint_le32 riff_header::ck_length() const
{
	return (ckSize % 2 == 0 ? ckSize : ckSize + 1);
}
