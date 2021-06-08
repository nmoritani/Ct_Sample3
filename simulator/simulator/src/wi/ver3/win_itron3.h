/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron3.h
 *
 *	@brief	Windows�� iTRON(Ver3.0)�T�[�r�X�R�[��.
 *
 *	@author	���V �閾
 */
#ifndef	__WIN_ITRON3_H__
#define	__WIN_ITRON3_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �f�[�^��^�C�v.
 *
 ****************************************************************************/
typedef int				INT;			//!< �����t������.
typedef unsigned int	UINT;			//!< ������������.
typedef	void			*VP;			//!< �|�C���^�ϐ�.
typedef void			(*FP)();		//!< �֐��A�h���X.
typedef	VP				VP_INT;			//!< VP �܂��� INT.
typedef	INT				ER;				//!< �G���[�R�[�h.
typedef	INT				HNO;			//!< �n���h���ԍ�.
typedef	INT				RNO;			//!< �����f�u�ԍ�.
typedef	INT				ID;				//!< ID�ԍ�.
typedef	UINT			ATR;			//!< ����.
typedef	INT				PRI;			//!< �^�X�N�D��x.
typedef	INT				BOOL_ID;		//!< BOOL �܂��� ID.
typedef	INT				ER_UINT;		//!< �G���[�R�[�h �܂��� UINT.

/*!
 *
 * @brief �^�C�}�\����.
 *
 */
typedef struct {
	short				utime;			//!< ���16�r�b�g.
	unsigned long		ltime;			//!< ����32�r�b�g.
} SYSTIME;

typedef	SYSTIME			CYCTIME;		//!< �����n���h���̎���.
typedef	SYSTIME			ALMTIME;		//!< �A���[���n���h���̎���.
typedef	long			DLYTIME;		//!< �^�X�N�f�B���C����.
typedef	long			TMO;			//!< �^�C���A�E�g�ݒ�l.

#define	TASK			void			//!< �^�X�N�̊֐��^�C�v.
#define TMRHDR			void			//!< �^�C�}��n���h���̊֐��^�C�v.
#define INTHDR			void			//!< ���荞�݃n���h���̊֐��^�C�v.

/****************************************************************************
 *
 * �V���{����`.
 *
 ****************************************************************************/
//! �I�u�W�F�N�g�̑���.
#define TA_ASM	 	0x0000				//!< �A�Z���u���ɂ��v���O����.
#define TA_HLNG 	0x0001				//!< ��������ɂ��v���O����.
#define TA_TFIFO	0x0000				//!< �҂��^�X�N��FIFO.
#define TA_TPRI 	0x0001				//!< �҂��^�X�N�͗D��x��.

//! �^�C���A�E�g�ݒ�.
#define TMO_POL 	0					//!< �|�[�����O.
#define TMO_FEVR	(-1)				//!< �i�v�҂�.

/****************************************************************************
 *
 * �G���[�R�[�h.
 *
 ****************************************************************************/
#define E_OK		0					//!< ����I��.
#define E_SYS		(-5)				//!< �V�X�e���G���[.
#define E_NOMEM 	(-10)				//!< �������s��.
#define E_NOSPT 	(-17)				//!< ���T�|�[�g�@�\.
#define E_INOSPT	(-18)				//!< ITRON/FILE�ł̖��T�|�[�g�@�\.
#define E_RSFN		(-20)				//!< �\��@�\�R�[�h�ԍ�.
#define E_RSATR 	(-24)				//!< �\�񑮐�.
#define E_PAR		(-33)				//!< �p�����[�^�G���[.
#define E_ID		(-35)				//!< �s��ID�ԍ�.
#define E_NOEXS 	(-52)				//!< �I�u�W�F�N�g�����݂��Ȃ�.
#define E_OBJ		(-63)				//!< �I�u�W�F�N�g�̏�Ԃ��s��.
#define E_MACV		(-65)				//!< �������A�N�Z�X�s�\�A�������A�N�Z�X���ᔽ.
#define E_OACV		(-66)				//!< �I�u�W�F�N�g�A�N�Z�X���ᔽ.
#define E_CTX		(-69)				//!< �R���e�L�X�g�G���[.
#define E_QOVR		(-73)				//!< �L���[�C���O�܂��̓l�X�g�̃I�[�o�[�t���[.
#define E_DLT		(-81)				//!< �҂��I�u�W�F�N�g���폜���ꂽ.
#define E_TMOUT 	(-85)				//!< �|�[�����O���s�܂��̓^�C���A�E�g.
#define E_RLWAI 	(-86)				//!< �҂���ԋ�������.
#define E_ILUSE		E_OBJ				//!< �T�[�r�X�R�[���s���g�p.

/****************************************************************************
 *
 * �^�X�N�Ǘ��@�\.
 *
 ****************************************************************************/
/*!
 *
 * @brief �^�X�N�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			tskatr;				//!< �^�X�N�̑���.
	FP			task;				//!< �X�^�[�g��A�h���X.
	PRI			itskpri;			//!< �����̃^�X�N�D��x.
	INT			stksz;				//!< �X�^�b�N��T�C�Y.
} T_CTSK;

/*!
 *
 * @brief �^�X�N��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	PRI			tskpri; 			//!< ���݂̗D��x.
	UINT		tskstat;			//!< �^�X�N���.
	UINT		tskwait;			//!< �҂��v��.
	ID			wid; 				//!< �҂��I�u�W�F�N�gID.
	INT			wupcnt;				//!< �N���v���J�E���g.
	INT			suscnt;				//!< �T�X�y���h�v���J�E���g.
	ATR			tskatr; 			//!< �^�X�N����.
	FP			task;				//!< �^�X�N�̋N���A�h���X.
	PRI			itskpri;			//!< �^�X�N�N�����D��x.
	INT			stksz;				//!< �X�^�b�N�T�C�Y.
} T_RTSK;

/*!
 *
 * @brief �^�X�NID�ݒ�l.
 *
 */
#define TSK_SELF	0				//!< ���^�X�N�w��.
 
/*!
 *
 * @brief �^�X�N�D��x(tskpri).
 *
 */
#define TPRI_INI	0				//!< �^�X�N�N�����̏����D��x���w�� (chg_pri).
#define TPRI_RUN	0				//!< ���̎����s���̍ō��D��x���w�� (rot_rdq).

/*!
 *
 * @brief �^�X�N���s���(tskstat).
 *
 */
#define	TTS_RUN 	0x0001			//!< �^�X�N���s���.
#define	TTS_RDY 	0x0002			//!< �^�X�N���s�\���.
#define	TTS_WAI 	0x0004			//!< �^�X�N�҂����.
#define	TTS_SUS 	0x0008			//!< �����҂����.
#define	TTS_WAS 	0x000C			//!< ��d�҂����.
#define	TTS_DMT 	0x0010			//!< �^�X�N�x�~��.
 
/*!
 *
 * @brief �^�X�N�҂��v��(tskwait).
 *
 */
#define TTW_SLP 	0x0001			//!< �N���҂�.
#define TTW_DLY 	0x0002			//!< ���Ԍo�ߑ҂�.
#define TTW_FLG 	0x0010			//!< �C�x���g�t���O�҂�.
#define TTW_SEM 	0x0020			//!< �Z�}�t�H�����l���҂�.
#define TTW_MBX 	0x0040			//!< ���[���{�b�N�X����̎�M�҂�.
#define TTW_SMBF	0x0080			//!< ���b�Z�[�W�o�b�t�@�ւ̑��M�҂�.
#define TTW_RMBF 	0x0100			//!< ���b�Z�[�W�o�b�t�@����̎�M�҂�.
#define TTW_CAL 	0x0200			//!< �����f�u�ďo�҂�.
#define TTW_ACP 	0x0400			//!< �����f�u��t�҂�.
#define TTW_RDV 	0x0800			//!< �����f�u�I���҂�.
#define TTW_MPL 	0x1000			//!< �ϒ��������u���b�N�̊l���҂�.
#define TTW_MPF 	0x2000			//!< �Œ蒷�������u���b�N�̊l���҂�.
#define TTW_SDTQ 	0x0000			//!< �f�[�^�L���[�ւ̑��M�҂�   (Ver3.0�ł͎g�p���Ȃ�).
#define TTW_RDTQ 	0x0000			//!< �f�[�^�L���[����̎�M�҂� (Ver3.0�ł͎g�p���Ȃ�).
#define TTW_MTX 	0x0000			//!< �~���[�e�b�N�X�̃��b�N�҂� (Ver3.0�ł͎g�p���Ȃ�).

// �T�[�r�X�R�[���̒�`.
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk );
ER		del_tsk( ID tskid );
ER		sta_tsk( ID tskid, VP_INT stacd );
void	ext_tsk( void );
void	exd_tsk( void );
ER		ter_tsk( ID tskid );
ER		chg_pri( ID tskid, PRI tskpri );
ER		ref_tsk( T_RTSK *pk_rtsk, ID tskid );
ER		slp_tsk( void );
ER		tslp_tsk( TMO tmout );
ER		wup_tsk( ID tskid );
ER		can_wup( INT *p_wupcnt, ID tskid );
ER		rel_wai( ID tskid );
ER		sus_tsk( ID tskid );
ER		rsm_tsk( ID tskid );
ER		frsm_tsk( ID tskid );
ER		dly_tsk( DLYTIME dlytim );
 
/****************************************************************************
 *
 * ������ʐM�@�\ (�Z�}�t�H).
 *
 ****************************************************************************/
/*!
 *
 * @brief �Z�}�t�H�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			sematr;				//!< �Z�}�t�H�̑���.
	INT			isemcnt;			//!< �Z�}�t�H�̏����l.
	INT			maxsem; 			//!< �Z�}�t�H�̍ő�l.
} T_CSEM;

/*!
 *
 * @brief �Z�}�t�H��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID 	wtsk;				//!< �҂��^�X�N�̗L��.
	INT			semcnt;				//!< ���݂̃Z�}�t�H�J�E���g�l.
} T_RSEM;

// �T�[�r�X�R�[���̒�`.
ER		cre_sem( ID semid, const T_CSEM *pk_csem );
ER		del_sem( ID semid );
ER		sig_sem( ID semid );
ER		wai_sem( ID semid );
ER		pol_sem( ID semid );
ER		twai_sem( ID semid, TMO tmout );
ER		ref_sem( T_RSEM *pk_rsem, ID semid );

/****************************************************************************
 *
 * ������ʐM�@�\ (�C�x���g�t���O).
 *
 ****************************************************************************/
/*!
 *
 * @brief �C�x���g�t���O�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			flgatr;				//!< �C�x���g�t���O�̑���.
	UINT		iflgptn;			//!< �C�x���g�t���O�̏����l.
} T_CFLG;

/*!
 *
 * @brief �C�x���g�t���O��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< �҂��^�X�N�̗L��.
	UINT		flgptn;				//!< �C�x���g�t���O�̃r�b�g�p�^�[��.
} T_RFLG;

/*!
 *
 * @brief �C�x���g�t���O����(flgatr).
 *
 */
#define TA_WSGL 	0x0000			//!< �����^�X�N�̑҂��������Ȃ�.
#define TA_WMUL 	0x0008			//!< �����^�X�N�̑҂�������.
#define	TA_CLR		0x0004			//!< �t���O�p�^�[���̃N���A (Ver3.0�ł͎g��Ȃ�).

/*!
 *
 * @brief �C�x���g�t���O�̑҂�����(wfmode).
 *
 */
#define	TWF_ANDW	0x0000			//!< AND�҂�.
#define	TWF_ORW 	0x0002			//!< OR�҂�.
#define	TWF_CLR 	0x0001			//!< �N���A�w��.

// �T�[�r�X�R�[���̒�`.
ER		cre_flg( ID flgid, const T_CFLG *pk_cflg );
ER		del_flg( ID flgid );
ER		set_flg( ID flgid, UINT setptn );
ER		clr_flg( ID flgid, UINT clrptn );
ER		wai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode );
ER		pol_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode );
ER		twai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode, TMO tmout );
ER		ref_flg( T_RFLG *pk_rflg, ID flgid );

