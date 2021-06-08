/**
 *  Copyright (c) 2018 Persol AVC Technology1
 *  Element:			CtFastContainerLevelGauge
 */


#ifndef __CtFastContainerLevelGauge_H__
#define __CtFastContainerLevelGauge_H__

#include "CtWindowCommon.h"
#include "CtViewDesign.h"
#include "CtRecViewContainer.h"

class CtFastContainerLevelGauge : public CtRecViewContainer
{
	//static const int LEVEL_DISP_COUNT = 10;	// •œ‹AŽž‚É10V‘Ò‚¿‚·‚é

protected:
	enum LevelGaugeFocusType {
		LevelGaugeFocusType_FocusLock,
		LevelGaugeFocusType_NearMinus,
		LevelGaugeFocusType_NearPlus,
		LevelGaugeFocusType_Far,
	};

public :
	CtFastContainerLevelGauge();
	virtual ~CtFastContainerLevelGauge();
	
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();
	virtual bool handleParamEvent(const CtEventParam& Param);
	bool updateFastDraw();
	virtual bool startupContainer();

protected :
#ifdef WIN32_GUI_SIM
	short m_angle;
	short m_level;
#endif

	int dispcouter;
	static const int a_table[];
	static const int l_table[];
	
	virtual void updatePos();
	void updatePosCommon(int aori, int balance, CtRegion rAori, CtRegion rCenter, CtRegion rBar);
	int getAngleValue();
	int getBalanceValue();
	bool isDispLevelGauge();
	LevelGaugeFocusType getFocusType(int value);

private:
	CtColor getFarColor();
	CtColor getNearColor();
	CtColor getFocusLockColor();
	
	CtLabel*	m_pAori;
	CtLabel*	m_pCenter;
	CtLabel*	m_pBar;
};

#endif
