/**
*	Copyright (c) 2018  Panasonic Corporation, All rights reserved
*	$Id$
*
*	@file
*	@brief	CtPlatforms.h
*/

#include "kernel.h"
#include "kernel_id.h"

#if !defined(__CT_PLATFORMS_H__)
#define __CT_PLATFORMS_H__

#if 0
#define	TWF_ANDW		0x0000			//!< AND�҂�.
#define	TWF_ORW 		0x0002			//!< OR�҂�.
#define E_TMOUT 		(-50)			//!< �|�[�����O���s�܂��̓^�C���A�E�g.
#define	TBIT_FLGPTN		32				//!< �C�x���g�t���O�̃r�b�g��.
#define	TCYC_STP		0x00			//!< �����n���h�������삵�Ă��Ȃ�.

typedef int				W;
typedef	int				ID;				//!< ID�ԍ�.
typedef	int				ER;				//!< �G���[�R�[�h.
typedef int				BOOL;
typedef int				INT;			//!< �����t������.
typedef unsigned int	UINT;			//!< ������������.
typedef unsigned int	UW;
typedef	unsigned int	FLGPTN;			//!< �C�x���g�t���O�E�p�^�[��.
typedef unsigned int	uint32;
typedef unsigned int	size_t;

typedef	INT				ID;				//!< ID�ԍ�.
typedef	INT				ER;				//!< �G���[�R�[�h.
typedef UINT			STAT;			//!< ������������.
typedef	SYSTIME			RELTIM;			//!< �����n���h���̎���.

typedef struct {
	ID 					wtskid;			//!< ���[���{�b�N�X�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	T_MSG				*pk_msg;		//!< ���b�Z�[�W�L���[�̐擪�̃��b�Z�[�W�p�P�b�g�̃A�h���X.
} T_RMBX;

typedef struct {
	short				utime;			//!< ���16�r�b�g.
	unsigned long		ltime;			//!< ����32�r�b�g.
} SYSTIME;

typedef struct {
	ID 					wtskid;			//!< �ϒ��������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT	/*SIZE*/		fmplsz;			//!< �ϒ��������v�[���̋󂫗̈�̍��v�T�C�Y.
	UINT				fblksz;			//!< �l���\�ȍő�̘A���󂫗̈�̃T�C�Y.
} T_RMPL;

typedef struct {
	STAT				cycstat;		//!< �����n���h���̓�����.
	RELTIM				lefttim; 		//!< ���̋N�������܂ł̎���.
} T_RCYC;


#define TMO_FEVR			(-1)		//!< �i�v�҂�.
#define E_OK				0			//!< ����I��.

#define TRUE				1
#define FALSE				0

#define E_OK				0			//!< ����I��.
#define E_CTX				(-25)		//!< �R���e�L�X�g�G���[.
#define	NULL				0
#endif

typedef int BOOL;
#define TRUE	1
#define FALSE	0

typedef unsigned int	uint32;
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

	extern void CtCycHandler(VP_INT exinf);
	extern void AvdfCycHandler(VP_INT exinf);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

extern void ct_init_platforms();
extern void ct_start(void);


////////////////////////////////////////////////////////////
extern ER ct_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);
extern ER ct_dly_tsk(DLYTIME dlytim);
extern ER ct_act_tsk(ID tskid);
extern ER ct_sta_tsk(ID tskid, VP_INT stacd);
extern ER ct_del_tsk(ID tskid);
extern ER ct_ref_tsk(ID tskid, T_RTSK * pk_rtsk);
extern ER ct_get_tid(ID *p_tskid);
extern ER ct_tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
extern ER ct_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);
extern ER ct_rel_mpl(ID mplid, VP blk);
extern ER ct_del_mpl(ID mplid);
extern ER ct_ref_mpl(ID mpfid, T_RMPL *pk_rmpl);
extern ER ct_cre_cyc(ID cycid, const T_CCYC *pk_ccyc);
extern ER ct_stp_cyc(ID cycid);
extern ER ct_del_cyc(ID cycid);
extern ER ct_sta_cyc(ID cycid);
extern ER ct_ref_cyc(ID cycid, T_RCYC *pk_rcyc);
extern ER ct_loc_cpu(void);
extern ER ct_iloc_cpu(void);
extern ER ct_unl_cpu(void);
extern ER ct_iunl_cpu(void);
extern ER ct_rel_wai(ID tskid);
extern ER ct_irel_wai(ID tskid);
extern ER ct_cre_sem(ID semid, const T_CSEM *pk_csem);
extern ER ct_del_sem(ID semid);
extern ER ct_sig_sem(ID semid);
extern ER ct_wai_sem(ID semid);
extern ER ct_pol_sem(ID semid);
extern ER ct_cre_flg(ID flgid, const T_CFLG *pk_cflg);
extern ER ct_del_flg(ID flgid);
extern ER ct_set_flg(ID flgid, FLGPTN setptn);
extern ER ct_iset_flg(ID flgid, FLGPTN setptn);
extern ER ct_wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
extern ER ct_twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
extern ER ct_clr_flg(ID flgid, FLGPTN clrptn);
extern ER ct_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);
extern ER ct_del_mbx(ID mbxid);
extern ER ct_snd_msg(ID mbxid, T_MSG *pk_msg);
extern ER ct_snd_mbx(ID mbxid, T_MSG *pk_msg);
extern ER ct_rcv_msg(ID mbxid, T_MSG **ppk_msg);
extern ER ct_rcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER ct_prcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER ct_trcv_msg(ID mbxid, T_MSG **ppk_msg, TMO tmout);
extern ER ct_ref_mbx(ID mbxid, T_RMBX *pk_rmbx);


#endif // !defined(__CT_PLATFORMS_H__)


