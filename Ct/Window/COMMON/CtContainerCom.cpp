#include "CtContainerCom.h"


CtContainerCom::CtContainerCom() :
	m_pCom(NULL),
	m_ComModeFlash(false)
{
}

CtContainerCom::~CtContainerCom(){

}

CtLayout* CtContainerCom::createContainer(){
	CtFontSet fSet_Center = CtFontSet(FontTypeOutline_alignCenter_Middle,CtColor::White,CtColor::Black);

	CtLayout* pLayout = new CtLayout();
	
    m_pCom = new CtLabel(STR_ID_NO_10664,fSet_Center);
	pLayout->addWidget(m_pCom);

    updateCom();

    return pLayout;
}

bool CtContainerCom::destroyContainer(){
    return true;
}

bool CtContainerCom::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;

	switch(Param.getParamId()){
	case AplParamComDisplay:
		updateCom();
		break;
	default:
		bRet = false;
		break;
	}

    return bRet;
}

void CtContainerCom::updateCom(){
	switch( APL_PARAM_GET_DATA( AplParamComDisplay ) ){
	case APL_SYS_PARAM_COM_UNDISPLAY:
	default:
        if(m_ComModeFlash){
            m_pCom->stopFlash();
            m_ComModeFlash = false;
        }
		m_pCom->setVisible(false);
		break;
	case APL_SYS_PARAM_COM_DISPLAY:
        if(m_ComModeFlash){
            m_pCom->stopFlash();
            m_ComModeFlash = false;
        }
		m_pCom->setVisible(true);
		break;
	case APL_SYS_PARAM_COM_FLASHING_DISPLAY:
		m_pCom->setVisible(true);
		m_pCom->startFlash(CtEventFlash::Freq_1Hz);
		m_ComModeFlash = true;
		break;
	}

}
