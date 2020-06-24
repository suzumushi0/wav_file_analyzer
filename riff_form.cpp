//
// Copyright (c) 2020 Muneyoshi Suzuki. All Rights Reserved. 
//
// 2020-6-24
//
// riff_form.cpp: 
//

#include <iostream>
#include "riff_form.h"
#include "wav_file_analyzer.h"

// Definition of formType identifier
const char* riff_form::formType_WAVE {"WAVE"};


void riff_form::read_file()
{
    riff_file.read(formType, sizeof(formType));
    if (!riff_file.good()) {
        cout << "formType read error." << endl;
        riff_file.close();
        exit(-1);
    }
}

void riff_form::print_form() const
{
    cout << "formType\t\t\t" << string {formType, sizeof(formType)} << endl;
}
