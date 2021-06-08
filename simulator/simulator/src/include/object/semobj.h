/**
 *  Hyper Operating System V4 Advance
 *
 * @file  semobj.h
 * @brief %jp{�Z�}�t�H�I�W�F�N�g�̃w�b�_�t�@�C��}%en{Semaphore object heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__semobj_h__
#define _KERNEL__object__semobj_h__



/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */

/* %jp{�Z�}�t�H�J�E���^�l�p�̌^} */
#if _KERNEL_SEMCB_BITFIELD		/* %jp{SEMCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_SEMCB_TBITDEF_SEMCNT	: (_KERNEL_SEM_TBIT_SEMCNT+1)	/**< %jp{�Z�}�t�H�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_SEMCB_TBITDEF_SEMCNT	: _KERNEL_SEM_TBIT_SEMCNT		/**< %jp{�Z�}�t�H�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{SEMCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_SEM_TMAX_SEMCNT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_SEM_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_SEMCB_T_SEMCNT;			/**< %jp{�Z�}�t�H�J�E���^��SEMCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_SEMCB_TBITDEF_SEMCNT									/**< %jp{�Z�}�t�H�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�Z�}�t�H�����p�̌^} */
#if _KERNEL_SEMCB_BITFIELD		/* %jp{SEMCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

/* %jp{TA_TFIFO �� TA_TPRI �̔���� 1bit �K�v} */
typedef unsigned int					_KERNEL_SEM_T_SEMATR;
typedef unsigned int					_KERNEL_SEMCB_T_SEMATR;
#define _KERNEL_SEMCB_TBITDEF_SEMATR	: 1

#else							/* %jp{SEMCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_SEM_T_SEMATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_SEMCB_T_SEMATR;
#define _KERNEL_SEMCB_TBITDEF_SEMATR

#endif



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_SEMCB_SPLIT_RO


/** %jp{�Z�}�t�H�R���g���[���u���b�N(���[�h�I�����[��)}%en{Semaphore Control Block(read-only)} */
typedef struct _kernel_t_semcb_ro
{
#if _KERNEL_SEMCB_SEMATR
	_KERNEL_SEMCB_T_SEMATR	sematr		_KERNEL_SEMCB_TBITDEF_SEMATR;		/**< %jp{�Z�}�t�H����} */
#endif

#if _KERNEL_SEMCB_MAXSEM
	_KERNEL_SEMCB_T_SEMCNT	maxsem		_KERNEL_SEMCB_TBITDEF_SEMCNT;		/**< %jp{�Z�}�t�H�̍ő厑����} */
#endif
} _KERNEL_T_SEMCB_RO;

typedef const _KERNEL_T_SEMCB_RO	*_KERNEL_T_SEMCB_RO_PTR;


