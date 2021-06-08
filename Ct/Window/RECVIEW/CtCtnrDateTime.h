/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtCtnrDateTime_H__
#define __CtCtnrDateTime_H__

#include "Ct.h"
#include "CtRecViewContainer.h"
#include "CtStackLabel.h"

class CtCtnrDateTime : public CtRecViewContainer
{
#define CLOCKSET_CHECK_LEAP_YEAR(year)	((!((year)%4) && (year)%100) || !((year)%400))
public:

	CtCtnrDateTime();
	virtual bool destroyWindow();
	virtual CtLayout* createContainer();
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool setStatusMode(bool bStatusMode);
	virtual bool startupContainer();
protected :
	enum {
		CT_TIMER_ID_DATE_TIME,
	};
	~CtCtnrDateTime();
private :
	bool updateDateTime();
	//bool updateDispSel();
	char* convertMonthToString(int Month);

	CtLayout* m_pAll;
	CtLabel* m_pDateTime;
};

#endif /* __CtCtnrDateTime_H__ */