/****************************************************************************
 *
 * ������ʐM�@�\ (���[���{�b�N�X).
 *
 ****************************************************************************/
/*!
 *
 * @brief ���b�Z�[�W��p�P�b�g�\����.
 *
 */
typedef struct _T_MSG {
	struct _T_MSG	*nextmsg;		//!< ���̃��b�Z�[�W��p�P�b�g�\���̂̃|�C���^.
	PRI				msgpri;			//!< ���b�Z�[�W�̗D��x.
} T_MSG;

/*!
 *
 * @brief ���[���{�b�N�X�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			mbxatr;				//!< ���[���{�b�N�X�̑���.
} T_CMBX;

/*!
 *
 * @brief ���[���{�b�N�X��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< �҂��^�X�N�̗L��.
	T_MSG		*pk_msg;			//!< ���Ɏ�M����郁�b�Z�[�W.
} T_RMBX;

/*!
 *
 * @brief ���[���{�b�N�X����(mbxatr).
 *
 */
#define TA_MFIFO	0x0000			//!< ���b�Z�[�W��FIFO.
#define TA_MPRI 	0x0002			//!< ���b�Z�[�W�͗D��x��.
 
// �T�[�r�X�R�[���̒�`.
ER		cre_mbx( ID mbxid, const T_CMBX *pk_cmbx );
ER		del_mbx( ID mbxid );
ER		snd_msg( ID mbxid, T_MSG *pk_msg );
ER		rcv_msg( T_MSG **ppk_msg, ID mbxid );
ER		prcv_msg( T_MSG **ppk_msg, ID mbxid );
ER		trcv_msg( T_MSG **ppk_msg, ID mbxid, TMO tmout );
ER		ref_mbx( T_RMBX *pk_rmbx, ID mbxid );
 
