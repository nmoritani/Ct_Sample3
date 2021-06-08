/**
 *  Hyper Operating System V4 Advance
 *
 * @file  tskobj.h
 * @brief %jp{�^�X�N�u�W�F�N�g�̃w�b�_�t�@�C��}%en{task object heder file}
 *
 * Copyright (C) 1998-2008 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL__object__tskobj_h__
#define _KERNEL__object__tskobj_h__



/* ------------------------------------------ */
/*  Primitive type definition                 */
/* ------------------------------------------ */

/* %jp{�^�X�N�n���h���̌^}%en{Task-handle} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */
typedef int								_KERNEL_TCB_T_TSKHDL;			/**< %jp{�^�X�N�n���h����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKHDL		: _KERNEL_TBIT_TSKHDL			/**< %jp{�^�X�N�n���h���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef _KERNEL_T_TSKHDL				_KERNEL_TCB_T_TSKHDL;			/**< %jp{�^�X�N�n���h����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKHDL										/**< %jp{�^�X�N�n���h���̃r�b�g�t�B�[���h�錾���̕�} */
#endif


/* %jp{�^�X�N��Ԃ̌^}%en{Task-state} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKSTAT		: (_KERNEL_TSK_TBIT_TSKSTAT+1)	/**< %jp{�^�X�N��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKSTAT		: _KERNEL_TSK_TBIT_TSKSTAT		/**< %jp{�^�X�N��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TSKSTAT;			/**< %jp{�^�X�N��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_TSKSTAT										/**< %jp{�^�X�N��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�^�X�N�D��x�̌^}%en{Task priopity} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TPRI		: (_KERNEL_TSK_TBIT_TPRI+1)		/**< %jp{�^�X�N�D��x�̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TPRI		: _KERNEL_TSK_TBIT_TPRI			/**< %jp{�^�X�N�D��x�̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TPRI <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_TPRI;				/**< %jp{�^�X�N�D��x�����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_TPRI;				/**< %jp{�^�X�N�D��x��TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_TPRI										/**< %jp{�^�X�N�D��x�̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�^�X�N�҂��v��}%en{Task wait} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKWAIT		: (_KERNEL_TSK_TBIT_TSKWAIT+1)	/**< %jp{�^�X�N�҂��v���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TSKWAIT		: _KERNEL_TSK_TBIT_TSKWAIT		/**< %jp{�^�X�N�҂��v���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_TSKWAIT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_TSKWAIT;			/**< %jp{�^�X�N�҂��v����TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_TSKWAIT										/**< %jp{�^�X�N�҂��v���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ�}%jp{Waitbject-ID} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_WOBJID		: (_KERNEL_TSK_TBIT_WOBJID+1)	/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ��̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_WOBJID		: _KERNEL_TSK_TBIT_WOBJID		/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ��̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WOBJID <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_WOBJID;			/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ���TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_WOBJID										/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ��̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{�N���v���L���[�C���O��}%en{Activate queuing count} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_ACTCNT		: (_KERNEL_TSK_TBIT_ACTCNT+1)	/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_ACTCNT		: _KERNEL_TSK_TBIT_ACTCNT		/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_ACTCNT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_ACTCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_ACTCNT										/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/*  %jp{�N���v���L���[�C���O��}%en{Wakeup queuing count} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_WUPCNT		: (_KERNEL_TSK_TBIT_WUPCNT+1)	/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_WUPCNT		: _KERNEL_TSK_TBIT_WUPCNT		/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_WUPCNT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_WUPCNT;			/**< %jp{�N���v���L���[�C���O����TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_WUPCNT										/**< %jp{�N���v���L���[�C���O���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/*  %jp{�����҂��v���l�X�g��}%en{Suspend nest count} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_SUSCNT		: (_KERNEL_TSK_TBIT_SUSCNT+1)	/**< %jp{�����҂��v���l�X�g���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_SUSCNT		: _KERNEL_TSK_TBIT_SUSCNT		/**< %jp{�����҂��v���l�X�g���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_SUSCNT <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_SUSCNT;			/**< %jp{�����҂��v���l�X�g����TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_SUSCNT										/**< %jp{�����҂��v���l�X�g���̃r�b�g�t�B�[���h�錾���̕�} */

#endif


typedef _KERNEL_T_MTXHDL				_KERNEL_TSK_T_MTXHDL;
typedef _KERNEL_T_MTXHDL				_KERNEL_TCB_T_MTXHDL;
#define _KERNEL_TCB_TBITDEF_MTXHDL


/*  %jp{�^�X�N�f�[�^}%en{Task data} */
#if _KERNEL_TCB_BITFIELD			/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

typedef VP_INT							_KERNEL_TSK_T_DATA;
typedef int								_KERNEL_TCB_T_DATA;
#define _KERNEL_TCB_TBITDEF_DATA		: _KERNEL_TSK_TBIT_DATA

#else								/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef VP_INT							_KERNEL_TSK_T_DATA;
typedef VP_INT							_KERNEL_TCB_T_DATA;
#define _KERNEL_TCB_TBITDEF_DATA

#endif


/*  %jp{�G���[�R�[�h}%en{Error code} */
#if _KERNEL_TCB_BITFIELD			/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

typedef signed int						_KERNEL_TSK_T_ERCD;
typedef signed int						_KERNEL_TCB_T_ERCD;
#define _KERNEL_TCB_TBITDEF_ERCD		: _KERNEL_TSK_TBIT_ERCD

#else								/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_ERCD;
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_ERCD;
#define _KERNEL_TCB_TBITDEF_ERCD

#endif


/* %jp{�^�X�N����}%en{Task attribute} */
typedef ATR								_KERNEL_TSK_T_TSKATR;
typedef ATR								_KERNEL_TCB_T_TSKATR;
#define _KERNEL_TCB_TBITDEF_TSKATR


