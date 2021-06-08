#ifndef _SVGSTYLE_H_
#define _SVGSTYLE_H_

#include "SvgUtil.h"

class SvgParser;
class SvgObject;

typedef struct {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
} SVGRGB;

//fill,stroke
typedef struct {
	SVGRGB		rgb;
	SvgObject	*ref_obj;
} SVGPAINT;

typedef enum {
	SVGDISPLAY_NONE,
	SVGDISPLAY_OTHER,
	SVGDISPLAY_END,
} SVGDISPLAY;

typedef enum {
	SVGLINECAP_BUTT,
	SVGLINECAP_ROUND,
	SVGLINECAP_SQUARE,
	SVGLINECAP_END
} SVGLINECAP;

typedef enum {
	SVGLINEJOIN_MITER,
	SVGLINEJOIN_ROUND,
	SVGLINEJOIN_BEVEL,
	SVGLINEJOIN_END
} SVGLINEJOIN;

typedef enum {
	SVGFILLRULE_EVENODD,
	SVGFILLRULE_NONZERO,
	SVGFILLRULE_END
} SVGFILLRULE;

class SvgStyle {
public:
protected:
	SVGDISPLAY		m_display;
	bool			m_fill_enable;
	SVGPAINT		m_fill;
	float			m_fill_opacity;
	SVGFILLRULE		m_fill_rule;
	bool			m_stroke_enable;
	SVGPAINT		m_stroke;
	float			m_stroke_width;
	SVGLINECAP		m_stroke_linecap;
	SVGLINEJOIN		m_stroke_linejoin;
	float			m_stroke_opacity;
	float			m_stroke_miter_limit;
	SVGRGB			m_stop_color;
	float			m_stop_opacity;

public:
	SvgStyle();
	void copy_from(const SvgStyle *src);
	PARSE_RESULT parse_style(SvgParser *parser, SvgObject *parent, const char *attr);
	PARSE_RESULT parse_attribute(SvgParser *parser, SvgObject *parent, const char *att[]);
	PARSE_RESULT parse_paint(SvgParser *parser, SvgObject *parent, const char *str, SVGPAINT *paint, bool *enable);
	PARSE_RESULT parse_color(const char *str, SVGRGB *rgb);
	PARSE_RESULT parse_url(SvgParser *parser, SvgObject *parent, const char *str, SvgObject **ref_obj);
	PARSE_RESULT parse_display(const char *str, SVGDISPLAY *display);
	PARSE_RESULT parse_linecap(const char *str, SVGLINECAP *cap);
	PARSE_RESULT parse_linejoin(const char *str, SVGLINEJOIN *join);
	PARSE_RESULT parse_fillrule(const char *str, SVGFILLRULE *rule);
	//
	SVGDISPLAY display() const { return m_display; }
	bool fill_enable() const { return m_fill_enable; }
	const SVGPAINT *fill() const { return &m_fill; }
	float fill_opacity() const { return m_fill_opacity; }
	SVGFILLRULE fill_rule() const { return m_fill_rule; }
	bool stroke_enable() const { return m_stroke_enable; }
	const SVGPAINT *stroke() const { return &m_stroke; }
	float stroke_width() const { return m_stroke_width; }
	SVGLINECAP stroke_linecap() const { return m_stroke_linecap; }
	SVGLINEJOIN stroke_linejoin() const { return m_stroke_linejoin; }
	float stroke_opacity() const { return m_stroke_opacity; }
	const SVGRGB *stop_color() const { return &m_stop_color; }
	float stop_opacity() const { return m_stop_opacity; }
	float stroke_miter_limit() const { return m_stroke_miter_limit; }
};

#endif
