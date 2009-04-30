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


#ifndef LAYER3_H
#define LAYER3_H

#include "bitstream.h"
/* Side information */
typedef struct {
        unsigned part2_3_length;
        unsigned big_values;
        unsigned count1;
        unsigned global_gain;
        unsigned scalefac_compress;
        unsigned table_select[3];
        unsigned region0_count;
        unsigned region1_count;
        unsigned preflag;
        unsigned scalefac_scale;
        unsigned count1table_select;

        unsigned part2_length;
        unsigned sfb_lmax;
        unsigned address1;
        unsigned address2;
        unsigned address3;
        double quantizerStepSize;
        unsigned slen[4];
} gr_info;

typedef struct {
    int main_data_begin; /* unsigned -> int */
    unsigned private_bits;
    int resvDrain;
    unsigned scfsi[2][4];
    struct {
        struct {
            gr_info tt;
        } ch[2];
    } gr[2];
} side_info_t;

typedef struct {
    double  l[2][2][21];
} psy_ratio_t;

typedef struct {
        double  l[2][2][21];
} psy_xmin_t;

typedef struct {
    int l[2][2][22];            /* [cb] */
    int s[2][2][13][3];         /* [window][cb] */
} scalefac_t;

typedef struct {
	side_info_t  	side_info;
    bitstream_t     bs;			//share
 
    double          avg_slots_per_frame;
    double          frac_slots_per_frame;	//share
    long            whole_slots_per_frame;	//share
    double          slot_lag;				//share
    unsigned long   sent_bits;	//share
    unsigned long   frame_bits;	//share
    int             sideinfo_len;	//share
    
    double          sb_sample[2][3][18][SBLIMIT];		//share
} compress_info_t;

void compress_init();
int compress_frame(char* pcm,int pcm_size);
void compress();

void compress_close();
#endif