/* %jp{�^�X�N�g�����}%jp{Extended information} */
typedef VP_INT							_KERNEL_TSK_T_EXINF;
typedef VP_INT							_KERNEL_TCB_T_EXINF;
#define _KERNEL_TCB_TBITDEF_EXINF


/* %jp{�^�X�N�̊J�n�Ԓn}%en{Start address} */
typedef void (*_KERNEL_TSK_T_TASK)(VP_INT exinf);
typedef void (*_KERNEL_TCB_T_TASK)(VP_INT exinf);
#define _KERNEL_TCB_TBITDEF_TASK


/* %jp{�X�^�b�N�T�C�Y}%en{Stack size} */
typedef SIZE							_KERNEL_TSK_T_STKSZ;
typedef SIZE							_KERNEL_TCB_T_STKSZ;
#define _KERNEL_TCB_TBITDEF_STKSZ


/* %jp{�X�^�b�N�̈�̐擪�Ԓn}%en{Stack base address} */
typedef VP								_KERNEL_TSK_T_STK;
typedef VP								_KERNEL_TCB_T_STK;
#define _KERNEL_TCB_TBITDEF_STK


/* Initial stack pointer */
typedef VP								_KERNEL_TSK_T_ISP;
typedef VP								_KERNEL_TCB_T_ISP;
#define _KERNEL_TCB_TBITDEF_ISP



/* %jp{���Ύ���}%en{Relative-Time} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_RELTIM		: (_KERNEL_TSK_TBIT_RELTIM+1)	/**< %jp{���Ύ��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_RELTIM		: _KERNEL_TSK_TBIT_RELTIM		/**< %jp{���Ύ��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_B) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_UB) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_H) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_UH) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_W) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_UW) && !(_KERNEL_OPT_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#elif (_KERNEL_TSK_TMAX_RELTIM <= _KERNEL_TMAX_D) && _KERNEL_OPT_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_RELTIM;			/**< %jp{���Ύ��Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_RELTIM;			/**< %jp{���Ύ��Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#endif
#define _KERNEL_TCB_TBITDEF_RELTIM										/**< %jp{���Ύ��Ԃ̃r�b�g�t�B�[���h�錾���̕�} */

#endif



/* %jp{�^�X�N��O�������[�`�������p�̌^} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

/* %jp{TA_HLNG �� TA_ASM �̔���� 2bit �K�v} */
typedef unsigned int					_KERNEL_TSK_T_TEXATR;
typedef unsigned int					_KERNEL_TCB_T_TEXATR;
#define _KERNEL_TCB_TBITDEF_TEXATR		: 2

#else							/* %jp{TEXCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TEXATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TEXATR;
#define _KERNEL_TCB_TBITDEF_TEXATR

#endif


/* %jp{�^�X�N��O�������[�`���̋N���Ԓn�̌^} */
typedef void (*_KERNEL_TSK_T_TEXRTN)(TEXPTN texptn, VP_INT exinf);
typedef FP								_KERNEL_TCB_T_TEXRTN;
#define _KERNEL_TCB_TBITDEF_TEXRTN


/* %jp{�^�X�N��O�����֎~��Ԃ̌^} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ����Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TEXSTAT		: 1 + 1							/**< %jp{�^�X�N��O������Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TEX_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ����Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TEXCB_T_TEXSTAT;		/**< %jp{�^�X�N��O������Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TEXSTAT		: 1								/**< %jp{�^�X�N��O������Ԃ̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TEXCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ����Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TEXSTAT;			/**< %jp{�^�X�N��O������Ԃ�TCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_TCB_TBITDEF_TEXSTAT										/**< %jp{�^�X�N��O������Ԃ̃r�b�g�t�B�[���h�錾���̕�} */

#endif


/* %jp{��O�v���p�^�[���p�̌^} */
#if _KERNEL_TCB_BITFIELD		/* %jp{TCB�Ƀr�b�g�t�B�[���h�𗘗p����ꍇ} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE	/* %jp{�����t�D��̏ꍇ1bit���₵�ĕ����t���g��} */
typedef signed int						_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef signed int						_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TEXPTN		: _KERNEL_TEX_TBIT_TEXPTN + 1	/**< %jp{��O�v���p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */
#else
typedef unsigned int					_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef unsigned int					_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#define _KERNEL_TCB_TBITDEF_TEXPTN		: _KERNEL_TEX_TBIT_TEXPTN		/**< %jp{��O�v���p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */
#endif

#else							/* %jp{TEXCB�Ƀr�b�g�t�B�[���h�𗘗p���Ȃ��ꍇ} */

#if _KERNEL_TEX_TBIT_TEXPTN <= 7 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_B				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 8 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 15 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_H				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 16 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 31 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_W				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 32 && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#elif _KERNEL_TEX_TBIT_TEXPTN <= 63 && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_D				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_TSK_T_TEXPTN;			/**< %jp{��O�v���p�^�[�������Z���삷��Ƃ��̌^} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_TCB_T_TEXPTN;			/**< %jp{��O�v���p�^�[����TEXCB�Ɋi�[����Ƃ��̌^} */
#endif

#define _KERNEL_TCB_TBITDEF_TEXPTN										/**< %jp{��O�v���p�^�[���̃r�b�g�t�B�[���h�錾���̕�} */

#endif




/* -------------------------------------------------------------------- */
/*  TCB definetion                                                      */
/* -------------------------------------------------------------------- */

#include "core/dsp.h"
#include "core/que.h"
#include "core/rdq.h"
#include "core/toq.h"
#include "core/sys.h"



/* -------------------------------------------------------------------- */
/*  TCB definetion                                                      */
/* -------------------------------------------------------------------- */

#if _KERNEL_TCB_SPLIT_RO

