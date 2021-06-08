/**
 *  Hyper Operating System V4 Advance
 *
 * @file  sys.h
 * @brief %en{system heder file}%jp{�V�X�e������̃w�b�_�t�@�C��}
 *
 * Copyright (C) 1998-2009 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL__core_sys_h__
#define _KERNEL__core_sys_h__


#include "core/hep.h"
#include "core/tim.h"
#include "core/toq.h"
#include "core/tmq.h"
#include "core/dpc.h"


/* %jp{�V�X�e���̏��} */
#define _KERNEL_TSS_TSK			0x00		/**< %jp{�^�X�N�����s��} */
#define _KERNEL_TSS_LOC			0x01		/**< %jp{�����݋֎~(loc_cpu �L��)} */
#define _KERNEL_TSS_DSP			0x02		/**< %jp{�f�B�X�p�b�`�֎~ (dis_dsp �L��)} */
#define _KERNEL_TSS_CTX			0x04		/**< %jp{�^�X�N�Ɨ������s��} */
#define _KERNEL_TSS_SYS			0x08		/**< %jp{�V�X�e�����[�h} */


/** %jp{�v���Z�b�T������}%en{Processor control block} */
typedef struct _kernel_t_proccb
{
	STAT				stat;				/**< %jp{�V�X�e���̃R���e�L�X�g���}%en{system state} */
	UB                  dlydsp;				/**< %jp{�f�B�X�p�b�`�̃f�B���C�Ǘ�} */

#if _KERNEL_SPT_DPC
	UB                  svcent;				/**< %jp{�T�[�r�X�R�[�����s���Ǘ�} */
#endif

	_KERNEL_T_TSKHDL	tskhdl_run;			/**< %jp{���s���^�X�N} */
	_KERNEL_T_CTXCB		sysctxcb;			/**< %jp{�V�X�e���R���e�L�X�g(�A�C�h�����s��)�̃R���e�L�X�g} */
	SIZE				sysstksz;			/**< %jp{�V�X�e���R���e�L�X�g�̃X�^�b�N�T�C�Y} */
	VP					sysstk;				/**< %jp{�V�X�e���R���e�L�X�g�̃X�^�b�N} */
	SIZE				intstksz;			/**< %jp{�����݃R���e�L�X�g�̃X�^�b�N�T�C�Y} */
	VP					intstk;				/**< %jp{�����݃R���e�L�X�g�̃X�^�b�N} */
} _KERNEL_T_PROCCB;


/** %jp{�V�X�e��������}%en{system control block} */
typedef struct _kernel_t_syscb
{
	_KERNEL_T_RDQCB		rdqcb;				/**< %jp{���f�B�[�L���[}%en{ready-queue} */

	_KERNEL_T_TIMCB		timcb;

#if _KERNEL_SPT_TOQ
	_KERNEL_T_TOQCB		toqcb;				/**< %jp{�^�C���A�E�g�L���[}%en{timeout-queue} */
#endif

#if _KERNEL_SPT_TMQ
	_KERNEL_T_TMQCB		tmqcb;				/**< %jp{�^�C�}�L���[}%en{timer-queue} */
#endif

#if _KERNEL_SPT_HEP
	_KERNEL_T_HEPCB		hepcb;				/**< %jp{�J�[�l���������q�[�v}%en{kernel heap-memory control block} */
#endif

#if _KERNEL_SPT_DPC
	_KERNEL_T_DPCCB		dpccb;				/**< %jp{�x���v���V�[�W���R�[���p���b�Z�[�W�L���[} */
#endif

	_KERNEL_T_PROCCB	proccb[1];			/**< %jp{�v���Z�b�T������}%en{processor control block} */
} _KERNEL_T_SYSCB;


/** %jp{�V�X�e��������(���[�h�I�����[)}%en{system control block(read only)} */
typedef struct _kernel_t_syscb_ro
{
	_KERNEL_T_TIMCB_RO timcb_ro;
} _KERNEL_T_SYSCB_RO;


