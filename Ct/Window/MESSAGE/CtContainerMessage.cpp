/**
*  Copyright (c) 2009-2010 Panasonic Corporation
*  Element:	CtButton
*/
#include "CtContainerMessage.h"
#include "CtContainerBattery.h"
#include "CtContainerMenuTitle.h"
#include "CtContainerCtrlButton.h"
#include "CtLanguage.h"

CtContainerMessage::CtContainerMessage(CtWindowID Windowid):
	m_WindowID(Windowid),
	m_Info(NULL),
	m_Param(AplParamIdMax),
	m_Value(0)
{
	setClassType(CtClassType_Container);
}

CtContainerMessage::~CtContainerMessage()
{
	CtTimer::getInstance()->cancelAlarm(CT_MSG_TIMER_ID, this);
}

void CtContainerMessage::setParam(int param, int value)
{
	m_Param = param;
	m_Value = value;
}

bool CtContainerMessage::startupContainer()
{
	setTimer();
	return true;
}

CtLayout* CtContainerMessage::createContainer()
{
	m_Info = CtMessageInfo::getMessageInfo(m_WindowID);
	if (m_Info == NULL) {
		return NULL;
	}

	CtLayout* pLayout = createLayout();

	return pLayout;
}

CtLayout* CtContainerMessage::createLayout()
{
	CtLayout* pLayout = NULL;

	switch (m_Info->Design) {
	case CtMessageInfo::Telop:
		pLayout = createTelop();
		break;
	case CtMessageInfo::Dialog:
		pLayout = createDialog();
		break;
	case CtMessageInfo::Full:
		pLayout = createFull();
		break;
	default:
		break;
	}

	return pLayout;
}

CtLayout* CtContainerMessage::createTelop()
{
	/* 比率    4:2:8 -> 16:8:32 */
	/* Top           -> 16              */
	/* Label         -> 1 + (6 * n) + 1 */
	/* Bottom        -> All-Top-Bottom  */

	/* Message */
	CtColor color = CtMessageInfo::getBgColor(m_Info->WindowID);
	short Num;
	CtLayout* pLable = createMessage(Num);
	CtVLayout* pMessage = new CtVLayout(color);
	pMessage->addStretch(1);
	pMessage->addWidget(pLable, Num * 6);	/* pgr0398 */
	pMessage->addStretch(1);

	/* Telop */
	CtHLayout* pTelop = new CtHLayout();
	pTelop->addStretch(2);
	pTelop->addWidget(pMessage, CtMargin(0, 0), 49);
	pTelop->addStretch(2);

	CtVLayout*	pAll = new CtVLayout(CtColor::Trans);
	pAll->addStretch(16);
	pAll->addWidget(pTelop, (Num * 6) + 2);	/* pgr0398 */
	pAll->addStretch((TELOP_LINES * 4) - 16 - (Num * 6) + 2);	/* pgr0398 */

	return pAll;
}

CtLayout* CtContainerMessage::createDialog()
{
	CtHLayout* pLayout = new CtHLayout();
	CtLabel* pLabel = NULL;
	CtFontSet fSet;

	switch (m_Info->Title.Type) {
	case CtMessageInfo::TitleType_Normal:
	{
		/* Title Label */
		fSet = CtFontSet(FontTypeNormal_Middle, CtColor::White);
		fSet.setSize(39);
		if (m_Info->Title.id != STR_ID_MAX_SIZE) {
			pLabel = new CtLabel(m_Info->Title.id, fSet);
		}
		else {
			pLabel = new CtLabel(m_Info->Title.str, fSet);
		}

		/* Title Layout */
		pLayout->addStretch(14);
		pLayout->addWidget(pLabel, 960 - 14 - 15 - 60);
		pLayout->addStretch(15);
	}

	break;
	case CtMessageInfo::TitleType_Battery:
	{
		/* Title Label */
		fSet = CtFontSet(FontTypeNormal_Middle, CtColor::White);
		fSet.setSize(39);
		if (m_Info->Title.id != STR_ID_MAX_SIZE) {
			pLabel = new CtLabel(m_Info->Title.id, fSet);
		}
		else {
			pLabel = new CtLabel(m_Info->Title.str, fSet);
		}

		/* Title Layout */
		CtContainerBattery* pBatt = new CtContainerBattery();
		pLayout->addStretch(14);
		pLayout->addWidget(pLabel, 960 - 14 - 15 - 60);
		pLayout->addContainer(pBatt, CtMargin(25, 0), 60);
		pLayout->addStretch(15);
	}
	break;
	case CtMessageInfo::TitleType_Menu:
	{
		CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);
		pLayout->addContainer(pTitle);
	}
	break;
	default:
		break;
	}


	/* Message Label */
	short Num;
	CtLayout* pMessageLable = createMessage(Num);
	CtVLayout* pMessage = new CtVLayout();
	pMessage->addStretch(DIALOG_LINES - Num);	/* pgr0398 */
	pMessage->addWidget(pMessageLable, Num * 2);	/* pgr0398 */
	pMessage->addStretch(DIALOG_LINES - Num);	/* pgr0398 */


	/* Connect Title & Message */
	CtColor color = CtMessageInfo::getBgColor(m_Info->WindowID);
	CtVLayout *pMain = new CtVLayout();
	pMain->addWidget(pLayout, 80);
	pMain->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pMain->addWidget(pMessage, 640 - 80);

	/* Ctrl Button */
	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(m_Info->set.valid, false, false, m_Info->ret.valid);
	pCtrl->setFocusable(true);
	pCtrl->setTransColor(true);
	pCtrl->setTrans(true);

	/* Layout */
	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(pCtrl);
	pAll->addWidget(pMain);

	return pAll;
}

