#ifndef __OUTPUT_TYPE_H__
#define __OUTPUT_TYPE_H__

//データの順番を変更するとimage_resource_db.xlsに影響するので禁止 */
typedef enum {
	OUTPUT_TYPE_1BPP,
	OUTPUT_TYPE_8BPP,
	OUTPUT_TYPE_8BPP_RLE,
    OUTPUT_TYPE_16BPP,
	//    OUTPUT_TYPE_16BPP_DMP,
	OUTPUT_TYPE_32BPP,
	//	OUTPUT_TYPE_32BPP_DMP,
	OUTPUT_TYPE_32BPP_RLE2,
	OUTPUT_TYPE_MAX
} OUTPUT_TYPE;

/* 出力フラグ 個別 */
#define		OUTPUT_SVG_ABSCOORD			0x00010000			//絶対座標に変換
#define		OUTPUT_SVG_CNV_TO_PATH		0x00020000			//path以外のオブジェクトをpathに変換して出力
#define     OUTPUT_DMP_ALIGNMENT        0x00040000          //DMP GE用にWidth:16, height:8のアライメント(padding)

#endif
