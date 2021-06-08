/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_007.h"

CtWindow* CtWindow_007::createWindow()
{
	m_pWin = new CtWindow();
#if 0
	CtLayout* pLayout = new CtLayout(CtColor::Trans);
	m_pWin->addWidget(pLayout);
	m_pWin->setVisible(true);
#else
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	
	CtHLayout *pLayout001 = new CtHLayout();
	pLayout001->addWidget(new CtLabel("Network Setting", fSet), 0, AlignLeft);
	CtLabel* pLabel = new CtLabel(CtSize(10,10), "XYZ");
	//	pLabel->setFastDraw(true);
	pLayout001->addWidget(pLabel);

	CtHLayout *pLayout002 = new CtHLayout();
	pLayout002->addWidget(new CtLabel(IC_REEL),  1);
	pLayout002->addWidget(new CtLabel("SSID", fSet), 1);
	pLayout002->addWidget(new CtLabel("Standard Jazz", fSet), AlignRight, 4);
	
//	CtListContainer* pList = new CtListContainer();
//	CtLayout* pLayout004 = pList->create();
	m_pList = new CtListContainer();
	//	CtLayout* pLayout004 = m_pList->create();
	
	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget(pLayout001, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout002, CtMargin(10,10,4,4), 1);
	pLayoutAll->addContainer(m_pList, CtMargin(10,10,100,100), 5);
	m_pWin->addWidget(pLayoutAll);

	//pWin->setWindowID(id);
	m_pWin->setColor(CtColor::Black);
#endif	
	return m_pWin;
}

CtWindow_007::CtWindow_007(CtWindowContents *pContents)
{
}

CtWindow_007::~CtWindow_007()
{
}

bool CtWindow_007::destroyWindow()
{
	return true;
}
bool CtWindow_007::handleKeyEvent(const CtEventKey& Key) {
	return false;
}
bool CtWindow_007::handleButtonEvent(const CtEventButton& Button)
{
	return false;
}
