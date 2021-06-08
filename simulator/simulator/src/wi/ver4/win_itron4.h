/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron4.h
 *
 *	@brief	Windows�� iTRON(Ver4.0)�T�[�r�X�R�[��.
 *
 *	@author	���V �閾
 */
#ifndef	__WIN_ITRON4_H__
#define	__WIN_ITRON4_H__

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
typedef void			(*FP)();		//!< �֐��G���g����A�h���X.
typedef	VP				VP_INT;			//!< VP �܂��� INT.
typedef	INT				ER;				//!< �G���[�R�[�h.
typedef	INT				HNO;			//!< �n���h���ԍ�.
typedef	INT				RDVNO;			//!< �����f�u�ԍ�.
typedef	INT				ID;				//!< ID�ԍ�.
typedef	UINT			ATR;			//!< ����.
typedef	INT				PRI;			//!< �^�X�N�D��x.
typedef	INT				FN;				//!< �t�@���N�V������R�[�h.
typedef	INT				ER_UINT;		//!< �G���[�R�[�h �܂��� UINT.
typedef	INT				ER_ID;			//!< �G���[�R�[�h �܂��� ID.
typedef UINT			STAT;			//!< ������������.
typedef UINT			INTNO;			//!< ���荞�ݔԍ�.
typedef	UINT			TEXPTN;			//!< �^�X�N��O�v��.
typedef	UINT			FLGPTN;			//!< �C�x���g�t���O��p�^�[��.
typedef	UINT			RDVPTN;			//!< �����f�u����.
typedef	UINT			MODE;			//!< �҂����[�h.
typedef INT				BOOL;
typedef unsigned short	USHORT;
typedef short			SHORT;

typedef unsigned long long	UD;
typedef unsigned long		UW;
typedef unsigned short		UH;
typedef unsigned char		UB;
typedef signed long long	D;
typedef signed int			W;
typedef signed short		H;
typedef signed char			B;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/*!
 *
 * @brief �^�C�}�\����.
 *
 */
typedef struct
{
	short				utime;			//!< ���16�r�b�g.
    unsigned long		ltime;			//!< ����32�r�b�g.
} SYSTIME;

typedef SYSTIME			SYSTIM;

typedef	SYSTIME			RELTIM;			//!< �����n���h���̎���.
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
#define	TA_ACT		0x0002				//!< �^�X�N�����シ���ɋN��.
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
#define E_NOSPT 	(-9)				//!< ���T�|�[�g�@�\.
#define E_RSFN		(-10)				//!< �\��@�\�R�[�h�ԍ�.
#define E_RSATR 	(-11)				//!< �\�񑮐�.
#define E_PAR		(-17)				//!< �p�����[�^�G���[.
#define E_ID		(-18)				//!< �s��ID�ԍ�.
#define E_CTX		(-25)				//!< �R���e�L�X�g�G���[.
#define E_MACV		(-26)				//!< �������A�N�Z�X�s�\�A�������A�N�Z�X���ᔽ.
#define E_OACV		(-27)				//!< �I�u�W�F�N�g�A�N�Z�X���ᔽ.
#define E_ILUSE		(-28)				//!< �T�[�r�X�R�[���s���g�p.
#define E_NOMEM 	(-33)				//!< �������s��.
#define E_NOID	 	(-34)				//!< ID�ԍ��s��.
#define E_OBJ		(-41)				//!< �I�u�W�F�N�g�̏�Ԃ��s��.
#define E_NOEXS 	(-42)				//!< �I�u�W�F�N�g�����݂��Ȃ�.
#define E_QOVR		(-43)				//!< �L���[�C���O�܂��̓l�X�g�̃I�[�o�[�t���[.
#define E_RLWAI 	(-49)				//!< �҂���ԋ�������.
#define E_TMOUT 	(-50)				//!< �|�[�����O���s�܂��̓^�C���A�E�g.
#define E_DLT		(-51)				//!< �҂��I�u�W�F�N�g���폜���ꂽ.
#define E_CLS		(-52)				//!< �҂��I�u�W�F�N�g�̏�Ԃ��ω�����.
#define E_WBLK		(-57)				//!< �m���u���b�L���O��t��.
#define E_BOVR		(-58)				//!< �o�b�t�@�I�[�o�[�t���[.

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
	ATR			tskatr;				//!< �^�X�N�̑���.
	VP_INT		exinf;				//!< �g�����.
	FP			task;				//!< �X�^�[�g��A�h���X.
	PRI			itskpri;			//!< �����̃^�X�N�D��x.
	INT			stksz;				//!< �X�^�b�N��T�C�Y.
	VP			stk;				//!< �X�^�b�N�̈�̐擪�A�h���X.
} T_CTSK;

/*!
 *
 * @brief �^�X�N��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	STAT		tskstat;			//!< �^�X�N���.
	PRI			tskpri; 			//!< ���݂̗D��x.
	PRI			tskbpri; 			//!< �x�[�X�D��x.
	STAT		tskwait;			//!< �҂��v��.
	ID			wobjid; 			//!< �҂��I�u�W�F�N�gID.
	TMO			lefttmo;			//!< �^�C���A�E�g�܂ł̎���.
	UINT		actcnt;				//!< �N���v���J�E���g.
	UINT		wupcnt;				//!< �N���v���J�E���g.
	UINT		suscnt;				//!< �T�X�y���h�v���J�E���g.
} T_RTSK;

/*!
 *
 * @brief �^�X�N��Ԃ̎Q�Ɨp�\���� (�ȈՔ�).
 *
 */
typedef struct {
	STAT		tskstat;			//!< �^�X�N���.
	STAT		tskwait;			//!< �҂��v��.
} T_RTST;

/*!
 *
 * @brief �^�X�N��O�����̒�`�p�\����.
 *
 */
typedef struct {
	ATR			texatr;				//!< �^�X�N��O�������[�`���̑���.
	FP			texrtn;				//!< �^�X�N��O�������[�`���̃X�^�[�g��A�h���X.
} T_DTEX;

/*!
 *
 * @brief �^�X�N��O������Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	STAT		texstat;			//!< �^�X�N��O�����̏��.
	TEXPTN		pndptn; 			//!< �ۗ���O�v��.
} T_RTEX;

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
#define TTW_SEM 	0x0004			//!< �Z�}�t�H�����l���҂�.
#define TTW_FLG 	0x0008			//!< �C�x���g�t���O�҂�.
#define TTW_SDTQ 	0x0010			//!< �f�[�^�L���[�ւ̑��M�҂�.
#define TTW_RDTQ 	0x0020			//!< �f�[�^�L���[����̎�M�҂�.
#define TTW_MBX 	0x0040			//!< ���[���{�b�N�X����̎�M�҂�.
#define TTW_MTX 	0x0080			//!< �~���[�e�b�N�X�̃��b�N�҂�.
#define TTW_SMBF	0x0100			//!< ���b�Z�[�W�o�b�t�@�ւ̑��M�҂�.
#define TTW_RMBF	0x0200			//!< ���b�Z�[�W�o�b�t�@����̎�M�҂�.
#define TTW_CAL 	0x0400			//!< �����f�u�ďo�҂�.
#define TTW_ACP 	0x0800			//!< �����f�u��t�҂�.
#define TTW_RDV 	0x1000			//!< �����f�u�I���҂�.
#define TTW_MPF 	0x2000			//!< �Œ蒷�������u���b�N�̊l���҂�.
#define TTW_MPL 	0x4000			//!< �ϒ��������u���b�N�̊l���҂�.

// �T�[�r�X�R�[���̒�`.
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk );
ER_ID	acre_tsk( const T_CTSK *pk_ctsk );
ER		del_tsk( ID tskid );
ER		act_tsk( ID tskid );
ER		iact_tsk( ID tskid );
ER_UINT	can_act( ID tskid );
ER		sta_tsk( ID tskid, VP_INT stacd );
void	ext_tsk( void );
void	exd_tsk( void );
ER		ter_tsk( ID tskid );
ER		chg_pri( ID tskid, PRI tskpri );
ER		get_pri( ID tskid, PRI *p_tskpri );
ER		ref_tsk( ID tskid, T_RTSK *pk_rtsk );
ER		ref_tst( ID tskid, T_RTST *pk_rtst );
ER		slp_tsk( void );
ER		tslp_tsk( TMO tmout );
ER		wup_tsk( ID tskid );
ER		iwup_tsk( ID tskid );
ER_UINT	can_wup( ID tskid );
ER		rel_wai( ID tskid );
ER		irel_wai( ID tskid );
ER		sus_tsk( ID tskid );
ER		rsm_tsk( ID tskid );
ER		frsm_tsk( ID tskid );
ER		dly_tsk( DLYTIME dlytim );
ER		def_tex( ID tskid, T_DTEX *pk_dtex );
ER		ras_tex( ID tskid, TEXPTN rasptn );
ER		iras_tex( ID tskid, TEXPTN rasptn );
ER		dis_tex( void );
ER		ena_tex( void );
INT		sns_tex( void );
ER		ref_tex( ID tskid, T_RTEX *pk_rtex );

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
	ATR			sematr;				//!< �Z�}�t�H�̑���.
	UINT		isemcnt;			//!< �Z�}�t�H�̏����l.
	UINT		maxsem; 			//!< �Z�}�t�H�̍ő�l.
} T_CSEM;

/*!
 *
 * @brief �Z�}�t�H��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			wtskid;				//!< �Z�}�t�H�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	UINT		semcnt;				//!< ���݂̃Z�}�t�H�J�E���g�l.
} T_RSEM;

// �T�[�r�X�R�[���̒�`.
ER		cre_sem( ID semid, const T_CSEM *pk_csem );
ER_ID	acre_sem( const T_CSEM *pk_csem );
ER		del_sem( ID semid );
ER		sig_sem( ID semid );
ER		isig_sem( ID semid );
ER		wai_sem( ID semid );
ER		pol_sem( ID semid );
ER		twai_sem( ID semid, TMO tmout );
ER		ref_sem( ID semid, T_RSEM *pk_rsem );

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
	ATR			flgatr;				//!< �C�x���g�t���O�̑���.
	FLGPTN		iflgptn;			//!< �C�x���g�t���O�̏����l.
} T_CFLG;

/*!
 *
 * @brief �C�x���g�t���O��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			wtskid;				//!< �C�x���g�t���O�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	FLGPTN		flgptn;				//!< �C�x���g�t���O�̃r�b�g�p�^�[��.
} T_RFLG;

/*!
 *
 * @brief �C�x���g�t���O����(flgatr).
 *
 */
#define TA_WSGL 	0x0000			//!< �����^�X�N�̑҂��������Ȃ�.
#define TA_WMUL 	0x0002			//!< �����^�X�N�̑҂�������.
#define	TA_CLR		0x0004			//!< �t���O�p�^�[���̃N���A.

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
ER_ID	acre_flg( const T_CFLG *pk_cflg );
ER		del_flg( ID flgid );
ER		set_flg( ID flgid, FLGPTN setptn );
ER		iset_flg( ID flgid, FLGPTN setptn );
ER		clr_flg( ID flgid, FLGPTN clrptn );
ER		wai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn );
ER		pol_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn );
ER		twai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout );
ER		ref_flg( ID flgid, T_RFLG *pk_rflg );

