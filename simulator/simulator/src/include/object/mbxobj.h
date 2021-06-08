/**
 *  Hyper Operating System V4 Advance
 *
 * @file  mbxobj.h
 * @brief %jp{���[���{�b�N�X�I�W�F�N�g�̃w�b�_�t�@�C��}%en{Mailbox object heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__object__mbxobj_h__
#define _KERNEL__object__mbxobj_h__



/* ------------------------------------------ */
/*  type definition                           */
/* ------------------------------------------ */

/* %jp{���[���{�b�N�X�����p�̌^(4bit�K�v)} */
#if _KERNEL_MBXCB_BITFIELD		/* %jp{MBXCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_MBX_T_MBXATR;			/**< %jp{���[���{�b�N�X���������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_MBXCB_T_MBXATR;			/**< %jp{���[���{�b�N�X������MBXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MBXCB_TBITDEF_MBXATR	: 3 + 1							/**< %jp{���[���{�b�N�X�����̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_MBX_T_MBXATR;			/**< %jp{���[���{�b�N�X���������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_MBXCB_T_MBXATR;			/**< %jp{���[���{�b�N�X������MBXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_MBXCB_TBITDEF_MBXATR	: 3								/**< %jp{���[���{�b�N�X�����̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{MBXCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_MBX_T_MBXATR;			/**< %jp{���[���{�b�N�X���������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_MBXCB_T_MBXATR;			/**< %jp{���[���{�b�N�X������MBXCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UB				_KERNEL_MBX_T_MBXATR;			/**< %jp{���[���{�b�N�X���������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_MBXCB_T_MBXATR;			/**< %jp{���[���{�b�N�X������MBXCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_MBXCB_TBITDEF_MBXATR									/**< %jp{���[���{�b�N�X�����̃r�b�g�t�B�[���h�錾���̕�} */

#endif


typedef	PRI		_KERNEL_MBX_T_MPRI;
typedef	PRI		_KERNEL_MBXCB_T_MPRI;
#define _KERNEL_MBXCB_TBITDEF_MPRI



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_MBXCB_SPLIT_RO

/** %jp{���[���{�b�N�X�R���g���[���u���b�N(���[�h�I�����[��)} */
typedef struct _kernel_t_mbxcb_rom
{
#if _KERNEL_MBXCB_MBXATR
	_KERNEL_MBXCB_T_MBXATR	mbxatr		_KERNEL_MBXCB_TBITDEF_MBXATR;		/**< %jp{���[���{�b�N�X����} */
#endif

#if _KERNEL_MBXCB_MAXMPRI
	_KERNEL_MBXCB_T_MPRI	maxmpri		_KERNEL_MBXCB_TBITDEF_MPRI;			/**< %jp{���M����郁�b�Z�[�W�̗D��x�̍ő�l} */
#endif
} _KERNEL_T_MBXCB_RO;

typedef const _KERNEL_T_MBXCB_RO	*_KERNEL_T_MBXCB_RO_PTR;


/** %jp{���[���{�b�N�X�R���g���[���u���b�N} */
typedef struct _kernel_t_mbxcb
{
#if _KERNEL_MBXCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�^�X�N�̑҂��s��} */
#endif

#if _KERNEL_MBXCB_MSGQUE
	VP						msgque;											/**< %jp{���b�Z�[�W�L���[} */
#endif

#if _KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_PTRARRAY
	_KERNEL_T_MBXCB_RO_PTR	mbxcb_ro;										/**< %jp{�R���g���[���u���b�NRO���ւ̃|�C���^} */
#endif
} _KERNEL_T_MBXCB;

typedef _KERNEL_T_MBXCB				*_KERNEL_T_MBXCB_PTR;


#else


/** %jp{���[���{�b�N�X�R���g���[���u���b�N} */
typedef struct _kernel_t_mbxcb
{
#if _KERNEL_MBXCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{�^�X�N�̑҂��s��} */
#endif

#if _KERNEL_MBXCB_MSGQUE
	VP						msgque;											/**< %jp{���b�Z�[�W�L���[} */
#endif

#if _KERNEL_MBXCB_MBXATR
	_KERNEL_MBXCB_T_MBXATR	mbxatr		_KERNEL_MBXCB_TBITDEF_MBXATR;		/**< %jp{���[���{�b�N�X����} */
#endif

#if _KERNEL_MBXCB_MAXMPRI
	_KERNEL_MBXCB_T_MPRI	maxmpri		_KERNEL_MBXCB_TBITDEF_MPRI;			/**< %jp{���M����郁�b�Z�[�W�̗D��x�̍ő�l} */
#endif
} _KERNEL_T_MBXCB;

