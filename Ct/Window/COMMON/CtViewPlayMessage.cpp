/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtViewPlayMessage
 */

#include "CtViewPlayMessage.h"


CtViewPlayMessage::CtViewPlayMessage() :
	m_pWin(NULL),
	m_pMsg(NULL),
	CtWindowMain()
{

}

CtWindow* CtViewPlayMessage::createWindow()
{
    CtLabel *pLabel = NULL;
	CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);


	// Msg
	CtHLayout *pLayoutMsg = new CtHLayout(CtColor::Gray);

    pLayoutMsg->addStretch(5);

    m_pMsg = new CtStackLabel();

    m_pMsgStr = new CtLabel("",fSet_Center);
    m_pMsg->addLabel(m_pMsgStr);
    pLabel = new CtLabel(STR_ID_NO_10658,fSet_Center);
    m_pMsg->addLabel(pLabel);
    pLabel = new CtLabel(STR_ID_NO_10659,fSet_Center);
    m_pMsg->addLabel(pLabel);
    pLabel = new CtLabel(STR_ID_NO_10660,fSet_Center);
    m_pMsg->addLabel(pLabel);
    pLabel = new CtLabel(STR_ID_NO_10661,fSet_Center);
    m_pMsg->addLabel(pLabel);
    pLabel = new CtLabel(STR_ID_NO_10662,fSet_Center);
    m_pMsg->addLabel(pLabel);
    pLabel = new CtLabel(STR_ID_NO_10663,fSet_Center);
    m_pMsg->addLabel(pLabel);

	pLayoutMsg->addWidget(m_pMsg,AlignCenter,110);

    pLayoutMsg->addStretch(5);

	CtVLayout *pMsgLayer = new CtVLayout();

    pMsgLayer->addStretch(16);
	pMsgLayer->addWidget(pLayoutMsg,6);
    pMsgLayer->addStretch(68);

	// Window
	m_pWin = new CtWindow(CtRegion(0,0,960,540), CtColor::Trans);
	m_pWin->addWidget(pMsgLayer);
	m_pWin->setVisible(true);    
	m_pWin->setLayout();

	initDisplay();

	return m_pWin;
}

CtViewPlayMessage::~CtViewPlayMessage()
{
    destroyWindow();
}


bool CtViewPlayMessage::destroyWindow(){
    return true;
}

void CtViewPlayMessage::initDisplay(){
    return;
}

bool CtViewPlayMessage::handleParamEvent(const CtEventParam& Param){
	bool bRet = false;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	return false;
}

void CtViewPlayMessage::dispRecViewMessage(const char * Str){
	m_pMsgStr->setText(Str);
}

void CtViewPlayMessage::dispRecViewMessage(const GDI_STRING_ID StringID){
	m_pMsgStr->setStringID(StringID);
}