/****************************************************************************
 *
 * ������ʐM�@�\ (�f�[�^�L���[).
 *
 ****************************************************************************/
/*!
 *
 * @brief �f�[�^�L���[�������\����.
 *
 */
typedef struct {
	ATR			dtqatr;				//!< �f�[�^�L���[�̑���.
	UINT		dtqcnt;				//!< �f�[�^�L���[�̈�̌�.
	VP			dtq;				//!< �f�[�^�L���[�̈�̐擪�A�h���X.
} T_CDTQ;

/*!
 *
 * @brief �f�[�^�L���[��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			stskid;				//!< �f�[�^�L���[�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	ID 			rtskid;				//!< �f�[�^�L���[�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	UINT		sdtqcnt;			//!< �f�[�^�L���[�ɓ����Ă���f�[�^��.
} T_RDTQ;

// �T�[�r�X�R�[���̒�`.
ER		cre_dtq( ID dtqid, const T_CDTQ *pk_cdtq );
ER_ID	acre_dtq( const T_CDTQ *pk_cdtq );
ER		del_dtq( ID dtqid );
ER		snd_dtq( ID dtqid, VP_INT data );
ER		psnd_dtq( ID dtqid, VP_INT data );
ER		ipsnd_dtq( ID dtqid, VP_INT data );
ER		tsnd_dtq( ID dtqid, VP_INT data, TMO tmout );
ER		fsnd_dtq( ID dtqid, VP_INT data );
ER		ifsnd_dtq( ID dtqid, VP_INT data );
ER		rcv_dtq( ID dtqid, VP_INT *p_data );
ER		prcv_dtq( ID dtqid, VP_INT *p_data );
ER		trcv_dtq( ID dtqid, VP_INT *p_data, TMO tmout );
ER		ref_dtq( ID dtqid, T_RDTQ *pk_rdtq );

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

typedef struct
{
	T_MSG   nextmsg;     /* message header */
	PRI     msgpri;     /* message priority */
} T_MSG_PRI;
	
