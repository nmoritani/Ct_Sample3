/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtHomeInfoVersion.h"
#include "CtInfoVersionTop.h"
#include "CtInfoVersionMiddle.h"
#include "CtInfoVersionBottom.h"
#include "CtLabel.h"

CtHomeInfoVersion::CtHomeInfoVersion() :
    m_pInfoboxTop(NULL),
    m_pInfoboxBottom(NULL),
    m_pInfoboxMiddle(NULL),
    m_Middle(NULL),
    m_Bottom(NULL),
    m_pAll(NULL),
    m_TouchPress(false),
    m_pWin(NULL)
{
}

CtWindow* CtHomeInfoVersion::createWindow()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);

    m_pWin = new CtWindow(CtColor::Black);
    m_pAll = new CtVLayout();
	
    m_pInfoboxTop  = new CtInfoVersionTop;
    m_pInfoboxBottom  = new CtInfoVersionBottom;
    m_pInfoboxMiddle  = new CtInfoVersionMiddle;
	//mori    addContainer(m_pInfoboxTop);
	//mori    addContainer(m_pInfoboxBottom);
	//mori    addContainer(m_pInfoboxMiddle);

	//mori    m_pAll->addWidget(m_pInfoboxTop->create(),92);
	m_pAll->addContainer(m_pInfoboxTop,92);
	//mori    m_Middle = m_pInfoboxMiddle->create();
	//mori    m_Bottom = m_pInfoboxBottom->create();
	//mori    m_pAll->addWidget(m_Middle, 356);
	//mori    m_pAll->addWidget(m_Bottom, 92);
	m_pAll->addContainer(m_pInfoboxMiddle, 356);
	m_pAll->addContainer(m_pInfoboxBottom, 92);

    m_pWin->addWidget(m_pAll);
    m_pWin->setRegion(CtRegion(0,0,960,540));
    m_pWin->setVisible(true);
    m_pWin->setLayout();
    return m_pWin;
}

CtHomeInfoVersion::~CtHomeInfoVersion()
{
}


bool CtHomeInfoVersion::destroyWindow()
{
    return true;
}

bool CtHomeInfoVersion::handleKeyEvent(const CtEventKey& Key){
    bool bRet = false;

    if(( Key.getKeyCode() == CtEventKey::KeyCode_ManualFunction) ||( Key.getKeyCode() == CtEventKey::KeyCode_Enter)){
        return true;
    }
	
	switch (Key.getKeyAction()) {
    case CtEventKey::Press:
		switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_Up:
			bRet = true;
            break;
		case CtEventKey::KeyCode_Down:
			m_pWin->requestWindow(Window_Info_Media,OpenSwap,NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_Left:
			m_pWin->requestWindow(Window_Info_Switches,OpenSwap,NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_Right:
			bRet = true;
            break;
		case CtEventKey::KeyCode_MmrPlus:
			m_pWin->requestWindow(Window_Info_Switches,OpenSwap,NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_User3:
		case CtEventKey::KeyCode_MmrMinus:
			m_pWin->requestWindow(Window_Info_Network,OpenSwap,NULL);
			bRet = true;
            break;
		default:
			break;
		}
		break;
	default:
        switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_Up:
			bRet = true;
            break;
		case CtEventKey::KeyCode_Down:
			bRet = true;
            break;
		case CtEventKey::KeyCode_Left:
			bRet = true;
            break;
		case CtEventKey::KeyCode_Right:
			bRet = true;
            break;
        case CtEventKey::KeyCode_MmrPlus:
			bRet = true;
            break;
		case CtEventKey::KeyCode_MmrMinus:
			bRet = true;
            break;
        default:
			break;
		}
		break;
	}

    return bRet;
}

/*********************************************************************************
 ???????????????A????(touch_Press????)???L?^?????A
 (Press???????????A??????TRUE???????????ARelease????????????????FALSE??????????)
 ???????????????C?????{?^???????????????????Y???????????f????
 ?????l??TRUE???????A???????????????B                                           
*********************************************************************************/
bool CtHomeInfoVersion::handleTouchEvent(const CtEventTouch& Touch){
    CtEventTouch::TouchPosition pos = Touch.getPosition();

	CtPosition Pos;
    Pos.x = pos.m_X;
	Pos.y = pos.m_Y;

    CtButton* infoTouchButton = NULL;

    switch (Touch.getAction()) {
	    case CtEventTouch::Press:
            if(!m_TouchPress){
                infoTouchButton = ((CtInfoVersionTop*)m_pInfoboxTop)->getTouchButton(Pos);
                if( NULL == infoTouchButton){
                    infoTouchButton = ((CtInfoVersionBottom*)m_pInfoboxBottom)->getTouchButton(Pos);
                }
                if( NULL != infoTouchButton){
                    CtEventInterface::requestButtonCmd(infoTouchButton, this, CtEventButton::ShortPress);
                }
            }
            m_TouchPress = true;
            break;
        case CtEventTouch::Release:
            m_TouchPress = false;
            break;
        default:
            break;
    }
    return true;
}