/** %jp{�V�X�e��������}%en{system control block} */
extern       _KERNEL_T_SYSCB		_kernel_syscb;
extern const _KERNEL_T_SYSCB_RO		_kernel_syscb_ro;

/* system */
#define _KERNEL_SYS_INI_SYS()				do {} while (0)														/**< %jp{�V�X�e���̏�����} */
#define _KERNEL_SYS_GET_PRC()				(0)																	/**< %jp{�v���Z�b�T�ԍ��擾} */
#define _KERNEL_SYS_GET_PRCCB()				(&_kernel_syscb.proccb[_KERNEL_SYS_GET_PRC()])						/**< %jp{�v���Z�b�T����u���b�N�̎擾} */

/* ready queue */
#define _KERNEL_SYS_GET_RDQ()				(&_kernel_syscb.rdqcb)												/**< %jp{���f�B�[�L���[�̎擾} */
#define _KERNEL_SYS_CRE_RDQ()				_KERNEL_CRE_RDQ(_KERNEL_SYS_GET_RDQ())								/**< %en{create ready-queue}%jp{���f�B�[�L���[�̐���} */
#define _KERNEL_SYS_DEL_RDQ()				_KERNEL_DEL_RDQ(_KERNEL_SYS_GET_RDQ())								/**< %en{delete ready-queue}%jp{���f�B�[�L���[�̍폜} */
#define _KERNEL_SYS_ADD_RDQ(tskhdl)			_KERNEL_ADD_RDQ(_KERNEL_SYS_GET_RDQ(), (tskhdl))					/**< %jp{�^�X�N�����f�B�[�L���[�ɒǉ�} */
#define _KERNEL_SYS_RMV_RDQ(tskhdl)			_KERNEL_RMV_RDQ(_KERNEL_SYS_GET_RDQ(), (tskhdl))					/**< %jp{�^�X�N�����f�B�[������O��} */
#define _KERNEL_SYS_RMH_RDQ()				_KERNEL_RMH_RDQ(_KERNEL_SYS_GET_RDQ())								/**< %jp{�L���[�̐擪�^�X�N�̎��O��} */
#define _KERNEL_SYS_REF_RDQ()				_KERNEL_REF_RDQ(_KERNEL_SYS_GET_RDQ())								/**< %jp{�L���[�̐擪�^�X�N�̎Q��} */
#define _KERNEL_SYS_ROT_RDQ(tskpri)			_KERNEL_ROT_RDQ(_KERNEL_SYS_GET_RDQ(), (tskpri))					/**< %jp{���f�B�[�L���[�̉�]} */

/* time */
#define _KERNEL_SYS_GET_TIMCB()				(&_kernel_syscb.timcb)
#define _KERNEL_SYS_GET_TIMCB_RO()			(&_kernel_syscb_ro.timcb_ro)
#define	_KERNEL_SYS_INI_TIM()				_KERNEL_INI_TIM(_KERNEL_SYS_GET_TIMCB(), _KERNEL_SYS_GET_TIMCB_RO())
#define	_KERNEL_SYS_SIG_TIM()				_KERNEL_SIG_TIM(_KERNEL_SYS_GET_TIMCB(), _KERNEL_SYS_GET_TIMCB_RO())
#define	_KERNEL_SYS_GET_TIC()				_KERNEL_GET_TIC(_KERNEL_SYS_GET_TIMCB(), _KERNEL_SYS_GET_TIMCB_RO())
#define	_KERNEL_SYS_SET_TIM(p_tim)			_KERNEL_SET_TIM(_KERNEL_SYS_GET_TIMCB(), (p_tim))
#define	_KERNEL_SYS_GET_TIM()				_KERNEL_GET_TIM(_KERNEL_SYS_GET_TIMCB())

