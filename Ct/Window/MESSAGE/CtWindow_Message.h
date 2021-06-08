/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_Message
 */


#ifndef __CtWindow_Message_H__
#define __CtWindow_Message_H__

#include "CtWindowCommon.h"
#include "CtMessageInfo.h"
#include "CtContainerMessage.h"

class CtWindow_Message : public CtWindowMain
{
public:
	CtWindow_Message(CtWindowID id, CtWindowContents *pContents);
	~CtWindow_Message();
	virtual CtWindow* createWindow();
	bool destroyWindow();

private:

private:
	CtMessageInfo::MessageInfo*   m_Info;

	int m_Param;
	int m_Value;

};
#endif
