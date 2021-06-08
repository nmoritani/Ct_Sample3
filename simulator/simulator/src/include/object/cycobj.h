/**
 *  Hyper Operating System V4 Advance
 *
 * @file  cycobj.h
 * @brief %jp{�����n���h���I�W�F�N�g�̃w�b�_�t�@�C��}%en{Cyclic Handler object heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__cycobj_h__
#define _KERNEL__object__cycobj_h__

#include "core/tmq.h"


/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */

/* %jp{�����n���h�������p�̌^} */
#if _KERNEL_CYCCB_BITFIELD		/* %jp{CYCCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

typedef unsigned int					_KERNEL_CYC_T_CYCATR;
typedef unsigned int					_KERNEL_CYCCB_T_CYCATR;
#define _KERNEL_CYCCB_TBITDEF_CYCATR	: 3

#else							/* %jp{CYCCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_CYC_T_CYCATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_CYCCB_T_CYCATR;
#define _KERNEL_CYCCB_TBITDEF_CYCATR

#endif

typedef RELTIM							_KERNEL_CYC_T_RELTIM;
typedef RELTIM							_KERNEL_CYCCB_T_RELTIM;
#define _KERNEL_CYCCB_TBITDEF_RELTIM

typedef VP_INT							_KERNEL_CYC_T_EXINF;
typedef VP_INT							_KERNEL_CYCCB_T_EXINF;
#define _KERNEL_CYCCB_TBITDEF_EXINF

typedef void (*_KERNEL_CYC_T_CYCHDR)(VP_INT exinf);
typedef void (*_KERNEL_CYCCB_T_CYCHDR)(VP_INT exinf);
#define _KERNEL_CYCCB_TBITDEF_CYCHDR



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_CYCCB_SPLIT_RO


/** %jp{�����n���h���R���g���[���u���b�N(���[�h�I�����[��)}%en{Cyclic Handler Control Block(read-only)} */
typedef struct _kernel_t_cyccb_ro
{
#if _KERNEL_CYCCB_CYCATR
	_KERNEL_CYCCB_T_CYCATR	cycatr		_KERNEL_CYCCB_TBITDEF_CYCATR;		/**< %jp{�����n���h������} */
#endif

#if _KERNEL_CYCCB_EXINF
	_KERNEL_CYCCB_T_EXINF	exinf		_KERNEL_CYCCB_TBITDEF_EXINF;		/**< %jp{�����n���h���̊g�����} */
#endif

#if _KERNEL_CYCCB_CYCHDR
	_KERNEL_CYCCB_T_CYCHDR	cychdr		_KERNEL_CYCCB_TBITDEF_CYCHDR;		/**< %jp{�����n���h���̋N������} */
#endif

#if _KERNEL_CYCCB_CYCTIM
	_KERNEL_CYCCB_T_RELTIM	cyctim		_KERNEL_CYCCB_TBITDEF_RELTIM;		/**< %jp{�����n���h���̋N������} */
#endif

#if _KERNEL_CYCCB_CYCPHS
	_KERNEL_CYCCB_T_RELTIM	cycphs		_KERNEL_CYCCB_TBITDEF_RELTIM;		/**< %jp{�����n���h���̋N���ʑ�} */
#endif
} _KERNEL_T_CYCCB_RO;

typedef const _KERNEL_T_CYCCB_RO	*_KERNEL_T_CYCCB_RO_PTR;


