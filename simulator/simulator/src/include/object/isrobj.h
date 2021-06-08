/**
 *  Hyper Operating System V4 Advance
 *
 * @file  isrobj.h
 * @brief %jp{�����݃T�[�r�X���[�`���I�u�W�F�N�g}%en{interrupt service routine object heder file}
 *
 * Copyright (C) 1998-2008 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL__object__isrobj_h__
#define _KERNEL__object__isrobj_h__



/* ------------------------------------------ */
/*  Interrupt manegement                      */
/* ------------------------------------------ */

struct _kernel_t_isrcb;

#if _KERNEL_IRCATR_REG_BASE
extern const VP					_kernel_irc_reg_base;
#endif

/* %jp{�����ݏ��} */
typedef struct _kernel_t_intinf
{
	_KERNEL_T_ISRHDL			head;
} _KERNEL_T_INTINF;

/** %jp{�����ݏ��e�[�u��} */
#if _KERNEL_SPT_CRE_ISR || _KERNEL_SPT_ACRE_ISR
extern       _KERNEL_T_INTINF	_kernel_int_tbl[];
#else
extern const _KERNEL_T_INTINF	_kernel_int_tbl[];
#endif

extern const INTNO _kernel_min_intno;			/**< %jp{�����ݔԍ��̍ŏ��l} */
extern const INTNO _kernel_max_intno;			/**< %jp{�����ݔԍ��̍ő�l} */

#define _KERNEL_INT_TMIN_INTNO					(_kernel_min_intno)
#define _KERNEL_INT_TMAX_INTNO					(_kernel_max_intno)

#define _KERNEL_INT_GET_INTINF(intno)			(&_kernel_int_tbl[(intno) - _KERNEL_INT_TMIN_INTNO])
#define _KERNEL_INT_GET_HEAD(intno)				(_KERNEL_INT_GET_INTINF(intno)->head)
#define _KERNEL_INT_SET_HEAD(intno, x)			do { _KERNEL_INT_GET_INTINF(intno)->head = (x); } while (0)



/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */

/* %jp{ISR�̃n���h���̌^} */
typedef _KERNEL_T_ISRHDL				_KERNEL_ISR_T_ISRHDL;
typedef _KERNEL_T_ISRHDL				_KERNEL_ISRCB_T_ISRHDL;
#define _KERNEL_ISRCB_TBITDEF_ISRHDL

/* %jp{�g�����̌^} */
typedef VP_INT							_KERNEL_ISR_T_EXINF;
typedef VP_INT							_KERNEL_ISRCB_T_EXINF;
#define _KERNEL_ISRCB_TBITDEF_EXINF

/* %jp{�����݃T�[�r�X���[�`���̊J�n�Ԓn�̌^} */
typedef void (*_KERNEL_ISR_T_ISR)(VP_INT exinf);
typedef void (*_KERNEL_ISRCB_T_ISR)(VP_INT exinf);
#define _KERNEL_ISRCB_TBITDEF_ISR


/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_ISRCB_SPLIT_RO


/* %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N(���[�h�I�����[��)} */
typedef struct _kernel_t_isrcb_ro
{
	_KERNEL_ISRCB_T_EXINF	exinf		_KERNEL_ISRCB_TBITDEF_EXINF;		/**< %jp{�����݃T�[�r�X���[�`���̊g�����} */
	_KERNEL_ISRCB_T_ISR		isr			_KERNEL_ISRCB_TBITDEF_ISR;			/**< %jp{�����݃T�[�r�X���[�`���̋N���Ԓn} */
} _KERNEL_T_ISRCB_RO;

typedef const _KERNEL_T_ISRCB_RO	*_KERNEL_T_ISRCB_RO_PTR;


