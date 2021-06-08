/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:           CtContainerNetworkUser
 */
#include "CtContainerNetworkUser.h"
#include "CtMenuButton.h"

#define LIST_MAX            1000
#define LIST_ROW            7
#define WidgetUSER_OFFSET   (1000)

CtContainerNetworkUser::CtContainerNetworkUser( CtWindowID id, CtWindowContents* pContents ) :
    m_id(id),
    m_pContents(NULL),
	m_MenuList(NULL)
{
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsUserInfo((CtWindowContentsUserInfo&)*pContents);
    }
}
bool CtContainerNetworkUser::destroyContainer()
{
	return true;
}
CtContainerNetworkUser::~CtContainerNetworkUser()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
}

CtLayout* CtContainerNetworkUser::createContainer()
{
	m_MenuList = new CtContainerVariableMenuList(m_id);
	update_ListView();

	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_MenuList);

	return pAll;
}

bool CtContainerNetworkUser::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if( m_pContents != NULL ){
        delete m_pContents;
        m_pContents = NULL;
    }

    if( pContents == NULL ) return mRet;

    m_pContents = new CtWindowContentsUserInfo((CtWindowContentsUserInfo&)*pContents);

    mRet = true;

    return mRet;

}

void CtContainerNetworkUser::updateContents()
{
    update_ListView();
}

/* ================================================================================== */
/* User ListXV ==================================================================== */
/* ================================================================================== */
void CtContainerNetworkUser::update_ListView()
{

    if( m_pContents == NULL ) return;
    if(m_MenuList == NULL ) return ;

	int current = m_pContents->getCurrentIndex();

    /* ‘O‰ñ•\Ž¦•”•i‚ð”jŠü */
	m_MenuList->cleanupList();

    CtWindowContentsUserInfo::UserInfoList &list = m_pContents->getUserInfoList();

    for(int i = 0; i < list.size() && i < LIST_MAX; i++) {
        if( list[i] != NULL ){
			CtMenuButton *pButton = new CtMenuButton(AutoSize, getUserInfoLayout(i), CtButton::Rect);
			pButton->setWidgetID(i + 1 + WidgetUSER_OFFSET);
			pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);

			m_MenuList->addButton(pButton);
        }
    }

	if( current < 0 || current > list.size() ){
		current = list.size();
	}

	m_MenuList->setCurrentIndex(current);
	m_MenuList->updateEnd();

}

/* ================================================================================== */
/* UserInfo Layout•`‰æ ============================================================== */
/* ================================================================================== */
CtLayout* CtContainerNetworkUser::getUserInfoLayout( int index )
{
	/* Layout\’z                                           960      */
	/*  |       |__|________________________________________________________|__|  */
	/*  |       |--|----------350-------------------------------------------|--|  */
	/*  |- 126 -|15|                                                        |15|  */
	/*  |       |  |   Name                                                 |  |  */
	/*  |       |__|________________________________________________________|__|  */
	


    CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	

    CtHLayout* pItemLayout = new CtHLayout();

    if ( m_pContents != NULL ) {

        CtWindowContentsUserInfo::UserInfoListItr Itr;
        Itr = m_pContents->getUserInfoList().begin();

        char name[50] = {0};


        /* SSID Label */
        sprintf(name, "%s", (*(Itr+index))->getUserInfo().name);
        CtLabel* pUser = new CtLabel(name, fSet_Left);
		CtVLayout* pUserLayout = new CtVLayout();
		pUserLayout->addStretch(10);
		pUserLayout->addWidget(pUser,70);
		pUserLayout->addStretch(20);

		pItemLayout->addStretch(15);
		pItemLayout->addWidget(pUserLayout, AlignLeft,960-15-15);
		pItemLayout->addStretch(15);

    }

	CtLayout* pLayout = new CtLayout();
	pLayout->addWidget(pItemLayout);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 1, CtColor::White)), AlignBottom);
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 1, CtColor::White)), AlignTop);

    return pLayout;
}

bool CtContainerNetworkUser::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Release‚Å‚Ì‚Ýˆ— */
    if ((Button.getPressType() != CtEventButton::Release) &&
        (Button.getPressType() != CtEventButton::RepeatPress)) {
        return false;
    }

    if (m_pContents != NULL) {
        unsigned long select_index = Button.getWidgetID() - WidgetUSER_OFFSET - 1;
        m_pContents->setCurrentIndex(select_index);
    }

    switch(Button.getWidgetID()) {
    case WidgetID_UP:
    case WidgetID_DOWN:
    case WidgetID_RET:
        break;
    default:
		CtEventInterface::requestFuncCmd(getScreenSel(), m_id, FuncID_SELECT_USER_ACCOUNT_NUMBER, m_pContents);
		bFlag = true;
        break;
    }
    return bFlag;
}

