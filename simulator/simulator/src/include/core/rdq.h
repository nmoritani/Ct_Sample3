/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  rdq.h
 * @brief %jp{���f�B�[�L���[�I�u�W�F�N�g�̃w�b�_�t�@�C��}%en{ready-queue object heder file}
 *
 * Copyright (C) 1998-2008 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef __HOS_V4a__knl_rdq_h__
#define __HOS_V4a__knl_rdq_h__


#if _KERNEL_RDQ_ALGORITHM == _KERNEL_RDQ_ALG_SINGLE_QUE


/* ------------------------------------------ */
/*             single queue                   */
/* ------------------------------------------ */


/** %en{ready-queue control block}%jp{���f�B�[�L���[�Ǘ��u���b�N} */
typedef struct _kernel_t_rdqcb
{
	_KERNEL_T_QUE	que;
} _KERNEL_T_RDQCB;


#define _KERNEL_CRE_RDQ(rdqcb)			_KERNEL_CRE_QUE(&(rdqcb)->que)				/**< %en{create ready-queue}%jp{���f�B�[�L���[�̐���} */
#define _KERNEL_DEL_RDQ(rdqcb)			_KERNEL_DEL_QUE(&(rdqcb)->que)				/**< %en{delete ready-queue}%jp{���f�B�[�L���[�̍폜} */

#define _KERNEL_ADD_RDQ(rdqcb, tskhdl)	_KERNEL_ADP_QUE(&(rdqcb)->que, (tskhdl))	/**< %jp{�^�X�N�����f�B�[�L���[�ɒǉ�} */
#define _KERNEL_RMV_RDQ(rdqcb, tskhdl)	_KERNEL_RMV_QUE(&(rdqcb)->que, (tskhdl))	/**< %jp{�^�X�N�����f�B�[������O��} */

#define _KERNEL_RMH_RDQ(rdqcb)			_KERNEL_RMH_QUE(&(rdqcb)->que)				/**< %jp{�L���[�̐擪�^�X�N�̎��O��} */
#define _KERNEL_REF_RDQ(rdqcb)			_KERNEL_REF_QUE(&(rdqcb)->que)				/**< %jp{�L���[�̐擪�^�X�N�̎Q��} */

#define _KERNEL_ROT_RDQ(rdqcb, tskpri)	_KERNEL_RTP_QUE(&(rdqcb)->que, (tskpri))	/**< %jp{���f�B�[�L���[�̉�]} */


#elif _KERNEL_RDQ_ALGORITHM == _KERNEL_RDQ_ALG_ARRAYED_QUE

/* ------------------------------------------ */
/*               arrayed que                  */
/* ------------------------------------------ */

/** %en{ready-queue control block}%jp{���f�B�[�L���[�Ǘ��u���b�N} */
typedef struct _kernel_t_rdqcb
{
	_KERNEL_T_QUE	que[_KERNEL_TSK_TMAX_TPRI];
} _KERNEL_T_RDQCB;


#define _KERNEL_CRE_RDQ(rdqcb)			_kernel_cre_rdq((rdqcb))					/**< %jp{���f�B�[�L���[�̐���}%en{create ready-queue} */
#define _KERNEL_DEL_RDQ(rdqcb)			_kernel_del_rdq((rdqcb))					/**< %jp{���f�B�[�L���[�̍폜}%en{delete ready-queue} */

#define _KERNEL_ADD_RDQ(rdqcb, tskhdl)	_kernel_add_rdq((rdqcb), (tskhdl))			/**< %jp{�^�X�N�����f�B�[�L���[�ɒǉ�} */
#define _KERNEL_RMV_RDQ(rdqcb, tskhdl)	_kernel_rmv_rdq((rdqcb), (tskhdl))			/**< %jp{�^�X�N�����f�B�[������O��} */

#define _KERNEL_RMH_RDQ(rdqcb)			_kernel_rmh_rdq((rdqcb))					/**< %jp{�L���[�̐擪�^�X�N�̎��O��} */
#define _KERNEL_REF_RDQ(rdqcb)			_kernel_ref_rdq((rdqcb))					/**< %jp{�L���[�̐擪�^�X�N�̎Q��} */

#define _KERNEL_ROT_RDQ(rdqcb, tskpri)	_kernel_rot_rdq((rdqcb), (tskpri))			/**< %jp{���f�B�[�L���[�̉�]} */


#ifdef __cplusplus
extern "C" {
#endif

void             _kernel_cre_rdq(_KERNEL_T_RDQCB *rdqcb);							/**< %jp{���f�B�[�L���[�̐���}%en{create ready-queue} */
void             _kernel_del_rdq(_KERNEL_T_RDQCB *rdqcb);							/**< %jp{���f�B�[�L���[�̍폜}%en{delete ready-queue} */

void             _kernel_add_rdq(_KERNEL_T_RDQCB *rdqcb, _KERNEL_T_TSKHDL tskhdl);	/**< %jp{�^�X�N�����f�B�[�L���[�ɒǉ�} */
void             _kernel_rmv_rdq(_KERNEL_T_RDQCB *rdqcb, _KERNEL_T_TSKHDL tskhdl);	/**< %jp{�^�X�N�����f�B�[�L���[������O��} */

_KERNEL_T_TSKHDL _kernel_rmh_rdq(_KERNEL_T_RDQCB *rdqcb);							/**< %jp{���f�B�[�L���[�̐擪�^�X�N�̎��O��} */
_KERNEL_T_TSKHDL _kernel_ref_rdq(_KERNEL_T_RDQCB *rdqcb);							/**< %jp{���f�B�[�L���[�̐擪�^�X�N�̎Q��} */

void             _kernel_rot_rdq(_KERNEL_T_RDQCB *rdqcb, PRI tskpri);				/**< %jp{���f�B�[�L���[�̉�]} */

#ifdef __cplusplus
}
#endif



#else	/* error */

#error Illegal value : _KERNEL_QUE_ALGORITHM

#endif



#endif	/* __HOS_V4a__knl_que_h__ */



/* end of file */
