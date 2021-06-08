/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtRecViewModeCheck_H__
#define __CtRecViewModeCheck_H__

#include "Ct.h"
#include "CtWidget.h"
#include "CtWindowMain.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtRecView2.h"

#include "CtModeCheckAudio.h"
#include "CtModeCheckNetwork.h"
#include "CtModeCheckStatus.h"
#include "CtModeCheckSwitch.h"
#include "CtModeCheckFunction.h"

class CtRecViewModeCheck : public CtWindowMain
{
public:
	enum {
		CT_TIMER_ID_MODE_CHECK
	};
	CtRecViewModeCheck( CtWindowContents *pContents = NULL);
    virtual ~CtRecViewModeCheck();
	CtWindow* createWindow();
	virtual bool destroyWindow();

	bool handleTimerEvent(const CtEventTimer& Timer);
	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	virtual bool startupWindow();

private :
    CtWindow *m_pWin;
	CtLayout *m_pAll;
	CtStackLabel* m_pStkModeChk;

	CtModeCheckAudio* m_pAudio;
	CtModeCheckNetwork* m_pNetWork;
	CtModeCheckStatus* m_pStatus;
	CtModeCheckSwitch* m_pSwitch;
	CtModeCheckFunction* m_pFunction;

};

#endif /* __CtMenuButtonList_H__ */
