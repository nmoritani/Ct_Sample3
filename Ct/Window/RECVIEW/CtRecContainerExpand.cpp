/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtRecContainerExpand.h"

CtRecContainerExpand::ExpandPos CtRecContainerExpand::Pos[] = {
	/* NOW */													/* UP */										/* DOWN */											/* LEFT */									/* RIGHT */
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8		},
{ APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8,		APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7,	APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8		},
};

CtRecContainerExpand::CtRecContainerExpand() :
	m_pWin(NULL),
	m_pUp(NULL),
	m_pDown(NULL),
	m_pLeft(NULL),
	m_pRight(NULL),
	m_pMarker(NULL),
	m_pAll(NULL),
	m_pMarkerRect(NULL)
{

}

CtRecContainerExpand::~CtRecContainerExpand()
{
}

CtLayout* CtRecContainerExpand::createContainer()
{
	CtLayout *pExView = createExpandView();

	CtLayout *pExMarker = createExpandMarker();

	/************************LayoutMain***********************/
	m_pAll = new CtLayout();

	/* Expand部品群構築 */
	CtLayout  *pLayoutThrough = new CtLayout();
	pLayoutThrough->addWidget(pExMarker);
	pLayoutThrough->addWidget(pExView);

	m_pAll->addWidget(pLayoutThrough);
	m_pAll->setScreenSel(ScreenLCD);

	updateExpand();

	return m_pAll;
}

CtLayout* CtRecContainerExpand::createExpandView()
{
	CtGridLayout *pButtonMap = new CtGridLayout(3, 3);

	m_pUp = new CtButton(CtSize(66, 54));
	m_pUp->setTop(new CtLabel(IC_MENU_UP));
	m_pDown = new CtButton(CtSize(66, 54));
	m_pDown->setTop(new CtLabel(IC_MENU_DOWN));
	m_pLeft = new CtButton(CtSize(66, 54));
	m_pLeft->setTop(new CtLabel(IC_MENU_KB_LEFT));
	m_pRight = new CtButton(CtSize(66, 54));
	m_pRight->setTop(new CtLabel(IC_MENU_KB_RIGHT));

	m_pUp->setFocusable(false);
	m_pDown->setFocusable(false);
	m_pLeft->setFocusable(false);
	m_pRight->setFocusable(false);
	
	pButtonMap->setWidget(m_pUp		, 0, 1, AlignTop);
	pButtonMap->setWidget(m_pDown	, 2, 1, AlignBottom);
	pButtonMap->setWidget(m_pLeft	, 1, 0, CtMargin(0,0,20,0), AlignLeft);
	pButtonMap->setWidget(m_pRight	, 1, 2, CtMargin(0,0,0,20), AlignRight);
	
	return pButtonMap;
}

CtLayout* CtRecContainerExpand::createExpandMarker()
{
	CtLayout  *pAll = new CtLayout();
	CtHLayout *pHpos = new CtHLayout();
	CtVLayout *pVpos = new CtVLayout();
	m_pMarker = new CtLayout(CtSize(VIEW_EXPAND_MARKER_SIZE_W, VIEW_EXPAND_MARKER_SIZE_H));

	/* 外枠 */
	m_pMarker->addWidget(new CtLabel(CtRect(CtColor(0, 0, 0, 191), 2, CtColor::White)));

	m_pMarkerRect = new CtLabel(CtSize(getExpandMarkerSizeW(), getExpandMarkerSizeH()), CtRect(CtColor::Trans, 2, CtColor::Green));
	m_pMarker->addWidget(m_pMarkerRect);

	/* ここの数字は適当に調整 */
	pHpos->addStretch(4);
	pHpos->addWidget(m_pMarker, VIEW_EXPAND_MARKER_SIZE_W);
	pHpos->addStretch(VIEW_WINDOW_SIZE_W - VIEW_EXPAND_MARKER_SIZE_W - 4);
	pVpos->addStretch(424);
	pVpos->addWidget(pHpos, 72);
	pVpos->addStretch(4);
	pAll->addWidget(pVpos);

	return pAll;
}

