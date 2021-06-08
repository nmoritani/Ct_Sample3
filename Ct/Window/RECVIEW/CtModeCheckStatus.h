/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtModeCheckStatus_H__
#define __CtModeCheckStatus_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"

class CtModeCheckStatus : public CtContainer
{
public:
	CtModeCheckStatus();
	virtual bool destroyWindow();
	virtual bool startupContainer();
	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	CtLayout* createContainer();

	bool setHide();
protected :
	~CtModeCheckStatus();

private :
	CtLayout* createLineWarn();
	CtLayout* createLineAwbNg();
	CtLayout* createLineAbbNg();
	CtLayout* createLineIpRemote();


	CtLayout *m_pAll;

	CtLabel* m_pWarnLine1;
	CtLabel* m_pWarnLine2;
	CtLabel* m_pAwbNg;
	CtLabel* m_pAbbNg;

	bool updateWarningState();
	bool updateAwbNg(int t_Id, int int_Data);
	bool updateAbbNg(int t_Id, int int_Data);

	CtLabel* m_pIpRemote;
	bool updateIpRemote(int t_Id, int int_Data);
	
};

#endif /* __CtMenuButtonList_H__ */

