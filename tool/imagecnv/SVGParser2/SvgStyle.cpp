#include "stdafx.h"
#include "SvgParser.h"
#include "SvgStyle.h"
#include "SvgUtil.h"

SvgStyle::SvgStyle()
{
	//初期値設定　SVG仕様書参照
	m_display = SVGDISPLAY_OTHER;	//初期値は表示
	//
	m_fill_enable = true;
	m_fill.rgb.r = 0;
	m_fill.rgb.g = 0;
	m_fill.rgb.b = 0;
	m_fill.ref_obj = NULL;
	m_fill_opacity = 1.0f;
	if (g_SVGPARSER_COMPATIBLE_GENSKETCH_EVENODD) {
		m_fill_rule = SVGFILLRULE_EVENODD;	//NONZEROが仕様としては正しいがGENSKETCHがこちらがデフォルトなのであわせる
	} else {
		m_fill_rule = SVGFILLRULE_NONZERO;
	}
	//
	m_stroke_enable = false;
	m_stroke.rgb.r = 0;
	m_stroke.rgb.g = 0;
	m_stroke.rgb.b = 0;
	m_stroke.ref_obj = NULL;
	m_stroke_width = 1.0f;
	m_stroke_linecap = SVGLINECAP_BUTT;
	m_stroke_linejoin = SVGLINEJOIN_MITER;
	m_stroke_opacity = 1.0f;
	m_stroke_miter_limit = 4.0f;
	//
	m_stop_color.r = 0;
	m_stop_color.g = 0;
	m_stop_color.b = 0;
	m_stop_opacity = 1.0f;
}

void SvgStyle::copy_from(const SvgStyle *src)
{
	//初期値設定　SVG仕様書参照
	m_display = src->display();	//初期値は表示
	//
	m_fill_enable = src->fill_enable();
	m_fill = *src->fill();
	m_fill_opacity = src->fill_opacity();
	m_fill_rule = src->fill_rule();
	//
	m_stroke_enable = src->stroke_enable();
	m_stroke = *src->stroke();
	m_stroke_width = src->stroke_width();
	m_stroke_linecap = src->stroke_linecap();
	m_stroke_linejoin = src->stroke_linejoin();
	m_stroke_opacity = src->stroke_opacity();
	m_stroke_miter_limit = src->stroke_miter_limit();
	//
	m_stop_color = *src->stop_color();
	m_stop_opacity = src->stop_opacity();
}
static const char *find_style_separator(const char *p)
{
	while (*p && *p != ':' && *p != ';') {
		p++;
	}

	return p;
}

//style属性の解析
PARSE_RESULT SvgStyle::parse_style(SvgParser *parser, SvgObject *parent, const char *attr)
{
	char			name[256];
	char			val[256];
	const char		*att[2];
	const char		*ptr1, *ptr2;
	PARSE_RESULT	ret = PARSED;

	//name:val;name:val;...からname,valに分割して解析
	ptr1 = attr;
	while (*ptr1 != '\0') {
		//name
		ptr2 = find_style_separator(ptr1);
		strncpy_s(name, numof(name), ptr1, (ptr2 - ptr1));
		//val
		if (*ptr2 == ':') {
			ptr1 = ptr2 + 1;
			ptr2 = find_style_separator(ptr1);
			strncpy_s(val, numof(val), ptr1, (ptr2 - ptr1));
		} else {
			val[0] = '\0';
		}
		//解析
		SVG_DPRINTF("style:%s=%s\n", name, val);
		att[0] = name;
		att[1] = val;
		if (parse_attribute(parser, parent, att) < 0) {
			ret = PARSE_ERROR;
		}
		//next
		ptr1 = ptr2;
		if (*ptr1 != '\0') {
			ptr1++;
		}
	}

	return ret;
}

PARSE_RESULT SvgStyle::parse_attribute(SvgParser *parser, SvgObject *parent, const char *att[])
{
	if (!strcmp(att[0], "display")) {
		return parse_display(att[1], &m_display);
	} else
	if (!strcmp(att[0], "opacity")) {
		m_fill_enable = true;
		m_fill_opacity = (float)atof(att[1]);
		m_stroke_opacity = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "fill")) {
		return parse_paint(parser, parent, att[1], &m_fill, &m_fill_enable);
	} else
	if (!strcmp(att[0], "fill-opacity")) {
		m_fill_opacity = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "fill-rule")) {
		return parse_fillrule(att[1], &m_fill_rule);
	} else
	if (!strcmp(att[0], "stroke")) {
		return parse_paint(parser, parent, att[1], &m_stroke, &m_stroke_enable);
	} else
	if (!strcmp(att[0], "stroke-opacity")) {
		m_stroke_opacity = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "stroke-width")) {
		m_stroke_width = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "stroke-linecap")) {
		return parse_linecap(att[1], &m_stroke_linecap);
	} else
	if (!strcmp(att[0], "stroke-linejoin")) {
		return parse_linejoin(att[1], &m_stroke_linejoin);
	} else
	if (!strcmp(att[0], "stroke-miterlimit")) {
		m_stroke_miter_limit = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "stop-color")) {
		return parse_color(att[1], &m_stop_color);
	} else
	if (!strcmp(att[0], "stop-opacity")) {
		m_stop_opacity = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "stop-dasharray")) {
		//ダッシュは対応できていないのでエラーとする
		return PARSE_ERROR;
	} else
	{
		//不明な属性は無視する
		return NOT_PARSED;
	}
}

