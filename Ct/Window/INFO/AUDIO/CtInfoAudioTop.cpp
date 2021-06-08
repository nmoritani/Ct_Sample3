/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoAudioTop
 */
#include "CtInfoAudioTop.h"
#include "CtLabel.h"
#include "CtWindow.h"

CtInfoAudioTop::CtInfoAudioTop() :
    m_pBox(NULL),
    m_pButtonDiagnostics(NULL),
    m_pButtonSwitches(NULL),
    m_pButtonVersion(NULL)
{
    setClassType(CtClassType_LayoutMain);
}


CtLayout* CtInfoAudioTop::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSet1 = CtFontSet(FontTypeNormal_alignCenter,CtColor::Yellow);
    CtSize fontSize = CtSize(272,66);
    CtSize buttonSize = CtSize(312,82);

    CtHLayout* pButtonBox = new CtHLayout();
    CtLayout *pTop = new CtLayout();

    pButtonBox->addStretch(6);
    /*INFO画面のDIAGNOSTICSボタンを作成する*/
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10688, fSet));
    m_pButtonDiagnostics = new CtButton(buttonSize, None, pTop);
    m_pButtonDiagnostics->getBase()->setImageID(IC_INFO_TOP);
    pButtonBox->addWidget(m_pButtonDiagnostics, 312);

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
    m_pBox->addStretch(7);


    m_pBox->setName("@@@CtInfoNetworkTop@@@");
	//mori    m_pBox->setEventHandler(this);

    return m_pBox;
}

bool CtInfoAudioTop::destroyContainer()
{
    if (m_pBox)
    {
        delete m_pBox;
    }
    else
    {
        /* No Operation */
    }
    return true;
}

bool CtInfoAudioTop::handleButtonEvent(const CtEventButton& Event)
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
    else if (pButton == m_pButtonDiagnostics)
    {
		if( (pWin = m_pButtonDiagnostics->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Diagnostics, OpenSwap, NULL);
		}
        ret = true;
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

CtInfoAudioTop::~CtInfoAudioTop()
{
}

CtButton* CtInfoAudioTop::getTouchButton(CtPosition Pos){
    if(m_pButtonDiagnostics->isContains(Pos)){
        return m_pButtonDiagnostics;
    }else if(m_pButtonSwitches->isContains(Pos)){
        return m_pButtonSwitches;
    }else if(m_pButtonVersion->isContains(Pos)){
        return m_pButtonVersion;
    }else{
        return NULL;
    }
}
