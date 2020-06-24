//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// riff_int.h: 
//

#pragma once

// Note:
// All integer fields in Resource Interchange File Format (RIFF) are represented in little endian format.
// The followint definitions depend on Intel CPU architecture and Microsoft C++ compiler.

using uint_le16 = unsigned __int16;		// unsigned little endian 16 bit integer (Microsoft specific integer type)
using uint_le32 = unsigned __int32;		// unsigned little endian 32 bit integer (Microsoft specific integer type)