/*!
 *
 * @brief ���[���{�b�N�X�������\����.
 *
 */
typedef struct {
	ATR			mbxatr;				//!< ���[���{�b�N�X�̑���.
	PRI			maxmpri;			//!< ���M����郁�b�Z�[�W�D��x�̍ő�l.
	VP			mprihd;				//!< �D��x�ʂ̃��b�Z�[�W�L���[�w�b�_�̈�̃A�h���X.
} T_CMBX;

/*!
 *
 * @brief ���[���{�b�N�X��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			wtskid;				//!< ���[���{�b�N�X�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	T_MSG		*pk_msg;			//!< ���b�Z�[�W�L���[�̐擪�̃��b�Z�[�W�p�P�b�g�̃A�h���X.
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
ER_ID	acre_mbx( const T_CMBX *pk_cmbx );
ER		del_mbx( ID mbxid );
ER		snd_msg( ID mbxid, T_MSG *pk_msg );
ER		rcv_msg( ID mbxid, T_MSG **ppk_msg );
ER		prcv_msg( ID mbxid, T_MSG **ppk_msg );
ER		trcv_msg( ID mbxid, T_MSG **ppk_msg, TMO tmout );
ER		ref_mbx( ID mbxid, T_RMBX *pk_rmbx );
#define prcv_mbx	prcv_msg

/****************************************************************************
 *
 * �g��������ʐM�@�\ (�~���[�e�b�N�X).
 *
 ****************************************************************************/
