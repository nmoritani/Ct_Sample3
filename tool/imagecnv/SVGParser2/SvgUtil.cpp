#include "stdafx.h"
#include "SvgUtil.h"


const int m_coords_num_table[] = {
	2,		//SVG_CMD_M
	2,		//SVG_CMD_m
	0,		//SVG_CMD_Z
	0,		//SVG_CMD_z
	2,		//SVG_CMD_L
	2,		//SVG_CMD_l
	1,		//SVG_CMD_H
	1,		//SVG_CMD_h
	1,		//SVG_CMD_V
	1,		//SVG_CMD_v
	6,		//SVG_CMD_C
	6,		//SVG_CMD_c
	4,		//SVG_CMD_S
	4,		//SVG_CMD_s
	4,		//SVG_CMD_Q
	4,		//SVG_CMD_q
	2,		//SVG_CMD_T
	2,		//SVG_CMD_t
	7,		//SVG_CMD_A
	7		//SVG_CMD_a
};


const char m_svg_cmd_str[] = {
	'M',		//SVG_CMD_M
	'm',		//SVG_CMD_m
	'Z',		//SVG_CMD_Z
	'z',		//SVG_CMD_z
	'L',		//SVG_CMD_L
	'l',		//SVG_CMD_l
	'H',		//SVG_CMD_H
	'h',		//SVG_CMD_h
	'V',		//SVG_CMD_V
	'v',		//SVG_CMD_v
	'C',		//SVG_CMD_C
	'c',		//SVG_CMD_c
	'S',		//SVG_CMD_S
	's',		//SVG_CMD_s
	'Q',		//SVG_CMD_Q
	'q',		//SVG_CMD_q
	'T',		//SVG_CMD_T
	't',		//SVG_CMD_t
	'A',		//SVG_CMD_A
	'a'			//SVG_CMD_a
};


