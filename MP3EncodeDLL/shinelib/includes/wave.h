//    Shine is an MP3 encoder
//    Copyright (C) 1999-2000  Gabriel Bouvigne
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.


#ifndef WAVE_H
#define WAVE_H

#include <stdio.h>
#include "types.h"

bool  wave_open();
bool  wave_open_stream();
int   wave_get(short buffer[2][samp_per_frame]);
int   wave_get_pcm(short buffer[2][samp_per_frame],char* data,int size);
void  wave_close();

#endif
