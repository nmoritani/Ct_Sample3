/**
 *  Hyper Operating System V4 Advance
 *
 * @file  mtxobj.h
 * @brief %jp{�~���[�e�b�N�X�I�W�F�N�g�̃w�b�_�t�@�C��}%en{Mutex object heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__mtxobj_h__
#define _KERNEL__object__mtxobj_h__



/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */


/* %jp{�~���[�e�b�N�X�����^�X�N�n���h���p�̌^} */
typedef _KERNEL_T_TSKHDL				_KERNEL_MTX_T_TSKHDL;			/**< %jp{�~���[�e�b�N�X�����^�X�N�n���h�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_TSKHDL				_KERNEL_MTXCB_T_TSKHDL;			/**< %jp{�~���[�e�b�N�X�����^�X�N�n���h����MTXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MTXCB_TBITDEF_TSKHDL

/* %jp{�~���[�e�b�N�X�n���h���p�̌^} */
typedef _KERNEL_T_MTXHDL				_KERNEL_MTX_T_MTXHDL;			/**< %jp{�~���[�e�b�N�X�����^�X�N�n���h�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_MTXHDL				_KERNEL_MTXCB_T_MTXHDL;			/**< %jp{�~���[�e�b�N�X�����^�X�N�n���h����MTXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MTXCB_TBITDEF_MTXHDL


/* %jp{�~���[�e�b�N�X�̏���D��x�^} */
typedef PRI								_KERNEL_MTX_T_CEILPRI;			/**< %jp{�~���[�e�b�N�X�̏���D��x�����Z���삷��Ƃ��̌^} */
typedef PRI								_KERNEL_MTXCB_T_CEILPRI;		/**< %jp{�~���[�e�b�N�X�̏���D��x��MTXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MTXCB_TBITDEF_CEILPRI


/* %jp{�~���[�e�b�N�X�����p�̌^} */
#if _KERNEL_MTXCB_BITFIELD		/* %jp{MTXCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

typedef unsigned int					_KERNEL_MTX_T_MTXATR;
typedef unsigned int					_KERNEL_MTXCB_T_MTXATR;
#define _KERNEL_MTXCB_TBITDEF_MTXATR	: 3

#else							/* %jp{MTXCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_MTX_T_MTXATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_MTXCB_T_MTXATR;
#define _KERNEL_MTXCB_TBITDEF_MTXATR

#endif



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_MTXCB_SPLIT_RO


/** %jp{�~���[�e�b�N�X�R���g���[���u���b�N(���[�h�I�����[��)}%en{Mutex Control Block(read-only)} */
typedef struct _kernel_t_mtxcb_ro
{
#if _KERNEL_MTXCB_MTXATR
	_KERNEL_MTXCB_T_MTXATR	mtxatr		_KERNEL_MTXCB_TBITDEF_MTXATR;		/**< %jp{�~���[�e�b�N�X����} */
#endif

#if _KERNEL_MTXCB_CEILPRI
	_KERNEL_MTXCB_T_CEILPRI	ceilpri		KERNEL_MTXCB_TBITDEF_CEILPRI;		/**< %jp{�~���[�e�b�N�X�̏���D��x} */
#endif
} _KERNEL_T_MTXCB_RO;

typedef const _KERNEL_T_MTXCB_RO	*_KERNEL_T_MTXCB_RO_PTR;


