/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_FILE
 */


#include "CtWindow_FILE.h"

CtWindow_FILE::CtWindow_FILE( CtWindowContents* pContents ) :
    m_pFile(NULL),
    m_pWin(NULL),
    m_pPage(NULL),
    m_pContentsFile(NULL)
{
	setClassType(CtClassType_WindowFILE);
    if (pContents != NULL) {
        m_pContentsFile = new CtWindowContentsFileInfo((CtWindowContentsFileInfo&)*pContents);
    }
}

CtWindow* CtWindow_FILE::createWindow()
{
    CtFontSet fSet = CtFontSet(CtColor::White);

    m_pWin = new CtWindow();

	CtVLayout *pAll = new CtVLayout();
	m_pFile = new CtContainerFile( getWindowID(), m_pContentsFile );

    pAll->addContainer(m_pFile, 0, 498);

	m_pWin->addWidget(pAll);
	
	return m_pWin;
}

CtWindow_FILE::~CtWindow_FILE()
{
	if( m_pContentsFile != NULL ){
		delete m_pContentsFile;
		m_pContentsFile = NULL;
	}
}

bool CtWindow_FILE::destroyWindow()
{
	return true;
}

bool CtWindow_FILE::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;
    if (m_pFile != NULL) {
        m_pFile->setContents( pContents );
        mRet = true;
    }
    return mRet;
}

bool CtWindow_FILE::updateContents()
{
    if (m_pFile != NULL) {
        m_pFile->updateContents();
    }
	return true;
}
