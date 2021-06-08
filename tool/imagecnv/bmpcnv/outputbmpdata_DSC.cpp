#include "stdafx.h"
#include <vector>
#include "outputbmpdata.h"

using namespace std;

typedef struct {
	IMGCOLOR	col;
	unsigned char	index;
} COLMATCHDATA;

typedef struct {
	vector<COLMATCHDATA>	table;
} COLMATCHCACHE;

static int output_1bpp(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp, OUTPUT_TYPE type);
static int output_8bpp(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_rle(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_rle_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_pal(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_pal_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_stretch_h(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_stretch_v(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_pal_stretch_h(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_8bpp_pal_stretch_v(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_32bpp(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int output_32bpp_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp);
static int make_near_color_palette_map(IMGCOLOR *palette, int palette_num, IMGCOLOR *refpal, int refpal_num, unsigned char *map);
static unsigned char find_near_color(IMGCOLOR *palette, int palette_num, IMGCOLOR col);
static unsigned char find_near_color_cache(COLMATCHCACHE *cache, IMGCOLOR *palette, int palette_num, IMGCOLOR col);

/* �o�b�t�@�o�� */
static void output_vector(vector<unsigned char> *buffer, int column, const char *id, int flag, FILE *fp);
static void output_imgbuf(unsigned char *buffer, int size, int column, int stride, int flag, FILE *fp);
static void output_palette(IMGCOLOR *palette, int num, bool premultiplied, const char *id, int flag, FILE *fp);
static void output_offsetvector(vector<unsigned long> *offset, vector<unsigned char> *buffer, int column, const char *id, int flag, FILE *fp);
static void output_header(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp);
static void output_header_index(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp);
static void output_header_pal(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, int palette_num, FILE *fp);
static void output_header_32bpp(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp);
static void output_endmarker(const char *id, int flag, FILE *fp);

/* ���������O�X�֘A */
#define MAXRUNLENGTH_RLE		0x7F	//�A���f�[�^�̍ő吔
#define EOL							0x00										//�s�̏I�[

//�f�[�^�`�F�b�N
#ifdef _DEBUG
 #define DECOMPRESS_CHECK
#endif

/* ���������O�X�Q�֘A */

/****
 RLE2�f�[�^�`��
 0x00						���g�p
 0x01�`0x7E,AA,BB,CC...		��A���f�[�^��(0x01�`0x7E)����
 0x7F,NL,NH,AA,BB,CC...		��A���f�[�^��(((NH<<8)+NL)+0x7F)����
 0x80,0x01�`0xFE			�O�s�Ɠ���̃f�[�^��(0x01�`0xFE)����
 0x80,0xFF,NL,NH			�O�s�Ɠ���̃f�[�^��(((NH<<8)+NL)+0xFF)����
 0x81�`0xFE,XX				�A���f�[�^XX��(0x01�`0x7E)����
 0xFF,NL,NH,XX				�A���f�[�^XX��(((NH<<8)+NL)+0x7F)����
 ****/

#define DISCONTINUITY_2B_DATA		0x7F										//��A���f�[�^(2Byte)
#define MAXDISCONTINUITY_1B_LENGTH	0x7E										//��A���f�[�^�ő吔(1Byte)
#define MAXDISCONTINUITY_2B_LENGTH	((MAXDISCONTINUITY_1B_LENGTH + 1) + 0xFFFF)	//��A���f�[�^�ő吔(2Byte)

#define SAMELINE_DATA				0x80										//����s�f�[�^
#define SAMELINE_2B_DATA			0xFF										//����s�f�[�^(2byte)
#define MAXSAMELINE_1B_LENGTH		0xFE										//����s�f�[�^�ő吔(1Byte)
#define MAXSAMELINE_2B_LENGTH		((MAXSAMELINE_1B_LENGTH + 1) + 0xFFFF)			//����s�f�[�^�ő吔(2Byte)

#define CONTINUITY_DATA_FLAG		0x80										//�A���f�[�^�t���O
#define CONTINUITY_2B_DATA			0xFF										//�A���f�[�^(2Byte)
#define MAXCONTINUITY_1B_LENGTH		0x7E										//�A���f�[�^�T�C�Y(1Byte)
#define MAXCONTINUITY_2B_LENGTH		((MAXCONTINUITY_1B_LENGTH + 1) + 0xFFFF)		//�A���f�[�^�T�C�Y(2Byte)

#define DATA_8BPP  1
#define DATA_32BPP 2
#define MIN_RUNLENGTH_8BPP   3
#define MIN_SAMELENGTH_8BPP  3
#define MIN_RUNLENGTH_32BPP  2
#define MIN_SAMELENGTH_32BPP 2

typedef void (*COLORWRITER)(vector<unsigned char> *output, IMGCOLOR col);
static void color_writer_8bpp(vector<unsigned char> *output, IMGCOLOR col);
static void color_writer_32bpp(vector<unsigned char> *output, IMGCOLOR col);
static int compress_rle(vector<unsigned char> *output, IMGCOLOR *pixels, int count, COLORWRITER color_writer, unsigned long *max_value);
static int compress_rle2(vector<unsigned char> *output, IMGCOLOR *pixels, int width, int height, COLORWRITER colorWriter, unsigned long *max_value, int bpptype);
static void compress_data_discontinuity_rle2(vector<unsigned char> *output, IMGCOLOR *pixels, COLORWRITER colorWriter, int anotherdatanum, int position);
/* �C���[�W�ϊ��@*/
static IMAGE *convert_to_8bpp(IMAGE *img);

//8bpp
static int decompress_rle2_8bpp(vector<unsigned char> *input, vector<unsigned char> *output, int width, int height);
static void decompress_data_sameline_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output, int width);
static void decompress_data_sameline_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output, int width);
static void decompress_data_continuity_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output);
static void decompress_data_continuity_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output);
static int decompress_data_discontinuity_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output);
static int decompress_data_discontinuity_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output);

//32bpp
static int decompress_rle2_32bpp(vector<unsigned char> *input, vector<unsigned long> *output, int width, int height);
static void decompress_data_sameline_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output, int width);
static void decompress_data_sameline_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output, int width);
static void decompress_data_continuity_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output);
static void decompress_data_continuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output);
static int decompress_data_discontinuity_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output);
static int decompress_data_discontinuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output);