/*!
 *
 * @brief �~���[�e�b�N�X�������\����.
 *
 */
typedef struct {
	ATR			mtxatr; 			//!< �~���[�e�b�N�X�̑���.
	PRI			ceilpri;			//!< �~���[�e�b�N�X�̏���D��x.
} T_CMTX;

/*!
 *
 * @brief �~���[�e�b�N�X��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID			htskid;				//!< �~���[�e�b�N�X�����b�N���Ă���^�X�N��ID�ԍ�.
	ID			wtskid;				//!< �~���[�e�b�N�X�҂��s��̐擪�̃^�X�NID�ԍ�.
} T_RMTX;

#define	TA_INHERIT		0x02		//!< �D��x�p���v���g�R��.
#define	TA_CEILING		0x03		//!< ����D��x�v���g�R��.

// �T�[�r�X�R�[���̒�`.
ER		cre_mtx( ID mtxid, const T_CMTX *pk_cmtx );
ER_ID	acre_mtx( const T_CMTX *pk_cmtx );
ER		del_mtx( ID mtxid );
ER		loc_mtx( ID mtxid );
ER		ploc_mtx( ID mtxid );
ER		tloc_mtx( ID mtxid, TMO tmout );
ER		unl_mtx( ID mtxid );
ER		ref_mtx( ID mtxid, T_RMTX *pk_rmtx );

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
	ATR				mbfatr; 		//!< ���b�Z�[�W�o�b�t�@�̑���.
	UINT			maxmsz; 		//!< ���b�Z�[�W�̍ő�T�C�Y.
	/*SIZE*/ UINT	mbfsz;			//!< ���b�Z�[�W�o�b�t�@�̈�̃T�C�Y.
	VP				mbf;			//!< ���b�Z�[�W�o�b�t�@�̈�̃A�h���X.
} T_CMBF;