/** %jp{�^�X�N�R���g���[���u���b�N(ROM��)}%en{Task control block for ROM} */
typedef struct _kernel_t_tcb_ro				/* �^�X�N�R���g���[���u���b�N(ROM��) */
{
#if _KERNEL_TCB_TSKATR
	_KERNEL_TCB_T_TSKATR	tskatr		_KERNEL_TCB_TBITDEF_TSKATR;		/**< %jp{�^�X�N����}%en{Task attribute} */
#endif

#if _KERNEL_TCB_EXINF
	_KERNEL_TCB_T_EXINF		exinf		_KERNEL_TCB_TBITDEF_EXINF;		/**< %jp{�^�X�N�̊g�����}%en{Task extend information} */
#endif

#if _KERNEL_TCB_TASK
	_KERNEL_TCB_T_TASK		task		_KERNEL_TCB_TBITDEF_TASK;		/**< %jp{�^�X�N�̋N���Ԓn}%en{Task start address} */
#endif

#if _KERNEL_TCB_TSKPRI
	_KERNEL_TCB_T_TPRI		itskpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̋N�����D��x}%en{Task initial priority} */
#endif

#if _KERNEL_TCB_STKSZ
	_KERNEL_TCB_T_STKSZ		stksz		_KERNEL_TCB_TBITDEF_STKSZ;		/**< %jp{�^�X�N�̃X�^�b�N�̃T�C�Y�i�o�C�g���j}%en{Task stack size(in bytes)} */
#endif

#if _KERNEL_TCB_STK
	_KERNEL_TCB_T_STK		stk			_KERNEL_TCB_TBITDEF_STK;		/**< %jp{�^�X�N�̃X�^�b�N�̈�̐擪�Ԓn}%en{Base address of task stack space} */
#endif

#if _KERNEL_TCB_ISP
	_KERNEL_TCB_T_ISP		isp			_KERNEL_TCB_TBITDEF_ISP;		/**< %jp{�X�^�b�N�|�C���^�̏����l}%en{Task initial stack pointer} */
#endif

#if _KERNEL_TCB_TEXATR
	_KERNEL_TCB_T_TEXATR	texatr		_KERNEL_TCB_TBITDEF_TEXATR;		/**< %jp{�^�X�N��O�������[�`������} */
#endif

#if _KERNEL_TCB_TEXRTN
	_KERNEL_TCB_T_TEXRTN	texrtn		_KERNEL_TCB_TBITDEF_TEXRTN;		/**< %jp{�^�X�N��O�������[�`���̋N���Ԓn} */
#endif
} _KERNEL_T_TCB_RO;

typedef const _KERNEL_T_TCB_RO		*_KERNEL_T_TCB_RO_PTR;


/** %jp{�^�X�N�R���g���[���u���b�N(RAM��)}%en{Task control block for RAM} */
typedef struct _kernel_t_tcb
{
#if _KERNEL_TCB_CTXCB
	_KERNEL_T_CTXCB			ctxcb;										/**< %jp{�^�X�N�̃R���e�L�X�g}%en{Execution context control block} */
#endif

#if _KERNEL_TCB_QUE
	_KERNEL_T_QUE			*pk_que;									/**< %jp{�����Ă���L���[}%en{Pointer of the queue for which the task connected} */
#endif

#if _KERNEL_TCB_QUEOBJ
	_KERNEL_QUEOBJ														/**< %jp{�L���[�ɐڑ�����ׂ̃I�u�W�F�N�g}%en{Object for queue connection} */
#endif

#if _KERNEL_TCB_TOQOBJ
	_KERNEL_TOQOBJ														/* %jp{�^�C���A�E�g�L���[�ɐڑ�����ׂ̃I�u�W�F�N�g}%en{Timeout queue object} */
#endif

#if _KERNEL_TCB_TSKSTAT
	_KERNEL_TCB_T_TSKSTAT	tskstat		_KERNEL_TCB_TBITDEF_TSKSTAT;	/**< %jp{�^�X�N���}%en{Task state} */
#endif

#if _KERNEL_TCB_TSKPRI
	_KERNEL_TCB_T_TPRI		tskpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̌��ݗD��x}%en{Task current priority} */
#endif

#if _KERNEL_TCB_TSKBPRI
	_KERNEL_TCB_T_TPRI		tskbpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̃x�[�X�D��x}%en{Task base priority} */
#endif

#if _KERNEL_TCB_TSKWAIT
	_KERNEL_TCB_T_TSKWAIT	tskwait		_KERNEL_TCB_TBITDEF_TSKWAIT;	/**< %jp{�҂��v��}%en{Reason for waiting} */
#endif

#if _KERNEL_TCB_WOBJID
	_KERNEL_TCB_T_WOBJID	wobjid		_KERNEL_TCB_TBITDEF_WOBJID;		/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ�}%en{Object ID number for which the task waiting} */
#endif

#if _KERNEL_TCB_ACTCNT
	_KERNEL_TCB_T_ACTCNT	actcnt		_KERNEL_TCB_TBITDEF_ACTCNT;		/**< %jp{�N���v���L���[�C���O��}%en{Activation request count} */
#endif

#if _KERNEL_TCB_WUPCNT
	_KERNEL_TCB_T_WUPCNT	wupcnt		_KERNEL_TCB_TBITDEF_WUPCNT;		/**< %jp{�N���v���L���[�C���O��}%en{Wakeup request count} */
#endif

#if _KERNEL_TCB_SUSCNT
	_KERNEL_TCB_T_SUSCNT	suscnt		_KERNEL_TCB_TBITDEF_SUSCNT;		/**< %jp{�����҂��v���l�X�g��}%en{Suspension count} */
#endif

#if _KERNEL_TCB_MTXHDL
	_KERNEL_TCB_T_MTXHDL	mtxhdl		_KERNEL_TCB_TBITDEF_MTXHDL;		/**< %jp{���L����~���[�e�b�N�X�̃��X�g} */	
#endif

#if _KERNEL_TCB_ERCD
	_KERNEL_TCB_T_ERCD		ercd		_KERNEL_TCB_TBITDEF_ERCD;		/**< %jp{�҂��������̃G���[�R�[�h}%en{error code} */
