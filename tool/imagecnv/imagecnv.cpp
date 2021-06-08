// imagecnv.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#pragma warning( disable : 4819)
#pragma warning( disable : 4996)
#include "SvgParser.h"
#include "bmpcnv.h"
#include "svgcnv.h"
#include "jpegcnv.h"
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <fstream>

using namespace std;
int convert_file(const char *filename, const char *plt_name, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp);
int convert_bmp(const char *filename, IMGCOLOR *color_plt, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp);
int convert_png(const char *filename, IMGCOLOR *color_plt, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp);
int convert_svg(const char *filename, const char *img_id, OUTPUT_TYPE type, FILE *output_fp);
int convert_jpeg(const char *filename, const char *img_id, OUTPUT_TYPE type, FILE *output_fp);
static void printout_data_null(const char *id, FILE *output_fp);
static vector<string> split_basename(const string &str, char delim);

///* デバッグ出力切り替え */
//bool Engine::UI::SVG::SvgUtils::IsDebug = false;

/* 変換時間計測フラグ */
static bool chktime_on = false;

/* 絶対座標変換フラグ */
static bool abscoord = false;

int _tmain(int argc, _TCHAR* argv[])
{
	int i, j, ret, align_width = 0, align_height = 0;
	char datafile_name[257];
	char id_name[65];
	char outputbase_name[257];
	char plt_name[257];
	char work[20];
	char wid[20] = {0};
	char hei[20] = {0};

	OUTPUT_TYPE type = OUTPUT_TYPE_8BPP;
	//初期化
	datafile_name[0] = '\0';
	id_name[0] = '\0';
	outputbase_name[0] = '\0';
	plt_name[0] = '\0';

	if (argc > 1) {
		/* 引数あり */
		for (i=1;i<argc;i++){
			wcstombs( work, argv[i], 20 );
			if (!_stricmp((const char *)work, "-f")) {
				wcstombs( datafile_name, argv[i+1], 256 );
				//fprintf(stdout, "OK filename:%s\n",datafile_name);
				i++;
			} else
			if (!_stricmp((const char *)work, "-i")) {
				wcstombs( id_name, argv[i+1], 64 );
				//fprintf(stdout, "OK id:%s\n",id_name);
				i++;
			} else
			if (!_stricmp((const char *)work, "-t")) {
				wcstombs( work, argv[i+1], 10 );
				type = (OUTPUT_TYPE)atoi((const char *)work);
				//fprintf(stdout, "OK type:%d\n",type);
				i++;
			} else
			if (!_stricmp((const char *)work, "-o")) {
				//出力ファイル名(拡張子除く)
				wcstombs( outputbase_name, argv[i+1], 256 );
				//fprintf(stdout, "OK outputbase_name:%s\n",outputbase_name);
				i++;
			} else
			if (!_stricmp((const char *)work, "-p")) {
				//パレット指定
				wcstombs( plt_name, argv[i+1], 256 );
				//fprintf(stdout, "OK plt_name:%s\n",plt_name);
				i++;
			} else
			if (!_stricmp((const char *)work, "-w")) {
				wcstombs( wid, argv[i+1], 256);
				i++;
			} else
			if (!_stricmp((const char *)work, "-h")) {
				wcstombs( hei, argv[i+1], 256);
				i++;
			} else
			if (!_stricmp((const char *)work, "-chktime")) {
				chktime_on = true;
			} else
			if (!_stricmp((const char *)work, "--abscoord")) {
				abscoord = true;
			}
		}
	} else {
		fprintf(stderr, "imagecnv -f file -t outtype, -i idname, -a align -p pallet, ...\n");
		fprintf(stderr, "  -f : file_name   : xxx.svg xxx.png etc...\n");
		fprintf(stderr, "  -t : bitmap_type : 0=1BPP, 1=8BPP, 2=8BPP_RLE, 3=16BPP, 4=32BPP, 5=32BPP_RLE\n");
		fprintf(stderr, "  -i : id_name     : extern name \n");
		fprintf(stderr, "  -w : align width : alignment for bitmap files (ex DMP 32)\n");
		fprintf(stderr, "  -h : align height: alignment for bitmap files (ex DMP 8)\n");
		return 0;
	}

	if (wid[0] != 0) {
		align_width = atoi(wid);
	}
	if (hei[0] != 0) {
		align_height = atoi(hei);
	}

	if (strlen(datafile_name) == 0) {
		ret = -1;
	}
	if (strlen(id_name) == 0) {
		for (i=0,j=0; i<strlen(datafile_name); i++,j++) {
			if ((i>(signed int)0) && ((datafile_name[i-1] == '\\') || (datafile_name[i-1] == '\/'))) {
				j = 0;	
			}
			if (datafile_name[i] == '-') {
				id_name[j] = '_';
			} else if (datafile_name[i] == '.') {
				break;
			} else {
				id_name[j] = datafile_name[i];
			}
		}
		id_name[j] = NULL;
	}
	ret = convert_file(datafile_name, plt_name, id_name, type, align_width, align_height, stdout);
	if (ret == -1) {
		//生成失敗時は、NULLデータ生成
		printout_data_null(id_name, stdout);
	}
	else {
#if 0
		//TESTコード

		convert_file("sample\\radialgradient.svg","" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP, stdout);
//		convert_file("sample\\expobar_back_black_l.png","" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_HR_AUTO_RLE2, stdout);
//		convert_file("sample\\expobar_back_shadow_l.png","" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_HR_AUTO_RLE2, stdout);
//		convert_file("sample\\box.svg","sample\\STANDARD.bin" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP, stdout);
//		convert_file("sample\\gradient.svg","sample\\STANDARD.bin" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_1BPP, stdout);
//		convert_file("sample\\gradient.svg","sample\\STANDARD.bin" ,"I_SAMPLE", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP, stdout);


//		convert_file("sample\\SCREEN_TOPMENU-SAMPLE_JPEG_BACK_IMAGE_1.jpg", "", "I_BTN_COMMON_W254_TIT", (OUTPUT_TYPE)OUTPUT_TYPE_HR_AUTO_RLE2, stdout);
//		convert_file("sample\\WIFI_JP.png", "sample\\STANDARD.bin", "I_WIFI_CERTIFICATION_JP", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP_RLE, stdout);

//		convert_file("sample\\auto_sc.svg",	"ID_IMAGE09902",			(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\btn_common.svg",	"ID_IMAGE09902",			(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\btn_common_blk.svg",	"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\scene_hdr_1.svg",	"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\otr_arw_right_9_sp1.svg",	"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\other.svg",		"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\box.svg",			"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\curve.svg",		"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\line.svg",		"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\otr_cha_af_hojo_sp1.svg","_I_ICON",	(OUTPUT_TYPE)OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\scn_cok_32.svg", "_I_SCN_COK", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\ply_flp_sort_bar_frm.svg",  "_I_SCN_COK",(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\btn_common_l42_on_l.svg",	"_I_ICON",	(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\roshutu_bar_sp1.svg",	"_I_ICON", (OUTPUT_TYPE)OUTPUT_TYPE_1BPP,	stdout);
//		convert_file("sample\\A_MODE_icon.svg","_I_SCN_COK", (OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\SCREEN_TOPMENU-SAMPLE_JPEG_BACK_IMAGE_1.jpg",	"_I_ICON",			(OUTPUT_TYPE)OUTPUT_TYPE_8BPP,			stdout);

//		convert_file("sample\\viera_travel.bmp",	"_I_ICON", OUTPUT_TYPE_8BPP_PAL_RLE2,	stdout);
//		convert_file("sample\\burst_search_bar.png",	"_I_ICON", OUTPUT_TYPE_32BPP_RLE2,	stdout);
//		convert_file("sample\\itimatu.png",	"_I_ICON", OUTPUT_TYPE_32BPP_RLE2,	stdout);
//		convert_file("sample\\guide_slide_3d_mode_1_fz.bmp", "_I_ICON", OUTPUT_TYPE_8BPP,  stdout);
//		convert_file("sample\\guide_slide_3d_mode_2_fz.bmp", "_I_ICON", OUTPUT_TYPE_8BPP,  stdout);
//		convert_file("sample\\guide_slide_3d_mode_3_fz.bmp", "_I_ICON", OUTPUT_TYPE_8BPP,  stdout);
//		convert_file("sample\\test_1bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_1BPP,			stdout);
//		convert_file("sample\\test_4bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\test_8bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\test_8bpp.png",	"_I_ICON",	OUTPUT_TYPE_8BPP,			stdout);
//		convert_file("sample\\test_4bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_8BPP_RLE,		stdout);
//		convert_file("sample\\test_8bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_8BPP_RLE,		stdout);
//		convert_file("sample\\test_8bpp.png",	"_I_ICON",	OUTPUT_TYPE_8BPP_RLE,		stdout);
//		convert_file("sample\\test_8bpp.png",	"_I_ICON",	OUTPUT_TYPE_8BPP_PAL,		stdout);
//		convert_file("sample\\test_8bpp.png",	"_I_ICON",	OUTPUT_TYPE_8BPP_PAL_RLE2,	stdout);
//		convert_file("sample\\test_24bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_32BPP,			stdout);
//		convert_file("sample\\test_24bpp.png",	"_I_ICON",	OUTPUT_TYPE_32BPP,			stdout);
//		convert_file("sample\\test_32bpp.png",	"_I_ICON",	OUTPUT_TYPE_32BPP,			stdout);
//		convert_file("sample\\test_24bpp.bmp",	"_I_ICON",	OUTPUT_TYPE_32BPP_RLE2,		stdout);
//		convert_file("sample\\test_24bpp.png",	"_I_ICON",	OUTPUT_TYPE_32BPP_RLE2,		stdout);
//		convert_file("sample\\test_32bpp.png",	"_I_ICON",	OUTPUT_TYPE_32BPP_RLE2,		stdout);
//		convert_file("sample\\stretch_h_1.png",	"_I_ICON",	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H,	stdout);
//		convert_file("sample\\stretch_h_2.png",	"_I_ICON",	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H,	stdout);
#endif
	}
	//_CrtDumpMemoryLeaks();

	return 0;
}

