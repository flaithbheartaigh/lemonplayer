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


#include <stdio.h>
#include <string.h>

#include "types.h"
#include "wave.h"
#include "error.h"

#include "layer3.h"
#include "l3subband.h"
#include "l3mdct.h"
#include "l3loop.h"
#include "l3bitstream.h"
//#include "bitstream.h"

compress_info_t compress_info;

static void update_status(int frames_processed)
{
    printf("\015[Frame %6d of %6ld] (%2.2f%%)", 
            frames_processed,config.mpeg.total_frames,
            (double)((double)frames_processed/config.mpeg.total_frames)*100); 
    fflush(stdout);
}


void compress()
{
    int             frames_processed;			//½ø¶ÈÌõ not use
    static short    buffer[2][samp_per_frame];
    int             channel;	//temporary

    int             i;			//temporary
    int             gr;			//temporary
//    short           sam[2][1344];  	//not use
//    double           snr32[32];		//not use
    side_info_t  side_info;					//every frame
    short          *buffer_window[2];		//every frame
    double          win_que[2][HAN_SIZE];	//every frame
    double          sb_sample[2][3][18][SBLIMIT];		//every frame
    double          mdct_freq[2][2][samp_per_frame2];	//every frame
    int             enc[2][2][samp_per_frame2];			//every frame
    scalefac_t   scalefactor;				//every frame
    bitstream_t     bs;			//share
 
    double          avg_slots_per_frame;
    double          frac_slots_per_frame;	//share
    long            whole_slots_per_frame;	//share
    double          slot_lag;				//share
    
    int             mean_bits;	//every frame
    unsigned long   sent_bits  = 0;	//share
    unsigned long   frame_bits = 0;	//share
    int             sideinfo_len;	//share

    open_bit_stream_w(&bs, config.outfile, BUFFER_SIZE);
    
//    memset((char*)snr32,0,sizeof(snr32));
//    memset((char *)sam,0,sizeof(sam));
    memset((char *)&side_info,0,sizeof(side_info_t));

    subband_initialise();
    mdct_initialise();

    config.mpeg.samples_per_frame = samp_per_frame;
    config.mpeg.total_frames      = config.wave.total_samples/config.mpeg.samples_per_frame;
    config.mpeg.bits_per_slot     = 8;
    frames_processed              = 0;

    sideinfo_len = 32;
 
	if(config.wave.channels==1)
			sideinfo_len += 136;
        else
			sideinfo_len += 256;

/* Figure average number of 'slots' per frame. */
    avg_slots_per_frame   = ((double)config.mpeg.samples_per_frame / 
                             ((double)config.wave.samplerate/1000)) *
                            ((double)config.mpeg.bitr /
                             (double)config.mpeg.bits_per_slot);
    whole_slots_per_frame = (int)avg_slots_per_frame;
    frac_slots_per_frame  = avg_slots_per_frame - (double)whole_slots_per_frame;
    slot_lag              = -frac_slots_per_frame;
    if(frac_slots_per_frame==0)
		config.mpeg.padding = 0;

    while(wave_get(buffer))
    {
        if ((frames_processed++)%7==0)
			update_status(frames_processed);

        buffer_window[0] = buffer[0];
        buffer_window[1] = buffer[1];

        if(frac_slots_per_frame)
            if(slot_lag>(frac_slots_per_frame-1.0))
            { /* No padding for this frame */
                slot_lag    -= frac_slots_per_frame;
                config.mpeg.padding = 0;
            }
            else 
            { /* Padding for this frame  */
                slot_lag    += (1-frac_slots_per_frame);
                config.mpeg.padding = 1;
            }
       config.mpeg.bits_per_frame = 8*(whole_slots_per_frame + config.mpeg.padding);
       mean_bits = (config.mpeg.bits_per_frame - sideinfo_len)>>1;


/* polyphase filtering */
       for(gr=0;gr<2;gr++)
            for(channel=config.wave.channels; channel--; )
                for(i=0;i<18;i++)
                {
                    window_subband(&buffer_window[channel],
                                      &win_que[channel][0],
                                      channel);
                    filter_subband(&win_que[channel][0],
                                      &sb_sample[channel][gr+1][i][0]);
                }

/* apply mdct to the polyphase output */
        mdct_sub(sb_sample, mdct_freq, &side_info);


/* bit and noise allocation */
        iteration_loop(mdct_freq,&side_info,
                          enc, mean_bits,&scalefactor);


/* write the frame to the bitstream */

       format_bitstream(enc,&side_info,&scalefactor, 
                           &bs,mdct_freq);

       frame_bits = sstell(&bs) - sent_bits;

       sent_bits += frame_bits;
    }    


}

