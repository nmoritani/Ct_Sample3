/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */

#include "CtContainerToggleDialog.h"

CtContainerToggleDialog::CtContainerToggleDialog(CtWindowID id) :
	m_WindowID(id),
	m_Toggle(0),
	m_CurSelect(0),
	m_bPressMmr(false)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerToggleDialog::~CtContainerToggleDialog()
{
	destroyContainer();
}
bool CtContainerToggleDialog::destroyContainer()
{
	return true;
}

CtLayout* CtContainerToggleDialog::createContainer()
{
	CtLayout* pLayout = createLayout();

	return pLayout;
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerToggleDialog::createLayout()
{
	/* Title */
	CtLayout* pTitle = createTitle();

	/* Toggle */
	CtLayout* pToggle = createToggle();

	/* Button */
	CtContainerCtrlButton* pButton = new CtContainerCtrlButton(true, true, true, true);

	/* Main */
	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout* pMain = new CtVLayout();
	pMain->addWidget(pTitle, 80);
	pMain->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pMain->addStretch(240);
	pMain->addWidget(pToggle, 80);
	pMain->addStretch(240);

	/* All */
	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(pButton);
	pAll->addWidget(pMain);

	executionUpdate();

	return pAll;
}
CtLayout* CtContainerToggleDialog::createTitle()
{

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	GDI_STRING_ID STR_ID = CtMenuInfoToggleDialog::getTitle(m_WindowID);

	CtLabel* pTitle = NULL;
	if (STR_ID != STR_ID_MAX_SIZE) {
		pTitle = new CtLabel(STR_ID, fSet);
	}
	else {
		pTitle = new CtLabel("", fSet);
	}
	CtVLayout* pV = new CtVLayout();
	pV->addStretch(12);
	pV->addWidget(pTitle, AlignLeft, 60);
	pV->addStretch(18);

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addWidget(pV, CtMargin(0, 15));


	return pLayout;
}

CtLayout* CtContainerToggleDialog::createToggle()
{
	return NULL;
}

//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerToggleDialog::handleButtonEvent(const CtEventButton& Button)
{
	if (Button.getPressType() == CtEventButton::Release) {
		if (Button.getWidgetID() == WidgetID_SET) { executionSet();  return true; }
	}

	if (Button.getPressType() == CtEventButton::Release ||
		Button.getPressType() == CtEventButton::RepeatPress) {
		if (Button.getWidgetID() == WidgetID_RET) { executionRet();  return true; }
	}

	if (Button.getPressType() == CtEventButton::ShortPress ||
		Button.getPressType() == CtEventButton::RepeatPress) {
		if (Button.getWidgetID() == WidgetID_UP) { executionUp();  return true; }
		if (Button.getWidgetID() == WidgetID_DOWN) { executionDown();  return true; }
	}

	if (Button.getPressType() == CtEventButton::ShortPress ||
		Button.getPressType() == CtEventButton::Release) {
		for (int i = 0; i < m_Toggle.size(); i++) {
			if (Button.getWidget() == m_Toggle[i].Button) {
				m_CurSelect = i;
				m_Toggle[m_CurSelect].Button->setPressed();
				m_Toggle[m_CurSelect].Button->cancelPressed();
				return true;
			}
		}
	}

	return false;
}
bool CtContainerToggleDialog::handleKeyEvent(const CtEventKey& Key)
{
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
	case CtEventKey::KeyCode_Reset:
		if (Key.getKeyAction() == CtEventKey::Release) {
			return executionReset();
		}
		break;
	case CtEventKey::KeyCode_Left:
		if (Key.getKeyAction() == CtEventKey::Press) {
			if (m_CurSelect > 0) {
				m_CurSelect--;
			}
		}
		break;
	case CtEventKey::KeyCode_Right:
		if (Key.getKeyAction() == CtEventKey::Press) {
			if (m_CurSelect < m_Toggle.size() - 1) {
				m_CurSelect++;
			}
		}
		break;

	default:
		break;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
void CtContainerToggleDialog::executionUpdate()
{
	executionCheckData();
	executionPrintDebug();
}
bool CtContainerToggleDialog::executionUp()
{
	int offset = m_Toggle[m_CurSelect].offset;

	m_Toggle[m_CurSelect].Data++;
	if (m_Toggle[m_CurSelect].Data > m_Toggle[m_CurSelect].Max) {
		m_Toggle[m_CurSelect].Data = offset;
	}

	m_Toggle[m_CurSelect].Stack->index(m_Toggle[m_CurSelect].Data - offset);
	executionUpdate();

	return true;
}
bool CtContainerToggleDialog::executionDown()
{
	int offset = m_Toggle[m_CurSelect].offset;

	m_Toggle[m_CurSelect].Data--;
	if (m_Toggle[m_CurSelect].Data < offset) {
		m_Toggle[m_CurSelect].Data = m_Toggle[m_CurSelect].Max;
	}

	m_Toggle[m_CurSelect].Stack->index(m_Toggle[m_CurSelect].Data - offset);
	executionUpdate();

	return true;
}
bool CtContainerToggleDialog::executionSet()
{
	CtWindow *pWindow = NULL;
	if (m_CurSelect == m_Toggle.size() - 1) {
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}
	else {
		m_CurSelect++;
		m_Toggle[m_CurSelect].Button->setPressed();
		m_Toggle[m_CurSelect].Button->cancelPressed();
	}

	return true;
}
bool CtContainerToggleDialog::executionRet()
{
	CtWindow *pWindow = NULL;

	CtEventInterface::requestFuncCmd(FuncID_WINDOW_CLOSE, pWindow);
	CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	return true;
}
bool CtContainerToggleDialog::executionReset()
{
	return false;
}

void CtContainerToggleDialog::executionCheckData()
{
	for (int i = 0; i < m_Toggle.size(); i++) {
		int Min = m_Toggle[i].offset;
		int Max = m_Toggle[i].Max;
		int Data = m_Toggle[i].Data;
		if (Data < Min || Max < Data) {
			m_Toggle[i].Data = Min;
		}
	}
}
void CtContainerToggleDialog::executionPrintDebug()
{
	CtDebugPrint(CtDbg, "-- ToggleData ----------------------\n");
	for (int i = 0; i < m_Toggle.size(); i++) {
		CtDebugPrint(CtDbg, "%d Date %5d Min %5d Max %5d\n", i, m_Toggle[i].Data, m_Toggle[i].offset, m_Toggle[i].Max);
	}
	CtDebugPrint(CtDbg, "------------------------------------\n");
}
