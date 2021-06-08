/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerSpinBox.h"
//#include <stdlib.h>

CtContainerSpinBox::CtContainerSpinBox(CtWindowID id) :
	m_WindowID(id),
	m_Info(NULL),
	m_bPressMmr(false),
	m_Laval(CtWindowContentsPressLevel::Level1),
	m_bPressBtn(false),
	m_pParamBox(NULL),
	m_pCtrl(NULL),
	m_LabelSize(0)

{
	setClassType(CtClassType_LayoutMain);
}
CtContainerSpinBox::~CtContainerSpinBox()
{
	destroyContainer();
}

CtLayout* CtContainerSpinBox::createContainer()
{
	m_Info = CtMenuInfoSpinBox::getSpinBoxInfo(m_WindowID);

	CtLayout* pAll = createLayout();

	executionWfmSet();
	return pAll;
}
bool CtContainerSpinBox::destroyContainer()
{
	executionWfmRevert();
	executionRet(true);
	return true;
}
bool CtContainerSpinBox::startupContainer()
{
	checkInvalid();
	return true;
}
//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerSpinBox::createLayout()
{
	/* Title */
	CtColor color = CtMenuInfo::getMenuBackColor();

	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);
	pTitle->setColor(CtColor(color));

	/* Main */
	CtLayout* pMain = createMain();

	CtVLayout* pLayout = new CtVLayout();
	pLayout->addContainer(pTitle, 80);
	pLayout->addWidget(pMain, 560);

	m_pCtrl = new CtContainerCtrlButton(true, true, true, true);
	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_pCtrl);
	pAll->addWidget(pLayout);

	return pAll;
}

CtLayout* CtContainerSpinBox::createMain()
{
	CtLayout* pLayout = NULL;

	if (m_Info == NULL)return pLayout;

	switch (m_Info->Design) {
	case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar1:
	case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar2:
	case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar3:
		pLayout = createBar();
		break;
	case CtMenuInfoSpinBox::SpinBoxDesignType_Normal:
	case CtMenuInfoSpinBox::SpinBoxDesignType_Long:
	default:
		pLayout = createNormal();
		break;
	}

	return pLayout;
}

CtLayout* CtContainerSpinBox::createNormal()
{
	/* Label */
	CtLayout* pLabel = createLabel();

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(pLabel, AlignLeft, 960 - 126);

	return pMain;
}
CtLayout* CtContainerSpinBox::createBar()
{
	/* Ctrl */
//	m_pCtrl = new CtContainerCtrlButton(true, true, true, true);
	/* Label */
	CtLayout* pLabel = createLabel();
	/* LevelBar */
	CtContainerLevelBar* pLevelBar = new CtContainerLevelBar(m_Info->ParamId, m_Info->disp.max, m_Info->disp.min);
	pLevelBar->setLevelBarType(getLevelBarType());

	CtVLayout* pBox = new CtVLayout();
	pBox->addStretch(98);
	pBox->addWidget(pLabel, 66);
	pBox->addStretch(24);
	pBox->addContainer(pLevelBar, CtMargin(0, 8), 186);
	pBox->addStretch(186);

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(pBox, 78);
	pMain->addStretch(756);

	return pMain;
}
CtLayout* CtContainerSpinBox::createLabel()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_pParamBox = new CtParamBox(m_Info->ParamId);
	m_pParamBox->setFontSet(fSet);


	switch (m_Info->action) {
	case CtMenuInfoSpinBox::SpinBoxActionType_Table:
	{
		short size = 0;
		CtMenuInfoSpinBox::CtMenuSpinBoxTable* Table;
		Table = CtMenuInfoSpinBox::getSpinBoxTable(m_WindowID);
		m_pParamBox->setLabelType(CtParamLabel::TypeStacked);
		while (Table->WindowId == m_WindowID) {
			if (Table->strid != STR_ID_MAX_SIZE) {
				m_pParamBox->addLabel(Table->strid, fSet, Table->value);
				size = CtMenuInfo::getStringSize(Table->strid);
			}
			else {
				m_pParamBox->addLabel(Table->str, fSet, Table->value);
				size = CtMenuInfo::getStringSize(Table->strid);
			}
			if (size > m_LabelSize) {
				m_LabelSize = size;
			}
			Table++;
		}
	}
	break;
	case CtMenuInfoSpinBox::SpinBoxActionType_Value:
	{
		int min = CtMenuInfoSpinBox::getNumericMin(m_Info);
		m_pParamBox->setLabelType(CtParamLabel::TypeNumeric);
		m_pParamBox->setRange(min, m_Info->disp.max);
		m_pParamBox->setStep(m_Info->disp.step);
		m_pParamBox->setForm(m_Info->disp.str);
		m_pParamBox->setCorrection(0, m_Info->disp.coef);
	}
	break;
	default:
		break;
	}

	/* Layout */
	CtLayout *pLayout = createLabelLayout();
	pLayout->addWidget(m_pParamBox, CtMargin(5, 5), AlignCenter);

	return pLayout;

}
CtLayout* CtContainerSpinBox::createLabelLayout()
{
	CtLayout *pLayout = NULL;

	if (m_LabelSize != 0) {
		if (m_LabelSize < 114)
			m_LabelSize = 114; // 最小サイズ

		pLayout = new CtLayout(CtSize(m_LabelSize, 66));
		pLayout->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_1_ADJUST), AlignCenter);
	}
	else {
		switch (m_Info->Design) {
		case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar1:
		case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar2:
		case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar3:
		{
			pLayout = new CtLayout(CtSize(78, 66));
			pLayout->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_2_ADJUST), AlignCenter);
			break;
		}
		case CtMenuInfoSpinBox::SpinBoxDesignType_Long:
		{
			pLayout = new CtLayout(CtSize(114 * 2 + 14, 66));
			pLayout->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_1_ADJUST), AlignCenter);
			break;
		}
		case CtMenuInfoSpinBox::SpinBoxDesignType_Normal:
		default:
			pLayout = new CtLayout(CtSize(114, 66));
			pLayout->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_1_ADJUST), AlignCenter);
			break;
		}
	}

	return pLayout;
}
	

