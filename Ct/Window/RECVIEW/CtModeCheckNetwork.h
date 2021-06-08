/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtModeCheckNetwork_H__
#define __CtModeCheckNetwork_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"

class CtModeCheckNetwork : public CtContainer
{
public:
	CtModeCheckNetwork();
	virtual bool destroyWindow();
	bool startupContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	CtLayout* createContainer();
protected :
	~CtModeCheckNetwork();

private :
	CtLayout *m_pAll;

	CtLabel* m_pDeviceSel;
	bool updateDeviceSel(int int_Data);

	CtLabel* m_pNetWorkFunc;
	bool updateNetWorkFunc(int int_Data);

	CtHLayout* m_pStrmFormatLine;
	CtLabel* m_pStrmFormat;
	bool updateStrmFormat();

	CtHLayout* m_pStrmDataTypeLine;
	CtLabel* m_pStrmDataType;
	bool updateStrmDataType();

	CtLabel* m_pIpRemote;
	bool updateIpRemote(int int_Data);

	CtLabel* m_pIpAddress;
	bool updateIpAddress();
};

#endif /* __CtMenuButtonList_H__ */

