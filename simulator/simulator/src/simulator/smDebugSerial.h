/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   smDebugSerial (�V�~�����[�^�[�p�Ȃ̂ŁA�V���A���̕ς��ɏo�̓E�B���h�E�ɏo��)
 */
#ifndef __SM_DEBUG_SERIAL__
#define __SM_DEBUG_SERIAL__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

unsigned char smDebugPrintf(int dmyLevel, const char *format, ...);

#define SMDEBUG_LOGOUT_DT(Format, ...)

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __SM_DEBUG_SERIAL__ */
