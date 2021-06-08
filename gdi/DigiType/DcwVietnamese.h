#ifndef __DCWVIETNAMESE_H

#include "DcwLayout.h"

#define IS_Vietnamese_NSMs(ch)	(((ch)==0x0300 || (ch)==0x0301 || (ch)==0x0303 || (ch)==0x0309 || (ch)==0x0323) ? 1 : 0)

DT16_ushort Latin_Vietnamese(DT16_ushort ch, DT16_ushort last_ch);

#endif
