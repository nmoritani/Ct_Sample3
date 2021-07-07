#include "wi_platform.h"
#include "pthread.h"

#ifdef WIN32_GUI_SIM

/////////////////////////////////////////////////////////////////////////
#include "pthread_initialize.h"
ER wi_init()
{
	init_pthread_lib();
	return E_OK;
}


/////////////////////////////////////////////////////////////////////////
#include "pthread_thread.h"

ER wi_cre_tsk(ID tskid, const T_CTSK *pk_ctsk)
{
	thread_arg arg;
	arg.tskatr = pk_ctsk->tskatr;
	arg.exinf = pk_ctsk->exinf;
	arg.task = PTHREAD_START_FUNC_CAST(pk_ctsk->task);
	arg.itskpri = pk_ctsk->itskpri;
	arg.stksz = pk_ctsk->stksz;
	arg.stk = pk_ctsk->stk;
	return create_thread(tskid, &arg);
}

ER	wi_dly_tsk(DLYTIME dlytim)
{
	return thread_delay(dlytim);
}

ER	wi_act_tsk(ID tskid)
{
	return thread_active(tskid);
}

ER	wi_sta_tsk(ID tskid, VP_INT stacd)
{
	return thread_start(tskid, (unsigned int)stacd);
}

ER	wi_del_tsk(ID tskid)
{
	return delete_thread(tskid);
}

//�I�������p�Ȃ̂Ō��
ER wi_ref_tsk(ID tskid, T_RTSK * pk_rtsk)
{
	return E_OK;
}

ER	wi_get_tid(ID *p_tskid)
{
	return get_thread_id(p_tskid);
}

/////////////////////////////////////////////////////////////////////////
#include "pthread_variable_mempool.h"

ER	wi_cre_mpl(ID mplid, const T_CMPL *pk_cmpl)
{
	return	E_OK;
}

ER	wi_tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout)
{
	return	get_variable_mempool(mplid, blksz, p_blk);
}

ER	wi_rel_mpl(ID mplid, VP blk)
{
	return	free_variable_mempool(mplid, blk);
}

ER	wi_del_mpl(ID mplid)
{
	return	E_OK;
}

//�g���Ă��Ȃ��̂Ō��
ER	wi_ref_mpl(ID mpfid, T_RMPL *pk_rmpl)
{
	return	E_OK;
}


/////////////////////////////////////////////////////////////////////////
#include "pthread_cycle_handler.h"

ER	wi_cre_cyc(ID cycid, const T_CCYC *pk_ccyc)
{
	cycle_time_arg arg;
	arg.attr = pk_ccyc->cycatr;
	arg.cycle_time = ((DWORDLONG)(pk_ccyc->cyctim.utime) << 32) + (DWORDLONG)(pk_ccyc->cyctim.ltime);
	arg.func = pk_ccyc->cychdr;

	return create_cycle_handler(cycid, &arg);
}

ER	wi_stp_cyc(ID cycid)
{
	return	stop_cycle_handler(cycid);
}


ER	wi_del_cyc(ID cycid)
{
	return	delete_cycle_handler(cycid);
}

ER	wi_sta_cyc(ID cycid)
{
	return	start_cycle_handler(cycid);
}

ER	wi_ref_cyc(ID cycid, T_RCYC *pk_rcyc)
{
	cycle_handler_state state;

	int errcode = reference_cycle_handler(cycid, &state);

	if (E_OK == errcode) {
		pk_rcyc->cycstat = (state.active) ? TCYC_STA : TCYC_STP;
		pk_rcyc->lefttim.ltime = state.remain_time;
	}

	return errcode;	
}


///////////////////////////////////////////////////////////////////////////
//mem_mng�p
//CPU���b�N��Ԃւ̈ڍs
ER	wi_loc_cpu(void)
{
	return	E_OK;
}

ER	wi_iloc_cpu(void)
{
	return	E_OK;
}

ER	wi_unl_cpu(void)
{
	return	E_OK;
}

ER	wi_iunl_cpu(void)
{
	return	E_OK;
}

///////////////////////////////////////////////////////////////////////////
//�V�~�����[�^�I���p�̃R�[���Ȃ̂Ō��

ER wi_rel_wai(ID tskid)
{
	return E_OK;
}

ER	wi_irel_wai(ID tskid)
{
	return	E_OK;
}



/////////////////////////////////////////////////////////////////////////
#include "pthread_semaphore.h"
//�Z�}�t�H�̐���
ER	wi_cre_sem(ID semid, const T_CSEM *pk_csem)
{
	/* pk_csem�͖��g�p */
	return create_semaphore(semid);
}

