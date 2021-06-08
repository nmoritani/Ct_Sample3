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

static int output_1bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, FILE *fp, OUTPUT_TYPE type);
static int output_8bpp(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp);
static int output_8bpp_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp);
static int output_8bpp_rle(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp);
static int output_8bpp_rle_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp);
static int output_16bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, int buf_width, int buf_height, FILE *fp);
static int output_32bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, int buf_width, int buf_height, FILE *fp);
static int output_32bpp_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, FILE *fp);
static int make_near_color_palette_map(IMGCOLOR *palette, int palette_num, IMGCOLOR *refpal, int refpal_num, unsigned char *map);
static unsigned char find_near_color(IMGCOLOR *palette, int palette_num, IMGCOLOR col);
static unsigned char find_near_color_cache(COLMATCHCACHE *cache, IMGCOLOR *palette, int palette_num, IMGCOLOR col);

/* バッファ出力 */
static void output_vector(vector<unsigned char> *buffer, int column, int align, const char *id, int flag, FILE *fp);
static void output_imgbuf(unsigned char *buffer, int size, int column, int stride, int flag, FILE *fp);
static void output_palette(IMGCOLOR *palette, int num, bool premultiplied, const char *id, int flag, FILE *fp);
static void output_offsetvector(vector<unsigned long> *offset, vector<unsigned char> *buffer, int column, const char *id, int flag, FILE *fp);
static void output_header(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp);
static void output_header_index(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp);
static void output_header_32bpp(IMAGE *img, int align_width, int align_height, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp);
static void output_endmarker(const char *id, int flag, FILE *fp);

/* ランレングス関連 */
#define MAXRUNLENGTH_RLE		0x7F	//連続データの最大数
#define EOL							0x00										//行の終端

//データチェック
#ifdef _DEBUG
 #define DECOMPRESS_CHECK
#endif

/* ランレングス２関連 */

/****
 RLE2データ形式
 0x00						未使用
 0x01～0x7E,AA,BB,CC...		非連続データが(0x01～0x7E)個続く
 0x7F,NL,NH,AA,BB,CC...		非連続データが(((NH<<8)+NL)+0x7F)個続く
 0x80,0x01～0xFE			前行と同一のデータが(0x01～0xFE)個続く
 0x80,0xFF,NL,NH			前行と同一のデータが(((NH<<8)+NL)+0xFF)個続く
 0x81～0xFE,XX				連続データXXが(0x01～0x7E)個続く
 0xFF,NL,NH,XX				連続データXXが(((NH<<8)+NL)+0x7F)個続く
 ****/

#define DISCONTINUITY_2B_DATA		0x7F										//非連続データ(2Byte)
#define MAXDISCONTINUITY_1B_LENGTH	0x7E										//非連続データ最大数(1Byte)
#define MAXDISCONTINUITY_2B_LENGTH	((MAXDISCONTINUITY_1B_LENGTH + 1) + 0xFFFF)	//非連続データ最大数(2Byte)

#define SAMELINE_DATA				0x80										//同一行データ
#define SAMELINE_2B_DATA			0xFF										//同一行データ(2byte)
#define MAXSAMELINE_1B_LENGTH		0xFE										//同一行データ最大数(1Byte)
#define MAXSAMELINE_2B_LENGTH		((MAXSAMELINE_1B_LENGTH + 1) + 0xFFFF)			//同一行データ最大数(2Byte)

#define CONTINUITY_DATA_FLAG		0x80										//連続データフラグ
#define CONTINUITY_2B_DATA			0xFF										//連続データ(2Byte)
#define MAXCONTINUITY_1B_LENGTH		0x7E										//連続データサイズ(1Byte)
#define MAXCONTINUITY_2B_LENGTH		((MAXCONTINUITY_1B_LENGTH + 1) + 0xFFFF)		//連続データサイズ(2Byte)

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
/* イメージ変換　*/
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

