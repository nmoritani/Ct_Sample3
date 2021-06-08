#include "stdafx.h"
#include "windows.h"
#include "bmpload.h"

#define BGR2RGB(p) {\
		unsigned char tmp = *p;\
		*p = *(p + 2);\
		*(p + 2) = tmp;\
	}


int bmp_load(const char *filename, IMAGE *img)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBQUAD palette[256];
	FILE *fp;
	size_t readsize;
	int i, j;
	int palette_num;

	img_init(img);

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		return -1;
	}

	readsize = fread(&bf, 1, sizeof(BITMAPFILEHEADER), fp);
	if (readsize != sizeof(BITMAPFILEHEADER)) {
		goto error;
	}

	if (bf.bfType != 'MB') {
		goto error;
	}

	readsize = fread(&bi, 1, sizeof(BITMAPINFOHEADER), fp);
	if (readsize != sizeof(BITMAPINFOHEADER)) {
		goto error;
	}

	if (bi.biCompression != BI_RGB) {
		goto error;
	}

	img->width   = bi.biWidth;
	img->height  = bi.biHeight;
	img->pixel_depth = bi.biBitCount;
	img->pixel_bytes = bi.biBitCount / 8;

	//パレット読み込み
	palette_num = bi.biClrUsed;
	if (palette_num == 0) {
		//biClrUsedが0の時はデフォルト値を使用する必要がある
		switch (bi.biBitCount) {
		case 1:
			palette_num = 2;
			break;
		case 4:
			palette_num = 16;
			break;
		case 8:
			palette_num = 256;
			break;
		default:
			palette_num = 0;
			break;
		}
	}
	if (palette_num > 256) {	//256以上は未対応
		goto error;
	}
	if (palette_num > 0) {
		fread(palette, sizeof(RGBQUAD), palette_num, fp);
		img->palette_num = palette_num;
		img->palette_premultiplied = false;
		img->palette = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * img->palette_num);
		for (i = 0; i < img->palette_num; i++) {
			img->palette[i].r = palette[i].rgbRed;
			img->palette[i].g = palette[i].rgbGreen;
			img->palette[i].b = palette[i].rgbBlue;
			img->palette[i].a = 255;
		}
	}
	//ピクセルデータ位置までシーク
	fseek(fp, bf.bfOffBits, SEEK_SET);
	img->row_bytes = (img->pixel_depth * img->width + 7) / 8;	//1bpp,4bppがあるのでpixel_bytesは使えない
	img->row_bytes = (img->row_bytes + 3) & ~3;				//4バイトアライメント
	img->stride = img->row_bytes - ((img->pixel_depth * img->width + 7) / 8);	//1バイトアライメント

	//ピクセルデータ読み込み(BGRA)
	img->buf = (unsigned char*)malloc(img->row_bytes * img->height);
	for (i = img->height - 1; i >= 0; i--) {
		//最下行から格納されている
		fread(img->buf + img->row_bytes * i, 1, img->row_bytes, fp);
	}

	if (img->pixel_depth == 24 || img->pixel_depth == 32) {
		for (i = 0; i < img->height; i++) {
			for (j = 0; j < img->width; j++) {
				unsigned char *p;
				p = img->buf + img->row_bytes * i + j * img->pixel_bytes;
				//BGR->RGBに変換
				BGR2RGB(p);
			}
		}
	}

	fclose(fp);

	return 0;

error:
	if (fp) fclose(fp);
	img_free(img);

	return -1;
}

