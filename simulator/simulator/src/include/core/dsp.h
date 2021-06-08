/**
 *  Hyper Operating System V4 Advance
 *
 * @file  dsp.h
 * @brief %jp{�^�X�N�f�B�X�p�b�`���̃w�b�_�t�@�C��}%en{task dispatcher heder file}
 *
 * Copyright (C) 1998-2009 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL_core__dsp_h__
#define _KERNEL_core__dsp_h__



#ifdef __cplusplus
extern "C" {
#endif

void _kernel_dsp_tsk(void);								/**< %jp{�^�X�N�f�B�X�p�b�`} */
void _kernel_ent_tsk(VP_INT exinf1, VP_INT exinf2);		/**< %jp{�^�X�N�G���g���[�|�C���g} */

void _kernel_dsp_sta_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{���^�X�N���J�n����} */
void _kernel_dsp_ext_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{���^�X�N���I������} */
void _kernel_dsp_ter_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{���^�X�N���I������} */
void _kernel_dsp_wai_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{���^�X�N��҂���Ԃɂ���} */
void _kernel_dsp_wup_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{���^�X�N��҂���������} */
void _kernel_dsp_sus_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{�^�X�N���T�X�y���h����} */
void _kernel_dsp_rsm_tsk(_KERNEL_T_TSKHDL tskhdl);		/**< %jp{�^�X�N���T�X�y���h��������} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_DSP_TSK()				_kernel_dsp_tsk()				/**< %jp{�^�X�N�X�P�W���[�����s} */


#if _KERNEL_SPT_SUS_TSK	/*  %jp{�T�X�y���h����̃��f���̏ꍇ} */

#define _KERNEL_DSP_STA_TSK(tskhdl)		_kernel_dsp_sta_tsk(tskhdl)		/**< %jp{���^�X�N���J�n����} */
#define _KERNEL_DSP_EXT_TSK(tskhdl)		_kernel_dsp_ext_tsk(tskhdl)		/**< %jp{���^�X�N���I������} */
#define _KERNEL_DSP_TER_TSK(tskhdl)		_kernel_dsp_ter_tsk(tskhdl)		/**< %jp{���^�X�N���I������} */
#define _KERNEL_DSP_WAI_TSK(tskhdl)		_kernel_dsp_wai_tsk(tskhdl)		/**< %jp{���^�X�N��҂���Ԃɂ���} */
#define _KERNEL_DSP_WUP_TSK(tskhdl)		_kernel_dsp_wup_tsk(tskhdl)		/**< %jp{���^�X�N��҂���������} */
#define _KERNEL_DSP_SUS_TSK(tskhdl)		_kernel_dsp_sus_tsk(tskhdl)		/**< %jp{�^�X�N���T�X�y���h����} */
#define _KERNEL_DSP_RSM_TSK(tskhdl)		_kernel_dsp_rsm_tsk(tskhdl)		/**< %jp{�^�X�N���T�X�y���h��������} */


#else /* %jp{�T�X�y���h�����̃��f���̏ꍇ} */

#if _KERNEL_RUNTSK_ON_RDQ	/* %jp{���s�������f�B�[�L���[�Ɍq���ꍇ} */

#define _KERNEL_DSP_STA_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_RDY); _KERNEL_ADD_RDQ(tskhdl); } while (0)		/**< %jp{���^�X�N���J�n����} */
#define _KERNEL_DSP_EXT_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_DMT); _KERNEL_RMV_RDQ(tskhdl); } while (0)		/**< %jp{���^�X�N���I������} */
#define _KERNEL_DSP_TER_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_DMT); _KERNEL_RMV_RDQ(tskhdl); } while (0)		/**< %jp{���^�X�N���I������} */
#define _KERNEL_DSP_WAI_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_WAI); _KERNEL_RMV_RDQ(tskhdl); } while (0)		/**< %jp{���^�X�N��҂���Ԃɂ���} */
#define _KERNEL_DSP_WUP_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_RDY); _KERNEL_ADD_RDQ(tskhdl); } while (0)		/**< %jp{���^�X�N��҂���������} */

#else /* %jp{���s���̓��f�B�[�L���[����O���ꍇ} */

#define _KERNEL_DSP_STA_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_RDY); _KERNEL_ADD_RDQ(tskhdl); } while (0)		/**< ���^�X�N���J�n���� */
#define _KERNEL_DSP_EXT_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_DMT);                          } while (0)		/**< ���^�X�N���I������ */
#define _KERNEL_DSP_TER_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_DMT); _KERNEL_RMV_RDQ(tskhdl); } while (0)		/**< ���^�X�N���I������ */
#define _KERNEL_DSP_WAI_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_WAI);                          } while (0)		/**< ���^�X�N��҂���Ԃɂ��� */
#define _KERNEL_DSP_WUP_TSK(tskhdl)		do { _KERNEL_TSK_SET_TSKSTAT(_KERNEL_TSK_TSKHDL2TCB(tskhdl), _KERNEL_TTS_RDY); _KERNEL_ADD_RDQ(tskhdl); } while (0)		/**< ���^�X�N��҂��������� */

#endif

#endif



#endif	/* _KERNEL_core__dsp_h__ */



/* end of file */
