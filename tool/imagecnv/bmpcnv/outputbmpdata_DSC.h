#ifndef __OUTPUTBITMAPDATA_H__
#define __OUTPUTBITMAPDATA_H__

#include "imagedata.h"
#include "output_type.h"

int output_bmpdata(IMAGE *img, IMGCOLOR *color_plt, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);

#endif
