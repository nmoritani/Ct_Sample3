/**
@file     pathdumper.c
@brief    デバッグコンソールへのフォントのOpenVGパス出力モジュール
@author   Yuji Nomura @DSC BU, Panasonic Corp.
@date     2013.4.15  新規作成
@par      更新履歴:
*/

/*
  使用方法
  1. fontapi_config.h にて STRPATH_DUMPER を 1 にする
  2. dump_strpath_info_C()またはdump_strpath_SVG()のプロトタイプ宣言を追加し、呼び出す

	extern void dump_strpath_C(VGPath vgpath);
	extern void dump_strpath_SVG(VGPath vgpath);

  3. デバッグコンソールに次のような文字列が出力される
	dump_strpath_C() writes:
------------------------------
const VGubyte pathSegments[] = {0x02, 0x04, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0a, 0x04, 0x00};
const VGfloat pathData[] = {29.300001f, 42.700001f, 33.000000f, 48.700001f, 32.600002f, 50.799999f, 30.400000f, 55.600002f, 17.900000f, 87.700005f, 48.799999f, 87.700005f, 50.900002f, 93.700005f, 15.800000f, 93.700005f, 8.100000f, 112.599998f, 1.100000f, 112.599998f, 29.300001f, 42.700001f, 29.300001f, 42.700001f, 37.500000f, 42.700001f, 66.099998f, 112.599998f, 59.100002f, 112.599998f, 50.900002f, 93.700005f, 48.799999f, 87.700005f, 35.799999f, 55.600002f, 34.700001f, 53.000000f, 33.000000f, 48.700001f, 29.300001f, 42.700001f};
------------------------------

	dump_strpath_SVG() writes:
------------------------------
<svg width="14px" height="23px"
    xmlns="http://www.w3.org/2000/svg" version="1.1">
  <g transform="scale(0.200000,0.200000)">
    <path d="M 29.300001,42.700001 L 33.000000,48.700001 Q 32.600002,50.799999 30.400000,55.600002 L 17.900000,87.700005 L 48.799999,87.700005 L 50.900002,93.700005 L 15.800000,93.700005 L 8.100000,112.599998 L 1.100000,112.599998 L 29.300001,42.700001 z M 29.300001,42.700001 L 37.500000,42.700001 L 66.099998,112.599998 L 59.100002,112.599998 L 50.900002,93.700005 L 48.799999,87.700005 L 35.799999,55.600002 Q 34.700001,53.000000 33.000000,48.700001 L 29.300001,42.700001 z" />
  </g>
</svg>
------------------------------

  補足
  ・GV200かGV210にしか対応していません。
  ・dump_strpath_C()の出力は、OpenVGのパスデータですので、画面上の見た目が似ていても、
    fontapiやGPIの設定によって内部表現が全く異なることがあります。例えば、
    - G5では、常にフォントサイズが1000でパス生成されます。（GPIでフォントサイズに縮小して描画しています）
    - コンパクトGENWARE機種の非UTF-8 I/Fの出力以外は、上下反転します。（上位層で上下反転して描画しています）
  ・G5のGPIで用いられるOffsetY/scale解決前のEMPATHをOffsetY/scale情報付きのSVG形式で出力するには、
    次の関数を使用してください。
	extern void dump_strpath_SVG_for_EMPATH(VGPath vgpath, int fontsize_x, int fontsize_y, VGfloat offsetY, VGfloat scaleY);
    offsetY, scaleYには、FONTAPI_GET_PATH_FUNCTION()が返す値をそのまま渡します。
    使用例:
			path = FONTAPI_GET_PATH_FUNCTION(&style, ucs_str, &vfOffsetY, &vfScaleY);
			dump_strpath_SVG_for_EMPATH(path, style.size_x, style.size_y, vfOffsetY, vfScaleY);
*/

#include "fontapi_config.h"
#include <math.h>

//#if KCSPEC_ASIC_TYPE == _VENUS7_HD2_ || KCSPEC_ASIC_TYPE == _VENUS7_FHD_
//#define GV200 1
//#elif KCSPEC_ASIC_TYPE == _VENUS8_FHD_
#define GV210 1
//#endif

