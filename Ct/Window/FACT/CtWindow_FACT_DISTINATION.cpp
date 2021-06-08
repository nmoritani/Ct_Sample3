/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_FACT_DISTINATION
 */


#include "CtWindow_FACT_DISTINATION.h"

CtWindow_FACT_DISTINATION::CtWindow_FACT_DISTINATION( CtWindowContents* pContents ) :
    m_pNet(NULL),
    m_pWin(NULL),
    m_pContents(NULL)
{
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsFactDistination((CtWindowContentsFactDistination&)*pContents);
    }
	setClassType(CtClassType_WindowFACT);
}

CtWindow* CtWindow_FACT_DISTINATION::createWindow()
{
    CtFontSet fSet = CtFontSet(CtColor::White);
    m_pWin = new CtWindow();
	
	m_pNet = new CtContainerFactDistination( getWindowID(), m_pContents );


	m_pWin->addContainer(m_pNet);

	return m_pWin;
}

CtWindow_FACT_DISTINATION::~CtWindow_FACT_DISTINATION()
{
	if( m_pContents != NULL ){
		delete m_pContents;
		m_pContents = NULL;
	}
}

bool CtWindow_FACT_DISTINATION::destroyWindow()
{
	return true;
}

bool CtWindow_FACT_DISTINATION::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if (pContents != NULL) {
    	if( m_pContents != NULL ){
    		delete m_pContents;
    		m_pContents = NULL;
    	}
        m_pContents = new CtWindowContentsFactDistination((CtWindowContentsFactDistination&)*pContents);
    }

    if (m_pNet != NULL) {
        m_pNet->setContents( m_pContents );
        mRet = true;
    }
    return mRet;
}

bool CtWindow_FACT_DISTINATION::updateContents()
{
    if (m_pNet != NULL) {
        return m_pNet->updateContents();
    }

	return false;
}


