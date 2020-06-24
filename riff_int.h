//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-7-12
//
// riff_int.h: 
//

#pragma once

// Note:
// All integer fields in Resource Interchange File Format (RIFF) are represented in little endian format.
// The followint definitions depend on Intel CPU architecture.

using uint_le16 = uint16_t;		// unsigned little endian 16 bit integer
using uint_le32 = uint32_t;		// unsigned little endian 32 bit integer