/**
 @brief 画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_file(const char *filename, const char *plt_name, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp)
{
	int			ret;
	const char	*p = filename;
	const char	*ext = p;
	FILE		*fp;
	IMGCOLOR	*color_plt = NULL;

	//拡張子検索
	while (*p) {
		if (*p == '.') {
			ext = p;
		}
		p++;
	}

	//ファイルチェック(JPEG以外)
	if (_stricmp(ext, ".jpg") && _stricmp(ext, ".jpeg")) {
		fp = fopen(filename, "rb");
		if (fp == NULL) {
			if (!chktime_on)	fprintf(stderr, "ERROR: [%s] - File Not Found.\n", img_id);
			return -1;
		}
		fclose(fp);
	}

	//パレットデータ取得
	if(plt_name[0] != '\0'){
		fp = fopen(plt_name, "rb");
		if (fp == NULL) {
			return -1;
		}
		color_plt = (IMGCOLOR*)malloc(sizeof(IMGCOLOR) * 256);
		fread(color_plt, 1, 256*4, fp);
		fclose(fp);
	}

		//判定
	if (!_stricmp(ext, ".bmp")) {
		//BMP形式
		ret = convert_bmp(filename, color_plt, img_id, type, align_width, align_height, output_fp);
	} else if (!_stricmp(ext, ".png")) {
		//PNG形式
		ret = convert_png(filename, color_plt, img_id, type, align_width, align_height, output_fp);
	} else if (!_stricmp(ext, ".svg")) {
		//SVG形式 OUTPUT_TYPEからOUTPUT_SVG_TYPEへキャストできるように実装している
		ret = convert_svg(filename, img_id, type, output_fp);
	} else if (!_stricmp(ext, ".jpg") || !_stricmp(ext, ".jpeg")) {
		//SVG形式 OUTPUT_TYPEからOUTPUT_SVG_TYPEへキャストできるように実装している
		ret = convert_jpeg(filename, img_id, type, output_fp);
	} else {
		ret = -1;
	}
	if(color_plt != NULL){
		free(color_plt);
	}

	return ret;
}

/**
 @brief BMP画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_bmp(const char *filename, IMGCOLOR *color_plt, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp)
{
	IMAGE	img;
	int		ret;
	long	oldTime, midTime, newTime;

	if (chktime_on)	oldTime = timeGetTime();

	//画像読み込み
	ret = bmp_load(filename, &img);
	if (ret < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Parse Failed.(%s)\n", img_id, filename);
		return -1;
	}

	if (chktime_on)	midTime = timeGetTime();
	//出力フラグ
	int flag = 0;
	//出力
	ret = output_bmpdata(&img, color_plt, img_id, type, flag, align_width, align_height, output_fp);

	if (chktime_on)	newTime = timeGetTime();

	if (ret < 0) {
		fprintf(stderr, "ERROR: %s - ", img_id);
		if (ret == -1) {
			if (!chktime_on)	fprintf(stderr, "Imagefile Read Error.(%s)\n", filename);
		}
		else if(ret == -2) {
			if (!chktime_on)	fprintf(stderr, "Output Type Error.(%s)\n", filename);
		}
		else if(ret == -3) {
			if (!chktime_on)	fprintf(stderr, "Pixel-Depth(%d) Error.(%s)\n", img.pixel_depth, filename);
		}
		else if(ret == -4) {
			if (!chktime_on)	fprintf(stderr, "Image Size(%d,%d) Error.(%s)\n", img.width, img.height, filename);
		}
		else {
			if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		}
		img_free(&img);
		return -1;
	}

	if (chktime_on) {
		fprintf(stderr, "bmp,%d,%d,%d,%dx%d,%d,%s,%s\n",
			newTime-oldTime, midTime-oldTime, newTime-midTime, img.width, img.height, img.pixel_depth, img_id, filename);
	}
	//データ解放
	img_free(&img);

	return 0;
}

/**
 @brief PNG画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_png(const char *filename, IMGCOLOR *color_plt, const char *img_id, OUTPUT_TYPE type, int align_width, int align_height, FILE *output_fp)
{
	IMAGE	img;
	int		ret;
	long	oldTime, midTime, newTime;

	if (chktime_on)	oldTime = timeGetTime();

	//画像読み込み
	ret = png_load(filename, &img);
	if (ret < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Parse Failed.(%s)\n", img_id, filename);
		return -1;
	}

	if (chktime_on)	midTime = timeGetTime();
	//出力フラグ
	int flag = 0;
	//出力
	ret = output_bmpdata(&img, color_plt, img_id, type, flag, align_width, align_height, output_fp);

	if (chktime_on)	newTime = timeGetTime();

	if (ret < 0) {
		fprintf(stderr, "ERROR: %s - ", img_id);
		if (ret == -1) {
			if (!chktime_on)	fprintf(stderr, "Imagefile Read Error.(%s)\n", filename);
		}
		else if(ret == -2) {
			if (!chktime_on)	fprintf(stderr, "Output Type Error.(%s)\n", filename);
		}
		else if(ret == -3) {
			if (!chktime_on)	fprintf(stderr, "Pixel-Depth(%d) Error.(%s)\n", img.pixel_depth, filename);
		}
		else if(ret == -4) {
			if (!chktime_on)	fprintf(stderr, "Image Size(%d,%d) Error.(%s)\n", img.width, img.height, filename);
		}
		else {
			if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		}
		img_free(&img);
		return -1;
	}

	if (chktime_on) {
		fprintf(stderr, "png,%d,%d,%d,%dx%d,%d,%s,%s\n",
			newTime-oldTime, midTime-oldTime, newTime-midTime, img.width, img.height, img.pixel_depth, img_id, filename);
	}
	//データ解放
	img_free(&img);

	return 0;
}

#if 0
/**
 @brief SVG画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_svg(const char *filename, const char *img_id, OUTPUT_SVG_TYPE type, FILE *output_fp)
{
	int ret;
	long	oldTime, midTime, newTime;

	if (chktime_on)	oldTime = timeGetTime();

	Engine::UI::SVG::SvgDocument Doc(filename, "");
	Engine::UI::SVG::SvgBuildVisitor Builder(&Doc);

	if (chktime_on)	midTime = timeGetTime();
#if 1
	//データ生成
	ret = output_svgdata(&Builder, img_id, type, abscoord, output_fp);
	if (chktime_on)	newTime = timeGetTime();

	if (ret < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		return -1;
	}
#endif
	if (chktime_on) {
		fprintf(stderr, "svg,%d,%d,%d,%dx%d,%d,%s,%s\n",
			newTime-oldTime, midTime-oldTime, newTime-midTime, (int)Builder.GetWith(), (int)Builder.GetHeight(), 0, img_id, filename);
	}
	return 0;
}
#endif

/**
 @brief SVG画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_svg(const char *filename, const char *img_id, OUTPUT_TYPE type, FILE *output_fp)
{
	int ret;
	long	oldTime, midTime, newTime;

	if (chktime_on)	oldTime = timeGetTime();

	SvgParser parser;;

	if (parser.parse(filename) < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		return -1;
	}

	if (chktime_on)	midTime = timeGetTime();

	//データ生成
	//出力フラグ
	int flag = 0;
	if (abscoord) {
		flag |= OUTPUT_SVG_ABSCOORD;
	}
	
	//出力
	ret = output_svgdata(&parser, img_id, type, flag, output_fp);
	if (chktime_on)	newTime = timeGetTime();

	if (ret < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		return -1;
	}

	if (chktime_on) {
		fprintf(stderr, "svg,%d,%d,%d,%dx%d,%d,%s,%s\n",
			newTime-oldTime, midTime-oldTime, newTime-midTime, (int)parser.root()->width(), (int)parser.root()->height(), 0, img_id, filename);
	}
	return 0;
}

/**
 @brief JPEG画像ファイルを変換する
 @param filename		画像ファイル名
 @param img_id			画像のID(例:_I_SAMPLE)
 @param type			出力形式（outputbmpdata.h参照）
 @param output_fp		出力先
 */
