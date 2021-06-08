/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  cfgknl.h
 * @brief %jp{�J�[�l���d�l�̃R���t�B�M�����[�V�����p�w�b�_�t�@�C��}%en{kernel configuration heder file}
 *
 * Copyright (C) 1998-2009 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


/*
%jp{
  �{�t�@�C���ɂāA�J�[�l�������̃R���t�B�M�����[�V�������s���B
  �{�t�@�C���̕ύX��̓J�[�l���̃��r���h���K�v�ł���B
  �܂��A�{�t�@�C���̓Z���u������̑O�����ɂ��g������z�肵�Ă���̂ŁA
C����\��(�Ⴆ��typedef�Ȃ�)�͂��̒��ɂ͋L�ڂ����A�}�N����`�Ȃǂ�
�v���v���Z�b�T�f�B���N�e�B�u�݂̂��L�ڂ��鎖�Ƃ���B
}
*/



#ifndef _KERNEL__config__cfgknl_h__
#define _KERNEL__config__cfgknl_h__



/* ---------------------------------------------- */
/*  Optimize                                      */
/* ---------------------------------------------- */

/* %jp{���l�̏��������̂�D�悵�čœK������} */
#define _KERNEL_CFG_OPT_RW_SIZE			1					/**< %jp{���[�h���C�g�f�[�^�T�C�Y(�ʏ��RAM�z�u)�̗D��x} */
#define _KERNEL_CFG_OPT_RO_SIZE			2					/**< %jp{���[�h�I�����[�f�[�^(�ʏ��ROM�z�u)�̃T�C�Y�̗D��x} */
#define _KERNEL_CFG_OPT_CODE_SIZE		2					/**< %jp{�R�[�h�T�C�Y(�ʏ��ROM�z�u)�̗D��x} */
#define _KERNEL_CFG_OPT_SPEED			3					/**< %jp{���s���x�̗D��x} */
#define _KERNEL_CFG_OPT_POWER			3					/**< %jp{����d�̗͂D��x} */



/* ---------------------------------------------- */
/*  ID number                                     */
/* ---------------------------------------------- */

/* %jp{�ő�I�u�W�F�N�gID�l} */
#define _KERNEL_CFG_TMAX_TSKID			127					/**< %jp{�^�X�NID�̍ő�l} */
#define _KERNEL_CFG_TMAX_SEMID			127					/**< %jp{�Z�}�t�HID�̍ő�l} */
#define _KERNEL_CFG_TMAX_FLGID			127					/**< %jp{�C�x���g�t���OID�̍ő�l} */
#define _KERNEL_CFG_TMAX_DTQID			127					/**< %jp{�f�[�^�L���[ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_MBXID			127					/**< %jp{���[���{�b�N�XID�̍ő�l} */
#define _KERNEL_CFG_TMAX_MTXID			127					/**< %jp{�~���[�e�b�N�XID�̍ő�l} */
#define _KERNEL_CFG_TMAX_MBFID			127					/**< %jp{���b�Z�[�W�o�b�t�@ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_PORID			127					/**< %jp{�����f�u�[ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_MPFID			127					/**< %jp{�Œ蒷�������v�[��ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_MPLID			127					/**< %jp{�ϒ��������v�[��ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_CYCID			127					/**< %jp{�����n���h��ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_ALMID			127					/**< %jp{�A���[���n���h��ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_OVRID			127					/**< %jp{�I�[�o�[�����n���h��ID�̍ő�l} */
#define _KERNEL_CFG_TMAX_ISRID			127					/**< %jp{�����݃T�[�r�X���[�`��ID�̍ő�l} */

/* %jp{�R���t�B�M�����[�^���w�莞�f�t�H���g�ő�ID�l} */
#define _KERNEL_CFG_DEF_TMAX_TSKID		15					/**< %jp{�^�X�NID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_SEMID		15					/**< %jp{�Z�}�t�HID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_FLGID		15					/**< %jp{�C�x���g�t���OID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_DTQID		15					/**< %jp{�f�[�^�L���[ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_MBXID		15					/**< %jp{���[���{�b�N�XID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_MTXID		15					/**< %jp{�~���[�e�b�N�XID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_MBFID		15					/**< %jp{���b�Z�[�W�o�b�t�@ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_PORID		15					/**< %jp{�����f�u�[ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_MPFID		15					/**< %jp{�Œ蒷�������v�[��ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_MPLID		15					/**< %jp{�ϒ��������v�[��ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_CYCID		15					/**< %jp{�����n���h��ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_ALMID		15					/**< %jp{�A���[���n���h��ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_OVRID		15					/**< %jp{�I�[�o�[�����n���h��ID�̍ő�l} */
#define _KERNEL_CFG_DEF_TMAX_ISRID		15					/**< %jp{�����݃T�[�r�X���[�`��ID�̍ő�l} */



/* ---------------------------------------------- */
/*  Kernel-internal                               */
/* ---------------------------------------------- */

/* %jp{�x���v���V�[�W���[�R�[��}%en{Deferred Procedure Call} */
#define _KERNEL_CFG_DPC					FALSE

/* %jp{�Ώ̌^�}���`�v���Z�b�T�Ή�[������]}{%en{Symmetric Multiple Processor[unsupported]} */
#define _KERNEL_CFG_SMP					FALSE

/* %jp{���d�����ݑΉ�}%en{Multiple interrupt} */
#define _KERNEL_CFG_MULTIPLE_INT		TRUE

/* %jp{�V�X�e���^�X�N��TCB�����蓖�Ă�(���������邪����������⑝����H) [������]} */
#define _KERNEL_CFG_SYSTSK_TCB			FALSE

/* %jp{���s���Ƀ^�X�N�����f�B�[�L���[�Ɍq�����܂܂Ƃ��� [������]} */
#define _KERNEL_CFG_RUNTSK_ON_RDQ		TRUE

/* %jp{�T�X�y���h���Ƀ^�X�N�����f�B�[�L���[�Ɍq�����܂܂Ƃ��� [������]} */
#define _KERNEL_CFG_SUSTSK_ON_RDQ		FALSE


/* %jp{�^�X�N�n���h����ID�ŊǗ�(�ȃ����������ᑬ)�ɂ��邩�ǂ���} */
#define _KERNEL_CFG_TSKHDL_ID			TRUE

/* %jp{�~���[�e�b�N�X�n���h����ID�ŊǗ�(�ȃ����������ᑬ)�ɂ��邩�ǂ��� [������]} */
#define _KERNEL_CFG_MTXHDL_ID			TRUE

/* %jp{�����݃T�[�r�X���[�`���n���h����ID�ŊǗ�(�ȃ����������ᑬ)�ɂ��邩�ǂ���} */
#define _KERNEL_CFG_ISRHDL_ID			FALSE



/* ---------------------------------------------- */
/*  General task-queue                            */
/* ---------------------------------------------- */

/** %jp{�L���[�̃A���S���Y��} */
#define _KERNEL_CFG_QUE_ALGORITHM		_KERNEL_QUE_ALG_ONEWAYLIST

/* %jp{
   _KERNEL_QUE_ALG_ONEWAYLIST : �P�����L���[(�ȃ������������O�����x��)
   _KERNEL_QUE_ALG_TWOWAYLIST : �o�����L���[(���O��������)
   _KERNEL_QUE_ALG_AUTO       : �����I��(�œK���w�肩�玩���őI������)
}%en{
   _KERNEL_QUE_ALG_ONEWAYLIST : small-memory
   _KERNEL_QUE_ALG_TWOWAYLIST : high-speed
   _KERNEL_QUE_ALG_AUTO       : auto select
}*/



/* ---------------------------------------------- */
/*  Ready-queue                                   */
/* ---------------------------------------------- */

/** %jp{���f�B�[�L���[�̃A���S���Y��} */
#define _KERNEL_CFG_RDQ_ALGORITHM		_KERNEL_RDQ_ALG_SINGLE_QUE

/* %jp{
   _KERNEL_RDQ_ALG_SINGLE_QUE         : �V���O���L���[(�ȃ����������A�^�X�N����������ƒx��)
   _KERNEL_RDQ_ALG_ARRAYED_QUE        : �D��x�������L���[��z��(������x���������A�D��x���Ń���������)
   _KERNEL_RDQ_ALG_BITMAP_ARRAYED_QUE : �z�񉻃L���[�ɒT���r�b�g�}�b�v�������(�D��x�������Ȃ���΍���)   [������]
   _KERNEL_RDQ_ALG_HEAP_QUE           : �q�[�v��(�D��x���������Ă����������ق���)                         [������]
}%en{
   _KERNEL_RDQ_ALG_SINGLE_QUE         : 
   _KERNEL_RDQ_ALG_ARRAYED_QUE        : 
   _KERNEL_RDQ_ALG_BITMAP_ARRAYED_QUE : 
   _KERNEL_RDQ_ALG_HEAP_QUE           : 
}*/



/* ---------------------------------------------- */
/*  Tasks                                         */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_TSK_TA_ACT			TRUE				/**< %jp{TA_TACT�ɑΉ�����} */


/** %jp{�^�X�N�R���g���[���u���b�N�̊Ǘ��A���S���Y��} */
#define _KERNEL_CFG_TCB_ALGORITHM		_KERNEL_TCB_ALG_PTRARRAY

/* %jp{
   _KERNEL_TCB_ALG_BLKARRAY	: TCB�u���b�N���̂�z�񉻂��ĊǗ�(�\�߃u���b�N���m��)
   _KERNEL_TCB_ALG_PTRARRAY	: TCB���w���|�C���^��z�񉻂��ĊǗ�(�u���b�N�{�͓̂��I�Ƀ������m��)
}*/


#define _KERNEL_CFG_TCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_TCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */
#define _KERNEL_CFG_TCB_TTW_PACK		TRUE				/**< %jp{�҂��v�������k���ĕێ����邩} */



/* ---------------------------------------------- */
/*  Task Exception Handling Routine               */
/* ---------------------------------------------- */

/** %jp{�^�X�N��O�������[�`���R���g���[���u���b�N�̊Ǘ��A���S���Y��} */
#define _KERNEL_CFG_TEXCB_ALGORITHM		_KERNEL_TEXCB_ALG_PTRARRAY

/* %jp{
   _KERNEL_TCB_ALG_BLKARRAY	: TCB�u���b�N���̂�z�񉻂��ĊǗ�(�\�߃u���b�N���m��)
   _KERNEL_TCB_ALG_PTRARRAY	: TCB���w���|�C���^��z�񉻂��ĊǗ�(�u���b�N�{�͓̂��I�Ƀ������m��)
}*/

#define _KERNEL_CFG_TEXCB_SPLIT_RO		FALSE				/**< %jp{TEXCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_TEXCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TEXCB�����k���邩} */



/* ---------------------------------------------- */
/*  Smaphores                                     */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_SEM_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_SEM_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_CFG_SEM_MAXSEM			TRUE				/**< %jp{maxsem(����`�F�b�N)���g��} */

/* Control block */
#define _KERNEL_CFG_SEMCB_ALGORITHM		_KERNEL_SEMCB_ALG_PTRARRAY
#define _KERNEL_CFG_SEMCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_SEMCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */



/* ---------------------------------------------- */
/*  Eventflags                                    */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_FLG_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_FLG_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_CFG_FLG_TA_WSGL			TRUE				/**< %jp{TA_WSGL�����ɑΉ�����} */
#define _KERNEL_CFG_FLG_TA_WMUL			TRUE				/**< %jp{TA_WMUL�����ɑΉ�����} */
#define _KERNEL_CFG_FLG_TA_CLR			TRUE				/**< %jp{TA_CLR�����ɑΉ�����} */

/* Control block */
#define _KERNEL_CFG_FLGCB_ALGORITHM		_KERNEL_FLGCB_ALG_PTRARRAY
#define _KERNEL_CFG_FLGCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_FLGCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */


/* ---------------------------------------------- */
/*  Data queues                                   */
/* ---------------------------------------------- */

/* Configuration */
#define _KERNEL_CFG_DTQ_DTQCNT_ZERO		TRUE				/**< %jp{�L���[�T�C�Y0�ɑΉ�����} */
#define _KERNEL_CFG_DTQ_DTQCNT_NONZERO	TRUE				/**< %jp{�L���[�T�C�Y��0�ɑΉ�����} */

/* Attribute */
#define _KERNEL_CFG_DTQ_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_DTQ_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */

/* Control block */
#define _KERNEL_CFG_DTQCB_ALGORITHM		_KERNEL_DTQCB_ALG_PTRARRAY
#define _KERNEL_CFG_DTQCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_DTQCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */


/* ---------------------------------------------- */
/*  Mailboxes                                     */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_MBX_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_MBX_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_CFG_MBX_TA_MFIFO		TRUE				/**< %jp{TA_MFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_MBX_TA_MPRI			TRUE				/**< %jp{TA_MPRI�����ɑΉ�����} */


/* Algorithm */
#define _KERNEL_CFG_MBX_ALGORITHM		_KERNEL_MBX_ALG_ARRAYED_MQUE
/* %jp{
   _KERNEL_MBX_ALG_SINGLE_MQUE  : ��{�̃��b�Z�[�W�L���[�ō\������(�D��x�T������̂Œᑬ)          [������]
   _KERNEL_MBX_ALG_ARRAYED_MQUE : �D��x�̐������z���ɃL���[������(�D��x���ɂ���ă�����������)
}*/


/* Control block */
#define _KERNEL_CFG_MBXCB_ALGORITHM		_KERNEL_MBXCB_ALG_PTRARRAY
#define _KERNEL_CFG_MBXCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_MBXCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */



/* ---------------------------------------------- */
/*  Mutex                                         */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_MTX_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_MTX_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_CFG_MTX_TA_INHERIT		TRUE				/**< %jp{TA_INHERIT�����ɑΉ�����} */
#define _KERNEL_CFG_MTX_TA_CEILING		TRUE				/**< %jp{TA_CEILING�����ɑΉ�����} */

/* Control block */
#define _KERNEL_CFG_MTXCB_ALGORITHM		_KERNEL_MTXCB_ALG_PTRARRAY
#define _KERNEL_CFG_MTXCB_SPLIT_RO		FALSE				/**< %jp{TCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_MTXCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */



/* ---------------------------------------------- */
/*  Fixed-sized Memory Pools                      */
/* ---------------------------------------------- */

/* Attribute */
#define _KERNEL_CFG_MPF_TA_TFIFO		TRUE				/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_CFG_MPF_TA_TPRI			TRUE				/**< %jp{TA_TPRI�����ɑΉ�����} */

/* Value range */
#define _KERNEL_CFG_MPF_TMAX_BLKCNT		(-1)				/**< %jp{�u���b�N���̍ő�l} */
#define _KERNEL_CFG_MPF_TMAX_BLKSZ		(-1)				/**< %jp{�u���b�N�T�C�Y�̍ő�l} */

/* Algorithm */
#define _KERNEL_CFG_MPF_ALGORITHM		_KERNEL_MPF_ALG_CHAIN_NUM
/* %jp{
   _KERNEL_MPF_ALG_CHAIN_PTR : �󂫃u���b�N���|�C���^�Ń`�F�C��(��Z��̖���CPU�ł�����)
   _KERNEL_MPF_ALG_CHAIN_NUM : �󂫃u���b�N���u���b�N�ԍ��Ń`�F�C��(���������팸�ł���ꍇ����)
}*/

/* Control block */
#define _KERNEL_CFG_MPFCB_ALGORITHM		_KERNEL_MPFCB_ALG_PTRARRAY
#define _KERNEL_CFG_MPFCB_SPLIT_RO		FALSE				/**< %jp{MPFCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_MPFCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */



/* ------------------------------------------------------------------ */
/*  System Time Management                                            */
/* ------------------------------------------------------------------ */

/* %jp{�^�C���e�B�b�N�̎���}%en{Time Tick Period} */
#define _KERNEL_CFG_FRACTIONAL_TIMTIC	TRUE				/**< %jp{�R���t�B�M�����[�^�Ń^�C���e�B�b�N�̕����w�������} */
#define _KERNEL_CFG_TIC_NUME			1					/**< %jp{�f�t�H���g�̃^�C���e�B�b�N�����̕��q} */
#define _KERNEL_CFG_TIC_DENO			1					/**< %jp{�f�t�H���g�̃^�C���e�B�b�N�����̕���} */



/* ------------------------------------------------------------------ */
/*  Cyclic Handlers                                                   */
/* ------------------------------------------------------------------ */

/* Attribute */
#define _KERNEL_CFG_CYC_TA_STA			TRUE				/**< %jp{TA_STA�����ɑΉ�����} */
#define _KERNEL_CFG_CYC_TA_PHS			TRUE				/**< %jp{TA_PHS�����ɑΉ�����} */

/* Control block */
#define _KERNEL_CFG_CYCCB_ALGORITHM		_KERNEL_CYCCB_ALG_PTRARRAY
#define _KERNEL_CFG_CYCCB_SPLIT_RO		FALSE				/**< %jp{CYCCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_CYCCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */



/* ---------------------------------------------- */
/*  Interrupt Service Routines                    */
/* ---------------------------------------------- */

/* Control block */
#define _KERNEL_CFG_ISRCB_ALGORITHM		_KERNEL_ISRCB_ALG_PTRARRAY
#define _KERNEL_CFG_ISRCB_SPLIT_RO		FALSE				/**< %jp{ISRCB�̕s�ϕ��𕪊�����ROM���z�u�Ƃ��邩} */
#define _KERNEL_CFG_ISRCB_BITFIELD		FALSE				/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */





/* ---------------------------------------------- */
/*  Service call support                          */
/* ---------------------------------------------- */

/* Task management functions */
#define _KERNEL_CFG_CRE_TSK				TRUE				/* cre_tsk */
#define _KERNEL_CFG_ACRE_TSK			TRUE				/* acre_tsk */
#define _KERNEL_CFG_DEL_TSK				TRUE				/* del_tsk */
#define _KERNEL_CFG_ACT_TSK				TRUE				/* act_tsk */
#define _KERNEL_CFG_IACT_TSK			TRUE				/* iact_tsk */
#define _KERNEL_CFG_CAN_ACT 			TRUE				/* can_act */
#define _KERNEL_CFG_STA_TSK 			TRUE				/* sta_tsk */
#define _KERNEL_CFG_EXT_TSK 			TRUE				/* ext_tsk */
#define _KERNEL_CFG_EXD_TSK 			TRUE				/* exd_tsk */
#define _KERNEL_CFG_TER_TSK 			TRUE				/* ter_tsk */
#define _KERNEL_CFG_CHG_PRI 			TRUE				/* chg_pri */
#define _KERNEL_CFG_GET_PRI 			TRUE				/* get_pri */
#define _KERNEL_CFG_REF_TSK 			TRUE				/* ref_tsk */
#define _KERNEL_CFG_REF_TST 			TRUE				/* ref_tst */

/* Task dependent synchronization functions */
#define _KERNEL_CFG_SLP_TSK 			TRUE				/* slp_tsk */
#define _KERNEL_CFG_TSLP_TSK			TRUE				/* tslp_tsk */
#define _KERNEL_CFG_WUP_TSK 			TRUE				/* wup_tsk */
#define _KERNEL_CFG_IWUP_TSK			TRUE				/* iwup_tsk */
#define _KERNEL_CFG_CAN_WUP 			TRUE				/* can_wup */
#define _KERNEL_CFG_REL_WAI 			TRUE				/* rel_wai */
#define _KERNEL_CFG_IREL_WAI			TRUE				/* irel_wai */
#define _KERNEL_CFG_SUS_TSK 			TRUE				/* sus_tsk */
#define _KERNEL_CFG_RSM_TSK 			TRUE				/* rsm_tsk */
#define _KERNEL_CFG_FRSM_TSK			TRUE				/* frsm_tsk */
#define _KERNEL_CFG_DLY_TSK 			TRUE				/* dly_tsk */

/* Task exception handling functions */
#define _KERNEL_CFG_DEF_TEX 			TRUE				/* def_tex */
#define _KERNEL_CFG_RAS_TEX 			TRUE				/* ras_tex */
#define _KERNEL_CFG_IRAS_TEX			TRUE				/* iras_tex */
#define _KERNEL_CFG_DIS_TEX 			TRUE				/* dis_tex */
#define _KERNEL_CFG_ENA_TEX 			TRUE				/* ena_tex */
#define _KERNEL_CFG_SNS_TEX 			TRUE				/* sns_tex */
#define _KERNEL_CFG_REF_TEX 			TRUE				/* ref_tex */

/* Semaphores */
#define _KERNEL_CFG_CRE_SEM 			TRUE				/* cre_sem */
#define _KERNEL_CFG_ACRE_SEM			TRUE				/* acre_sem */
#define _KERNEL_CFG_DEL_SEM 			TRUE				/* del_sem */
#define _KERNEL_CFG_SIG_SEM 			TRUE				/* sig_sem */
#define _KERNEL_CFG_ISIG_SEM			TRUE				/* isig_sem */
#define _KERNEL_CFG_WAI_SEM 			TRUE				/* wai_sem */
#define _KERNEL_CFG_POL_SEM 			TRUE				/* pol_sem */
#define _KERNEL_CFG_TWAI_SEM			TRUE				/* twai_sem */
#define _KERNEL_CFG_REF_SEM 			TRUE				/* ref_sem */

/* Eventflags */
#define _KERNEL_CFG_CRE_FLG 			TRUE				/* cre_flg */
#define _KERNEL_CFG_ACRE_FLG			TRUE				/* acre_flg */
#define _KERNEL_CFG_DEL_FLG 			TRUE				/* del_flg */
#define _KERNEL_CFG_SET_FLG 			TRUE				/* set_flg */
#define _KERNEL_CFG_ISET_FLG			TRUE				/* iset_flg */
#define _KERNEL_CFG_CLR_FLG 			TRUE				/* clr_flg */
#define _KERNEL_CFG_WAI_FLG 			TRUE				/* wai_flg */
#define _KERNEL_CFG_POL_FLG 			TRUE				/* pol_flg */
#define _KERNEL_CFG_TWAI_FLG			TRUE				/* twai_flg */
#define _KERNEL_CFG_REF_FLG 			TRUE				/* ref_flg */

/* Data queues */
#define _KERNEL_CFG_CRE_DTQ 			TRUE				/* cre_dtq */
#define _KERNEL_CFG_ACRE_DTQ			TRUE				/* acre_dtq */
#define _KERNEL_CFG_DEL_DTQ 			TRUE				/* del_dtq */
#define _KERNEL_CFG_SND_DTQ 			TRUE				/* snd_dtq */
#define _KERNEL_CFG_PSND_DTQ			TRUE				/* psnd_dtq */
#define _KERNEL_CFG_IPSND_DTQ			TRUE				/* ipsnd_dtq */
#define _KERNEL_CFG_TSND_DTQ			TRUE				/* tsnd_dtq */
#define _KERNEL_CFG_FSND_DTQ			TRUE				/* fsnd_dtq */
#define _KERNEL_CFG_IFSND_DT			TRUE				/* ifsnd_dtq */
#define _KERNEL_CFG_RCV_DTQ 			TRUE				/* rcv_dtq */
#define _KERNEL_CFG_PRCV_DTQ			TRUE				/* prcv_dtq */
#define _KERNEL_CFG_TRCV_DTQ			TRUE				/* trcv_dtq */
#define _KERNEL_CFG_REF_DTQ 			TRUE				/* ref_dtq */

/* Mailboxes */
#define _KERNEL_CFG_CRE_MBX 			TRUE				/* cre_mbx */
#define _KERNEL_CFG_ACRE_MBX			TRUE				/* acre_mbx */
#define _KERNEL_CFG_DEL_MBX 			TRUE				/* del_mbx */
#define _KERNEL_CFG_SND_MBX 			TRUE				/* snd_mbx */
#define _KERNEL_CFG_RCV_MBX 			TRUE				/* rcv_mbx */
#define _KERNEL_CFG_PRCV_MBX			TRUE				/* prcv_mbx */
#define _KERNEL_CFG_TRCV_MBX			TRUE				/* trcv_mbx */
#define _KERNEL_CFG_REF_MBX 			TRUE				/* ref_mbx */

/* Mutexes */
#define _KERNEL_CFG_CRE_MTX 			TRUE				/* cre_mtx */
#define _KERNEL_CFG_ACRE_MTX			TRUE				/* acre_mtx */
#define _KERNEL_CFG_DEL_MTX 			TRUE				/* del_mtx */
#define _KERNEL_CFG_LOC_MTX 			TRUE				/* loc_mtx */
#define _KERNEL_CFG_PLOC_MTX			TRUE				/* ploc_mtx */
#define _KERNEL_CFG_TLOC_MTX			TRUE				/* tloc_mtx */
#define _KERNEL_CFG_UNL_MTX 			TRUE				/* unl_mtx */
#define _KERNEL_CFG_REF_MTX 			TRUE				/* ref_mtx */

/* Message buffers */
#define _KERNEL_CFG_CRE_MBF 			FALSE				/* cre_mbf */
#define _KERNEL_CFG_ACRE_MBF			FALSE				/* acre_mbf */
#define _KERNEL_CFG_DEL_MBF 			FALSE				/* del_mbf */
#define _KERNEL_CFG_SND_MBF 			FALSE				/* snd_mbf */
#define _KERNEL_CFG_PSND_MBF			FALSE				/* psnd_mbf */
#define _KERNEL_CFG_TSND_MBF			FALSE				/* tsnd_mbf */
#define _KERNEL_CFG_RCV_MBF 			FALSE				/* rcv_mbf */
#define _KERNEL_CFG_PRCV_MBF			FALSE				/* prcv_mbf */
#define _KERNEL_CFG_TRCV_MBF			FALSE				/* trcv_mbf */
#define _KERNEL_CFG_REF_MBF 			FALSE				/* ref_mbf */

/* Rendezvous */
#define _KERNEL_CFG_CRE_POR 			FALSE				/* cre_por */
#define _KERNEL_CFG_ACRE_POR			FALSE				/* acre_por */
#define _KERNEL_CFG_DEL_POR 			FALSE				/* del_por */
#define _KERNEL_CFG_CAL_POR 			FALSE				/* cal_por */
#define _KERNEL_CFG_TCAL_POR			FALSE				/* tcal_por */
#define _KERNEL_CFG_ACP_POR 			FALSE				/* acp_por */
#define _KERNEL_CFG_PACP_POR			FALSE				/* pacp_por */
#define _KERNEL_CFG_TACP_POR			FALSE				/* tacp_por */
#define _KERNEL_CFG_FWD_POR 			FALSE				/* fwd_por */
#define _KERNEL_CFG_RPL_RDV 			FALSE				/* rpl_rdv */
#define _KERNEL_CFG_REF_POR 			FALSE				/* ref_por */
#define _KERNEL_CFG_REF_RDV 			FALSE				/* ref_rdv */

/* Fixed-sized memory pools */
#define _KERNEL_CFG_CRE_MPF 			TRUE				/* cre_mpf */
#define _KERNEL_CFG_ACRE_MPF			TRUE				/* acre_mpf */
#define _KERNEL_CFG_DEL_MPF 			TRUE				/* del_mpf */
#define _KERNEL_CFG_GET_MPF 			TRUE				/* get_mpf */
#define _KERNEL_CFG_PGET_MPF			TRUE				/* pget_mpf */
#define _KERNEL_CFG_TGET_MPF			FALSE				/* tget_mpf */
#define _KERNEL_CFG_REL_MPF 			TRUE				/* rel_mpf */
#define _KERNEL_CFG_REF_MPF 			FALSE				/* ref_mpf */

/* Variable-sized memory pools */
#define _KERNEL_CFG_CRE_MPL 			FALSE				/* cre_mpl */
#define _KERNEL_CFG_ACRE_MPL			FALSE				/* acre_mpl */
#define _KERNEL_CFG_DEL_MPL 			FALSE				/* del_mpl */
#define _KERNEL_CFG_GET_MPL 			FALSE				/* get_mpl */
#define _KERNEL_CFG_PGET_MPL			FALSE				/* pget_mpl */
#define _KERNEL_CFG_TGET_MPL			FALSE				/* tget_mpl */
#define _KERNEL_CFG_REL_MPL 			FALSE				/* rel_mpl */
#define _KERNEL_CFG_REF_MPL 			FALSE				/* ref_mpl */

/* System time management */
#define _KERNEL_CFG_SET_TIM 			TRUE				/* set_tim */
#define _KERNEL_CFG_GET_TIM 			TRUE				/* get_tim */
#define _KERNEL_CFG_ISIG_TIM			TRUE				/* isig_tim */

/* Cyclic handlers */
#define _KERNEL_CFG_CRE_CYC 			TRUE				/* cre_cyc */
#define _KERNEL_CFG_ACRE_CYC			TRUE				/* acre_cyc */
#define _KERNEL_CFG_DEL_CYC 			TRUE				/* del_cyc */
#define _KERNEL_CFG_STA_CYC 			TRUE				/* sta_cyc */
#define _KERNEL_CFG_STP_CYC 			TRUE				/* stp_cyc */
#define _KERNEL_CFG_REF_CYC 			TRUE				/* ref_cyc */

/* Alarm handlers */
#define _KERNEL_CFG_CRE_ALM 			FALSE				/* cre_alm */
#define _KERNEL_CFG_ACRE_ALM			FALSE				/* acre_alm */
#define _KERNEL_CFG_DEL_ALM 			FALSE				/* del_alm */
#define _KERNEL_CFG_STA_ALM 			FALSE				/* sta_alm */
#define _KERNEL_CFG_STP_ALM 			FALSE				/* stp_alm */
#define _KERNEL_CFG_REF_ALM 			FALSE				/* ref_alm */

/* Overrun handlers */				
#define _KERNEL_CFG_DEF_OVR 			FALSE				/* def_ovr */
#define _KERNEL_CFG_STA_OVR 			FALSE				/* sta_ovr */
#define _KERNEL_CFG_STP_OVR 			FALSE				/* stp_ovr */
#define _KERNEL_CFG_REF_OVR 			FALSE				/* ref_ovr */

/* System management functions */
#define _KERNEL_CFG_ROT_RDQ 			FALSE				/* rot_rdq */
#define _KERNEL_CFG_IROT_RDQ			FALSE				/* irot_rdq */
#define _KERNEL_CFG_GET_TID 			FALSE				/* get_tid */
#define _KERNEL_CFG_IGET_TID			FALSE				/* iget_tid */
#define _KERNEL_CFG_LOC_CPU 			FALSE				/* loc_cpu */
#define _KERNEL_CFG_ILOC_CPU			FALSE				/* iloc_cpu */
#define _KERNEL_CFG_UNL_CPU 			FALSE				/* unl_cpu */
#define _KERNEL_CFG_ILNL_CPU			FALSE				/* ilnl_cpu */
#define _KERNEL_CFG_DIS_DSP 			FALSE				/* dis_dsp */
#define _KERNEL_CFG_ENA_DSP 			FALSE				/* ena_dsp */
#define _KERNEL_CFG_SNS_CTX 			FALSE				/* sns_ctx */
#define _KERNEL_CFG_SNS_LOC 			FALSE				/* sns_loc */
#define _KERNEL_CFG_SNS_DSP 			FALSE				/* sns_dsp */
#define _KERNEL_CFG_SNS_DPN 			FALSE				/* sns_dpn */
#define _KERNEL_CFG_REF_SYS 			FALSE				/* ref_sys */

/* Interrupt management functions */
#define _KERNEL_CFG_DEF_INH 			TRUE				/* def_inh */
#define _KERNEL_CFG_CRE_ISR 			TRUE				/* cre_isr */
#define _KERNEL_CFG_ACRE_ISR			TRUE				/* acre_isr */
#define _KERNEL_CFG_DEL_ISR 			FALSE				/* del_isr */
#define _KERNEL_CFG_REF_ISR 			FALSE				/* ref_isr */
#define _KERNEL_CFG_DIS_INT 			FALSE				/* dis_int */
#define _KERNEL_CFG_ENA_INT 			FALSE				/* ena_int */
#define _KERNEL_CFG_CHG_ILV 			FALSE				/* chg_ilv */
#define _KERNEL_CFG_GET_ILV 			FALSE				/* get_ilv */

/* Service call management functions */				
#define _KERNEL_CFG_DEF_SVC 			FALSE				/* def_svc */
#define _KERNEL_CFG_CAL_SVC 			FALSE				/* cal_svc */

/* System configulation management functions */
#define _KERNEL_CFG_DEF_EXC				FALSE				/* def_exc */
#define _KERNEL_CFG_REF_CFG	 			FALSE				/* ref_cfg */
#define _KERNEL_CFG_REF_VER	 			FALSE				/* ref_ver */

/* Static API */
#define _KERNEL_CFG_SCRE_TSK			TRUE				/* CRE_TSK */
#define _KERNEL_CFG_SDEF_TEX			FALSE				/* DEF_TEX */
#define _KERNEL_CFG_SCRE_SEM			TRUE				/* CRE_SEM */
#define _KERNEL_CFG_SCRE_FLG			TRUE				/* CRE_FLG */
#define _KERNEL_CFG_SCRE_DTQ			FALSE				/* CRE_DTQ */
#define _KERNEL_CFG_SCRE_MBX			FALSE				/* CRE_MBX */
#define _KERNEL_CFG_SCRE_MTX			FALSE				/* CRE_MTX */
#define _KERNEL_CFG_SCRE_MBF			FALSE				/* CRE_MBF */
#define _KERNEL_CFG_SCRE_POR			FALSE				/* CRE_POR */
#define _KERNEL_CFG_SCRE_MPF			FALSE				/* CRE_MPF */
#define _KERNEL_CFG_SCRE_MPL			FALSE				/* CRE_MPL */
#define _KERNEL_CFG_SCRE_CYC			FALSE				/* CRE_CYC */
#define _KERNEL_CFG_SCRE_ALM			FALSE				/* CRE_ALM */
#define _KERNEL_CFG_SDEF_OVR			FALSE				/* DEF_OVR */
#define _KERNEL_CFG_SDEF_INH			FALSE				/* DEF_INH */
#define _KERNEL_CFG_SCRE_ISR			FALSE				/* CRE_ISR */
#define _KERNEL_CFG_SDEF_SVC			FALSE				/* DEF_SVC */
#define _KERNEL_CFG_SDEF_EXC			FALSE				/* DEF_EXC */
#define _KERNEL_CFG_SATT_INI			TRUE				/* ATT_INI */
#define _KERNEL_CFG_SINCLUDE			TRUE				/* INCLUDE */



#endif	/* _KERNEL__config__cfgknl_h__ */



/* end of file */
