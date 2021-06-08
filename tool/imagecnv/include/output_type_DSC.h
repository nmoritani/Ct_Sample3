#ifndef __OUTPUT_TYPE_H__
#define __OUTPUT_TYPE_H__

//データの順番を変更するとimage_resource_db.xlsに影響するので禁止 */
typedef enum {
	OUTPUT_TYPE_1BPP,
	OUTPUT_TYPE_8BPP,
	OUTPUT_TYPE_8BPP_RLE,
	OUTPUT_TYPE_HR_8BPP_PAL,
	OUTPUT_TYPE_HR_8BPP_PAL_RLE2,
	OUTPUT_TYPE_8BPP_STRETCH_H,			//(未対応)縦横伸張 ボタン用画像
	OUTPUT_TYPE_8BPP_STRETCH_V,			//(未対応)縦横伸張 ボタン用画像
	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H,	//縦横伸張 ボタン用画像
	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_V,	//縦横伸張 ボタン用画像
	OUTPUT_TYPE_HR_32BPP,
	OUTPUT_TYPE_HR_32BPP_RLE2,
	OUTPUT_TYPE_HR_AUTO,				//8bpp画像->8BPP_PAL		32bpp画像->32BPP
	OUTPUT_TYPE_HR_AUTO_RLE2,			//8bpp画像->8BPP_PAL_RLE2	32bpp画像->32BPP_RLE2
	OUTPUT_TYPE_1BPP_REVERSE,			//モノクロ 白黒反転
	OUTPUT_TYPE_MAX
} OUTPUT_TYPE;

/* 出力フラグ 個別 */
#define		OUTPUT_SVG_ABSCOORD			0x00010000			//絶対座標に変換
#define		OUTPUT_SVG_CNV_TO_PATH		0x00020000			//path以外のオブジェクトをpathに変換して出力
#define		OUTPUT_FOR_HIRESO_APL		0x00040000			//高解像度アプリ用出力（HR形式のサイズを1/2しない)


#endif