/****************************************************************************
 *
 * �g��������ʐM�@�\ (���b�Z�[�W�o�b�t�@).
 *
 ****************************************************************************/
/*!
 *
 * @brief ���b�Z�[�W�o�b�t�@�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			mbfatr; 			//!< ���b�Z�[�W�o�b�t�@�̑���.
	INT			bufsz;				//!< ���b�Z�[�W�o�b�t�@�̃T�C�Y.
	INT			maxmsz; 			//!< ���b�Z�[�W�̍ő咷.
} T_CMBF;

/*!
 *
 * @brief ���b�Z�[�W�o�b�t�@��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< ��M�҂��^�X�N�̗L��.
	BOOL_ID		stsk;				//!< ���M�҂��^�X�N�̗L��.
	INT			msgsz;				//!< ���Ɏ�M����郁�b�Z�[�W�̃T�C�Y.
	INT			frbufsz;			//!< �󂫃o�b�t�@�̃T�C�Y.
} T_RMBF;

// �T�[�r�X�R�[���̒�`.
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf );
ER		del_mbf( ID mbfid );
ER		snd_mbf( ID mbfid, VP msg, INT msgsz );
ER		psnd_mbf( ID mbfid, VP msg, INT msgsz );
ER		tsnd_mbf( ID mbfid, VP msg, INT msgsz, TMO tmout );
ER		rcv_mbf( VP msg, INT *p_msgsz, ID mbfid );
ER		prcv_mbf( VP msg, INT *p_msgsz, ID mbfid );
ER		trcv_mbf( VP msg, INT *p_msgsz, ID mbfid, TMO tmout );
ER		ref_mbf( T_RMBF *pk_rmbf, ID mbfid );

/****************************************************************************
 *
 * �g��������ʐM�@�\ (�����f�u).
 *
 ****************************************************************************/