//チェック
static int checkdata_8bpp(IMGCOLOR *b_data, int b_datasize, vector<unsigned char> *a_data);
static int checkdata_32bpp(IMGCOLOR *b_data, int b_datasize, vector<unsigned long> *a_data);

/*
 bmpload/pngloadで解析したイメージデータをC言語形式で出力する
 */
int output_bmpdata(IMAGE *img, IMGCOLOR *color_plt, const char *id, OUTPUT_TYPE type, int flag, int align_width, int align_height, FILE *fp)
{
	int ret;
	ImgGetPixel *getter;

	getter = img_get_pixelfunc(img);
	if (getter == NULL) {
		return -1;
	}

	//出力形式にあわせて関数を呼び出す
	switch (type) {
	case OUTPUT_TYPE_1BPP:
		ret = output_1bpp(img, id, getter, flag, fp, type);
		break;
	case OUTPUT_TYPE_8BPP:
		ret = output_8bpp(img, color_plt, id, getter, flag, fp);
		break;
	case OUTPUT_TYPE_8BPP_RLE:
		ret = output_8bpp_rle(img, color_plt, id, getter, flag, fp);
		break;
	case OUTPUT_TYPE_16BPP:
		ret = output_16bpp(img, id, getter, flag, align_width, align_height, fp);
        break;
	case OUTPUT_TYPE_32BPP:
		ret = output_32bpp(img, id, getter, flag, align_width, align_height, fp);
		break;
	case OUTPUT_TYPE_32BPP_RLE2:
		ret = output_32bpp_rle2(img, id, getter, flag, fp);
		break;
	default:
		ret = -2;
		break;
	}

	delete getter;

	return ret;
}

