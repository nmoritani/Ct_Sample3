/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtPlayView
 */


#ifndef __CtPlayView_H__
#define __CtPlayView_H__

#include "Ct.h"

#include "CtWindowMain.h"

#include "CtWindowCommon.h"

#include "CtICManager.h"
#include "CtTimer.h"

#include "CtFastContainerAudioLevel_View.h"
#include "CtContainerPlayViewProgress.h"
#include "CtContainerButtonGroup.h"
#include "CtContainerCom.h"

const int CT_NAVI_TIMER_ID = 0;
const int CT_AUDIO_VOL_TIMER_ID = 1;

class CtPlayView : public CtWindowMain{
public :
	CtPlayView();

	virtual ~CtPlayView();

	CtWindow* createWindow();

	virtual bool destroyWindow();

	virtual bool handleParamEvent(const CtEventParam& Param);

	virtual bool handleTimerEvent(const CtEventTimer& Timer);

	virtual bool handleTouchEvent(const CtEventTouch & Event);

	virtual bool handleKeyEvent(const CtEventKey& Key);

	virtual bool startupWindow();
private :
	CtLayout* createTop();

	CtLayout* createMiddle();

	CtLayout* createLast();

	CtLayout* createAudioLevelMeter();

	void createProgressBar();

	CtLayout* createAudioVolume();

	void updateStatusPlay(int int_Data);

	void initDisplay();

	void initRecCheckDisp(bool isDisp = false);

	void updateAudioVol(int nVol);

	void setAlarm(int Uid, unsigned long Time);

	bool cancelAlarm(int Uid);

	bool dispPlayBackNavi(bool isDisp);
	void dispProgressBar(bool isDisp);
	bool isAbleDispAudioVol();
	bool updateSlideMotion(CtPosition Pos, const CtEventTouch & Event);
	bool updateFanStopped(int int_Data);
	/**********************  attributes **********************/
	
	CtWindow*						m_pWin;

	//CtLabel*						m_pClipName;
	CtLabel*						m_pFanStopped;
	CtLayout*						m_pMeter;

	CtButton*						m_pCap;

	CtContainerPlayViewProgress*	m_pProgressBar;

	CtStackLabel*					m_pPlayStatus;

	CtLayout*						m_pTime;

	CtContainerButtonGroup*			m_pBtnGroup;

	bool							m_PbNaviDisp;

	bool							m_SlideAction;

	CtPosition						m_SlidePos;

	CtHLayout*						m_pProgressBarLayout;

	CtFastContainerAudioLevel*		m_pAudioLevel;

	int								m_PreAudioVol;
	CtLayout*						m_pAudioVolume;
		CtStackLabel*						m_pVolumeVal[27];
};
#endif