//�`�F�b�N
static int checkdata_8bpp(IMGCOLOR *b_data, int b_datasize, vector<unsigned char> *a_data);
static int checkdata_32bpp(IMGCOLOR *b_data, int b_datasize, vector<unsigned long> *a_data);

/*
 bmpload/pngload�ŉ�͂����C���[�W�f�[�^��C����`���ŏo�͂���
 */
int output_bmpdata(IMAGE *img, IMGCOLOR *color_plt, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int ret;
	ImgGetPixel *getter;
	bool hireso;

	getter = img_get_pixelfunc(img);
	if (getter == NULL) {
		return -1;
	}

	switch (type) {
	case OUTPUT_TYPE_HR_8BPP_PAL:
	case OUTPUT_TYPE_HR_8BPP_PAL_RLE2:
	case OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H:
	case OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_V:
	case OUTPUT_TYPE_HR_32BPP:
	case OUTPUT_TYPE_HR_32BPP_RLE2:
	case OUTPUT_TYPE_HR_AUTO:
	case OUTPUT_TYPE_HR_AUTO_RLE2:
		if (flag & OUTPUT_FOR_HIRESO_APL) {
			//���𑜓x�A�v���̏ꍇ�́u���𑜓x�A�C�R���v�Ƃ����T�O�͂Ȃ�
			hireso = false;
		} else {
			//���𑜓x�`���̓w�b�_�̃T�C�Y��1/2�ɂ��ďo�͂��邽�ߊ�T�C�Y�̓G���[�Ƃ���
			if ((img->width  & 1) != 0 || (img->height  & 1) != 0) {
				return -4;
			}
			hireso = true;
		}
		break;
	case OUTPUT_TYPE_1BPP:
	case OUTPUT_TYPE_8BPP:
	case OUTPUT_TYPE_8BPP_RLE:
	case OUTPUT_TYPE_8BPP_STRETCH_H:
	case OUTPUT_TYPE_8BPP_STRETCH_V:
	default:
		hireso = false;
		break;
	}


	//�o�͌`���ɂ��킹�Ċ֐����Ăяo��
	switch (type) {
	case OUTPUT_TYPE_1BPP:
	case OUTPUT_TYPE_1BPP_REVERSE:
		ret = output_1bpp(img, id, getter, hireso, flag, fp, type);
		break;
	case OUTPUT_TYPE_8BPP:
		ret = output_8bpp(img, color_plt, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_8BPP_RLE:
		ret = output_8bpp_rle(img, color_plt, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_8BPP_PAL:
		ret = output_8bpp_pal(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_8BPP_PAL_RLE2:
		ret = output_8bpp_pal_rle2(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_8BPP_STRETCH_H:
		ret = output_8bpp_stretch_h(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_8BPP_STRETCH_V:
		ret = output_8bpp_stretch_v(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H:
		ret = output_8bpp_pal_stretch_h(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_V:
		ret = output_8bpp_pal_stretch_v(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_32BPP:
		ret = output_32bpp(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_32BPP_RLE2:
		ret = output_32bpp_rle2(img, id, getter, hireso, flag, fp);
		break;
	case OUTPUT_TYPE_HR_AUTO:
		if (img->pixel_depth < 16) {
			ret = output_8bpp_pal(img, id, getter, hireso, flag, fp);
		} else {
			ret = output_32bpp(img, id, getter, hireso, flag, fp);
		}
		break;
	case OUTPUT_TYPE_HR_AUTO_RLE2:
		if (img->pixel_depth < 16) {
			ret = output_8bpp_pal_rle2(img, id, getter, hireso, flag, fp);
		} else {
			/* 8bpp�ւ̕ϊ������݂� */
			IMAGE *img8bpp;
			img8bpp = convert_to_8bpp(img);
			if (img8bpp != NULL) {
				ImgGetPixel *getter8bpp = img_get_pixelfunc(img8bpp);
				ret = output_8bpp_pal_rle2(img8bpp, id, getter8bpp, hireso, flag, fp);
				delete getter8bpp;
				img_free(img8bpp);
				free(img8bpp);
			} else {
				ret = output_32bpp_rle2(img, id, getter, hireso, flag, fp);
			}
		}
		break;
	default:
		ret = -2;
		break;
	}

	delete getter;

	return ret;
}

static int output_1bpp(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp, OUTPUT_TYPE type)
{
	int width;
	int height;
	int i, j, bit;
	unsigned dat;
	vector<unsigned char> buf;
	IMGCOLOR col;
	IMGCOLOR black;

	if(type == OUTPUT_TYPE_1BPP_REVERSE){
		//���F�����ɂ���
		black.r = 255;
		black.g = 255;
		black.b = 255;
		black.a = 255;
	}else{
		//���F�����ɂ���
		black.r = 0;
		black.g = 0;
		black.b = 0;
		black.a = 255;
	}
	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		bit = 0x80;
		dat = 0;
		for (j = 0; j < width; j++) {
			col = getter->getRGBA();
			//���Ƃ���F���P�Ƃ���
			if (col.n == black.n) {
				dat |= bit;
			}
			bit >>= 1;
			if (bit == 0) {
				bit = 0x80;
				buf.push_back(dat);
			dat = 0;
			}
		}
		//���܂肪����Ώo��
		if (bit != 0x80) {
			buf.push_back(dat);
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_1BPP_TRANS", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, (width + 7) / 8, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	vector<unsigned char>	buf;

	if(color_plt != NULL){
		output_8bpp_plt(img, color_plt, id, getter, hireso, flag, fp);
		return 0;
	}

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back((unsigned char)getter->get().n);
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_TRANS", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;
	vector<unsigned long>	offset;
	COLMATCHCACHE cache;
	unsigned char map[256];

	memset(map, 0, sizeof(map));
	if (img->pixel_depth <= 8) {
		//�p���b�g�ϊ�
		make_near_color_palette_map(img->palette, img->palette_num, color_plt, 256, map);
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (img->pixel_depth > 8) {
				//RGBA�ϊ�
				buf.push_back((unsigned long)find_near_color_cache(&cache, color_plt, 256, getter->get()));
			}else{
				//�p���b�g�ϊ�
				buf.push_back(map[getter->get().n]);
			}
		}
	}
	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_TRANS", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_rle(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;
	vector<unsigned long>	offset;

	if(color_plt != NULL){
		output_8bpp_rle_plt(img, color_plt, id, getter, hireso, flag, fp);
		return 0;
	}

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;

	//�s�P�ʂň��k(GEN�`��)
	for (i = 0; i < height; i++) {
		offset.push_back(buf.size()+(height*2));
		pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width);
		for (j = 0; j < width; j++) {
			pixels[j] = getter->get();
		}
		compress_rle(&buf, pixels, width, &color_writer_8bpp, NULL);
		buf.push_back(EOL);
	}
	if(pixels != NULL){
		free(pixels);
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_index(img, buf.size()+height+offset.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_RLE_TRANS", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_offsetvector(&offset, &buf, 32, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_rle_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;
	vector<unsigned long>	offset;
	COLMATCHCACHE cache;
	unsigned char map[256];

	memset(map, 0, sizeof(map));
	if (img->pixel_depth <= 8) {
		//�p���b�g�ϊ�
		make_near_color_palette_map(img->palette, img->palette_num, color_plt, 256, map);
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;

	//�s�P�ʂň��k(GEN�`��)
	for (i = 0; i < height; i++) {
		offset.push_back(buf.size()+(height*2));
		pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width);
		for (j = 0; j < width; j++) {
			if (img->pixel_depth > 8) {
				//RGBA�ϊ�
				pixels[j].n = (unsigned long)find_near_color_cache(&cache, color_plt, 256, getter->get());
			}else{
				//�p���b�g�ϊ�
				pixels[j].n = map[getter->get().n];
			}
		}
		compress_rle(&buf, pixels, width, &color_writer_8bpp, NULL);
		buf.push_back(EOL);
	}
	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_index(img, buf.size()+height+offset.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_RLE_TRANS", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_offsetvector(&offset, &buf, 32, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);
	return 0;
}

static int make_near_color_palette_map(IMGCOLOR *palette, int palette_num, IMGCOLOR *refpal, int refpal_num, unsigned char *map)
{
	int i;

	/* �p���b�g�ԍ��̕ϊ��e�[�u�����쐬 */
	for (i = 0; i < palette_num; i++) {
		/* �����ԍ��̐F��D�悷�� */
		if (i < refpal_num && palette[i].n == refpal[i].n) {
			map[i] = i;
		} else {
			map[i] = find_near_color(refpal, refpal_num, palette[i]);
		}
	}
	return 0;
}

static unsigned char find_near_color(IMGCOLOR *palette, int palette_num, IMGCOLOR col)
{
	int i;
	unsigned char near_index = 0;
	unsigned int distance;
	unsigned int min_distance = (unsigned int)-1;
	int dr, dg, db, da;

	/* �ߎ��F��T�� */
	for (i = 0; i < palette_num; i++) {
		/* �������v�Z */
		dr = palette[i].r - col.r;
		dg = palette[i].g - col.g;
		db = palette[i].b - col.b;
		da = palette[i].a - col.a;
		distance = ((dr * dr + dg * dg + db * db) << 8) + abs(da);
		if (distance < min_distance) {
			/* �������ł��߂��ԍ���ۑ� */
			near_index = i;
			min_distance = distance;
		}
	}

	return near_index;
}

static unsigned char find_near_color_cache(COLMATCHCACHE *cache, IMGCOLOR *palette, int palette_num, IMGCOLOR col)
{
	int i;
	int cache_size;
	int index;
	COLMATCHDATA data;

	/* �L���b�V������T�� */
	cache_size = cache->table.size();
	for (i = 0; i < cache_size; i++) {
		if (cache->table.at(i).col.n == col.n) {
			return cache->table.at(i).index;
		}
	}
	/* �p���b�g���猟�� */
	index = find_near_color(palette, palette_num, col);
	/* �L���b�V���ɓo�^ */
	data.col = col;
	data.index = index;
	cache->table.push_back(data);

	return index;
}

static int output_8bpp_pal(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	int max_palette;		//�g�p���Ă���ő�p���b�g�ԍ�
	unsigned char col;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;
	max_palette = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = (unsigned char)getter->get().n;
			buf.push_back(col);
			//�g�p���Ă���p���b�g�̍ő�l���X�V
			if (col > max_palette) {
				max_palette = col;
			}
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_pal(img, 0, 32, id, "GDI_IMAGE_TYPE_H_8BPP_PLT", hireso, flag, max_palette + 1, fp);	//����܂łO�ŏo�͂��Ă����̂ł��킹��

	//�p���b�g�f�[�^���t�@�C���ɏo��
	output_palette(img->palette, max_palette + 1, img->palette_premultiplied, id, flag, fp);
	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_pal_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int j;
	IMGCOLOR	*pixels = NULL;
	unsigned long max_palette;		//�g�p���Ă���ő�p���b�g�ԍ�
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;

	pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width * height);
	for (j = 0; j < width * height; j++) {
		pixels[j] = getter->get();
	}
	//�S�f�[�^�����k
	compress_rle2(&buf, pixels, width , height, &color_writer_8bpp, &max_palette, DATA_8BPP);

#ifdef DECOMPRESS_CHECK
	int ret;
	vector<unsigned char>	decompress_buf;	//�𓀌�f�[�^
	//�f�[�^��
	decompress_rle2_8bpp(&buf, &decompress_buf, width, height);
	//�𓀃f�[�^�`�F�b�N
	ret = checkdata_8bpp(pixels, width * height, &decompress_buf);
	if (ret != 0) {
		free(pixels);
		return -5;
	}
#endif
	if(pixels != NULL){
		free(pixels);
	}
	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_pal(img, 0, 8, id, "GDI_IMAGE_TYPE_H_8BPP_PLT_RLE2", hireso, flag, max_palette + 1, fp);	//����܂łO�ŏo�͂��Ă����̂ł��킹��

	//�p���b�g�f�[�^���t�@�C���ɏo��
	output_palette(img->palette, max_palette + 1, img->palette_premultiplied, id, flag, fp);
	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, 32, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

/*
 �{�^���̂悤�ɉ������Ɉ����L�΂��ĕ`�悷�邽�߂̌`��(���Ή�)
 �f�[�^�\����8BPP�摜�Ɠ����ŉ摜�^�C�v�݂̂��قȂ�
 */
static int output_8bpp_stretch_h(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
#if 0	//���Ή�
	int width;
	int height;
	int i, j;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	//�f�[�^�`����output_8bpp�Ɠ���
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back((unsigned char)getter->get().n);
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(img, buf.size(), 8, id, "UNKNOWN", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
#else
	return -1;
#endif
}

/*
 �{�^���̂悤�ɉ������Ɉ����L�΂��ĕ`�悷�邽�߂̌`��(���Ή�)
 �f�[�^�\����8BPP�摜�Ɠ����ŉ摜�^�C�v�݂̂��قȂ�
 */
static int output_8bpp_stretch_v(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
#if 0	//���Ή�
	int width;
	int height;
	int i, j;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	//�f�[�^�`����output_8bpp�Ɠ���
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back((unsigned char)getter->get().n);
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(img, buf.size(), 8, id, "UNKNOWN", hireso, flag, fp);

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
#else
	return -1;
#endif
}

/*
 �{�^���̂悤�ɉ������Ɉ����L�΂��ĕ`�悷�邽�߂̌`��
 �f�[�^�\����8BPP�摜�Ɠ����ŉ摜�^�C�v�݂̂��قȂ�
 */
#if 1
static int output_8bpp_pal_stretch_h(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	int max_palette;		//�g�p���Ă���ő�p���b�g�ԍ�
	unsigned char col;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^��z��ɓW�J����
	width = img->width;
	height = img->height;
	int count = width * height;
	unsigned char *pixels = new unsigned char[count];
	for (i = 0; i < count; i++) {
		pixels[i] = (unsigned char)getter->get().n;
	}
	//�������������k����
	int mid_min = width;	//�����̕�
	int mid;
	for (i = 0; i < height; i++) {
		unsigned char *p = &pixels[i * width];
		unsigned char *l = p + ((width - 1) / 2);
		unsigned char *r = p + (width / 2);
		//�����@����l r ����
		//��@����lr����
		//�����l
		col = *r;
		//�������獶�E�����ɓ����f�[�^��T��
		for (j = 0; j < ((width + 1) / 2); j++) {
			if (*l != col || *r != col) {
				break;
			}
			l--;
			r++;
		}
		//�����̕�
		mid = (r - l) - 1;
		if (mid_min > mid) {
			mid_min = mid;
		}
	}
	//�S�̂��璆�����������������̂����[
	int edge_num = (width - mid_min) / 2;
	//���[�ƒ����P�h�b�g���o�b�t�@�Ɋi�[
	max_palette = 0;
	for (i = 0; i < height; i++) {
		//�����i�[
		unsigned char *p;
		p = &pixels[i * width];
		for (j = 0; j < edge_num; j++) {
			buf.push_back(*p);
			if (*p > max_palette) {
				max_palette = *p;
			}
			p++;
		}
		//�����i�[ �����
		//�w�b�_�ɂ�1/2�����T�C�Y���o�͂���邽�ߋ����T�C�Y�̉摜�ɂ���
		if (mid_min > 0) {
			p = &pixels[i * width + (width / 2)];
			buf.push_back(*p);
			buf.push_back(*p);
			if (*p > max_palette) {
				max_palette = *p;
			}
		}
		//�E���i�[
		p = &pixels[i * width + width - edge_num];
		for (j = 0; j < edge_num; j++) {
			buf.push_back(*p);
			if (*p > max_palette) {
				max_palette = *p;
			}
			p++;
		}
	}
	//���������
	delete[] pixels;
	
	//�摜�̃T�C�Y��ύX����
	IMAGE tmp_img = *img;
	tmp_img.width = edge_num * 2;
	if (mid_min > 0) {
		tmp_img.width += 2;
	}

	//�o��
	//GDI�p�f�[�^�`��
	//GDI�Ƃ��̕`��`���̑g�ݍ��킹�͑��݂��Ȃ�
	
	return -5;

}
#else
static int output_8bpp_pal_stretch_h(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	int max_palette;		//�g�p���Ă���ő�p���b�g�ԍ�
	unsigned char col;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	//�f�[�^�`����output_8bpp_pal�Ɠ���
	width = img->width;
	height = img->height;
	max_palette = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = (unsigned char)getter->get().n;
			buf.push_back(col);
			//�g�p���Ă���p���b�g�̍ő�l���X�V
			if (col > max_palette) {
				max_palette = col;
			}
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_pal(img, 0, 8, id, "UNKNOWN", hireso, flag, max_palette + 1, fp);	//����܂łO�ŏo�͂��Ă����̂ł��킹��

	//�p���b�g�f�[�^���t�@�C���ɏo��
	output_palette(img->palette, max_palette + 1, img->palette_premultiplied, id, flag, fp);
	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}
#endif

/*
 �X�N���[���o�[�̂悤�ɏc�����Ɉ����L�΂��ĕ`�悷�邽�߂̌`��
 �f�[�^�\����8BPP�摜�Ɠ����ŉ摜�^�C�v�݂̂��قȂ�
 */
static int output_8bpp_pal_stretch_v(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	int max_palette;		//�g�p���Ă���ő�p���b�g�ԍ�
	unsigned char col;
	vector<unsigned char>	buf;

	//�p���b�g�Ȃ�(8bpp�𒴂���j�͕ϊ��ł��Ȃ�
	if (img->pixel_depth > 8) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	//�f�[�^�`����output_8bpp_pal�Ɠ���
	width = img->width;
	height = img->height;
	max_palette = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = (unsigned char)getter->get().n;
			buf.push_back(col);
			//�g�p���Ă���p���b�g�̍ő�l���X�V
			if (col > max_palette) {
				max_palette = col;
			}
		}
	}

	//GDI�p�f�[�^�`��
	//GDI�Ƃ��̕`��`���̑g�ݍ��킹�͑��݂��Ȃ�
	
	return -5;
}

static int output_32bpp(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	IMGCOLOR col;
	vector<unsigned char>	buf;

	//�p���b�g����͕ϊ��ł��Ȃ�
	if (img->pixel_depth < 16) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = getter->get();
			buf.push_back(col.a);
			buf.push_back(col.b);
			buf.push_back(col.g);
			buf.push_back(col.r);
		}
	}

	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_32bpp(img, 0, 32, id, "GDI_IMAGE_TYPE_H_32BPP", hireso, flag, fp);	//����܂łO�ŏo�͂��Ă����̂ł��킹��
	
	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, width * 4, id, flag, fp);
	
	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_32bpp_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, bool hireso, int flag, FILE *fp)
{
	int width;
	int height;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;

	//�p���b�g����͕ϊ��ł��Ȃ�
	if (img->pixel_depth < 16) {
		return -3;
	}

	//�f�[�^���o�b�t�@�ɍ쐬
	width = img->width;
	height = img->height;

	pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width * height);
	for (j = 0; j < width * height; j++) {
		pixels[j] = getter->get();
	}
	//�S�f�[�^�����k
	compress_rle2(&buf, pixels, width , height, &color_writer_32bpp, NULL, DATA_32BPP);

#ifdef DECOMPRESS_CHECK
	int ret;
	vector<unsigned long>	decompress_buf;	//�𓀌�f�[�^
	//�f�[�^��
	decompress_rle2_32bpp(&buf, &decompress_buf, width, height);
	//�𓀃f�[�^�`�F�b�N
	ret = checkdata_32bpp(pixels, width * height, &decompress_buf);
	if (ret != 0) {
		free(pixels);
		return -5;
	}
#endif

	if(pixels != NULL){
		free(pixels);
	}
	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header_32bpp(img, 0, 32, id, "GDI_IMAGE_TYPE_H_32BPP_RLE2", hireso, flag, fp);	//����܂łO�ŏo�͂��Ă����̂ł��킹��

	//�o�b�t�@�̃f�[�^���t�@�C���ɏo��
	output_vector(&buf, 32, id, flag, fp);

	//END�}�[�J�[�o��
	output_endmarker(id, flag, fp);

	return 0;
}

/* �o�b�t�@�o�� */
static void output_vector(vector<unsigned char> *buffer, int column, const char *id, int flag, FILE *fp)
{
	int size = buffer->size();
	int i, n;

	fprintf(fp, "const unsigned char pc%s[]={\n", id);

	n = 0;
	for (i = 0; i < size; i++) {
		if (n >= column) {
			fprintf(fp, ",\n");
			n = 0;
		}
		if (n == 0) {
			//fprintf(fp, "\t");
		} else {
			fprintf(fp, ",");
		}
		fprintf(fp, "0x%02X", buffer->at(i));
		n++;
	}
	if (n != 0) {
		fprintf(fp, "\n");
	}

	fprintf (fp, "};\n\n");

}

static void output_imgbuf(unsigned char *buffer, int size, int column, int stride, int flag, FILE *fp)
{
	int i, n;
	unsigned char *ptr;

	n = 0;
	ptr = buffer;
	for (i = 0; i < size; i++) {
		if (n >= column) {
			fprintf(fp, ",\n");
			n = 0;
			ptr += stride;
		}
		if (n == 0) {
			//fprintf(fp, "\t");
		} else {
			fprintf(fp, ",");
		}
		fprintf(fp, "0x%02X", *ptr);
		n++;
		ptr++;
	}
	if (n != 0) {
		fprintf(fp, "\n");
	}
}

static void output_palette(IMGCOLOR *palette, int num, bool premultiplied, const char *id, int flag, FILE *fp)
{
	int i, n;

	fprintf(fp, "const unsigned char pcPLT_%s[]={\n", id);

	n = 0;
	for (i = 0; i < num; i++) {
		if (n >= 8) {
			fprintf(fp, ",\n");
			n = 0;
		}
		if (n == 0) {
			//fprintf(fp, "\t");
		} else {
			fprintf(fp, ", ");
		}
		if (premultiplied) {
			fprintf(fp, "0x%02X,0x%02X,0x%02X,0x%02X",
				palette->a,
				palette->b,
				palette->g,
				palette->r
				);
		} else {
			fprintf(fp, "0x%02X,0x%02X,0x%02X,0x%02X",
				palette->a,
				palette->b * palette->a / 255,
				palette->g * palette->a / 255,
				palette->r * palette->a / 255
				);
		}
		palette++;
		n++;
	}
	if (n != 0) {
		fprintf(fp, "\n");
	}

	fprintf (fp, "};\n\n");
}

static void output_offsetvector(vector<unsigned long> *offset, vector<unsigned char> *buffer, int column, const char *id, int flag, FILE *fp)
{
	int size = offset->size();
	int i, n;

	fprintf(fp, "const unsigned char pc%s[]={\n", id);

	n = 0;
	for (i = 0; i < size; i++) {
		if (n == 0) {
			//fprintf(fp, "\t");
		}
		fprintf(fp, "0x%02X,0x%02X,", offset->at(i)%256, offset->at(i)/256);
		n += 2;
		if (n >= column) {
			fprintf(fp, "\n");
			n = 0;
		}
	}
	size = buffer->size();
	for (i = 0; i < size; i++) {
		if (n == 0) {
			//fprintf(fp, "\t");
		}
		fprintf(fp, "0x%02X", buffer->at(i));
		if(i != (size - 1)) {
			fprintf(fp, ",");
		}
			
		n++;
		if (n >= column) {
			fprintf(fp, "\n");
			n = 0;
		}
	}
	if (n != 0) {
		fprintf(fp, "\n");
	}

	fprintf (fp, "};\n\n");

}

/* ���������O�X���k�֐� */
static void color_writer_8bpp(vector<unsigned char> *output, IMGCOLOR col)
{
	output->push_back((unsigned char)col.n);
}

static void color_writer_32bpp(vector<unsigned char> *output, IMGCOLOR col)
{
	output->push_back((unsigned char)col.a);
	output->push_back((unsigned char)col.b);
	output->push_back((unsigned char)col.g);
	output->push_back((unsigned char)col.r);
}

static int compress_rle(vector<unsigned char> *output, IMGCOLOR *pixels, int count, COLORWRITER colorWriter, unsigned long *max_value)
{
	int i, j, position;
	int runlength, anotherdatanum;
	IMGCOLOR prevcol;

	if (max_value != NULL) {
		unsigned long	max;
		//�g�p����Ă���ő�̃s�N�Z���l��������i�p���b�g�ԍ��̍ő�l��������̂Ɏg�p����j
		max = 0;
		for (i = 0; i < count; i++) {
			if (pixels[i].n > max) {
				max = pixels[i].n;
			}
		}
		*max_value = max;
	}

	i = 0;
	anotherdatanum = 0;
	position = 0;

	while (i < count) {
		//�A����
		prevcol.n = pixels[i].n;
		runlength = 1;
		while (i + runlength < count && runlength < MAXRUNLENGTH_RLE) {
			if (pixels[i + runlength].n != prevcol.n) {
				break;
			}
			runlength++;
		}
		//��A���f�[�^����
		if(anotherdatanum > 0){
			if ((runlength >= 2) || (anotherdatanum == MAXRUNLENGTH_RLE) ) {
				//��A���f�[�^����������
				output->push_back(anotherdatanum);
				//��A���f�[�^��������
				for(j = 0; j < anotherdatanum; j++) {
					colorWriter(output, pixels[position + j]);
				}
				//�J�E���g�N���A
				anotherdatanum = 0;
				position = 0;
			}
		}

		if (runlength >= 2) {
			//�A���f�[�^��������(CONTINUITY_DATA_FLAG + runlength, data)
			output->push_back(CONTINUITY_DATA_FLAG + runlength);
			colorWriter(output, prevcol);
			i += runlength;
		} else {
			//�A������1�Ȃ��A���f�[�^���𐔂���
			if(anotherdatanum == 0){
				position = i;
			}
			anotherdatanum++;
			i++;
		}
	}

	//��A���f�[�^����
	if(anotherdatanum > 0){
		//��A���f�[�^����������
		output->push_back(anotherdatanum);
		//��A���f�[�^��������
		for(j = 0; j < anotherdatanum; j++) {
			colorWriter(output, pixels[position + j]);
		}
		//�J�E���g�N���A
		anotherdatanum = 0;
		position = 0;
	}

	return 0;
}

static int compress_rle2(vector<unsigned char> *output, IMGCOLOR *pixels, int width, int height, COLORWRITER colorWriter, unsigned long *max_value, int bpptype)
{
	int i, position;
	int runlength, count, samelength, anotherdatanum;
	int min_runlength, min_samelength;
	int extralength;
	IMGCOLOR prevcol;
	unsigned char tmp;

	count = width * height;

	//�A���f�[�^�A����s�f�[�^�̈��k�ŏ�����ݒ�
	if(bpptype == DATA_8BPP){
		min_runlength  = MIN_RUNLENGTH_8BPP;
		min_samelength = MIN_SAMELENGTH_8BPP;
	} else {
		min_runlength  = MIN_RUNLENGTH_32BPP;
		min_samelength = MIN_SAMELENGTH_32BPP;
	}

	if (max_value != NULL) {
		unsigned long	max;
		//�g�p����Ă���ő�̃s�N�Z���l��������i�p���b�g�ԍ��̍ő�l��������̂Ɏg�p����j
		max = 0;
		for (i = 0; i < count; i++) {
			if (pixels[i].n > max) {
				max = pixels[i].n;
			}
		}
		*max_value = max;
	}
	i = 0;
	anotherdatanum = 0;
	position = 0;

	while (i < count) {
		prevcol.n = pixels[i].n;
		runlength = 1;
		samelength = 0;
		//�A����
		while ((i + runlength < count) && (runlength < MAXCONTINUITY_2B_LENGTH)) {
			if (pixels[i + runlength].n != prevcol.n) {
				break;
			}
			runlength++;
		}
		//�A���s
		if(i > width){
			while ((i + samelength < count) && (samelength < MAXSAMELINE_2B_LENGTH)) {
				if (pixels[i + samelength].n != pixels[i + samelength - width].n) {
					break;
				}
				samelength++;
			}
		}
		//��A���f�[�^����
		if(anotherdatanum > 0){
			if ((runlength >= min_runlength) || (samelength >= min_samelength) || (anotherdatanum == MAXDISCONTINUITY_2B_LENGTH) ) {
				compress_data_discontinuity_rle2(output, pixels, colorWriter, anotherdatanum, position);
				anotherdatanum = 0;
				position = 0;
			}
		}
		
		if (runlength >= min_runlength && (runlength > samelength)) {
			//�A���f�[�^�̏�������
			if(runlength > MAXCONTINUITY_1B_LENGTH) {
				//�A���f�[�^��������(0xFF,runlength(2byte),data)
				output->push_back(CONTINUITY_2B_DATA);
				extralength = runlength - (MAXCONTINUITY_1B_LENGTH + 1);
				tmp = (unsigned char)(extralength & 0xFF);
				output->push_back(tmp);
				tmp = (unsigned char)((extralength >> 8) & 0xFF);
				output->push_back(tmp);
				colorWriter(output, prevcol);
			} else {
				//�A���f�[�^��������(CONTINUITY_DATA_FLAG + runlength, data)
				output->push_back(CONTINUITY_DATA_FLAG + runlength);
				colorWriter(output, prevcol);
			}
			i += runlength;
			
		} else if(samelength >= min_samelength){
			//����s�f�[�^�̏�������(SAMELINE_DATA, samelength)
			output->push_back(SAMELINE_DATA);
			if(samelength > MAXSAMELINE_1B_LENGTH) {
				//2byte
				output->push_back(SAMELINE_2B_DATA);
				extralength = samelength - (MAXSAMELINE_1B_LENGTH + 1);
				tmp = (unsigned char)(extralength & 0xFF);
				output->push_back(tmp);
				tmp = (unsigned char)((extralength >> 8) & 0xFF);
				output->push_back(tmp);
				
			} else {
				output->push_back(samelength);
			}
			i += samelength;

		} else {
			//�A������1�Ȃ��A���f�[�^���𐔂���
			if(anotherdatanum == 0){
				position = i;
			}
			anotherdatanum++;
			i++;
		}
	}
	//��A���f�[�^����
	if(anotherdatanum > 0){
		compress_data_discontinuity_rle2(output, pixels, colorWriter, anotherdatanum, position);
		anotherdatanum = 0;
		position = 0;
	}
	return 0;
}
	
static void compress_data_discontinuity_rle2(vector<unsigned char> *output, IMGCOLOR *pixels, COLORWRITER colorWriter, int anotherdatanum, int position)
{
	int i;
	unsigned char tmp;
	int extralength;

	if(anotherdatanum > MAXDISCONTINUITY_1B_LENGTH) {
		output->push_back(DISCONTINUITY_2B_DATA);
		extralength = anotherdatanum - (MAXDISCONTINUITY_1B_LENGTH + 1);
		tmp = (unsigned char)(extralength & 0xFF);
		output->push_back(tmp);
		tmp = (unsigned char)((extralength >> 8) & 0xFF);
		output->push_back(tmp);
	} else {
		output->push_back(anotherdatanum);
	}
	for(i = 0; i < anotherdatanum; i++) {
		colorWriter(output, pixels[position + i]);
	}
}

#ifdef DECOMPRESS_CHECK
//��(8bpp)
static int decompress_rle2_8bpp(vector<unsigned char> *input, vector<unsigned char> *output, int width, int height)
{
	int i, size, cnt;
	unsigned char tmp;
	
	size = input->size();
	
	for(i = 0; i < size; i++ ){
		tmp = input->at(i);
		//�𓀏���
		if(tmp > SAMELINE_DATA){
			//�A���f�[�^
			if(tmp == CONTINUITY_2B_DATA){
				//�A���f�[�^(2byte)
				decompress_data_continuity_2byte_8bpp(i, input, output);
				i += 3;
			} else {
				//�A���f�[�^(1byte)
				decompress_data_continuity_1byte_8bpp(i, input, output);
				i++;
			}
		} else if(tmp == SAMELINE_DATA) {
			//����s�f�[�^
			if(input->at(i + 1) == SAMELINE_2B_DATA){
				decompress_data_sameline_2byte_8bpp(i, input, output, width);
				i += 3;
			} else {
				decompress_data_sameline_1byte_8bpp(i, input, output, width);
				i += 1;
			}
		} else {
			//��A���f�[�^
			if(tmp == DISCONTINUITY_2B_DATA){
				//��A���f�[�^(2byte)
				cnt = decompress_data_discontinuity_2byte_8bpp(i, input, output);
				i+= 2 + cnt;
			} else {
				//��A���f�[�^(1byte)
				cnt = decompress_data_discontinuity_1byte_8bpp(i, input, output);
				i+= cnt;
			}
		}
	}
	return 0;
}

//��(32bpp)
static int decompress_rle2_32bpp(vector<unsigned char> *input, vector<unsigned long> *output, int width, int height)
{
	int i, size, cnt;
	unsigned long tmp;
	
	size = input->size();
	
	for(i = 0; i < size; i++ ){
		tmp = input->at(i);
		//�𓀏���
		if(tmp > SAMELINE_DATA){
			//�A���f�[�^
			if(tmp == CONTINUITY_2B_DATA){
				//�A���f�[�^(2byte)
				decompress_data_continuity_2byte_32bpp(i, input, output);
				i += 6;
			} else {
				//�A���f�[�^(1byte)
				decompress_data_continuity_1byte_32bpp(i, input, output);
				i += 4;
			}
		} else if(tmp == SAMELINE_DATA) {
			//����s�f�[�^
			if(input->at(i + 1) == SAMELINE_2B_DATA){
				decompress_data_sameline_2byte_32bpp(i, input, output, width);
				i += 3;
			} else {
				decompress_data_sameline_1byte_32bpp(i, input, output, width);
				i += 1;
			}
		} else {
			//��A���f�[�^
			if(tmp == DISCONTINUITY_2B_DATA){
				//��A���f�[�^(2byte)
				cnt = decompress_data_discontinuity_2byte_32bpp(i, input, output);
				i+= 2 + cnt;
			} else {
				//��A���f�[�^(1byte)
				cnt = decompress_data_discontinuity_1byte_32bpp(i, input, output);
				i+= cnt;
			}
		}
	}
	return 0;
}

//����s�f�[�^�̉�(8bpp 1byte)
static void decompress_data_sameline_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output, int width)
{
	int i, cnt, point;
	unsigned char data;

	cnt = input->at(num + 1);
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//����s�f�[�^�̉�(32bpp 1byte)
static void decompress_data_sameline_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output, int width)
{
	int i, cnt, point;
	unsigned long data;
	
	cnt = input->at(num + 1);
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//����s�f�[�^�̉�(8bpp 2byte)
static void decompress_data_sameline_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output, int width)
{
	int i, cnt, point, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 3) << 8) & 0xFF00;	//���
	tmp2 = input->at(num + 2) & 0x00FF;	//����
	cnt = (tmp1 | tmp2) + MAXSAMELINE_1B_LENGTH + 1;
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//����s�f�[�^�̉�(32bpp 2byte)
static void decompress_data_sameline_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output, int width)
{
	int i, cnt, point, tmp1,tmp2;
	unsigned long data;
	
	tmp1 = (input->at(num + 3) << 8) & 0xFF00;	//���
	tmp2 = input->at(num + 2) & 0x00FF;	//����
	cnt = (tmp1 | tmp2) + MAXSAMELINE_1B_LENGTH + 1;
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//�A���f�[�^�̉�(8bpp 1byte)
static void decompress_data_continuity_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt;
	unsigned char data;
	
	cnt = input->at(num) & 0x7F;
	data = input->at(num + 1);
	for(i = 0; i < cnt; i++){
		output->push_back(data);
	}
}

//�A���f�[�^�̉�(32bpp 1byte)
static void decompress_data_continuity_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt;
	IMGCOLOR data;
	
	cnt =    ((input->at(num)) & 0x7F);
	data.a = (input->at(num + 1 ));
	data.b = (input->at(num + 2 ));
	data.g = (input->at(num + 3 ));
	data.r = (input->at(num + 4 ));
	for(i = 0; i < cnt; i++){
		output->push_back(data.n);
	}
}

//�A���f�[�^�̉�(8bpp 2byte)
static void decompress_data_continuity_2byte_8bpp (int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//���
	tmp2 =  input->at(num + 1) & 0x00FF;	    //����
	cnt  = (tmp1 | tmp2) + MAXCONTINUITY_1B_LENGTH + 1;
	data = input->at(num + 3);

	for(i = 0; i < cnt; i++){
		output->push_back(data);
	}
}

//�A���f�[�^�̉�(32bpp 2byte)
static void decompress_data_continuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt, tmp1,tmp2;
	IMGCOLOR data;
	
	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//���
	tmp2 =  input->at(num + 1) & 0x00FF;	    //����
	cnt  = (tmp1 | tmp2) + MAXCONTINUITY_1B_LENGTH + 1;
	data.a = (input->at(num + 3 ));
	data.b = (input->at(num + 4 ));
	data.g = (input->at(num + 5 ));
	data.r = (input->at(num + 6 ));

	for(i = 0; i < cnt; i++){
		output->push_back(data.n);
	}
}

//��A���f�[�^�̉�(8bpp 1byte)
static int decompress_data_discontinuity_1byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt;
	unsigned char data;

	cnt = input->at(num);
	for(i = 0; i < cnt; i++){
		data = input->at(num + 1 + i);
		output->push_back(data);
	}
	return cnt;
}