/** %jp{�����n���h���R���g���[���u���b�N}%en{Cyclic Handler Control Block} */
typedef struct _kernel_t_cyccb
{
#if _KERNEL_CYCCB_TIMOBJ
	_KERNEL_T_TIMOBJ		timobj;											/**< %jp{�^�C�}�I�u�W�F�N�g���p��} */
#endif


#if _KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_PTRARRAY
	_KERNEL_T_CYCCB_RO_PTR	cyccb_ro;										/**< %jp{�����n���h���R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_CYCCB;

typedef _KERNEL_T_CYCCB				*_KERNEL_T_CYCCB_PTR;


#else


/** %jp{�����n���h���R���g���[���u���b�N}%en{Cyclic Handler Control Block} */
typedef struct _kernel_t_cyccb
{
#if _KERNEL_CYCCB_TIMOBJ
	_KERNEL_T_TIMOBJ		timobj;											/**< %jp{�^�C�}�I�u�W�F�N�g���p��} */
#endif


#if _KERNEL_CYCCB_CYCATR
	_KERNEL_CYCCB_T_CYCATR	cycatr		_KERNEL_CYCCB_TBITDEF_CYCATR;		/**< %jp{�����n���h������} */
#endif

#if _KERNEL_CYCCB_EXINF
	_KERNEL_CYCCB_T_EXINF	exinf		_KERNEL_CYCCB_TBITDEF_EXINF;		/**< %jp{�����n���h���̊g�����} */
#endif

#if _KERNEL_CYCCB_CYCHDR
	_KERNEL_CYCCB_T_CYCHDR	cychdr		_KERNEL_CYCCB_TBITDEF_CYCHDR;		/**< %jp{�����n���h���̋N������} */
#endif

#if _KERNEL_CYCCB_CYCTIM
	_KERNEL_CYCCB_T_RELTIM	cyctim		_KERNEL_CYCCB_TBITDEF_RELTIM;		/**< %jp{�����n���h���̋N������} */
#endif

#if _KERNEL_CYCCB_CYCPHS
	_KERNEL_CYCCB_T_RELTIM	cycphs		_KERNEL_CYCCB_TBITDEF_RELTIM;		/**< %jp{�����n���h���̋N���ʑ�} */
#endif

} _KERNEL_T_CYCCB;

typedef _KERNEL_T_CYCCB				_KERNEL_T_CYCCB_RO;
typedef const _KERNEL_T_CYCCB_RO	*_KERNEL_T_CYCCB_RO_PTR;
typedef _KERNEL_T_CYCCB				*_KERNEL_T_CYCCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_cycid;										/**< %jp{�����n���h��ID�̍ő�l} */

#define _KERNEL_CYC_TMIN_ID				1														/**< %jp{�����n���h��ID�̍ŏ��l} */
#define _KERNEL_CYC_TMAX_ID				(_kernel_max_cycid)										/**< %jp{�����n���h��ID�̍ő�l} */

#define _KERNEL_CYC_CHECK_CYCID(cycid)	((cycid) >= _KERNEL_CYC_TMIN_ID && (cycid) <= _KERNEL_CYC_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_BLKARRAY
#if _KERNEL_CYCCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_CYCCB					_kernel_cyccb_tbl[];									/**< %jp{�����n���h���R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_CYCCB_RO			_kernel_cyccb_ro_tbl[];									/**< %jp{�����n���h���R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_CYC_ID2CYCCB(cycid)		(&_kernel_cyccb_tbl[(cycid) - _KERNEL_CYC_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_CYC_CYCCB2ID(cyccb)		(((cyccb) - &_kernel_cyccb_tbl[0]) + _KERNEL_CYC_TMIN_ID])	/**< %jp{ID�̎擾} */
#define _KERNEL_CYC_CHECK_EXS(cycid)	(_kernel_cyccb_ro_tbl[(cycid) - _KERNEL_CYC_TMIN_ID].cychdr != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_CYCCB					_kernel_cyccb_tbl[];									/**< %jp{�����n���h���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_CYC_ID2CYCCB(cycid)		(&_kernel_cyccb_tbl[(cycid) - _KERNEL_CYC_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_CYC_CYCCB2ID(cyccb)		_kernel_cyccb2id(cyccb)									/**< %jp{ID�̎擾} */
#define _KERNEL_CYC_CHECK_EXS(cycid)	(_kernel_cyccb_tbl[(cycid) - _KERNEL_CYC_TMIN_ID].cychdr != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_CYCCB					*_kernel_cyccb_tbl[];									/**< %jp{�����n���h���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_CYC_ID2CYCCB(cycid)		(_kernel_cyccb_tbl[(cycid) - _KERNEL_CYC_TMIN_ID])		/**< %jp{�����n���h��ID����CYCCB �A�h���X���擾} */
#define _KERNEL_CYC_CHECK_EXS(cycid)	(_KERNEL_CYC_ID2CYCCB(cycid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*   Accessor for CYCCB                       */
/* ------------------------------------------ */

/* cyccb_ro */
#if !_KERNEL_CYCCB_SPLIT_RO								
#define _KERNEL_CYC_GET_CYCCB_RO(cycid, cyccb)	(cyccb)
#else
#if _KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_BLKARRAY		/* %jp{CYCCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_CYC_GET_CYCCB_RO(cycid, cyccb)	(&_kernel_cyccb_ro_tbl[(cycid)])
#elif _KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_PTRARRAY		/* %jp{CYCCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_CYC_GET_CYCCB_RO(cycid, cyccb)	((cyccb)->cyccb_ro)
#endif
#endif


/* timobj */
#define _KERNEL_CYC_GET_TIMOBJ(cyccb)			(&(cyccb)->timobj)


/* cycatr */
#if _KERNEL_CYCCB_CYCATR
#define _KERNEL_CYC_SET_CYCATR(cyccb_ro, x)	do { (cyccb_ro)->cycatr = (_KERNEL_CYCCB_T_CYCATR)(x); } while (0)
#define _KERNEL_CYC_GET_CYCATR(cyccb_ro)		((_KERNEL_CYC_T_CYCATR)(cyccb_ro)->cycatr)
#else
#define _KERNEL_CYC_SET_CYCATR(cyccb_ro, x)	do { } while (0)
#define _KERNEL_CYC_GET_CYCATR(cyccb_ro)		(0)
#endif

/* exinf */
#if _KERNEL_CYCCB_EXINF
#define _KERNEL_CYC_SET_EXINF(cyccb_ro, x)	do { (cyccb_ro)->exinf = (_KERNEL_CYCCB_T_EXINF)(x); } while (0)
#define _KERNEL_CYC_GET_EXINF(cyccb_ro)		((_KERNEL_CYC_T_EXINF)(cyccb_ro)->exinf)
#else
#define _KERNEL_CYC_SET_EXINF(cyccb_ro, x)	do { } while (0)
#define _KERNEL_CYC_GET_EXINF(cyccb_ro)		(0)
#endif

/* cychdr */
#if _KERNEL_CYCCB_CYCHDR
#define _KERNEL_CYC_SET_CYCHDR(cyccb_ro, x)	do { (cyccb_ro)->cychdr = (_KERNEL_CYCCB_T_CYCHDR)(x); } while (0)
#define _KERNEL_CYC_GET_CYCHDR(cyccb_ro)	((_KERNEL_CYC_T_CYCHDR)(cyccb_ro)->cychdr)
#else
#define _KERNEL_CYC_SET_CYCHDR(cyccb_ro, x)	do { } while (0)
#define _KERNEL_CYC_GET_CYCHDR(cyccb_ro)	(0)
#endif

/* cyctim */
#if _KERNEL_CYCCB_CYCTIM
#define _KERNEL_CYC_SET_CYCTIM(cyccb_ro, x)		do { (cyccb_ro)->cyctim = (_KERNEL_CYCCB_T_RELTIM)(x); } while (0)
#define _KERNEL_CYC_GET_CYCTIM(cyccb_ro)		((_KERNEL_CYC_T_RELTIM)(cyccb_ro)->cyctim)
#else
#define _KERNEL_CYC_SET_CYCTIM(cyccb_ro, x)		do { } while (0)
#define _KERNEL_CYC_GET_CYCTIM(cyccb_ro)		(0)
#endif

/* cycphs */
#if _KERNEL_CYCCB_CYCPHS
#define _KERNEL_CYC_SET_CYCPHS(cyccb_ro, x)		do { (cyccb_ro)->cycphs = (_KERNEL_CYCCB_T_RELTIM)(x); } while (0)
#define _KERNEL_CYC_GET_CYCPHS(cyccb_ro)		((_KERNEL_CYC_T_RELTIM)(cyccb_ro)->cycphs)
#else
#define _KERNEL_CYC_SET_CYCPHS(cyccb_ro, x)		do { } while (0)
#define _KERNEL_CYC_GET_CYCPHS(cyccb_ro)		(0)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */




/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER   _kernel_cre_cyc(ID cycid, const T_CCYC *pk_ccyc);					/**< %jp{�����n���h������}%en{Create Cyclic Handler} */
void _kernel_cyc_hdr(_KERNEL_T_TIMOBJ *pk_timobj, RELTIM ovrtim);		/**< %jp{�����n���h��}%en{Cyclic Handler} */

#ifdef __cplusplus
}
#endif




#endif	/* _KERNEL__object__cycobj_h__ */


/* end of file */
