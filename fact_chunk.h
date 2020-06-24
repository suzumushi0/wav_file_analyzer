//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// fact_chunk.h: 
//

#pragma once

#include "riff_int.h"

class fact_chunk {
public:
	void		read_file(const uint_le32 len);	// read len bytes fact information
	void		print_fact() const;				// print fact chunk contents
private:
	uint_le32	dwFileSize;				// Number of samples (nBlockAlign x dwFileSize = data ckSize)
};

