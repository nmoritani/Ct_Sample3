/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtAreaSetting
 */


#ifndef __CtAreaSetting_H__
#define __CtAreaSetting_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtWindowMain.h"
#include "CtWindowCommon.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"
#include "CtWindowContentsAreaSettingConfirm.h"


class CtAreaSetting : public CtWindowMain {
public :
	CtAreaSetting(CtWindowContents *pContents);
	
	virtual ~CtAreaSetting();

	CtWindow* createWindow();

	bool destroyWindow();

	bool handleButtonEvent(const CtEventButton& Button);

    bool handleKeyEvent(const CtEventKey& Key);

private :	

	void requestNextWindow();

	ContentsAreaSetting chackFocusButton();

	/**********************  attributes **********************/
	CtWindow *m_pWin;

	CtToggleButton *m_pAREA1;
	CtToggleButton *m_pAREA2;
	CtToggleButton *m_pAREA3;
	CtToggleButton *m_pAREA4;

    CtButton *m_pConfirm;
    CtButton *m_pCancel;

    // true：   画面上「決定」と「戻る」のボタンがある
    // false：  画面上「決定」と「戻る」のボタンがない
    bool m_bFlagForTwoBtn;

	ContentsAreaSetting m_Area;

};


#endif
