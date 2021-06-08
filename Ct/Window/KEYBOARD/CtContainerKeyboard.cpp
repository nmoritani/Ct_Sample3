/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerKeyboard.h"
#include <stdlib.h>

CtContainerKeyboard::CtContainerKeyboard(CtWindowID id) :
	m_WindowID(id),
	m_pFileContents(NULL),
	m_pText(NULL),
	m_pCaps(NULL),
	m_pBS(NULL),
	m_pRet(NULL),
	m_pKigou(NULL),
	m_pSpace(NULL),
	m_pLeft(NULL),
	m_pRight(NULL),
	m_pEnter(NULL),
	m_Info(NULL)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerKeyboard::CtContainerKeyboard(CtWindowID id, CtWindowContents* pContents) :
	m_WindowID(id),
	m_pFileContents(NULL),
	m_pText(NULL),
	m_pCaps(NULL),
	m_pBS(NULL),
	m_pRet(NULL),
	m_pKigou(NULL),
	m_pSpace(NULL),
	m_pLeft(NULL),
	m_pRight(NULL),
	m_pEnter(NULL),
	m_Info(NULL)
{
	setClassType(CtClassType_LayoutMain);

	if (pContents != NULL) {
		m_pFileContents = new CtWindowContentsFileInfo((CtWindowContentsFileInfo&)*pContents);
	}
}
CtContainerKeyboard::~CtContainerKeyboard()
{
	if (m_pFileContents != NULL) {
		delete m_pFileContents;
		m_pFileContents = NULL;
	}
}
bool CtContainerKeyboard::destroyContainer()
{
	return true;
}

