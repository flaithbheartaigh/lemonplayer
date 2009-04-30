#ifndef SHINE_H_
#define SHINE_H_

# ifdef __cplusplus
extern "C" {
# endif

void ShineEncode();

void init_encode_stream(char* filemp3);
void init_encode_file(char* filewave,char* filemp3);

int get_encode_frame_length();
int decode_one_frame(char*pcm,int pcm_size);

void close_encode_file(bool wavfile);


# ifdef __cplusplus
}
# endif

#endif /*SHINE_H_*/
