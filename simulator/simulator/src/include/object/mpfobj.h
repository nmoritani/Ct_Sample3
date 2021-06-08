/**
 *  Hyper Operating System V4 Advance
 *
 * @file  mpfobj.h
 * @brief %en{Semaphore object heder file}%jp{�Œ蒷�������v�[���I�W�F�N�g�̃w�b�_�t�@�C��}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__mpfobj_h__
#define _KERNEL__object__mpfobj_h__



/* ------------------------------------------ */
/*  type definition                           */
/* ------------------------------------------ */

/* %jp{�Œ蒷�������v�[���u���b�N���̌^} */
#if _KERNEL_MPFCB_BITFIELD		/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MPFCB_TBITDEF_BLKCNT	: _KERNEL_MPF_TBIT_BLKCNT + 1	/**< %jp{�Œ蒷�������v�[���u���b�N���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MPFCB_TBITDEF_BLKCNT	: _KERNEL_MPF_TBIT_BLKCNT		/**< %jp{�Œ蒷�������v�[���u���b�N���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_B) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_H) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_W) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKCNT <= _KERNEL_TMAX_D) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_MPF_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_MPFCB_T_BLKCNT;			/**< %jp{�Œ蒷�������v�[���u���b�N����MPFCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_MPFCB_TBITDEF_BLKCNT									/**< %jp{�Œ蒷�������v�[���u���b�N���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�̌^} */
#if _KERNEL_MPFCB_BITFIELD		/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MPFCB_TBITDEF_BLKSZ	: _KERNEL_MPF_TBIT_BLKSZ + 1		/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MPFCB_TBITDEF_BLKSZ	: _KERNEL_MPF_TBIT_BLKSZ			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_B) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_UB) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_H) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_UH) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_W) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_UW) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_MPF_TMAX_BLKSZ <= _KERNEL_TMAX_D) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_MPF_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_MPFCB_T_BLKSZ;			/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y��MPFCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_MPFCB_TBITDEF_BLKSZ										/**< %jp{�Œ蒷�������v�[���u���b�N�T�C�Y�̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�Œ蒷�������v�[�������p�̌^} */
#if _KERNEL_MPFCB_BITFIELD		/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

/* %jp{TA_TFIFO �� TA_TPRI �̔���� 1bit �K�v} */
typedef unsigned int					_KERNEL_MPF_T_MPFATR;
typedef unsigned int					_KERNEL_MPFCB_T_MPFATR;
#define _KERNEL_MPFCB_TBITDEF_MPFATR	: 1

#else							/* %jp{MPFCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_MPF_T_MPFATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPFCB_T_MPFATR;
#define _KERNEL_MPFCB_TBITDEF_MPFATR

#endif

typedef VP								_KERNEL_MPF_T_MPF;
typedef VP								_KERNEL_MPFCB_T_MPF;
#define _KERNEL_MPFCB_TBITDEF_MPF		


/* %jp{�������u���b�N�̃n���h��} */
#if _KERNEL_MPF_ALGORITHM == _KERNEL_MPF_ALG_CHAIN_PTR		/* %jp{�|�C���^�Ǘ�} */

typedef VP								_KERNEL_MPF_T_BLKHDL;
typedef VP								_KERNEL_MPFCB_T_BLKHDL;
#define _KERNEL_MPFCB_TBITDEF_BLKHDL
#define _KERNEL_MPF_BLKHDL_NULL			NULL
#define _KERNEL_MPF_BLKHDL2PTR(mpfhdl, blkhdl)		(blkhdl)
#define _KERNEL_MPF_PTR2BLKHDL(mpfhdl, blkptr)		(blkptr)

#elif _KERNEL_MPF_ALGORITHM == _KERNEL_MPF_ALG_CHAIN_NUM	/* %jp{�u���b�N�ԍ��Ǘ�} */

typedef _KERNEL_MPF_T_BLKCNT			_KERNEL_MPF_T_BLKHDL;
typedef _KERNEL_MPFCB_T_BLKCNT			_KERNEL_MPFCB_T_BLKHDL;
#define _KERNEL_MPFCB_TBITDEF_BLKHDL	_KERNEL_MPFCB_TBITDEF_BLKCNT
#define _KERNEL_MPF_BLKHDL_NULL			0
#define _KERNEL_MPF_BLKHDL2PTR(mpfhdl, blkhdl)		((VP)((VB *)_KERNEL_MPF_GET_MPF(mpfhdl) + ((SIZE)((blkhdl) - 1) * (SIZE)_KERNEL_MPF_GET_BLKSZ(mpfhdl))))
#define _KERNEL_MPF_PTR2BLKHDL(mpfhdl, blkptr)		(((VB *)(blkptr) - (VB *)_KERNEL_MPF_GET_MPF(mpfhdl)) / _KERNEL_MPF_GET_BLKSZ(mpfhdl) + 1)