CtLayout* CtContainerKeyboard::createContainer()
{
	m_Info = CtKeyboardInfo::getKeyboardInfo(m_WindowID);
	if (m_Info == NULL) {
		return new CtLayout();
	}

	CtLayout* pAll = createLayout();

	switch (m_Info->Type) {
	case CtKeyboardInfo::KeyboardType_Number:
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
		m_pKeyboard->index(2);
		break;
	default:
		m_pKeyboard->index(0);
		break;
	}
	return pAll;
}
bool CtContainerKeyboard::startupContainer() {
	return true;
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerKeyboard::createLayout()
{
	CtBuilderKeyboard* pBuilder = new CtBuilderKeyboard(m_WindowID);
	pBuilder->setContents(m_pFileContents);

	CtLayout* pAll = pBuilder->createLayout();

	m_pText        = pBuilder->getTextField();
	m_pKeyboard    = pBuilder->getKeyboard();
	m_pCaps        = pBuilder->getCaps();
	m_pBS          = pBuilder->getBS();
	m_pRet         = pBuilder->getRet();
	m_pKigou       = pBuilder->getKigou();
	m_pSpace       = pBuilder->getSpace();
	m_pLeft        = pBuilder->getLeft();
	m_pRight       = pBuilder->getRight();
	m_pEnter       = pBuilder->getEnter();

	delete pBuilder;

	setEnterValid();

	return pAll;
}

//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerKeyboard::handleButtonEvent(const CtEventButton& Button)
{
	CtWindow *pWindow = NULL;

	if (Button.getPressType() == CtEventButton::PressInvalid)
		return false;

	if (Button.getWidget() == m_pRet) {
		if (Button.getPressType() == CtEventButton::Release ||
			Button.getPressType() == CtEventButton::RepeatPress) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		}
	}

	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	if (Button.getWidget() == m_pCaps) {
		// キーボード切替
		updateKeyBoard();
	}
	else if (Button.getWidget() == m_pKigou) {
		// 記号表示
			m_pCaps->setSelect(false);
			updateKeyBoard();
	}
	else if (Button.getWidget() == m_pSpace) {
		if ((int)strlen(m_pText->getString()) < m_Info->Size) {
			m_pText->insertChar(' ');
		}
	}
	else if (Button.getWidget() == m_pLeft) {
		m_pText->backwardCursor();
	}
	else if (Button.getWidget() == m_pRight) {
		m_pText->forwardCursor();
	}
	else if (Button.getWidget() == m_pBS) {
		m_pText->backspaceChar();
	}
	else if (Button.getWidget() == m_pEnter) {
		pushEnter();
		link();
	}
	else {
		// TextFieldへ文字列格納
		unsigned short * str;
		CtButton* pButton = (CtButton*)Button.getWidget();

		if (pButton->isLabel() == true) {
			if ((str = static_cast<CtLabel*>(pButton)->getText()) != NULL) {
				if ((int)strlen(m_pText->getString()) < m_Info->Size) {
					m_pText->insertChar((char)(str[0] & 0xff));
				}
			}
		}
	}
	setEnterValid();
	return true;
}
bool CtContainerKeyboard::handleKeyEvent(const CtEventKey& Key) {

	bool bRet = true;
	CtWindow *pWindow = NULL;

	switch (Key.getKeyAction()) {
	case CtEventKey::Release:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
		case CtEventKey::KeyCode_GripUser1:
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		case CtEventKey::KeyCode_Reset:
		{
			char* pStr = m_pText->getString();
			for (int len = 0; pStr[len]; len++) {
				m_pText->deleteChar();
			}
			setEnterValid();
			return true;
		}
		default:
			bRet = false;
			break;
		}
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
void CtContainerKeyboard::updateKeyBoard()
{
	if (m_pKigou->isSelected() == true) {
		if (m_pCaps->isSelected() == true) {
			m_pKeyboard->index(3);
		}
		else {
			m_pKeyboard->index(2);
		}
	}
	else {
		if (m_pCaps->isSelected() == true) {
			m_pKeyboard->index(1);
		}
		else {
			m_pKeyboard->index(0);
		}
	}
	
	return;
}
void CtContainerKeyboard::setEnterValid()
{
	if (true == isValid()) {
		m_pEnter->setInvalid(false);
	}
	else {
		m_pEnter->setInvalid(true);
	}
}
void CtContainerKeyboard::pushEnter()
{
	switch (m_Info->Text) {
	case CtKeyboardInfo::TextType_Default:
	case CtKeyboardInfo::TextType_File:
	case CtKeyboardInfo::TextType_None:
	{
		unsigned char tmp_str[520];
		memset(tmp_str, 0, sizeof(tmp_str));
		APL_PARAM_GET_DATA_AREA(m_Info->ParamId, (unsigned char *)tmp_str, m_Info->Size);
		if (memcmp(tmp_str, (unsigned char *)m_pText->getString(), m_Info->Size) != 0) {
			APL_PARAM_SET_DATA_AREA(m_Info->ParamId, (unsigned char *)m_pText->getString(), m_Info->Size);
		}
		else {
			APL_PARAM_EXEC_FAKE_UPDATE(m_Info->ParamId);
		}
		break;
	}
	case CtKeyboardInfo::TextType_Number:
	case CtKeyboardInfo::TextType_Number0:
	{
		int value = atoi(m_pText->getString());
		APL_PARAM_SET_DATA(m_Info->ParamId, value);
		break;
	}
	case CtKeyboardInfo::TextType_Ip:
	{
		char *strTextField = m_pText->getString();
		unsigned char IP[4];
		memset(IP, 0, sizeof(IP));
		unsigned char tmp_str[100];
		memset(tmp_str, 0, sizeof(tmp_str));
		/* char[4]に変換 */

		char* temp;
		temp = strtok(strTextField, ".");
		IP[0] = (unsigned char)atoi(temp != NULL ? temp : "000");
		temp = strtok(NULL, ".");
		IP[1] = (unsigned char)atoi(temp != NULL ? temp : "000");
		temp = strtok(NULL, ".");
		IP[2] = (unsigned char)atoi(temp != NULL ? temp : "000");
		temp = strtok(NULL, ".");
		IP[3] = (unsigned char)atoi(temp != NULL ? temp : "000");

		APL_PARAM_GET_DATA_AREA(m_Info->ParamId, (unsigned char *)tmp_str, 4);
		if (memcmp(tmp_str, IP, 4) != 0) {
			APL_PARAM_SET_DATA_AREA(m_Info->ParamId, (unsigned char *)IP, 4);
		}
		else {
			APL_PARAM_EXEC_FAKE_UPDATE(m_Info->ParamId);
		}
		break;
	}
	case CtKeyboardInfo::TextType_Special:
	{
		unsigned char tmp_str[100];
		memset(tmp_str, 0, sizeof(tmp_str));
		AplParamEepromId tmpeep = AplParamSceneFileName1;
		switch (APL_PARAM_GET_DATA(AplParamSceneMode)) {
		case APL_SYS_PARAM_SCENE_MODE_1:   tmpeep = AplParamSceneFileName1;   break;
		case APL_SYS_PARAM_SCENE_MODE_2:   tmpeep = AplParamSceneFileName2;   break;
		case APL_SYS_PARAM_SCENE_MODE_3:   tmpeep = AplParamSceneFileName3;   break;
		case APL_SYS_PARAM_SCENE_MODE_4:   tmpeep = AplParamSceneFileName4;   break;
		case APL_SYS_PARAM_SCENE_MODE_5:   tmpeep = AplParamSceneFileName5;   break;
		case APL_SYS_PARAM_SCENE_MODE_6:   tmpeep = AplParamSceneFileName6;   break;
		default:   break;
		}
		APL_PARAM_GET_DATA_AREA(tmpeep, (unsigned char *)tmp_str, m_Info->Size);
		if (memcmp(tmp_str, (unsigned char *)m_pText->getString(), m_Info->Size) != 0) {
			APL_PARAM_SET_DATA_AREA(tmpeep, (unsigned char *)m_pText->getString(), m_Info->Size);
		}
		else {
			APL_PARAM_EXEC_FAKE_UPDATE(tmpeep);
		}
		break;
	}
	default:
		break;
	}
}
void CtContainerKeyboard::link()
{
	switch (m_Info->action.Type) {
	case CtKeyboardInfo::ActionType_Special:
	{
		if (m_pFileContents != NULL) {
			char fileName[8] = { 0 };
			char nameChar[8] = { 0 };
			CtWindowID overwriteId = WindowID_MAX;
			CtWindowID sureId = WindowID_MAX;

			switch (m_Info->WindowId) {
			case Window_Menu_SCENE_FILE_SAVE_KEYBOARD:
				overwriteId = Window_Menu_SCENE_FILE_SAVE_OVERWRITE;
				sureId = Window_Menu_SCENE_FILE_SAVE_CONFIRM;
				break;
			case Window_Menu_SETUP_FILE_SAVE_KEYBOARD:
				overwriteId = Window_Menu_SETUP_FILE_SAVE_OVERWRITE;
				sureId = Window_Menu_SETUP_FILE_SAVE_CONFIRM;
				break;
			default:
				break;
			}

			CtWindowContentsFileInfo::FileInfoList &list = m_pFileContents->getFileInfoList();
			CtWindowContentsFileInfo::FileInfoListItr Itr;
			Itr = m_pFileContents->getFileInfoList().begin();
			APL_PARAM_GET_DATA_AREA(m_Info->ParamId, (unsigned char *)nameChar, m_Info->Size);
			for (int i = 0; i < list.size(); i++) {
				if (list[i] != NULL) {
					memcpy(fileName, (*(Itr + (unsigned long)i))->getFileInfo().FileName, 8);
					if (strncmp(fileName, nameChar, 8) == 0) {
						/* OVERWRITE */
						CtEventInterface::requestWindowCmd(CtEventWindow::Change, overwriteId, m_pFileContents);
						break;
					}
					if (i == (list.size() - 1)) {
						/* SURE */
						CtEventInterface::requestWindowCmd(CtEventWindow::Change, sureId, m_pFileContents);
						break;
					}
				}
			}
		}
	}
	break;
	case CtKeyboardInfo::ActionType_Function:
		CtEventInterface::requestFuncCmd(m_Info->action.FuncID, m_pEnter->getWindow());
		break;
	case CtKeyboardInfo::ActionType_Transfer:
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)m_Info->action.OpenType, m_Info->action.WindowId);
		break;
	case CtKeyboardInfo::ActionType_Default:
	default:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		break;
	}
}
bool CtContainerKeyboard::isValid()
{
	bool flag = true;
	char *strTextField = m_pText->getString();
	int len = strlen(strTextField);

	switch (m_Info->Exclusion) {
	case CtKeyboardInfo::ExcclusionType_Ip:
	{
		flag = checkAddressFormat();
	}
	break;
	case CtKeyboardInfo::ExcclusionType_Number:
	{
		int num = 0;
		for (int i = 0; i < len; i++) {
			num = num * 10 + atoi(&strTextField[i]);
		}
		if (0 == num) {
			flag = false;
		}
		break;
	}
	case CtKeyboardInfo::ExcclusionType_PassWord:
	{
		if (len < 8) {
			flag = false;
		}
		break;
	}
	case CtKeyboardInfo::ExcclusionType_UserPassWord:
	{
		if (len < 6) {
			flag = false;
		}
		break;
	}
	case CtKeyboardInfo::ExcclusionType_Port:
	{
		int num = atoi(strTextField);

		if (0 > num || num > 65535) {
			flag = false;
		}
		break;
	}
	case CtKeyboardInfo::ExcclusionType_Range:
	{
		int num = atoi(strTextField);

		if (0 > num || num > 128 || len == 0) {
			flag = false;
		}
		break;
	}
	case CtKeyboardInfo::ExcclusionType_Freedom:
	{
		flag = true;
		break;
	}
	default:
		if (len == 0) {
			flag = false;
		}
		break;
	}
	return flag;
}
bool CtContainerKeyboard::checkAddressFormat() {
	bool flag = true;
	char *strTextField = m_pText->getString();
	int len = strlen(strTextField);

	/* Invalid IP address:
	* 1#   .1.1.1; start with .(formatCheck
	* 2#   1.1.1.1. end with .(formatCheck
	* 3#   256.0.0.1;number exceeded 255(AreaError
	* 4#   1.1.1.1.1; more then 4 segment(formatCheck
	* 5#   1.1.1.0000; more then 3 segmentLen(formatCheck:number of digits
	*/
	int letterPos = 0;
	int dotCount = 0;
	int segment = 0;		// IP segment value  
	int segmentLen;			// The number of characters contained in each IP segment 

	for (segmentLen = 1; segmentLen < 5; segmentLen++) {
		if ('.' == strTextField[letterPos]) {
			// Met dot. 
			if (1 == segmentLen) {
				//#1 
				// .1.1.1 or 1..1.1 is isInvalid. Met dot without number inhead  
				flag = false;
				break;
			}
			else {
				segment = 0;
				segmentLen = 0;   // set -1 as next line is ipSegmentLen++  
				dotCount++;
				if (dotCount > 3) {
					flag = false;  // #4 
					break;
				}
			}
		}
		else {
			segment = segment * 10 + strTextField[letterPos] - 0x30;
			if (segment > 255) {
				// 256.0.0.0 is Invalid #3 
				flag = false;
				break;
			}
		}
		letterPos++;
		if (segmentLen > 3) {
			// 1.1.1.0000 isInvalid. #5
			flag = false;
			break;
		}
		if (len == letterPos) {
			if ('.' == strTextField[letterPos - 1]) {
				// 1.1.1.1. isInvalid. dot is in the end. #2  
				flag = false;
			}

			break;
		}
	}
	if (3 != dotCount) {
		flag = false;
	}
	return flag;
}
