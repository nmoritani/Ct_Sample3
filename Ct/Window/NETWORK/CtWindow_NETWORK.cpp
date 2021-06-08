/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK
 */


#include "CtWindow_NETWORK.h"

CtWindow_NETWORK::CtWindow_NETWORK( CtWindowContents* pContents ) :
    m_pNet(NULL),
    m_pWin(NULL),
    m_pContents(NULL)
{
	setClassType(CtClassType_WindowNETWORK);
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsApInfo((CtWindowContentsApInfo&)*pContents);
    }
}

CtWindow* CtWindow_NETWORK::createWindow()
{
    m_pWin = new CtWindow();

	m_pNet = new CtContainerNetwork( getWindowID(), m_pContents );

	m_pWin->addContainer(m_pNet);

	return m_pWin;
}

CtWindow_NETWORK::~CtWindow_NETWORK()
{
	if( m_pContents != NULL ){
		delete m_pContents;
		m_pContents = NULL;
	}
}

bool CtWindow_NETWORK::destroyWindow()
{
	return true;
}

bool CtWindow_NETWORK::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;
	
    if (pContents != NULL) {
    	if( m_pContents != NULL ){
    		delete m_pContents;
    		m_pContents = NULL;
    	}
        m_pContents = new CtWindowContentsApInfo((CtWindowContentsApInfo&)*pContents);
    }
	
    if (m_pNet != NULL) {
        m_pNet->setContents( m_pContents );
        mRet = true;
    }
    return mRet;
}