/* timeout queue */
#define _KERNEL_SYS_GET_TOQCB()				(&_kernel_syscb.toqcb)												/**< %jp{�^�C���A�E�g�L���[�̎擾} */
#define _KERNEL_SYS_ADD_TOQ(tskhdl, tmout)	_KERNEL_ADD_TOQ(_KERNEL_SYS_GET_TOQCB(), (tskhdl), (tmout))
#define _KERNEL_SYS_RMV_TOQ(tskhd)			_KERNEL_RMV_TOQ(_KERNEL_SYS_GET_TOQCB(), (tskhd))
#define _KERNEL_SYS_SIG_TOQ(tictim)			_KERNEL_SIG_TOQ(_KERNEL_SYS_GET_TOQCB(), (tictim))

/* timer queue */
#define _KERNEL_SYS_GET_TMQ()				(&_kernel_syscb.tmqcb)												/**< %jp{�^�C�}�L���[�̎擾} */
#define _KERNEL_SYS_ADD_TMQ(pk_timobj)		_KERNEL_ADD_TMQ(_KERNEL_SYS_GET_TMQ(), (pk_timobj))
#define _KERNEL_SYS_RMV_TMQ(pk_timobj)		_KERNEL_RMV_TMQ(_KERNEL_SYS_GET_TMQ(), (pk_timobj))
#define _KERNEL_SYS_BSY_TMQ(pk_timobj)		_KERNEL_BSY_TMQ(_KERNEL_SYS_GET_TMQ(), (pk_timobj))
#define _KERNEL_SYS_SIG_TMQ(tictim)			_KERNEL_SIG_TMQ(_KERNEL_SYS_GET_TMQ(), (tictim))

/* kernel memory heap */
#define _KERNEL_SYS_GET_HEP()				(&_kernel_syscb.hepcb)												/**< %jp{�^�C�}�L���[�̎擾} */
#define _KERNEL_SYS_INI_HEP(hepsz, hep)		_KERNEL_CRE_HEP(_KERNEL_SYS_GET_HEP(), (hepsz), (hep))				/**< %jp{�J�[�l���������q�[�v�̏�����} */
#define _KERNEL_SYS_ALC_HEP(size)			_KERNEL_ALC_HEP(_KERNEL_SYS_GET_HEP(), (size))						/**< %jp{�J�[�l���������̊�����} */
#define _KERNEL_SYS_FRE_HEP(ptr)			_KERNEL_FRE_HEP(_KERNEL_SYS_GET_HEP(), (ptr))						/**< %jp{�J�[�l���������̊J��} */
#define _KERNEL_SYS_ALG_HEP(size)			_KERNEL_ALG_HEP(_KERNEL_SYS_GET_HEP(), (size))						/**< %jp{�J�[�l���������̃T�C�Y�A���C�����g} */

/* kernel dpc queue */
#if _KERNEL_SPT_DPC
#define _KERNEL_SYS_GET_DPC()				(&_kernel_syscb.dpccb)												/**< %jp{DPC�L���[�̎擾} */
#define _KERNEL_SYS_INI_DPC(que, quecnt)	_KERNEL_INI_DPC(_KERNEL_SYS_GET_DPC(), (que), (quecnt))				/**< %jp{DPC�L���[�̏�����} */
#define _KERNEL_SYS_REQ_DPC(svc, id, param)	_KERNEL_REQ_DPC(_KERNEL_SYS_GET_DPC(), (svc), (id), (param))		/**< %jp{DPC�L���[�֎��s���N�G�X�g} */
#define _KERNEL_SYS_EXE_DPC()				_KERNEL_EXE_DPC(_KERNEL_SYS_GET_DPC())								/**< %jp{DPC�L���[�̎��s} */
#else
#define _KERNEL_SYS_GET_DPC()				NULL																/**< %jp{DPC�L���[�̎擾} */
#define _KERNEL_SYS_INI_DPC(que, quecnt)	do {} while (0)														/**< %jp{DPC�L���[�̏�����} */
#define _KERNEL_SYS_REQ_DPC(svc, id, param)	E_NOMEM																/**< %jp{DPC�L���[�֎��s���N�G�X�g} */
#define _KERNEL_SYS_EXE_DPC()				do {} while (0)														/**< %jp{DPC�L���[�̎��s} */
#endif



