/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoDiagnosticsBottom
 */
#include "CtInfoDiagnosticsBottom.h"
#include "CtLabel.h"
#include "CtWindow.h"

CtInfoDiagnosticsBottom::CtInfoDiagnosticsBottom() :
    m_pBox(NULL),
    m_pButtonNetwork(NULL),
    m_pButtonAudio(NULL),
    m_pButtonMedia(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

CtLayout* CtInfoDiagnosticsBottom::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSetBlack = CtFontSet(FontTypeNormal_alignCenter,CtColor::Black);
    CtSize fontSize = CtSize(272,66);
    CtSize buttonSize = CtSize(312,82);

    CtHLayout* pButtonBox = new CtHLayout();
    CtLayout *pTop = new CtLayout();

    pButtonBox->addStretch(6);
    /*INFO画面のNETWORKボタンを作成する*/
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10690, fSet));
    m_pButtonNetwork = new CtButton(buttonSize, None, pTop);
    m_pButtonNetwork->getBase()->setImageID(IC_INFO_BOTTOM);
    pButtonBox->addWidget(m_pButtonNetwork, 312);

    pButtonBox->addStretch(6);
    /*INFO画面のAudioボタンを作成する*/
    pTop = new CtLayout();
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10669, fSet));
    m_pButtonAudio = new CtButton(buttonSize, None, pTop);
    m_pButtonAudio->getBase()->setImageID(IC_INFO_BOTTOM);
    pButtonBox->addWidget(m_pButtonAudio, 312);

    pButtonBox->addStretch(6);
    /*INFO画面のMEDIAボタンを作成する*/
    pTop = new CtLayout();
    pTop->addWidget(new CtLabel(fontSize, STR_ID_NO_10691, fSet));
    m_pButtonMedia = new CtButton(buttonSize, None, pTop);
    m_pButtonMedia->getBase()->setImageID(IC_INFO_BOTTOM);
    pButtonBox->addWidget(m_pButtonMedia, 312);

    pButtonBox->addStretch(6);

    m_pBox = new CtVLayout(CtColor(48, 51, 56, 0xff));
    m_pBox->addStretch(7);
    m_pBox->addWidget(pButtonBox, 82); 
    m_pBox->addStretch(3);

    m_pBox->setName("@@@CtInfoNetworkTop@@@");
	//mori    m_pBox->setEventHandler(this);

    return m_pBox;
}

bool CtInfoDiagnosticsBottom::destroyContainer()
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

bool CtInfoDiagnosticsBottom::handleButtonEvent(const CtEventButton& Event)
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
    else if (pButton == m_pButtonNetwork)
    {
		if( (pWin = m_pButtonNetwork->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Network, OpenSwap, NULL);
		}
        ret = true;
    }
    else if (pButton == m_pButtonAudio)
    {
		if( (pWin = m_pButtonAudio->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Audio, OpenSwap, NULL);
		}
        ret = true;
    }
    else if (pButton == m_pButtonMedia)
    {
		if( (pWin = m_pButtonMedia->getWindow()) != NULL ){
			pWin->requestWindow(Window_Info_Media, OpenSwap, NULL);
		}
        ret = true;
    }
    else
    {
        /* No Operation */
    }
    return ret;
}

CtInfoDiagnosticsBottom::~CtInfoDiagnosticsBottom()
{
}

CtButton* CtInfoDiagnosticsBottom::getTouchButton(CtPosition Pos){
    if(m_pButtonNetwork->isContains(Pos)){
        return m_pButtonNetwork;
    }else if(m_pButtonAudio->isContains(Pos)){
        return m_pButtonAudio;
    }else if(m_pButtonMedia->isContains(Pos)){
        return m_pButtonMedia;
    }else{
        return NULL;
    }
}