/*!
 *
 * @brief �����f�u�|�[�g�������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			poratr; 			//!< �|�[�g����.
	INT			maxcmsz;			//!< �ďo���̃��b�Z�[�W�̍ő咷.
	INT			maxrmsz;			//!< �ԓ����̃��b�Z�[�W�̍ő咷.
} T_CPOR;

/*!
 *
 * @brief �����f�u�|�[�g��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< �ďo�҂��^�X�N�̗L��.
	BOOL_ID		atsk;				//!< ��t�҂��^�X�N�̗L��.
} T_RPOR;

// �T�[�r�X�R�[���̒�`.
ER		cre_por( ID porid, const T_CPOR *pk_cpor );
ER		del_por( ID porid );
ER		cal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz );
ER		pcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz );
ER		tcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz, TMO tmout );
ER		acp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn );
ER		pacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn );
ER		tacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn, TMO tmout );
ER		fwd_por( ID porid, UINT calptn, RNO rdvno , VP msg, INT cmsgsz );
ER		rpl_rdv( RNO rdvno, VP msg, INT cmsgsz );
ER		ref_por( T_RPOR *pk_rpor, ID porid );

/****************************************************************************
 *
 * �������v�[���Ǘ��@�\ (�Œ蒷�������v�[��).
 *
 ****************************************************************************/