#if KCSPEC_OPENVG && STRPATH_DUMPER
#if GV200 || GV210

#ifndef VG_API_CALL
#define VG_API_CALL extern
#endif

#ifdef _WIN32
 #include <VG/openvg.h>
#else
 #include <openvg_wrapper.h>
#endif
#include <VG/vgu.h>

#if CFG_ENABLE_HJ_SHELL
#ifdef __arm__
#include <hj_debug.h>
#define dbgprintf hj_DebugArm_WriteFormat
#define dbgprint hj_DebugArm_WriteFormat
#else
#include <hj_fw/hj_debug.h>
#endif
#else
#define dbgprintf
#define dbgprint
#endif

static void myPathBounds(VGPath, VGfloat *, VGfloat *, VGfloat *, VGfloat *);

#define OVG_OBJECT_CHECK_FOR_DEMO_ONLY
typedef VGfloat VGvalue;
typedef struct OVGpathStruct {
#ifdef OVG_OBJECT_CHECK_FOR_DEMO_ONLY
    VGint           iD;                 /**< object ID */
    void *          admin;              /**< administrator */
#endif
    VGint           format;             /**< path format */
    VGPathDatatype  datatype;           /**< data type */
    VGvalue         scale;              /**< scale */
    VGvalue         bias;               /**< bias */
    VGint           numSegments;        /**< number of segments */
    VGint           numCoords;          /**< number of coordinates */
    VGPathCapabilities  cap;            /**< path capability */
    void *          data;               /**< data pointer */
    VGubyte *       segment;            /**< segment pointer */
    VGint           dirty;              /**< dirty flag */
    VGint           deleted;            /**< delete flag */
    VGfloat         bbox[4];            /**< bouding box */
    VGint           refCount;           /**< reference count */
    VGint           segmentSize;        /**< memory size allocated for segment array */
    VGint           dataSize;           /**< memory size allocated for data array */
    VGint           invalid;            /**< invalidate flag */
    struct OVGpathStruct *next;         /**< next */
    void *          aldep;              /**< path info 2008.12.26 */
} OVGpath;

void dump_strpath_info_C(VGPath vgpath) {
	OVGpath *ovgpath = (OVGpath *)vgpath;
	dbgprintf("OVGpath info: ovgpath=%p, datatype=%d, numSegments=%d, numCoords=%d\r\n", (void *)ovgpath, ovgpath->datatype, ovgpath->numSegments, ovgpath->numCoords);
}

void dump_strpath_comment_C(const FONT_STYLE *style, const unsigned short *str) {
	dbgprintf("/* size=(%d,%d) spacing=%d R2L=%d str = ", style->size_x, style->size_y, style->spacing, style->righttoleft);
	while(*str){
		dbgprintf("%04x ", *str);
		str++;
	}
	dbgprint(" */\r\n");
}

void dump_strpath_C(VGPath vgpath) {
	int i;
	VGfloat *dataptr;
	OVGpath *ovgpath = (OVGpath *)vgpath;

	if (ovgpath->numSegments > 0 && ovgpath->numSegments < 100000){

		/* note */
		dbgprintf("/* OVGpath info: ovgpath=%p, datatype=%d, numSegments=%d, numCoords=%d */\r\n", (void *)ovgpath, ovgpath->datatype, ovgpath->numSegments, ovgpath->numCoords);

		dbgprintf("const VGubyte pathSegments[] = {");
		for(i=0; i<ovgpath->numSegments; i++){
			if (i > 0)
				dbgprintf(", ");
			dbgprintf("0x%02x", ovgpath->segment[i]);
		}
		dbgprintf("};\r\n");

		if (ovgpath->datatype == VG_PATH_DATATYPE_S_16){
			VGshort *sptr;
			dbgprintf("const VGshort pathData[] = {");
			sptr = (VGshort *)ovgpath->data;
			for(i=0; i<ovgpath->numCoords; i++){
				if (i > 0)
					dbgprintf(", ");
				dbgprintf("%d", sptr[i]);  /* TODO: scale(1/5) if necessary */
			}
		}else{
			dbgprintf("const VGfloat pathData[] = {");
			dataptr = (VGfloat *)ovgpath->data;
			for(i=0; i<ovgpath->numCoords; i++){
				if (i > 0)
					dbgprintf(", ");
				dbgprintf("%ff", dataptr[i]);  /* TODO: scale(1/5) if necessary */
			}
		}
		dbgprintf("};\r\n");
	}
}