#endif

#if _KERNEL_TCB_DATA
	_KERNEL_TCB_T_DATA		data		_KERNEL_TCB_TBITDEF_DATA;		/**< %jp{�^�X�N�������̎󂯓n���f�[�^}%en{task data} */
#endif

#if _KERNEL_TCB_TSKID
	_KERNEL_TCB_T_TSKID		tskid		_KERNEL_TCB_TBITDEF_TSKID;		/**< %jp{�^�X�NID�ԍ��̋t�����p}%en{Task object ID} */
#endif

#if _KERNEL_TCB_TEXSTAT
	_KERNEL_TCB_T_TEXSTAT	texstat		_KERNEL_TCB_TBITDEF_TEXSTAT;	/**< %jp{�^�X�N��O�������} */
#endif

#if _KERNEL_TCB_RASPTN
	_KERNEL_TCB_T_TEXPTN	rasptn		_KERNEL_TCB_TBITDEF_TEXPTN;		/**< %jp{�^�X�N��O�����v��} */
#endif


/* %jp{�|�C���^�Ǘ�����ROM��/RAM���𕪗�����ꍇ�̓|�C���^�𒣂�} */
#if _KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_PTRARRAY
	const _KERNEL_T_TCB_RO	*tcb_ro;
#endif
} _KERNEL_T_TCB;

typedef _KERNEL_T_TCB			*_KERNEL_T_TCB_PTR;


#else


/** %jp{�^�X�N�R���g���[���u���b�N}%en{Task Control Block} */
typedef struct _kernel_t_tcb
{
#if _KERNEL_TCB_CTXCB
	_KERNEL_T_CTXCB			ctxcb;										/**< %jp{�^�X�N�̃R���e�L�X�g}%en{Execution context control block} */
#endif

#if _KERNEL_TCB_QUE
	_KERNEL_T_QUE			*pk_que;									/**< %jp{�����Ă���L���[}%en{Pointer of the queue for which the task connected} */
#endif

#if _KERNEL_TCB_QUEOBJ
	_KERNEL_QUEOBJ														/**< %jp{�L���[�ɐڑ�����ׂ̃I�u�W�F�N�g}%en{Object for queue connection} */
#endif
	
#if _KERNEL_TCB_TOQOBJ
	_KERNEL_TOQOBJ														/**< %jp{�^�C���A�E�g�L���[�ɐڑ�����ׂ̃I�u�W�F�N�g}%en{Timeout queue object} */
#endif

#if _KERNEL_TCB_TSKSTAT
	_KERNEL_TCB_T_TSKSTAT	tskstat		_KERNEL_TCB_TBITDEF_TSKSTAT;	/**< %jp{�^�X�N���}%en{Task state} */
#endif

#if _KERNEL_TCB_TSKPRI
	_KERNEL_TCB_T_TPRI		tskpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̌��ݗD��x}%en{Task current priority} */
#endif

#if _KERNEL_TCB_TSKBPRI
	_KERNEL_TCB_T_TPRI		tskbpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̃x�[�X�D��x}%en{Task base priority} */
#endif

#if _KERNEL_TCB_TSKWAIT
	_KERNEL_TCB_T_TSKWAIT	tskwait		_KERNEL_TCB_TBITDEF_TSKWAIT;	/**< %jp{�҂��v��}%en{Reason for waiting} */
#endif

#if _KERNEL_TCB_WOBJID
	_KERNEL_TCB_T_WOBJID	wobjid		_KERNEL_TCB_TBITDEF_WOBJID;		/**< %jp{�҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ�}%en{Object ID number for which the task waiting} */
#endif

#if _KERNEL_TCB_ACTCNT
	_KERNEL_TCB_T_ACTCNT	actcnt		_KERNEL_TCB_TBITDEF_ACTCNT;		/**< %jp{�N���v���L���[�C���O��}%en{Activation request count} */
#endif

#if _KERNEL_TCB_WUPCNT
	_KERNEL_TCB_T_WUPCNT	wupcnt		_KERNEL_TCB_TBITDEF_WUPCNT;		/**< %jp{�N���v���L���[�C���O��}%en{Wakeup request count} */
#endif

#if _KERNEL_TCB_SUSCNT
	_KERNEL_TCB_T_SUSCNT	suscnt		_KERNEL_TCB_TBITDEF_SUSCNT;		/**< %jp{�����҂��v���l�X�g��}%en{Suspension count} */
#endif

#if _KERNEL_TCB_MTXHDL
	_KERNEL_TCB_T_MTXHDL	mtxhdl		_KERNEL_TCB_TBITDEF_MTXHDL;		/**< %jp{���L����~���[�e�b�N�X�̃��X�g} */	
#endif

#if _KERNEL_TCB_ERCD
	_KERNEL_TCB_T_ERCD		ercd		_KERNEL_TCB_TBITDEF_ERCD;		/**< %jp{�҂��������̃G���[�R�[�h}%en{error code} */
#endif

#if _KERNEL_TCB_DATA
	_KERNEL_TCB_T_DATA		data		_KERNEL_TCB_TBITDEF_DATA;		/**< %jp{�^�X�N�������̎󂯓n���f�[�^}%en{task data} */
#endif

#if _KERNEL_TCB_TSKID
	_KERNEL_TCB_T_TSKID		tskid		_KERNEL_TCB_TBITDEF_TSKID;		/**< %jp{�^�X�NID�ԍ��̋t�����p}%en{Task object ID} */
#endif

#if _KERNEL_TCB_TEXSTAT
	_KERNEL_TCB_T_TEXSTAT	texstat		_KERNEL_TCB_TBITDEF_TEXSTAT;	/**< %jp{�^�X�N��O�������} */
#endif

