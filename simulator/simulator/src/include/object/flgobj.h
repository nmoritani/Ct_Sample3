/**
 *  Hyper Operating System V4 Advance
 *
 * @file  flgobj.h
 * @brief %jp{�C�x���g�t���O�I�W�F�N�g�̃w�b�_�t�@�C��}%en{Eventflag object heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__flgobj_h__
#define _KERNEL__object__flgobj_h__



/* ------------------------------------------ */
/*  type definition                           */
/* ------------------------------------------ */

/* %jp{�t���O�p�^�[���p�̌^} */
#if _KERNEL_FLGCB_BITFIELD		/* %jp{FLGCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_FLGCB_TBITDEF_FLGPTN	: _KERNEL_FLG_TBIT_FLGPTN + 1	/**< %jp{�t���O�p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_FLGCB_TBITDEF_FLGPTN	: _KERNEL_FLG_TBIT_FLGPTN		/**< %jp{�t���O�p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{FLGCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_FLG_TBIT_FLGPTN <= 7 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 8 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 15 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 16 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 31 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 32 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_FLG_TBIT_FLGPTN <= 63 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_FLG_T_FLGPTN;			/**< %jp{�t���O�p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_FLGCB_T_FLGPTN;			/**< %jp{�t���O�p�^�[����FLGCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_FLGCB_TBITDEF_FLGPTN									/**< %jp{�t���O�p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�C�x���g�t���O�����p�̌^(4bit�K�v)} */
#if _KERNEL_FLGCB_BITFIELD		/* %jp{FLGCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_FLG_T_FLGATR;			/**< %jp{�C�x���g�t���O���������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_FLGCB_T_FLGATR;			/**< %jp{�C�x���g�t���O������FLGCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_FLGCB_TBITDEF_FLGATR	: 4 + 1							/**< %jp{�C�x���g�t���O�����̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_FLG_T_FLGATR;			/**< %jp{�C�x���g�t���O���������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_FLGCB_T_FLGATR;			/**< %jp{�C�x���g�t���O������FLGCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_FLGCB_TBITDEF_FLGATR	: 4								/**< %jp{�C�x���g�t���O�����̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{FLGCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_FLG_T_FLGATR;			/**< %jp{�C�x���g�t���O���������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_FLGCB_T_FLGATR;			/**< %jp{�C�x���g�t���O������FLGCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UB				_KERNEL_FLG_T_FLGATR;			/**< %jp{�C�x���g�t���O���������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_FLGCB_T_FLGATR;			/**< %jp{�C�x���g�t���O������FLGCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_FLGCB_TBITDEF_FLGATR									/**< %jp{�C�x���g�t���O�����̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/** %jp{�҂��t���O���\����} */
typedef struct _kernel_t_flginf
{
	MODE   wfmode;		/**< %jp{�҂����[�h} */
	FLGPTN waiptn;		/**< %jp{�҂��r�b�g�p�^�[���i�������p�^�[���ƌ��p)} */
} _KERNEL_T_FLGINF;



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_FLGCB_SPLIT_RO


/** %jp{�C�x���g�t���O�R���g���[���u���b�N(���[�h�I�����[��)}%en{Eventflag Control Block(read-only)} */
typedef struct _kernel_t_flgcb_ro
{
#if _KERNEL_FLGCB_FLGATR
	_KERNEL_FLGCB_T_FLGATR	flgatr		_KERNEL_FLGCB_TBITDEF_FLGPTN;		/**< %jp{�C�x���g�t���O����} */
#endif
} _KERNEL_FLGCB_T_RO;

/** %jp{�C�x���g�t���O�R���g���[���u���b�N}%en{Eventflag Control Block} */
typedef struct _kernel_t_flgcb
{
#if _KERNEL_FLGCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�^�X�N�̑҂��s��} */
#endif

#if _KERNEL_FLGCB_FLGPTN
	_KERNEL_FLGCB_T_FLGPTN	flgptn		_KERNEL_FLGCB_TBITDEF_FLGPTN;		/**< %jp{�C�x���g�t���O�̃r�b�g�p�^�[��} */
#endif
} _KERNEL_T_FLGCB;


