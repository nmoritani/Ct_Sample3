#ifndef __CtDbgTskId_H__
#define __CtDbgTskId_H__

#include "kernel.h"

#ifdef WIN32_GUI_SIM
#include "win_itron.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif
    extern void Ct_DbgTask();

#ifndef WIN32_GUI_SIM
	static ID CT_DBG_TSKID;
    static ID CT_MBXID_DBG;
    //static ID CT_FLGID_DBGTASK = 116;
#endif

#ifndef WIN32_GUI_SIM
	const ID CT_DBG_TSKPRI = APL_MAIN_TSKPRI - 2;
#endif
BOOL static act_DbgTsk() {

#ifndef WIN32_GUI_SIM
	T_CTSK k_cDbgTsk = { TA_HLNG , 0, Ct_DbgTask, CT_DBG_TSKPRI, 0x2000, 0 };
	CT_DBG_TSKID = acre_tsk(&k_cDbgTsk);

	T_CMBX k_cmbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	CT_MBXID_DBG = acre_mbx(&k_cmbx);

	// FlgÇÃé©ìÆê∂ê¨ÇÕìÆçÏÇµÇ»Ç¢
	T_CFLG k_cDbgFlg = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	//CT_FLGID_DBGTASK = acre_flg(&k_cDbgFlg);
    //static T_CFLG ct_flg_dbg = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
    //cre_flg(CT_FLGID_DBGTASK, &ct_flg_dbg);
#else

#endif /*WIN32_GUI_SIM*/

	act_tsk(CT_DBG_TSKID);
	return TRUE;
}

#ifdef __cplusplus
}
#endif
#endif