//��A���f�[�^�̉�(32bpp 1byte)
static int decompress_data_discontinuity_1byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt;
	IMGCOLOR data;

	cnt = input->at(num);
	for(i = 0; i < cnt; i++){
		data.a = (input->at(num + 1 + (i * 4)));
		data.b = (input->at(num + 2 + (i * 4)));
		data.g = (input->at(num + 3 + (i * 4)));
		data.r = (input->at(num + 4 + (i * 4)));
		output->push_back(data.n);
	}
	return (cnt * 4);
}
	
//��A���f�[�^�̉�(8bpp 2byte)
static int decompress_data_discontinuity_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//���
	tmp2 = input->at(num + 1) & 0x00FF;	//����
	cnt  = (tmp1 | tmp2) + MAXDISCONTINUITY_1B_LENGTH + 1;
	for(i = 0; i < cnt; i++){
		data = input->at(num + 3 + i);
		output->push_back(data);
	}
	return cnt;
}
	
//��A���f�[�^�̉�(32bpp 2byte)
static int decompress_data_discontinuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt, tmp1,tmp2;
	IMGCOLOR data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//���
	tmp2 = input->at(num + 1) & 0x00FF;	//����
	cnt  = (tmp1 | tmp2) + MAXDISCONTINUITY_1B_LENGTH + 1;
	for(i = 0; i < cnt; i++){
		data.a = (input->at(num + 3 + (i * 4)));
		data.b = (input->at(num + 4 + (i * 4)));
		data.g = (input->at(num + 5 + (i * 4)));
		data.r = (input->at(num + 6 + (i * 4)));
		output->push_back(data.n);
	}
	return (cnt * 4);
}
#endif


