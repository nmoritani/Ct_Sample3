/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
 /*!
  *	@file	win_itron_main.c
  *
  *	@brief	Windows�� iTRON�T�[�r�X�R�[���̃��C�����[�`��.
  *
  *	@author	���V �閾
  */

#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "kprintf.h"
#include "win_itron.h"
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_mail_box.h"
#include "wi_message_buffer.h"
#include "wi_rendezvous_port.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"
#include "wi_cycle_handler.h"
#include "wi_alarm_handler.h"
#include "wi_interrupt.h"
#include "wi_systemmgr.h"
#include "wi_resource.h"
#include "kernel_id.h"
#include "VMI.h"
#include "gdi_draw_test.h"
#include "gdi_config.h"
#include "WinDrawTask.h"



  /****************************************************************************
   *
   * �V�X�e���Ǘ��X���b�h�ւ̃��b�Z�[�W.
   *
   ****************************************************************************/
#define	WM_SYSTEM_EXIT	(WM_USER + 1)		//!< �V�X�e���̏I��.
#define	WM_DELETE_TASK	(WM_USER + 2)		//!< �^�X�N�̍폜.

   /****************************************************************************
	*
	* ���[�J���֐���`.
	*
	****************************************************************************/
static BOOL			WinITRON_Init(void);
static void			WinITRON_Quit(void);
static unsigned int __stdcall SystemTask(void* arg);
static TASK			InitTask(VP_INT stacd);

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static HANDLE	SystemThread = NULL;		//!< �V�X�e���Ǘ��X���b�h�̃n���h��.
static DWORD	ThreadId = 0;			//!< �V�X�e���Ǘ��X���b�h�̎��ʎq.


/****************************************************************************/
/*!
 *	@brief	iTRON�T�[�r�X�R�[���̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL		WinITRON_Init(void)
{
	unsigned int tid;

	//! �V�X�e���Ǘ��X���b�h���N������.
	SystemThread = (HANDLE)_beginthreadex(NULL, 0, &SystemTask, NULL, 0, &tid);

	//! �^�X�N�̗D��x��ݒ肷��.
	SetThreadPriority(SystemThread, THREAD_PRIORITY_HIGHEST);

	//! �v���Z�X�̗D�揇�ʃN���X��ʏ�̃A�v���P�[�V������菭���Ⴍ����.
	if (!SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS)) {
		return FALSE;
	}
	//! �V�X�e����ԊǗ��@�\�̏�������.
	wi_InitSysMgr();

	//	//! ���荞�݋@�\�̏�������.
	//	wi_InitInterrupt();

	//! ���ʊ֐��̏�������.
	if (!wi_CommonInit()) {
		return FALSE;
	}
	//! ���荞�݋@�\�̏�������.
	wi_InitInterrupt();

	//! �^�X�N�Ǘ��̏�������.
	wi_InitTask();

	//! �Z�}�t�H�̏�������.
	wi_InitSemaphore();

	//! �C�x���g�t���O�̏�������.
	wi_InitEvFlag();

	//! ���[���{�b�N�X�̏�������.
	wi_InitMailBox();

	//! ���b�Z�[�W��o�b�t�@�̏�������.
	wi_InitMsgBuffer();

	//! �Œ蒷�������v�[���̏�������.
	wi_InitFixedMemPool();

	//! �ϒ��������v�[���̏�������.
	wi_InitVarMemPool();

	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	iTRON�T�[�r�X�R�[���̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
static void		WinITRON_Quit(void)
{
	//! �V�X�e���Ǘ��X���b�h���I��������.
	if (SystemThread) {
		//! - �V�X�e���Ǘ��X���b�h�ɏI����ʒm����.
		PostThreadMessage(ThreadId, WM_SYSTEM_EXIT, 0, 0);

		//! - �X���b�h����~����̂��m�F����.
		wi_DormantThread(SystemThread, 1000);

		//! - �V�X�e���Ǘ��X���b�h�̃n���h�����������.
		CloseHandle(SystemThread);
	}
	//! �V�X�e����ԊǗ��@�\�̏I������.
	wi_QuitSysMgr();

	//! ���荞�݋@�\�̏I������.
	wi_QuitInterrupt();

	//! �^�X�N�Ǘ��̏I������.
	wi_QuitTask();

	//! �Z�}�t�H�̏I������.
	wi_QuitSemaphore();

	//! �C�x���g�t���O�̏I������.
	wi_QuitEvFlag();

	//! ���[���{�b�N�X�̏I������.
	wi_QuitMailBox();

	//! ���b�Z�[�W��o�b�t�@�̏I������.
	wi_QuitMsgBuffer();

	//! �Œ蒷�������v�[���̏I������.
	wi_QuitFixedMemPool();

	//! �ϒ��������v�[���̏I������.
	wi_QuitVarMemPool();

	//! ���ʊ֐��̏I������.
	wi_CommonQuit();
}

/****************************************************************************/
/*!
 *	@brief	���[�U�[��A�v���P�[�V�����̋N���^�X�N.
 *
 *	@param	[in]	stacd	�^�X�N�̋N���R�[�h.
 *
 *	@retval	�Ȃ�.
 */

