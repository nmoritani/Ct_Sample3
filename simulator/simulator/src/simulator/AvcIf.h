/**
 *	Copyright (c) 2008-2009 Matsushita Electric Industrial Co., Ltd.
 *	$Id$
 *
 *	@file
 *	@brief
 */

#ifndef __AVC_H__
#define __AVC_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <itron.h>
#include <kernel.h>
#include <kernel_id.h>

typedef	enum _AVC_ER_ {
	AVC_ER_OK	= 0,
	AVC_ER_PARAM,
	AVC_ER_CALL_NEXT_FIELD
} AVC_ER;


typedef	AVC_ER	(*AVDF_CALLBACK)(VP);
AVC_ER	AVDF_AddCallback(AVDF_CALLBACK p_CbAdr, VP vp_Param, BOOL bl_ExeOnBlank);

#ifdef	__cplusplus
}
#endif // __cplusplus

#endif // __AVC_H__
