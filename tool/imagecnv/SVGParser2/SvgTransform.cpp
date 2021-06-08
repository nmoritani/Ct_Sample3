#include "stdafx.h"
#include "SvgTransform.h"
#include "SvgUtil.h"

SvgTransform::SvgTransform(const SvgTransform *from)
{
	m_matrix[0][0] = from->m_matrix[0][0];
	m_matrix[0][1] = from->m_matrix[0][1];
	m_matrix[1][0] = from->m_matrix[1][0];
	m_matrix[1][1] = from->m_matrix[1][1];
	m_matrix[2][0] = from->m_matrix[2][0];
	m_matrix[2][1] = from->m_matrix[2][1];
}

PARSE_RESULT SvgTransform::parse(const char *attribute)
{
	PARSE_RESULT r;
	if (!strncmp(attribute, "translate", 9)) {
		r = parse_translate(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	if (!strncmp(attribute, "matrix", 6)) {
		r = parse_matrix(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	if (!strncmp(attribute, "scale", 5)) {
		r = parse_scale(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	{
		//Unknown
		fprintf(stderr, "Unknown transform value '%s'\n", attribute);
		return PARSE_ERROR;
	}
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//transformが複数指定されている場合は未対応のためエラーとする
	if (*attribute != '\0') {
		return PARSE_ERROR;
	}

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_translate(const char *attribute, const char **next_addr)
{
	float	x, y;

	//translateの部分を飛ばす
	attribute += 9;
	//'('を探す
	attribute = svgutil_skip_to_char(attribute, '(');
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//数値変換
	x = (float)strtod(attribute, (char**)&attribute);
	//次の数値まで飛ばす
	attribute = svgutil_skip_to_next_token(attribute);
	//数値変換
	y = (float)strtod(attribute, (char**)&attribute);
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//')'チェック
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'を飛ばす
	attribute++;
	//行列に設定
	m_matrix[0][0] = 1;
	m_matrix[0][1] = 0;
	m_matrix[1][0] = 0;
	m_matrix[1][1] = 1;
	m_matrix[2][0] = x;
	m_matrix[2][1] = y;
	//
	SVG_DPRINTF("translae: %f, %f\n", x, y);
	//次の文字の場所を返す
	*next_addr = attribute;

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_matrix(const char *attribute, const char **next_addr)
{
	int	line, column;

	//matrixの部分を飛ばす
	attribute += 6;
	//'('を探す
	attribute = svgutil_skip_to_char(attribute, '(');
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//行列データ取得
	for (column = 0; column < 3; column++) {
		for (line = 0; line < 2; line++) {
			//数値変換
			m_matrix[column][line] = (float)strtod(attribute, (char**)&attribute);
			//次の数値まで飛ばす
			attribute = svgutil_skip_to_next_token(attribute);
		}
	}
	//')'チェック
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'を飛ばす
	attribute++;
	//
	SVG_DPRINTF("matrix: %f, %f, %f, %f, %f, %f\n",
				m_matrix[0][0], m_matrix[0][1], m_matrix[1][0], m_matrix[1][1], 
				m_matrix[2][0], m_matrix[2][1]);
	//次の文字の場所を返す
	*next_addr = attribute;

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_scale(const char *attribute, const char **next_addr)
{
	float	x, y;

	//scaleの部分を飛ばす
	attribute += 5;
	//'('を探す
	attribute = svgutil_skip_to_char(attribute, '(');
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//数値変換
	x = (float)strtod(attribute, (char**)&attribute);
	//次の数値まで飛ばす
	attribute = svgutil_skip_to_next_token(attribute);
	//数値変換
	y = (float)strtod(attribute, (char**)&attribute);
	//空白を飛ばす
	attribute = svgutil_skip_space(attribute);
	//')'チェック
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'を飛ばす
	attribute++;
	//行列に設定
	m_matrix[0][0] = x;
	m_matrix[0][1] = 0;
	m_matrix[1][0] = 0;
	m_matrix[1][1] = y;
	m_matrix[2][0] = 0;
	m_matrix[2][1] = 0;
	//
	SVG_DPRINTF("scale: %f, %f\n", x, y);
	//次の文字の場所を返す
	*next_addr = attribute;

	return PARSED;
}

/* 行列計算(２次元計算に特化) */
inline static void matrix_mul(const float m1[3][2], const float m2[3][2], float out[3][2])
{
	out[0][0] = m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1];
	out[0][1] = m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1];
	out[1][0] = m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1];
	out[1][1] = m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1];
	out[2][0] = m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0];
	out[2][1] = m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1];
}

//右から掛ける
void SvgTransform::mul(const SvgTransform *t)
{
	float	tmp[3][2];
	matrix_mul(m_matrix, t->m_matrix, tmp);		//arg1 * arg2 -> arg3
	memcpy(m_matrix, tmp, sizeof(m_matrix));
}

//座標変換
void SvgTransform::trans_xy(float x, float y, float *out_x, float *out_y) const
{
	*out_x = m_matrix[0][0] * x + m_matrix[1][0] * y + m_matrix[2][0];
	*out_y = m_matrix[0][1] * x + m_matrix[1][1] * y + m_matrix[2][1];
}

//恒等変換かどうか判定
bool SvgTransform::is_identity() const
{
	if (m_matrix[0][0] == 1.0f && m_matrix[1][0] == 0.0f && m_matrix[2][0] == 0.0f && 
		m_matrix[0][1] == 0.0f && m_matrix[1][1] == 1.0f && m_matrix[2][1] == 0.0f) {
		return true;
	}

	return false;
}


//デバッグ表示
void SvgTransform::debug_print()
{
#if SVGDEBUGOUT
	SVG_DPRINTF(" %f, %f %f\n", m_matrix[0][0], m_matrix[1][0], m_matrix[2][0]);
	SVG_DPRINTF(" %f, %f %f\n", m_matrix[0][1], m_matrix[1][1], m_matrix[2][1]);
#endif
}

