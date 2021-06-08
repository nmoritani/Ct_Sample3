/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtPlayView
 */

#include "CtPlayView.h"
#include "CtContainerBattery.h"
#include "CtContainerWifi.h"
#include "AplParamService.h"
#include "CtFastContainerTimeCode.h"


#define ColorProgressBase	CtColor(ColorRGBA, 0xd4d4d4ff, NULL)
#define ColorProgressBar	CtColor(ColorRGBA, 0x66e300ff, NULL)

#define ProgressBarBase		CtMargin(3,12)
#define ProgressBarBar		CtMargin(5,14)

CtPlayView::CtPlayView() :
	m_pWin(NULL),
	m_pProgressBar(NULL),
	m_pPlayStatus(NULL),
	m_pTime(NULL),
	m_pMeter(NULL),
	m_pBtnGroup(NULL),
	m_PbNaviDisp(false),
	m_SlideAction(false),
	m_pProgressBarLayout(NULL),
	m_pFanStopped(NULL),
	m_pAudioVolume(NULL)
{
	setTransView(true);
	m_PreAudioVol = APL_PARAM_GET_DATA(AplParamAudioVol);
	if (m_PreAudioVol <= 0 || 28 <= m_PreAudioVol) m_PreAudioVol = 1;
}

CtWindow* CtPlayView::createWindow()
{
	CtLayout* pTop = createTop();

	CtLayout* pMid = createMiddle();

	CtLayout* pLast = createLast();
	/************************LayoutMain Layer***********************/
	CtVLayout *pLayoutMain = new CtVLayout();

	pLayoutMain->addWidget(pTop, 1);//1
#if 1
	pLayoutMain->addWidget(pMid, 12);	//24
	pLayoutMain->setStretch(pMid, 10, ScreenLOUT);//24
#else
	pLayoutMain->addWidget(pMid, 12, ScreenLCD);//24
	pLayoutMain->addWidget(pMid, 10, ScreenLOUT);//24
#endif
	pLayoutMain->addWidget(pLast, 1);

	// Window
	m_pWin = new CtWindow( /*CtColor::Trans*/);
	m_pWin->addWidget(pLayoutMain);
	m_pWin->setVisible(true);
	m_pWin->setTrans(true);
	m_pWin->setRoundFocus(true);
	if (m_pBtnGroup != NULL) {
		m_pWin->setDefaultFocus(m_pBtnGroup->getDefaultFocusWidget());
	}
	return m_pWin;
}

CtPlayView::~CtPlayView()
{
	destroyWindow();
}

CtLayout* CtPlayView::createTop() {
	CtRecViewFontSet fSet_Center = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	CtRecViewFontSet fSet_Left = CtRecViewFontSet(FontTypeNormal, CtColor::White);
	CtRecViewFontSet fSet_Right = CtRecViewFontSet(FontTypeNormal_alignRight, CtColor::White);
	fSet_Center.setSize(18);
	fSet_Left.setSize(18);
	fSet_Right.setSize(18);

	CtLabel *pLabel = NULL;
	CtLabel *pNone = NULL;

	/************************TOP***********************/
	CtHLayout *pTop = new CtHLayout(CtColor::Trans);

	// TC
	CtFastContainerTimeCode *pTimeCode = new CtFastContainerTimeCode(true, CT_COMMON_TYPE_PLAY);
	pTimeCode->setWindowID(getWindowID());

	pTop->addContainer(pTimeCode, AlignCenter, 15);

	pTop->addStretch(24);
	// PlayStatus
	m_pPlayStatus = new CtStackLabel();
	pLabel = new CtLabel(IC_OSD_STOP);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_PLAY);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_STILL);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_BOS);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_EOS);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_FFX10);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_FFX20);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_REWX10);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_REWX20);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_SLOW_FEED);
	m_pPlayStatus->addLabel(pLabel);
	pLabel = new CtLabel(IC_OSD_SLOW_BACK);
	m_pPlayStatus->addLabel(pLabel);

	m_pPlayStatus->index(APL_SYS_PARAM_STATUS_PLAY_PLAYING);

	pTop->addWidget(m_pPlayStatus, AlignCenter, 6);

	pTop->addStretch(5);

	CtContainerBattery *pBattery = new CtContainerBattery(CT_COMMON_TYPE_PLAY);
	pTop->addContainer(pBattery, AlignCenter, 3);

	return pTop;
}

