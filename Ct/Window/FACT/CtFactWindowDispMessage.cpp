/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDispMessage
*/


#include "CtFactWindowDispMessage.h"

CtFactWindowDispMessage::CtFactWindowDispMessage(CtWindowContents *pContents) :
	m_pContent(NULL)
{
	if( pContents != NULL ){
		m_pContent = new CtWindowContentsDispMessage((CtWindowContentsDispMessage&)*pContents);
	}
	setClassType(CtClassType_WindowFACT);
}


CtWindow* CtFactWindowDispMessage::createWindow()
{
	m_pWin = new CtWindow();
	CtVLayout* pAll = new CtVLayout(CtColor::Gray);

	if( m_pContent != NULL ){
		CtHLayout* pLayou1 = new CtHLayout();
		
		pAll->addWidget(pLayou1);

		/* 1’i–Ú */
		pLayou1->addWidget(new CtLabel(m_pContent->getMessage()));
		
	
	}
	m_pWin->addWidget(pAll, CtMargin(20, 20));
	m_pWin->setTrans(false);
	m_pWin->setColor(CtColor::Trans);

	return m_pWin;
}


CtFactWindowDispMessage::~CtFactWindowDispMessage()
{
	if(m_pContent != NULL){
		delete m_pContent;
		m_pContent = NULL;	
	}
}

bool CtFactWindowDispMessage::destroyWindow()
{
	return true;
}



bool CtFactWindowDispMessage::setContents(const CtWindowContents* pContents)
{
	return false;
}

