/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#ifndef __CtRecContainerTouchNavi_H__
#define __CtRecContainerTouchNavi_H__

#include "Ct.h"
#include "CtWindowMain.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtToggleButton.h"

class CtRecTouchNavi : public CtWindowMain
{
private:
	enum {
		CT_TIMER_ID_TOUCH_NAVI_TIME,
	};
public:
	CtRecTouchNavi();
    virtual ~CtRecTouchNavi();
	CtWindow* createWindow();
	bool restartWindow();
	bool startupWindow();
	bool setVisible(bool bVisible);
	bool isVisible();

	void setTimeLimit(bool bSet);

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleTouchEvent(const CtEventTouch& Touch);
	bool handleTimerEvent(const CtEventTimer& Timer);

private :
	CtLayout* createSceneBtns();
	bool updateSceneBtns(int currentSceneNo);
	bool updateSceneFileName(int changeSceneNo);

	CtLayout* createUserBtns();
	void updateUserBtns(int changeUserNo, int changeUserFuncNo);
	GDI_STRING_ID getUserFuncNameStrId(int UserFuncNo);
	
	bool m_bOpenFirstPressFlg;
private :
	CtRecViewFontSet m_fSet_Center;
	CtLayout *m_pAll;

	CtLabel* m_pSceneFileName1;
	CtLabel* m_pSceneFileName2;
	CtLabel* m_pSceneFileName3;
	CtLabel* m_pSceneFileName4;
	CtLabel* m_pSceneFileName5;
	CtLabel* m_pSceneFileName6;

	CtToggleButton *m_pPreScene;
	CtToggleButton *m_pSceneFile1;
	CtToggleButton *m_pSceneFile2;
	CtToggleButton *m_pSceneFile3;
	CtToggleButton *m_pSceneFile4;
	CtToggleButton *m_pSceneFile5;
	CtToggleButton *m_pSceneFile6;
	
	CtButton *m_pUser8;
	CtButton *m_pUser9;
	CtButton *m_pUser10;
	CtButton *m_pUser11;
	CtButton *m_pUser12;

	CtLabel* m_pUser8Func;
	CtLabel* m_pUser9Func;
	CtLabel* m_pUser10Func;
	CtLabel* m_pUser11Func;
	CtLabel* m_pUser12Func;
};
#endif /* __CtMenuButtonList_H__ */