typedef	_KERNEL_T_MBXCB				_KERNEL_T_MBXCB_RO;
typedef const _KERNEL_T_MBXCB_RO	*_KERNEL_T_MBXCB_RO_PTR;
typedef	_KERNEL_T_MBXCB				*_KERNEL_T_MBXCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_mbxid;										/**< %jp{���[���{�b�N�XID�̍ő�l} */

#define _KERNEL_MBX_TMIN_ID				1														/**< %jp{���[���{�b�N�XID�̍ŏ��l} */
#define _KERNEL_MBX_TMAX_ID				(_kernel_max_mbxid)										/**< %jp{���[���{�b�N�XID�̍ő�l} */

#define _KERNEL_MBX_CHECK_MBXID(mbxid)	((mbxid) >= _KERNEL_MBX_TMIN_ID && (mbxid) <= _KERNEL_MBX_TMAX_ID)



/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_BLKARRAY
#if _KERNEL_MBXCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_MBXCB					_kernel_mbxcb_tbl[];									/**< %jp{���[���{�b�N�X�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_MBXCB_RO			_kernel_mbxcb_ro_tbl[];									/**< %jp{���[���{�b�N�X�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_MBX_ID2MBXCB(mbxid)		(&_kernel_mbxcb_tbl[(mbxid) - _KERNEL_MBX_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MBX_CHECK_EXS(mbxid)	(_kernel_mbxcb_ro_tbl[(mbxid) - _KERNEL_MBX_TMIN_ID].mbxatr & _KERNEL_MBX_TA_CRE)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_MBX_TA_CRE				0x08													/**< %jp{mbxatr�̃r�b�g�ɐ����ς�bit�����蓖��} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_MBXCB					_kernel_mbxcb_tbl[];									/**< %jp{���[���{�b�N�X�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MBX_ID2MBXCB(mbxid)		(&_kernel_mbxcb_tbl[(mbxid) - _KERNEL_MBX_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_MBX_CHECK_EXS(mbxid)	(_kernel_mbxcb_tbl[(mbxid) - _KERNEL_MBX_TMIN_ID].mbxatr & _KERNEL_MBX_TA_CRE)
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_MBX_TA_CRE				0x08													/**< %jp{mbxatr�̃r�b�g�ɐ����ς�bit�����蓖��} */

#endif

#elif _KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_MBXCB					*_kernel_mbxcb_tbl[];									/**< %jp{���[���{�b�N�X�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_MBX_ID2MBXCB(mbxid)		(_kernel_mbxcb_tbl[(mbxid) - _KERNEL_MBX_TMIN_ID])		/**< %jp{���[���{�b�N�XID����MBXCB �A�h���X���擾} */
#define _KERNEL_MBX_CHECK_EXS(mbxid)	(_KERNEL_MBX_ID2MBXCB(mbxid) != NULL)					/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */
#define _KERNEL_MBX_TA_CRE				0

#else

#error error: _KERNEL_MBXCB_ALGORITHM

#endif



/* ------------------------------------------ */
/*   Accessor for MBXCB                       */
/* ------------------------------------------ */

/* mbxcb_ro */
#if !_KERNEL_MBXCB_SPLIT_RO								
#define _KERNEL_MBX_GET_MBXCB_RO(mbxid, mbxcb)	(mbxcb)
#else
#if _KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_BLKARRAY		/* %jp{MBXCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_MBX_GET_MBXCB_RO(mbxid, mbxcb)	(&_kernel_mbxcb_ro_tbl[(mbxid)])
#elif _KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_PTRARRAY		/* %jp{MBXCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_MBX_GET_MBXCB_RO(mbxid, mbxcb)	((mbxcb)->mbxcb_ro)
#endif
#endif


/* que */
#define _KERNEL_MBX_GET_QUE(mbxcb)				(&(mbxcb)->que)

