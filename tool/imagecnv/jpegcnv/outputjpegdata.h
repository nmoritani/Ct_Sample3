#ifndef __OUTPUTJPEGDATA_H__
#define __OUTPUTJPEGDATA_H__

#include "output_type.h"

int output_jpegdata(const char *screen_no, const char *sample_no, const unsigned char *data, int data_size, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);

#endif
