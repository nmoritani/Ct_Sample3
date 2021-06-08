#include "stdafx.h"

#include "imagedata.h"
#include "bmpload.h"
#include "pngload.h"


void img_init(IMAGE *img)
{
	memset(img, 0, sizeof(IMAGE));
}

void img_free(IMAGE *img)
{
	if (img->buf) free(img->buf);
	if (img->palette) free(img->palette);
}

ImgGetPixel* img_get_pixelfunc(IMAGE *img)
{
	switch (img->pixel_depth) {
	case 1:
		return new ImgGetPixel1bpp(img);
	case 2:
		return new ImgGetPixel2bpp(img);
	case 4:
		return new ImgGetPixel4bpp(img);
	case 8:
		return new ImgGetPixel8bpp(img);
	case 16:
		return new ImgGetPixel16bpp(img);
	case 24:
		return new ImgGetPixel24bpp(img);
	case 32:
		return new ImgGetPixel32bpp(img);
	default:
		return NULL;
	}
}


//1bpp
ImgGetPixel1bpp::ImgGetPixel1bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	bit = 0x01;
	cnt = 8;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel1bpp::get()
{
	IMGCOLOR col;
	cnt -= 1;
	col.n = (*ptr >> cnt) & bit;
	if (cnt == 0) {
		cnt = 8;
		ptr++;
	}
	pos++;
	if (pos >= img->width) {
		if (cnt != 8) {
			ptr++;	//端数がある場合はポインタを進める
		}
		ptr += img->stride;
		pos = 0;
		cnt = 8;
	}

	return col;
}

IMGCOLOR ImgGetPixel1bpp::getRGBA()
{
	return img->palette[get().n];
}

//2bpp
ImgGetPixel2bpp::ImgGetPixel2bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	bit = 0x03;
	cnt = 8;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel2bpp::get()
{
	IMGCOLOR col;
	cnt -= 2;
	col.n = (*ptr >> cnt) & bit;
	if (cnt == 0) {
		cnt = 8;
		ptr++;
	}
	pos++;
	if (pos >= img->width) {
		//端数があるときはptrを進める
		if (cnt != 8) {
			ptr++;
		}
		ptr += img->stride;
		pos = 0;
		cnt = 8;
	}

	return col;
}

IMGCOLOR ImgGetPixel2bpp::getRGBA()
{
	return img->palette[get().n];
}

//4bpp
ImgGetPixel4bpp::ImgGetPixel4bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	bit = 0x0F;
	cnt = 8;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel4bpp::get()
{
	IMGCOLOR col;
	cnt -= 4;
	col.n = (*ptr >> cnt) & bit;
	if (cnt == 0) {
		cnt = 8;
		ptr++;
	}
	pos++;
	if (pos >= img->width) {
		//端数があるときはptrを進める
		if (cnt != 8) {
			ptr++;
		}
		ptr += img->stride;
		pos = 0;
		cnt = 8;
	}

	return col;
}

IMGCOLOR ImgGetPixel4bpp::getRGBA()
{
	return img->palette[get().n];
}

//8bpp
ImgGetPixel8bpp::ImgGetPixel8bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel8bpp::get()
{
	IMGCOLOR col;
	col.n = *ptr;
	ptr++;
	pos++;
	if (pos >= img->width) {
		ptr += img->stride;
		pos = 0;
	}

	return col;
}

IMGCOLOR ImgGetPixel8bpp::getRGBA()
{
	return img->palette[get().n];
}

//16bpp
ImgGetPixel16bpp::ImgGetPixel16bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	ptr = image->buf;
}

//RGB555の値をRGB32の値に変換する
static unsigned char col32to256(unsigned char c)
{
	return (c << 3) + (c >> 2);	//このように計算するらしい ペイントなどの読込値とも一致する
}


IMGCOLOR ImgGetPixel16bpp::get()
{
	IMGCOLOR col;
	unsigned short rgb;

	rgb = *ptr | (*(ptr+1) << 8);
	ptr += 2;
	col.r = col32to256((rgb >> 10) & 0x1f);
	col.g = col32to256((rgb >> 5) & 0x1f);
	col.b = col32to256((rgb) & 0x1f);
	col.a = 0xff;
	pos++;
	if (pos >= img->width) {
		ptr += img->stride;
		pos = 0;
	}

	return col;
}

IMGCOLOR ImgGetPixel16bpp::getRGBA()
{
	return get();
}

//24bpp
ImgGetPixel24bpp::ImgGetPixel24bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel24bpp::get()
{
	IMGCOLOR col;
	col.r = *ptr++;
	col.g = *ptr++;
	col.b = *ptr++;
	col.a = 0xff;
	pos++;
	if (pos >= img->width) {
		ptr += img->stride;
		pos = 0;
	}

	return col;
}

IMGCOLOR ImgGetPixel24bpp::getRGBA()
{
	return get();
}

//32bpp
ImgGetPixel32bpp::ImgGetPixel32bpp(IMAGE *image)
{
	img = image;
	pos = 0;
	ptr = image->buf;
}

IMGCOLOR ImgGetPixel32bpp::get()
{
	IMGCOLOR col;
	col.r = *ptr++;
	col.g = *ptr++;
	col.b = *ptr++;
	col.a = *ptr++;
	pos++;
	if (pos >= img->width) {
		ptr += img->stride;
		pos = 0;
	}

	return col;
}

IMGCOLOR ImgGetPixel32bpp::getRGBA()
{
	return get();
}