/* mbxptn */
#if _KERNEL_MBXCB_MSGQUE
#define _KERNEL_MBX_SET_MSGQUE(mbxcb, x)		do { (mbxcb)->msgque = (VP)(x); } while (0)
#define _KERNEL_MBX_GET_MSGQUE(mbxcb)			((VP)&(mbxcb)->msgque)
#else
#define _KERNEL_MBX_SET_MSGQUE(mbxcb, x)		do { } while (0)
#define _KERNEL_MBX_GET_MSGQUE(mbxcb)			(0)
#endif


/* mbxatr */
#if _KERNEL_MBXCB_MBXATR
#define _KERNEL_MBX_SET_MBXATR(mbxcb_ro, x)		do { (mbxcb_ro)->mbxatr = (_KERNEL_MBXCB_T_MBXATR)(x); } while (0)
#define _KERNEL_MBX_GET_MBXATR(mbxcb_ro)		((_KERNEL_MBX_T_MBXATR)(mbxcb_ro)->mbxatr)
#else
#define _KERNEL_MBX_SET_MBXATR(mbxcb_ro, x)		do { } while (0)
#if _KERNEL_SPT_MBX_TA_TFIFO && _KERNEL_SPT_MBX_TA_MFIFO
#define _KERNEL_MBX_GET_MBXATR(mbxcb_ro)		(TA_TFIFO | TA_MFIFO)
#elif _KERNEL_SPT_MBX_TA_TFIFO && _KERNEL_SPT_MBX_TA_MPRI
#define _KERNEL_MBX_GET_MBXATR(mbxcb_ro)		(TA_TFIFO | TA_MPRI)
#elif _KERNEL_SPT_MBX_TA_MPRI && _KERNEL_SPT_MBX_TA_MFIFO
#define _KERNEL_MBX_GET_MBXATR(mbxcb_ro)		(TA_TFIFO | TA_FIFO)
#else
#define _KERNEL_MBX_GET_MBXATR(mbxcb_ro)		(TA_TPRI | TA_MPRI)
#endif
#endif

/* maxmpri */
#if _KERNEL_MBXCB_MAXMPRI
#define _KERNEL_MBX_SET_MAXMPRI(mbxcb_ro, x)	do { (mbxcb_ro)->maxmpri = (_KERNEL_MBXCB_T_MPRI)(x); } while (0)
#define _KERNEL_MBX_GET_MAXMPRI(mbxcb_ro)		((_KERNEL_MBX_T_MPRI)(mbxcb_ro)->maxmpri)
#else
#define _KERNEL_MBX_SET_MAXMPRI(mbxcb_ro, x)	do { } while (0)
#define _KERNEL_MBX_GET_MAXMPRI(mbxcb_ro)		(1)
#endif




