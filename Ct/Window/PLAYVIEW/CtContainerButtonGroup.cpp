#include "CtContainerButtonGroup.h"

CtContainerButtonGroup::CtContainerButtonGroup() :
	m_pFastForward(NULL),
	m_pRewind(NULL),
	m_pStop(NULL),
	m_pPlayPause(NULL),
	m_pFFStackLabel(NULL),
	m_pRwStackLabel(NULL),
	m_pContents(NULL)
{
	setClassType(CtClassType_LayoutMain);
}

CtContainerButtonGroup::~CtContainerButtonGroup() {
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
}

CtLayout* CtContainerButtonGroup::createContainer() {
	CtLabel* pLabel = NULL;

	CtHLayout* pBtnArea = new CtHLayout();
	pBtnArea->addStretch(14);

	// ButtonGroup
	m_pBtnGroup = new CtVLayout();
	{

		// None
		m_pBtnGroup->addStretch(30);

		// FastForward
		m_pFFStackLabel = new CtStackLabel();
		{
			m_pFFStackLabel->addLabel(new CtLabel(IC_OSD_KEYTOP_FF), 0);
			m_pFFStackLabel->addLabel(new CtLabel(IC_OSD_KEYTOP_FRAME_ADVANCE), 1);
			m_pFFStackLabel->index(0);
		}
		m_pFastForward = new CtToggleButton(CtSize(80, 66), m_pFFStackLabel);

		m_pBtnGroup->addWidget(m_pFastForward, AlignCenter, 66);

		// None
		m_pBtnGroup->addStretch(56);

		// Rewind
		m_pRwStackLabel = new CtStackLabel();
		m_pRwStackLabel->addLabel(new CtLabel(IC_OSD_KEYTOP_REW), 0);
		m_pRwStackLabel->addLabel(new CtLabel(IC_OSD_KEYTOP_FRAME_RETURN), 1);
		m_pRwStackLabel->index(0);

		m_pRewind = new CtToggleButton(CtSize(80, 66), m_pRwStackLabel);
		m_pBtnGroup->addWidget(m_pRewind, AlignCenter, 66);

		// None
		m_pBtnGroup->addStretch(56);

		// Stop
		m_pStop = new CtToggleButton(new CtLabel(IC_OSD_KEYTOP_STOP));

		m_pBtnGroup->addWidget(m_pStop, AlignCenter, 66);

		// None
		m_pBtnGroup->addStretch(56);

		// PlayPause
		m_pPlayPause = new CtToggleButton(new CtLabel(IC_OSD_KEYTOP_PLAY_STILL));
		m_pBtnGroup->addWidget(m_pPlayPause, AlignCenter, 66);

		m_pBtnGroup->addStretch(18);
	}
	pBtnArea->addWidget(m_pBtnGroup, 78);
	pBtnArea->addStretch(772);
	pBtnArea->addStretch(4);

	// Cap
	CtVLayout *pLayoutCap = new CtVLayout();
	m_pCapture = new CtToggleButton(CtSize(80, 66));
	m_pCapture->setTop(new CtLabel(IC_OSD_CAP));
	pLayoutCap->addWidget(m_pCapture, AlignCenter);
	pBtnArea->addWidget(pLayoutCap, 78);

	pBtnArea->addStretch(14);
	return pBtnArea;
}

bool CtContainerButtonGroup::startupContainer() {
	updateCapState(APL_PARAM_GET_DATA(AplParamPlayPhotoShot));
	updateStatusPlay();
	return true;
}

bool CtContainerButtonGroup::destroyContainer() {
	return true;
}

bool CtContainerButtonGroup::isBtnsContain(const CtPosition& Pos) {
	if (m_pBtnGroup->isContains(Pos, getScreenSel()) == true) return true;
	if (m_pCapture->isContains(Pos, getScreenSel()) == true) return true;
	return false;
}

bool CtContainerButtonGroup::handleParamEvent(const CtEventParam& Param) {
	bool isRedraw = true;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamStatusPlay:
	case AplParamOutIndicatorPlayBackStatus:
	case AplParamLcdIndicatorPlayBackStatus:
		updateStatusPlay();
		isRedraw = true;
		break;
	case AplParamPlayPhotoShot:
		updateCapState(int_Data);
		isRedraw = true;
		break;
	default:
		isRedraw = false;
		break;
	}
	return isRedraw;
}

