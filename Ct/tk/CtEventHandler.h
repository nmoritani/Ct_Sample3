/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEventHandler
 */


#ifndef __CtEventHandler_H__
#define __CtEventHandler_H__

#include <CtList.h>
#include "CtObject.h"
#include "CtEvent.h"

class CtEventHandler : public CtObject {
public:
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleFlashEvent(const CtEventFlash& Flash);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	virtual bool handleRequestEvent(const CtEventRequest& Request);
	
	virtual CtEventFilter getEventFilter() const;
	virtual bool isReceiveEvent(const CtEventFilter _filter);
	virtual bool setEventFilter(const CtEventFilter _filter);
	virtual bool clearEventFilter(const CtEventFilter _filter);
	void setUseFlag(CtEventFilter _filter);
	void clearUseFlag(CtEventFilter _filter);
	
	virtual bool setEventInvalid(bool bInvalid);
	bool isEventInvalid() const;

protected:
	CtEventHandler();
	virtual ~CtEventHandler();

private:
	unsigned int useHandler;
	CtEventFilter m_EventFilter;
};

#endif