/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{�L���[�ڑ�} */
#if _KERNEL_SPT_MBX_TA_TFIFO && _KERNEL_SPT_MBX_TA_TPRI		/* %jp{TA_TFIFO��TA_TPRI�����Ή�(�����Ŕ���)} */
#define _KERNEL_MBX_ADD_QUE(mbxcb, mbxcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_MBX_GET_QUE(mbxcb), tskhdl, _KERNEL_MBX_GET_MBXATR(mbxcb_ro))
#elif _KERNEL_SPT_MBX_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO �̂ݗ��p } */
#define _KERNEL_MBX_ADD_QUE(mbxcb, mbxcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_MBX_GET_QUE(mbxcb), tskhdl)
#elif !_KERNEL_SPT_MBX_TA_TFIFO && _KERNEL_SPT_MBX_TA_TPRI	/* %jp{TA_TPRI �̂ݗ��p } */
#define _KERNEL_MBX_ADD_QUE(mbxcb, mbxcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_MBX_GET_QUE(mbxcb), tskhdl)
#else
#error error:_KERNEL_SPT_MBX_TA_TPRI and _KERNEL_SPT_MBX_TA_TFIFO
#endif

/* %jp{�L���[���O��} */
#define _KERNEL_MBX_RMV_QUE(mbxcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_MBX_GET_QUE(mbxcb), tskhdl)

/* %jp{�L���[�擪���o��} */
#define _KERNEL_MBX_RMH_QUE(mbxcb)			_KERNEL_RMH_QUE(_KERNEL_MBX_GET_QUE(mbxcb))


/* %jp{�^�C���A�E�g�L���[����} */
#if _KERNEL_SPT_TRCV_MBX	/* %jp{trcv_mbx�T�|�[�g���̓^�C���A�E�g�L���[���l������} */
#define _KERNEL_MBX_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#define _KERNEL_MBX_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_MBX_ADD_TOQ(tskhdl)			do { } while (0)
#define _KERNEL_MBX_RMV_TOQ(tskhdl)			do { } while (0)
#endif


/* %jp{���b�Z�[�W�L���[����} */
#if _KERNEL_SPT_MBX_TA_MFIFO && _KERNEL_SPT_MBX_TA_MPRI		/* %jp{TA_MFIFO��TA_MPRI�����Ή�(�����Ŕ���)} */
#define _KERNEL_MBX_ADD_MSG(mbxcb, mbxcb_ro, pk_msg)	do { if ( _KERNEL_MBX_GET_MBXATR(mbxcb_ro) & TA_MPRI ) { _kernel_adp_msg((mbxcb), (pk_msg)); } else { _kernel_adf_msg((mbxcb), (pk_msg)); }} while(0)
#define _KERNEL_MBX_RMV_MSG(mbxcb, mbxcb_ro)			(_KERNEL_MBX_GET_MBXATR(mbxcb_ro) & TA_MPRI ? _kernel_rmp_msg((mbxcb), _KERNEL_MBX_GET_MAXMPRI(mbxcb_ro)) : _kernel_rmf_msg(mbxcb))
#elif _KERNEL_SPT_MBX_TA_MFIFO && !_KERNEL_SPT_MBX_TA_MPRI	/* %jp{TA_MFIFO �̂ݗ��p } */
#define _KERNEL_MBX_ADD_MSG(mbxcb, mbxcb_ro, pk_msg)	_kernel_adf_msg((mbxcb), (pk_msg))
#define _KERNEL_MBX_RMV_MSG(mbxcb, mbxcb_ro)			_kernel_rmf_msg(mbxcb)
#elif !_KERNEL_SPT_MBX_TA_MFIFO && _KERNEL_SPT_MBX_TA_MPRI	/* %jp{TA_MPRI �̂ݗ��p } */
#define _KERNEL_MBX_ADD_MSG(mbxcb, mbxcb_ro, pk_msg)	_kernel_adp_msg((mbxcb), (pk_msg))
#define _KERNEL_MBX_RMV_MSG(mbxcb, mbxcb_ro)			_kernel_rmp_msg((mbxcb), _KERNEL_MBX_GET_MAXMPRI(mbxcb_ro))
#else
#error error:_KERNEL_SPT_MBX_TA_MPRI and _KERNEL_SPT_MBX_TA_MFIFO
#endif

#ifdef __cplusplus
extern "C" {
#endif

ER     _kernel_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);							/**< %jp{���[���{�b�N�X�𐶐�} */
void   _kernel_adf_msg(_KERNEL_T_MBXCB_PTR mbxcb, T_MSG *pk_msg);					/**< %jp{FIFO�L���[�Ƀ��b�Z�[�W��ǉ�} */
void   _kernel_adp_msg(_KERNEL_T_MBXCB_PTR mbxcb, T_MSG *pk_msg);					/**< %jp{�D��x�L���[�Ƀ��b�Z�[�W��ǉ�} */
void   _kernel_add_msq(T_MSG **ppk_msgque, T_MSG *pk_msg);							/**< %jp{���b�Z�[�W�L���[�ւ̃��b�Z�[�W�ǉ�} */
T_MSG *_kernel_rmf_msg(_KERNEL_T_MBXCB_PTR mbxcb);									/**< %jp{FIFO�L���[���烁�b�Z�[�W�����o��} */
T_MSG *_kernel_rmp_msg(_KERNEL_T_MBXCB_PTR mbxcb, _KERNEL_MBXCB_T_MPRI maxmpri);	/**< %jp{�D��x�L���[���烁�b�Z�[�W�����o��} */
T_MSG *_kernel_rmv_msq(T_MSG **ppk_msgque);											/**< %jp{���b�Z�[�W�L���[���烁�b�Z�[�W���o��} */

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__mbxobj_h__ */



/* end of file */
