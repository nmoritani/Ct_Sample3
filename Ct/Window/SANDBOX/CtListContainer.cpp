/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtListContainer.h"

#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtGridView.h"

CtListContainer::CtListContainer() :
	m_pList(NULL),
	m_pButtonPageUp(NULL),
	m_pButtonPageDown(NULL),
	m_pButtonLineUp(NULL),
	m_pButtonLineDown(NULL)
{
	setClassType(CtClassType_LayoutMain);
}


CtLayout* CtListContainer::createContainer()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	CtFontSet fSet2 = CtFontSet(FontTypeNormal_alignCenter, CtColor::Yellow);
	CtHLayout *pTop = NULL;
	CtButton  *pBtn  = NULL;
	
	int WidgetID = 1;

	m_pList = new CtListView(6);
	CtLabel* pLabel = new CtLabel(CtRect(CtColor::Trans, 2, CtColor::Yellow));
	m_pList->setSelectLabel(pLabel, CtMargin(2,2,2,2));

	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL), AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING :", fSet), AlignLeft, 4);
//	pTop->addWidget(new CtLabel("MP4", fSet), AlignRight, 2);
	pTop->addWidget(new CtLabel(STR_ID_NO_10001), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(10));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);

	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL), AlignCenter);
	pTop->addWidget(new CtButton("REC SETTING2 :", fSet), AlignLeft);
	pTop->addWidget(new CtButton("MP5", fSet), AlignRight);
	pTop->setElementsMargin(CtMargin(6));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	//	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pTop);

	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 3 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 4 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	//	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pTop);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 5 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 6 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 7 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 8 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	//	pBtn = new CtButton(AutoSize, pTop, Line);
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 9 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 10 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 11 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 12 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 13 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 14 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	
	pTop = new CtHLayout();
	pTop->addWidget(new CtLabel(IC_REEL),  AlignCenter);
	pTop->addWidget(new CtLabel("REC SETTING 15 :", fSet),  AlignLeft, 4);
	pTop->addWidget(new CtLabel("AVCHD", fSet), AlignRight, 2);
	pTop->setElementsMargin(CtMargin(8));
	pBtn = new CtButton(AutoSize, pTop);
	pBtn->setWidgetID(WidgetID); WidgetID++;
	m_pList->addWidget(pBtn);
	m_pList->setCurrentElement(0);
	
	CtVLayout *pLayout003 = new CtVLayout();
	m_pButtonPageUp = new CtButton("PU", fSet2);
	m_pButtonPageUp->setFocusable(false);
	m_pButtonPageDown = new CtButton("PD", fSet2);
	m_pButtonPageDown->setFocusable(false);
	m_pButtonLineUp = new CtButton("UP", fSet2);
	m_pButtonLineUp->setFocusable(false);
	m_pButtonLineDown = new CtButton("DW", fSet2);
	m_pButtonLineDown->setFocusable(false);
	
	pLayout003->addWidget(m_pButtonPageUp, CtMargin(10,10));
	pLayout003->addWidget(m_pButtonLineUp, CtMargin(10,10));
	pLayout003->addWidget(m_pButtonLineDown, CtMargin(10,10));
	pLayout003->addWidget(m_pButtonPageDown, CtMargin(10,10));

	CtHLayout *pLayout004 = new CtHLayout();
	pLayout004->addWidget(pLayout003, CtMargin(10,10,10,10), 1);
	pLayout004->addWidget(m_pList, CtMargin(10,10,10,10), 5);
	pLayout004->setColor(CtColor::Black);
	
	m_testcnt = 0;
	
	return pLayout004;
#if 0
	CtVLayout *pLayout007 = new CtVLayout();
	pLayout007->addWidget(pTop, 1);
	pLayout007->addWidget(pLayout004, 5);
	return pLayout007;
#endif	
}

bool CtListContainer::handleButtonEvent(const CtEventButton& Event)
{
	CtButton *pButton = (CtButton*)Event.getWidget();

	CtDebugPrint(CtDbg, "WidgetID %d \n", Event.getWidgetID());

	if (Event.getPressType() != CtEventButton::Release)
		return false;
	
	m_testcnt++;

	if (pButton == m_pButtonPageUp) {
		m_pList->prevPage();
	} else if (pButton == m_pButtonPageDown) {
		m_pList->nextPage();
#if 0
		if (m_pButtonPageUp->isInvalid() == false)
			m_pButtonPageUp->setInvalid(true);
		else
			m_pButtonPageUp->setInvalid(false);
#endif		
			
	} else if (pButton == m_pButtonLineUp) {
		m_pList->prevElement();
	} else if (pButton == m_pButtonLineDown) {
		m_pList->nextElement();
	}
	
#if 0	
	if ((m_testcnt % 2) == 0) {
		m_pTest = new CtLabel(IC_ALERT);
		m_pButtonPageDown->setBase(m_pTest);
	} else {
		m_pButtonPageDown->setBaseShape(Line);
	}
#endif	
	return true;
}

CtListContainer::~CtListContainer()
{
}


