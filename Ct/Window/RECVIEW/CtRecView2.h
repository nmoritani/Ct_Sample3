/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtRecView
 */


#ifndef __CtRecView2_H__
#define __CtRecView2_H__

#include "Ct.h"
#include "CtParamBox.h"
#include "CtMmlLayout.h"

#include "CtContainerBattery.h"
#include "CtContainerWifi.h"

#include "CtContainerCard1.h"
#include "CtContainerCard2.h"

#include "CtFastContainerAudioLevel.h"
#include "CtFastContainerLevelGaugeL.h"
#include "CtFastContainerLevelGaugeR.h"
#include "CtFastContainerTimeCode.h"
#include "CtFastDrawContainerIris.h"
#include "CtFastDrawContainerZoom.h"
#include "CtFastDrawContainerSpotMeterVal.h"
#include "CtFastContainerAudioLevel_View.h"
#include "CtFastDrawContainerFocus.h"
#include "CtCtnrDateTime.h"
#include "CtContainerCom.h"
#include "CtContainerMml.h"
#include "CtRecContainerExpand.h"
#include "CtRecTouchNavi.h"

class CtRecView2 : public CtWindowMain {
public:

	CtRecView2();
	virtual ~CtRecView2();
	CtWindow* createWindow();
	virtual bool startupWindow();
	virtual bool destroyWindow() { return true; };

	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleButtonEvent(const CtEventButton& Button) { return false; };


private:
	enum {
		CT_TIMER_ID_TOUCH_NAVI_DISP,
		CT_TIMER_ID_EXIT,
		CT_TIMER_ID_AUDIO_VOL,
		CT_TIMER_ID_DISP_CHECK,
	};
	CtRecViewFontSet m_fSetDef;
	void init();

	// ICï\é¶ä«óù
	bool setIcManager();
	bool resetIcManager();
protected:
	CtLayout* createLine1();
	CtLayout* createLine2();
	CtLayout* createLine3();
	CtLayout* createLine5();
	CtLayout* createLine6();
	CtLayout* createLine7();
	CtLayout* createLine8();

	CtWindow*						m_pWin;
	CtVLayout*						m_pTotalLine;

	// K519
	//////// Line1 Member ////////
	CtFastContainerTimeCode*		m_pTC;// !Åö
	CtLabel*						m_pAutoMnl;// Åö
	CtContainerCard1*				m_pCard1;// Åö
	CtContainerCard2*				m_pCard2;// Åö
	CtLabel*						m_pSlotFunc;// Åö
	CtLabel*						m_pStreamingState;// Åö
	CtContainerWifi*				m_pWifi;// Åö
	CtContainerBattery*				m_pBat;// Åö
	bool updateSlotFunc(int t_Id, int int_Data);
	bool updateStreamState(int t_Id, int int_Data);
	bool updateAutoMnlMode(int t_Id, int int_Data);

	//////// Line2 ////////
	CtLabel*						m_pLineAndFreq;// Åö
	
	CtLabel*						m_pVfrRecFrameRate;// Åö
	CtLabel*						m_pS_Slow;
	CtMmlLayout*						m_pVfrRecFrameRateLayout;// Åö
	CtStackLabel*						m_pStkVfrArea;
	

	CtHLayout*						m_pBondingDeckState;// Åö
	CtLabel*					m_pBondingDeviceStatus;// Åö
	CtLabel*					m_pBondingConnectStatus;// Åö
	CtLabel*					m_pBondingBatteryRemain;// Åö
	CtLayout*					m_pBondingErrorStatus;// Åö

	CtHLayout*						m_pLayoutRecRemoteAll;// Åö
	CtLabel*					m_pRecRemoteIcon;// Åö
	CtLabel*					m_pRecRemoteStr;// Åö

	CtLabel*						m_pRecMode;// Åö
	CtLabel*						m_pFlashBand;
	CtLabel*						m_pHdr_Drs;
	CtLabel*						m_pOis;

	bool updateSystemRecMode(int t_Id, int int_Data);
	bool updateVFRValue();
	bool updateBondingStatus(int t_Id, int int_Data);
	bool updateRemoteRec();
	bool updateRecMode(int t_Id, int int_Data);
	bool updateFBC(int t_Id, int int_Data);
	bool updateDRS(int t_Id, int int_Data);
	bool updateOIS(int t_Id, int int_Data);

	//////// Line3 ////////
	CtLabel*						m_pMainCodec;// Åö
	CtContainerCom*					m_pCom;
	CtLabel*						m_pSceneFileName;// Åö
	CtLabel*						m_pArea_AfArea;// Åö
	//CtStackLabel*					m_pArea_AfArea;
	CtLabel*						m_pNdFilterWarn;// Åö
	CtLabel*						m_pFanStopped;// Åö

	bool updateMainCodec(int t_Id, int int_Data);
	bool updateSceneFileName(int t_Id, int int_Data);
	bool updateAreaMode(int t_Id, int int_Data);
	bool updateNdFilterWarn(int t_Id, int int_Data);
	bool updateFanStopped(int int_Data);

	//////// Gauge Line ////////
	CtVLayout*						m_pLevelGaugeLayout;
	CtFastContainerLevelGaugeL*		m_pLevelL;
	CtFastContainerLevelGaugeR*		m_pLevelR;

	//////// Line7 ////////

	CtLabel*						m_pIrRec;
	bool updateIrRec(int t_Id, int int_Data);

	//////// Line8 ////////
	CtContainerMml*						m_pMML;
	CtLabel*						m_pDzoom;
	bool updateDzoom(int t_Id, int int_Data);

	//////// Line9 ////////
	CtLabel*							m_pWbData;
	CtMmlLayout*							m_pWbDataLayout;
	CtFastDrawContainerSpotMeterVal*	m_pYget;
	CtCtnrDateTime*						m_pDateTime;
	CtLabel*							m_pHighSens;
	CtFastDrawContainerFocus*			m_pFocus;

	bool updateWB();
	bool updateH_Sens(int t_Id, int int_Data);

	//////// Line10 ////////
	CtFastContainerAudioLevel*			m_pAudioLevelMeter;
	CtLabel*							m_pGain;
	CtLabel*							m_pNdFilter;
	CtLabel*						m_pShutterSpeed;
	CtMmlLayout*						m_pShutterSpeedLayout;
	CtFastDrawContainerIris*		m_pIris;
	CtFastDrawContainerZoom*		m_pZoom;
	CtLayout*						m_pAudioMonitorVolArea;
	CtLabel*						m_pAudioMonitorVol;

	bool updateGain();
	bool updateNdFilter();
	bool updateShutterSpeed();
	bool updateAudioVol(int int_Data);

	/////////////////////////// IC ä«óùïœêî ////////////////////////////////////////////
	bool 							m_RecModeFlush;
	bool 							m_ComModeFlush;

	CtStackLabel*					m_pAudioCameraSwitchArea;
	int								m_PreAudioVol;
	CtStackLabel*					m_pVolumeVal[27];
	CtLayout*						m_pExpand;
	CtRecContainerExpand*			m_pRecContainerExpand;
	CtVLayout*						m_pSwitchLine;
};


#endif
