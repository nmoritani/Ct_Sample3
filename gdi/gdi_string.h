/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#ifndef __GDI_STRING_H__
#define __GDI_STRING_H__

typedef enum {
#include "../string/str_id.def"
	STRING_ID_INVALID,
	STRING_ID_0001 = 0,		/* �폜�\�� */
	STRING_ID_0002 = 0,		/* �폜�\�� */
	STRING_ID_0003 = 0,		/* �폜�\�� */
	STRING_ID_0004 = 0,		/* �폜�\�� */
} GDI_STRING_ID;

#endif