void CtContainerButtonGroup::updateStatusPlay()
{
	// Label貼り換え
	switch (APL_PARAM_GET_DATA(AplParamStatusPlay)) {
	case  APL_SYS_PARAM_STATUS_PLAY_PLAYING:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_10:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_20:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_10:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_20:
		m_pFFStackLabel->index(0);	//IC_OSD_KEYTOP_FF
		m_pRwStackLabel->index(0);	//IC_OSD_KEYTOP_REW
		break;
	case APL_SYS_PARAM_STATUS_PLAY_STILL:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_TOP:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_LAST:
	case APL_SYS_PARAM_STATUS_PLAY_STOP:
	case APL_SYS_PARAM_STATUS_PLAY_FF_SLOW:
	case APL_SYS_PARAM_STATUS_PLAY_REW_SLOW:
		m_pFFStackLabel->index(1);	//IC_OSD_KEYTOP_FRAME_ADVANCE
		m_pRwStackLabel->index(1);	//IC_OSD_KEYTOP_FRAME_RETURN
		break;
	default:
		m_pFFStackLabel->index(0);
		m_pRwStackLabel->index(0);
		break;
		//return;
	}

	m_pFastForward->setSelect(false);
	m_pRewind->setSelect(false);
	m_pStop->setSelect(false);
	m_pPlayPause->setSelect(false);

	m_pRewind->setHold(false);
	m_pPlayPause->setHold(false);
	m_pFastForward->setHold(false);
	m_pStop->setHold(false);

	// Button色設定
	switch (APL_PARAM_GET_DATA(AplParamStatusPlay)) {
	case  APL_SYS_PARAM_STATUS_PLAY_PLAYING:
		m_pPlayPause->setSelect(true);
		m_pPlayPause->setHold(true);
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_FF_SLOW:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_10:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_20:
		m_pFastForward->setSelect(true);
		m_pFastForward->setHold(true);
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_REW_SLOW:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_10:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_20:
		m_pRewind->setSelect(true);
		m_pRewind->setHold(true);
		
		break;
	case APL_SYS_PARAM_STATUS_PLAY_STOP:
		m_pStop->setSelect(true);
		m_pStop->setHold(true);
		break;
	case APL_SYS_PARAM_STATUS_PLAY_STILL:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_TOP:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_LAST:
		// 通常ボタンに切り替え
		break;
	default:
		return;
	}
}

bool CtContainerButtonGroup::updateCapState(int int_Data) {
	if (m_pCapture == NULL) return false;

	switch (int_Data) {
	case  APL_SYS_PARAM_PLAY_PHOTO_SHOT_VARID:
		m_pCapture->setSelect(false);
		return true;
		break;
	case APL_SYS_PARAM_PLAY_PHOTO_SHOT_RECORDING:
		m_pCapture->setSelect(true);
		m_pCapture->setVisible(true);
		return true;
		break;
	case APL_SYS_PARAM_PLAY_PHOTO_SHOT_INVARID:
	default:
		return m_pCapture->setVisible(false);
		break;
	}
}

bool CtContainerButtonGroup::handleButtonEvent(const CtEventButton& Button)
{
	CtFuncID func = FuncID_MAX;
	CtWindowContentsPlayControlState::PressType type = CtWindowContentsPlayControlState::Invalid;

	if (m_pCapture != NULL && Button.getWidget() == m_pCapture) {
		func = FuncID_CAPTURE;
	}else if (m_pFastForward != NULL && Button.getWidget() == m_pFastForward) {
		func = FuncID_FORWARD;
	}
	else if (m_pRewind != NULL && Button.getWidget() == m_pRewind) {
		func = FuncID_BACKWARD;
	}
	else if (m_pStop != NULL && Button.getWidget() == m_pStop) {
		func = FuncID_STOP;
	}
	else if (m_pPlayPause != NULL && Button.getWidget() == m_pPlayPause) {
		func = FuncID_PLAYPAUSE;
	}
	else {
		return false;
	}
	switch (Button.getPressType()) {
	case CtEventButton::PressInvalid:
		type = CtWindowContentsPlayControlState::Invalid;
		return false;
	case CtEventButton::ShortPress:
		type = CtWindowContentsPlayControlState::Press;
		break;
	case CtEventButton::LongPress:
		type = CtWindowContentsPlayControlState::LongPress;
		break;
	case CtEventButton::RepeatPress:
		type = CtWindowContentsPlayControlState::Repeat;
		break;
	case CtEventButton::Release:
		type = CtWindowContentsPlayControlState::Release;
		break;
	default:
		return false;
	}
	if (m_pContents == NULL) {
		m_pContents = new CtWindowContentsPlayControlState(Window_PlayView);
	}
	m_pContents->setPressType(type);
	CtEventInterface::requestFuncCmd(ScreenAll, Window_PlayView, func, m_pContents);
	
	return false;
}

bool CtContainerButtonGroup::handleKeyEvent(const CtEventKey& Key) {
	bool bRet = false;
	CtEventKey::KeyCode KeyCode = Key.getKeyCode();

	/* 表示されてない時はカーソル移動させない */
	if (getLayout()->isVisible()) {
		
	}

	return bRet;
}

CtWidget* CtContainerButtonGroup::getDefaultFocusWidget()
{
	switch (APL_PARAM_GET_DATA(AplParamStatusPlay)) {
	case  APL_SYS_PARAM_STATUS_PLAY_PLAYING:
		return m_pPlayPause;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_FF_SLOW:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_10:
	case  APL_SYS_PARAM_STATUS_PLAY_FF_20:
		return m_pFastForward;
		break;
	case  APL_SYS_PARAM_STATUS_PLAY_REW_SLOW:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_10:
	case  APL_SYS_PARAM_STATUS_PLAY_REW_20:
		return m_pRewind;
		break;
	case APL_SYS_PARAM_STATUS_PLAY_STOP:
		return m_pStop;
		break;
	case APL_SYS_PARAM_STATUS_PLAY_STILL:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_TOP:
	case APL_SYS_PARAM_STATUS_PLAY_STILL_LAST:
	default:
		return m_pPlayPause;
	}
}