void compress_init()
{
    open_bit_stream_w(&compress_info.bs, config.outfile, BUFFER_SIZE);
   
    memset((char *)&(compress_info.side_info),0,sizeof(side_info_t));

    subband_initialise();
    mdct_initialise();

    config.mpeg.samples_per_frame = samp_per_frame;
    config.mpeg.total_frames      = config.wave.total_samples/config.mpeg.samples_per_frame;
    config.mpeg.bits_per_slot     = 8;

    compress_info.sideinfo_len = 32;
 
	if(config.wave.channels==1)
		compress_info.sideinfo_len += 136;
    else
        compress_info.sideinfo_len += 256;

/* Figure average number of 'slots' per frame. */
	compress_info.avg_slots_per_frame   
						= ((double)config.mpeg.samples_per_frame / 
                             ((double)config.wave.samplerate/1000)) *
                            ((double)config.mpeg.bitr /
                             (double)config.mpeg.bits_per_slot);
	compress_info.whole_slots_per_frame = (int)compress_info.avg_slots_per_frame;
	compress_info.frac_slots_per_frame  = compress_info.avg_slots_per_frame - 
					(double)compress_info.whole_slots_per_frame;
	compress_info.slot_lag              = -compress_info.frac_slots_per_frame;
    if(compress_info.frac_slots_per_frame==0)
		config.mpeg.padding = 0;
}

int compress_frame(char* pcm,int pcm_size)
{
	int             channel;	//temporary
    int             i;			//temporary
    int             gr;			//temporary
    int				err;
    
    short          *buffer_window[2];		//every frame
    double          win_que[2][HAN_SIZE];	//every frame
//    double          sb_sample[2][3][18][SBLIMIT];		//every frame
    double          mdct_freq[2][2][samp_per_frame2];	//every frame
    int             enc[2][2][samp_per_frame2];			//every frame
    scalefac_t   	scalefactor;				//every frame    
    int             mean_bits;	//every frame
    
    static short    buffer[2][samp_per_frame];

    if(true)
    {
    	if (config.informat == IO_FORMAT_FILE)
    		err = wave_get(buffer);
    	else if (config.informat == IO_FORMAT_STREAM)
    		err = wave_get_stream(buffer,pcm,pcm_size);
    	
    	if (!err)
    		return err;
    	
        buffer_window[0] = buffer[0];
        buffer_window[1] = buffer[1];

        if(compress_info.frac_slots_per_frame)
            if(compress_info.slot_lag>(compress_info.frac_slots_per_frame-1.0))
            { /* No padding for this frame */
            	compress_info.slot_lag    -= compress_info.frac_slots_per_frame;
                config.mpeg.padding = 0;
            }
            else 
            { /* Padding for this frame  */
            compress_info.slot_lag    += (1-compress_info.frac_slots_per_frame);
                config.mpeg.padding = 1;
            }
       config.mpeg.bits_per_frame = 8*(compress_info.whole_slots_per_frame + 
    		   config.mpeg.padding);
       mean_bits = (config.mpeg.bits_per_frame - compress_info.sideinfo_len)>>1;


/* polyphase filtering */
       for(gr=0;gr<2;gr++)
            for(channel=config.wave.channels; channel--; )
                for(i=0;i<18;i++)
                {
                    window_subband(&buffer_window[channel],
                                      &win_que[channel][0],
                                      channel);
                    filter_subband(&win_que[channel][0],
                                      &(compress_info.sb_sample[channel][gr+1][i][0]));
                }

/* apply mdct to the polyphase output */
        mdct_sub(compress_info.sb_sample, mdct_freq, &compress_info.side_info);


/* bit and noise allocation */
        iteration_loop(mdct_freq,&compress_info.side_info,
                          enc, mean_bits,&scalefactor);


/* write the frame to the bitstream */

       format_bitstream(enc,&compress_info.side_info,&scalefactor, 
                           &compress_info.bs,mdct_freq);

       compress_info.frame_bits = sstell(&compress_info.bs) - compress_info.sent_bits;

       compress_info.sent_bits += compress_info.frame_bits;
    }    
    
    return 1;

}


void compress_close()
	{
	close_bit_stream_rw(&compress_info.bs);
	}