/*!
 *
 * @brief ���b�Z�[�W�o�b�t�@��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			stskid;				//!< ���b�Z�[�W�o�b�t�@�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	ID 			rtskid;				//!< ���b�Z�[�W�o�b�t�@�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			smsgcnt;			//!< ���b�Z�[�W�o�b�t�@�ɓ����Ă��郁�b�Z�[�W�̐�.
	INT			fmbfsz;				//!< ���b�Z�[�W�o�b�t�@�̋󂫗̈�̃T�C�Y.
} T_RMBF;

// �T�[�r�X�R�[���̒�`.
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf );
ER_ID	acre_mbf( const T_CMBF *pk_cmbf );
ER		del_mbf( ID mbfid );
ER		snd_mbf( ID mbfid, VP msg, UINT msgsz );
ER		psnd_mbf( ID mbfid, VP msg, UINT msgsz );
ER		tsnd_mbf( ID mbfid, VP msg, UINT msgsz, TMO tmout );
ER_UINT	rcv_mbf( ID mbfid, VP msg );
ER_UINT	prcv_mbf( ID mbfid, VP msg );
ER_UINT	trcv_mbf( ID mbfid, VP msg, TMO tmout );
ER		ref_mbf( ID mbfid, T_RMBF *pk_rmbf );

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
	ATR			poratr; 			//!< �����f�u�|�[�g�̑���.
	UINT		maxcmsz;			//!< �ďo���̃��b�Z�[�W�̍ő咷.
	UINT		maxrmsz;			//!< �ԓ����̃��b�Z�[�W�̍ő咷.
} T_CPOR;

/*!
 *
 * @brief �����f�u�|�[�g��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			ctskid;				//!< �����f�u�|�[�g�̌ďo�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	ID 			atskid;				//!< �����f�u�|�[�g�̎�t�҂��s��̐擪�̃^�X�N��ID�ԍ�.
} T_RPOR;

/*!
 *
 * @brief �����f�u��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			wtskid;				//!< �����f�u�I���҂���Ԃ̃^�X�N��ID�ԍ�.
} T_RRDV;

// �T�[�r�X�R�[���̒�`.
ER		cre_por( ID porid, const T_CPOR *pk_cpor );
ER_ID	acre_por( const T_CPOR *pk_cpor );
ER		del_por( ID porid );
ER_UINT	cal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz );
ER_UINT	tcal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz, TMO tmout );
ER_UINT	acp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg );
ER_UINT	pacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg );
ER_UINT	tacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg, TMO tmout );
ER		fwd_por( ID porid, RDVPTN calptn, RDVNO rdvno, VP msg, UINT cmsgsz );
ER		rpl_rdv( RDVNO rdvno, VP msg, UINT cmsgsz );
ER		ref_por( ID porid, T_RPOR *pk_rpor );
ER		ref_rdv( RDVNO rdvno, T_RRDV *pk_rrdv );

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
	ATR			mpfatr; 			//!< �Œ蒷�������v�[���̑���.
	UINT		blkcnt; 			//!< �m�ۂł��郁�����u���b�N��.
	UINT		blfsz;				//!< �������u���b�N�̃T�C�Y.
	VP			mpf;				//!< �Œ蒷�������v�[���̈�̃A�h���X.
} T_CMPF;

/*!
 *
 * @brief �Œ蒷�������v�[����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	ID 			wtskid;				//!< �Œ蒷�������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ�.
	UINT		fblkcnt; 			//!< �󂫃u���b�N�̌�.
} T_RMPF;

// �T�[�r�X�R�[���̒�`.
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf );
ER_ID	acre_mpf( const T_CMPF *pk_cmpf );
ER		del_mpf( ID mpfid );
ER		get_blf(ID mpfid, VP *p_blf );
ER		pget_blf(ID mpfid, VP *p_blf );
ER		tget_blf(ID mpfid, VP *p_blf, TMO tmout );
ER		rel_blf( ID mpfid, VP blk );
ER		ref_mpf( ID mpfid, T_RMPF *pk_rmpf );

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
	ATR				mplatr; 		//!< �ϒ��������v�[������.
	INT	/*SIZE*/	mplsz;			//!< �ϒ��������v�[���̃T�C�Y.
	VP				mpl;			//!< �ϒ��������v�[���̈�̃A�h���X.
} T_CMPL; 

/*!
 *
 * @brief �ϒ��������v�[����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct
{
	ID 				wtskid;			//!< �ϒ��������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT	/*SIZE*/	fmplsz;			//!< �ϒ��������v�[���̋󂫗̈�̍��v�T�C�Y.
	UINT			fblksz;			//!< �l���\�ȍő�̘A���󂫗̈�̃T�C�Y.
} T_RMPL; 


// �T�[�r�X�R�[���̒�`.
ER		cre_mpl( ID mplid , const T_CMPL *pk_cmpl );
ER		acre_mpl( const T_CMPL *pk_cmpl );
ER		del_mpl( ID mplid );
ER		get_mpl( ID mplid, UINT blksz, VP *p_blk );
ER		pget_mpl( ID mplid, UINT blksz, VP *p_blk );
ER		tget_mpl( ID mplid, UINT blksz, VP *p_blk, TMO tmout );
ER		rel_mpl( ID mplid, VP blk);
ER		rel_blk( ID mpfid, VP blk );
ER		ref_mpl( ID mplid, T_RMPL *pk_rmpl );

