/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	Comfortable Toolkit Header
 */

#ifndef __Ct_H__
#define __Ct_H__

#include <stdio.h>
#include <string.h>

#include "CtType.h"
#include "CtConfig.h"

inline CtScreenSel toSelScreen(int no) {
	return (CtScreenSel)(1 << no);
}
inline int toNoScreen(CtScreenSel sel)	{
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (sel & (1<<i))
			return i;
	}
	return 0;
}

#endif
