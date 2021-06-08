/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   itron.h のラッパー (シミュレーター用)
 */
#ifndef __ITRON_H__
#define __ITRON_H__

#include "win_itron.h"

/**
 *  itron4 では下記システムコールが msg → mbx と改名されているが、シミュレーターで使っている win 用のライブラリでは
 *  追従できていないらしくシステムコール名が msg のままなのでここで対応する
 */
#define snd_mbx(...)	snd_msg(__VA_ARGS__)
#define rcv_mbx(...)	rcv_msg(__VA_ARGS__)

/* wiのヘッダにNULL定義が存在しないため追加 */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif	/* __ITRON_H__ */