int CtRecContainerExpand::getExpandMarkerSizeW()
{
	int value = APL_PARAM_GET_DATA(AplParamLcdFocusExpandValue);
	int w = 60;
	switch (value) {
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_2X:	w = 60; break;
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_3X:	w = 40; 	break;
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_4X:	w = 30; 	break;
	default: break;
	}
	return w;
}
int CtRecContainerExpand::getExpandMarkerSizeH()
{
	int value = APL_PARAM_GET_DATA(AplParamLcdFocusExpandValue);
	int h = 36;
	switch (value) {
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_2X:	h = 36; break;
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_3X:	h = 24; 	break;
	case APL_SYS_PARAM_FOCUS_EXPAND_VALUE_4X:	h = 18; 	break;
	default: break;
	}
	return h;
}
void CtRecContainerExpand::getExpandCenterPos(int* x, int* y)
{
	if ((x == NULL) || (y == NULL)) {
		return;
	}

	int step_w = VIEW_EXPAND_MARKER_SIZE_W / 6;
	int step_h = VIEW_EXPAND_MARKER_SIZE_H / 6;

	switch (APL_PARAM_GET_DATA(AplParamLcdFocusExpandPosUserSw)) {
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0:
		*x = step_w * 2;
		*y = step_h * 2;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1:
		*x = step_w * 3;
		*y = step_h * 2;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2:
		*x = step_w * 4;
		*y = step_h * 2;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3:
		*x = step_w * 2;
		*y = step_h * 3;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4:
		*x = step_w * 3;
		*y = step_h * 3;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5:
		*x = step_w * 4;
		*y = step_h * 3;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6:
		*x = step_w * 2;
		*y = step_h * 4;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7:
		*x = step_w * 3;
		*y = step_h * 4;
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8:
		*x = step_w * 4;
		*y = step_h * 4;
		break;
	default:	break;
	}
	CtDebugPrint(CtDbg, " Center[x=%d][y=%d] \n", *x, *y);
}
int CtRecContainerExpand::getExpandYPos()
{
	int up = 0;
	int x = 0, y = 0;
	getExpandCenterPos(&x, &y);
	up = m_pMarker->getRegion().y + y - (getExpandMarkerSizeH() / 2);
	return up;
}
int CtRecContainerExpand::getExpandXPos()
{
	int left;
	int x = 0, y = 0;
	getExpandCenterPos(&x, &y);
	left = m_pMarker->getRegion().x + x - (getExpandMarkerSizeW() / 2);
	return left;
}

void CtRecContainerExpand::setNextPos(ExpandIndex next)
{
	int index = APL_PARAM_GET_DATA(AplParamLcdFocusExpandPosUserSw);
	for (int i = 0; i < sizeof(Pos) / sizeof(ExpandPos); i++) {  /*pgr0360*/
		if (index == Pos[i].now) {
			index = i;
			break;
		}
	}
	if (index >= 0 && index < sizeof(Pos) / sizeof(ExpandPos)) {	/*pgr0360*/
		APL_PARAM_SET_DATA(AplParamLcdFocusExpandPosUserSw, Pos[index].next[next]);
	}
	updateExpand();
}
bool CtRecContainerExpand::destroyWindow()
{
	return true;
}
bool CtRecContainerExpand::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	if (Button.getWidget() == m_pUp) {
		setNextPos(ExpandIndex_Up);
		return true;
	}
	else if (Button.getWidget() == m_pDown) {
		setNextPos(ExpandIndex_Down);
		return true;
	}
	else if (Button.getWidget() == m_pLeft) {
		setNextPos(ExpandIndex_Left);
		return true;
	}
	else if (Button.getWidget() == m_pRight) {
		setNextPos(ExpandIndex_Right);
		return true;
	}
	return false;
}