#endif



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_MPFCB_SPLIT_RO

/** %jp{�Œ蒷�������v�[���R���g���[���u���b�N(ROM��)} */
typedef struct _kernel_t_mpfcb_ro
{
#if _KERNEL_MPFCB_MPFATR
	_KERNEL_MPFCB_T_MPFATR	mpfatr		_KERNEL_MPFCB_TBITDEF_MPFATR;		/**< %jp{�Œ蒷�������v�[������} */
#endif

#if _KERNEL_MPFCB_BLKCNT
	_KERNEL_MPFCB_T_BLKCNT	blkcnt		_KERNEL_MPFCB_TBITDEF_BLKCNT;		/**< %jp{�l���ł��郁�����u���b�N��(��)} */
#endif

#if _KERNEL_MPFCB_BLKSZ
	_KERNEL_MPFCB_T_BLKCNT	blksz		_KERNEL_MPFCB_TBITDEF_BLKSZ;		/**< %jp{�������u���b�N�̃T�C�Y(�o�C�g��)} */
#endif

#if _KERNEL_MPFCB_MPF
	_KERNEL_MPFCB_T_MPF		mpf			_KERNEL_MPFCB_TBITDEF_MPF;			/**< %jp{�Œ蒷�������v�[���̈�̐擪�Ԓn} */
#endif
} _KERNEL_T_MPFCB_RO;

typedef const _KERNEL_T_MPFCB_RO	*_KERNEL_T_MPFCB_RO_PTR;


/** %jp{�Œ蒷�������v�[���R���g���[���u���b�N(RAM��)} */
typedef struct _kernel_t_mpfcb
{
#if _KERNEL_MPFCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�Œ蒷�������v�[���҂��^�X�N�L���[} */
#endif

#if _KERNEL_MPFCB_FREBLK
	_KERNEL_MPFCB_T_BLKHDL	freblk		_KERNEL_MPFCB_TBITDEF_BLKHDL;		/**< %jp{�ŏ��̃������v�[���̋󂫃������u���b�N�ʒu} */
#endif

#if _KERNEL_MPFCB_FBLKCNT
	_KERNEL_MPFCB_T_BLKCNT	fblkcnt		_KERNEL_MPFCB_TBITDEF_BLKCNT;		/**< %jp{�Œ蒷�������v�[���̋󂫃������u���b�N��(��)} */
#endif

#if _KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_PTRARRAY
	_KERNEL_MPFCB_T_ROM		*mpfcb_rom;										/**< %jp{�Œ蒷�������v�[���R���g���[���u���b�NROM���ւ̃|�C���^} */
#endif
} _KERNEL_T_MPFCB;

typedef _KERNEL_T_MPFCB				*_KERNEL_T_MPFCB_PTR;


#else


/** %jp{�Œ蒷�������v�[���R���g���[���u���b�N} */
typedef struct _kernel_t_mpfcb
{
#if _KERNEL_MPFCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�Œ蒷�������v�[���҂��^�X�N�L���[} */
#endif

#if _KERNEL_MPFCB_FREBLK
	_KERNEL_MPFCB_T_BLKHDL	freblk		_KERNEL_MPFCB_TBITDEF_BLKHDL;		/**< %jp{�ŏ��̃������v�[���̋󂫃������u���b�N�ʒu} */
#endif

#if _KERNEL_MPFCB_FBLKCNT
	_KERNEL_MPFCB_T_BLKCNT	fblkcnt		_KERNEL_MPFCB_TBITDEF_BLKCNT;		/**< %jp{�Œ蒷�������v�[���̋󂫃������u���b�N��(��)} */
#endif

#if _KERNEL_MPFCB_MPFATR
	_KERNEL_MPFCB_T_MPFATR	mpfatr		_KERNEL_MPFCB_TBITDEF_MPFATR;		/**< %jp{�Œ蒷�������v�[������} */
#endif

#if _KERNEL_MPFCB_BLKCNT
	_KERNEL_MPFCB_T_BLKCNT	blkcnt		_KERNEL_MPFCB_TBITDEF_BLKCNT;		/**< %jp{�l���ł��郁�����u���b�N��(��)} */
#endif

#if _KERNEL_MPFCB_BLKSZ
	_KERNEL_MPFCB_T_BLKSZ	blksz		_KERNEL_MPFCB_TBITDEF_BLKSZ;		/**< %jp{�������u���b�N�̃T�C�Y(�o�C�g��)} */
#endif

#if _KERNEL_MPFCB_MPF
	_KERNEL_MPFCB_T_MPF		mpf			_KERNEL_MPFCB_TBITDEF_MPF;			/**< %jp{�Œ蒷�������v�[���̈�̐擪�Ԓn} */
#endif
} _KERNEL_T_MPFCB;

