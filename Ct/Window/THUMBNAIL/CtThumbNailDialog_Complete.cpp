/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialog_Complete
 */

#include "CtThumbNailDialog_Complete.h"

CtThumbNailDialog_Complete::CtThumbNailDialog_Complete( CtWindowContents *pContents ) :
	m_pButtonOK(NULL)
{
}

CtWindow* CtThumbNailDialog_Complete::createWindow()
{
	CtWindow* pWin = new CtWindow();
	
	CtHLayout* pAll = new CtHLayout();
	CtVLayout* pBody = new CtVLayout(CtColor(ColorRGBA, 0x000000ac, NULL));    //“§‰ß14%

	pBody->addWidget(createMessage(), 0, 290);	
	pBody->addWidget(createControl(), 0, 250);

    pAll->addStretch( 24 );
	pAll->addWidget(pBody, 912);
	pAll->addStretch( 24 );
	
	pWin->addWidget( pAll );
	pWin->setColor(CtColor::Trans);
	pWin->setVisible(true);
	
	return pWin;
}

CtThumbNailDialog_Complete::~CtThumbNailDialog_Complete()
{
	destroyWindow();
}

bool CtThumbNailDialog_Complete::destroyWindow()
{
	return true;
}

CtLayout* CtThumbNailDialog_Complete::createMessage()
{	
	CtVLayout* pParts = new CtVLayout();
	CtHLayout* pTelop = new CtHLayout();
	
	pParts->addStretch( 230 );

	switch( getWindowID() ) {
	case Window_CopyComplete:
		pTelop->addWidget(new CtLabel(STR_ID_NO_10912),CtMargin(0,0));      //Copy completed.
		break;
	case Window_DeleteComplete:
		pTelop->addWidget(new CtLabel(STR_ID_NO_10909),CtMargin(0,0));      //Deletion completed.
		break;
	case Window_CopyCanceled:
		pTelop->addWidget(new CtLabel(STR_ID_NO_10913),CtMargin(0,0));      //Copy canceled.
		break;
	case Window_DeleteCanceled:
		pTelop->addWidget(new CtLabel(STR_ID_NO_10910),CtMargin(0,0));      //Deletion canceled.
		break;

	default:
		break;
	}

	pParts->addWidget(pTelop, 60);
	
	return pParts;	
}

CtLayout* CtThumbNailDialog_Complete::createControl()
{
	CtFontSet fSetWhite = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

	CtVLayout *pAll	= new CtVLayout();
	CtHLayout *pControlLayout = new CtHLayout();
	m_pButtonOK = new CtButton(CtSize(144, 60), STR_ID_NO_6456, fSetWhite);
    m_pButtonOK->setFocus(false);

	pControlLayout->addStretch( 96 );
	pControlLayout->addStretch( 288 );
	pControlLayout->addWidget(m_pButtonOK, CtMargin(0,0), 144);
    pControlLayout->addStretch( 288 );
	pControlLayout->addStretch( 96 );

    pAll->addStretch( 64 );
	pAll->addWidget(pControlLayout, 0, 60);
	pAll->addStretch( 126 );

	return pAll;	
}

bool CtThumbNailDialog_Complete::handleButtonEvent(const CtEventButton& Button)
{	
    bool bFlag = false;
    CtWindow *pWin = NULL;

	/* Release‚Å‚Ì‚Ýˆ— */
	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}

	if( m_pButtonOK != NULL && Button.getWidget() == m_pButtonOK ){
        if ( (pWin = m_pButtonOK->getWindow()) != NULL) {
            pWin->requestWindow(WindowNone,Close,NULL) ;                   
            bFlag = true;
        }
    }

	return bFlag;
    }

bool CtThumbNailDialog_Complete::handleKeyEvent(const CtEventKey& Key){
    bool bRet = false;

    switch (Key.getKeyAction()) {
    case CtEventKey::Press: 
        switch (Key.getKeyCode()) {
            case CtEventKey::KeyCode_Exit:
            case CtEventKey::KeyCode_GripUser1:
            {
                CtWindow* pWin = NULL;
        	    if( (pWin = m_pButtonOK->getWindow()) != NULL )
        		    pWin->requestWindow(WindowNone,Close,NULL);
                
            }
        	bRet = true;
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