#if _KERNEL_TCB_RASPTN
	_KERNEL_TCB_T_TEXPTN	rasptn		_KERNEL_TCB_TBITDEF_TEXPTN;		/**< %jp{�^�X�N��O�����v��} */
#endif
	
	
#if _KERNEL_TCB_TSKATR
	_KERNEL_TCB_T_TSKATR	tskatr		_KERNEL_TCB_TBITDEF_TSKATR;		/**< %jp{�^�X�N����}%en{Task attribute} */
#endif

#if _KERNEL_TCB_EXINF
	_KERNEL_TCB_T_EXINF		exinf		_KERNEL_TCB_TBITDEF_EXINF;		/**< %jp{�^�X�N�̊g�����}%en{Task extend information} */
#endif

#if _KERNEL_TCB_TASK
	_KERNEL_TCB_T_TASK		task		_KERNEL_TCB_TBITDEF_TASK;		/**< %jp{�^�X�N�̋N���Ԓn}%en{Task start address} */
#endif

#if _KERNEL_TCB_ITSKPRI
	_KERNEL_TCB_T_TPRI		itskpri		_KERNEL_TCB_TBITDEF_TPRI;		/**< %jp{�^�X�N�̋N�����D��x}%en{Task initial priority} */
#endif

#if _KERNEL_TCB_STKSZ
	_KERNEL_TCB_T_STKSZ		stksz		_KERNEL_TCB_TBITDEF_STKSZ;		/**< %jp{�^�X�N�̃X�^�b�N�̃T�C�Y�i�o�C�g���j}%en{Task stack size(in bytes)} */
#endif

#if _KERNEL_TCB_STK
	_KERNEL_TCB_T_STK		stk			_KERNEL_TCB_TBITDEF_STK;		/**< %jp{�^�X�N�̃X�^�b�N�̈�̐擪�Ԓn}%en{Base address of task stack space} */
#endif

#if _KERNEL_TCB_ISP
	_KERNEL_TCB_T_ISP		isp			_KERNEL_TCB_TBITDEF_ISP;		/**< %jp{�X�^�b�N�|�C���^�̏����l}%en{Task initial stack pointer} */
#endif

#if _KERNEL_TCB_TEXATR
	_KERNEL_TCB_T_TEXATR	texatr		_KERNEL_TCB_TBITDEF_TEXATR;		/**< %jp{�^�X�N��O�������[�`������} */
#endif

#if _KERNEL_TCB_TEXRTN
	_KERNEL_TCB_T_TEXRTN	texrtn		_KERNEL_TCB_TBITDEF_TEXRTN;		/**< %jp{�^�X�N��O�������[�`���̋N���Ԓn} */
#endif
} _KERNEL_T_TCB;

typedef _KERNEL_T_TCB				_KERNEL_T_TCB_RO;
typedef const _KERNEL_T_TCB_RO		*_KERNEL_T_TCB_RO_PTR;
typedef _KERNEL_T_TCB				*_KERNEL_T_TCB_PTR;

#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_tskid;										/**< %jp{�^�X�NID�̍ő�l} */

#define _KERNEL_TSK_TMIN_ID				1														/**< %jp{�^�X�NID�̍ŏ��l} */
#define _KERNEL_TSK_TMAX_ID				(_kernel_max_tskid)										/**< %jp{�^�X�NID�̍ő�l} */

#define _KERNEL_TSK_CHECK_TSKID(tskid)	((tskid) >= _KERNEL_TSK_TMIN_ID && (tskid) <= _KERNEL_TSK_TMAX_ID)
																								/**< %jp{ID�͈̓`�F�b�N} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_BLKARRAY
#if _KERNEL_TCB_SPLIT_RO

/* %jp{�u���b�N�z��Ǘ���RO�����̏ꍇ}%en{block array} */
extern  _KERNEL_T_TCB					_kernel_tcb_tbl[];										/**< %jp{�^�X�N�R���g���[���u���b�N�e�[�u��} */
extern const _KERNEL_T_TCB_RO			_kernel_tcb_ro_tbl[];									/**< %jp{�^�X�N�R���g���[���u���b�N(���[�h�I�����[��)�e�[�u��} */
#define _KERNEL_TSK_ID2TCB(tskid)		(&_kernel_tcb_tbl[(tskid) - _KERNEL_TSK_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_TSK_CHECK_EXS(tskid)	(_kernel_tcb_ro_tbl[(tskid) - _KERNEL_TSK_TMIN_ID].task != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#else

/* %jp{�u���b�N�z��Ǘ��̏ꍇ}%en{block array} */
extern  _KERNEL_T_TCB					_kernel_tcb_tbl[];										/**< %jp{�^�X�N�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_TSK_ID2TCB(tskid)		(&_kernel_tcb_tbl[(tskid) - _KERNEL_TSK_TMIN_ID])		/**< %jp{�R���g���[���u���b�N�̎擾} */
#define _KERNEL_TSK_CHECK_EXS(tskid)	(_kernel_tcb_tbl[(tskid) - _KERNEL_TSK_TMIN_ID].task != NULL)				
																								/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif

#elif _KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_PTRARRAY

/* %jp{�|�C���^�z��Ǘ��̏ꍇ}%en{pointer array} */
extern  _KERNEL_T_TCB					*_kernel_tcb_tbl[];										/**< %jp{�^�X�N�R���g���[���u���b�N�e�[�u��} */
#define _KERNEL_TSK_ID2TCB(tskid)		(_kernel_tcb_tbl[(tskid) - _KERNEL_TMIN_TSKID])			/**< %jp{�^�X�NID����TCB �A�h���X���擾} */
#define _KERNEL_TSK_CHECK_EXS(tskid)	(_KERNEL_TSK_ID2TCB(tskid) != NULL)						/**< %jp{�I�u�W�F�N�g�̑��݃`�F�b�N} */

#endif



/* ------------------------------------------ */
/*  Convert Handle                            */
/* ------------------------------------------ */