CtLayout* CtContainerMessage::createFull()
{
	/* Message Label */
	short Num;
	CtLayout* pMessageLable = createMessage(Num);
	CtVLayout* pMessage = new CtVLayout();
	pMessage->addStretch(9 - Num);	/* pgr0398 */
	pMessage->addWidget(pMessageLable, Num * 2);	/* pgr0398 */
	pMessage->addStretch(10 - Num);	/* pgr0398 */

	/* Ctrl Button */
	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(m_Info->set.valid, false, false, m_Info->ret.valid);

	/* Layout */
	CtColor color = CtMessageInfo::getBgColor(m_Info->WindowID);
	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(pCtrl);
	pAll->addWidget(pMessage);

	return pAll;
}

CtLayout* CtContainerMessage::createMessage(short &Num)
{
	Num = 1;
	short indention = 0;
	CtLabel* pLabel = NULL;
	CtVLayout* pLayout = new CtVLayout();

	CtFontSet fSet = CtMessageInfo::getMessageFont(m_Info->WindowID);

	if (m_Info->Msg.id != STR_ID_MAX_SIZE) {
		pLabel = new CtLabel(m_Info->Msg.id, fSet);
		indention = CtMessageInfo::checkIndention(m_Info->Msg.id);
	}
	else {
		pLabel = new CtLabel(m_Info->Msg.str, fSet);
		indention = CtMessageInfo::checkIndention(m_Info->Msg.str);
	}
	CtAlign algin = AlignCenter;

	CtMessageInfo::NextStringInfo* Next = CtMessageInfo::getMessageNext(m_Info->WindowID);
	if (Next != NULL) {
		if (Next->NextType == CtMessageInfo::NextRight) {
			algin = AlignRight;
		}
	}
			pLayout->addWidget(pLabel, algin, indention + 1);	/* pgr0398 */
		Num += indention;
	// 2行目以降
	if (Next != NULL) {
		while (Next->WindowID == m_Info->WindowID)
		{
			indention = 0;
			if (Next->NextType == CtMessageInfo::NextUnder) {
				Num++;
				if (Next->id != STR_ID_MAX_SIZE) {
					pLabel = new CtLabel(Next->id, fSet);
					indention = CtMessageInfo::checkIndention(Next->id);
				}
				else {
					pLabel = new CtLabel(Next->str, fSet);
					indention = CtMessageInfo::checkIndention(Next->str);
				}
				pLayout->addWidget(pLabel, indention + 1);	/* pgr0398 */
				Num += indention;
			}
			else if (Next->NextType == CtMessageInfo::NextRight) {
				CtHLayout* pHLayout = new CtHLayout();
				short left =  0;
				short right = 0;
				{
					if (m_Info->Msg.id != STR_ID_MAX_SIZE) {
						left = (short)getMsgStrSize(m_Info->Msg.id);
						pHLayout->addWidget(pLayout, left);
					}
					else {
						left = (short)getMsgStrSize(m_Info->Msg.str);
						pHLayout->addWidget(pLayout, left);
					}
					pHLayout->addStretch(10);
					//右側
					if (Next->id != STR_ID_MAX_SIZE) {
						right = (short)getMsgStrSize(Next->id);
						pHLayout->addWidget(new CtLabel(Next->id, fSet), AlignLeft, right);
					}
					else if (Next->ParamID != AplParamIdMax) {
						char Param[32];
						memset(Param, 0, sizeof(Param));
						sprintf(Param, Next->SubScr, APL_PARAM_GET_DATA(Next->ParamID));
						right = (short)getMsgStrSize(Param);
						pHLayout->addWidget(new CtLabel(Param, fSet), AlignLeft, right);
					}
					else {
						right = (short)getMsgStrSize(Next->str);
						pHLayout->addWidget(new CtLabel(Next->str, fSet), AlignLeft, right);
					}
				
				}
				CtHLayout* pH = new CtHLayout();
				pH->addStretch((887 - left - right - 10) / 2);	/* pgr0398 */
				pH->addWidget(pHLayout, left + right + 10);	/* pgr0398 */
				pH->addStretch((887 - left - right - 10) / 2);	/* pgr0398 */
				return pH;
			}
			Next++;
		}
	}
	return pLayout;
}