int convert_jpeg(const char *filename, const char *img_id, OUTPUT_TYPE type, FILE *output_fp)
{
	int		ret;
	long	oldTime, newTime;
	char	basename[100];
	string	str_basename;
	vector<string>		info;

	if (chktime_on)	oldTime = timeGetTime();

	//ファイル名からIDを取得
	_splitpath_s(filename, NULL, 0, NULL, 0, basename, (sizeof(basename)/sizeof(basename[0])), NULL, 0);
	/* string型に変換する */
	str_basename = basename;
	info = split_basename(str_basename, '-');

	//データ生成
	//出力フラグ
	int flag = 0;
	//出力
	ret = output_jpegdata(info[0].c_str(), info[1].c_str(), NULL, 0, img_id, type, flag, output_fp);

	if (chktime_on)	newTime = timeGetTime();

	if (ret < 0) {
		if (!chktime_on)	fprintf(stderr, "ERROR: %s - Convert Failed.(%s)\n", img_id, filename);
		return -1;
	}

	if (chktime_on) {
		fprintf(stderr, "jpeg,%d,%s,%s\n",
			newTime-oldTime, img_id, filename);
	}
	return 0;
}

static vector<string> split_basename(const string &str, char delim)
{
	vector<string> result;
	size_t current = 0;
	size_t found;
	
	while((found = str.find_first_of(delim, current)) != string::npos){
		result.push_back(string(str, current, found - current));
		current = found + 1;
	}
	result.push_back(string(str, current, str.size() - current));
	return result;
}

static void printout_data_null(const char *id, FILE *fp)
{
	fprintf (fp, "const GDI_IMAGE GDI%s __rodata_imagedata ={GDI_IMAGE_TYPE_NONE,0,0,NULL};\n", id);
	fprintf(fp, "\n");
}

