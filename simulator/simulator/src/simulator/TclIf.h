/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   TCL�u���b�N �w�b�_�[�t�@�C�� (�V�~�����[�^�[�p)
 */
#ifndef _TCL_IF_H_
#define _TCL_IF_H_

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#include "SysIf.h"
	
//�G���[��`
typedef enum tcl_err {
	TCL_ER_OK = 0,
	TCL_ER_NG,
	TCL_ER_INVALID,						/* �l���� �ˁu���v�\��,���APb��OSD�\��,HDMI-TC�p */
	TCL_ER_CANCEL,						/* �L�����Z���ʒm�p */
	TCL_ER_CONTINUE						/* ���������p �����p���w�� */
} TCL_ER;

	
TCL_ER TCL_GetDateTimeDelay(SYS_DATE_TIME *pValue, W delay );

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* _TCL_IF_H_ */