/*!
 *
 * @brief �Œ蒷�������v�[���������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			mpfatr; 			//!< �Œ蒷�������v�[���̑���.
	INT			mpfcnt; 			//!< �Œ蒷�������v�[���S�̂̃u���b�N��.
	INT			blfsz;				//!< �Œ蒷��������u���b�N�̃T�C�Y.
} T_CMPF;

/*!
 *
 * @brief �Œ蒷�������v�[����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< �҂��^�X�N�̗L��.
	INT			frbcnt; 			//!< �󂫃u���b�N�̌�.
} T_RMPF;

// �T�[�r�X�R�[���̒�`.
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf );
ER		del_mpf( ID mpfid );
ER		get_blf( VP *p_blf, ID mpfid );
ER		pget_blf( VP *p_blf, ID mpfid );
ER		tget_blf( VP *p_blf, ID mpfid, TMO tmout );
ER		rel_blf( ID mpfid, VP blk );
ER		ref_mpf( T_RMPF *pk_rmpf, ID mpfid );

/****************************************************************************
 *
 * �������v�[���Ǘ��@�\ (�ϒ��������v�[��).
 *
 ****************************************************************************/
/*!
 *
 * @brief �ϒ��������v�[���������\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			mplatr; 			//!< �ϒ��������v�[������.
	INT			mplsz;				//!< �ϒ��������v�[���̃T�C�Y.
} T_CMPL; 

/*!
 *
 * @brief �ϒ��������v�[����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	BOOL_ID		wtsk;				//!< �҂��^�X�N�̗L��.
	INT			frsz;				//!< �󂫗̈�̍��v�T�C�Y.
	INT			maxsz;				//!< �ő�̘A���󂫗̈�̃T�C�Y.
} T_RMPL; 

// �T�[�r�X�R�[���̒�`.
ER		cre_mpl( ID mplid, const T_CMPL *pk_cmpl );
ER		del_mpl( ID mplid );
ER		get_blk( VP p_blk, ID mplid, INT blksz );
ER		pget_blk( VP p_blk, ID mplid, INT blksz );
ER		tget_blk( VP p_blk, ID mplid, INT blksz, TMO tmout );
ER		rel_blk( ID mplid, VP blk );
ER		ref_mpl(T_RMPL *pk_rmpl, ID mplid );

/****************************************************************************
 *
 * ���ԊǗ��@�\.
 *
 ****************************************************************************/

// �T�[�r�X�R�[���̒�`.
ER		set_tim( const SYSTIME *pk_tim );
ER		get_tim( SYSTIME *pk_tim );

#define	ret_tmr()	return

/****************************************************************************
 *
 * ���ԊǗ��@�\ (�����n���h��).
 *
 ****************************************************************************/
/*!
 *
 * @brief �����n���h����`���p�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			cycatr; 			//!< �����n���h������.
	FP			cychdr;				//!< �����n���h���̃A�h���X.
	UINT		cycact;				//!< �����n���h���̊������.
	CYCTIME		cyctim; 			//!< �����N�����ԊԊu.
} T_DCYC;

/*!
 *
 * @brief �����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	CYCTIME		lfttim; 			//!< ���̋N�������܂ł̎���.
	UINT		cycact;				//!< �����n���h���̊������.
} T_RCYC;

/*!
 *
 * @brief �����n���h���������(cycact).
 *
 */
#define	TCY_OFF 	0x0000			//!< �����n���h���̒�~.
#define	TCY_ON		0x0001			//!< �����n���h���̋N��.
#define	TCY_INI 	0x0002			//!< �����J�E���^�̏�����.

// �T�[�r�X�R�[���̒�`.
ER		def_cyc( HNO cycno, const T_DCYC *pk_dcyc );
ER		act_cyc( HNO cycno, UINT cycact );
ER		ref_cyc( T_RCYC *pk_rcyc, HNO cycno );

