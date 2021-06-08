/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDispMessage
*/


#ifndef __CtFactWindowDispMessage_H__
#define __CtFactWindowDispMessage_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsDispMessage.h"

class CtFactWindowDispMessage : public CtWindowMain
{
public:
	CtFactWindowDispMessage(CtWindowContents *pContents);
	~CtFactWindowDispMessage();
	CtWindow* createWindow();

private:

	CtWindow *m_pWin;

private:
	bool destroyWindow();

	bool setContents(const CtWindowContents * pContents);

	CtWindowContentsDispMessage* m_pContent;

};

#endif
