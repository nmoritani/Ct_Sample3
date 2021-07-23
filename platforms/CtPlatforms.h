/**
*	Copyright (c) 2018  Persol AVC Technorogy, All rights reserved
*	$Id$
*
*	@file
*	@brief	CtPlatforms.h
*/

#ifndef __CTPLATFORMS_H__
#define __CTPLATFORMS_H__

#include <system_wrapper.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if 0
typedef char    B;
typedef short   H;
typedef long    W;

typedef unsigned char   UB;
typedef unsigned short  UH;
typedef unsigned long   UW;

typedef char    VB;
typedef short   VH;
typedef long    VW;

typedef	int				ID;				//!< ID�ԍ�.
typedef	int				ER;				//!< �G���[�R�[�h.
typedef int				INT;			//!< �����t������.
typedef unsigned int	UINT;			//!< ������������.

typedef unsigned int	FLGPTN;
#endif
	
typedef int BOOL;
#define TRUE	1
#define FALSE	0

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL	0
#endif
	
#define APL_MAIN_TSKPRI		120
#define GUI_TSKPRI			70
#define CT_MAIN_TSKPRI		118	/* ��APL�`��^�X�N�Ɠ����x */
#define CT_DRAW_TSKPRI      46 /* 40����ύX STC��艺�� */


extern syswrap_cyclic_handler_t ct_cyclic_handler;

extern syswrap_memorypool_t	ct_mempool_fast;
extern syswrap_memorypool_t ct_mempool_normal;
	
extern void Ct_Init();
extern void Ct_Term();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* __CTPLATFORMS_H__ */


