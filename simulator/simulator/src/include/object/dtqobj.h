/**
 *  Hyper Operating System V4 Advance
 *
 * @file  dtqobj.h
 * @brief %jp{�f�[�^�L���[�W�F�N�g�̃w�b�_�t�@�C��}%en{Data queue object heder file}
 *
 * Copyright (C) 1998-2009 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__dtqobj_h__
#define _KERNEL__object__dtqobj_h__



/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */

/* %jp{�f�[�^�L���[�J�E���^�l�p�̌^} */
#if _KERNEL_DTQCB_BITFIELD		/* %jp{DTQCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_DTQCB_TBITDEF_DTQCNT	: (_KERNEL_DTQ_TBIT_DTQCNT+1)	/**< %jp{�f�[�^�L���[�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_DTQCB_TBITDEF_DTQCNT	: _KERNEL_DTQ_TBIT_DTQCNT		/**< %jp{�f�[�^�L���[�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{DTQCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_DTQ_TMAX_DTQCNT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_DTQ_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_DTQCB_T_DTQCNT;			/**< %jp{�f�[�^�L���[�J�E���^��DTQCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_DTQCB_TBITDEF_DTQCNT									/**< %jp{�f�[�^�L���[�J�E���^�̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�f�[�^�L���[�����p�̌^} */
#if _KERNEL_DTQCB_BITFIELD		/* %jp{DTQCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

/* %jp{TA_TFIFO �� TA_TPRI �̔���� 1bit �K�v} */
typedef unsigned int					_KERNEL_DTQ_T_DTQATR;
typedef unsigned int					_KERNEL_DTQCB_T_DTQATR;
#define _KERNEL_DTQCB_TBITDEF_DTQATR	: 1

#else							/* %jp{DTQCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_DTQ_T_DTQATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_DTQCB_T_DTQATR;
#define _KERNEL_DTQCB_TBITDEF_DTQATR

#endif


/* %jp{�f�[�^�L���[�̈�̐擪�Ԓn�p�̌^} */
typedef VP_INT*							_KERNEL_DTQ_T_DTQ;
typedef VP_INT*							_KERNEL_DTQCB_T_DTQ;
#define _KERNEL_DTQCB_TBITDEF_DTQ



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_DTQCB_SPLIT_RO

/** %jp{�f�[�^�L���[�R���g���[���u���b�N(���[�h�I�����[��)}%en{Data queue Control Block(read-only)} */
typedef struct _kernel_t_dtqcb_ro
{
#if _KERNEL_DTQCB_DTQATR
	_KERNEL_DTQCB_T_DTQATR	dtqatr		_KERNEL_DTQCB_TBITDEF_DTQATR;		/**< %jp{�f�[�^�L���[����}%en{Data queue attribute} */
#endif

#if _KERNEL_DTQCB_DTQCNT
	_KERNEL_DTQCB_T_DTQCNT	dtqcnt		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�̈�̗e��(�f�[�^�̌�)}%en{Capacity of the data queue area(the number of data elements)} */
#endif

#if _KERNEL_DTQCB_DTQ
	_KERNEL_DTQCB_T_DTQ		dtq			_KERNEL_DTQCB_TBITDEF_DTQ;			/**< %jp{�f�[�^�L���[�̈�̐擪�Ԓn}%en{Start address of the data queue area} */
#endif
} _KERNEL_T_DTQCB_RO;

