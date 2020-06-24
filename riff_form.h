//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// riff_form.h: 
//

#pragma once

#include <cstring>
#include "riff_int.h"

class riff_form {
public:
	void		read_file();			// read form information from file
	bool		is_WAVE() const;		// true if formType indicates WAVE format
	void		print_form() const;		// print format information
	uint_le32	form_length() const;	// return form field length
private:
	char		formType[4];			// form type filed
	// for definition of formType identifier
	static const char* formType_WAVE;
};

inline bool riff_form::is_WAVE() const
{
	return (strncmp(formType, formType_WAVE, sizeof(formType)) == 0);
}

inline uint_le32 riff_form::form_length() const
{
	return (sizeof(formType));
}