#if _KERNEL_TSKHDL_ID		/* %jp{�^�X�N�n���h����ID���g��}%en{TSKHDL is ID} */

#define _KERNEL_TSK_ID2TSKHDL(tskid)			(tskid)
#define _KERNEL_TSK_TSKHDL2ID(tskhdl)			(tskhdl)
#define _KERNEL_TSK_TCB2TSKHDL(tcb)				_KERNEL_TSK_TCB2ID(tcb)
#define _KERNEL_TSK_TSKHDL2TCB(tskhdl)			_KERNEL_TSK_ID2TCB(tskhdl)
#define _KERNEL_TSK_GET_TSKHDL(tskid, tcb)		(tskid)

#else						/* %jp{�^�X�N�n���h����TCB�̃A�h���X���g��}%en{TSKHDL is Address of TCB} */

#define _KERNEL_TSK_ID2TSKHDL(tskid)			_KERNEL_TSK_ID2TCB(tskid)
#define _KERNEL_TSK_TSKHDL2ID(tskhdl)			_KERNEL_TSK_TCB2ID(tskhdl)
#define _KERNEL_TSK_TCB2TSKHDL(tskhdl)			(tskhdl)
#define _KERNEL_TSK_TSKHDL2TCB(tskhdl)			(tskhdl)
#define _KERNEL_TSK_GET_TSKHDL(tskid, tcb)		(tcb)

#endif



/* ------------------------------------------ */
/*   Accessor for TCB                         */
/* ------------------------------------------ */

/* tcb_ro */
#if !_KERNEL_TCB_SPLIT_RO
#define _KERNEL_TSK_GET_TCB_RO(tskid, tcb)		(tcb)
#else
#if _KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_BLKARRAY		/* %jp{TCB��P���z��ŊǗ�}%en{array of block} */
#define _KERNEL_TSK_GET_TCB_RO(tskid, tcb)		(&_kernel_tcb_ro_tbl[(tskid)])
#elif _KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_PTRARRAY		/* %jp{TCB���|�C���^�z��ŊǗ�}%en{array of pointer} */
#define _KERNEL_TSK_GET_TCB_RO(tskid, tcb)		((tcb)->tcb_ro)
#endif
#endif


/* ctxcb */
#define _KERNEL_TSK_GET_CTXCB(tcb)				(&(tcb)->ctxcb)

/* que */
#if _KERNEL_TCB_QUE
#define _KERNEL_TSK_SET_QUE(tcb, x)				do { (tcb)->pk_que = (_KERNEL_T_QUE *)(x); } while(0)
#define _KERNEL_TSK_GET_QUE(tcb)				((_KERNEL_T_QUE *)(tcb)->pk_que)
#else	/* %jp{TCB�ɏ����L���[�̏����������Ȃ��ꍇ�͕ʏ�񂩂�̒T���ŋ��߂�} */
#define _KERNEL_TSK_SET_QUE(tcb, x)				do { } while(0)
#define _KERNEL_TSK_GET_QUE(tcb)				_kernel_get_que(tcb)
#endif

/* queobj */
#if _KERNEL_TCB_QUEOBJ
#define _KERNEL_TSK_CRE_QUEOBJ(tcb)				_KERNEL_CRE_QUEOBJ(tcb)
#define _KERNEL_TSK_DEL_QUEOBJ(tcb)				_KERNEL_DEL_QUEOBJ(tcb)
#else
#define _KERNEL_TSK_CRE_QUEOBJ(tcb)				do { } while(0)
#define _KERNEL_TSK_DEL_QUEOBJ(tcb)				do { } while(0)
#endif

/* toqobj */
#if _KERNEL_TCB_QUEOBJ
#define _KERNEL_TSK_CRE_TOQOBJ(tcb)				_KERNEL_CRE_TOQOBJ(tcb)
#define _KERNEL_TSK_DEL_TOQOBJ(tcb)				_KERNEL_DEL_TOQOBJ(tcb)
#else
#define _KERNEL_TSK_CRE_TOQOBJ(tcb)				do { } while(0)
#define _KERNEL_TSK_DEL_TOQOBJ(tcb)				do { } while(0)
#endif


/* tskstat */
#if _KERNEL_TCB_TSKSTAT
#define _KERNEL_TSK_SET_TSKSTAT(tcb, x)			do { (tcb)->tskstat = (_KERNEL_TCB_T_TSKSTAT)(x); } while(0)
#define _KERNEL_TSK_GET_TSKSTAT(tcb)			((_KERNEL_TSK_T_TSKSTAT)(tcb)->tskstat)
#else
#define _KERNEL_TSK_SET_TSKSTAT(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_TSKSTAT(tcb)			0
#endif

/* tskpri */
#if _KERNEL_TCB_TSKPRI	/* %jp{�ʏ��TCB�ւ̃A�N�Z�T} */
#define _KERNEL_TSK_SET_TSKPRI(tcb, x)			do { (tcb)->tskpri = (x); } while(0)
#define _KERNEL_TSK_GET_TSKPRI(tcb)				((tcb)->tskpri)
#else
#if _KERNEL_TCB_ITSKPRI	/* %jp{�D��x�Œ�(ROM�z�u)���̃A�N�Z�T} */
#define _KERNEL_TSK_SET_TSKPRI(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_TSKPRI(tcb)				((tcb)->itskpri)
#else					/* %jp{�D��x���g�p��(�S��FIFO��)��1�ɌŒ肷��} */
#define _KERNEL_TSK_SET_TSKPRI(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_TSKPRI(tcb)				(1)
#endif
#endif

/* tskbpri */
#if _KERNEL_TCB_TSKBPRI
#define _KERNEL_TSK_SET_TSKBPRI(tcb, x)			do { (tcb)->tskbpri = (x); } while(0)
#define _KERNEL_TSK_GET_TSKBPRI(tcb)			((tcb)->tskbpri)
#else
#define _KERNEL_TSK_SET_TSKBPRI(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_TSKBPRI(tcb)			_KERNEL_TSK_GET_TSKPRI(tcb)
#endif

