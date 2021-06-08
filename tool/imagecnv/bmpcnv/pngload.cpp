#include "stdafx.h"
#include "zlib.h"
#include "png.h"

#include "pngload.h"


int png_load(const char *filename, IMAGE *img)
{
	int bit_depth, color_type;
	png_structp png_ptr;
	png_infop info_ptr = NULL, end_info = NULL;
	png_uint_32 width, height, h;
	int i;
	FILE *fp;
	png_bytepp row_ptr;


	img_init(img);

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		return -1;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		goto error;
	}
	info_ptr = png_create_info_struct(png_ptr);
	end_info = png_create_info_struct(png_ptr);
	if (info_ptr == NULL || end_info == NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		goto error;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		goto error;
	}

	png_init_io(png_ptr, fp);

	png_read_info(png_ptr, info_ptr);

	png_set_interlace_handling(png_ptr);

	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
				&color_type, NULL, NULL, NULL);


	if ((color_type & PNG_COLOR_MASK_COLOR) == 0) {
		/* カラーデータ以外はサポートしない */
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		goto error;
	}

	img->width   = (int)width;
	img->height  = (int)height;
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		img->pixel_depth = bit_depth;
		img->pixel_bytes = bit_depth / 8;
	} else {
		//カラー形式はRGBAに展開する
		img->pixel_depth = 32;
		img->pixel_bytes = 4;
		png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);	/* アルファーチャネルを補完 */
		png_read_update_info(png_ptr, info_ptr);			/* 更新 */
	}
	img->row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	img->stride = img->row_bytes - (img->pixel_depth * img->width + 7)/8;
	img->buf = (unsigned char*)malloc(img->row_bytes * img->height);

	//パレット読み込み
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_color *palette = NULL;
		png_bytep trans = NULL;
		int palette_num = 0;
		int trans_num = 0;

		png_get_PLTE(png_ptr, info_ptr, &palette, &palette_num);
		png_get_tRNS(png_ptr, info_ptr, &trans, &trans_num, NULL);
		img->palette_num = palette_num;
		img->palette_premultiplied = false;
		img->palette = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * palette_num);
		for (i = 0; i < palette_num; i++) {
			img->palette[i].r =	palette[i].red;
			img->palette[i].g =	palette[i].green;
			img->palette[i].b =	palette[i].blue;
			img->palette[i].a =	(i < trans_num)? trans[i] : 0xff;
		}
	}

	png_set_read_status_fn(png_ptr, NULL);
	//ピクセルデータ読み込み(R,G,B,A)
	row_ptr =  (png_bytepp)malloc(sizeof(char*) * height);
	for (h = 0; h < height; h++) {
		row_ptr[h] = img->buf + (h * img->row_bytes);
	}
	png_read_image(png_ptr, row_ptr);
	if (img->pixel_depth == 32) {
		for (h = 0; h < height; h++) {
			unsigned char *dt;
			dt = row_ptr[h];
			for (i=0;i<(img->row_bytes/4);i++,dt+=4) {
				unsigned int a = *(dt+3);
				*dt = *dt * a / 255;
				*(dt+1) = *(dt+1) * a / 255;
				*(dt+2) = *(dt+2) * a / 255;
			}
		}
	}
	free(row_ptr);
	//残りデータの読み込み（いまのところ使っていない）
	png_read_end(png_ptr, end_info);

	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

	if (fp) fclose(fp);

	return 0;

error:
	if (fp) fclose(fp);
	img_free(img);

	return -1;

}