#ifdef DECOMPRESS_CHECK
//���k�O�ƈ��k�ˉ𓀌�̃f�[�^���r
static int checkdata_8bpp(IMGCOLOR *before_data, int before_datasize, vector<unsigned char> *after_data)
{
	int i;

	//�T�C�Y�`�F�b�N
	if (after_data->size() != before_datasize) {
		return -1;
	}

	//��r
	for (i = 0; i < before_datasize; i++) {
		if (before_data[i].n != after_data->at(i)) {
			return -1;
		}
	}

	//OK
	return 0;
}

	
static int checkdata_32bpp(IMGCOLOR *before_data, int before_datasize, vector<unsigned long> *after_data)
{
	int i;

	//�T�C�Y�`�F�b�N
	if (after_data->size() != before_datasize) {
		return -1;
	}

	//��r
	for (i = 0; i < before_datasize; i++) {
		if (before_data[i].n != after_data->at(i)) {
			return -1;
		}
	}

	//OK
	return 0;
}
#endif

static void output_header(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;

	if (hireso) {
		width /= 2;
		height /= 2;
	}

	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const unsigned char pc%s[];\n", id);
	fprintf (fp, "/* Header */\n");
	
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI%s={%s,%d,%d,0,pc%s};\n",
					id, type, width, height, id);
	fprintf(fp, "\n");
}

