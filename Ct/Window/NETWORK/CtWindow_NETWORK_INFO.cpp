/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK_INFO
 */


#include "CtWindow_NETWORK_INFO.h"

CtWindow_NETWORK_INFO::CtWindow_NETWORK_INFO( CtWindowContents* pContents ) :
    m_pContents(NULL),
	m_pCtrl(NULL)
{
	for (int i = 0; i < LINE_NUM; i++) {
		m_pLabel[i] = NULL;
	}
	setClassType(CtClassType_WindowNETWORK_INFO);
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsNetworkInformation((CtWindowContentsNetworkInformation&)*pContents);
    }
}
CtWindow_NETWORK_INFO::~CtWindow_NETWORK_INFO()
{
	if( m_pContents != NULL ){
		delete m_pContents;
		m_pContents = NULL;
	}
}
bool CtWindow_NETWORK_INFO::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_NETWORK_INFO::createWindow()
{
	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(getWindowID());

	/* List */
	CtLayout* pList = createNetworkInfo();

	/* Ctrl */
	m_pCtrl = new CtContainerCtrlButton(false, true, true, true);
	m_pCtrl->setTrans(true);
	m_pCtrl->setTransColor(true);

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(pList, 960 - 126);

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addContainer(pTitle, 80);
	pLayout->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pLayout->addWidget(pMain, 640 - 80);

	CtLayout* pAll = new CtLayout(CtColor(ColorRGBA, 0x000000B2, NULL));
	pAll->addContainer(m_pCtrl);
	pAll->addWidget(pLayout);
	
	CtWindow* pWin = new CtWindow();
	pWin->addWidget(pAll);

	updateWindow();

	return pWin;
}

CtLayout* CtWindow_NETWORK_INFO::createNetworkInfo()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSet.setSize(34);
	CtVLayout* pLayout = new CtVLayout();

	for(int i = 0; i < LINE_NUM; i++){
		m_pLabel[i] = new CtLabel("", fSet);
		pLayout->addWidget(m_pLabel[i], AlignLeft, 1);
	}

	return pLayout;
}

void CtWindow_NETWORK_INFO::updateWindow()
{
	if (m_pContents == NULL) {
		return;
	}
	CtWindowContentsNetworkInformation::CtInformationTextInfo &info = m_pContents->getInformationTextInfo();

	char str[80] = { 0 };
	char infoStr[CtWindowContentsNetworkInformation::CT_NETWORK_INFORMATION_TEXT_MAX] = { 0 };
	int strNum = 0;
	int labelNum = 0;

	sprintf(infoStr, "%s", info.InformationText);

	for (unsigned int i = 0; i < strlen(infoStr); i++) {
		if (labelNum >= LINE_NUM) {
			break;
		}
		else if ((infoStr[i] == '\n') || (infoStr[i] == '\r') || (infoStr[i + 1] == NULL)) {
			if ((infoStr[i] != '\n') && (infoStr[i] != '\r')) {
				str[strNum] = infoStr[i];
			}
			m_pLabel[labelNum]->setText(str);
			strNum = 0;
			labelNum++;
			memset(str, '\0', sizeof(str));
			str[0] = ' ';
		}
		else {
			str[strNum++] = infoStr[i];
		}
	}

	if (labelNum < LINE_NUM) {
		for (int i = labelNum; i < LINE_NUM; i++) {
			m_pLabel[i]->setText(" ");
		}
	}

	m_pCtrl->setInvalid(WidgetID_UP, info.IsValidUpButton);
	m_pCtrl->setInvalid(WidgetID_DOWN, info.IsValidDownButton);

}
bool CtWindow_NETWORK_INFO::updateContents()
{
	updateWindow();
	return true;
}


bool CtWindow_NETWORK_INFO::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;
	
    if (pContents != NULL) {
    	if( m_pContents != NULL ){
    		delete m_pContents;
    		m_pContents = NULL;
    	}
        m_pContents = new CtWindowContentsNetworkInformation((CtWindowContentsNetworkInformation&)*pContents);
    }
	
    return mRet;
}
bool CtWindow_NETWORK_INFO::handleButtonEvent(const CtEventButton& Button)
{
	bool bFlag = false;

	/* ReleaseÇ≈ÇÃÇ›èàóù */
	if ((Button.getPressType() != CtEventButton::Release) &&
		(Button.getPressType() != CtEventButton::RepeatPress)) {
		return false;
	}

	switch (Button.getWidgetID()) {
	case WidgetID_UP:
		executionUp();
		bFlag = true;
		break;
	case WidgetID_DOWN:
		executionDown();
		bFlag = true;
		break;
	case WidgetID_RET:
		executionRet();
		bFlag = true;
		break;
	default:
		break;
	}
	return bFlag;
}

bool CtWindow_NETWORK_INFO::handleKeyEvent(const CtEventKey& Key)
{

	bool bRet = false;
	CtWindow* pWin = NULL;

	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_MmrPlus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			executionUp();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressUp:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			executionUp();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_MmrMinus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			executionDown();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressDown:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			executionDown();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Release) {
			executionRet();
			return true;
		}
		break;
	default:
		break;
	}

	return bRet;
}
bool CtWindow_NETWORK_INFO::executionUp()
{
	CtWindow* pWindow = NULL;
	CtEventInterface::requestFuncCmd(getScreenSel(), getWindowID(), FuncID_UP, NULL);
	return true;
}

bool CtWindow_NETWORK_INFO::executionDown()
{
	CtWindow* pWindow = NULL;
	CtEventInterface::requestFuncCmd(getScreenSel(), getWindowID(), FuncID_DOWN, NULL);
	return true;
}

bool CtWindow_NETWORK_INFO::executionRet()
{
	CtWindow* pWindow = NULL;
	CtEventInterface::requestFuncCmd(getScreenSel(), getWindowID(), FuncID_RET, NULL);
	CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
	return true;
}