#define _KERNEL_SYS_INI_SYSSTK(stksz, stk)	do { _KERNEL_SYS_GET_PRCCB()->sysstksz = (stksz); _KERNEL_SYS_GET_PRCCB()->sysstk = (stk); } while(0)
																												/**< %jp{�V�X�e���X�^�b�N�̏�����} */
#define _KERNEL_SYS_INI_INTSTK(stksz, stk)	_KERNEL_INI_INT((stksz), (stk))										/**< %jp{�����݃X�^�b�N�̏�����} */

#define _KERNEL_SYS_GET_STST()				(_KERNEL_SYS_GET_PRCCB()->stat)										/**< %jp{�J�����g�v���Z�b�T��Ԃ̎擾} */
#define _KERNEL_SYS_SET_STST(x)				do { _KERNEL_SYS_GET_PRCCB()->stat = (x); } while (0)				/**< %jp{�J�����g�v���Z�b�T��Ԃ̐ݒ�} */
#define _KERNEL_SYS_GET_RUNTSK()			(_KERNEL_SYS_GET_PRCCB()->tskhdl_run)								/**< %jp{�J�����g�v���Z�b�T�̎��s���^�X�N�擾} */
#define _KERNEL_SYS_SET_RUNTSK(x)			do { _KERNEL_SYS_GET_PRCCB()->tskhdl_run = (x); } while (0)			/**< %jp{�J�����g�v���Z�b�T�̎��s���^�X�N�ݒ�} */
#define _KERNEL_SYS_GET_SYSCTXCB()			(&_KERNEL_SYS_GET_PRCCB()->sysctxcb)								/**< %jp{�J�����g�v���Z�b�T�̃V�X�e���R���e�L�X�g�擾} */
#define _KERNEL_SYS_GET_SYSSTKSZ()			(_KERNEL_SYS_GET_PRCCB()->sysstksz)									/**< %jp{�J�����g�v���Z�b�T�̃V�X�e���R���e�L�X�g�̏����X�^�b�N�T�C�Y�擾} */
#define _KERNEL_SYS_GET_SYSSTK()			(_KERNEL_SYS_GET_PRCCB()->sysstk)									/**< %jp{�J�����g�v���Z�b�T�̃V�X�e���R���e�L�X�g�̏����X�^�b�N�A�h���X�擾} */
#define _KERNEL_SYS_GET_SYSISP()			((VP)((UB *)_KERNEL_SYS_GET_SYSSTK() + _KERNEL_SYS_GET_SYSSTKSZ()))	/**< %jp{�J�����g�v���Z�b�T�̃V�X�e���R���e�L�X�g�̏����X�^�b�N�|�C���^�擾} */


#if _KERNEL_PROCATR_SYS_CTX
#define _KERNEL_SYS_SET_CTX()				_KERNEL_PROC_SET_CTX()												/**< %jp{��^�X�N�R���e�L�X�g�ɐݒ�} */
#define _KERNEL_SYS_CLR_CTX()				_KERNEL_PROC_CLR_CTX()												/**< %jp{��^�X�N�R���e�L�X�g������} */
#define _KERNEL_SYS_SNS_CTX()				_KERNEL_PROC_SNS_CTX()												/**< %jp{�R���e�L�X�g��Ԃ��Q��} */
#else
#define _KERNEL_SYS_SET_CTX()				do { _KERNEL_SYS_GET_PRCCB()->stat |= _KERNEL_TSS_CTX; } while (0)	/**< %jp{��^�X�N�R���e�L�X�g�ɐݒ�} */
#define _KERNEL_SYS_CLR_CTX()				do { _KERNEL_SYS_GET_PRCCB()->stat &= ~_KERNEL_TSS_CTX; } while (0)	/**< %jp{��^�X�N�R���e�L�X�g������} */
#define _KERNEL_SYS_SNS_CTX()				((_KERNEL_SYS_GET_PRCCB()->stat & _KERNEL_TSS_CTX) ? TRUE : FALSE)	/**< %jp{�R���e�L�X�g��Ԃ��Q��} */
#endif