#else


/** %jp{�C�x���g�t���O�R���g���[���u���b�N} */
typedef struct _kernel_t_flgcb
{
#if _KERNEL_FLGCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�^�X�N�̑҂��s��} */
#endif

#if _KERNEL_FLGCB_FLGPTN
	_KERNEL_FLGCB_T_FLGPTN	flgptn		_KERNEL_FLGCB_TBITDEF_FLGPTN;		/**< %jp{�C�x���g�t���O�̃r�b�g�p�^�[��} */
#endif

#if _KERNEL_FLGCB_FLGATR
	_KERNEL_FLGCB_T_FLGATR	flgatr		_KERNEL_FLGCB_TBITDEF_FLGPTN;		/**< %jp{�C�x���g�t���O����} */
#endif
} _KERNEL_T_FLGCB;

typedef _KERNEL_T_FLGCB		_KERNEL_T_FLGCB_RO;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_flgid;										/**< %jp{�C�x���g�t���OID�̍ő�l} */

#define _KERNEL_FLG_TMIN_ID				1														/**< %jp{�C�x���g�t���OID�̍ŏ��l} */
#define _KERNEL_FLG_TMAX_ID				(_kernel_max_flgid)										/**< %jp{�C�x���g�t���OID�̍ő�l} */

#define _KERNEL_FLG_CHECK_FLGID(flgid)	((flgid) >= _KERNEL_FLG_TMIN_ID && (flgid) <= _KERNEL_FLG_TMAX_ID)



/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */


#if _KERNEL_FLGCB_ALGORITHM == _KERNEL_FLGCB_ALG_BLKARRAY
#if _KERNEL_FLGCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_FLGCB					_kernel_flgcb_tbl[];									/**< %jp{�C�x���g�t���O�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_FLGCB_RO			_kernel_flgcb_ro_tbl[];									/**< %jp{�C�x���g�t���O�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_FLG_ID2FLGCB(flgid)		(&_kernel_flgcb_tbl[(flgid) - _KERNEL_FLG_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_FLG_CHECK_EXS(flgid)	(_kernel_flgcb_ro_tbl[(flgid) - _KERNEL_FLG_TMIN_ID].flgatr & _KERNEL_FLG_TA_CRE)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_FLG_TA_CRE				0x08													/**< %jp{flgatr�̃r�b�g�ɐ����ς�bit�����蓖��} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_FLGCB					_kernel_flgcb_tbl[];									/**< %jp{�C�x���g�t���O�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_FLG_ID2FLGCB(flgid)		(&_kernel_flgcb_tbl[(flgid) - _KERNEL_FLG_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_FLG_CHECK_EXS(flgid)	(_kernel_flgcb_tbl[(flgid) - _KERNEL_FLG_TMIN_ID].flgatr & _KERNEL_FLG_TA_CRE)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_FLG_TA_CRE				0x08													/**< %jp{flgatr�̃r�b�g�ɐ����ς�bit�����蓖��} */

#endif

#elif _KERNEL_FLGCB_ALGORITHM == _KERNEL_FLGCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_FLGCB					*_kernel_flgcb_tbl[];									/**< %jp{�C�x���g�t���O�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_FLG_ID2FLGCB(flgid)		(_kernel_flgcb_tbl[(flgid) - _KERNEL_FLG_TMIN_ID])		/**< %jp{�C�x���g�t���OID����FLGCB �A�h���X���擾} */
#define _KERNEL_FLG_CHECK_EXS(flgid)	(_KERNEL_FLG_ID2FLGCB(flgid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_FLG_TA_CRE				0

#endif



/* ------------------------------------------ */
/*   Accessor for FLGCB                       */
/* ------------------------------------------ */

