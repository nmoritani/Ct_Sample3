/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK_USER
 */


#include "CtWindow_NETWORK_USER.h"

CtWindow_NETWORK_USER::CtWindow_NETWORK_USER( CtWindowContents* pContents ) :
    m_pNet(NULL),
    m_pWin(NULL),
    m_pPage(NULL),
    m_pContents(NULL)
{
	setClassType(CtClassType_WindowNETWORK_USER);
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsUserInfo((CtWindowContentsUserInfo&)*pContents);
    }
}

CtWindow* CtWindow_NETWORK_USER::createWindow()
{
    CtFontSet fSet = CtFontSet(CtColor::White);
    m_pWin = new CtWindow();
	
	CtLayout *pAll = new CtLayout();
	m_pNet = new CtContainerNetworkUser( getWindowID(), m_pContents );

	pAll->addContainer(m_pNet);

	m_pWin->addWidget(pAll);

	return m_pWin;
}

CtWindow_NETWORK_USER::~CtWindow_NETWORK_USER()
{
	if( m_pContents != NULL ){
		delete m_pContents;
		m_pContents = NULL;
	}
}

bool CtWindow_NETWORK_USER::destroyWindow()
{
	return true;
}

bool CtWindow_NETWORK_USER::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if (pContents != NULL) {
    	if( m_pContents != NULL ){
    		delete m_pContents;
    		m_pContents = NULL;
    	}
        m_pContents = new CtWindowContentsUserInfo((CtWindowContentsUserInfo&)*pContents);
    }

    if (m_pNet != NULL) {
        m_pNet->setContents( m_pContents );
        mRet = true;
    }
    return mRet;
}
bool CtWindow_NETWORK_USER::updateContents()
{
	m_pNet->updateContents();
	return true;
}