/** %jp{�Z�}�t�H�R���g���[���u���b�N}%en{Semaphore Control Block} */
typedef struct _kernel_t_semcb
{
#if _KERNEL_SEMCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�Z�}�t�H�҂��^�X�N�L���[} */
#endif

#if _KERNEL_SEMCB_SEMCNT
	_KERNEL_SEMCB_T_SEMCNT	semcnt		_KERNEL_SEMCB_TBITDEF_SEMCNT;		/**< %jp{�Z�}�t�H�̎�����} */
#endif


#if _KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_PTRARRAY
	_KERNEL_T_SEMCB_RO_PTR	semcb_ro;										/**< %jp{�Z�}�t�H�R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_SEMCB;

typedef _KERNEL_T_SEMCB				*_KERNEL_T_SEMCB_PTR;


#else


/** %jp{�Z�}�t�H�R���g���[���u���b�N}%en{Semaphore Control Block} */
typedef struct _kernel_t_semcb
{
#if _KERNEL_SEMCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�Z�}�t�H�҂��^�X�N�L���[} */
#endif

#if _KERNEL_SEMCB_SEMCNT
	_KERNEL_SEMCB_T_SEMCNT	semcnt		_KERNEL_SEMCB_TBITDEF_SEMCNT;		/**< %jp{�Z�}�t�H�̎�����} */
#endif

#if _KERNEL_SEMCB_SEMATR
	_KERNEL_SEMCB_T_SEMATR	sematr		_KERNEL_SEMCB_TBITDEF_SEMATR;		/**< %jp{�Z�}�t�H����} */
#endif

#if _KERNEL_SEMCB_MAXSEM
	_KERNEL_SEMCB_T_SEMCNT	maxsem		_KERNEL_SEMCB_TBITDEF_SEMCNT;		/**< %jp{�Z�}�t�H�̍ő厑����} */
#endif
} _KERNEL_T_SEMCB;

typedef _KERNEL_T_SEMCB				_KERNEL_T_SEMCB_RO;
typedef const _KERNEL_T_SEMCB_RO	*_KERNEL_T_SEMCB_RO_PTR;
typedef _KERNEL_T_SEMCB				*_KERNEL_T_SEMCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_semid;										/**< %jp{�Z�}�t�HID�̍ő�l} */

#define _KERNEL_SEM_TMIN_ID				1														/**< %jp{�Z�}�t�HID�̍ŏ��l} */
#define _KERNEL_SEM_TMAX_ID				(_kernel_max_semid)										/**< %jp{�Z�}�t�HID�̍ő�l} */

#define _KERNEL_SEM_CHECK_SEMID(semid)	((semid) >= _KERNEL_SEM_TMIN_ID && (semid) <= _KERNEL_SEM_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_BLKARRAY
#if _KERNEL_SEMCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_SEMCB					_kernel_semcb_tbl[];									/**< %jp{�Z�}�t�H�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_SEMCB_RO			_kernel_semcb_ro_tbl[];									/**< %jp{�Z�}�t�H�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_SEM_ID2SEMCB(semid)		(&_kernel_semcb_tbl[(semid) - _KERNEL_SEM_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_SEM_CHECK_EXS(semid)	(_kernel_semcb_ro_tbl[(semid) - _KERNEL_SEM_TMIN_ID].maxsem > 0)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_SEMCB					_kernel_semcb_tbl[];									/**< %jp{�Z�}�t�H�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_SEM_ID2SEMCB(semid)		(&_kernel_semcb_tbl[(semid) - _KERNEL_SEM_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_SEM_CHECK_EXS(semid)	(_kernel_semcb_tbl[(semid) - _KERNEL_SEM_TMIN_ID].maxsem > 0)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_SEMCB					*_kernel_semcb_tbl[];									/**< %jp{�Z�}�t�H�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_SEM_ID2SEMCB(semid)		(_kernel_semcb_tbl[(semid) - _KERNEL_SEM_TMIN_ID])		/**< %jp{�Z�}�t�HID����SEMCB �A�h���X���擾} */
#define _KERNEL_SEM_CHECK_EXS(semid)	(_KERNEL_SEM_ID2SEMCB(semid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*   Accessor for SEMCB                       */
/* ------------------------------------------ */

/* semcb_ro */
#if !_KERNEL_SEMCB_SPLIT_RO								
#define _KERNEL_SEM_GET_SEMCB_RO(semid, semcb)	(semcb)
#else
#if _KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_BLKARRAY		/* %jp{SEMCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_SEM_GET_SEMCB_RO(semid, semcb)	(&_kernel_semcb_ro_tbl[(semid)])
#elif _KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_PTRARRAY		/* %jp{SEMCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_SEM_GET_SEMCB_RO(semid, semcb)	((semcb)->semcb_ro)
#endif
#endif


/* que */
#define _KERNEL_SEM_GET_QUE(semcb)			(&(semcb)->que)


/* semcnt */
#if _KERNEL_SEMCB_SEMCNT
#define _KERNEL_SEM_SET_SEMCNT(semcb, x)	do { (semcb)->semcnt = (_KERNEL_SEMCB_T_SEMCNT)(x); } while (0)
#define _KERNEL_SEM_GET_SEMCNT(semcb)		((_KERNEL_SEM_T_SEMCNT)(semcb)->semcnt)
#else
#define _KERNEL_SEM_SET_SEMCNT(semcb, x)	do { } while (0)
#define _KERNEL_SEM_GET_SEMCNT(semcb)		(0)
#endif


/* sematr */
#if _KERNEL_SEMCB_SEMATR
#define _KERNEL_SEM_SET_SEMATR(semcb, x)	do { (semcb)->sematr = (_KERNEL_SEMCB_T_SEMATR)(x); } while (0)
#define _KERNEL_SEM_GET_SEMATR(semcb)		((_KERNEL_SEM_T_SEMATR)(semcb)->sematr)
#else
#define _KERNEL_SEM_SET_SEMATR(semcb, x)	do { } while (0)
#if _KERNEL_SPT_SEM_TA_TFIFO
#define _KERNEL_SEM_GET_SEMATR(semcb)		(TA_TFIFO)
#else
#define _KERNEL_SEM_GET_SEMATR(semcb)		(TA_TPRI)
#endif
#endif


/* maxsem */
#if _KERNEL_SEMCB_MAXSEM
#define _KERNEL_SEM_SET_MAXSEM(semcb_ro, x)	do { (semcb_ro)->maxsem = (_KERNEL_SEMCB_T_SEMCNT)(x); } while (0)
#define _KERNEL_SEM_GET_MAXSEM(semcb_ro)	((_KERNEL_SEM_T_SEMCNT)(semcb_ro)->maxsem)
#else
#define _KERNEL_SEM_SET_MAXSEM(semcb_ro, x)	do { } while (0)
#define _KERNEL_SEM_GET_MAXSEM(semcb_ro)	(_KERNEL_TMAX_MAXSEM)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_SEM_TA_TFIFO && _KERNEL_SPT_SEM_TA_TPRI		/* %jp{TA_TFIFO �� TA_TPRI �̍��� } */
#define _KERNEL_SEM_ADD_QUE(semcb, semcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_SEM_GET_QUE(semcb), tskhdl, _KERNEL_SEM_GET_SEMATR(semcb_ro))
#elif _KERNEL_SPT_SEM_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_SEM_ADD_QUE(semcb, semcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_SEM_GET_QUE(semcb), tskhdl)
#elif !_KERNEL_SPT_SEM_TA_TFIFO && _KERNEL_SPT_SEM_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_SEM_ADD_QUE(semcb, semcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_SEM_GET_QUE(semcb), tskhdl)
#else
#error error:_KERNEL_SPT_SEM_TA_TPRI and _KERNEL_SPT_SEM_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_SEM_RMV_QUE(semcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_SEM_GET_QUE(semcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_SEM_RMH_QUE(semcb)			_KERNEL_RMH_QUE(_KERNEL_SEM_GET_QUE(semcb))


/* %jp{�^�C���A�E�g�L���[�ڑ�} */
#if _KERNEL_SPT_TWAI_SEM	/* %jp{twai_sem�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_SEM_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#else
#define _KERNEL_SEM_ADD_TOQ(tskhdl)			do { } while (0)
#endif

/* %jp{�^�C���A�E�g�L���[���O��} */
#if _KERNEL_SPT_TWAI_SEM	/* %jp{twai_sem�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_SEM_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_SEM_RMV_TOQ(tskhdl)			do { } while (0)
#endif



/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER _kernel_cre_sem(ID semid, const T_CSEM *pk_csem);	/**< %jp{�Z�}�t�H����}%en{Create Semaphore} */
ER _kernel_wai_sem(ID semid, TMO tmout);				/**< %jp{�Z�}�t�H�����̊l��(������)}%en{Acquire Semaphore Resource} */

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__semobj_h__ */


/* end of file */
