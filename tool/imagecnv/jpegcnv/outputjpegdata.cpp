#include "stdafx.h"
#include "outputjpegdata.h"

//using namespace std;
static void output_header(int data_size, const char *id, char *type, int flag, FILE *fp);
static void output_jpeg_no(const char *screen_no, const char *sample_no, const char *id, int flag, FILE *fp);
static void output_jpeg_data(const unsigned char *data, int data_size, const char *id, int flag, FILE *fp);
static void output_endmarker(const char *id, int flag, FILE *fp);

/**
 @brief JPEG�����o�͂���
 @param screen_no		AVP_Get_SampleImage�ɓn��screen_no
 @param sample_no		AVP_Get_SampleImage�ɓn��sample_no
 @param data			JPEG�f�[�^(���g�p)
 @param data_size		JPEG�f�[�^�̃T�C�Y(���g�p)
 @param img_id			�摜��ID(��:_I_SAMPLE)
 @param type			�o�͌`���ioutputbmpdata.h�Q�Ɓj
 @param output_fp		�o�͐�
 */
int output_jpegdata(const char *screen_no, const char *sample_no, const unsigned char *data,
					int data_size, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	//�w�b�_�f�[�^���t�@�C���ɏo��
	output_header(data_size, id, "GDI_TYPE_EX_JPEG_ID", flag, fp);

	//���@�p�f�[�^�o��
	output_jpeg_no(screen_no, sample_no, id, flag, fp);

	//END�}�[�J�[�o��
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