//�Z�}�t�H�̍폜
ER	wi_del_sem(ID semid)
{
	return	delete_semaphore(semid);
}

//�Z�}�t�H�����̕ԋp
ER	wi_sig_sem(ID semid)
{
	return signal_semaphore(semid);
}

//�Z�}�t�H�����̊l��
ER	wi_wai_sem(ID semid)
{
	return wait_semaphore(semid);
}

//�Z�}�t�H�����̊l�� (�|�[�����O)
ER	wi_pol_sem(ID semid)
{
	return	E_OK;
}


/////////////////////////////////////////////////////////////////////////
#include "pthread_event_flag.h"

//�C�x���g�t���O�̐���
ER	wi_cre_flg(ID flgid, const T_CFLG *pk_cflg)
{
	return pthread_create_eventflag(flgid, pk_cflg->flgatr, pk_cflg->iflgptn);
}

//�C�x���g�t���O�̍폜
ER	wi_del_flg(ID flgid)
{
	return	pthread_delete_eventflag(flgid);
}

//�C�x���g�t���O�̃Z�b�g
ER	wi_set_flg(ID flgid, FLGPTN setptn)
{
	return pthread_event_set_flag(flgid, setptn);
}

//�C�x���g�t���O�̃Z�b�g (��^�X�N�R���e�L�X�g����̌ďo���p)
ER	wi_iset_flg(ID flgid, FLGPTN setptn)
{
	return pthread_event_set_flag(flgid, setptn);
}

//�C�x���g�t���O�҂� (�^�C���A�E�g�Ȃ�)
ER	wi_wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	return	pthread_event_wait_flag(flgid, waiptn, wfmode, p_flgptn);
}

//�C�x���g�t���O�҂� (�^�C���A�E�g����)
ER	wi_twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout)
{
	return	pthread_event_t_wait_flag(flgid, waiptn, wfmode, p_flgptn, tmout);
}
//�C�x���g�t���O�̃N���A
ER	wi_clr_flg(ID flgid, FLGPTN clrptn)
{
	return	pthread_event_clear_flag(flgid, clrptn);
}

/////////////////////////////////////////////////////////////////////////
#include "pthread_messagebox.h"

ER	wi_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx)
{
	/* ��2������pk_cmbx�͖��g�p */
	return create_mbox(mbxid);
}

//���[���{�b�N�X�폜
ER	wi_del_mbx(ID mbxid)
{
	return delete_mbox(mbxid);
}

//���[���{�b�N�X���M
ER	wi_snd_msg(ID mbxid, T_MSG *pk_msg)
{
	return send_message(mbxid, pk_msg);
}

//���[���{�b�N�X���M
ER	wi_snd_mbx(ID mbxid, T_MSG *pk_msg)
{
	return send_message(mbxid, pk_msg);
}

//���[���{�b�N�X��M
ER	wi_rcv_msg(ID mbxid, T_MSG **ppk_msg)
{
	return receive_message(mbxid, (void**)ppk_msg);
}

//���[���{�b�N�X��M
ER	wi_rcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	return receive_message(mbxid, (void**)ppk_msg);
}

//���[���{�b�N�X��M(�|�[�����O)
ER	wi_prcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	return p_receive_message(mbxid, (void**)ppk_msg);
}

//���[���{�b�N�X��M(�^�C���A�E�g����)
ER	wi_trcv_msg(ID mbxid, T_MSG **ppk_msg, TMO tmout)
{
	return t_receive_message(mbxid, (void**)ppk_msg, tmout);
}

//	���[���{�b�N�X�̏�ԎQ��.
ER	wi_ref_mbx(ID mbxid, T_RMBX *pk_rmbx)
{
	pk_rmbx->pk_msg = NULL;
	pk_rmbx->wtskid = 0;

	return	E_OK;
}

ER wi_cycle_timer(ID id, const T_CTSK * pk_ctsk)
{
	thread_arg arg;
	arg.tskatr = pk_ctsk->tskatr;
	arg.exinf = pk_ctsk->exinf;
	arg.task = PTHREAD_START_FUNC_CAST(pk_ctsk->task);
	arg.itskpri = pk_ctsk->itskpri;
	arg.stksz = pk_ctsk->stksz;
	arg.stk = pk_ctsk->stk;
	return create_cycle_timer_thread(id, &arg);
}

void wi_cycle_thread()
{
	cycle_thread();
}

/////////////////////////////////////////////////////////////////////////






#endif




//sns_ctx();