ER		iloc_cpu(void);
ER		iunl_cpu(void);

/****************************************************************************
 *
 * ���ԊǗ��@�\.
 *
 ****************************************************************************/

// �T�[�r�X�R�[���̒�`.
ER		set_tim( const SYSTIME *pk_tim );
ER		get_tim( SYSTIME *pk_tim );
ER		isig_tim( void );

#define	ret_tmr()	return;

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
	ATR			cycatr; 			//!< �����n���h������.
	VP_INT		exinf;				//!< �g�����.
	FP			cychdr;				//!< �����n���h���̃A�h���X.
	RELTIM		cyctim; 			//!< �����N�����ԊԊu.
	RELTIM		cycphs; 			//!< �����N���ʑ�.
} T_CCYC;

/*!
 *
 * @brief �����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	STAT		cycstat;			//!< �����n���h���̓�����.
	RELTIM		lefttim; 			//!< ���̋N�������܂ł̎���.
} T_RCYC;

/*!
 *
 * @brief �����n���h���̓�����(cycstat).
 *
 */
#define	TCYC_STP		0x00		//!< �����n���h�������삵�Ă��Ȃ�.
#define	TCYC_STA		0x01		//!< �����n���h�������삵�Ă���.

#define	TA_STA			0x02		//!< �����n���h�����N��.
#define	TA_PHS			0x04		//!< �����n���h���̋N���ʑ�����.

// �T�[�r�X�R�[���̒�`.
ER		cre_cyc( ID cycid, const T_CCYC *pk_ccyc );
ER		acre_cyc( const T_CCYC *pk_ccyc );
ER		del_cyc( ID cycid );
ER		sta_cyc( ID cycid );
ER		stp_cyc( ID cycid );
ER		ref_cyc( ID cycid, T_RCYC *pk_rcyc );

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
	ATR			almatr; 			//!< �A���[����n���h������.
	VP_INT		exinf;				//!< �g�����.
	FP			almhdr;				//!< �A���[����n���h���̃A�h���X.
} T_CALM;

/*!
 *
 * @brief �A���[����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	STAT		almstat;			//!< �A���[����n���h���̓�����.
	RELTIM		lefttim; 			//!< �A���[����n���h���̋N�������܂ł̎���.
} T_RALM;

/*!
 *
 * @brief �N�������w�胂�[�h(tmmode).
 *
 */
#define TTM_ABS 	0x0000			//!< ��Ύ����ł̎w��.
#define TTM_REL 	0x0001			//!< ���Ύ����ł̎w��.

/*!
 *
 * @brief �A���[����n���h���̓�����(almstat).
 *
 */
#define	TALM_STP		0x00		//!< �A���[����n���h�������삵�Ă��Ȃ�.
#define	TALM_STA		0x01		//!< �A���[����n���h�������삵�Ă���.

// �T�[�r�X�R�[���̒�`.
ER		cre_alm( ID almid, const T_CALM *pk_calm );
ER_ID	acre_alm( const T_CALM *pk_calm );
ER		del_alm( ID almid );
ER		sta_alm( ID almid, RELTIM almtim );
ER		stp_alm( ID almid );
ER		ref_alm( ID almid, T_RALM *pk_ralm );

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
	ATR			inhatr; 			//!< �����݃n���h������.
	FP			inthdr;				//!< �����݃n���h���A�h���X.
} T_DINH;

// �T�[�r�X�R�[���̒�`.
ER		def_inh( INTNO intno, const T_DINH *pk_dinh );
ER		dis_int( INTNO intno );
ER		ena_int( INTNO intno );
ER		loc_cpu( void );
ER		unl_cpu( void );

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
	unsigned short	maker;			//!< ���[�J�[.
	unsigned short	prid;			//!< �J�[�l���̎��ʔԍ�.
	unsigned short	spver;			//!< �d�l���o�[�W����.
	unsigned short	prver;			//!< �J�[�l���̃o�[�W�����ԍ�.
	unsigned short	prno[4];		//!< ���i�Ǘ����.
} T_RVER;

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
ER		get_ver( T_RVER *pk_rver );
ER		ref_cfg( T_RCFG *pk_rcfg );

#ifdef __cplusplus
}
#endif
#endif	// __WIN_ITRON4_H__
/* End of file */
