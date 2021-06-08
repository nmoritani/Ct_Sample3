/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastDrawContainerTcgWarning
 */
#include "CtFastDrawContainerTcgWarning.h"


CtFastDrawContainerTcgWarning::CtFastDrawContainerTcgWarning() :
	m_hList(0)
{
	m_pLabel = NULL;
	setClassType(CtClassType_LayoutMain);
}


CtLayout* CtFastDrawContainerTcgWarning::createContainer()
{
	m_pLayout = new CtLayout(CtColor::Black);
	
	m_pLabel = new CtLabel();
	m_pLayout->addWidget(m_pLabel);
	
	return m_pLayout;
}

bool CtFastDrawContainerTcgWarning::destroyContainer()
{
	return true;
}

CtFastDrawContainerTcgWarning::~CtFastDrawContainerTcgWarning()
{
	destroy();
}

bool CtFastDrawContainerTcgWarning::initialFastDraw()
{
	CtVLayout *pLayout = NULL;
	GDI_IMAGE_ID  parts[IconParts_Max] = {IC_TCG, IC_TCG_SLAVE, IC_UBG, IC_DUR, IC_WARNING, IC_ALERT};
	GDI_STRING_ID s_parts[IconParts_Max] = {STR_ID_NO_10680, STR_ID_NO_10680, STR_ID_NO_10681, STR_ID_NO_10360, STR_ID_NO_10360, STR_ID_NO_10360};

	CtFontSet fSet_White = CtFontSet( FontTypeNormal_alignCenter, CtColor::White );
	CtFontSet fSet_Black = CtFontSet( FontTypeNormal_alignCenter, CtColor::Black );
	
	for (int i = 0; i < IconParts_Max; i++) {
		switch( parts[i] ){
		case IC_TCG:
		case IC_UBG:
		case IC_DUR:
			{
				CtLabel* pLabel = new CtLabel(s_parts[i],fSet_White);
				pLayout = new CtVLayout(m_pLabel->getRegion());
				pLayout->addStretch(23);
				pLayout->addWidget(pLabel,50);
				pLayout->addStretch(15);
				pLayout->setLayout();
				//m_hList.push_back(pLayout->convertDrawable());
				delete pLayout;
			}
			break;
		case IC_TCG_SLAVE: 
			{
				CtLabel* pLabel = new CtLabel(s_parts[i],fSet_Black);
				//pLabel->setBgColor(CtColor::White);
				pLayout = new CtVLayout(m_pLabel->getRegion());
				pLayout->addStretch(23);
				pLayout->addWidget(pLabel,50);
				pLayout->addStretch(15);
				pLayout->setLayout();
				//m_hList.push_back(pLayout->convertDrawable());
				delete pLayout;
			}
			break;
		case IC_WARNING:
		case IC_ALERT:
			pLayout = new CtVLayout(m_pLabel->getRegion());
			pLayout->addStretch(19);
			pLayout->addWidget(new CtLabel(parts[i]),64);
			pLayout->addStretch(12);
			pLayout->setLayout();
			//m_hList.push_back(pLayout->convertDrawable());
			delete pLayout;
			break;
		}
	}

	m_pLabel->setFastDraw(true);

	return true;
}

bool CtFastDrawContainerTcgWarning::cleanupFastDraw()
{
	/* Drawableを無効化 */
	m_pLabel->setDrawable(GDI_INVALID_ID);

	/* Drawableを破棄 */
	for (int i = 0; i < IconParts_Max; i++) {
		GDI_DeleteDrawable(m_hList[i]);
		m_hList[i] = GDI_INVALID_ID;
	}
	return true;
}

bool CtFastDrawContainerTcgWarning::updateFastDraw()
{
    if( isDispWarningAlert() == false ){
        if( APL_SYS_PARAM_SWITCH_OFF == APL_PARAM_GET_DATA( AplParamTcInSlave ) ){
           switch( APL_PARAM_GET_DATA( AplParamCounterMode )){
            case APL_SYS_PARAM_COUNTER_MODE_TC:
           		if( m_pLabel->getDrawable() !=  m_hList[IconParts_TCG] ) m_pLabel->setDrawable( m_hList[IconParts_TCG] );
                break;
            case APL_SYS_PARAM_COUNTER_MODE_UB:
                if( m_pLabel->getDrawable() !=  m_hList[IconParts_UBG] ) m_pLabel->setDrawable( m_hList[IconParts_UBG] );
                break;
            case APL_SYS_PARAM_COUNTER_MODE_TIME:
                if( m_pLabel->getDrawable() !=  m_hList[IconParts_DUR] ) m_pLabel->setDrawable( m_hList[IconParts_DUR] );
                break;
            default:
                break;
            }
        }else{
            // 外部TCにスレーブ中はTCGを白黒反転（背景白、文字黒）する。
            if( m_pLabel->getDrawable() !=  m_hList[IconParts_TCG_SLAVE] ) m_pLabel->setDrawable( m_hList[IconParts_TCG_SLAVE] );
        }
    }else{
        if( isDispWarning() ){
            if( m_pLabel->getDrawable() !=  m_hList[IconParts_WARNING] ) m_pLabel->setDrawable( m_hList[IconParts_WARNING] );
        }else if( isDispAlert() ){
            // 表示優先順はワーニング > アラート。
            if( m_pLabel->getDrawable() !=  m_hList[IconParts_ALERT] ) m_pLabel->setDrawable( m_hList[IconParts_ALERT] );
        }
    }
	return true;
}

bool CtFastDrawContainerTcgWarning::isDispWarningAlert(){

	if( isDispWarning() ){
		return true;
	}
	if( isDispAlert() ){
		return true;
	}

	return false;

}

bool CtFastDrawContainerTcgWarning::isDispWarning(){

	int warning = APL_PARAM_GET_DATA( AplParamWarning );
	
	switch( warning ){
	case APL_SYS_PARAM_WARNING_NONE:
		break;
	case APL_SYS_PARAM_WARNING_LOW_BATTERY:
		return true;
	case APL_SYS_PARAM_WARNING_FAN_STOPPED:
		return true;
	case APL_SYS_PARAM_WARNING_HIGH_TEMP:
		break;
	case APL_SYS_PARAM_WARNING_REC_WARNING:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR:
		return true;
	case APL_SYS_PARAM_WARNING_NO_REMAIN:
		break;
	case APL_SYS_PARAM_WARNING_BATTERY_NEAR_END:
		break;
	case APL_SYS_PARAM_WARNING_REMAIN_LESS_2MIN:
		break;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING:
		return true;
	default:
		break;
	}
	return false;

}

bool CtFastDrawContainerTcgWarning::isDispAlert(){

	int alert = APL_PARAM_GET_DATA( AplParamAlert );
	
	switch( alert ){
	case APL_SYS_PARAM_ALERT_NONE:
		break;
	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_NOT_SDXC_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_REC_IMPOSSIBLE_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY:
		return true;
	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_FAN_STOPPED:
		return true;
	case APL_SYS_PARAM_ALERT_CLOCK_RESET:
		return true;
	default:
		break;
	}

	return false;

}