//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerSpinBox::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;

	switch (Button.getTimLv()) {
	case CtEventButton::Level_Default:
	case CtEventButton::Level1:
		m_Laval = CtWindowContentsPressLevel::Level1;
		break;
	case CtEventButton::Level2:
		m_Laval = CtWindowContentsPressLevel::Level2;
		break;
	case CtEventButton::Level3:
		m_Laval = CtWindowContentsPressLevel::Level3;
		break;
	case CtEventButton::Level4:
	default:
		m_Laval = CtWindowContentsPressLevel::Level4;
		break;
	}

	switch (Button.getWidgetID()){
	case WidgetID_UP:
		/* PressとRepeatPress時のみ制御 */
		if ((Button.getPressType() == CtEventButton::ShortPress)||
			(Button.getPressType() == CtEventButton::RepeatPress)) {
			return executionUp();
		}

		break;
	case WidgetID_DOWN:
		/* PressとRepeatPress時のみ制御 */
		if ((Button.getPressType() == CtEventButton::ShortPress) ||
			(Button.getPressType() == CtEventButton::RepeatPress)) {
			return executionDown();
		}
		break;
	case WidgetID_SET:
		/* Releaseでのみ処理 */
		if (Button.getPressType() == CtEventButton::Release) {
			bRet = executionSet();
			return bRet;
		}
		break;
	case WidgetID_RET:
		/* ReleaseおよびRepeat でのみ処理 */
		if (Button.getPressType() == CtEventButton::Release ||
			Button.getPressType() == CtEventButton::RepeatPress) {
			bRet = executionRet();
			return bRet;
		}
		break;
	default:
		break;
	}

	return bRet;
}
bool CtContainerSpinBox::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getTimLv()){
	case CtEventKey::Level_Default:
	case CtEventKey::Level1:
		m_Laval = CtWindowContentsPressLevel::Level1;
		break;
	case CtEventKey::Level2:
		m_Laval = CtWindowContentsPressLevel::Level2;
		break;
	case CtEventKey::Level3:
		m_Laval = CtWindowContentsPressLevel::Level3;
		break;
	case CtEventKey::Level4:
	default:
		m_Laval = CtWindowContentsPressLevel::Level4;
		break;
	}

	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_MmrPlus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			return executionUp();
		}
		break;
	case CtEventKey::KeyCode_DialPressUp:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			m_bPressMmr = true;
			return executionUp();
		}
		break;
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_MmrMinus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			return executionDown();
		}
		break;
	case CtEventKey::KeyCode_DialPressDown:
		m_bPressMmr = true;
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			return executionDown();
		}
		break;
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Release) {
			executionRet();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Enter:
		if (Key.getKeyAction() == CtEventKey::Release) {
			return executionSet();
		}
		break;
	case CtEventKey::KeyCode_ManualFunction:
		if (Key.getKeyAction() == CtEventKey::Release) {
			if (m_bPressMmr != true) {
				return executionSet();
			}
			m_bPressMmr = false;
		}
		break;
	default:
		break;
	}
	return false;

}
bool CtContainerSpinBox::handleParamEvent(const CtEventParam& Param)
{
	return false;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
void CtContainerSpinBox::executionWfmSet()
{
	switch (m_Info->Wfm) {													/* parasoft-suppress BD-PB-NP */
	case CtMenuInfoSpinBox::SpinBoxWfmMode_WAVE:
		APL_PARAM_SET_CACHE_DATA(AplParamWFMMode, APL_SYS_PARAM_WFM_MODE_WAVE);
		APL_PARAM_SET_CACHE_DATA(AplParamWFM, APL_SYS_PARAM_SWITCH_ON);
		break;
	case CtMenuInfoSpinBox::SpinBoxWfmMode_VECTOR:
		APL_PARAM_SET_CACHE_DATA(AplParamWFMMode, APL_SYS_PARAM_WFM_MODE_VECTOR);
		APL_PARAM_SET_CACHE_DATA(AplParamWFM, APL_SYS_PARAM_SWITCH_ON);
		break;
	case CtMenuInfoSpinBox::SpinBoxWfmMode_ON:
		APL_PARAM_SET_CACHE_DATA(AplParamWFM, APL_SYS_PARAM_SWITCH_ON);
		break;
	case CtMenuInfoSpinBox::SpinBoxWfmMode_OFF:
	default:
		break;
	}
}
void CtContainerSpinBox::executionWfmRevert()
{
	/* とりあえず戻す(RecViewの復帰はAPL側で実施) */
	APL_PARAM_SET_CACHE_DATA(AplParamWFM, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamWFMMode, APL_PARAM_GET_MASTER_DATA(AplParamWFMMode));
}

bool CtContainerSpinBox::executionUp()
{
	if (m_pParamBox == NULL)return false;
	m_pParamBox->setStep(getStep());
	m_pParamBox->inc();
	checkInvalid();
	return true;
}

bool CtContainerSpinBox::executionDown()
{
	if (m_pParamBox == NULL)return false;
	m_pParamBox->setStep(getStep());
	m_pParamBox->dec();
	checkInvalid();
	return true;
}

bool CtContainerSpinBox::executionRet(bool bDestructor)
{
	if (m_pParamBox == NULL)return false;

	if (m_bPressBtn == false) {
		m_pParamBox->resetParam();

		if (bDestructor == false) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		}
	}

	m_bPressBtn = true;
	return true;
}

