/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:           CtContainerNetwork
 */
#include "CtContainerNetwork.h"

#define LIST_MAX            1000
#define LIST_ROW            7
#define WidgetID_SCENEALL   (0xFFFC)
#define WidgetID_SCENE1     (0xFFFB)
#define WidgetID_SCENE2     (0xFFFA)
#define WidgetID_SCENE3     (0xFFF9)
#define WidgetID_SCENE4     (0xFFF8)
#define WidgetID_SCENE5     (0xFFF7)
#define WidgetAP_OFFSET   (1000)

static const GDI_STRING_ID EncString[] = {
	STR_ID_NO_10577,	//10577: 「WPA-TKIP」: 
	STR_ID_NO_10578,	//10578: 「WPA-AES」: 
	STR_ID_NO_10579,	//10579: 「WPA2-TKIP」: 
	STR_ID_NO_10580,	//10580: 「WPA2-AES」: 
	STR_ID_NO_10581,	//10581: 「NONE」: 
};

CtContainerNetwork::CtContainerNetwork( CtWindowID id, CtWindowContents* pContents ) :
    m_id(id),
    m_pContents(NULL),
	m_MenuList(NULL)
{
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsApInfo((CtWindowContentsApInfo&)*pContents);
    }
}
bool CtContainerNetwork::destroyContainer()
{
	return true;
}

CtContainerNetwork::~CtContainerNetwork()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
}

CtLayout* CtContainerNetwork::createContainer()
{
	m_MenuList = new CtContainerVariableMenuList(m_id);
	update_ListView();

	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_MenuList);

    return pAll;
}

bool CtContainerNetwork::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if( m_pContents != NULL ){
        delete m_pContents;
        m_pContents = NULL;
    }

    if( pContents == NULL ) return mRet;

    m_pContents = new CtWindowContentsApInfo((CtWindowContentsApInfo&)*pContents);

    mRet = true;

    return mRet;

}

void CtContainerNetwork::updateContents()
{
    update_ListView();
}

/* ================================================================================== */
/* Ap List更新 ==================================================================== */
/* ================================================================================== */
void CtContainerNetwork::update_ListView()
{

    if( m_pContents == NULL ) return;
    if( m_MenuList == NULL ) return ;

	int current = m_pContents->getCurrentIndex();
	
    /* 前回表示部品を破棄 */
	m_MenuList->cleanupList();

    CtWindowContentsApInfo::ApInfoList &list = m_pContents->getApInfoList();

    for(int i = 0; i < list.size() && i < LIST_MAX; i++) {
        if( list[i] != NULL ){
			CtMenuButton *pBtn = new CtMenuButton(AutoSize, getApInfoLayout(i), CtButton::Rect);
			pBtn->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
            pBtn->setWidgetID(i+1+WidgetAP_OFFSET);

			m_MenuList->addButton(pBtn);
        }
    }

	if( current < 0 || current > list.size() ){
		current = list.size();
	}

	m_MenuList->setCurrentIndex(current);
	m_MenuList->updateEnd();

}


/* ================================================================================== */
/* ApInfo Layout描画 ============================================================== */
/* ================================================================================== */
CtLayout* CtContainerNetwork::getApInfoLayout( int index )
{
    /* Layout構築                                                                       960      */
	/*  |       |__|____________________________|____|____|____|_________________|____|______________|__|  */
	/*  |       |--|----------400---------------|----|-20-|----|-------170-------|----|------90------|--|  */
    /*  |- 126 -|15|                            | 34 |    | 40 |                 | 50 |              |15|  */
    /*  |       |  |   SSID                     |    | Ｈ |    |    Encryption   |    |    Signal    |  |  */
    /*  |       |__|____________________________|____|____|____|_________________|____|______________|__|  */
													       

    CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

    CtHLayout* pItemLayout = new CtHLayout();

    if ( m_pContents != NULL ) {

        CtWindowContentsApInfo::ApInfoListItr Itr;
        Itr = m_pContents->getApInfoList().begin();

        char ssid[50] = {0};

        CtVLayout* pSsid = new CtVLayout();     	//SSID
		CtVLayout* pEcnryption = new CtVLayout();   //ENCRYPT
		CtLabel* pSignal = NULL;  // SIGNAL

        /* SSID Label */
		{
			sprintf(ssid, "%s", (*(Itr+index))->getApInfo().ssid);
			pSsid->addStretch(10);
			pSsid->addWidget(new CtLabel(ssid, fSet_Left),70);
			pSsid->addStretch(20);
		}

        /* Ecnryption Label */
		{
			pEcnryption->addStretch(10);
			pEcnryption->addWidget(new CtLabel(EncString[(*(Itr + index))->getApInfo().EncryptionType], fSet_Center), 70);
			pEcnryption->addStretch(20);
		}

    	/* Signal Strength */
    	switch( (*(Itr+index))->getApInfo().SignalStrength ){
    	case CtApInfo::SignalStrength_None:
    	default:
			pSignal = new CtLabel(IC_WIFI_AP_SIG_LV0);
    		break;
    	case CtApInfo::SignalStrength_1:
			pSignal = new CtLabel(IC_WIFI_AP_SIG_LV1);
			break;
    	case CtApInfo::SignalStrength_2:
			pSignal = new CtLabel(IC_WIFI_AP_SIG_LV2);
			break;
    	case CtApInfo::SignalStrength_3:
			pSignal = new CtLabel(IC_WIFI_AP_SIG_LV3);
			break;
    	case CtApInfo::SignalStrength_4:
			pSignal = new CtLabel(IC_WIFI_AP_SIG_LV4);
			break;
    	}
		pSignal->setFixedColor(true);
    	
		pItemLayout->addStretch(15);
		pItemLayout->addWidget(pSsid, AlignLeft, 400);
		pItemLayout->addStretch(34);
		if ((*(Itr + index))->getApInfo().IsHistory) {
			CtVLayout* pH = new CtVLayout();
			pH->addStretch(10);
			pH->addWidget(new CtLabel("H", fSet_Center), 70);
			pH->addStretch(20);
			pItemLayout->addWidget(pH,20);
		}
		else {
			pItemLayout->addStretch(20);
		}
		pItemLayout->addStretch(40);
		pItemLayout->addWidget(pEcnryption, 170);
		pItemLayout->addStretch(50);
		pItemLayout->addWidget(pSignal,CtMargin(12,11,0,0) , 90);
		pItemLayout->addStretch(15);

    }

	CtLayout* pLayout = new CtLayout();
	pLayout->addWidget(pItemLayout);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 1, CtColor::White)), AlignBottom);
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 1, CtColor::White)), AlignTop);

    return pLayout;
}


bool CtContainerNetwork::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Releaseでのみ処理 */
    if ((Button.getPressType() != CtEventButton::Release) &&
        (Button.getPressType() != CtEventButton::RepeatPress)) {
        return false;
    }

    if (m_pContents != NULL) {
        unsigned long select_index = Button.getWidgetID() - WidgetAP_OFFSET - 1;
        m_pContents->setCurrentIndex(select_index);
    }

    switch(Button.getWidgetID()) {
    case WidgetID_UP:
    case WidgetID_DOWN:
    case WidgetID_RET:
		break;
    default:
		CtEventInterface::requestFuncCmd(getScreenSel(), m_id, FuncID_SELECT_AP_NUMBER, m_pContents);
		bFlag = true;
    }

    return bFlag;
}


