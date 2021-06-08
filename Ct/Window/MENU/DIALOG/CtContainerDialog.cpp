/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerDialog.h"

CtContainerDialog::CtContainerDialog(CtWindowID id, CtWindowContents *pContents) :
	m_WindowID(id),
	m_pContents(NULL)
{
	if (pContents != NULL) {
		m_pContents = new CtWindowContentsVersionDisp((CtWindowContentsVersionDisp&)*pContents);
	}
	memset(&m_Info, 0, sizeof(m_Info));
	m_SetParam.id = AplParamIdMax;
	m_SetParam.val = 0;
	setClassType(CtClassType_LayoutMain);
}
CtContainerDialog::~CtContainerDialog()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
	destroyContainer();
}

CtLayout* CtContainerDialog::createContainer()
{

	CtBuilderDialog* pBuilder = new CtBuilderDialog(m_WindowID);


	CtLayout *pAll = pBuilder->createContainer(m_pContents);    /* pgr0541 */


	delete pBuilder;


	return pAll;
}
bool CtContainerDialog::destroyContainer()
{
	return true;
}


//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerDialog::handleButtonEvent(const CtEventButton& Button)
{
	if (Button.getPressType() == CtEventButton::Release ||
		Button.getPressType() == CtEventButton::RepeatPress) {
		if (Button.getWidgetID() == WidgetID_RET) { return executionRet(); }
	}

	/* Release‚Å‚Ì‚Ýˆ— */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	if (Button.getWidgetID() == WidgetID_SET) { return executionSet(); }
	return false;
}
bool CtContainerDialog::handleKeyEvent(const CtEventKey& Key) {

	bool bRet = false;

	switch (Key.getKeyAction()) {
	case CtEventKey::Release:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
		case CtEventKey::KeyCode_GripUser1:
			bRet = executionRet();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return bRet;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
bool CtContainerDialog::executionSet()
{
	CtMenuInfoDialog::CtMenuDialogInfo *pInfo = CtMenuInfoDialog::getDialogInfo(m_WindowID);
	CtFuncID fancId = (pInfo != NULL) ? pInfo->set.funcid : FuncID_MAX;
	bool     bClose = (pInfo != NULL) ? pInfo->set.bClose : false;

	// AplParamXV
	if (m_SetParam.id != AplParamIdMax) {
		APL_PARAM_SET_DATA(m_SetParam.id, m_SetParam.val);
	}

	// FuncID
	if (fancId != FuncID_MAX) {
		CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, fancId, NULL);
	}

	// Window‘JˆÚ
	if (bClose) {
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}

	return false;
}

bool CtContainerDialog::executionRet()
{
	CtMenuInfoDialog::CtMenuDialogInfo *pInfo = CtMenuInfoDialog::getDialogInfo(m_WindowID);
	CtFuncID fancId = (pInfo != NULL) ? pInfo->ret.funcid : FuncID_MAX;
	bool     bClose = (pInfo != NULL) ? pInfo->ret.bClose : false;

	// FuncID
	if (fancId != FuncID_MAX) {
		CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, fancId, NULL);
	}

	// Window‘JˆÚ
	if (bClose) {
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}

	return true;
}