#if _KERNEL_PROCATR_SYS_LOC
#define _KERNEL_SYS_SET_LOC()				_KERNEL_PROC_SET_CTX()												/**< %jp{���b�N��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_LOC()				_KERNEL_PROC_CLR_CTX()												/**< %jp{���b�N��Ԃ�����} */
#define _KERNEL_SYS_SNS_LOC()				_KERNEL_PROC_SNS_CTX()												/**< %jp{���b�N��Ԃ��Q��} */
#else
#define _KERNEL_SYS_SET_LOC()				do { _KERNEL_SYS_GET_PRCCB()->stat |= _KERNEL_TSS_LOC; } while (0)	/**< %jp{���b�N��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_LOC()				do { _KERNEL_SYS_GET_PRCCB()->stat &= ~_KERNEL_TSS_LOC; } while (0)	/**< %jp{���b�N��Ԃ�����} */
#define _KERNEL_SYS_SNS_LOC()				((_KERNEL_SYS_GET_STST() & _KERNEL_TSS_LOC) ? TRUE : FALSE)			/**< %jp{���b�N��Ԃ��Q��} */
#endif

#if _KERNEL_PROCATR_SYS_DSP
#define _KERNEL_SYS_SET_DSP()				_KERNEL_PROC_SET_DSP()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_DSP()				_KERNEL_PROC_CLR_DSP()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�����} */
#define _KERNEL_SYS_SNS_DSP()				_KERNEL_PROC_SNS_DSP()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ��Q��} */
#else
#define _KERNEL_SYS_SET_DSP()				do { _KERNEL_SYS_GET_PRCCB()->stat |= _KERNEL_TSS_DSP; } while (0)	/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_DSP()				do { _KERNEL_SYS_GET_PRCCB()->stat &= ~_KERNEL_TSS_DSP; } while (0)	/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�����} */
#define _KERNEL_SYS_SNS_DSP()				((_KERNEL_SYS_GET_PRCCB()->stat & _KERNEL_TSS_DSP) ? TRUE : FALSE)	/**< %jp{�f�B�X�p�b�`�֎~��Ԃ��Q��} */
#endif

#if _KERNEL_PROCATR_SYS_SYS
#define _KERNEL_SYS_SET_SYS()				_KERNEL_PROC_SET_SYS()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_SYS()				_KERNEL_PROC_CLR_SYS()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�����} */
#define _KERNEL_SYS_SNS_SYS()				_KERNEL_PROC_SNS_SYS()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ��Q��} */
#else
#define _KERNEL_SYS_SET_SYS()				do { _KERNEL_SYS_GET_PRCCB()->stat |= _KERNEL_TSS_SYS; } while (0)	/**< %jp{�V�X�e����Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_SYS()				do { _KERNEL_SYS_GET_PRCCB()->stat &= ~_KERNEL_TSS_SYS; } while (0)	/**< %jp{�V�X�e����Ԃ�����} */
#define _KERNEL_SYS_SNS_SYS()				((_KERNEL_SYS_GET_PRCCB()->stat & _KERNEL_TSS_SYS) ? TRUE : FALSE)	/**< %jp{�V�X�e����Ԃ��Q��} */
#endif

#if _KERNEL_PROCATR_SYS_DLY
#define _KERNEL_SYS_SET_DLY()				_KERNEL_PROC_SET_DLY()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�ݒ�} */
#define _KERNEL_SYS_CLR_DLY()				_KERNEL_PROC_CLR_DLY()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ�����} */
#define _KERNEL_SYS_SNS_DLY()				_KERNEL_PROC_SNS_DLY()												/**< %jp{�f�B�X�p�b�`�֎~��Ԃ��Q��} */
#else
#define _KERNEL_SYS_SET_DLY()				do { _KERNEL_SYS_GET_PRCCB()->dlydsp = TRUE;} while (0)				/**< %jp{�f�B�X�p�b�`�x������ݒ�} */
#define _KERNEL_SYS_CLR_DLY()				do { _KERNEL_SYS_GET_PRCCB()->dlydsp = FALSE;} while (0)			/**< %jp{�f�B�X�p�b�`�x����������} */
#define _KERNEL_SYS_SNS_DLY()				(_KERNEL_SYS_GET_PRCCB()->dlydsp)									/**< %jp{�f�B�X�p�b�`�x�������Q��} */
#endif

