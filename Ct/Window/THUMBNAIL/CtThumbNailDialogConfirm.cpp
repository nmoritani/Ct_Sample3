/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialog_Confirm
 */

#include "CtThumbNailDialogConfirm.h"
#include "CtContainerCtrlButton.h"

CtThumbNailDialogConfirm ::CtThumbNailDialogConfirm (CtWindowContents *pContents) :
	m_pWin(NULL),
	m_pSetBtn(NULL),
	m_pRetBtn(NULL)
{
	m_bButtonFirstPress = false;
}

CtWindow* CtThumbNailDialogConfirm ::createWindow()
{
	m_pWin = new CtWindow();

	
	CtVLayout* pMainAll = new CtVLayout(CtColor(ColorRGBA, 0x000000B2, NULL));
	pMainAll->addWidget(createTitle(), 80);
	pMainAll->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2); // Titleと文言の境界線
	pMainAll->addWidget(createMessage(), 640 - 80);

	CtLayout* pAll = new CtLayout();
	pAll->addWidget(pMainAll);
	pAll->addWidget(createControl());

	m_pWin->addWidget(pAll);
	m_pWin->setColor(CtColor::Trans);
	m_pWin->setVisible(true);
	if (m_pRetBtn) m_pWin->setDefaultFocus(m_pRetBtn);
	return m_pWin;
}

CtThumbNailDialogConfirm::~CtThumbNailDialogConfirm()
{

}

bool CtThumbNailDialogConfirm::destroyWindow()
{
	return true;
}

CtLayout* CtThumbNailDialogConfirm::createTitle()
{
	CtHLayout* pTitleLayout = new CtHLayout();
	
	CtLabel* pTitle = NULL;
	CtFontSet fSet = CtFontSet(FontTypeNormal_Middle, CtColor::White);
	fSet.setSize(39);

	if (getWindowID() == Window_CopyConfirm) {
		pTitle = new CtLabel(STR_ID_NO_10016, fSet);
	}
	else {
		pTitle = new CtLabel(STR_ID_NO_10014, fSet);
	}

	pTitleLayout->addStretch(14);
	pTitleLayout->addWidget(pTitle, 871);
	pTitleLayout->addStretch(15);

	return pTitleLayout;
}

/* Are You Sure? */
CtLayout* CtThumbNailDialogConfirm::createMessage()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);

	CtHLayout* pMessage = new CtHLayout();
	{
		CtVLayout* pTextArea = new CtVLayout();
		{
			// 「Are you Sure?」
			pTextArea->addWidget(new CtLabel(STR_ID_NO_10907, fSet));
			// 「(n Clips)」
			CtHLayout* pClipLine = new CtHLayout();
			pClipLine->addStretch(2);

			int nClip = APL_PARAM_GET_DATA(AplParamSelectedClipNum);
			char str[50] = { 0 };
			GDI_STRING_ID strId = STR_ID_NO_11562;
			if (nClip > 1) {
				// 複数
				strId = STR_ID_NO_11563;
			}
			sprintf(str, "(%d ", nClip);
			CtFontSet fRight = fSet;
			fRight.setFontAttribute(FontTypeNormal_alignRight);
			CtLabel* pClipNum = new CtLabel(str, fRight);
			pClipLine->addWidget(pClipNum, 5);

			CtLabel* pClipStr = new CtLabel(strId, fSet);
			pClipLine->addWidget(pClipStr, 4);

			pClipLine->addWidget(new CtLabel(")", fSet), 1);

			pClipLine->addStretch(2);
			pTextArea->addWidget(pClipLine);
		}

		pMessage->addStretch(4);
		pMessage->addWidget(pTextArea, 3);
		pMessage->addStretch(4);
	}
	CtVLayout* pVL = new CtVLayout();
	pVL->addStretch(5);
	pVL->addWidget(pMessage, 4);
	pVL->addStretch(5);
	return pVL;
}

CtLayout* CtThumbNailDialogConfirm::createControl()
{
	m_pSetBtn = new CtButton(CtSize(78, 78), IC_MENU_SET);
	m_pSetBtn->setWidgetID(FuncID_SET);
	m_pRetBtn = new CtButton(CtSize(78, 78), IC_MENU_RETURN);
	m_pRetBtn->setWidgetID(FuncID_RET);
	
	/* V Layout 640 */
	CtVLayout* pV = new CtVLayout();
	pV->addStretch(80);
	pV->addStretch(16);
	pV->addWidget(m_pSetBtn, 78);
	pV->addStretch(65);
	pV->addStretch(86);
	pV->addStretch(78);
	pV->addStretch(65);
	pV->addWidget(m_pRetBtn, 78);
	pV->addStretch(16);

	/* H Layout 960 */
	CtHLayout* pH = new CtHLayout();
	pH->addStretch(14);
	pH->addWidget(pV, 78);
	pH->addStretch(960 - 14 - 78);

	return pH;
}

bool CtThumbNailDialogConfirm::handleButtonEvent(const CtEventButton& Button)
{
	bool bFlag = false;

	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			m_bButtonFirstPress = true;
		}
		return false;
	}
	if (m_bButtonFirstPress == false) {
		return false;
	}
	if (( m_pSetBtn != NULL && m_pSetBtn == Button.getWidget())
	 || ( m_pRetBtn != NULL && m_pRetBtn == Button.getWidget())) {
		CtEventInterface::requestFuncCmd(getScreenSel(), getWindowID(), (CtFuncID)Button.getWidgetID(), NULL);
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, getScreenSel(), WindowNone);
		return true;
	}

	return false;
}

bool CtThumbNailDialogConfirm::handleKeyEvent(const CtEventKey& Key)
{
	bool bRet = false;

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
		case CtEventKey::KeyCode_GripUser1:
			if (m_pWin != NULL) {
				CtEventInterface::requestWindowCmd(CtEventWindow::Close, getScreenSel(), WindowNone);
				bRet = true;
			}
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