/* tskwait */
#if _KERNEL_TCB_TSKWAIT
#define _KERNEL_TSK_SET_TSKWAIT(tcb, x)			do { (tcb)->tskwait = (x); } while(0)
#define _KERNEL_TSK_GET_TSKWAIT(tcb)			((tcb)->tskwait)
#else
#define _KERNEL_TSK_SET_TSKWAIT(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_TSKWAIT(tcb)			(0)
#endif

/* wobjid */
#if _KERNEL_TCB_WOBJID
#define _KERNEL_TSK_SET_WOBJID(tcb, x)			do { (tcb)->wobjid = (x); } while(0)
#define _KERNEL_TSK_GET_WOBJID(tcb)				((tcb)->wobjid)
#else
#define _KERNEL_TSK_SET_WOBJID(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_WOBJID(tcb)				(0)
#endif

/* actcnt */
#if _KERNEL_TCB_ACTCNT
#define _KERNEL_TSK_SET_ACTCNT(tcb, x)			do { (tcb)->actcnt = (x); } while(0)
#define _KERNEL_TSK_GET_ACTCNT(tcb)				((tcb)->actcnt)
#else
#define _KERNEL_TSK_SET_ACTCNT(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_ACTCNT(tcb)				(0)
#endif

/* wupcnt */
#if _KERNEL_TCB_WUPCNT
#define _KERNEL_TSK_SET_WUPCNT(tcb, x)			do { (tcb)->wupcnt = (x); } while(0)
#define _KERNEL_TSK_GET_WUPCNT(tcb)				((tcb)->wupcnt)
#else
#define _KERNEL_TSK_SET_WUPCNT(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_WUPCNT(tcb)				(0)
#endif

/* suscnt */
#if _KERNEL_TCB_SUSCNT
#define _KERNEL_TSK_SET_SUSCNT(tcb, x)			do { (tcb)->suscnt = (x); } while(0)
#define _KERNEL_TSK_GET_SUSCNT(tcb)				((tcb)->suscnt)
#else
#define _KERNEL_TSK_SET_SUSCNT(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_SUSCNT(tcb)				(0)
#endif

/* mtxhdl */
#if _KERNEL_TCB_MTXHDL
#define _KERNEL_TSK_SET_MTXHDL(tcb, x)			do { (tcb)->mtxhdl = (x); } while(0)
#define _KERNEL_TSK_GET_MTXHDL(tcb)				((tcb)->mtxhdl)
#else
#define _KERNEL_TSK_SET_MTXHDL(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_MTXHDL(tcb)				_KERNEL_MTXHDL_NULL
#endif

/* ercd */
#if _KERNEL_TCB_ERCD
#define _KERNEL_TSK_SET_ERCD(tcb, x)			do { (tcb)->ercd = (x); } while(0)
#define _KERNEL_TSK_GET_ERCD(tcb)				((tcb)->ercd)
#else
#define _KERNEL_TSK_SET_ERCD(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_ERCD(tcb)				(E_OK)
#endif

/* data */
#if _KERNEL_TCB_DATA
#define _KERNEL_TSK_SET_DATA(tcb, x)			do { (tcb)->data = (x); } while(0)
#define _KERNEL_TSK_GET_DATA(tcb)				((tcb)->data)
#else
#define _KERNEL_TSK_SET_DATA(tcb, x)			do { } while(0)
#define _KERNEL_TSK_GET_DATA(tcb)				(0)
#endif

/* texstat */
#if _KERNEL_TCB_TEXSTAT
#define _KERNEL_TSK_SET_TEXSTAT(tcb, x)			do { (tcb)->texstat = (_KERNEL_TCB_T_TEXSTAT)(x); } while (0)
#define _KERNEL_TSK_GET_TEXSTAT(tcb)				((_KERNEL_TSK_T_TEXSTAT)(tcb)->texstat)
#else
#define _KERNEL_TSK_SET_TEXSTAT(tcb, x)			do { } while (0)
#define _KERNEL_TSK_GET_TEXSTAT(tcb)			(_KERNEL_TXS_DIS)
#endif

/* rasptn */
#if _KERNEL_TCB_RASPTN
#define _KERNEL_TSK_SET_RASPTN(tcb, x)			do { (tcb)->rasptn = (_KERNEL_TCB_T_TEXPTN)(x); } while (0)
#define _KERNEL_TSK_GET_RASPTN(tcb)				((_KERNEL_TSK_T_TEXPTN)(tcb)->rasptn)
#else
#define _KERNEL_TSK_SET_RASPTN(texcb, x)		do { } while (0)
#define _KERNEL_TSK_GET_RASPTN(texcb)			(0)
#endif


/* tskid */
#if _KERNEL_TCB_TSKID
#define _KERNEL_TSK_SET_TSKID(tcb_ro, x)		do { (tcb_ro)->tskid = (x); } while(0)
#define _KERNEL_TSK_GET_TSKID(tcb_ro)			((tcb_ro)->tskid)
#else
#define _KERNEL_TSK_SET_TSKID(tcb_ro, x)		do { } while(0)
#define _KERNEL_TSK_GET_TSKID(tcb_ro)			(0)
#endif

/* tskatr */
#if _KERNEL_TCB_TSKATR
#define _KERNEL_TSK_SET_TSKATR(tcb_ro, x)		do { (tcb_ro)->tskatr = (x); } while(0)
#define _KERNEL_TSK_GET_TSKATR(tcb_ro)			((tcb_ro)->tskatr)
#else	/* %jp{tskatr���g�p����TA_HLNG�ɌŒ肷��} */
#define _KERNEL_TSK_SET_TSKATR(tcb_ro, x)		do { } while(0)
#define _KERNEL_TSK_GET_TSKATR(tcb_ro)			(TA_HLNG)
#endif