static void output_header_index(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;
	if (hireso) {
		width /= 2;
		height /= 2;
	}
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const unsigned char pc%s[];\n", id);
	fprintf (fp, "/* Header */\n");
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI%s={%s,%d,%d,0,pc%s};\n",
					id, type, width, height, id);
	fprintf(fp, "\n");

}

static void output_header_pal(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, int palette_num, FILE *fp)
{
	int width = img->width;
	int height = img->height;
	if (hireso) {
		width /= 2;
		height /= 2;
	}
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const unsigned char pcPLT_%s[];\n", id);
	fprintf (fp, "extern const unsigned char pc%s[];\n", id);
	fprintf (fp, "/* Header */\n");

	fprintf (fp, "const GDI_IMAGE_BITMAP_PLT GDI%s={%s,%d,%d,0,pc%s,pcPLT_%s,%d};\n",
				id, type, width, height, id, id, palette_num);
	fprintf(fp, "\n");
}

static void output_header_32bpp(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, bool hireso, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;
	if (hireso) {
		width /= 2;
		height /= 2;
	}
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const unsigned char pc%s[];\n", id);
	fprintf (fp, "/* Header */\n");
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI%s={%s,%d,%d,0,pc%s};\n",
				id, type, width, height, id);
	fprintf(fp, "\n");
}