#define S(a) (a)
#define SCEIL(a) (a)

void dump_strpath_info_SVG(VGPath vgpath) {
	OVGpath *ovgpath = (OVGpath *)vgpath;
	dbgprintf("OVGpath info: ovgpath=%p, datatype=%d, numSegments=%d, numCoords=%d\r\n", (void *)ovgpath, ovgpath->datatype, ovgpath->numSegments, ovgpath->numCoords);
}

void dump_strpath_comment_SVG(const FONT_STYLE *style, const unsigned short *str) {
	/* ヘッダ */
	dbgprintf("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\r\n");

	dbgprintf("<!-- size=(%d,%d) spacing=%d R2L=%d str = ", SCEIL(style->size_x), SCEIL(style->size_y), style->spacing, style->righttoleft);
	while(*str){
		dbgprintf("%04x ", *str);
		str++;
	}
	dbgprint("-->\r\n");
}

/* vgpathは左下原点 */
void dump_strpath_SVG_main(VGPath vgpath,
						   VGfloat precedingScaleX,  /* 見た目品質のための拡大生成の還元率 */
						   VGfloat precedingScaleY,  /* EMPATHの場合はフォントサイズへの縮小率 */
						   VGfloat offsetX,  /* EMPATHのオフセット量 */
						   VGfloat offsetY,
						   VGfloat scaleX,  /* Ascent/descentを収める為にさらに縮小表示する場合 */
						   VGfloat scaleY,
						   VGfloat coordScaleX,  /* 左下原点座標→左上原点座標の変換用 */
						   VGfloat coordScaleY,
						   VGfloat coordTranslateX,
						   VGfloat coordTranslateY)
{
	int i;
	VGfloat *data;
	VGshort *sdata;

	int x, y;
	VGfloat minX, minY, width, height;  /* for PathBounds / PathTransformedBounds */
	OVGpath *ovgpath;

	ovgpath = (OVGpath *)vgpath;

	data = (VGfloat *)ovgpath->data;
	sdata = (VGshort *)ovgpath->data;

	if (ovgpath->numSegments <= 0 || ovgpath->numSegments >= 100000)
		return;

	/* vgPathBounds(vgpath, &minX, &minY, &width, &height); */ /* toooo slow and uses too much memory */
	myPathBounds(vgpath, &minX, &minY, &width, &height);

	/* <svg>タグの領域外に出る部分があれば、その分領域を広げる */
	if (minX * precedingScaleX + offsetX < 0) {
		width -= (minX * precedingScaleX + offsetX) * scaleX;
		offsetX = -minX * precedingScaleX;
	}
	if (minY * precedingScaleY + offsetY < 0) {
		height -= (minY * precedingScaleY + offsetY) * scaleY;
		offsetY = -minY * precedingScaleY;
	}

	width *= precedingScaleX * scaleX;
	height *= precedingScaleY * scaleY;

	if (coordScaleX == -1) coordTranslateX += ceilf(width);
	if (coordScaleY == -1) coordTranslateY += ceilf(height);

	/* <svg> */
	dbgprintf("<svg width=\"%dpx\" height=\"%dpx\"\r\n", (int)ceilf(width), (int)ceilf(height));
	dbgprintf("    xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\r\n");

	/* note */
	dbgprintf("<!-- OVGpath info: ovgpath=%p, datatype=%d, numSegments=%d, numCoords=%d -->\r\n", (void *)ovgpath, ovgpath->datatype, ovgpath->numSegments, ovgpath->numCoords);

	/* coordinate transformation */
	dbgprintf("  <g transform=\"translate(%f,%f) scale(%f,%f)\">\r\n", coordTranslateX, coordTranslateY, coordScaleX, coordScaleY);

	/* scaling for fitting boundary */
	dbgprintf("    <g transform=\"scale(%f,%f)\">\r\n", scaleX, scaleY);

	/* translating for offsetting EMPATH */
	dbgprintf("      <g transform=\"translate(%f,%f)\">\r\n", offsetX, offsetY);

	/* scaling for better precision */
	dbgprintf("        <g transform=\"scale(%f,%f)\">\r\n", precedingScaleX, precedingScaleY);

	/* <path> */
	dbgprintf("          <path d=\"");
	for(i=0; i<ovgpath->numSegments; i++){
		/* 区切り空白 */
		if (i > 0){
			dbgprintf(" ");
		}

		if (ovgpath->datatype == VG_PATH_DATATYPE_S_16){
			switch (ovgpath->segment[i]) {
			case VG_MOVE_TO_ABS:
				dbgprintf("M %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_MOVE_TO_REL:
				dbgprintf("m %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_LINE_TO_ABS:
				dbgprintf("L %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_LINE_TO_REL:
				dbgprintf("l %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_HLINE_TO_ABS:
				dbgprintf("H %d", S(sdata[0]));
				sdata += 1;
				break;
			case VG_HLINE_TO_REL:
				dbgprintf("h %d", S(sdata[0]));
				sdata += 1;
				break;
			case VG_VLINE_TO_ABS:
				dbgprintf("V %d", S(sdata[0]));
				sdata += 1;
				break;
			case VG_VLINE_TO_REL:
				dbgprintf("v %d", S(sdata[0]));
				sdata += 1;
				break;
			case VG_QUAD_TO_ABS: 
				dbgprintf("Q %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]));
				sdata += 4;
				break;
			case VG_QUAD_TO_REL: 
				dbgprintf("q %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]));
				sdata += 4;
				break;
			case VG_CUBIC_TO_ABS:
				dbgprintf("C %d,%d %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]), S(sdata[4]), S(sdata[5]));
				sdata += 6;
				break;
			case VG_CUBIC_TO_REL:
				dbgprintf("c %d,%d %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]), S(sdata[4]), S(sdata[5]));
				sdata += 6;
				break;
			case VG_SQUAD_TO_ABS:
				dbgprintf("T %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_SQUAD_TO_REL:
				dbgprintf("t %d,%d", S(sdata[0]), S(sdata[1]));
				sdata += 2;
				break;
			case VG_SCUBIC_TO_ABS:
				dbgprintf("S %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]));
				sdata += 4;
				break;
			case VG_SCUBIC_TO_REL:
				dbgprintf("s %d,%d %d,%d", S(sdata[0]), S(sdata[1]), S(sdata[2]), S(sdata[3]));
				sdata += 4;
				break;
			case VG_SCCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_SCCWARC_TO_ABS!!");
				break;
			case VG_SCCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_SCCWARC_TO_REL!!");
				break;
			case VG_SCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_SCWARC_TO_ABS!!");
				break;
			case VG_SCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_SCWARC_TO_REL!!");
				break;
			case VG_LCCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_LCCWARC_TO_ABS!!");
				break;
			case VG_LCCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_LCCWARC_TO_REL!!");
				break;
			case VG_LCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_LCWARC_TO_ABS!!");
				break;
			case VG_LCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_LCWARC_TO_REL!!");
				break;
			case VG_CLOSE_PATH:
				dbgprintf("z");
				break;
			default:
				break;
			}
		}else{
			switch (ovgpath->segment[i]) {
			case VG_MOVE_TO_ABS:
				dbgprintf("M %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_MOVE_TO_REL:
				dbgprintf("m %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_LINE_TO_ABS:
				dbgprintf("L %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_LINE_TO_REL:
				dbgprintf("l %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_HLINE_TO_ABS:
				dbgprintf("H %f", S(data[0]));
				data += 1;
				break;
			case VG_HLINE_TO_REL:
				dbgprintf("h %f", S(data[0]));
				data += 1;
				break;
			case VG_VLINE_TO_ABS:
				dbgprintf("V %f", S(data[0]));
				data += 1;
				break;
			case VG_VLINE_TO_REL:
				dbgprintf("v %f", S(data[0]));
				data += 1;
				break;
			case VG_QUAD_TO_ABS: 
				dbgprintf("Q %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]));
				data += 4;
				break;
			case VG_QUAD_TO_REL: 
				dbgprintf("q %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]));
				data += 4;
				break;
			case VG_CUBIC_TO_ABS:
				dbgprintf("C %f,%f %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]), S(data[4]), S(data[5]));
				data += 6;
				break;
			case VG_CUBIC_TO_REL:
				dbgprintf("c %f,%f %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]), S(data[4]), S(data[5]));
				data += 6;
				break;
			case VG_SQUAD_TO_ABS:
				dbgprintf("T %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_SQUAD_TO_REL:
				dbgprintf("t %f,%f", S(data[0]), S(data[1]));
				data += 2;
				break;
			case VG_SCUBIC_TO_ABS:
				dbgprintf("S %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]));
				data += 4;
				break;
			case VG_SCUBIC_TO_REL:
				dbgprintf("s %f,%f %f,%f", S(data[0]), S(data[1]), S(data[2]), S(data[3]));
				data += 4;
				break;
			case VG_SCCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_SCCWARC_TO_ABS!!");
				break;
			case VG_SCCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_SCCWARC_TO_REL!!");
				break;
			case VG_SCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_SCWARC_TO_ABS!!");
				break;
			case VG_SCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_SCWARC_TO_REL!!");
				break;
			case VG_LCCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_LCCWARC_TO_ABS!!");
				break;
			case VG_LCCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_LCCWARC_TO_REL!!");
				break;
			case VG_LCWARC_TO_ABS:
				dbgprintf("!!UNKNOWN VG_LCWARC_TO_ABS!!");
				break;
			case VG_LCWARC_TO_REL:
				dbgprintf("!!UNKNOWN VG_LCWARC_TO_REL!!");
				break;
			case VG_CLOSE_PATH:
				dbgprintf("z");
				break;
			default:
				break;
			}
		}
	}
	dbgprintf("\" />\r\n");
	dbgprintf("        </g>\r\n");
	dbgprintf("      </g>\r\n");
	dbgprintf("    </g>\r\n");
	dbgprintf("  </g>\r\n");
	dbgprintf("</svg>\r\n");
}

void dump_strpath_SVG_for_EMPATH(VGPath vgpath, int fontsize_x, int fontsize_y, VGfloat offsetY, VGfloat scaleY)
{
	dump_strpath_SVG_main(vgpath, fontsize_x / 1000.0f, fontsize_y / 1000.0f, 0, -offsetY, 1, scaleY, 1, -1, 0, 0);
}

void dump_strpath_SVG(VGPath vgpath) {
#if KCSPEC_SLR || !CFG_USE_GENWARE	/* コンパクトOpenVG機種はDT_COORD_LEFT_TOP */
	const int coordScaleY = -1;  /* DT_COORD_LEFT_BOT用 */
#else
	const int coordScaleY = 1;  /* DT_COORD_LEFT_TOP用 */
#endif

#if KCSPEC_SLR
	const float precedingScaleX = 1;
	const float precedingScaleY = 1;
#else
	float precedingScaleX = 0.2f;  /* 大抵の画面で、縦横5倍のフォントサイズでVGPath生成している */
	float precedingScaleY = 0.2f;
#endif

	dump_strpath_SVG_main(vgpath, precedingScaleX, precedingScaleY, 0, 0, 1, 1, 1, coordScaleY, 0, 0);
}

void myPathBounds(VGPath path, VGfloat *minXp, VGfloat *minYp, VGfloat *widthp, VGfloat *heightp)
{
	OVGpath *ovgpath = (OVGpath *)path;
	int i,j;

	if (ovgpath->datatype == VG_PATH_DATATYPE_S_16){
		VGshort *pathData;
		VGshort minX, minY, maxX, maxY, currentX, currentY;

		pathData = (VGshort *)ovgpath->data;
		minX = minY = maxX = maxY = currentX = currentY = 0;

		for(i=j=0; i<ovgpath->numSegments; i++){
			switch(ovgpath->segment[i]){
			case VG_MOVE_TO_ABS:
			case VG_LINE_TO_ABS:
			case VG_SQUAD_TO_ABS:
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_MOVE_TO_REL:
			case VG_LINE_TO_REL:
			case VG_SQUAD_TO_REL:
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_HLINE_TO_ABS:
				currentX = pathData[j++];
				break;
			case VG_HLINE_TO_REL:
				currentX += pathData[j++];
				break;
			case VG_VLINE_TO_ABS:
				currentY = pathData[j++];
				break;
			case VG_VLINE_TO_REL:
				currentY += pathData[j++];
				break;
			case VG_QUAD_TO_ABS:
			case VG_SCUBIC_TO_ABS:
				j += 2;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_QUAD_TO_REL:
			case VG_SCUBIC_TO_REL:
				j += 2;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_CUBIC_TO_ABS:
				j += 4;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_CUBIC_TO_REL:
				j += 4;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_SCCWARC_TO_ABS:
			case VG_SCWARC_TO_ABS:
			case VG_LCCWARC_TO_ABS:
			case VG_LCWARC_TO_ABS:
				/* ignoring arc, just looking at end point */
				j += 3;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_SCCWARC_TO_REL:
			case VG_SCWARC_TO_REL:
			case VG_LCCWARC_TO_REL:
			case VG_LCWARC_TO_REL:
				/* ignoring arc, just looking at end point */
				j += 3;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_CLOSE_PATH:
			default:
				break;
			}

			if (currentX < minX) minX = currentX;
			if (currentY < minY) minY = currentY;
			if (currentX > maxX) maxX = currentX;
			if (currentY > maxY) maxY = currentY;
		}

		*minXp = minX;
		*minYp = minY;
		*widthp = maxX - minX;
		*heightp = maxY - minY;
	}else{
		VGfloat *pathData;
		VGfloat minX, minY, maxX, maxY, currentX, currentY;

		pathData = (VGfloat *)ovgpath->data;
		minX = minY = maxX = maxY = currentX = currentY = 0.0f;

		for(i=j=0; i<ovgpath->numSegments; i++){
			switch(ovgpath->segment[i]){
			case VG_MOVE_TO_ABS:
			case VG_LINE_TO_ABS:
			case VG_SQUAD_TO_ABS:
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_MOVE_TO_REL:
			case VG_LINE_TO_REL:
			case VG_SQUAD_TO_REL:
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_HLINE_TO_ABS:
				currentX = pathData[j++];
				break;
			case VG_HLINE_TO_REL:
				currentX += pathData[j++];
				break;
			case VG_VLINE_TO_ABS:
				currentY = pathData[j++];
				break;
			case VG_VLINE_TO_REL:
				currentY += pathData[j++];
				break;
			case VG_QUAD_TO_ABS:
			case VG_SCUBIC_TO_ABS:
				j += 2;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_QUAD_TO_REL:
			case VG_SCUBIC_TO_REL:
				j += 2;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_CUBIC_TO_ABS:
				j += 4;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_CUBIC_TO_REL:
				j += 4;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_SCCWARC_TO_ABS:
			case VG_SCWARC_TO_ABS:
			case VG_LCCWARC_TO_ABS:
			case VG_LCWARC_TO_ABS:
				/* ignoring arc, just looking at end point */
				j += 3;
				currentX = pathData[j++];
				currentY = pathData[j++];
				break;
			case VG_SCCWARC_TO_REL:
			case VG_SCWARC_TO_REL:
			case VG_LCCWARC_TO_REL:
			case VG_LCWARC_TO_REL:
				/* ignoring arc, just looking at end point */
				j += 3;
				currentX += pathData[j++];
				currentY += pathData[j++];
				break;
			case VG_CLOSE_PATH:
			default:
				break;
			}

			if (currentX < minX) minX = currentX;
			if (currentY < minY) minY = currentY;
			if (currentX > maxX) maxX = currentX;
			if (currentY > maxY) maxY = currentY;
		}

		*minXp = minX;
		*minYp = minY;
		*widthp = maxX - minX;
		*heightp = maxY - minY;
	}
}

#endif /* GV200 || GV210 */
#endif /* KCSPEC_OPENVG && STRPATH_DUMPER */
