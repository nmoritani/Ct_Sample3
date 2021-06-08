/**
 *  Copyright (c) 2009 Copyright(c) 2018 Persol AVC Technology.
 *
 *  @brief      GUI �f�o�b�O�v�����g �w�b�_�t�@�C��
 */
#ifndef __CT_DEBUG_PRINT_H__
#define __CT_DEBUG_PRINT_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "CtAssert.h"
#include "SysIf.h"

#define CtLog			0xF0000000		// �V�X�e�������[�X�łł��o��
#define CtDt			0x0F000000		// Date�o�͂���
#define CtLogDt			CtLog | CtDt	// �V�X�e�������[�X�łł�Date�o��
#define CtDbg			0x00000001		// �ʏ�Debug�p
#define CtDbgDt			CtDbg | CtDt	// �ʏ�Debug��Date�o��
#define CtDbgIdCmd		0x00000002		// DebugCommand�o�͗p
/*
*    CtDebugPrint()
*/
#if defined CT_DEBUG_PRINT_FUNC
	void CtDebug(unsigned long int id, const char *funcname, int linenum, const char *fmt, ...);

	/* �֐����̂� */
	#define CtDebugPrint(id, fmt, ...)		CtDebug(id, __PRETTY_FUNCTION__, __LINE__, fmt, ##__VA_ARGS__);
#else
	void CtDebug(unsigned long int id, const char *idname, const char *fmt, ...);

	/* ������̂ݕ\�� */
	#define CtDebugPrint(id, fmt, ...)		CtDebug(id, #id, fmt, ##__VA_ARGS__);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __CT_DEBUG_PRINT_H__ */
