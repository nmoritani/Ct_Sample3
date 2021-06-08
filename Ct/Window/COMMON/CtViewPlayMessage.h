/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtViewPlayMessage
 */


#ifndef __CtViewPlayMessage_H__
#define __CtViewPlayMessage_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtWindowMain.h"
#include "CtWindowCommon.h"
#include "AplParamService.h"


class CtViewPlayMessage : public CtWindowMain {
public :
	CtViewPlayMessage();

	virtual ~CtViewPlayMessage();

	CtWindow* createWindow();

	virtual bool destroyWindow();

	virtual bool handleParamEvent(const CtEventParam& Param);

	void dispRecViewMessage(const char * Str);

	void dispRecViewMessage(const GDI_STRING_ID StringID);


private :	
	void initDisplay();

	/**********************  attributes **********************/
	CtWindow *m_pWin;

	CtLabel*		m_pMsgStr;

	CtStackLabel*	m_pMsg;

};


#endif