CtLayout* CtPlayView::createMiddle() {
	CtRecViewFontSet fSet_Center = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);

	CtLabel *pNone = NULL;
	CtLabel* pLabel = NULL;

	/************************MID***********************/
	CtLayout* pMidAll = new CtLayout();
	CtHLayout *pMid = new CtHLayout();

	// None
	pMid->addStretch(1);
	pMid->addStretch(14);
	pMid->addStretch(2);

	CtVLayout* pVLayout = new CtVLayout();
	{
		CtFontSet fset = CtFontSet(FontTypeOutline_alignCenter, CtColor::White);
		fset.edgeColor = CtColor::Black;
		m_pFanStopped = new CtLabel(STR_ID_NO_10737, fset);

		pVLayout->addStretch(1);
		pVLayout->addWidget(m_pFanStopped, AlignCenter, 1);
		pVLayout->addStretch(2, ScreenLCD);
		pVLayout->addStretch(8);
	}

	pMid->addWidget(pVLayout, AlignCenter, 19);
	pMid->addStretch(1);

	// Com
	CtVLayout *pLayoutCom = new CtVLayout();
	pLayoutCom->addStretch(1);
	CtContainerCom* pCom = new CtContainerCom();
	pLayoutCom->addContainer(pCom, AlignCenter, 2);

	// None
	pLayoutCom->addStretch(2, ScreenLCD);
	pLayoutCom->addStretch(7);

	pMid->addWidget(pLayoutCom, AlignCenter, 6);

	// None
	pMid->addStretch(1);
	pMid->addStretch(8);
	pMid->addStretch(1);

	// 統合
	pMidAll->addWidget(pMid);

	// ButtonGroup
	m_pBtnGroup = new CtContainerButtonGroup();
	m_pBtnGroup->setScreenSel(ScreenLCD);
	pMidAll->addContainer(m_pBtnGroup);

	return pMidAll;
}

CtLayout* CtPlayView::createLast() {
	/************************LAST***********************/
	CtLayout *pLast = new CtLayout();
	{
		createProgressBar();
		pLast->addWidget(m_pProgressBarLayout);
		CtLayout* pMeter = createAudioLevelMeter();
		pLast->addWidget(pMeter);
	}
	return pLast;
}

CtLayout* CtPlayView::createAudioLevelMeter() {
	/************************AudioLevelMeter***********************/
	CtHLayout *pMeter = new CtHLayout();
	// AudioLevelMeter
	m_pAudioLevel = new CtFastContainerAudioLevel_View(false);
	pMeter->addContainer(m_pAudioLevel, AlignCenter, 13);
	// AudioVolMeter
	m_pAudioVolume = createAudioVolume();
	pMeter->addWidget(m_pAudioVolume, 40);
	
	bool bDisp = APL_PARAM_GET_DATA(AplParamLcdIndicatorAudioLevelMeter) == APL_SYS_PARAM_SWITCH_ON;
	m_pAudioLevel->setScreenSel(bDisp ? ScreenAll : ScreenNone);
	
	return pMeter;
}

void CtPlayView::createProgressBar() {
	CtRect BarRect = CtRect(ColorProgressBar, 0, ColorProgressBar);
	CtRect BaseRect = CtRect(ColorProgressBase, 2, CtColor(ColorRGBA, 0x000000ff, NULL));

	m_pProgressBar =
		new CtContainerPlayViewProgress(
			CT_FRAME_TYPE_PROGRESS_BAR,
			BaseRect,
			BarRect,
			new CtLabel(IC_OSD_SLIDER_BTN),
			ProgressBarBase,
			ProgressBarBar);

	CtVLayout *pVLayout = new CtVLayout();
	pVLayout->addStretch(1);
	pVLayout->addContainer(m_pProgressBar, 2);
	pVLayout->addStretch(1);

	m_pProgressBarLayout = new CtHLayout(/*CtColor(ColorRGBA, 0x00000072, NULL)*/);
	m_pProgressBarLayout->addStretch(4);
	m_pProgressBarLayout->addWidget(pVLayout, 11);
	m_pProgressBarLayout->addStretch(1);
}

