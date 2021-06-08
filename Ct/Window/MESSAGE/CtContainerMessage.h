/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:	CtButton
 */
 
#ifndef __CtContainerMessage_H_
#define __CtContainerMessage_H_

#include "CtMessageInfo.h"
#include "CtWindowCommon.h"
#include "CtMenuInfo.h"

const int CT_MSG_TIMER_ID = 0;

class CtContainerMessage : public CtContainer
{
public :

	CtContainerMessage(CtWindowID Windowid);
	virtual ~CtContainerMessage();
	virtual CtLayout* createContainer();

	bool handleButtonEvent(const CtEventButton& Button);
	bool handleTouchEvent(const CtEventTouch& Touch);
	bool handleTimerEvent(const CtEventTimer& Timer);
	bool handleKeyEvent(const CtEventKey& Key);

	virtual bool startupContainer();
	void setParam(int param, int value);

private:
	virtual bool destroyContainer() { return true; }

	/* Builder */
	CtLayout* createLayout();
	CtLayout* createTelop();
	CtLayout* createDialog();
	CtLayout* createFull();
	CtLayout* createMessage(short &Num);

	/* Registre */
	void executionSet();
	void executionRet();
	void closeWindow();

	void setTimer();

	int getMsgStrSize(char* Str);
	int getMsgStrSize(GDI_STRING_ID STR_ID);

private:
	CtWindowID m_WindowID;
	CtMessageInfo::MessageInfo*   m_Info;
	int m_Param;
	int m_Value;
	unsigned int m_Lines;

};

#endif