static TASK	SimulatorTask(VP_INT stacd)
{
	//! ���[�U�[��A�v���P�[�V�����̋N��.
	SimulatorWindowDraw();
	exd_tsk();
}


/****************************************************************************/
/*!
 *	@brief	���荞�݂𔭐�������.
 *
 *	@param	[in]	num		���荞�݃n���h���ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	request_interrupt(UINT num)
{
	wi_IntrruptRequest(num);
}

/****************************************************************************/
/*!
 *	@brief	���荞�ݗv�����N���A����.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	clear_interrupt_request(UINT num)
{
	wi_ClearIntrruptRequest(num);
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e���Ǘ��^�X�N�Ƀ^�X�N����\�[�X�̍폜��v������.
 *
 *	@param	[in]	id		�^�X�NID���ʎq.
 *
 *	@retval	�Ȃ�.
 */
void	wi_DeleteTaskReq(ID id)
{
	if (ThreadId) {
		PostThreadMessage(ThreadId, WM_DELETE_TASK, (WPARAM)id, 0);
	}
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e���Ǘ��^�X�N.
 *
 *	@param	[in]	arg		�^�X�N���\�[�X�\���̂̃|�C���^.
 *
 *	@retval	���0��Ԃ�.
 */
static unsigned __stdcall SystemTask(void* arg)
{
	MSG	msg;

	//! �X���b�h���ʎq���擾����.
	ThreadId = GetCurrentThreadId();

	//! ���b�Z�[�W���[�v.
	while (GetMessage(&msg, NULL, 0, 0)) {

		//! �V�X�e���̏I���̏ꍇ�̓��b�Z�[�W���[�v�𔲂���.
		if (msg.message == WM_SYSTEM_EXIT) {
			break;
		}
		switch (msg.message) {
		case WM_DELETE_TASK:
			del_tsk((ID)msg.wParam);
			break;
		}
	}
	_endthreadex(0);
	return 0;
}

/****************************************************************************/
extern void Ct_MainTask();
extern void Ct_DrawTask();
extern void Ct_DbgTask();
extern void CtCycHandler(VP_INT exinf);
extern void AvdfCycHandler(VP_INT exinf);
extern void GUI_TsTask();


#include "gdi_config.h"

BOOL ITRON_Init(void)
{
#ifdef __ITRON3__
	static const T_CTSK	ctsk = { NULL, TA_HLNG, InitTask, 1, 0 };
#else
	static const T_CTSK	ctsk = { TA_HLNG, NULL, SimulatorTask, 100, 0, NULL };
	static const T_CTSK ct_main_task = { TA_HLNG, 0, Ct_MainTask, 50, 0x4000, 0 };
	static const T_CTSK ct_draw_task = { TA_HLNG, 0, Ct_DrawTask, 40, 0x2000, 0 };
	static const T_CTSK ct_dbg_task = { TA_HLNG, 0, Ct_DbgTask, 60, 0x2000, 0 };
	static const T_CTSK gui_ts_task = { TA_HLNG, 0, GUI_TsTask, 99, 0x4000, 0 };

	static const T_CMPL ct_mpl = { TA_TFIFO, 0x80000*4, NULL };
	static const T_CMPL ct_fastmpl = { TA_TFIFO, 0x20000, NULL };
	static const T_CMPL gfxres_mpl = { TA_TFIFO, GFX_RES_SIZE, GUI_WORK_START };
	static const T_CMPL guiwork_mpl = { TA_TFIFO, GUI_WORK_SIZE, GFX_RES_START };
	static const T_CMPL gui_ts_mpl = { TA_TFIFO, 0x2000, NULL };

	static const T_CMBX ct_main_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX ct_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX win_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };				//WINDOWS�A�v�����̃E�B���h�E�`��X�V�p
	static const T_CMBX ct_dbg_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };

	static const T_CDTQ gui_ts_dtq = { TA_TFIFO, 10, NULL };

	static const T_CSEM ct_sem_receiver = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_object = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_synchro = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_gdi 		= {TA_TFIFO, 1, 1};
	static const T_CSEM gdi_sem_fontapi = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_draw = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_create_cache = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_context = { TA_TFIFO, 1, 1 };

	static const T_CCYC ct_cyc = { TA_HLNG, 0, CtCycHandler,{ 0, 10 }, 0 };
	static const T_CCYC avdf_cyc = { TA_HLNG | TA_STA, 0, AvdfCycHandler, {0, 14}, 0 };	// �^��AVDF�^�X�N (�{����16.6ms��������16�ɂ���Ɠ��������16,32�ƃo��������14�ɐݒ�)

	// Flag definition
	static const T_CFLG ct_flg_main = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_draw = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_synchro = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_dbg = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG gui_ts_flgid = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
#endif

	//! iTRON�T�[�r�X�R�[���̏�������.
	if (WinITRON_Init()) {
		//! �A�v���P�[�V�����̋N���^�X�N�𐶐�����.
		cre_tsk(TSKID_WINITRON, &ctsk);

		// �������v�[������
		cre_mpl(CT_MPL_ID, &ct_mpl);
		cre_mpl(CT_FASTMPL_ID, &ct_fastmpl);
		cre_mpl(GFX_RESMPL_ID, &gfxres_mpl);
    cre_mpl(FONT_LIBMPL_ID, &gfxres_mpl);
		cre_mpl(GUI_WORKMPL_ID, &guiwork_mpl);
		cre_mpl(GUI_TS_MPLID, &gui_ts_mpl);

		// �^�X�N����
		cre_tsk(CT_MAIN_TSKID, &ct_main_task);
		cre_tsk(CT_DRAW_TSKID, &ct_draw_task);
		cre_tsk(CT_DBG_TSKID, &ct_dbg_task);
		cre_tsk(GUI_TS_TSKID, &gui_ts_task);

		// ���[���{�b�N�X����
		cre_mbx(CT_MBXID_MAIN, &ct_main_mbx);
		cre_mbx(CT_MBXID_DRAW, &ct_draw_mbx);
		cre_mbx(MBXID_WIN_DRAW_TASK, &win_draw_mbx);
		cre_mbx(CT_MBXID_DBG, &ct_dbg_mbx);

		// �f�[�^�L���[����
		cre_dtq(GUI_TS_DTQID, &gui_ts_dtq);

		// �Z�}�t�H ����
		cre_sem(CT_SEMID_RECEIVER, &ct_sem_receiver);
		cre_sem(CT_SEMID_OBJECT, &ct_sem_object);
		cre_sem(CT_SEMID_SYNCHRO, &ct_sem_synchro);
		cre_sem(CT_SEMID_GDI, &ct_sem_gdi);
		cre_sem(GDI_SEMID_FONTAPI, &gdi_sem_fontapi);
		cre_sem(GDI_SEMID_DRAW, &gdi_sem_draw);
		cre_sem(GDI_SEMID_CREATE_CACHE, &gdi_sem_create_cache);
		cre_sem(GDI_SEMID_CONTEXT, &gdi_sem_context);

		// Flag definition
		cre_flg(CT_FLGID_MAINTASK, &ct_flg_main);
		cre_flg(CT_FLGID_DRAWTASK, &ct_flg_draw);
		cre_flg(CT_FLGID_SYNCHRO, &ct_flg_synchro);
		cre_flg(CT_FLGID_DBGTASK, &ct_flg_dbg);
		cre_flg(GUI_TS_FLGID, &gui_ts_flgid);

		// Cyclic Handler
		cre_cyc(CT_CYC_ID, &ct_cyc); // For AplTimerService
		cre_cyc(AVDF_CYC_ID, &avdf_cyc);

		return TRUE;
	}
	return FALSE;
}


void ITRON_START(void)
{
	//! ���������^�X�N�����N������.
	sta_tsk(TSKID_WINITRON, 0);
}

void ITRON_Quit(void)
{
	//TODO:�^�X�N����ĉ��ۂɗ�����̂ŁA�I���������ĂׂȂ��B�e�^�X�N�ɏI���ʒm���ĉ��K�v������
	WinITRON_Quit();
}

/* ��^�X�N���������iset_flg�Ăяo���p */
void ITRON_iset_flg(int flagid, UINT setptn)
{
	iset_flg(flagid, setptn);
}
/* End of file */