bool CtPlayView::destroyWindow()
{
	cancelAlarm(CT_NAVI_TIMER_ID);
	cancelAlarm(CT_AUDIO_VOL_TIMER_ID);
	return true;
}

bool CtPlayView::startupWindow()
{
	initDisplay();
	return true;
}

void CtPlayView::initDisplay() {
	int TempMargin = 0;

	/* ScrollBarのLayoutを再度計算する */
	CtRegion Region = m_pProgressBar->getLayout()->getRegion();
	if (ProgressBarBase.Left >= Region.height / 2) {
		TempMargin = ProgressBarBase.Left - Region.height / 2;
	}
	else {
		TempMargin = 0;
	}
	m_pProgressBar->setScrollBarMargin(CtMargin(0, TempMargin));
	m_pProgressBar->setPercent(APL_PARAM_GET_DATA(AplParamStatusPlaySeekBar));

	/* ProgressBarの背景もLCDのみ表示 */
	m_pProgressBarLayout->setScreenSel(ScreenLCD);

	updateStatusPlay(APL_PARAM_GET_DATA(AplParamStatusPlay));

	// RecCheck Decision
	if (Window_PlayView != this->getWindowID()) {
		initRecCheckDisp(false);
	}
	m_pAudioVolume->setVisible(false);
	updateFanStopped(APL_PARAM_GET_DATA(AplParamAlertFanStopped));
	dispPlayBackNavi(true);
}

bool CtPlayView::handleParamEvent(const CtEventParam& Param) {
	bool isRedraw = true;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamStatusPlay:
	case AplParamLcdIndicatorPlayBackStatus:
		updateStatusPlay(APL_PARAM_GET_DATA(AplParamStatusPlay));
		dispPlayBackNavi(true);
		isRedraw = true;
		break;
	case AplParamLcdCleanViewUserSw:
	case AplParamLcdSw:
		initDisplay();
		isRedraw = true;
		break;
	case AplParamAudioVol:
		updateAudioVol(int_Data);
		isRedraw = true;
		break;
	case AplParamAlertFanStopped:
		updateFanStopped(int_Data);
		isRedraw = true;
		break;
	case AplParamLcdIndicatorAudioLevelMeter:
		
		return m_pAudioLevel->setScreenSel(int_Data == APL_SYS_PARAM_SWITCH_ON ? ScreenAll : ScreenNone);
	default:
		isRedraw = false;
		break;
	}

	return isRedraw;
}

void CtPlayView::updateStatusPlay(int int_Data) {
	int Index = 0;

	switch (int_Data) {
	case APL_SYS_PARAM_STATUS_PLAY_STOP:
		Index = 0;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_PLAYING:
		Index = 1;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_STILL:
		Index = 2;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_STILL_TOP:
		Index = 3;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_STILL_LAST:
		Index = 4;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_FF_10:
		Index = 5;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_FF_20:
		Index = 6;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_REW_10:
		Index = 7;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_REW_20:
		Index = 8;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_FF_SLOW:
		Index = 9;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_REW_SLOW:
		Index = 10;
		break;
	default:
		return;
	}
	m_pPlayStatus->index(Index);
	if (APL_PARAM_GET_DATA(AplParamLcdIndicatorPlayBackStatus) == APL_SYS_PARAM_SWITCH_ON) {
		m_pPlayStatus->setVisible(true);
	}
	else {
		m_pPlayStatus->setVisible(false);
	}
}