/* exinf */
#if _KERNEL_TCB_EXINF
#define _KERNEL_TSK_SET_EXINF(tcb_ro, x)		do { (tcb_ro)->exinf = (x); } while(0)
#define _KERNEL_TSK_GET_EXINF(tcb_ro)			((tcb_ro)->exinf)
#else
#define _KERNEL_TSK_SET_EXINF(tcb_ro, x)		do { } while(0)
#define _KERNEL_TSK_GET_EXINF(tcb_ro)			(0)
#endif

/* task */
#if _KERNEL_TCB_TASK
#define _KERNEL_TSK_SET_TASK(tcb_ro, x)			do { (tcb_ro)->task = (_KERNEL_TCB_T_TASK)(x); } while(0)
#define _KERNEL_TSK_GET_TASK(tcb_ro)			((_KERNEL_TSK_T_TASK)(tcb_ro)->task)
#else
#define _KERNEL_TSK_SET_TASK(tcb_ro, x)			do { } while(0)
#define _KERNEL_TSK_GET_TASK(tcb_ro)			(0)
#endif

/* tskipri */
#if _KERNEL_TCB_ITSKPRI
#define _KERNEL_TSK_SET_ITSKPRI(tcb_ro, x)		do { (tcb_ro)->itskpri = (x); } while(0)
#define _KERNEL_TSK_GET_ITSKPRI(tcb_ro)			((tcb_ro)->itskpri)
#else	/* %jp{tskatr���g�p����TA_HLNG�ɌŒ肷��} */
#define _KERNEL_TSK_SET_ITSKPRI(tcb_ro, x)		do { } while(0)
#define _KERNEL_TSK_GET_ITSKPRI(tcb_ro)			(1)
#endif

/* stksz */
#if _KERNEL_TCB_STKSZ
#define _KERNEL_TSK_SET_STKSZ(tcb_ro, x)		do { (tcb_ro)->stksz = (x); } while(0)
#define _KERNEL_TSK_GET_STKSZ(tcb_ro)			((tcb_ro)->stksz)
#else
#define _KERNEL_TSK_SET_STKSZ(tcb_ro, x)		do { } while(0)
#define _KERNEL_TSK_GET_STKSZ(tcb_ro)			(0)
#endif

/* stk */
#if _KERNEL_TCB_STK
#define _KERNEL_TSK_SET_STK(tcb_ro, x)			do { (tcb_ro)->stk = (x); } while(0)
#define _KERNEL_TSK_GET_STK(tcb_ro)				((tcb_ro)->stk)
#else
#define _KERNEL_TSK_SET_STK(tcb_ro, x)			do { } while(0)
#define _KERNEL_TSK_GET_STK(tcb_ro)				(0)
#endif

/* isp */
#if _KERNEL_TCB_ISP
#define _KERNEL_TSK_SET_ISP(tcb_ro, x)			do { (tcb_ro)->isp = (x); } while(0)
#define _KERNEL_TSK_GET_ISP(tcb_ro)				((tcb_ro)->isp)
#else
#define _KERNEL_TSK_SET_ISP(tcb_ro, x)			do { } while(0)
#define _KERNEL_TSK_GET_ISP(tcb_ro)				((VP)((UB *)_KERNEL_TSK_GET_STK(tcb_ro) + _KERNEL_TSK_GET_STKSZ(tcb_ro)))
#endif

/* texatr */
#if _KERNEL_TCB_TEXATR
#define _KERNEL_TSK_SET_TEXATR(tcb_ro, x)		do { (tcb_ro)->texatr = (_KERNEL_TCB_T_TEXATR)(x); } while (0)
#define _KERNEL_TSK_GET_TEXATR(tcb_ro)			((_KERNEL_TSK_T_TEXATR)(tcb_ro)->texatr)
#else
#define _KERNEL_TSK_SET_TEXATR(texcb_ro, x)		do { } while (0)
#define _KERNEL_TSK_GET_TEXATR(texcb_ro)		(0)
#endif

/* texrtn */
#if _KERNEL_TCB_TEXRTN
#define _KERNEL_TSK_SET_TEXRTN(tcb_ro, x)		do { (tcb_ro)->texrtn = (_KERNEL_TCB_T_TEXRTN)(x); } while (0)
#define _KERNEL_TSK_GET_TEXRTN(tcb_ro)			((_KERNEL_TSK_T_TEXRTN)(tcb_ro)->texrtn)
#else
#define _KERNEL_TSK_SET_TEXRTN(tcb_ro, x)		do { } while (0)
#define _KERNEL_TSK_GET_TEXRTN(tcb_ro)			(0)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

#if _KERNEL_TCB_TSKSTAT
#define _KERNEL_TSK_SNS_RDY(tcb)	(_KERNEL_TSK_GET_TSKSTAT(tcb) == _KERNEL_TTS_RDY)
#define _KERNEL_TSK_SNS_WAI(tcb)	(_KERNEL_TSK_GET_TSKSTAT(tcb) & _KERNEL_TTS_WAI)
#define _KERNEL_TSK_SNS_SUS(tcb)	(_KERNEL_TSK_GET_TSKSTAT(tcb) & _KERNEL_TTS_SUS)
#else
#define _KERNEL_TSK_SNS_RDY(tcb)	()
#define _KERNEL_TSK_SNS_WAI(tcb)	()
#define _KERNEL_TSK_SNS_SUS(tcb)	(_KERNEL_TSK_GET_SUSCNT(tcb) > 0)
#endif


#ifdef __cplusplus
extern "C" {
#endif

ER   _kernel_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);		/**< %jp{�^�X�N�̐���} */
void _kernel_exe_tex(_KERNEL_T_TSKHDL tskhdl);				/**< %jp{�^�X�N��O�����̎��s} */

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__tskobj_h__ */



/* end of file */
