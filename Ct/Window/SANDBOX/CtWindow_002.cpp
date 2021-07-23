/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_002
 */


#include "CtWindow_002.h"

CtWindow* CtWindow_002::createWindow()
{
	//CtDebugPrint(CtDbg, " CreateWindow ID:%d ---\n", id);

	CtWindow* pWin = new CtWindow();

	CtLabel *pLabel1 = new CtLabel("Keyboad Test Window");
	pLabel1->setColor(CtColor::White);
	
	CtHLayout* pLayout = new CtHLayout();
    //pLayout->addStretch(1);
	pLayout->addWidget(pLabel1, 10);
    //	pLayout->addStretch(1);
	
	pWin = new CtWindow();

	m_pKeyContainer = new CtKeyboad();
	
	CtVLayout *pAll = new CtVLayout(CtColor::Black);
    pAll->addStretch(1);
 	pAll->addWidget(pLayout, 2);
	pAll->addContainer(m_pKeyContainer, 18);
    pAll->addStretch(1);
 
	pWin->addWidget(pAll, AlignCenter, 0);

	return pWin;
}

CtWindow_002::CtWindow_002(CtWindowContents *pContents)
{
}

CtWindow_002::~CtWindow_002()
{
}


