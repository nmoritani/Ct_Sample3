/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoDiagnosticsTop
 */
#include "CtInfoDiagnosticsTop.h"
#include "CtLabel.h"
#include "CtWindow.h"

CtInfoDiagnosticsTop::CtInfoDiagnosticsTop() :
    m_pBox(NULL),
    m_pButtonSwitches(NULL),
    m_pButtonVersion(NULL)
{
    setClassType(CtClassType_LayoutMain);
}


CtLayout* CtInfoDiagnosticsTop::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSetBlack = CtFontSet(FontTypeNormal_alignCenter,CtColor::Black);
    CtSize fontSize = CtSize(272,66);
    CtSize buttonSize = CtSize(312,82);

    CtHLayout* pButtonBox = new CtHLayout();
    CtLayout *pTop = new CtLayout();

    pButtonBox->addStretch(6);
    /*INFO画面のDIAGNOSTICSボタンを作成する*/
    CtLabel* buttonBase = new CtLabel(buttonSize, IC_INFO_TOP);
    buttonBase->setColor(CtColor(255, 216, 0, 0xff));
    pTop->addWidget(buttonBase);
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10688, fSetBlack));
    pButtonBox->addWidget(pTop, 312);

    pButtonBox->addStretch(6);
    /*INFO画面のSWITCHESボタンを作成する*/
    pTop = new CtLayout();
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10689, fSet));
    m_pButtonSwitches = new CtButton(buttonSize, None, pTop);
    m_pButtonSwitches->getBase()->setImageID(IC_INFO_TOP);
    pButtonBox->addWidget(m_pButtonSwitches, 312);

    pButtonBox->addStretch(6);
    /*INFO画面のVERSIONボタンを作成する*/
    pTop = new CtLayout();
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10800, fSet));
    m_pButtonVersion = new CtButton(buttonSize, None, pTop);
    m_pButtonVersion->getBase()->setImageID(IC_INFO_TOP);
    pButtonBox->addWidget(m_pButtonVersion, 312);

    pButtonBox->addStretch(6);

    m_pBox = new CtVLayout(CtColor(48, 51, 56, 0xff));
    m_pBox->addStretch(3);
    m_pBox->addWidget(pButtonBox, 82);
    m_pBox->addWidget(new CtLabel(CtRect(CtColor(255, 216, 0, 0xff), 0, CtColor(255, 216, 0, 0xff))), 4);
    m_pBox->addStretch(3);


    m_pBox->setName("@@@CtInfoNetworkTop@@@");

    return m_pBox;
}

bool CtInfoDiagnosticsTop::destroyContainer()
{
    if (m_pBox)
    {   
        //delete m_pBox;
    }
    else
    {
        /* No Operation */
    }
    return true;
}

bool CtInfoDiagnosticsTop::handleButtonEvent(const CtEventButton& Event)
{
	CtButton *pButton = (CtButton*)Event.getWidget();
    bool ret = false;
	CtWindow* pWin = NULL;

	/* ShortPressでのみ処理 */
	if( Event.getPressType() != CtEventButton::ShortPress ){
		return ret;
	}

    if (pButton == NULL)
    {
        return ret;
    }
    else if (pButton == m_pButtonSwitches)
    {
		if( (pWin = m_pButtonSwitches->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Switches, OpenSwap, NULL);
		}
        ret = true;
    }
    else if (pButton == m_pButtonVersion)
    {
		if( (pWin = m_pButtonVersion->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Version, OpenSwap, NULL);
		}
        ret = true;
    }
    else
    {
        /* No Operation */
    }
    return ret;
}

CtInfoDiagnosticsTop::~CtInfoDiagnosticsTop()
{
}

CtButton* CtInfoDiagnosticsTop::getTouchButton(CtPosition Pos){
    if(m_pButtonSwitches->isContains(Pos)){
        return m_pButtonSwitches;
    }else if(m_pButtonVersion->isContains(Pos)){
        return m_pButtonVersion;
    }else{
        return NULL;
    }
}