typedef _KERNEL_T_MPFCB				_KERNEL_T_MPFCB_RO;
typedef const _KERNEL_T_MPFCB_RO	*_KERNEL_T_MPFCB_RO_PTR;
typedef _KERNEL_T_MPFCB				*_KERNEL_T_MPFCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_mpfid;										/**< %jp{�Œ蒷�������v�[��ID�̍ő�l} */

#define _KERNEL_MPF_TMIN_ID				1														/**< %jp{�Œ蒷�������v�[��ID�̍ŏ��l} */
#define _KERNEL_MPF_TMAX_ID				(_kernel_max_mpfid)										/**< %jp{�Œ蒷�������v�[��ID�̍ő�l} */

#define _KERNEL_MPF_CHECK_MPFID(mpfid)	((mpfid) >= _KERNEL_MPF_TMIN_ID && (mpfid) <= _KERNEL_MPF_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_BLKARRAY
#if _KERNEL_MPFCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_MPFCB					_kernel_mpfcb_tbl[];									/**< %jp{�Œ蒷�������v�[���R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_MPFCB_RO			_kernel_mpfcb_ro_tbl[];									/**< %jp{�Œ蒷�������v�[���R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_MPF_ID2MPFCB(mpfid)		(&_kernel_mpfcb_tbl[(mpfid) - _KERNEL_MPF_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MPF_CHECK_EXS(mpfid)	(_kernel_mpfcb_ro_tbl[(mpfid) - _KERNEL_MPF_TMIN_ID].mpf != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_MPFCB					_kernel_mpfcb_tbl[];									/**< %jp{�Œ蒷�������v�[���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MPF_ID2MPFCB(mpfid)		(&_kernel_mpfcb_tbl[(mpfid) - _KERNEL_MPF_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MPF_CHECK_EXS(mpfid)	(_kernel_mpfcb_tbl[(mpfid) - _KERNEL_MPF_TMIN_ID].mpf != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_MPFCB					*_kernel_mpfcb_tbl[];									/**< %jp{�Œ蒷�������v�[���R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MPF_ID2MPFCB(mpfid)		(_kernel_mpfcb_tbl[(mpfid) - _KERNEL_TMIN_MPFID])		/**< %jp{�Œ蒷�������v�[��ID����MPFCB �A�h���X���擾} */
#define _KERNEL_MPF_CHECK_EXS(mpfid)	(_KERNEL_MPF_ID2MPFCB(mpfid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*   Accessor for MPFCB                       */
/* ------------------------------------------ */

/* mpfcb_ro */
#if !_KERNEL_MPFCB_SPLIT_RO								
#define _KERNEL_MPF_GET_MPFCB_RO(mpfid, mpfcb)	(mpfcb)
#else
#if _KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_BLKARRAY		/* %jp{MPFCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_MPF_GET_MPFCB_RO(mpfid, mpfcb)	(&_kernel_mpfcb_ro_tbl[(mpfid)])
#elif _KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_PTRARRAY		/* %jp{MPFCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_MPF_GET_MPFCB_RO(mpfid, mpfcb)	((mpfcb)->mpfcb_ro)
#endif
#endif


/* que */
#define _KERNEL_MPF_GET_QUE(mpfcb)			(&(mpfcb)->que)

/* freblk */
#if _KERNEL_MPFCB_FREBLK
#define _KERNEL_MPF_SET_FREBLK(mpfcb, x)		do { (mpfcb)->freblk = (_KERNEL_MPFCB_T_BLKHDL)(x); } while (0)
#define _KERNEL_MPF_GET_FREBLK(mpfcb)			((_KERNEL_MPF_T_BLKHDL)(mpfcb)->freblk)
#else
#define _KERNEL_MPF_SET_FREBLK(mpfcb, x)		do { } while (0)
#define _KERNEL_MPF_GET_FREBLK(mpfcb)			(0)
#endif

/* fblkcnt */
#if _KERNEL_MPFCB_FBLKCNT
#define _KERNEL_MPF_SET_FBLKCNT(mpfcb, x)		do { (mpfcb)->fblkcnt = (_KERNEL_MPFCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPF_GET_FBLKCNT(mpfcb)			((_KERNEL_MPF_T_BLKCNT)(mpfcb)->fblkcnt)
#else
#define _KERNEL_MPF_SET_FBLKCNT(mpfcb, x)		do { } while (0)
#define _KERNEL_MPF_GET_FBLKCNT(mpfcb)			(0)
#endif


