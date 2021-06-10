/*************************************************************************/
/**
 * @file      gemng_api.h
 * @brief     GEMNG 内部ヘッダ
 * @date      2011/10/12 新規作成
 * @copyright Panasonic Co.,Ltd.
 * @author    桝田
 *************************************************************************/
#ifndef __GEMNG_LOCAL_H__
#define __GEMNG_LOCAL_H__

/***************************************************************
                    インクルードファイル
***************************************************************/
#define _DMPNATIVE_

//#include <common.h>
#include "geman.h"
#include "ext_DrvCKGEN.h"
#include "EGL/egl.h"
#include "dmpallocator/dmp_allocator.h"
#include "oswrapper/os_wrapper.h"
#include "DMP/eglNative.h"
/***************************************************************
                        マクロ定義
***************************************************************/
#define UNUSED_VARIABLE(x)\
{\
	void *a;\
	a = (void*)x;\
}\

extern eDRV_ERR eLdCKGEN_ChangePll(sDRV_CKGEN_PLL_SELECT *psPllSel);


/* GEクロック制御 */
#define	GE_CLOCK_START()	do {mCKGEN_START_GEVG1_CK(); mCKGEN_START_GEVG2_CK();} while(0)
#define	GE_CLOCK_STOP()		do {mCKGEN_STOP_GEVG1_CK(); mCKGEN_STOP_GEVG2_CK();} while(0)

/* GEリセット制御 */
#define mRST_GE_ENABLE()	(unCKG_SFTRST2_ASM &= 0xfffb)
#define mRST_GE_DISABLE()	(unCKG_SFTRST2_ASM |= 0x0004)
#define GE_SFTRST_DISABLE()	do {mRST_GE_DISABLE();} while(0)
#define GE_SFTRST_ENABLE()	do {mRST_GE_ENABLE(); } while(0)


/***************************************************************
                        型定義
***************************************************************/
/***************************************************************
                        構造体
***************************************************************/

/***************************************************************
                        プロトタイプ宣言
***************************************************************/


#endif /* __GEMNG_LOCAL_H__ */
