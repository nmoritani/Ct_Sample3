#ifndef _SVGTRANSFORM_H_
#define _SVGTRANSFORM_H_

#include "SvgUtil.h"

class SvgTransform {
friend SvgTransform;
public:
protected:
	float	m_matrix[3][2];		//２次元変換用の変換行列	matrix[横index][縦index]
public:
	//コンストラクタ
	SvgTransform() {};
	SvgTransform(const SvgTransform *from);
	//解析
	PARSE_RESULT parse(const char *attribute);
	//乗算？
	void mul(const SvgTransform *t);
	//座標変換
	void trans_xy(float x, float y, float *out_x, float *out_y) const;
	//恒等変換かどうか判定
	bool is_identity() const;
	//デバッグ表示
	void debug_print();
protected:
	//translate(x,y)の解析
	PARSE_RESULT parse_translate(const char *attribute, const char **next_addr);
	//matrix(f,f,f,f,f,f)の解析
	PARSE_RESULT parse_matrix(const char *attribute, const char **next_addr);
	//scale(x,y)の解析
	PARSE_RESULT parse_scale(const char *attribute, const char **next_addr);

};

#endif
