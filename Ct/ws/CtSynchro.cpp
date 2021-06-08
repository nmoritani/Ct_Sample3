/** ��������N���X
 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

//#include "CtClassID.h"
#include "CtSynchro.h"
//#include "CtConvertErrorItron.h"

extern "C" {	// @@@
#include <kernel_id.h>
//#include "CtDebug.h"
}



/***********************************
static member.
***********************************/
const FLGPTN	CtSynchro::ms_InvalidFlgPtn = 0;
const UW 		CtSynchro::ms_MaxBit = TBIT_FLGPTN;/* ITRON�d�l��16�ȏオ�ۏႳ��Ă��邪�A
													   32�����̏ꍇ�̓R���p�C���G���[������B */
const ID		CtSynchro::ms_Flg = CT_FLGID_SYNCHRO;		/* 1�̃C�x���g�t���O�œ����ł���̂�16�^�X�N�܂ŁB
													   16�ȏ�̃^�X�N�������҂�����K�v������΁A����
													   �����o�[��z��ɂ��āA�����̃C�x���g�t���O��
													   �����ł���B */
FLGPTN			CtSynchro::ms_FlgPtnMap = 0;

/** �C�x���g�t���O�̏�Ԃ�������
 * 
 * @param [out]	�C�x���g�t���O���
 */
void	CtSynchro::initFlgInfo( FlgInfo &info )
{
	info.flgptn = ms_InvalidFlgPtn;
	info.flg = -1;	/* �����ȏꍇ��flgptn�����Q�Ƃ���Ȃ��̂�
					   �K���Ȓl�����Ă��� */
}

/** �C�x���g�t���O�������蓖�Ă�
 * 
 * @retval �C�x���g�t���O���
 */
CtSynchro::FlgInfo	CtSynchro::allocFlgInfo()
{
	ER		ercd;
	FlgInfo	info;
	UW		bit;

	/* ���������� */
	initFlgInfo( info );

	/* ���g�p��bit��T�� */
	ercd = wai_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );
	for ( bit = 0; bit < ms_MaxBit; ++bit ) {
		if ( ( ms_FlgPtnMap & ( 1 << bit ) ) == 0 ) {
			info.flgptn = ( 1 << bit );
			info.flg = ms_Flg;
			ms_FlgPtnMap |= ( 1 << bit );
			break;
		}
	}
	ercd = sig_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );

	//Ct_ASSERT( isValidFlgInfo( info ) );

	return info;
}

/** �C�x���g�t���O�����������
 *
 * @retval Ct_E_OK		����
 * @retval Ct_E_OK�ȊO	���s
 */
bool CtSynchro::freeFlgInfo( const FlgInfo &info )
{
	bool bRet = false;
	ER	ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( info ) ) {
		goto failed0;
	}
	ercd = wai_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );
	ms_FlgPtnMap &= ~info.flgptn;
	ercd = sig_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );

	bRet = true;

failed0:
	return bRet;
}

/** �R���X�g���N�^ */
CtSynchro::CtSynchro() : m_FlgInfo( allocFlgInfo() )
{
	//Ct_SET_CLASSID(Ct_CLS_SYNCHRO);
	//Ct_ASSERT( isValidFlgInfo( m_FlgInfo ) );
}



/** �f�X�g���N�^ */
CtSynchro::~CtSynchro()
{
	freeFlgInfo( m_FlgInfo );
}


/***********************************
public member.
***********************************/
/** �����ʒm��҂�
 * 
 * @param [in]	tout	�^�C���A�E�g�i�P�ʁF�~���b�j
 * @retval Ct_E_OK		����
 * @retval Ct_E_OK�ȊO	���s
 */
bool CtSynchro::wait(W tout)
{
	bool bRet = false;
	FLGPTN	retptn;
	ER		ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		//Ct_ASSERT( 0 );
		goto failed0;
	}

	ercd = twai_flg( m_FlgInfo.flg, m_FlgInfo.flgptn, TWF_ANDW, &retptn, tout );
	if ( ercd != E_OK ) {
		if ( ercd == E_TMOUT ) {
			/* �^�C���A�E�g */
			goto failed0;
		}
		//Ct_ASSERT( 0 );
		goto failed0;
	}

	/* �����ɕ�����FS�^�X�N�������ꍇ �� ��ʃ^�X�N�̕����D��x��
	   �����ꍇ�́Aflgptn �� retptn ���قȂ鎖�͂��肤��B */
//	Ct_ASSERT( flgptn == retptn );

	ercd = clr_flg( m_FlgInfo.flg, ~m_FlgInfo.flgptn );
	if ( ercd != E_OK ) {
		goto failed0;
	}

	bRet = true;

failed0:
	return bRet;
}



/** �����ʒm���s��
 * 
 * @retval Ct_E_OK		����
 * @retval Ct_E_OK�ȊO	���s
 */
bool CtSynchro::notify()
{
	bool	bRet = false;
	ER		ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

#ifdef WIN32_GUI_SIM
	ercd = set_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
#else
	if ( sns_ctx() ) {
		ercd = iset_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
	}
	else {
		ercd = set_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
	}
#endif
	if ( ercd != E_OK ) {
		goto failed0;
	}

	bRet = true;

failed0:
	return bRet;
}


