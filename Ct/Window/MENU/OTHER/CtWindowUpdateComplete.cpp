/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowUpdateComplete
 */


#include "CtWindowUpdateComplete.h"

CtWindowUpdateComplete::CtWindowUpdateComplete() :
	m_pOk(NULL)
{
	setTransView( true );
	setClassType(CtClassType_WindowMain);
}

CtWindow* CtWindowUpdateComplete::createWindow()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_pOk = new CtButton(AutoSize, new CtLabel(STR_ID_OK, fSet), CtButton::Rect);

	char Data[32] = {};
	int Value = APL_PARAM_GET_DATA(AplParamInfoVersion);
	unsigned char Version[5] = {};
	Version[0] = (unsigned char)((Value & 0xFF000000) >> 24);
	Version[1] = (unsigned char)((Value & 0x00FF0000) >> 16);
	Version[2] = (unsigned char)((Value & 0x0000F000) >> 12);
	Version[3] = (unsigned char)((Value & 0x00000F00) >> 8);
	Version[4] = (unsigned char)((Value & 0x000000FF) >> 0);
	sprintf(Data, "Ver.%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4]);

	CtVLayout* pMsg = new CtVLayout();
	pMsg->addWidget(new CtLabel(STR_ID_NO_10852), 1);
	pMsg->addWidget(new CtLabel(Data), 1);
	pMsg->addStretch(1);

	CtVLayout* pBut = new CtVLayout();
	pBut->addStretch(3);
	pBut->addWidget(m_pOk, CtMargin(0, 60), 2);

	CtGridLayout* pGrid = new CtGridLayout(2, 2);
	pGrid->setWidget(pMsg, 0, 0);
	pGrid->setWidget(pBut, 1, 1);

	CtLayout *pLayout = new CtLayout(CtColor(ColorRGBA, 0x262626ff, NULL));
	pLayout->addWidget(pGrid, CtMargin(50, 50));

	CtWindow* pWin = new CtWindow();
	pWin->addWidget(pLayout, CtMargin(40,60));
	
	return pWin;
}

CtWindowUpdateComplete::~CtWindowUpdateComplete()
{
	destroyWindow();
}

bool CtWindowUpdateComplete::destroyWindow()
{
	return true;
}

bool CtWindowUpdateComplete::handleButtonEvent(const CtEventButton& Button)
{

	/* ReleaseÇ≈ÇÃÇ›èàóù */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}
		
	if (m_pOk == Button.getWidget()) {
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		return true;
	}
	return false;
}

bool CtWindowUpdateComplete::handleKeyEvent(const CtEventKey& Key)
{
    bool bRet = false;
    
    switch (Key.getKeyAction()) {
    case CtEventKey::Release:
        switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_Exit:
        case CtEventKey::KeyCode_GripUser1:
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
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