/** %jp{�f�[�^�L���[�R���g���[���u���b�N}%en{Data queue Control Block} */
typedef struct _kernel_t_dtqcb
{
#if _KERNEL_DTQCB_SQUE
	_KERNEL_T_QUE			sque;											/**< %jp{�f�[�^�L���[���M�҂��^�X�N�L���[} */
#endif

#if _KERNEL_DTQCB_RQUE
	_KERNEL_T_QUE			rque;											/**< %jp{�f�[�^�L���[��M�҂��^�X�N�L���[} */
#endif

#if _KERNEL_DTQCB_SDTQCNT
	_KERNEL_DTQCB_T_DTQCNT	sdtqcnt		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�ɓ����Ă���f�[�^�̐�}%en{The number of data elemnts int the data queue} */
#endif

#if _KERNEL_DTQCB_HEAD
	_KERNEL_DTQCB_T_DTQCNT	head		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�̃f�[�^�擪�ʒu} */
#endif


#if _KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_PTRARRAY
	const _KERNEL_T_SEMCB_RO	*dtqcb_ro;									/**< %jp{�f�[�^�L���[�R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_DTQCB;


#else


/** %jp{�f�[�^�L���[�R���g���[���u���b�N}%en{Data queue Control Block} */
typedef struct _kernel_t_dtqcb
{
#if _KERNEL_DTQCB_SQUE
	_KERNEL_T_QUE			sque;											/**< %jp{�f�[�^�L���[���M�҂��^�X�N�L���[} */
#endif

#if _KERNEL_DTQCB_RQUE
	_KERNEL_T_QUE			rque;											/**< %jp{�f�[�^�L���[��M�҂��^�X�N�L���[} */
#endif

#if _KERNEL_DTQCB_SDTQCNT
	_KERNEL_DTQCB_T_DTQCNT	sdtqcnt		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�ɓ����Ă���f�[�^�̐�}%en{The number of data elemnts int the data queue} */
#endif

#if _KERNEL_DTQCB_HEAD
	_KERNEL_DTQCB_T_DTQCNT	head		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�̃f�[�^�擪�ʒu} */
#endif


#if _KERNEL_DTQCB_DTQATR
	_KERNEL_DTQCB_T_DTQATR	dtqatr		_KERNEL_DTQCB_TBITDEF_DTQATR;		/**< %jp{�f�[�^�L���[����}%en{Data queue attribute} */
#endif

#if _KERNEL_DTQCB_DTQCNT
	_KERNEL_DTQCB_T_DTQCNT	dtqcnt		_KERNEL_DTQCB_TBITDEF_DTQCNT;		/**< %jp{�f�[�^�L���[�̈�̗e��(�f�[�^�̌�)}%en{Capacity of the data queue area(the number of data elements)} */
#endif

#if _KERNEL_DTQCB_DTQ
	_KERNEL_DTQCB_T_DTQ		dtq			_KERNEL_DTQCB_TBITDEF_DTQ;			/**< %jp{�f�[�^�L���[�̈�̐擪�Ԓn}%en{Start address of the data queue area} */
#endif
} _KERNEL_T_DTQCB;

typedef _KERNEL_T_DTQCB		_KERNEL_T_DTQCB_RO;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_dtqid;										/**< %jp{�f�[�^�L���[ID�̍ő�l} */

#define _KERNEL_DTQ_TMIN_ID				1														/**< %jp{�f�[�^�L���[ID�̍ŏ��l} */
#define _KERNEL_DTQ_TMAX_ID				(_kernel_max_dtqid)										/**< %jp{�f�[�^�L���[ID�̍ő�l} */

#define _KERNEL_DTQ_CHECK_DTQID(dtqid)	((dtqid) >= _KERNEL_DTQ_TMIN_ID && (dtqid) <= _KERNEL_DTQ_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_BLKARRAY
#if _KERNEL_DTQCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_DTQCB					_kernel_dtqcb_tbl[];									/**< %jp{�f�[�^�L���[�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_DTQCB_RO			_kernel_dtqcb_ro_tbl[];									/**< %jp{�f�[�^�L���[�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_DTQ_ID2DTQCB(dtqid)		(&_kernel_dtqcb_tbl[(dtqid) - _KERNEL_DTQ_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_DTQ_CHECK_EXS(dtqid)	(_kernel_dtqcb_ro_tbl[(dtqid) - _KERNEL_DTQ_TMIN_ID].dtq != NULL)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_DTQCB					_kernel_dtqcb_tbl[];									/**< %jp{�f�[�^�L���[�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_DTQ_ID2DTQCB(dtqid)		(&_kernel_dtqcb_tbl[(dtqid) - _KERNEL_DTQ_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_DTQ_CHECK_EXS(dtqid)	(_kernel_dtqcb_tbl[(dtqid) - _KERNEL_DTQ_TMIN_ID].dtq != NULL)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_DTQCB					*_kernel_dtqcb_tbl[];									/**< %jp{�f�[�^�L���[�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_DTQ_ID2DTQCB(dtqid)		(_kernel_dtqcb_tbl[(dtqid) - _KERNEL_DTQ_TMIN_ID])		/**< %jp{�f�[�^�L���[ID����DTQCB �A�h���X���擾} */
#define _KERNEL_DTQ_CHECK_EXS(dtqid)	(_KERNEL_DTQ_ID2DTQCB(dtqid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*   Accessor for DTQCB                       */
/* ------------------------------------------ */

/* dtqcb_ro */
#if !_KERNEL_DTQCB_SPLIT_RO								
#define _KERNEL_DTQ_GET_DTQCB_RO(dtqid, dtqcb)	(dtqcb)
#else
#if _KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_BLKARRAY		/* %jp{DTQCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_DTQ_GET_DTQCB_RO(dtqid, dtqcb)	(&_kernel_dtqcb_ro_tbl[(dtqid)])
#elif _KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_PTRARRAY		/* %jp{DTQCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_DTQ_GET_DTQCB_RO(dtqid, dtqcb)	((dtqcb)->dtqcb_ro)
#endif
#endif


/* sque */
#define _KERNEL_DTQ_GET_SQUE(dtqcb)			(&(dtqcb)->sque)


/* rque */
#define _KERNEL_DTQ_GET_RQUE(dtqcb)			(&(dtqcb)->rque)


/* sdtqcnt */
#if _KERNEL_DTQCB_SDTQCNT
#define _KERNEL_DTQ_SET_SDTQCNT(dtqcb, x)	do { (dtqcb)->sdtqcnt = (_KERNEL_DTQCB_T_DTQCNT)(x); } while (0)
#define _KERNEL_DTQ_GET_SDTQCNT(dtqcb)		((_KERNEL_DTQ_T_DTQCNT)(dtqcb)->sdtqcnt)
#else
#define _KERNEL_DTQ_SET_SDTQCNT(dtqcb, x)	do { } while (0)
#define _KERNEL_DTQ_GET_SDTQCNT(dtqcb)		(0)
#endif


/* head */
#if _KERNEL_DTQCB_HEAD
#define _KERNEL_DTQ_SET_HEAD(dtqcb, x)		do { (dtqcb)->head = (_KERNEL_DTQCB_T_DTQCNT)(x); } while (0)
#define _KERNEL_DTQ_GET_HEAD(dtqcb)			((_KERNEL_DTQ_T_DTQCNT)(dtqcb)->head)
#else
#define _KERNEL_DTQ_SET_HEAD(dtqcb, x)		do { } while (0)
#define _KERNEL_DTQ_GET_HEAD(dtqcb)			(0)
#endif


/* dtqatr */
#if _KERNEL_DTQCB_DTQATR
#define _KERNEL_DTQ_SET_DTQATR(dtqcb, x)	do { (dtqcb)->dtqatr = (_KERNEL_DTQCB_T_DTQATR)(x); } while (0)
#define _KERNEL_DTQ_GET_DTQATR(dtqcb)		((_KERNEL_DTQ_T_DTQATR)(dtqcb)->dtqatr)
#else
#define _KERNEL_DTQ_SET_DTQATR(dtqcb, x)	do { } while (0)
#if _KERNEL_SPT_DTQ_TA_TFIFO
#define _KERNEL_DTQ_GET_DTQATR(dtqcb)		(TA_TFIFO)
#else
#define _KERNEL_DTQ_GET_DTQATR(dtqcb)		(TA_TPRI)
#endif
#endif


/* dtqcnt */
#if _KERNEL_DTQCB_DTQCNT
#define _KERNEL_DTQ_SET_DTQCNT(dtqcb_ro, x)	do { (dtqcb_ro)->dtqcnt = (_KERNEL_DTQCB_T_DTQCNT)(x); } while (0)
#define _KERNEL_DTQ_GET_DTQCNT(dtqcb_ro)	((_KERNEL_DTQ_T_DTQCNT)(dtqcb_ro)->dtqcnt)
#else
#define _KERNEL_DTQ_SET_DTQCNT(dtqcb_ro, x)	do { } while (0)
#define _KERNEL_DTQ_GET_DTQCNT(dtqcb_ro)	(0)
#endif


/* dtq */
#if _KERNEL_DTQCB_DTQ
#define _KERNEL_DTQ_SET_DTQ(dtqcb_ro, x)	do { (dtqcb_ro)->dtq = (VP_INT *)(x); } while (0)
#define _KERNEL_DTQ_GET_DTQ(dtqcb_ro)		((VP_INT *)(dtqcb_ro)->dtq)
#else
#define _KERNEL_DTQ_SET_DTQ(dtqcb_ro, x)	do { } while (0)
#define _KERNEL_DTQ_GET_DTQ(dtqcb_ro)		(0)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_DTQ_TA_TFIFO && _KERNEL_SPT_DTQ_TA_TPRI		/* %jp{TA_TFIFO �� TA_TPRI �̍��� } */
#define _KERNEL_DTQ_ADD_SQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_DTQ_GET_SQUE(dtqcb), tskhdl, _KERNEL_DTQ_GET_DTQATR(dtqcb_ro))
#define _KERNEL_DTQ_ADD_RQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_DTQ_GET_RQUE(dtqcb), tskhdl, _KERNEL_DTQ_GET_DTQATR(dtqcb_ro))
#elif _KERNEL_SPT_DTQ_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_DTQ_ADD_SQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_DTQ_GET_SQUE(dtqcb), tskhdl)
#define _KERNEL_DTQ_ADD_RQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_DTQ_GET_RQUE(dtqcb), tskhdl)
#elif !_KERNEL_SPT_DTQ_TA_TFIFO && _KERNEL_SPT_DTQ_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_DTQ_ADD_SQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_DTQ_GET_SQUE(dtqcb), tskhdl)
#define _KERNEL_DTQ_ADD_RQUE(dtqcb, dtqcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_DTQ_GET_RQUE(dtqcb), tskhdl)
#else
#error error:_KERNEL_SPT_DTQ_TA_TPRI and _KERNEL_SPT_DTQ_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_DTQ_RMV_SQUE(dtqcb, tskhdl)		_KERNEL_RMV_QUE(_KERNEL_DTQ_GET_SQUE(dtqcb), tskhdl)
#define _KERNEL_DTQ_RMV_RQUE(dtqcb, tskhdl)		_KERNEL_RMV_QUE(_KERNEL_DTQ_GET_RQUE(dtqcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_DTQ_RMH_SQUE(dtqcb)				_KERNEL_RMH_QUE(_KERNEL_DTQ_GET_SQUE(dtqcb))
#define _KERNEL_DTQ_RMH_RQUE(dtqcb)				_KERNEL_RMH_QUE(_KERNEL_DTQ_GET_RQUE(dtqcb))


/* %jp{�^�C���A�E�g�L���[����} */
#if _KERNEL_SPT_TSND_DTQ	/* %jp{tsnd_dtq�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_DTQ_ADD_STOQ(tskhdl, tmout)		_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#define _KERNEL_DTQ_RMV_STOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_DTQ_ADD_STOQ(tskhdl)			do { } while (0)
#define _KERNEL_DTQ_RMV_STOQ(tskhdl)			do { } while (0)
#endif

#if _KERNEL_SPT_TRCV_DTQ	/* %jp{trcv_dtq�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_DTQ_ADD_RTOQ(tskhdl, tmout)		_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#define _KERNEL_DTQ_RMV_RTOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_DTQ_ADD_RTOQ(tskhdl)			do { } while (0)
#define _KERNEL_DTQ_RMV_RTOQ(tskhdl)			do { } while (0)
#endif



/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER _kernel_cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);		/**< %jp{�f�[�^�L���[����}%en{Create Data queue} */
ER _kernel_snd_dtq(ID dtqid, VP_INT data, TMO tmout);		/**< %jp{�f�[�^�L���[�ւ̑��M(������)}%en{Send Data Queue} */
ER _kernel_rcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);	/**< %jp{�f�[�^�L���[�����M(������)}%en{Receive from Data Queue} */

#ifdef __cplusplus
}
#endif




#endif	/* _KERNEL__object__dtqobj_h__ */


/* end of file */