bool CtContainerSpinBox::executionSet()
{
	if (m_pParamBox == NULL)return false;

	m_bPressBtn = true;

	m_pParamBox->setParam();

	CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);

	return true;
}
void CtContainerSpinBox::checkInvalid()
{
	m_pCtrl->setInvalid(WidgetID_UP,   !m_pParamBox->inc(0,true));
	m_pCtrl->setInvalid(WidgetID_DOWN, !m_pParamBox->dec(0,true));
}
int CtContainerSpinBox::getStep()
{
	if (m_Info == NULL) { return 1; }
	switch (m_Laval) {
	case CtWindowContentsPressLevel::Level1:
		return m_Info->disp.step * 1;
	case CtWindowContentsPressLevel::Level2:
		return m_Info->disp.step * 2;
	case CtWindowContentsPressLevel::Level3:
		return m_Info->disp.step * 5;
	case CtWindowContentsPressLevel::Level4:
		return m_Info->disp.step * 10;
	default:
		break;
	}
	return m_Info->disp.step;
}
CtContainerLevelBar::LevelBarType CtContainerSpinBox::getLevelBarType() 
{
	switch (m_Info->Design) {
	case CtMenuInfoSpinBox::SpinBoxDesignType_LevelBar3:
		return CtContainerLevelBar::LevelBarType_Short;
	default:
		break;
	}
	return CtContainerLevelBar::LevelBarType_Default;
}