bool CtContainerMessage::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}
	switch (Button.getWidgetID()) {
	case WidgetID_SET:
		executionSet();
		return true;
	case WidgetID_RET:
		executionRet();
		return true;
	default:
		break;
	}
	return false;
}

bool CtContainerMessage::handleTouchEvent(const CtEventTouch& Touch)
{
	if (Touch.getAction() == CtEventTouch::Press) {
		if (m_Info->touch == true) {
			closeWindow();
			return true;
		}
	}
	return false;
}

bool CtContainerMessage::handleTimerEvent(const CtEventTimer& Timer) {

	closeWindow();
	return true;
}

bool CtContainerMessage::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Release) {
			if (m_Info->ret.valid == true) {
				executionRet();
				return true;
			}
			else {
				CtEventInterface::requestFuncCmd(m_WindowID, FuncID_Exit);
				return true;
			}
		}
		break;
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_Left:
	case CtEventKey::KeyCode_Right:
	case CtEventKey::KeyCode_Enter:
	case CtEventKey::KeyCode_ManualFunction:
	case CtEventKey::KeyCode_MmrPlus:
	case CtEventKey::KeyCode_MmrMinus:
		if (Key.getKeyAction() == CtEventKey::Press) {
			if (m_Info->touch == true) {
				closeWindow();
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;

}

void CtContainerMessage::executionSet()
{
	CtWindow *pWindow = NULL;
	if (0 <= m_Param && m_Param < AplParamIdMax) {
		APL_PARAM_SET_DATA(m_Param, m_Value);
	}

	if (0 <= m_Info->set.FuncID && m_Info->set.FuncID < FuncID_MAX) {
		CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, m_Info->set.FuncID, NULL);
	}

	if (m_Info->set.WindowID != WindowID_MAX) {
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)m_Info->set.OpenType, m_Info->set.WindowID);
	}

	return;
}
void CtContainerMessage::executionRet()
{
	CtWindow *pWindow = NULL;

	if (0 <= m_Info->ret.FuncID && m_Info->ret.FuncID < FuncID_MAX) {
		CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, m_Info->ret.FuncID, NULL);
	}

	if (m_Info->ret.WindowID != WindowID_MAX) {
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)m_Info->ret.OpenType, m_Info->ret.WindowID);
	}
	return;
}

void CtContainerMessage::closeWindow()
{
	CtEventInterface::requestWindowCmd(CtEventWindow::Close, m_Info->ret.WindowID);

	return;
}

void CtContainerMessage::setTimer()
{
	/* タイマーを更新 */
	if (m_Info->time != 0) {
		CtTimer::getInstance()->cancelAlarm(CT_MSG_TIMER_ID, this);
		CtTimer::getInstance()->setAlarm(CT_MSG_TIMER_ID, m_Info->time, this);
	}
	else {
		CtTimer::getInstance()->cancelAlarm(CT_MSG_TIMER_ID, this);
	}
}

int CtContainerMessage::getMsgStrSize(char* Str) {

	CtSize Size;
	CtFontSet fSet = CtMessageInfo::getMessageFont(m_Info->WindowID);;

	fSet.setSize(46);
	fSet.setLanguageId(CtLanguage::getLanguageID());
	fSet.getStringSize(Size, Str);

	return Size.width;
}

int CtContainerMessage::getMsgStrSize(GDI_STRING_ID STR_ID) {

	CtSize Size;
	CtFontSet fSet = CtMessageInfo::getMessageFont(m_Info->WindowID);;

	fSet.setSize(46);
	fSet.setLanguageId(CtLanguage::getLanguageID());
	fSet.getStringSize(Size, STR_ID);

	return Size.width;
}
