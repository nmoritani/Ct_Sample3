/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEventHandler
 */


#include "CtEventHandler.h"
#include "CtTimer.h"
#include "CtFlash.h"

CtEventHandler::CtEventHandler() :
	m_EventFilter(EventNone),
	useHandler(0)
{
	setClassType(CtClassType_EventHandler);
}

CtEventHandler::~CtEventHandler()
{
	if (useHandler) {
		if (useHandler & EventTimer) {
			CtTimer::getInstance()->stopTimer(this);
		}
		if (useHandler & EventFlash) {
			CtFlash::getInstance()->stopFlash(this);
		}
	}
}

bool CtEventHandler::handleTouchEvent(const CtEventTouch& Touch)
{
	return false;
}
bool CtEventHandler::handleKeyEvent(const CtEventKey& Key)
{
	return false;
}
bool CtEventHandler::handleParamEvent(const CtEventParam& Param)
{
	return false;
}
bool CtEventHandler::handleTimerEvent(const CtEventTimer& Timer)
{
	return false;
}
bool CtEventHandler::handleFlashEvent(const CtEventFlash& Flash)
{
	return false;
}
bool CtEventHandler::handleButtonEvent(const CtEventButton& Button)
{
	return false;
}
bool CtEventHandler::handleWidgetEvent(const CtEventWidget& Widget)
{
	return false;
}
bool CtEventHandler::handleRequestEvent(const CtEventRequest& Request)
{
	return false;
}
void CtEventHandler::setUseFlag(CtEventFilter _filter)
{
	useHandler |= _filter;
}
void CtEventHandler::clearUseFlag(CtEventFilter _filter)
{
	useHandler &= ~_filter;
}

CtEventFilter CtEventHandler::getEventFilter() const
{
	return m_EventFilter;
}

bool CtEventHandler::setEventFilter(const CtEventFilter _filter)
{
	unsigned int tmp = m_EventFilter;
	
	tmp |= _filter;
	m_EventFilter = (CtEventFilter)tmp;
	return true;
}

bool CtEventHandler::clearEventFilter(CtEventFilter _filter)
{
	unsigned int tmp = m_EventFilter;
	
	tmp &= ~_filter;
	m_EventFilter = (CtEventFilter)tmp;
	return true;
}

bool CtEventHandler::isReceiveEvent(CtEventFilter _filter)
{
	if ((m_EventFilter & _filter) && (m_EventFilter & EventInvalid) == 0)
		return true;

	return false;
}

bool CtEventHandler::setEventInvalid(bool bInvalid)
{
	unsigned int tmp = m_EventFilter;

	if (bInvalid == true) {
		tmp |= EventInvalid;
	} else {
		tmp &= ~EventInvalid;
	}
	m_EventFilter = (CtEventFilter)tmp;
	return true;
}

bool CtEventHandler::isEventInvalid() const
{
	if ((unsigned int)m_EventFilter & EventInvalid)
		return true;

	return false;
}