/****************************************************************************
 *
 * ���ԊǗ��@�\ (�A���[����n���h��).
 *
 ****************************************************************************/
/*!
 *
 * @brief �A���[����n���h����`���p�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ATR			almatr; 			//!< �A���[����n���h������.
	FP			almhdr;				//!< �A���[����n���h���̃A�h���X.
	UINT		tmmode;				//!< �N�������w�胂�[�h.
	ALMTIME		almtim; 			//!< �N������.
} T_DALM;

/*!
 *
 * @brief �A���[����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			exinf;				//!< �g�����.
	ALMTIME		lfttim; 			//!< �N�������܂ł̎���.
} T_RALM;

/*!
 *
 * @brief �N�������w�胂�[�h(tmmode).
 *
 */
#define TTM_ABS 	0x0000			//!< ��Ύ����ł̎w��.
#define TTM_REL 	0x0001			//!< ���Ύ����ł̎w��.

// �T�[�r�X�R�[���̒�`.
ER		def_alm( HNO almno, const T_DALM *pk_dalm );
ER		ref_alm( T_RALM *pk_ralm, HNO almno );

/****************************************************************************
 *
 * ���荞�݊Ǘ��@�\.
 *
 ****************************************************************************/
/*!
 *
 * @brief �����݃n���h����`���p�\����.
 *
 */
typedef struct {
	ATR			intatr; 			//!< �����݃n���h������.
	FP			inthdr;				//!< �����݃n���h���A�h���X.
} T_DINT; 

// �T�[�r�X�R�[���̒�`.
ER		def_int( UINT dintno, const T_DINT *pk_dint );
ER		dis_int( UINT eintno );
ER		ena_int( UINT eintno );
ER		loc_cpu( void );
ER		unl_cpu( void );
#define	ret_int()		return
#define	ret_wup( _a )	return

/****************************************************************************
 *
 * �V�X�e���Ǘ��@�\.
 *
 ****************************************************************************/
/*!
 *
 * @brief �o�[�W�������\����.
 *
 */
typedef struct {
	unsigned short		maker;		//!< ���[�J�[.
	unsigned short		id;			//!< �`���ԍ�.
	unsigned short		spver;		//!< �d�l���o�[�W����.
	unsigned short		prver;		//!< ���i�o�[�W����.
	unsigned short		prno[4];	//!< ���i�Ǘ����.
	unsigned short		cpu;		//!< CPU���.
	unsigned short		var;		//!< �o���G�[�V�����L�q�q.
} T_VER;

/*!
 *
 * @brief �V�X�e�����\����.
 *
 */
typedef struct {
	INT			sysstat;			//!< �V�X�e�����.
} T_RSYS;
 
/*!
 *
 * @brief �R���t�B�O���[�V�����\����.
 *
 */
typedef struct {
	VP			dummy;				//!< ������`�݂̂̂��߃_�~�[�̃����o�ϐ����`.
} T_RCFG; 

/*!
 *
 * @brief �V�X�e�����(sysstat).
 *
 */
#define TSS_TSK 	0				//!< �^�X�N�����s���Ńf�B�X�p�b�`���������ʏ�̏��.
#define TSS_DDSP	1				//!< �^�X�N�����s����dis_dsp�����s������̏��(�f�B�X�p�b�`�֎~��).
#define TSS_LOC 	3				//!< �^�X�N�����s����loc_cpu�����s������̏��(�����݂���уf�B�X�p�b�`�֎~��).
#define TSS_INDP	4				//!< �^�X�N�Ɨ���(���荞�݃n���h���A�^�C�}�n���h��)���s��.

// �T�[�r�X�R�[���̒�`.
ER		rot_rdq( PRI tskpri );
ER		get_tid( ID *p_tskid );
ER		dis_dsp( void );
ER		ena_dsp( void );
ER		ref_sys( T_RSYS *pk_rsys );
ER		get_ver( T_VER *pk_ver );
ER		ref_cfg( T_RCFG *pk_rcfg );

#ifdef __cplusplus
}
#endif
#endif	// __WIN_ITRON3_H__
/* End of file */
