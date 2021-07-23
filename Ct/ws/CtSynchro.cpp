/** ��������N���X
 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

#include "CtSynchro.h"
#include <CtPlatforms.h>

extern "C" {	// @@@
}



/***********************************
static member.
***********************************/
const unsigned int CtSynchro::ms_InvalidFlgPtn = 0;
const unsigned int CtSynchro::ms_MaxBit = 16;
unsigned int CtSynchro::ms_FlgPtnMap = 0;
syswrap_event_t CtSynchro::m_Event = {0};
syswrap_semaphore_t CtSynchro::m_Semaphore = {0};

void CtSynchro::init()
{
	syswrap_create_event(&m_Event, THREAD_ATTR_FIFO, 0);
	syswrap_create_semaphore(&m_Semaphore, 1, THREAD_ATTR_FIFO);	// binary semaphore�łȂ��ƕ`��noize�o�܂�
}

void CtSynchro::term()
{
	syswrap_destroy_semaphore(&m_Semaphore);
	syswrap_destroy_event(&m_Event);
}


/** �C�x���g�t���O�̏�Ԃ�������
 * 
 * @param [out]	�C�x���g�t���O���
 */
void	CtSynchro::initFlgInfo( FlgInfo &info )
{
	info.flgptn = ms_InvalidFlgPtn;
	info.flg = NULL;
}

/** �C�x���g�t���O�������蓖�Ă�
 * 
 * @retval �C�x���g�t���O���
 */
CtSynchro::FlgInfo	CtSynchro::allocFlgInfo()
{
	SYSWRAP_ERROR ercd;
	FlgInfo	info;
	unsigned int bit;

	/* ���������� */
	initFlgInfo( info );

	/* ���g�p��bit��T�� */
	ercd = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_FOREVER);
	for ( bit = 0; bit < ms_MaxBit; ++bit ) {
		if ( ( ms_FlgPtnMap & ( 1 << bit ) ) == 0 ) {
			info.flgptn = ( 1 << bit );
			info.flg = &m_Event;
			ms_FlgPtnMap |= ( 1 << bit );
			break;
		}
	}
	ercd = syswrap_post_semaphore(&m_Semaphore);

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
	SYSWRAP_ERROR ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( info ) ) {
		goto failed0;
	}
	ercd = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_FOREVER);
	ms_FlgPtnMap &= ~info.flgptn;
	ercd = syswrap_post_semaphore(&m_Semaphore);

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
bool CtSynchro::wait(long timeout)
{
	bool bRet = false;
	unsigned int retptn;
	SYSWRAP_ERROR ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

	ercd = syswrap_wait_event(m_FlgInfo.flg, m_FlgInfo.flgptn, SYSWRAP_WAITFMODE_ANDW, &retptn, timeout);
	if ( ercd != SYSWRAP_ERR_OK ) {
		if ( ercd == SYSWRAP_ERR_TIMEOUT ) {
			/* �^�C���A�E�g */
			goto failed0;
		}
		goto failed0;
	}

	/* �����ɕ�����FS�^�X�N�������ꍇ �� ��ʃ^�X�N�̕����D��x��
	   �����ꍇ�́Aflgptn �� retptn ���قȂ鎖�͂��肤��B */

	ercd = syswrap_clear_event(m_FlgInfo.flg, ~m_FlgInfo.flgptn);
	if ( ercd != SYSWRAP_ERR_OK ) {
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
	SYSWRAP_ERROR ercd;

	/* �L����FlgInfo���ǂ����m�F */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

	ercd = syswrap_set_event(m_FlgInfo.flg, m_FlgInfo.flgptn);
	if ( ercd != SYSWRAP_ERR_OK ) {
		goto failed0;
	}
	bRet = true;

failed0:
	return bRet;
}