PARSE_RESULT SvgStyle::parse_paint(SvgParser *parser, SvgObject *parent, const char *str, SVGPAINT *paint, bool *enable)
{
	if (*str == '#') {
		//#RRGGBB
		*enable = true;
		return parse_color(str, &paint->rgb);
	} else
	if (!strncmp(str, "url(#", 5)) {
		*enable = true;
		return parse_url(parser, parent, str, &paint->ref_obj);
	} else
	if (!strcmp(str, "none")) {
		*enable = false;
		return PARSED;
	} else
	{
		//Error
		return PARSE_ERROR;
	}
}

inline static int c2hex(char c)
{
	if (c >= '0' && c <= '9') return	(c - '0');
	if (c >= 'a' && c <= 'f') return	(c - 'a' + 10);
	return (c - 'A' + 10);	//無効な文字は考慮しない
}

PARSE_RESULT SvgStyle::parse_color(const char *str, SVGRGB *rgb)
{
	//#RRGGBB以外は非対応
	if (strlen(str) != 7) {
		fprintf(stderr, "ERROR: unknown color value %s\n", str);
		return PARSE_ERROR;
	}
	//解析
	rgb->r = c2hex(str[1]) * 16 + c2hex(str[2]);
	rgb->g = c2hex(str[3]) * 16 + c2hex(str[4]);
	rgb->b = c2hex(str[5]) * 16 + c2hex(str[6]);

	return PARSED;
}

PARSE_RESULT SvgStyle::parse_url(SvgParser *parser, SvgObject *parent, const char *str, SvgObject **ref_obj)
{
	str += 5;	//skip "url(#"
	const char *end = strchr(str, ')');
	if (end == NULL) {
		return PARSE_ERROR;
	}

	char url[256];
	strncpy_s(url, numof(url), str, (end - str));

	SvgObject *obj = parser->find_defs(url);
	if (obj == NULL) {
		fprintf(stderr, "Can't find url %s\n", url);
		return PARSE_ERROR;
	}
	//参照カウントを増加させる
	obj->add_ref_count();
	//参照元オブジェクト設定
	obj->set_referred_object(parent);

	*ref_obj = obj;

	return PARSED;
}

PARSE_RESULT SvgStyle::parse_display(const char *str, SVGDISPLAY *display)
{
	if (!strcmp(str, "none")) {
		*display = SVGDISPLAY_NONE;
		return PARSED;
	} else
	{
		*display = SVGDISPLAY_OTHER;
		return PARSED;
	}
}

PARSE_RESULT SvgStyle::parse_linecap(const char *str, SVGLINECAP *cap)
{
	if (!strcmp(str, "butt")) {
		*cap = SVGLINECAP_BUTT;
		return PARSED;
	} else
	if (!strcmp(str, "round")) {
		*cap = SVGLINECAP_ROUND;
		return PARSED;
	} else
	if (!strcmp(str, "square")) {
		*cap = SVGLINECAP_SQUARE;
		return PARSED;
	} else
	{
		//不明な形状
		return PARSE_ERROR;
	}
}

PARSE_RESULT SvgStyle::parse_linejoin(const char *str, SVGLINEJOIN *join)
{
	if (!strcmp(str, "miter")) {
		*join = SVGLINEJOIN_MITER;
		return PARSED;
	} else
	if (!strcmp(str, "round")) {
		*join = SVGLINEJOIN_ROUND;
		return PARSED;
	} else
	if (!strcmp(str, "bevel")) {
		*join = SVGLINEJOIN_BEVEL;
		return PARSED;
	} else
	{
		//不明な形状
		return PARSE_ERROR;
	}
}

PARSE_RESULT SvgStyle::parse_fillrule(const char *str, SVGFILLRULE *rule)
{
	if (!strcmp(str, "nonzero")) {
		*rule = SVGFILLRULE_NONZERO;
		return PARSED;
	} else
	if (!strcmp(str, "evenodd")) {
		*rule = SVGFILLRULE_EVENODD;
		return PARSED;
	} else
	{
		//不明な形状
		return PARSE_ERROR;
	}
}
