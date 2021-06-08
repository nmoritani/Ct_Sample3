/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  parssys.h
 * @brief %jp{�V�X�e���R���t�B�M�����[�V�����̉��}%en{system configuration parser}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__prser_pitrncfg_h__
#define _KERNEL__prser_pitrncfg_h__


#if _KERNEL_CFG_MEM_ALIGN <= 0
#define _KERNEL_MEM_ALIGN			(sizeof(void *))
#else
#define _KERNEL_MEM_ALIGN			_KERNEL_CFG_MEM_ALIGN
#endif


/* %jp{INT�^��bit�����`����} */
#if _KERNEL_CFG_TBIT_INT <= 0		/* default */
#define _KERNEL_TBIT_INT		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_INT		_KERNEL_CFG_TBIT_INT
#endif

/* %jp{UINT�^��bit�����`����} */
#if _KERNEL_CFG_TBIT_UINT <= 0		/* default */
#define _KERNEL_TBIT_UINT		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_UINT		_KERNEL_CFG_TBIT_UINT
#endif


/* %jp{VP_INT���|�C���^�^�Ƃ��邩} */
#define _KERNEL_VP_INT_PTR		_KERNEL_CFG_VP_INT_PTR


/* %jp{BOOL�^��bit�����`����} */
#if _KERNEL_CFG_TBIT_BOOL <= 0		/* default */
#define _KERNEL_TBIT_BOOL		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_BOOL		_KERNEL_CFG_TBIT_BOOL
#endif


/*  %jp{FN�^��bit�����`����}%en{Function code} */
#if _KERNEL_CFG_TBIT_FN <= 0			/* default */
#define _KERNEL_TBIT_FN			_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_FN			_KERNEL_CFG_TBIT_FN
#endif


/* %jp{ER�^��bit�����`����}%en{Error code(signed integer)} */
#if _KERNEL_CFG_TBIT_ER <= 0			/* default */
#define _KERNEL_TBIT_ER			_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_ER			_KERNEL_CFG_TBIT_ER
#endif


/* %jp{ID�^��bit�����`����}%en{Object ID number(signed integer)} */
#if _KERNEL_CFG_TBIT_ID <= 0			/* default */
#define _KERNEL_TBIT_ID			_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_ID			_KERNEL_CFG_TBIT_ID
#endif


/* %jp{ATR�^��bit�����`����}%en{Object attribute(unsigned integer)} */
#if _KERNEL_CFG_TBIT_ATR <= 0		/* default */
#define _KERNEL_TBIT_ATR		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_ATR		_KERNEL_CFG_TBIT_ATR
#endif


/* %jp{STAT�^��bit�����`����}%en{Object state(unsigned integer)} */
#if _KERNEL_CFG_TBIT_STAT <= 0		/* default */
#define _KERNEL_TBIT_STAT		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_STAT		_KERNEL_CFG_TBIT_STAT
#endif


/* %jp{MODE�^��bit�����`����}%en{Service call operational mode(unsigned integer)} */
#if _KERNEL_CFG_TBIT_MODE <= 0		/* default */
#define _KERNEL_TBIT_MODE		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_MODE		_KERNEL_CFG_TBIT_MODE
#endif


/* %jp{PRI�^��bit�����`����}%en{Priority(signed integer)} */
#if _KERNEL_CFG_TBIT_PRI <= 0		/* default */
#define _KERNEL_TBIT_PRI		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_PRI		_KERNEL_CFG_TBIT_PRI
#endif


/* %jp{SIZE�^��bit�����`����}%en{Memory area size(unsigned integer)} */
#if _KERNEL_CFG_TBIT_SIZE <= 0		/* default */
#define _KERNEL_TBIT_SIZE		_KERNEL_TBIT_UINTPTR
#else
#define _KERNEL_TBIT_SIZE		_KERNEL_CFG_TBIT_SIZE
#endif


/* %jp{TMO�^��bit�����`����}%en{Timeout} */
#if _KERNEL_CFG_TBIT_TMO <= 0		/* default */
#define _KERNEL_TBIT_TMO		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_TMO		_KERNEL_CFG_TBIT_TMO
#endif


/* %jp{RELTIM�^��bit�����`����}%en{Relative time(unsigned integer, unit of time is implementation-defined)} */
#if _KERNEL_CFG_TBIT_RELTIM <= 0		/* default */
#define _KERNEL_TBIT_RELTIM		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_RELTIM		_KERNEL_CFG_TBIT_RELTIM
#endif


/* %jp{SYSTIM�^��bit�����`����}%en{System time(unsigned integer, unit of time is implementation-defined)} */
#define _KERNEL_SYSTIM_STRUCT	_KERNEL_CFG_SYSTIM_STRUCT
#if _KERNEL_CFG_TBIT_SYSTIM < 0		/* default */
#if _KERNEL_SYSTIM_STRUCT		/* %jp{�\���̉�����Ȃ�} */
#define _KERNEL_TBIT_SYSTIM		48
#else
#define _KERNEL_TBIT_SYSTIM		32
#endif
#else
#define _KERNEL_TBIT_SYSTIM		_KERNEL_CFG_TBIT_SYSTIM
#endif


/* %jp{ER_BOOL�^��bit�����`����}%en{Error code or a boolean value} */
#if _KERNEL_CFG_TBIT_ER_BOOL <= 0
#if _KERNEL_TBIT_ER >= _KERNEL_TBIT_BOOL
#define _KERNEL_TBIT_ER_BOOL	_KERNEL_TBIT_ER
#else
#define _KERNEL_TBIT_ER_BOOL	_KERNEL_TBIT_BOOL
#endif
#else
#define _KERNEL_TBIT_ER_BOOL	_KERNEL_CFG_TBIT_ER_BOOL
#endif


/* %jp{ER_ID��bit�����`����}%en{Error code or an object ID number} */
#if _KERNEL_CFG_TBIT_ER_ID <= 0
#if _KERNEL_TBIT_ER >= _KERNEL_TBIT_ID
#define _KERNEL_TBIT_ER_ID		_KERNEL_TBIT_ER
#else
#define _KERNEL_TBIT_ER_ID		_KERNEL_TBIT_ID
#endif
#else
#define _KERNEL_TBIT_ER_ID		_KERNEL_CFG_TBIT_ER_ID
#endif


/**< %jp{ER_UINT��bit�����`����}%en{Error code or an unsigned integer} */
#if _KERNEL_CFG_TBIT_ER_UINT <= 0
#if _KERNEL_TBIT_ER >= _KERNEL_TBIT_UINT
#define _KERNEL_TBIT_ER_UINT	_KERNEL_TBIT_ER
#else
#define _KERNEL_TBIT_ER_UINT	_KERNEL_TBIT_UINT
#endif
#else
#define _KERNEL_TBIT_ER_UINT	_KERNEL_CFG_TBIT_ER_UINT
#endif



/**< %jp{�^�X�N��O�v���̃p�^�[��(������������)}%en{Bit pattern for the task exception code(unsigned integer)} */
#if _KERNEL_CFG_TBIT_TEXPTN <= 0
#define _KERNEL_TBIT_TEXPTN		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_TEXPTN		_KERNEL_CFG_TBIT_TEXPTN
#endif


#if _KERNEL_CFG_TBIT_FLGPTN <= 0
#define _KERNEL_TBIT_FLGPTN		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_FLGPTN		_KERNEL_CFG_TBIT_FLGPTN
#endif


#if _KERNEL_CFG_TBIT_RDVPTN <= 0
#define _KERNEL_TBIT_RDVPTN		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_RDVPTN		_KERNEL_CFG_TBIT_RDVPTN
#endif


#if _KERNEL_CFG_TBIT_RDVNO <= 0

#define _KERNEL_TBIT_RDVNO		_KERNEL_TBIT_PROC_UINT
#else
#define _KERNEL_TBIT_RDVNO		_KERNEL_CFG_TBIT_RDVNO
#endif


#if _KERNEL_CFG_TBIT_OVRTIM <= 0
#define _KERNEL_TBIT_OVRTIM		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_OVRTIM		_KERNEL_CFG_TBIT_OVRTIM
#endif


#if _KERNEL_CFG_TBIT_INHNO <= 0
#define _KERNEL_TBIT_INHNO		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_INHNO		_KERNEL_CFG_TBIT_INHNO
#endif


#if _KERNEL_CFG_TBIT_INTNO <= 0
#define _KERNEL_TBIT_INTNO		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_INTNO		_KERNEL_CFG_TBIT_INTNO
#endif


#if _KERNEL_CFG_TBIT_EXCNO <= 0
#define _KERNEL_TBIT_EXCNO		_KERNEL_TBIT_PROC_INT
#else
#define _KERNEL_TBIT_EXCNO		_KERNEL_CFG_TBIT_EXCNO
#endif


/* */
/* %jp{�D��x�͈̔�}%en{Priority Range} */
#if _KERNEL_CFG_TMAX_TPRI <= 0
#define _KERNEL_TMAX_TPRI		_KERNEL_TMAX_PROC_INT					/**< %jp{�^�X�N�D��x�̍ő�l}%en{Maximum task priority} */
#else
#define _KERNEL_TMAX_TPRI		_KERNEL_CFG_TMAX_TPRI					/**< %jp{�^�X�N�D��x�̍ő�l}%en{Maximum task priority} */
#endif

#if _KERNEL_CFG_TMAX_MPRI <= 0
#define _KERNEL_TMAX_MPRI		_KERNEL_TMAX_PROC_INT					/**< %jp{���b�Z�[�W�D��x�̍ő�l}%en{Maximum message priority} */
#else
#define _KERNEL_TMAX_MPRI		_KERNEL_CFG_TMAX_MPRI					/**< %jp{���b�Z�[�W�D��x�̍ő�l}%en{Maximum message priority} */
#endif


/* %jp{�L���[�C���O�^�l�X�g�񐔂̍ő�l}%en{Maximum Nesting/Queueing Count} */
#if _KERNEL_CFG_TMAX_ACTCNT < 0
#define _KERNEL_TMAX_ACTCNT			_KERNEL_TMAX_UINT					/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#else
#define _KERNEL_TMAX_ACTCNT			_KERNEL_CFG_TMAX_ACTCNT				/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#endif

#if _KERNEL_CFG_TMAX_WUPCNT < 0
#define _KERNEL_TMAX_WUPCNT			_KERNEL_TMAX_UINT					/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#else
#define _KERNEL_TMAX_WUPCNT			_KERNEL_CFG_TMAX_WUPCNT				/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#endif

#if _KERNEL_CFG_TMAX_SUSCNT	< 0
#define _KERNEL_TMAX_SUSCNT			_KERNEL_TMAX_UINT					/**< %jp{�^�X�N�����҂��v���l�X�g���̍ő�l} */
#else
#define _KERNEL_TMAX_SUSCNT			_KERNEL_CFG_TMAX_SUSCNT				/**< %jp{�^�X�N�����҂��v���l�X�g���̍ő�l} */
#endif



/* */

#if _KERNEL_CFG_TEX_TBIT_TEXPTN < 0	
#define _KERNEL_TEX_TBIT_TEXPTN	_KERNEL_TBIT_TEXPTN						/**< %jp{�^�X�N��O�v���̃r�b�g��} */
#else
#define _KERNEL_TEX_TBIT_TEXPTN	_KERNEL_CFG_TEX_TBIT_TEXPTN				/**< %jp{�^�X�N��O�v���̃r�b�g��} */
#endif

#if _KERNEL_CFG_FLG_TBIT_FLGPTN < 0
#define _KERNEL_FLG_TBIT_FLGPTN	_KERNEL_TBIT_FLGPTN						/**< %jp{�C�x���g�t���O�̃r�b�g��} */
#else
#define _KERNEL_FLG_TBIT_FLGPTN	_KERNEL_CFG_FLG_TBIT_FLGPTN				/**< %jp{�C�x���g�t���O�̃r�b�g��} */
#endif

#if _KERNEL_CFG_RDV_TBIT_RDVPTN < 0
#define _KERNEL_RDV_TBIT_RDVPTN	_KERNEL_TBIT_RDVPTN						/**< %jp{�����f�u�����̃r�b�g��} */
#else
#define _KERNEL_RDV_TBIT_RDVPTN	_KERNEL_CFG_RDV_TBIT_RDVPTN				/**< %jp{�����f�u�����̃r�b�g��} */
#endif


/* %jp{�Z�}�t�H�̍ő�l}%en{Maximum value of the maximum definable semaphore resource count} */
#if _KERNEL_CFG_TMAX_MAXSEM <= 0
#define _KERNEL_TMAX_MAXSEM		_KERNEL_TMAX_PROC_UINT
#else
#define _KERNEL_TMAX_MAXSEM		_KERNEL_CFG_TMAX_MAXSEM
#endif



/* %jp{T_RTSK�̕ύX}%en{T_RTSK�̕ύX} */
#define _KERNEL_SPT_RTSK_TSKATR		_KERNEL_CFG_RTSK_TSKATR				/**< %jp{T_RTSK�� tskatr ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTSK_EXINF		_KERNEL_CFG_RTSK_EXINF				/**< %jp{T_RTSK�� exinf ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTSK_TASK		_KERNEL_CFG_RTSK_TASK				/**< %jp{T_RTSK�� task ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTSK_ITSKPRI	_KERNEL_CFG_RTSK_ITSKPRI			/**< %jp{T_RTSK�� itskpri ���܂߂邩(HOS�Ǝ��g���@�\)} */	
#define _KERNEL_SPT_RTSK_STKSZ		_KERNEL_CFG_RTSK_STKSZ				/**< %jp{T_RTSK�� stksz ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTSK_STK		_KERNEL_CFG_RTSK_STK				/**< %jp{T_RTSK�� stk ���܂߂邩(HOS�Ǝ��g���@�\)} */


/* %jp{T_RTST�̍\��}%en{T_RTST} */
#define _KERNEL_SPT_RTST_TSKATR		_KERNEL_CFG_RTST_TSKATR				/**< %jp{T_RTST�� tskatr ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTST_EXINF		_KERNEL_CFG_RTST_EXINF				/**< %jp{T_RTST�� exinf ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTST_TASK		_KERNEL_CFG_RTST_TASK				/**< %jp{T_RTST�� task ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTST_ITSKPRI	_KERNEL_CFG_RTST_ITSKPRI			/**< %jp{T_RTST�� itskpri ���܂߂邩(HOS�Ǝ��g���@�\)} */	
#define _KERNEL_SPT_RTST_STKSZ		_KERNEL_CFG_RTST_STKSZ				/**< %jp{T_RTST�� stksz ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_SPT_RTST_STK		_KERNEL_CFG_RTST_STK				/**< %jp{T_RTST�� stk ���܂߂邩(HOS�Ǝ��g���@�\)} */



#endif	/* _KERNEL__prser_pitrncfg_h__ */


/* end of file */
