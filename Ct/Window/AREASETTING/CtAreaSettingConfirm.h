/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtAreaSettingConfirm
 */


#ifndef __CtAreaSettingConfirm_H__
#define __CtAreaSettingConfirm_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtWindowMain.h"
#include "CtWindowCommon.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"



class CtAreaSettingConfirm : public CtWindowMain {
public :
	CtAreaSettingConfirm(CtWindowContents *pContents);
	
	virtual ~CtAreaSettingConfirm();

	CtWindow* createWindow();

	bool destroyWindow();

	bool handleButtonEvent(const CtEventButton& Button);

    bool handleKeyEvent(const CtEventKey& Key);

private :	

	/**********************  attributes **********************/
	CtWindow *m_pWin;


    CtButton *m_pConfirm;
    CtButton *m_pCancel;

    int m_nUseArea;
    int m_nAreaSettingType;


};


#endif
