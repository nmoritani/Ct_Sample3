#ifndef _SVGUTIL_H_
#define _SVGUTIL_H_

#define SVGDEBUGOUT		0

#if SVGDEBUGOUT
 #define SVG_DPRINTF(fmt, ...)	printf(fmt, __VA_ARGS__)
 #define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
 #define SVG_DPRINTF(fmt, ...)
 #define NEW  new
#endif

#define numof(a)	(sizeof(a)/sizeof((a)[0]))

//属性解析の戻り値
typedef enum {
	PARSED,
	NOT_PARSED,
	PARSE_ERROR
} PARSE_RESULT;

//コマンド 絶対・相対をセットで登録すること
typedef enum {
	SVG_CMD_M,
	SVG_CMD_m,
	SVG_CMD_Z,
	SVG_CMD_z,
	SVG_CMD_L,
	SVG_CMD_l,
	SVG_CMD_H,
	SVG_CMD_h,
	SVG_CMD_V,
	SVG_CMD_v,
	SVG_CMD_C,
	SVG_CMD_c,
	SVG_CMD_S,
	SVG_CMD_s,
	SVG_CMD_Q,
	SVG_CMD_q,
	SVG_CMD_T,
	SVG_CMD_t,
	SVG_CMD_A,
	SVG_CMD_a,
	SVG_CMD_MAX
} SVG_CMD;

class SvgObject;
class SvgStop;
class SvgStyle;

typedef vector<float>		SVGCOORDS;
typedef vector<SVG_CMD>		SVGCMDS;
typedef vector<SvgObject*>	SVGOBJECTLIST;
typedef vector<SvgStop*>	SVGSTOPS;
typedef map<string,SvgStyle*>	SVGSTYLEMAP;

extern const int m_coords_num_table[];
extern const char m_svg_cmd_str[];

template<class T, class U>
inline T svgutil_skip_to_char(T p, U c)
{
	while(*p) {
		if (*p == c) {
			p++;
			return p;
		}
		p++;
	}
	return p;
}

template<class T>
inline T svgutil_skip_space(T p)
{
	while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
		p++;
	}
	return p;
}

template<class T>
inline T svgutil_skip_to_next_token(T p)
{
	//空白を飛ばす
	p = svgutil_skip_space(p);
	//','なら飛ばす
	if (*p == ',') {
		p++;
		//,の後の空白を飛ばす
		p = svgutil_skip_space(p);
	}
	return p;
}

inline bool svgutil_is_num_start(char c)
{
	if (c == '-' || (c >= '0' && c <= '9')) {
		return true;
	}
	return false;
}

inline int svgutil_cmd_coords_num(SVG_CMD cmd) {
	return m_coords_num_table[cmd];
}

inline char svgutil_cmd_str(SVG_CMD cmd) {
	return m_svg_cmd_str[cmd];
}

inline float svgutil_bezier_control_point(float n) {
	return n * ((4 * (1.4142135623731f - 1)) / 3);
}

inline bool svgutil_is_cmd_relative(SVG_CMD cmd) {
	return ((cmd & 1) != 0);
}

inline SVG_CMD svgutil_cmd_cnv_to_abs(SVG_CMD cmd) {
	return (SVG_CMD)(cmd & ~1);
}

#endif