/* %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N} */
typedef struct _kernel_t_isrcb
{
	_KERNEL_ISRCB_T_ISRHDL	next		_KERNEL_ISRCB_TBITDEF_ISRHDL;		

#if _KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_PTRARRAY
	_KERNEL_T_ISRCB_RO_PTR	isrcb_ro;										/**< %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_ISRCB;

typedef _KERNEL_T_ISRCB				*_KERNEL_T_ISRCB_PTR;

#else


/* %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N} */
typedef struct _kernel_t_isrcb
{
	_KERNEL_ISRCB_T_ISRHDL	next		_KERNEL_ISRCB_TBITDEF_ISRHDL;		/**< %jp{���̊����݃T�[�r�X���[�`���R���g���[���u���b�N�ւ̃����N} */
	_KERNEL_ISRCB_T_EXINF	exinf		_KERNEL_ISRCB_TBITDEF_EXINF;		/**< %jp{�����݃T�[�r�X���[�`���̊g�����} */
	_KERNEL_ISRCB_T_ISR		isr			_KERNEL_ISRCB_TBITDEF_ISR;			/**< %jp{�����݃T�[�r�X���[�`���̋N���Ԓn} */
} _KERNEL_T_ISRCB;

typedef _KERNEL_T_ISRCB				_KERNEL_T_ISRCB_RO;
typedef const _KERNEL_T_ISRCB_RO	*_KERNEL_T_ISRCB_RO_PTR;
typedef _KERNEL_T_ISRCB				*_KERNEL_T_ISRCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_isrid;					/* %jp{�����݃T�[�r�X���[�`��ID�̍ő�l} */

#define _KERNEL_ISR_TMIN_ID				(1)									/**< %jp{�����݃T�[�r�X���[�`��ID�̍ŏ��l} */
#define _KERNEL_ISR_TMAX_ID				(_kernel_max_isrid)					/**< %jp{�����݃T�[�r�X���[�`��ID�̍ő�l} */

#define _KERNEL_ISR_CHECK_ISRID(isrid)	((isrid) >= _KERNEL_ISR_TMIN_ID && (isrid) <= _KERNEL_ISR_TMAX_ID)
																			/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_BLKARRAY
#if _KERNEL_ISRCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_ISRCB					_kernel_isrcb_tbl[];									/**< %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_ISRCB_RO			_kernel_isrcb_ro_tbl[];									/**< %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_ISR_ID2ISRCB(isrid)		(&_kernel_isrcb_tbl[(isrid) - _KERNEL_ISR_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_ISR_CHECK_EXS(isrid)	(_kernel_isrcb_ro_tbl[(isrid) - _KERNEL_ISR_TMIN_ID].isr != NULL)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_ISRCB					_kernel_isrcb_tbl[];									/**< %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_ISR_ID2ISRCB(isrid)		(&_kernel_isrcb_tbl[(isrid) - _KERNEL_ISR_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_ISR_CHECK_EXS(isrid)	(_kernel_isrcb_tbl[(isrid) - _KERNEL_ISR_TMIN_ID].isr  != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_ISRCB					*_kernel_isrcb_tbl[];									/**< %jp{�����݃T�[�r�X���[�`���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_ISR_ID2ISRCB(isrid)		(_kernel_isrcb_tbl[(isrid) - _KERNEL_ISR_TMIN_ID])		/**< %jp{�����݃T�[�r�X���[�`��ID����ISRCB �A�h���X���擾} */
#define _KERNEL_ISR_CHECK_EXS(isrid)	(_KERNEL_ISR_ID2ISRCB(isrid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*  Convert Handle                            */
/* ------------------------------------------ */

#if _KERNEL_ISRHDL_ID		/* %en{ISRHDL is ID}%jp{�^�X�N�|�C���^��ID���g��} */

#define _KERNEL_ISR_ID2ISRHDL(isrid)			(isrid)
#define _KERNEL_ISR_ISRHDL2ID(isrhdl)			(isrhdl)
#define _KERNEL_ISR_ISRCB2ISRHDL(isrcb)			_KERNEL_ISR_ISRCB2ID(isrcb)
#define _KERNEL_ISR_ISRHDL2ISRCB(isrhdl)		_KERNEL_ISR_ID2ISRCB(isrhdl)
#define _KERNEL_ISR_GET_ISRHDL(isrid, isrcb)	(isrid)

#else						/* %en{ISRHDL is address of ISRCB}%jp{�^�X�N�|�C���^��ISRCB�̃A�h���X���g��} */

#define _KERNEL_ISR_ID2ISRHDL(isrid)			_KERNEL_ISR_ID2ISRCB(isrid)
#define _KERNEL_ISR_ISRHDL2ID(isrhdl)			_KERNEL_ISR_ISRCB2ID(isrhdl)
#define _KERNEL_ISR_ISRCB2ISRHDL(isrhcb)		(isrhcb)
#define _KERNEL_ISR_ISRHDL2ISRCB(isrhdl)		(isrhdl)
#define _KERNEL_ISR_GET_ISRHDL(isrid, isrcb)	(isrcb)

#endif



/* ------------------------------------------ */
/*   Accessor for ISRCB                       */
/* ------------------------------------------ */

/* isrcb_ro */
#if !_KERNEL_ISRCB_SPLIT_RO								
#define _KERNEL_ISR_GET_ISRCB_RO(isrid, isrcb)	(isrcb)
#else
#if _KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_BLKARRAY		/* %jp{ISRCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_ISR_GET_ISRCB_RO(isrid, isrcb)	(&_kernel_isrcb_ro_tbl[(isrid)])
#elif _KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_PTRARRAY		/* %jp{ISRCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_ISR_GET_ISRCB_RO(isrid, isrcb)	((isrcb)->isrcb_ro)
#endif
#endif

#define _KERNEL_ISR_ISRHDL2ISRCBRO(isrhdl)	_KERNEL_ISR_GET_ISRCB_RO(_KERNEL_ISR_ISRHDL2ID(isrhdl), _KERNEL_ISR_ISRHDL2ISRCB(isrhdl))


#define _KERNEL_ISR_SET_NEXT(isrcb, x)		do { (isrcb)->next = (_KERNEL_ISRCB_T_ISRHDL)(x); } while (0)
#define _KERNEL_ISR_GET_NEXT(isrcb)			((_KERNEL_ISR_T_ISRHDL)(isrcb)->next)


#define _KERNEL_ISR_SET_EXINF(isrcb_ro, x)	do { (isrcb_ro)->exinf = (_KERNEL_ISRCB_T_EXINF)(x); } while (0)
#define _KERNEL_ISR_GET_EXINF(isrcb_ro)		((_KERNEL_ISR_T_EXINF)(isrcb_ro)->exinf)

#define _KERNEL_ISR_SET_ISR(isrcb_ro, x)	do { (isrcb_ro)->isr = (_KERNEL_ISRCB_T_ISR)(x); } while (0)
#define _KERNEL_ISR_GET_ISR(isrcb_ro)		((_KERNEL_ISRCB_T_ISR)(isrcb_ro)->isr)



/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER   _kernel_cre_isr(ID isrid, const T_CISR *pk_cisr);
void _kernel_exe_isr(INTNO intno);

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__isrobj_h__ */



/* end of file */