/* flgcb_ro */
#if !_KERNEL_FLGCB_SPLIT_RO								
#define _KERNEL_FLG_GET_FLGCB_RO(flgid, flgcb)	(flgcb)
#else
#if _KERNEL_FLGCB_ALGORITHM == _KERNEL_FLGCB_ALG_BLKARRAY		/* %jp{FLGCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_FLG_GET_FLGCB_RO(flgid, flgcb)	(&_kernel_flgcb_ro_tbl[(flgid)])
#elif _KERNEL_FLGCB_ALGORITHM == _KERNEL_FLGCB_ALG_PTRARRAY		/* %jp{FLGCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_FLG_GET_FLGCB_RO(flgid, flgcb)	((flgcb)->flgcb_ro)
#endif
#endif


/* que */
#define _KERNEL_FLG_GET_QUE(flgcb)				(&(flgcb)->que)

/* flgptn */
#if _KERNEL_FLGCB_FLGPTN
#define _KERNEL_FLG_SET_FLGPTN(flgcb, x)		do { (flgcb)->flgptn = (_KERNEL_FLGCB_T_FLGPTN)(x); } while (0)
#define _KERNEL_FLG_GET_FLGPTN(flgcb)			((_KERNEL_FLG_T_FLGPTN)(flgcb)->flgptn)
#else
#define _KERNEL_FLG_SET_FLGPTN(flgcb, x)		do { } while (0)
#define _KERNEL_FLG_GET_FLGPTN(flgcb)			(0)
#endif

/* flgatr */
#if _KERNEL_FLGCB_FLGATR
#define _KERNEL_FLG_SET_FLGATR(flgcb_ro, x)		do { (flgcb_ro)->flgatr = (_KERNEL_FLGCB_T_FLGATR)(x); } while (0)
#define _KERNEL_FLG_GET_FLGATR(flgcb_ro)		((_KERNEL_FLG_T_FLGATR)(flgcb_ro)->flgatr)
#else
#define _KERNEL_FLG_SET_FLGATR(flgcb_ro, x)		do { } while (0)
#if _KERNEL_SPT_FLG_TA_TFIFO
#define _KERNEL_FLG_GET_FLGATR(flgcb_ro)		(TA_TFIFO)
#else
#define _KERNEL_FLG_GET_FLGATR(flgcb_ro)		(TA_TPRI)
#endif
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_FLG_TA_TFIFO && _KERNEL_SPT_FLG_TA_TPRI		/* %jp{TA_TFIFO �� TA_TPRI �̍��� } */
#define _KERNEL_FLG_ADD_QUE(flgcb, flgcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_FLG_GET_QUE(flgcb), tskhdl, _KERNEL_FLG_GET_FLGATR(flgcb_ro))
#elif _KERNEL_SPT_FLG_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_FLG_ADD_QUE(flgcb, flgcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_FLG_GET_QUE(flgcb), tskhdl)
#elif !_KERNEL_SPT_FLG_TA_TFIFO && _KERNEL_SPT_FLG_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_FLG_ADD_QUE(flgcb, flgcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_FLG_GET_QUE(flgcb), tskhdl)
#else
#error error:_KERNEL_SPT_FLG_TA_TPRI and _KERNEL_SPT_FLG_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_FLG_RMV_QUE(flgcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_FLG_GET_QUE(flgcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_FLG_RMH_QUE(flgcb)			_KERNEL_RMH_QUE(_KERNEL_FLG_GET_QUE(flgcb))

/* %jp{�^�C���A�E�g�L���[�ڑ�} */
#if _KERNEL_SPT_TWAI_FLG	/* %jp{twai_sem�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_FLG_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#else
#define _KERNEL_FLG_ADD_TOQ(tskhdl)			do { } while (0)
#endif

/* %jp{�^�C���A�E�g�L���[����} */
#if _KERNEL_SPT_TWAI_FLG	/* %jp{twai_flg�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_FLG_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_FLG_RMV_TOQ(tskhdl)			do { } while (0)
#endif



/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER   _kernel_cre_flg(ID flgid, const T_CFLG *pk_cflg);
ER   _kernel_wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
BOOL _kernel_chk_flg(_KERNEL_T_FLGCB *flgcb, _KERNEL_T_FLGINF *pk_flginf);

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__flgobj_h__ */



/* end of file */
