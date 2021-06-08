/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowHome
 */


#ifndef __CtWindow_Home_H__
#define __CtWindow_Home_H__

#include "CtWindowCommon.h"
#include "CtFastContainerAudioLevel_Home.h"
#include "CtFastContainerTimeCode.h"
#include "AplParamService.h"
#include "CtInterface.h"
#include "CtStackLabel.h"
#include "CtContainerCard1.h"
#include "CtContainerCard2.h"
#include "CtContainerWifi.h"
#include "CtContainerBattery.h"
#include "CtFastDrawContainerTcgWarning.h"
#include "CtEventInterface.h"

const int CT_HOME_TIMER_ID = 0;
class CtWindowHome : public CtWindowMain{
private:
	//#define PixCodecFontSize 37
	
	typedef	enum LayoutIdentifyId{
		LayoutIdentifyUpper,
		LayoutIdentifyLower,
		/********** 使用しない事 **************/
		LayoutIdentifyMin = 0,
		LayoutIdentifyMax = LayoutIdentifyLower
		/**************************************/
	}LayoutIdentifyId;

	typedef enum ButtonId{
		ButtonIdFps,
		ButtonIdColor,
		ButtonIdShutter,
		ButtonIdEi,
		ButtonIdAudio,
		ButtonIdWb,
		/********** 使用しない事 **************/
		ButtonIdMin = 0,
		ButtonIdMax = ButtonIdWb
		/**************************************/
	}ButtonId;

	typedef	enum LayoutColorIdentifyId{
		LayoutColorIdentifyColorBtn,
		LayoutColordentifyOutColor,
		/********** 使用しない事 **************/
		LayoutColorIdentifyMin = 0,
		LayoutColorIdentifyMax = LayoutColordentifyOutColor
		/**************************************/
	}LayoutColorIdentifyId;
	
public:
	CtWindowHome();
	~CtWindowHome();

	CtButton* createBtnFps();
	CtButton* createBtnColor();
	CtButton* createBtnShutter();
	CtButton* createBtnEi();
	CtButton* createBtnAudio();
	CtButton* createBtnWb();
	CtLayout* create3BtnLayout(LayoutIdentifyId id);
	CtLayout* create3BtnNameUpperLayout();
	CtLayout* create3BtnNameLowerLayout();
	CtLayout* createFpsNumericLayout();
	CtLayout* createFpsOnIntLayout();
	CtLayout* createShutterNumericLayout(CtLabel* pLabel, const GDI_IMAGE_ID imgID);
	CtLayout* createCenterLeftLayout();
	CtLayout* createCenterRightLayout();
	CtLayout* createTCGOrWarningLayout();
	CtLayout* createSlotLayout();
	CtLayout* create2SlotFuncAndRecModeLayout();
	CtLayout* createOutColorLayout();
	CtLayout* create2SlotFuncOrSubRecLayoutLowerLeft();
	CtLayout* createRecModLayoutLowerRight();
	CtLayout* createRecModLayoutUpperRight();
	CtLayout* createSubRecAndRecModLayoutLowerLeftAndCenter();
	CtLayout* create2SlotFuncLayoutCenter();
	CtLayout* create2SlotFuncAndRecModLayoutCenter();
	CtLayout* createLanAndBatteryAndClipLayout();
	CtLayout* createClipLayout();

	void createVFRONLayout();
	void createVFROffLayout();
	void createMainVlogLayout();
	void createSubOffLayout();
	void createMainSceneLayout();
	void createShutterOff();
	void createShutterSec();
	void createShutterDeg();
	void createEiIsoLayout();
	void createEiGainLayout();
	void createWbNumLayout();
	void createAtwLayout();
	void createOutColor3XLayout();
	void createOutColor1XLayout();
	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleTouchEvent(const CtEventTouch& Touch);
	bool handleTimerEvent(const CtEventTimer& Timer);

	CtStackLabel* getISONative();
	CtStackLabel* getISO800Base();
	CtStackLabel* getISO2500Base();
	CtStackLabel* getLabelGain();
	CtStackLabel* getLabelColor(LayoutColorIdentifyId ColorId);
	CtStackLabel* getLabelMainCodec();
	