void CtPlayView::initRecCheckDisp(bool isDisp) {
	/* 再生状態非表示 */
	m_pPlayStatus->setVisible(isDisp);
	/* 再生NAVI非表示 */
	m_PbNaviDisp = isDisp;
	m_pBtnGroup->getLayout()->setVisible(isDisp);
	m_pProgressBar->getLayout()->setVisible(isDisp);
	m_pProgressBarLayout->setVisible(isDisp);
}

bool CtPlayView::handleTimerEvent(const CtEventTimer& Timer)
{
	switch (Timer.getTimeUid()) {
	case CT_NAVI_TIMER_ID:
		return dispPlayBackNavi(false);
		break;
	case CT_AUDIO_VOL_TIMER_ID:
		m_pAudioVolume->setVisible(false);
		dispProgressBar(true);
		return true;
		break;
	default:
		break;
	}

	return false;
}

bool CtPlayView::handleTouchEvent(const CtEventTouch & Event) {
	bool bRet = false;

	CtEventTouch::TouchPosition pos = Event.getPosition();
	CtPosition Pos;

	Pos.x = pos.m_X;
	Pos.y = pos.m_Y;

	switch (Event.getAction()) {
	case CtEventTouch::Press:
	case CtEventTouch::Move:
		break;
	case CtEventTouch::Slide:
		bRet = updateSlideMotion(Pos, Event);
		break;
	case CtEventTouch::Release:
		if (!m_PbNaviDisp) {
			bRet = true;
		}
		bRet = dispPlayBackNavi(true);
		break;
	default:
		break;
	}
	// 操作時延長
	setAlarm(CT_NAVI_TIMER_ID, 1000 * 3);

	return bRet;
}

void CtPlayView::setAlarm(int Uid, unsigned long Time) {
	cancelAlarm(Uid);
	CtTimer::getInstance()->setAlarm(Uid, Time, this);
}

bool CtPlayView::cancelAlarm(int Uid) {
	CtTimer::getInstance()->cancelAlarm(Uid, this);
	return true;
}

bool CtPlayView::handleKeyEvent(const CtEventKey& Key) {
	bool bRet = false;
	CtEventKey::KeyCode KeyCode = Key.getKeyCode();

	switch (KeyCode) {
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_Left:
	case CtEventKey::KeyCode_Right:
	case CtEventKey::KeyCode_Enter:
		return true;
		break;
	case CtEventKey::KeyCode_MmrMinus:
	case CtEventKey::KeyCode_MmrPlus:

	case CtEventKey::KeyCode_ManualFunction:
		bRet = dispPlayBackNavi(true);
		// 操作時延長
		setAlarm(CT_NAVI_TIMER_ID, 1000 * 3);
		break;
	default:
		break;
	}

	return bRet;
}

bool CtPlayView::updateFanStopped(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		return m_pFanStopped->setVisible(true);
	}
	else {
		return m_pFanStopped->setVisible(false);
	}
}

