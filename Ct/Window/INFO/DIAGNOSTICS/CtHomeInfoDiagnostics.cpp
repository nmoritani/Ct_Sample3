/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtHomeInfoDiagnostics.h"
#include "CtInfoDiagnosticsTop.h"
#include "CtInfoDiagnosticsMiddle.h"
#include "CtInfoDiagnosticsBottom.h"
#include "CtLabel.h"

CtHomeInfoDiagnostics::CtHomeInfoDiagnostics() :
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

CtWindow* CtHomeInfoDiagnostics::createWindow()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    m_pWin = new CtWindow(CtColor::Black);
    m_pAll = new CtVLayout();
	
    m_pInfoboxTop  = new CtInfoDiagnosticsTop;
    m_pInfoboxBottom  = new CtInfoDiagnosticsBottom;
    m_pInfoboxMiddle  = new CtInfoDiagnosticsMiddle;

	m_pAll->addContainer(m_pInfoboxTop,92);
	m_pAll->addContainer(m_pInfoboxMiddle, 356);
	m_pAll->addContainer(m_pInfoboxBottom, 92);

    m_pWin->addWidget(m_pAll);
    m_pWin->setRegion(CtRegion(0, 0, 960, 540));
    m_pWin->setVisible(true);
    m_pWin->setLayout();
    return m_pWin;
}

CtHomeInfoDiagnostics::~CtHomeInfoDiagnostics()
{
}


bool CtHomeInfoDiagnostics::destroyWindow()
{
	return true;
}

bool CtHomeInfoDiagnostics::handleKeyEvent(const CtEventKey& Key){
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
			m_pWin->requestWindow(Window_Info_Network, OpenSwap, NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_Left:
			bRet = true;
            break;
		case CtEventKey::KeyCode_Right:
			m_pWin->requestWindow(Window_Info_Switches, OpenSwap, NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_MmrPlus:
			m_pWin->requestWindow(Window_Info_Media, OpenSwap, NULL);
			bRet = true;
            break;
		case CtEventKey::KeyCode_User3:
		case CtEventKey::KeyCode_MmrMinus:
			m_pWin->requestWindow(Window_Info_Switches, OpenSwap, NULL);
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
 変数を設定して、現在(touch_Press動作)を記録して、
 (Press動作完了後、変数をTRUEに設定して、Releaseするまでに変数をFALSEに設定する)
 押下したままで任意のボタン上に移動してから該当変数を判断する
 変数値がTRUEの場合、何も動作しない。                                           
*********************************************************************************/
bool CtHomeInfoDiagnostics::handleTouchEvent(const CtEventTouch& Touch){
    CtEventTouch::TouchPosition pos = Touch.getPosition();

	CtPosition Pos;
    Pos.x = pos.m_X;
	Pos.y = pos.m_Y;

    CtButton* infoTouchButton = NULL;

    switch (Touch.getAction()) {
	    case CtEventTouch::Press:
            if(!m_TouchPress){
                infoTouchButton = ((CtInfoDiagnosticsTop*)m_pInfoboxTop)->getTouchButton(Pos);
                if( NULL == infoTouchButton){
                    infoTouchButton = ((CtInfoDiagnosticsBottom*)m_pInfoboxBottom)->getTouchButton(Pos);
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
