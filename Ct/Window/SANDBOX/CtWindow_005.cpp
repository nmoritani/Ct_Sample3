/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_005
 */


#include "CtWindow_005.h"

CtWindow* CtWindow_005::createWindow()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	CtFontSet fSet2 = CtFontSet(FontTypeNormal_alignCenter, CtColor::Green);
	CtFontSet fSet3 = CtFontSet(FontTypeNormal_alignCenter, CtColor::purple);
	CtFontSet fSet4 = CtFontSet(FontTypeNormal_alignCenter, CtColor::Red);
	
	pSymbol = new CtStackLabel();
	
	CtLabel* pKigouTop = new CtLabel(IC_OSD_KEYTOP_FRAME_ADVANCE);
	CtLabel* pInvalid = new CtLabel(IC_OSD_KEYTOP_FF);

	pSymbol->addLabel(pKigouTop, 0);
	pSymbol->addLabel(pInvalid, 1);
	/* Button */
	const CtStyle::CtProperty& prop = CtStyle::getProperty();
	
	pSymbolBtn = new CtToggleButton(CtSize(124, 66), pSymbol);
	pSymbolBtn->setSelectParts(CtToggleButton::Stroke);

	CtStackLabel* pSymbol1 = new CtStackLabel();
	CtLabel* pKigouTop1 = new CtLabel(IC_OSD_KEYTOP_FRAME_ADVANCE);
	CtLabel* pInvalid1 = new CtLabel(IC_OSD_KEYTOP_FF);
	pSymbol1->addLabel(pKigouTop1, 0);
	pSymbol1->addLabel(pInvalid1, 1);
	CtToggleButton* pSymbolBtn1 = new CtToggleButton(CtSize(124, 66), pSymbol1);
	pSymbolBtn1->setSelectParts(CtToggleButton::Stroke);
	
	CtStackLabel* pSymbol3 = new CtStackLabel();
	{
		CtLabel* pKigouTop2 = new CtLabel(IC_OSD_KEYTOP_FRAME_ADVANCE);
		CtLabel* pInvalid2 = new CtLabel(IC_OSD_KEYTOP_FF);
		pSymbol3->addLabel(pKigouTop2, 0);
		pSymbol3->addLabel(pInvalid2, 1);
	}
	CtToggleButton* pSymbolBtn2 = new CtToggleButton(CtSize(124, 66), pSymbol3);
	pSymbolBtn2->setSelectParts(CtToggleButton::Stroke);

	CtToggleButton* pSymbolBtn3 = new CtToggleButton(CtSize(124, 66), CtToggleButton::Stroke);
	pSymbolBtn1->setSelectParts(CtToggleButton::Stroke);

	CtToggleButton* pSymbolBtn4 = new CtToggleButton(CtSize(124, 66));
	pSymbolBtn1->setSelectParts(CtToggleButton::Stroke);

	//pSymbolBtn->setTop(pL);
	/////////////////////////////////////////////////////////
	pSymbol2 = new CtStackLabel();
	pSymbol2->addLabel(new CtLabel("000", fSet));
	pSymbol2->addLabel(new CtLabel("111", fSet2));
	pSymbol2->addLabel("222", fSet3);
	pSymbol2->addLabel("333", fSet4);
	CtButton* pButton = new CtButton(CtSize(124, 66));
	//m	pButton->setTop(pSymbol2);
	pSymbol2->index(1);

	CtVLayout* pMain = new CtVLayout();
	pMain->addWidget(pSymbolBtn);
	pMain->addWidget(pSymbolBtn1);
	pMain->addWidget(pSymbolBtn2);
	pMain->addWidget(pSymbolBtn3);
	pMain->addWidget(pSymbolBtn4);

	pMain->addWidget(pSymbol2);
	m_pWin = new CtWindow();
	m_pWin->addWidget(pMain);
	m_pWin->setDefaultFocus(pSymbolBtn);
	return m_pWin;
}
bool CtWindow_005::handleButtonEvent(const CtEventButton& Button) {

	int cur, max;
	
	if (Button.getPressType() != CtEventButton::Release)
		return false;
	
	if (pSymbolBtn->isSelected() == true) {
		pSymbol->index(1);
	} else {
		pSymbol->index(0);
	}

	cur = pSymbol2->getIndex();
	max = pSymbol2->getIndexMax();

	if (cur == max) {
		CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Blue);
		cur = 0;
		pSymbol2->setFontSet(fSet);
	} else {
		cur++;
	}
	pSymbol2->index(cur);
	
	return true;
}
CtWindow_005::CtWindow_005(CtWindowContents *pContents)
{
}

CtWindow_005::~CtWindow_005()
{
	destroyWindow();
}

bool CtWindow_005::destroyWindow()
{
	if (m_pWin != NULL) delete m_pWin;
	return true;
}
