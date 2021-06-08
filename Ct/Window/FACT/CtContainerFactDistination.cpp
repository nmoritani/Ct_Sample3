/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:           CtContainerFactDistination
 */
#include "CtContainerFactDistination.h"


#define LIST_MAX            1000
#define LIST_ROW            7
#define WidgetUSER_OFFSET   (1000)

CtContainerFactDistination::CtContainerFactDistination( CtWindowID id, CtWindowContents* pContents ) :
    m_id(id),
    m_pContents(NULL),
	m_MenuList(NULL)
{
    if (pContents != NULL) {
        m_pContents = new CtWindowContentsFactDistination((CtWindowContentsFactDistination&)*pContents);
    }
}
bool CtContainerFactDistination::destroyContainer()
{
	return true;
}
CtContainerFactDistination::~CtContainerFactDistination()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
}


CtLayout* CtContainerFactDistination::createContainer()
{
	m_MenuList = new CtContainerVariableMenuList(m_id);
	update_ListView();

	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_MenuList);

	return pAll;
}

bool CtContainerFactDistination::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if( m_pContents != NULL ){
        delete m_pContents;
        m_pContents = NULL;
    }

    if( pContents == NULL ) return mRet;

    m_pContents = new CtWindowContentsFactDistination((CtWindowContentsFactDistination&)*pContents);

    mRet = true;

    return mRet;

}

bool CtContainerFactDistination::updateContents()
{
    update_ListView();

	return true;
}

/* ================================================================================== */
/* User List更新 ==================================================================== */
/* ================================================================================== */
void CtContainerFactDistination::update_ListView()
{

    if( m_pContents == NULL ) return;
    if(m_MenuList == NULL ) return ;

	int current = m_pContents->getCurrentIndex();

    /* 前回表示部品を破棄 */
	m_MenuList->cleanupList();

    CtWindowContentsFactDistination::FactDistinationList &list = m_pContents->getFactDistinationList();

    for(int i = 0; i < list.size() && i < LIST_MAX; i++) {
        if( list[i] != NULL ){
        	CtMenuButton *pBtn = new CtMenuButton(AutoSize, getFactDistinationLayout(i), CtButton::Rect);
            pBtn->setWidgetID(i+1+WidgetUSER_OFFSET);
			pBtn->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);

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
/* FactDistination Layout描画 ============================================================== */
/* ================================================================================== */
CtLayout* CtContainerFactDistination::getFactDistinationLayout( int index )
{
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);

    CtLayout* pItemLayout = new CtHLayout();

    if ( m_pContents != NULL ) {

        CtWindowContentsFactDistination::FactDistinationListItr Itr;
        Itr = m_pContents->getFactDistinationList().begin();

        char name[50] = {0};

        CtLabel* pUser = new CtLabel(); 

        /* Label */
        sprintf(name, "%s", (*(Itr+index))->getFactDistination().name);
        pUser->setText(name);
        pUser->setFontSet(fSet_Left);

		pItemLayout->addStretch(15);
		{
			CtVLayout* pLabel = new CtVLayout();
			pLabel->addStretch(11);
			pLabel->addWidget(pUser,70);
			pLabel->addStretch(19);
			pItemLayout->addWidget(pLabel, AlignLeft, 930-126);
		}
		pItemLayout->addStretch(15);

    }

	CtLayout* pLayout = new CtLayout();
	pLayout->addWidget(pItemLayout);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 1, CtColor::White)), AlignBottom);
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 1, CtColor::White)), AlignTop);


    return pLayout;
}

bool CtContainerFactDistination::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Releaseでのみ処理 */
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