	void updateClipName();
	void updateClipNo();
	void updateBtnFpsNameLabel();
	void updateVFROnLabel();
	void updateVFROffLabel();
	void updateVFROnLayout();
	void updateVFRInvalidLayout();
	void updateBtnFps();
	void updateMainVlogLayout();
	void updateSubOffLayout();
	void updateMainSceneLayout();
	void updateBtnColor();
	void updateBtnShutter();
	void updateBtnEi();
	void updateBtnAudioCH1();
	void updateBtnAudioCH2();
	void updateBtnWb();
	void update2SlotFuncAndRecModeLayout();
	void updateOutColorLayout();
	void updateSysStatusLayout();
	void updateMainCodecLayout();
	void updateClipLayout();
	void updateSceneFileName();
	
private:
	CtWindow* createWindow();
	CtStackLabel* createStackLabelByList(const char** c, const CtFontSet &fset, int count);
	CtStackLabel* createStackLabelByList(const GDI_STRING_ID *strid, const CtFontSet &fset, int count);
	
	bool destroyWindow();

	CtWindow* m_pWin;
	char m_SceneFileName[33];
	CtStackLabel* m_pFpsName;
	CtLayout* m_pVRFOn;
	CtLayout* m_pVRFOff;
	CtLayout* m_pFpsIntLayout;
	CtLayout* m_pFpsDecLayout;
	CtLabel* m_pLabelIntPart;
	CtLabel* m_pLabelDecPart;
	CtLabel* m_pLabelInterlace;
	CtLabel* m_pLabelFpsOnInt;
	CtLabel* m_pDecFpsIcon;
	CtStackLabel* m_pLabelMainColor;
	CtStackLabel* m_pLabelSubColor;
	CtLabel* m_pLabelSceneName;
	CtLayout* m_pMainVLog;
	CtLayout* m_pSubOff;
	CtLayout* m_pMainScene;
	CtLabel* m_pLabelSec;
	CtLabel* m_pLabelDeg;
	CtLayout* m_pShutterOff;
	CtLayout* m_pShutterSec;
	CtLayout* m_pShutterDeg;
	CtStackLabel* m_pLabelIsoSel;
	CtLabel* m_pLabelGainSel;
	CtStackLabel* m_pLabelGain;
	CtStackLabel* m_pISONative;
	CtStackLabel* m_pISO800Base;
	CtStackLabel* m_pISO2500Base;
	CtLayout* m_pEiIso;
	CtLayout* m_pEiGain;
	CtLabel* m_pLabelCH1;
	CtLabel* m_pLabelCH2;
	CtStackLabel* m_pLabelSelCH1;
	CtStackLabel* m_pLabelSelCH2;
	CtStackLabel* m_pLabelSelInput;
	CtStackLabel* m_pLabelWb;
	CtLabel* m_pLabelWbNum;
	CtLayout* m_pWbNum;
	CtLayout* m_pATW;
	CtLabel* m_pLabel2SlotOrSub;
	CtLabel* m_pLabelBothCenter2Slot;
	CtLabel* m_pLabelBothCenterRec;
	CtLabel* m_pLabelCenter2Slot;
	CtLabel* m_pLabelSubRec;
	CtLabel* m_pLabelUpperRight;
	CtLabel* m_pLabelLowerRight;
	CtLayout* m_pLowerLeft;
	CtLayout* m_pLowerRight;
	CtLayout* m_pUpperRight;
	CtLayout* m_pLowerLeftAndCenter;
	CtLayout* m_pCenter;
	CtLayout* m_pBothCenter;
	CtLayout* m_p2SlotFuncNull;
	CtStackLabel* m_pLabelSdiOutColor;
	CtStackLabel* m_pLabelHdmiOutColor;
	CtStackLabel* m_pLabelLcdOutColor;
	CtStackLabel* m_pLabelMainOutColor;
	CtLayout* m_pOutColorX3;
	CtLayout* m_pOutColorX1;
	CtLabel* m_pLabelSysSta;
	CtStackLabel* m_pLabelMainCodec;
	CtLayout* m_pClip;
	CtLayout* m_pClipNull;
	CtLabel* m_pClipName;
	CtLabel* m_pClipNo;
	CtButton* m_pButtonFps;
	CtButton* m_pButtonColor;
	CtButton* m_pButtonShutter;
	CtButton* m_pButtonEi;
	CtButton* m_pButtonAudio;
	CtButton* m_pButtonWb;

	static CtColor LabelColor;
	static CtColor RectColor;
	static CtColor ImagColor;
	static CtColor LineColor;
	
	void moveFocus(bool Dir);
	void moveFocus(const CtDirection Dir );
	void updateFocus(bool flag);

	ButtonId m_FocusButton;

	bool m_bTouchButton;
	bool m_bManualFunction;
	bool m_bHighLight;
	bool m_bCanMmr;
};

#endif