/** %jp{�~���[�e�b�N�X�R���g���[���u���b�N}%en{Mutex Control Block} */
typedef struct _kernel_t_mtxcb
{
#if _KERNEL_MTXCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�~���[�e�b�N�X�҂��^�X�N�L���[} */
#endif

#if _KERNEL_MTXCB_TSKHDL
	_KERNEL_MTXCB_T_TSKHDL	tskhdl		_KERNEL_MTXCB_TBITDEF_TSKHDL;		/**< %jp{�~���[�e�b�N�X����������^�X�N�̃n���h��} */
#endif

#if _KERNEL_MTXCB_NEXT
	_KERNEL_T_MTXHDL		next;											/**< %jp{���̃~���[�e�b�N�X�n���h��} */
#endif

#if _KERNEL_MTXCB_PREV
	_KERNEL_T_MTXHDL		prev;											/**< %jp{�O�̃~���[�e�b�N�X�n���h��} */
#endif

#if _KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_PTRARRAY
	_KERNEL_T_MTXCB_RO_PTR	mtxcb_ro;										/**< %jp{�~���[�e�b�N�X�R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_MTXCB;

typedef _KERNEL_T_MTXCB				*_KERNEL_T_MTXCB_PTR;


#else


/** %jp{�~���[�e�b�N�X�R���g���[���u���b�N}%en{Mutex Control Block} */
typedef struct _kernel_t_mtxcb
{
#if _KERNEL_MTXCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�~���[�e�b�N�X�҂��^�X�N�L���[} */
#endif

#if _KERNEL_MTXCB_TSKHDL
	_KERNEL_MTXCB_T_TSKHDL	tskhdl		_KERNEL_MTXCB_TBITDEF_TSKHDL;		/**< %jp{�~���[�e�b�N�X����������^�X�N�̃n���h��} */
#endif

#if _KERNEL_MTXCB_NEXT
	_KERNEL_T_MTXHDL		next;											/**< %jp{���̃~���[�e�b�N�X�n���h��} */
#endif

#if _KERNEL_MTXCB_PREV
	_KERNEL_T_MTXHDL		prev;											/**< %jp{�O�̃~���[�e�b�N�X�n���h��} */
#endif

#if _KERNEL_MTXCB_MTXATR
	_KERNEL_MTXCB_T_MTXATR	mtxatr		_KERNEL_MTXCB_TBITDEF_MTXATR;		/**< %jp{�~���[�e�b�N�X����} */
#endif

#if _KERNEL_MTXCB_CEILPRI
	_KERNEL_MTXCB_T_CEILPRI	ceilpri		_KERNEL_MTXCB_TBITDEF_CEILPRI;		/**< %jp{�~���[�e�b�N�X�̏���D��x} */
#endif
} _KERNEL_T_MTXCB;

typedef _KERNEL_T_MTXCB				_KERNEL_T_MTXCB_RO;
typedef const _KERNEL_T_MTXCB_RO	*_KERNEL_T_MTXCB_RO_PTR;
typedef _KERNEL_T_MTXCB				*_KERNEL_T_MTXCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_mtxid;										/**< %jp{�~���[�e�b�N�XID�̍ő�l} */

#define _KERNEL_MTX_TMIN_ID				1														/**< %jp{�~���[�e�b�N�XID�̍ŏ��l} */
#define _KERNEL_MTX_TMAX_ID				(_kernel_max_mtxid)										/**< %jp{�~���[�e�b�N�XID�̍ő�l} */

#define _KERNEL_MTX_CHECK_MTXID(mtxid)	((mtxid) >= _KERNEL_MTX_TMIN_ID && (mtxid) <= _KERNEL_MTX_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_BLKARRAY
#if _KERNEL_MTXCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_MTXCB					_kernel_mtxcb_tbl[];									/**< %jp{�~���[�e�b�N�X�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_MTXCB_RO			_kernel_mtxcb_ro_tbl[];									/**< %jp{�~���[�e�b�N�X�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_MTX_ID2MTXCB(mtxid)		(&_kernel_mtxcb_tbl[(mtxid) - _KERNEL_MTX_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MTX_CHECK_EXS(mtxid)	(_kernel_mtxcb_ro_tbl[(mtxid) - _KERNEL_MTX_TMIN_ID].mtxatr != 0)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_MTXCB					_kernel_mtxcb_tbl[];									/**< %jp{�~���[�e�b�N�X�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MTX_ID2MTXCB(mtxid)		(&_kernel_mtxcb_tbl[(mtxid) - _KERNEL_MTX_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MTX_CHECK_EXS(mtxid)	(_kernel_mtxcb_tbl[(mtxid) - _KERNEL_MTX_TMIN_ID].mtxatr != 0)			
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_MTXCB					*_kernel_mtxcb_tbl[];									/**< %jp{�~���[�e�b�N�X�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MTX_ID2MTXCB(mtxid)		(_kernel_mtxcb_tbl[(mtxid) - _KERNEL_MTX_TMIN_ID])		/**< %jp{�~���[�e�b�N�XID����MTXCB �A�h���X���擾} */
#define _KERNEL_MTX_CHECK_EXS(mtxid)	(_KERNEL_MTX_ID2MTXCB(mtxid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*  Convert Handle                            */
/* ------------------------------------------ */

#if _KERNEL_MTXHDL_ID		/* %jp{�~���[�e�b�N�X�n���h����ID���g��}%en{MTXHDL is ID} */

#define _KERNEL_MTX_ID2MTXHDL(mtxid)			(mtxid)
#define _KERNEL_MTX_MTXHDL2ID(mtxhdl)			(mtxhdl)
#define _KERNEL_MTX_MTXCB2MTXHDL(mtxcb)			_KERNEL_MTX_MTXCB2ID(mtxcb)
#define _KERNEL_MTX_MTXHDL2MTXCB(mtxhdl)		_KERNEL_MTX_ID2MTXCB(mtxhdl)
#define _KERNEL_MTX_GET_MTXHDL(mtxid, mtxcb)	(mtxid)

#else						/* %jp{�~���[�e�b�N�X�n���h����MTXCB�̃A�h���X���g��}%en{TSKHDL is Address of MTXCB} */

#define _KERNEL_MTX_ID2MTXHDL(mtxid)			_KERNEL_MTX_ID2MTXCB(mtxid)
#define _KERNEL_MTX_MTXHDL2ID(mtxhdl)			_KERNEL_MTX_MTXCB2ID(mtxhdl)
#define _KERNEL_MTX_MTXCB2MTXHDL(mtxcb)			(mtxhdl)
#define _KERNEL_MTX_MTXHDL2MTXCB(mtxhdl)		(mtxhdl)
#define _KERNEL_MTX_GET_MTXHDL(mtxid, mtxcb)	(mtxcb)

#endif



/* ------------------------------------------ */
/*   Accessor for MTXCB                       */
/* ------------------------------------------ */

/* mtxcb_ro */
#if !_KERNEL_MTXCB_SPLIT_RO								
#define _KERNEL_MTX_GET_MTXCB_RO(mtxid, mtxcb)	(mtxcb)
#else
#if _KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_BLKARRAY		/* %jp{MTXCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_MTX_GET_MTXCB_RO(mtxid, mtxcb)	(&_kernel_mtxcb_ro_tbl[(mtxid)])
#elif _KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_PTRARRAY		/* %jp{MTXCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_MTX_GET_MTXCB_RO(mtxid, mtxcb)	((mtxcb)->mtxcb_ro)
#endif
#endif


/* que */
#define _KERNEL_MTX_GET_QUE(mtxcb)				(&(mtxcb)->que)


/* tskhdl */
#if _KERNEL_MTXCB_TSKHDL
#define _KERNEL_MTX_SET_TSKHDL(mtxcb, x)		do { (mtxcb)->tskhdl = (_KERNEL_MTXCB_T_TSKHDL)(x); } while (0)
#define _KERNEL_MTX_GET_TSKHDL(mtxcb)			((_KERNEL_MTX_T_TSKHDL)(mtxcb)->tskhdl)
#else
#define _KERNEL_MTX_SET_TSKHDL(mtxcb, x)		do { } while (0)
#define _KERNEL_MTX_GET_TSKHDL(mtxcb)			(0)
#endif


/* next */
#if _KERNEL_MTXCB_NEXT
#define _KERNEL_MTX_SET_NEXT(mtxcb, x)			do { (mtxcb)->next = (_KERNEL_MTXCB_T_MTXHDL)(x); } while (0)
#define _KERNEL_MTX_GET_NEXT(mtxcb)				((_KERNEL_MTX_T_MTXHDL)(mtxcb)->next)
#else
#define _KERNEL_MTX_SET_NEXT(mtxcb, x)			do { } while (0)
#define _KERNEL_MTX_GET_NEXT(mtxcb)				(0)
#endif


/* prev */
#if _KERNEL_MTXCB_PREV
#define _KERNEL_MTX_SET_PREV(mtxcb, x)			do { (mtxcb)->prev = (_KERNEL_MTXCB_T_MTXHDL)(x); } while (0)
#define _KERNEL_MTX_GET_PREV(mtxcb)				((_KERNEL_MTX_T_MTXHDL)(mtxcb)->prev)
#else
#define _KERNEL_MTX_SET_PREV(mtxcb, x)			do { } while (0)
#define _KERNEL_MTX_GET_PREV(mtxcb)				(0)
#endif



/* mtxatr */
#if _KERNEL_MTXCB_MTXATR
#define _KERNEL_MTX_SET_MTXATR(mtxcb_ro, x)		do { (mtxcb_ro)->mtxatr = (_KERNEL_MTXCB_T_MTXATR)(x); } while (0)
#define _KERNEL_MTX_GET_MTXATR(mtxcb_ro)		((_KERNEL_MTX_T_MTXATR)(mtxcb_ro)->mtxatr)
#else
#define _KERNEL_MTX_SET_MTXATR(mtxcb_ro, x)		do { } while (0)
#if _KERNEL_SPT_MTX_TA_CEILING
#define _KERNEL_MTX_GET_MTXATR(mtxcb_ro)		(TA_CEILING)
#else
#define _KERNEL_MTX_GET_MTXATR(mtxcb_ro)		(TA_INHERIT)
#endif
#endif


/* ceilpri */
#if _KERNEL_MTXCB_CEILPRI
#define _KERNEL_MTX_SET_CEILPRI(mtxcb_ro, x)	do { (mtxcb_ro)->ceilpri = (_KERNEL_MTXCB_T_CEILPRI)(x); } while (0)
#define _KERNEL_MTX_GET_CEILPRI(mtxcb_ro)		((_KERNEL_MTX_T_CEILPRI)(mtxcb_ro)->ceilpri)
#else
#define _KERNEL_MTX_SET_CEILPRI(mtxcb_ro, x)	do { } while (0)
#define _KERNEL_MTX_GET_CEILPRI(mtxcb_ro)		(1)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_MTX_TA_TFIFO && _KERNEL_SPT_MTX_TA_TPRI		/* %jp{TA_TFIFO �� TA_TPRI �̍��� } */
#define _KERNEL_MTX_ADD_QUE(mtxcb, mtxcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_MTX_GET_QUE(mtxcb), tskhdl, _KERNEL_MTX_GET_MTXATR(mtxcb_ro))
#elif _KERNEL_SPT_MTX_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_MTX_ADD_QUE(mtxcb, mtxcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_MTX_GET_QUE(mtxcb), tskhdl)
#elif !_KERNEL_SPT_MTX_TA_TFIFO && _KERNEL_SPT_MTX_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_MTX_ADD_QUE(mtxcb, mtxcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_MTX_GET_QUE(mtxcb), tskhdl)
#else
#error error:_KERNEL_SPT_MTX_TA_TPRI and _KERNEL_SPT_MTX_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_MTX_RMV_QUE(mtxcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_MTX_GET_QUE(mtxcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_MTX_RMH_QUE(mtxcb)			_KERNEL_RMH_QUE(_KERNEL_MTX_GET_QUE(mtxcb))


/* %jp{�^�C���A�E�g�L���[�ڑ�} */
#if _KERNEL_SPT_TLOC_MTX	/* %jp{tloc_mtx�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_MTX_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#else
#define _KERNEL_MTX_ADD_TOQ(tskhdl)			do { } while (0)
#endif

/* %jp{�^�C���A�E�g�L���[���O��} */
#if _KERNEL_SPT_TLOC_MTX	/* %jp{tloc_mtx�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_MTX_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_MTX_RMV_TOQ(tskhdl)			do { } while (0)
#endif



/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER   _kernel_cre_mtx(ID mtxid, const T_CMTX *pk_cmtx);					/**< %jp{�~���[�e�b�N�X����}%en{Create Mutex} */
ER   _kernel_loc_mtx(ID mtxid, TMO tmout);								/**< %jp{�~���[�e�b�N�X�̃��b�N(������)} */
void _kernel_add_mtx(_KERNEL_T_MTXHDL mtxhdl, _KERNEL_T_TSKHDL tskhdl);	/**< %jp{�^�X�N�Ƀ~���[�e�b�N�X��ڑ�} */
void _kernel_rmv_mtx(_KERNEL_T_MTXHDL mtxhdl, _KERNEL_T_TSKHDL tskhdl);	/**< %jp{�^�X�N����~���[�e�b�N�X�����O��} */


#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__mtxobj_h__ */


/* end of file */