/* mpfatr */
#if _KERNEL_MPFCB_MPFATR
#define _KERNEL_MPF_SET_MPFATR(mpfcb_ro, x)		do { (mpfcb_ro)->mpfatr = (_KERNEL_MPFCB_T_MPFATR)(x); } while (0)
#define _KERNEL_MPF_GET_MPFATR(mpfcb_ro)		((_KERNEL_MPF_T_MPFATR)(mpfcb_ro)->mpfatr)
#else
#define _KERNEL_MPF_SET_MPFATR(mpfcb_ro, x)		do { } while (0)
#if _KERNEL_SPT_MPF_TA_TFIFO
#define _KERNEL_MPF_GET_MPFATR(mpfcb_ro)		(TA_TFIFO)
#else
#define _KERNEL_MPF_GET_MPFATR(mpfcb_ro)		(TA_TPRI)
#endif
#endif

/* blkcnt */
#if _KERNEL_MPFCB_BLKCNT
#define _KERNEL_MPF_SET_BLKCNT(mpfcb_ro, x)		do { (mpfcb_ro)->blkcnt = (_KERNEL_MPFCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPF_GET_BLKCNT(mpfcb_ro)		((_KERNEL_MPF_T_BLKCNT)(mpfcb_ro)->blkcnt)
#else
#define _KERNEL_MPF_SET_BLKCNT(mpfcb_ro, x)		do { } while (0)
#define _KERNEL_MPF_GET_BLKCNT(mpfcb_ro)		(1)
#endif

/* blksz */
#if _KERNEL_MPFCB_BLKSZ
#define _KERNEL_MPF_SET_BLKSZ(mpfcb_ro, x)		do { (mpfcb_ro)->blksz = (_KERNEL_MPFCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPF_GET_BLKSZ(mpfcb_ro)			((_KERNEL_MPF_T_BLKCNT)(mpfcb_ro)->blksz)
#else
#define _KERNEL_MPF_SET_BLKSZ(mpfcb_ro, x)		do { } while (0)
#define _KERNEL_MPF_GET_BLKSZ(mpfcb_ro)			(_KERNEL_TMAX_BLKCNT)
#endif

/* mpf */
#if _KERNEL_MPFCB_MPF
#define _KERNEL_MPF_SET_MPF(mpfcb_ro, x)		do { (mpfcb_ro)->mpf = (_KERNEL_MPFCB_T_MPF)(x); } while (0)
#define _KERNEL_MPF_GET_MPF(mpfcb_ro)			((_KERNEL_MPF_T_MPF)(mpfcb_ro)->mpf)
#else
#define _KERNEL_MPF_SET_MPF(mpfcb_ro, x)		do { } while (0)
#define _KERNEL_MPF_GET_MPF(mpfcb_ro)			(NULL)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_MPF_TA_TFIFO && _KERNEL_SPT_MPF_TA_TPRI		/* %jp{TA_TFIFO �� TA_TPRI �̍��� } */
#define _KERNEL_MPF_ADD_QUE(mpfcb, mpfcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_MPF_GET_QUE(mpfcb), tskhdl, _KERNEL_MPF_GET_MPFATR(mpfcb_ro))
#elif _KERNEL_SPT_MPF_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_MPF_ADD_QUE(mpfcb, mpfcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_MPF_GET_QUE(mpfcb), tskhdl)
#elif !_KERNEL_SPT_MPF_TA_TFIFO && _KERNEL_SPT_MPF_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_MPF_ADD_QUE(mpfcb, mpfcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_MPF_GET_QUE(mpfcb), tskhdl)
#else
#error error:_KERNEL_SPT_MPF_TA_TPRI and _KERNEL_SPT_MPF_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_MPF_RMV_QUE(mpfcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_MPF_GET_QUE(mpfcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_MPF_RMH_QUE(mpfcb)			_KERNEL_RMH_QUE(_KERNEL_MPF_GET_QUE(mpfcb))


/* %jp{�^�C���A�E�g�L���[����} */
#if _KERNEL_SPT_TGET_MPF	/* %jp{tget_mpf�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_MPF_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#define _KERNEL_MPF_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_MPF_ADD_TOQ(tskhdl)			do { } while (0)
#define _KERNEL_MPF_RMV_TOQ(tskhdl)			do { } while (0)
#endif


/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER _kernel_cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);		/**< %jp{�Œ蒷�������v�[������} */

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__mpfobj_h__ */


/* end of file */
