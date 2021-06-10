#if 0
/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_pool.h

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     �V�K�쐬(AVFW���p)
 ******************************************************************************/

#ifndef _MEM_MNG_H_
#define _MEM_MNG_H_

// ----------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------
#include "ext_gevg_malloc.h"


// ----------------------------------------------------------------------
// �^��`
// ----------------------------------------------------------------------
typedef signed long		MEM_ER;
typedef signed long		MEM_ER_ID;
typedef void 			*MEM_VP;
typedef void			*MEM_ID;
typedef unsigned char	MEM_ATR;

// ----------------------------------------------------------------------
// �萔��`
// ----------------------------------------------------------------------
#define MEM_E_OK		(0)
#define MEM_E_ID		(-1)
#define MEM_E_PAR		(-2)
#define MEM_E_TMOUT		(-3)

#define MEM_TA_TFIFO	(0x01)		// �b��

#ifndef	NULL
#define	NULL			(0)
#endif

// ----------------------------------------------------------------------
// �}�N����`
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// �\���̒�`
// ----------------------------------------------------------------------
// �������v�[���������
typedef struct MEM_T_CMPF {
    MEM_ATR			mpfatr;
    unsigned long	blkcnt;
    unsigned long	blksz;
    MEM_VP			mpf;
} MEM_T_CMPF;

// �������v�[���ݒ�p�\����
typedef struct _SMemMngPool { /* pgr1232 */
    unsigned long	m_uiBlkSize;   // �������u���b�N�̃T�C�Y
    unsigned long	m_uiBlkNum;    // �������u���b�N�̐�
    unsigned long	m_uiMinSize;   // �{�v�[�����g�p���鉺���T�C�Y
    unsigned long	m_uiMaxSize;   // �{�v�[�����g�p�������T�C�Y
    unsigned long	m_ulPeakSize;  // �{�v�[�����擾�����ő�T�C�Y(for Debug)
    unsigned long	m_ulUseNum;    // �{�v�[���Ŏg�p���̐�(for Debug)
    unsigned long	m_ulPeakNum;   // �{�v�[�����擾�����ő�T�C�Y(for Debug)
    unsigned long	m_ulFail;      // �{�v�[�����擾���s������(for Debug)
    unsigned long	m_ulOtherSize; // �{�v�[�����擾���s������(for Debug)
} SMemMngPool;

// �������v�[���Ǘ��p�\����
typedef struct _SMemMngPoolMng { /* pgr1232 */
    SMemMngPool m_tPoolData;  // �������v�[���̃f�[�^
    MEM_ID m_Id;              // �������v�[����ID�ԍ�(���s�V�X�e���ł�pStartAddr)
    MEM_VP m_pStartAddr;      // �������v�[���̐擪�A�h���X
    MEM_VP m_pEndAddr;        // �������v�[���̏I�[�A�h���X
} SMemMngPoolMng;


// ----------------------------------------------------------------------
// �ϐ��錾(extern)
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// �֐��v���g�^�C�v�錾
// ----------------------------------------------------------------------
MEM_ER tkmem_mng_acre_mpf(MEM_T_CMPF *pk_cmpf, MEM_ID* id);
MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid);
MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk);
MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk);

#endif /* _MEM_POOL_H_ */

/*****************************************************************************/
/* Copyright (C) 2011 Panasonic Corporation.                                 */
/*****************************************************************************/
#endif