bool CtRecContainerExpand::handleKeyEvent(const CtEventKey& Key) {

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		{
			int index = APL_PARAM_GET_DATA(AplParamLcdFocusExpandPosUserSw);
			index++;
			if (index > APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_MAX) {
				index = APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_MAX;
			}
			APL_PARAM_SET_DATA(AplParamLcdFocusExpandPosUserSw, index);
		}
		return true;
		case CtEventKey::KeyCode_MmrPlus:
		{
			int index = APL_PARAM_GET_DATA(AplParamLcdFocusExpandPosUserSw);
			index--;
			if (index < APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_MIN) {
				index = APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_MIN;
			}
			APL_PARAM_SET_DATA(AplParamLcdFocusExpandPosUserSw, index);
		}
		return true;
		case CtEventKey::KeyCode_Up:
			setNextPos(ExpandIndex_Up);
			return true;
			break;
		case CtEventKey::KeyCode_Down:
			setNextPos(ExpandIndex_Down);
			return true;
			break;
		case CtEventKey::KeyCode_Right:
			setNextPos(ExpandIndex_Right);
			return true;
			break;
		case CtEventKey::KeyCode_Left:
			setNextPos(ExpandIndex_Left);
			return true;
			break;
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_ManualFunction:
			APL_PARAM_SET_DATA(AplParamLcdFocusExpandPosUserSw, APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4);
			return true;
		case CtEventKey::KeyCode_Exit:
			APL_PARAM_SET_DATA(AplParamLcdFocusExpandUserSw, APL_SYS_PARAM_SWITCH_OFF);
			return true;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;

}

bool CtRecContainerExpand::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamLcdFocusExpandValue:
	case AplParamLcdFocusExpandPosUserSw:
	case AplParamLcdFocusAssistUserSw:
	case AplParamLcdSw:
	case AplParamColorBar:
	case AplParamLcdFocusExpandUserSw:
	case AplParamSpotMeterUserSw:
	case AplParamBalanceLevel:
	case AplParamLcdCleanViewUserSw:
		updateExpand();
		return true;
	default:
		break;
	}

	return false;
}

void CtRecContainerExpand::updateExpand() {

	/* NULLチェック */
	if (m_pMarkerRect == NULL) return;
	if (m_pMarker == NULL) return;
	if (m_pUp == NULL) return;
	if (m_pDown == NULL) return;
	if (m_pLeft == NULL) return;
	if (m_pRight == NULL) return;

	/* LCD反転の場合は全て非表示 */
	if (APL_PARAM_GET_DATA(AplParamLcdSw) == APL_SYS_PARAM_LCD_SW_MIRROR) {
		m_pAll->setVisible(false);
	}
	else {
		m_pAll->setVisible(true);
	}

	/* マーカーサイズ&位置更新 */
	m_pMarkerRect->setRegion( CtRegion(getExpandXPos(),getExpandYPos(),getExpandMarkerSizeW(),getExpandMarkerSizeH()));

	/* マーカーボタン位置更新 */
	switch (APL_PARAM_GET_DATA(AplParamLcdFocusExpandPosUserSw)) {
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_0:
		m_pUp->setVisible(false);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(false);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_1:
		m_pUp->setVisible(false);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_2:
		m_pUp->setVisible(false);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(false);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_3:
		m_pUp->setVisible(true);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(false);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_4:
		m_pUp->setVisible(true);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_5:
		m_pUp->setVisible(true);
		m_pDown->setVisible(true);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(false);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_6:
		m_pUp->setVisible(true);
		m_pDown->setVisible(false);
		m_pLeft->setVisible(false);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_7:
		m_pUp->setVisible(true);
		m_pDown->setVisible(false);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(true);
		break;
	case  APL_SYS_PARAM_FOCUS_EXPAND_POS_USER_SW_POS_8:
		m_pUp->setVisible(true);
		m_pDown->setVisible(false);
		m_pLeft->setVisible(true);
		m_pRight->setVisible(false);
		break;
	default:	break;
	}
}