static void output_endmarker(const char *id, int flag, FILE *fp)
{
	fprintf (fp, "/* End Marker */\n");
	fprintf (fp, "IMAGE_MARKER(%s);\n", id);
}

static IMAGE *convert_to_8bpp(IMAGE *img)
{
	ImgGetPixel *getter;
	IMAGE	*img8bpp;

	getter = img_get_pixelfunc(img);

	img8bpp = (IMAGE*)malloc(sizeof(IMAGE));
	img_init(img8bpp);

	/* �摜���ݒ� */
	img8bpp->width = img->width;
	img8bpp->height = img->height;
	img8bpp->stride = 0;
	img8bpp->pixel_depth = 8;
	img8bpp->pixel_bytes = 1;
	img8bpp->buf = (unsigned char*)malloc(img->width * img->height);
	img8bpp->palette = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * 256);
	img8bpp->palette_premultiplied = true;	//�摜��premultiply����Ă���̂ō쐬�ł���p���b�g��premultiply�����

	/* �p���b�g���쐬���ϊ� */
	unsigned char	*dst = img8bpp->buf;
	int	count = img8bpp->width * img8bpp->height;
	int palnum = 0;
	int i, j;
	IMGCOLOR col;

	for (i = 0; i < count; i++) {
		col = getter->get();
		/* �p���b�g���� */
		for (j = 0; j < palnum; j++) {
			if (img8bpp->palette[j].n == col.n) {
				break;
			}
		}
		if (j == palnum) {
			/* ���ł�256����ꍇ�̓G���[���� */
			if (palnum == 256) {
				goto error;
			}
			/* �p���b�g�ɒǉ� */
			img8bpp->palette[palnum].n = col.n;
			palnum++;
		}
		/* �p���b�g�ԍ����f�[�^�ɒǉ� */
		*dst++ = j;
	}
	/* �p���b�g���ݒ� */
	img8bpp->palette_num = palnum;
	/* getter�폜 */
	delete getter;

	return img8bpp;
error:
	img_free(img8bpp);
	free(img8bpp);
	delete getter;

	return NULL;
}