static int output_1bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, FILE *fp, OUTPUT_TYPE type)
{
	int width;
	int height;
	int i, j, bit;
	unsigned dat;
	vector<unsigned char> buf;
	IMGCOLOR col;
	IMGCOLOR black;

	//黒色を黒にする
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;

	//データをバッファに作成
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		bit = 0x80;
		dat = 0;
		for (j = 0; j < width; j++) {
			col = getter->getRGBA();
			//黒とする色を１とする
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
		//あまりがあれば出力
		if (bit != 0x80) {
			buf.push_back(dat);
		}
	}

	//ヘッダデータをファイルに出力
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_1BPP_TRANS", flag, fp);

	//バッファのデータをファイルに出力
	output_vector(&buf, (width + 7) / 8, 0, id, flag, fp);

	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp)
{
	int width;
	int height;
	int i, j;
	vector<unsigned char>	buf;

	if(color_plt != NULL){
		output_8bpp_plt(img, color_plt, id, getter, flag, fp);
		return 0;
	}

	//パレットなし(8bppを超える）は変換できない
	if (img->pixel_depth > 8) {
		return -3;
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back((unsigned char)getter->get().n);
		}
	}

	//ヘッダデータをファイルに出力
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_TRANS", flag, fp);

	//バッファのデータをファイルに出力
	output_vector(&buf, width, 0, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp)
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
		//パレット変換
		make_near_color_palette_map(img->palette, img->palette_num, color_plt, 256, map);
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (img->pixel_depth > 8) {
				//RGBA変換
				buf.push_back((unsigned long)find_near_color_cache(&cache, color_plt, 256, getter->get()));
			}else{
				//パレット変換
				buf.push_back(map[getter->get().n]);
			}
		}
	}
	//ヘッダデータをファイルに出力
	output_header(img, buf.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_TRANS", flag, fp);

	//バッファのデータをファイルに出力
	output_vector(&buf, width, 0, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_rle(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp)
{
	int width;
	int height;
	int i;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;
	vector<unsigned long>	offset;

	if(color_plt != NULL){
		output_8bpp_rle_plt(img, color_plt, id, getter, flag, fp);
		return 0;
	}

	//パレットなし(8bppを超える）は変換できない
	if (img->pixel_depth > 8) {
		return -3;
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;

	//行単位で圧縮(GEN形式)
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

	//ヘッダデータをファイルに出力
	output_header_index(img, buf.size()+height+offset.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_RLE_TRANS", flag, fp);

	//バッファのデータをファイルに出力
	output_offsetvector(&offset, &buf, 32, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_8bpp_rle_plt(IMAGE *img, IMGCOLOR *color_plt, const char *id, ImgGetPixel *getter, int flag, FILE *fp)
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
		//パレット変換
		make_near_color_palette_map(img->palette, img->palette_num, color_plt, 256, map);
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;

	//行単位で圧縮(GEN形式)
	for (i = 0; i < height; i++) {
		offset.push_back(buf.size()+(height*2));
		pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width);
		for (j = 0; j < width; j++) {
			if (img->pixel_depth > 8) {
				//RGBA変換
				pixels[j].n = (unsigned long)find_near_color_cache(&cache, color_plt, 256, getter->get());
			}else{
				//パレット変換
				pixels[j].n = map[getter->get().n];
			}
		}
		compress_rle(&buf, pixels, width, &color_writer_8bpp, NULL);
		buf.push_back(EOL);
	}
	//ヘッダデータをファイルに出力
	output_header_index(img, buf.size()+height+offset.size(), 8, id, "GDI_IMAGE_TYPE_8BPP_RLE_TRANS", flag, fp);

	//バッファのデータをファイルに出力
	output_offsetvector(&offset, &buf, 32, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);
	return 0;
}

static int make_near_color_palette_map(IMGCOLOR *palette, int palette_num, IMGCOLOR *refpal, int refpal_num, unsigned char *map)
{
	int i;

	/* パレット番号の変換テーブルを作成 */
	for (i = 0; i < palette_num; i++) {
		/* 同じ番号の色を優先する */
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

	/* 近似色を探す */
	for (i = 0; i < palette_num; i++) {
		/* 距離を計算 */
		dr = palette[i].r - col.r;
		dg = palette[i].g - col.g;
		db = palette[i].b - col.b;
		da = palette[i].a - col.a;
		distance = ((dr * dr + dg * dg + db * db) << 8) + abs(da);
		if (distance < min_distance) {
			/* 距離が最も近い番号を保存 */
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

	/* キャッシュから探す */
	cache_size = cache->table.size();
	for (i = 0; i < cache_size; i++) {
		if (cache->table.at(i).col.n == col.n) {
			return cache->table.at(i).index;
		}
	}
	/* パレットから検索 */
	index = find_near_color(palette, palette_num, col);
	/* キャッシュに登録 */
	data.col = col;
	data.index = index;
	cache->table.push_back(data);

	return index;
}


static int output_32bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, int align_width, int align_height, FILE *fp)
{
	int width, padding, padding_height;
	int height;
	int i, j;
	IMGCOLOR col;
	double lr, lg, lb, la;
	vector<unsigned char>	buf;

	//パレットありは変換できない
	if (img->pixel_depth < 16) {
		return -3;
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;
	if (align_width == 0 || ((img->width * 4) % align_width) == 0) {
		padding = 0;
	} else {
		padding = align_width -((img->width * 4) % align_width);
	}

	if (align_height == 0 || (img->height % align_height) == 0) {
		padding_height = 0;
	} else {
		padding_height = align_height - (img->height % align_height);
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = getter->get();
			if (col.a == 0) {
				buf.push_back(0);
				buf.push_back(0);
				buf.push_back(0);
				buf.push_back(0);
			} else {
				lr = col.r / 255.0;
				lg = col.g / 255.0;
				lb = col.b / 255.0;
				la = col.a / 255.0;
				
				lr = lr * la;
				lg = lg * la;
				lb = lb * la;
				buf.push_back((short)(lb * 255));
				buf.push_back((short)(lg * 255));
				buf.push_back((short)(lr * 255));
				buf.push_back(col.a);
			}
		}
		if (padding) {
			for (j = 0; j < padding; j++) {
				buf.push_back(0);
			}
		}
	}

	for (i = 0; i < padding_height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back(0);
			buf.push_back(0);
			buf.push_back(0);
			buf.push_back(0);
		}
		if (padding) {
			for (j = 0; j < padding; j++) {
				buf.push_back(0);
			}
		}
	}
	//ヘッダデータをファイルに出力
	output_header_32bpp(img, (img->width*4)+padding, img->height+padding_height, 0, 32, id, "GDI_IMAGE_TYPE_32BPP", flag, fp);	//これまで０で出力していたのであわせる

	//バッファのデータをファイルに出力
	output_vector(&buf, (width * 4), padding, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_32bpp_rle2(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, FILE *fp)
{
	int width;
	int height;
	int j;
	IMGCOLOR	*pixels = NULL;
	vector<unsigned char>	buf;

	//パレットありは変換できない
	if (img->pixel_depth < 16) {
		return -3;
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;

	pixels = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * width * height);
	for (j = 0; j < width * height; j++) {
		pixels[j] = getter->get();
	}
	//全データを圧縮
	compress_rle2(&buf, pixels, width , height, &color_writer_32bpp, NULL, DATA_32BPP);

#ifdef DECOMPRESS_CHECK
	int ret;
	vector<unsigned long>	decompress_buf;	//解凍後データ
	//データ解凍
	decompress_rle2_32bpp(&buf, &decompress_buf, width, height);
	//解凍データチェック
	ret = checkdata_32bpp(pixels, width * height, &decompress_buf);
	if (ret != 0) {
		free(pixels);
		return -5;
	}
#endif

	if(pixels != NULL){
		free(pixels);
	}
	//ヘッダデータをファイルに出力
	output_header_32bpp(img, img->width*4, img->height, 0, 32, id, "GDI_IMAGE_TYPE_32BPP_RLE2", flag, fp);	//これまで０で出力していたのであわせる

	//バッファのデータをファイルに出力
	output_vector(&buf, 32, 0, id, flag, fp);

	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static int output_16bpp(IMAGE *img, const char *id, ImgGetPixel *getter, int flag, int align_width, int align_height, FILE *fp)
{
	int width, padding, padding_height;
	int height;
	int i, j;
	double lr, lg, lb, la;
	short ba, rg;
	IMGCOLOR col;
	vector<unsigned char>	buf;

	//パレットありは変換できない
	if (img->pixel_depth < 16) {
		return -3;
	}

	//データをバッファに作成
	width = img->width;
	height = img->height;
	if (align_width == 0 || ((img->width * 2) % align_width) == 0) {
		padding = 0;
	} else {
		padding = align_width -((img->width * 2) % align_width);
	}
	if (align_height == 0 || (img->height % align_height == 0)) {
		padding_height = 0;
	} else {
		padding_height = align_height - (img->height % align_height);
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			col = getter->get();
			if (col.a == 0) {
				buf.push_back(0);
				buf.push_back(0);
			} else {
				lr = col.r / 255.0;
				lg = col.g / 255.0;
				lb = col.b / 255.0;
				la = col.a / 255.0;

				lr = lr * la;
				lg = lg * la;
				lb = lb * la;
			
#if 1
				ba = (((short)(lb * 255)) & 0xf0) + (((col.a) & 0xf0) >> 4);
				rg = (((short)(lr * 255)) & 0xf0) + ((((short)(lg * 255)) & 0xf0) >> 4);
#else
				ab = (((short)((lb * 15))) << 4) + (short)(la * 15);
				gr = (((short)((lr * 15))) << 4) + (short)(lg * 15);
#endif
				buf.push_back(ba);
				buf.push_back(rg);
			}
		}
		for (j = 0; j < padding; j++) {
			buf.push_back(0);
		}
	}

	for (i = 0; i < padding_height; i++) {
		for (j = 0; j < width; j++) {
			buf.push_back(0);
			buf.push_back(0);
		}
		if (padding) {
			for (j = 0; j < padding; j++) {
				buf.push_back(0);
			}
		}
	}

	//ヘッダデータをファイルに出力
	output_header_32bpp(img, (img->width*2)+padding, img->height+padding_height, 0, 32, id, "GDI_IMAGE_TYPE_16BPP", flag, fp);	//これまで０で出力していたのであわせる
	
	//バッファのデータをファイルに出力
	output_vector(&buf, (width * 2), padding, id, flag, fp);
	
	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}


/* バッファ出力 */
static void output_vector(vector<unsigned char> *buffer, int column, int padding, const char *id, int flag, FILE *fp)
{
	int size = buffer->size();
	int i, n;

	fprintf(fp, "static const unsigned char data_%s[] __rodata_imagedata ={\n", id);

	n = 0;
	for (i = 0; i < size; i++) {
		if (n == column) {
			fprintf(fp, "  ");
		}
		if (n >= column + padding) {
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

	fprintf(fp, "static const unsigned char dataPLT_%s[] __rodata_imagedata ={\n", id);

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

	fprintf(fp, "static const unsigned char data_%s[] __rodata_imagedata ={\n", id);

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

/* ランレングス圧縮関数 */
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
		//使用されている最大のピクセル値を見つける（パレット番号の最大値を見つけるのに使用する）
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
		//連続数
		prevcol.n = pixels[i].n;
		runlength = 1;
		while (i + runlength < count && runlength < MAXRUNLENGTH_RLE) {
			if (pixels[i + runlength].n != prevcol.n) {
				break;
			}
			runlength++;
		}
		//非連続データ処理
		if(anotherdatanum > 0){
			if ((runlength >= 2) || (anotherdatanum == MAXRUNLENGTH_RLE) ) {
				//非連続データ数書き込み
				output->push_back(anotherdatanum);
				//非連続データ書き込み
				for(j = 0; j < anotherdatanum; j++) {
					colorWriter(output, pixels[position + j]);
				}
				//カウントクリア
				anotherdatanum = 0;
				position = 0;
			}
		}

		if (runlength >= 2) {
			//連続データ書き込み(CONTINUITY_DATA_FLAG + runlength, data)
			output->push_back(CONTINUITY_DATA_FLAG + runlength);
			colorWriter(output, prevcol);
			i += runlength;
		} else {
			//連続数が1なら非連続データ数を数える
			if(anotherdatanum == 0){
				position = i;
			}
			anotherdatanum++;
			i++;
		}
	}

	//非連続データ処理
	if(anotherdatanum > 0){
		//非連続データ数書き込み
		output->push_back(anotherdatanum);
		//非連続データ書き込み
		for(j = 0; j < anotherdatanum; j++) {
			colorWriter(output, pixels[position + j]);
		}
		//カウントクリア
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

	//連続データ、同一行データの圧縮最小個数を設定
	if(bpptype == DATA_8BPP){
		min_runlength  = MIN_RUNLENGTH_8BPP;
		min_samelength = MIN_SAMELENGTH_8BPP;
	} else {
		min_runlength  = MIN_RUNLENGTH_32BPP;
		min_samelength = MIN_SAMELENGTH_32BPP;
	}

	if (max_value != NULL) {
		unsigned long	max;
		//使用されている最大のピクセル値を見つける（パレット番号の最大値を見つけるのに使用する）
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
		//連続数
		while ((i + runlength < count) && (runlength < MAXCONTINUITY_2B_LENGTH)) {
			if (pixels[i + runlength].n != prevcol.n) {
				break;
			}
			runlength++;
		}
		//連続行
		if(i > width){
			while ((i + samelength < count) && (samelength < MAXSAMELINE_2B_LENGTH)) {
				if (pixels[i + samelength].n != pixels[i + samelength - width].n) {
					break;
				}
				samelength++;
			}
		}
		//非連続データ処理
		if(anotherdatanum > 0){
			if ((runlength >= min_runlength) || (samelength >= min_samelength) || (anotherdatanum == MAXDISCONTINUITY_2B_LENGTH) ) {
				compress_data_discontinuity_rle2(output, pixels, colorWriter, anotherdatanum, position);
				anotherdatanum = 0;
				position = 0;
			}
		}
		
		if (runlength >= min_runlength && (runlength > samelength)) {
			//連続データの書き込み
			if(runlength > MAXCONTINUITY_1B_LENGTH) {
				//連続データ書き込み(0xFF,runlength(2byte),data)
				output->push_back(CONTINUITY_2B_DATA);
				extralength = runlength - (MAXCONTINUITY_1B_LENGTH + 1);
				tmp = (unsigned char)(extralength & 0xFF);
				output->push_back(tmp);
				tmp = (unsigned char)((extralength >> 8) & 0xFF);
				output->push_back(tmp);
				colorWriter(output, prevcol);
			} else {
				//連続データ書き込み(CONTINUITY_DATA_FLAG + runlength, data)
				output->push_back(CONTINUITY_DATA_FLAG + runlength);
				colorWriter(output, prevcol);
			}
			i += runlength;
			
		} else if(samelength >= min_samelength){
			//同一行データの書き込み(SAMELINE_DATA, samelength)
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
			//連続数が1なら非連続データ数を数える
			if(anotherdatanum == 0){
				position = i;
			}
			anotherdatanum++;
			i++;
		}
	}
	//非連続データ処理
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
//解凍(8bpp)
static int decompress_rle2_8bpp(vector<unsigned char> *input, vector<unsigned char> *output, int width, int height)
{
	int i, size, cnt;
	unsigned char tmp;
	
	size = input->size();
	
	for(i = 0; i < size; i++ ){
		tmp = input->at(i);
		//解凍処理
		if(tmp > SAMELINE_DATA){
			//連続データ
			if(tmp == CONTINUITY_2B_DATA){
				//連続データ(2byte)
				decompress_data_continuity_2byte_8bpp(i, input, output);
				i += 3;
			} else {
				//連続データ(1byte)
				decompress_data_continuity_1byte_8bpp(i, input, output);
				i++;
			}
		} else if(tmp == SAMELINE_DATA) {
			//同一行データ
			if(input->at(i + 1) == SAMELINE_2B_DATA){
				decompress_data_sameline_2byte_8bpp(i, input, output, width);
				i += 3;
			} else {
				decompress_data_sameline_1byte_8bpp(i, input, output, width);
				i += 1;
			}
		} else {
			//非連続データ
			if(tmp == DISCONTINUITY_2B_DATA){
				//非連続データ(2byte)
				cnt = decompress_data_discontinuity_2byte_8bpp(i, input, output);
				i+= 2 + cnt;
			} else {
				//非連続データ(1byte)
				cnt = decompress_data_discontinuity_1byte_8bpp(i, input, output);
				i+= cnt;
			}
		}
	}
	return 0;
}

//解凍(32bpp)
static int decompress_rle2_32bpp(vector<unsigned char> *input, vector<unsigned long> *output, int width, int height)
{
	int i, size, cnt;
	unsigned long tmp;
	
	size = input->size();
	
	for(i = 0; i < size; i++ ){
		tmp = input->at(i);
		//解凍処理
		if(tmp > SAMELINE_DATA){
			//連続データ
			if(tmp == CONTINUITY_2B_DATA){
				//連続データ(2byte)
				decompress_data_continuity_2byte_32bpp(i, input, output);
				i += 6;
			} else {
				//連続データ(1byte)
				decompress_data_continuity_1byte_32bpp(i, input, output);
				i += 4;
			}
		} else if(tmp == SAMELINE_DATA) {
			//同一行データ
			if(input->at(i + 1) == SAMELINE_2B_DATA){
				decompress_data_sameline_2byte_32bpp(i, input, output, width);
				i += 3;
			} else {
				decompress_data_sameline_1byte_32bpp(i, input, output, width);
				i += 1;
			}
		} else {
			//非連続データ
			if(tmp == DISCONTINUITY_2B_DATA){
				//非連続データ(2byte)
				cnt = decompress_data_discontinuity_2byte_32bpp(i, input, output);
				i+= 2 + cnt;
			} else {
				//非連続データ(1byte)
				cnt = decompress_data_discontinuity_1byte_32bpp(i, input, output);
				i+= cnt;
			}
		}
	}
	return 0;
}

//同一行データの解凍(8bpp 1byte)
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

//同一行データの解凍(32bpp 1byte)
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

//同一行データの解凍(8bpp 2byte)
static void decompress_data_sameline_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output, int width)
{
	int i, cnt, point, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 3) << 8) & 0xFF00;	//上位
	tmp2 = input->at(num + 2) & 0x00FF;	//下位
	cnt = (tmp1 | tmp2) + MAXSAMELINE_1B_LENGTH + 1;
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//同一行データの解凍(32bpp 2byte)
static void decompress_data_sameline_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output, int width)
{
	int i, cnt, point, tmp1,tmp2;
	unsigned long data;
	
	tmp1 = (input->at(num + 3) << 8) & 0xFF00;	//上位
	tmp2 = input->at(num + 2) & 0x00FF;	//下位
	cnt = (tmp1 | tmp2) + MAXSAMELINE_1B_LENGTH + 1;
	point = output->size() - width;

	for(i = 0; i < cnt; i++){
		data = output->at(point + i);
		output->push_back(data);
	}
}

//連続データの解凍(8bpp 1byte)
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

//連続データの解凍(32bpp 1byte)
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

//連続データの解凍(8bpp 2byte)
static void decompress_data_continuity_2byte_8bpp (int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//上位
	tmp2 =  input->at(num + 1) & 0x00FF;	    //下位
	cnt  = (tmp1 | tmp2) + MAXCONTINUITY_1B_LENGTH + 1;
	data = input->at(num + 3);

	for(i = 0; i < cnt; i++){
		output->push_back(data);
	}
}

//連続データの解凍(32bpp 2byte)
static void decompress_data_continuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt, tmp1,tmp2;
	IMGCOLOR data;
	
	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//上位
	tmp2 =  input->at(num + 1) & 0x00FF;	    //下位
	cnt  = (tmp1 | tmp2) + MAXCONTINUITY_1B_LENGTH + 1;
	data.a = (input->at(num + 3 ));
	data.b = (input->at(num + 4 ));
	data.g = (input->at(num + 5 ));
	data.r = (input->at(num + 6 ));

	for(i = 0; i < cnt; i++){
		output->push_back(data.n);
	}
}

//非連続データの解凍(8bpp 1byte)
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

//非連続データの解凍(32bpp 1byte)
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
	
//非連続データの解凍(8bpp 2byte)
static int decompress_data_discontinuity_2byte_8bpp(int num, vector<unsigned char> *input, vector<unsigned char> *output)
{
	int i, cnt, tmp1,tmp2;
	unsigned char data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//上位
	tmp2 = input->at(num + 1) & 0x00FF;	//下位
	cnt  = (tmp1 | tmp2) + MAXDISCONTINUITY_1B_LENGTH + 1;
	for(i = 0; i < cnt; i++){
		data = input->at(num + 3 + i);
		output->push_back(data);
	}
	return cnt;
}
	
//非連続データの解凍(32bpp 2byte)
static int decompress_data_discontinuity_2byte_32bpp(int num, vector<unsigned char> *input, vector<unsigned long> *output)
{
	int i, cnt, tmp1,tmp2;
	IMGCOLOR data;

	tmp1 = (input->at(num + 2) << 8) & 0xFF00;	//上位
	tmp2 = input->at(num + 1) & 0x00FF;	//下位
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
//圧縮前と圧縮⇒解凍後のデータを比較
static int checkdata_8bpp(IMGCOLOR *before_data, int before_datasize, vector<unsigned char> *after_data)
{
	int i;

	//サイズチェック
	if (after_data->size() != before_datasize) {
		return -1;
	}

	//比較
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

	//サイズチェック
	if (after_data->size() != before_datasize) {
		return -1;
	}

	//比較
	for (i = 0; i < before_datasize; i++) {
		if (before_data[i].n != after_data->at(i)) {
			return -1;
		}
	}

	//OK
	return 0;
}
#endif

static void output_header(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;

	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const GDI_IMAGE_BITMAP GDI_IMAGE_%s;\n", id);
	
	fprintf (fp, "/* Header */\n");
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI_IMAGE_%s __rodata_imagedata ={%s, %d,%d,0,data_%s};\n",
					id, type, width, height, id);
	fprintf(fp, "\n");
}

static void output_header_index(IMAGE *img, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;
  
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const GDI_IMAGE_BITMAP GDI_IMAGE_%s;\n", id);
	fprintf (fp, "/* Header */\n");
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI_IMAGE_%s __rodata_imagedata ={%s, %d,%d,0,data_%s};\n",
					id, type, width, height, id);
	fprintf(fp, "\n");

}

static void output_header_32bpp(IMAGE *img, int buf_width, int buf_height, int data_size, int pixel_depth, const char *id, char *type, int flag, FILE *fp)
{
	int width = img->width;
	int height = img->height;
  
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const GDI_IMAGE_BITMAP GDI_IMAGE_%s;\n", id);
	fprintf (fp, "/* Header */\n");
	fprintf (fp, "const GDI_IMAGE_BITMAP GDI_IMAGE_%s __rodata_imagedata ={%s, %d,%d, %d,%d, 0, data_%s};\n",
				id, type, width, height, buf_width, buf_height, id);
	fprintf(fp, "\n");
}

static void output_endmarker(const char *id, int flag, FILE *fp)
{
	//	fprintf (fp, "/* End Marker */\n");
	//	fprintf (fp, "IMAGE_MARKER(%s);\n", id);
}

static IMAGE *convert_to_8bpp(IMAGE *img)
{
	ImgGetPixel *getter;
	IMAGE	*img8bpp;

	getter = img_get_pixelfunc(img);

	img8bpp = (IMAGE*)malloc(sizeof(IMAGE));
	img_init(img8bpp);

	/* 画像情報設定 */
	img8bpp->width = img->width;
	img8bpp->height = img->height;
	img8bpp->stride = 0;
	img8bpp->pixel_depth = 8;
	img8bpp->pixel_bytes = 1;
	img8bpp->buf = (unsigned char*)malloc(img->width * img->height);
	img8bpp->palette = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * 256);
	img8bpp->palette_premultiplied = true;	//画像はpremultiplyされているので作成できるパレットもpremultiplyされる

	/* パレットを作成しつつ変換 */
	unsigned char	*dst = img8bpp->buf;
	int	count = img8bpp->width * img8bpp->height;
	int palnum = 0;
	int i, j;
	IMGCOLOR col;

	for (i = 0; i < count; i++) {
		col = getter->get();
		/* パレット検索 */
		for (j = 0; j < palnum; j++) {
			if (img8bpp->palette[j].n == col.n) {
				break;
			}
		}
		if (j == palnum) {
			/* すでに256個ある場合はエラー処理 */
			if (palnum == 256) {
				goto error;
			}
			/* パレットに追加 */
			img8bpp->palette[palnum].n = col.n;
			palnum++;
		}
		/* パレット番号をデータに追加 */
		*dst++ = j;
	}
	/* パレット数設定 */
	img8bpp->palette_num = palnum;
	/* getter削除 */
	delete getter;

	return img8bpp;
error:
	img_free(img8bpp);
	free(img8bpp);
	delete getter;

	return NULL;
}