bool CtPlayView::updateSlideMotion(CtPosition Pos, const CtEventTouch & Event) {
	if (m_pProgressBar->getLayout()->isContains(Pos) ||
		m_pBtnGroup->isBtnsContain(Pos)) {
		return false;
	}

	const CtEventTouchSlide* pSlide = static_cast<const CtEventTouchSlide*>(&Event);
	switch (pSlide->getSlideDirection()) {
	case CtEventTouchSlide::SlideLeft:
		if (m_pWin != NULL) {
			CtEventInterface::requestFuncCmd(FuncID_PLAYNEXT, m_pWin, NULL);
			return true;
		}
		break;
	case CtEventTouchSlide::SlideRight:
		if (m_pWin != NULL) {
			CtEventInterface::requestFuncCmd(FuncID_PLAYPREV, m_pWin, NULL);
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

CtLayout* CtPlayView::createAudioVolume() {
	CtRecViewFontSet fSet = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);


	CtHLayout* pHAudioVol = new CtHLayout();
	{
		fSet.setFontAttribute(FontTypeOutline_alignRight);
		pHAudioVol->addWidget(new CtLabel("VOLUME[-]", fSet), AlignRight, 9);
		int i = 0;
		while (i < 27) {
			m_pVolumeVal[i] = new CtStackLabel();
			{
				m_pVolumeVal[i]->addLabel(new CtLabel(IC_OSD_VOL_OFF));
				m_pVolumeVal[i]->addLabel(new CtLabel(IC_OSD_VOL_ON));
			}
			pHAudioVol->addWidget(m_pVolumeVal[i], AlignCenter, 1);
			m_pVolumeVal[i]->index(0);
			i++;
		}
		fSet.setFontAttribute(FontTypeOutline);
		pHAudioVol->addWidget(new CtLabel("[+]", fSet), AlignLeft, 4);
	}
	m_pVolumeVal[m_PreAudioVol - 1]->index(1);

	return pHAudioVol;
}

bool CtPlayView::dispPlayBackNavi(bool isDisp) {

	/* RecCheckで表示指示は無視 */
	if (Window_PlayView != getWindowID()) {
		return false;
	}

	if (APL_SYS_PARAM_STATUS_PLAY_PLAYING != APL_PARAM_GET_DATA(AplParamStatusPlay)) {
		// 再生中ではない状態ではAudioVolを非表示
		if (m_pAudioVolume->isVisible() == true) {
			// 再生時以外はAudioVolキーはコマ送りとして機能する
			// 表示用途がないためProgressBarを表示させる
			m_pAudioVolume->setVisible(false);
			cancelAlarm(CT_AUDIO_VOL_TIMER_ID);
		}
	}
	if (isDisp == m_PbNaviDisp) {
		return false;
	}
	if (isDisp == true) {
		setAlarm(CT_NAVI_TIMER_ID, 1000 * 3);
		if (m_pBtnGroup != NULL) {
			if (m_pBtnGroup->getDefaultFocusWidget() != NULL) {
				m_pWin->setDefaultFocus(m_pBtnGroup->getDefaultFocusWidget());
			}
		}
	}

	m_PbNaviDisp = isDisp;
	if (m_pBtnGroup)m_pBtnGroup->setVisible(isDisp);
	dispProgressBar(isDisp);
	return true;
}

void CtPlayView::dispProgressBar(bool isDisp) {
	// Navi表示中 かつ表示要求
	if (m_PbNaviDisp == true && isDisp == true) {
		if (m_pAudioVolume->isVisible() == true) {
			// AudioVol表示中は非表示
			m_pProgressBar->getLayout()->setVisible(false);
			m_pProgressBarLayout->setVisible(false);
		}
		else {
			m_pProgressBar->getLayout()->setVisible(isDisp);
			m_pProgressBarLayout->setVisible(isDisp);
		}
	}
	else if (isDisp == false) {
		m_pProgressBar->getLayout()->setVisible(false);
		m_pProgressBarLayout->setVisible(false);
	}
}

void CtPlayView::updateAudioVol(int nVol) {
	if (isAbleDispAudioVol()) {
		// Vol値反映
		int i = 0;
		if (nVol > 27) {
			nVol = 27;
		}
		else if (nVol <= 0) {
			nVol = 1;
		}

		m_pVolumeVal[m_PreAudioVol - 1]->index(0);

		m_pVolumeVal[nVol - 1]->index(1);
		m_PreAudioVol = nVol;

		dispProgressBar(false);
		m_pAudioVolume->setVisible(true);
		setAlarm(CT_AUDIO_VOL_TIMER_ID, 1000 * 3);
	}
}

bool CtPlayView::isAbleDispAudioVol() {
	if (getWindowID() == Window_PlayView_RecCheck) {
		return false;
	}
	switch (APL_PARAM_GET_DATA(AplParamStatusPlay)) {
	case APL_SYS_PARAM_STATUS_PLAY_PLAYING:
	case APL_SYS_PARAM_STATUS_PLAY_FF_10:
	case APL_SYS_PARAM_STATUS_PLAY_FF_20:
	case APL_SYS_PARAM_STATUS_PLAY_REW_10:
	case APL_SYS_PARAM_STATUS_PLAY_REW_20:
		return true;
	default:
		return false;
		break;
	}
	return false;
}