#if !_KERNEL_PROCATR_SYS_CTX && !_KERNEL_PROCATR_SYS_LOC && !_KERNEL_PROCATR_SYS_DSP &&  !_KERNEL_PROCATR_SYS_SYS &&  !_KERNEL_PROCATR_SYS_DLY
#define _KERNEL_SYS_SNS_DPN()				((_KERNEL_SYS_GET_PRCCB()->stat != _KERNEL_TSS_TSK) ? TRUE : FALSE)	/**< %jp{�f�B�X�p�b�`�s�\���Q��} */
#else
#define _KERNEL_SYS_SNS_DPN()				(_KERNEL_SYS_SNS_CTX() || _KERNEL_SYS_SNS_LOC() || _KERNEL_SYS_SNS_DSP() || _KERNEL_SYS_SNS_SYS())
#endif


#if _KERNEL_SPT_DPC		/* %jp{�x���v���V�[�W���R�[���̏ꍇ} */

#define _KERNEL_SYS_SET_SVC()				do { _KERNEL_SYS_GET_PRCCB()->svcent = TRUE; } while (0)
#define _KERNEL_SYS_CLR_SVC()				do { _KERNEL_SYS_GET_PRCCB()->svcent = FALSE; } while (0)
#define _KERNEL_SYS_SNS_SVC()				(_KERNEL_SYS_GET_PRCCB()->svcent)

#define _KERNEL_ENTER_SVC()					do { _KERNEL_SYS_SET_SVC(); } while (0)
#define _KERNEL_LEAVE_SVC()					do { _KERNEL_SYS_EXE_DPC(); } while (0)

#define _KERNEL_SYS_LOC_DPC()				do { _KERNEL_DIS_INT(); } while (0)
#define _KERNEL_SYS_UNL_DPC()				do { if (!(_KERNEL_SYS_GET_STST() & _KERNEL_TSS_LOC)){ _KERNEL_ENA_INT(); } } while (0)
#define _KERNEL_SYS_SND_DPC(msg)			_KERNEL_DPC_SND_MSG(&_kernel_syscb.dpccb, (msg))
#define _KERNEL_SYS_RCV_DPC()				_KERNEL_DPC_RCV_MSG(&_kernel_syscb.dpccb)
#define _KERNEL_SYS_RDT_DPC()				_KERNEL_DPC_REF_DAT(&_kernel_syscb.dpccb)
#define _KERNEL_SYS_RFR_DPC()				_KERNEL_DPC_REF_FRE(&_kernel_syscb.dpccb)

#else					/* %jp{�o�Y���b�N�^�̏ꍇ} */

#define _KERNEL_ENTER_SVC()					do { _KERNEL_DIS_INT(); } while (0)
#if _KERNEL_PROCATR_SPT_MULTINT
#define _KERNEL_LEAVE_SVC()					do { if (!(_KERNEL_SYS_GET_STST() & (_KERNEL_TSS_LOC | _KERNEL_TSS_SYS))){ _KERNEL_ENA_INT(); } } while (0)
#else
#define _KERNEL_LEAVE_SVC()					do { if (!(_KERNEL_SYS_GET_STST() & (_KERNEL_TSS_LOC | _KERNEL_TSS_SYS | _KERNEL_TSS_CTX))){ _KERNEL_ENA_INT(); } } while (0)
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

void _kernel_cfg_ini(void);
void _kernel_cfg_sta(void);
void _kernel_idl_lop(void);				/**< %jp{�A�C�h�����[�v}%en{idle loop} */

#ifdef __cplusplus
}
#endif


#endif	/* _KERNEL__core_sys_h__ */




/* end of file */
