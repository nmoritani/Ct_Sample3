/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_SceneList
 */


#include "CtWindow_SceneList.h"

CtWindow_SceneList::CtWindow_SceneList() :
    m_pWin(NULL),
    m_pPage(NULL),
    m_pContentsFile(NULL)
{
	setClassType(CtClassType_WindowFILE);
}

CtWindow* CtWindow_SceneList::createWindow()
{

	CtMenuListView* pList = new CtMenuListView(7);
	CtMenuButton* pButton = NULL;
	CtParamLabel* pParamLabel = NULL;
	CtVLayout* pLayout = NULL;
	CtWindowContentsSelectSceneInfo* pContents = NULL;

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	/* ALL */
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(new CtLabel(STR_ID_BUTTON_ALL, fSet), CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_All);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[0] = pButton;
	pList->addWidget(pButton);

	/* SCENE1 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S1, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F1:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_1);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[1] = pButton;
	pList->addWidget(pButton);

	/* SCENE2 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S2, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F2:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_2);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[2] = pButton;
	pList->addWidget(pButton);

	/* SCENE3 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S3, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F3:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_3);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[3] = pButton;
	pList->addWidget(pButton);

	/* SCENE4 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S4, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F4:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_4);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[4] = pButton;
	pList->addWidget(pButton);

	/* SCENE5 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S5, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F5:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0, 15), AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_5);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pSceneBtn[5] = pButton;
	pList->addWidget(pButton);

	/* SCENE6 */
	pParamLabel = new CtParamLabel(AplParamSceneFileName_S6, fSet);
	pParamLabel->setLabelType(CtParamLabel::TypeStrings);
	pParamLabel->setForm("F6:%s");
	pLayout = new CtVLayout();
	pLayout->addStretch(MENU_POP_TOP);
	pLayout->addWidget(pParamLabel, CtMargin(0,15),AlignLeft, MENU_POP_LABEL);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 2, CtColor::White)), AlignBottom, MENU_POP_BOTTOM);
	pContents = new CtWindowContentsSelectSceneInfo(getWindowID());
	pContents->setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo_6);
	pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	pButton->setFuncAction(FuncID_SELECT_SCENE_NUMBER, pContents);
	m_pSceneBtn[6] = pButton;
	pList->addWidget(pButton);

	pList->setCurrentElement(0);
	pList->setLeftKeyAction(false);

	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(getWindowID());

	CtContainerCtrlButton* pCtrl = new  CtContainerCtrlButton(false, true, true, true);
	pCtrl->setTransColor(true);
	pCtrl->setTrans(true);

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(pList, 960 - 126);

	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout *pAll = new CtVLayout(color);
	pAll->addContainer(pTitle, 80);
	pAll->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pAll->addWidget(pMain, 640 - 80);

	CtLayout* pWin = new CtLayout();
	pWin->addWidget(pAll);
	pWin->addContainer(pCtrl);

	m_pWin = new CtWindow();
	m_pWin->addWidget(pWin);

	// EVA1では必要だがK519では不要
	//	update_SceneList(APL_PARAM_GET_DATA(AplParamColorMain));

	pCtrl->setInvalid(WidgetID_UP, true);
	pCtrl->setInvalid(WidgetID_DOWN, true);

	return m_pWin;
}

CtWindow_SceneList::~CtWindow_SceneList()
{
	destroyWindow();
}

bool CtWindow_SceneList::destroyWindow()
{
	return true;
}
bool CtWindow_SceneList::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if ((Button.getPressType() != CtEventButton::Release) &&
		(Button.getPressType() != CtEventButton::RepeatPress)) {
		return false;
	}
	switch (Button.getWidgetID()) {
	case WidgetID_RET:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		return true;
	default: 
		break;
	}
	return false;
}
bool CtWindow_SceneList::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Press) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
bool CtWindow_SceneList::handleParamEvent(const CtEventParam& Param)
{
	bool bFlag = false;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamColorMain:
		// EVA1では必要だがK519では不要
		//update_SceneList(int_Data);
		bFlag = false;
		break;

	default:
		break;
	}

	return bFlag;
}

/* ================================================================================== */
/* Scene List State更新 ============================================================= */
/* ================================================================================== */
void CtWindow_SceneList::update_SceneList(int int_Data)
{
	// EVA1では必要だがK519では不要

	/* NULLチェック */
	if (m_pSceneBtn[0] == NULL) { return; }
	if (m_pSceneBtn[1] == NULL) { return; }
	if (m_pSceneBtn[2] == NULL) { return; }
	if (m_pSceneBtn[3] == NULL) { return; }
	if (m_pSceneBtn[4] == NULL) { return; }
	if (m_pSceneBtn[5] == NULL) { return; }
	if (m_pSceneBtn[6] == NULL) { return; }

	for (int i = 0; i < 7; i++) {
		m_pSceneBtn[i]->setVisible(true);
		m_pSceneBtn[i]->setInvalid(false);
	}

	switch (int_Data) {
	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
		m_pSceneBtn[0]->setInvalid(false);
		m_pSceneBtn[1]->setInvalid(true);
		m_pSceneBtn[2]->setInvalid(true);
		m_pSceneBtn[3]->setInvalid(true);
		m_pSceneBtn[4]->setInvalid(true);
		m_pSceneBtn[5]->setInvalid(true);
		m_pSceneBtn[6]->setInvalid(true);
		break;
	default:
		break;
	}
}
