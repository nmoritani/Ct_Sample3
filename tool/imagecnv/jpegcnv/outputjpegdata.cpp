#include "stdafx.h"
#include "outputjpegdata.h"

//using namespace std;
static void output_header(int data_size, const char *id, char *type, int flag, FILE *fp);
static void output_jpeg_no(const char *screen_no, const char *sample_no, const char *id, int flag, FILE *fp);
static void output_jpeg_data(const unsigned char *data, int data_size, const char *id, int flag, FILE *fp);
static void output_endmarker(const char *id, int flag, FILE *fp);

/**
 @brief JPEG情報を出力する
 @param screen_no		AVP_Get_SampleImageに渡すscreen_no
 @param sample_no		AVP_Get_SampleImageに渡すsample_no
 @param data			JPEGデータ(未使用)
 @param data_size		JPEGデータのサイズ(未使用)
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int output_jpegdata(const char *screen_no, const char *sample_no, const unsigned char *data,
					int data_size, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	//ヘッダデータをファイルに出力
	output_header(data_size, id, "GDI_TYPE_EX_JPEG_ID", flag, fp);

	//実機用データ出力
	output_jpeg_no(screen_no, sample_no, id, flag, fp);

	//ENDマーカー出力
	output_endmarker(id, flag, fp);

	return 0;
}

static void output_header(int data_size, const char *id, char *type, int flag, FILE *fp)
{
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, " extern const unsigned short pc%s[];\n", id);
	fprintf (fp, "/* Header */\n");
	
	fprintf (fp, "const GDI_IMAGE GDI%s __rodata_imagedata ={%s,%d,%d};\n",
				id, type, 1, 1);
	fprintf(fp, "\n");
}

static void output_jpeg_no(const char *screen_no, const char *sample_no, const char *id, int flag, FILE *fp)
{
	fprintf (fp, "const unsigned short pc%s[2]  __rodata_imagedata = {%s, %s};\n", id, screen_no, sample_no);
}

static void output_endmarker(const char *id, int flag, FILE *fp)
{
	fprintf (fp, "/* End Marker */\n");
	fprintf (fp, "IMAGE_MARKER(%s);\n", id);
}

