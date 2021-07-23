/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtMsg
 */


#include "CtMsg.h"

CtMsg::CtMsg()
{
	m_Priority = 0;
}

CtMsg::CtMsg(int Priority)
{
	m_Priority = Priority;
}

CtMsg::~CtMsg()
{
}

int CtMsg::getPriority()
{
	return m_Priority;
}

void CtMsg::setPriority(int priority)
{
	m_Priority = priority;
}
