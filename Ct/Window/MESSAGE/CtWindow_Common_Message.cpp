/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_Common_Message.h"
#include "str_id.h"
#include "string_api.h"
#include "CtLanguage.h"

CtWindow_Common_Message::CtWindow_Common_Message( CtWindowContents *pContents ) :
	m_pWin(NULL),
	m_pSet(NULL),
	m_pRet(NULL),
	m_pTelopMainLayout(NULL),
	m_pTelopMsg(NULL),
	m_pTelop(NULL),
	m_pDialogMainLayout(NULL),
	m_pDialogTitle(NULL),
	m_pDialogMsg(NULL),
	m_pContent(NULL)
{
	if( pContents != NULL && pContents->getType() == Window_CommonMessage ){
		m_pContent = new CtWindowContentsMessage((CtWindowContentsMessage&)*pContents);
	}
}

CtWindow_Common_Message::~CtWindow_Common_Message()
{
	CtTimer::getInstance()->cancelAlarm(CT_COMMON_MSG_TIMER_ID, this );
	if (m_pContent != NULL){
		delete m_pContent;
		m_pContent = NULL;
	}
}

bool CtWindow_Common_Message::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_Common_Message::createWindow()
{
	m_pWin = new CtWindow();
	
	m_pDialogMainLayout = createDialog();
	m_pTelopMainLayout = createTelop();

	if( m_pDialogMainLayout != NULL ){
		m_pWin->addWidget(m_pDialogMainLayout);
	}
	if( m_pTelopMainLayout != NULL ){
		m_pWin->addWidget(m_pTelopMainLayout);
	}

    m_pWin->setRegion(CtRegion(MESSAGE_WINDOW_SIZE_X,MESSAGE_WINDOW_SIZE_Y,MESSAGE_WINDOW_SIZE_W,MESSAGE_WINDOW_SIZE_H));
//    m_pWin->setColor(CtColor::Trans);
 //   m_pWin->setVisible(true);
    m_pWin->setLayout();

	if( m_pRet != NULL ){
		m_pWin->setDefaultFocus(m_pRet);
	} else if( m_pSet != NULL ) {
		m_pWin->setDefaultFocus(m_pSet);
	}
	// TODO m_pWin->setInitialFocusType(FocusNormal);

	return m_pWin;
}

bool CtWindow_Common_Message::startupWindow()
{
	initMessage();
	return true;
}

CtLayout* CtWindow_Common_Message::createDialog()
{
	CtVLayout *pAll = new CtVLayout();
	pAll->addWidget(createTitle(), MESSAGE_TITLE_AREA);
	pAll->addWidget(createMain(), MESSAGE_MAIN_AREA);
	return pAll;
}

CtLayout* CtWindow_Common_Message::createTitle()
{
	if( m_pContent == NULL ) {
		return new CtLayout();
	}

	CtWindowContentsMessage::MessageDialogParts parts = m_pContent->getMessageInfo()->d_parts;
	
	CtHLayout* pTitle = new CtHLayout(CtColor(ColorRGBA, MESSAGE_TITLE_BG_COLOR, NULL));
	pTitle->addStretch(MESSAGE_DEFAULT_MARGIN);

	m_pDialogTitle = new CtLabel("",MESSAGE_TITLE_FONT);
	pTitle->addWidget(m_pDialogTitle,MESSAGE_TITLE_AREA_W);
	
	pTitle->addStretch(MESSAGE_DEFAULT_MARGIN);
	return pTitle;
}

CtLayout* CtWindow_Common_Message::createMain()
{
	if( m_pContent == NULL ) {
		return new CtLayout();
	}

	CtWindowContentsMessage::MessageDialogParts parts = m_pContent->getMessageInfo()->d_parts;
	CtFontSet fSet = MESSAGE_TEXT_FONT;
	fSet.setSize(50);
	
	CtLayout* pMain = new CtLayout(CtColor(ColorRGBA, MESSAGE_MAIN_AREA_BG_COLOR, NULL));
	/* コントロール作成 */
	CtHLayout *pControl = new CtHLayout();
	pControl->addWidget(createControl(parts.set,parts.ret),MESSAGE_CONTORL_AREA);
	pControl->addStretch(MESSAGE_MAIN_AREA);
	pMain->addWidget(pControl);
	/* メッセージ */
	CtHLayout *pMessage = new CtHLayout();
	pMessage->addStretch( MESSAGE_DEFAULT_MARGIN );

	m_pDialogMsg = new CtLabel("",fSet);
	pMessage->addWidget(m_pDialogMsg,MESSAGE_TEXT_AREA);
	
	pMessage->addStretch( MESSAGE_DEFAULT_MARGIN );
	pMain->addWidget(pMessage);
	
	return pMain;
}

CtLayout* CtWindow_Common_Message::createControl( bool bSet, bool bRet )  /*変数と関数同名です*/
{
	CtVLayout* pWin = new CtVLayout();
	
	pWin->addStretch(MESSAGE_DEFAULT_MARGIN);	// Space
	m_pSet = new CtButton(CtSize(MESSAGE_BUTTON_W,MESSAGE_BUTTON_H),IC_MENU_SET);
	pWin->addWidget(m_pSet,MESSAGE_BUTTON_H);
	pWin->addStretch(72);	// Space
	pWin->addStretch(MESSAGE_BUTTON_H);
	pWin->addStretch(62);	// Space
	pWin->addStretch(MESSAGE_BUTTON_H);
	pWin->addStretch(72);	// Space
	m_pRet = new CtButton(CtSize(MESSAGE_BUTTON_W,MESSAGE_BUTTON_H),IC_MENU_RETURN);
	pWin->addWidget(m_pRet,MESSAGE_BUTTON_H);
	pWin->addStretch(MESSAGE_DEFAULT_MARGIN);	// Space
	
	if( bSet == true ){
		m_pSet->setVisible(true);
	} else {
		m_pSet->setVisible(false);
	}
	if( bRet == true ){
		m_pRet->setVisible(true);
	} else {
		m_pRet->setVisible(false);
	}
	
	return pWin;
}

bool CtWindow_Common_Message::handleButtonEvent(const CtEventButton& Button)
{

	/* Releaseでのみ処理 */
	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}

	if( (m_pSet != NULL) && (Button.getWidget() == m_pSet) ) {return set();}
	if( (m_pRet != NULL) && (Button.getWidget() == m_pRet) ) {return ret();}
	return false;
}

bool CtWindow_Common_Message::set()
{
	CtWindow *pWindow = NULL;
	if ((pWindow = m_pSet->getWindow()) != NULL) {
		CtEventInterface::requestFuncCmd(FuncID_SET, m_pWin);
	}
	closeWindow();
	return true;
}

bool CtWindow_Common_Message::ret()
{
	CtWindow *pWindow = NULL;
	
	if( m_pRet != NULL ){
		if ((pWindow = m_pRet->getWindow()) != NULL) {
			CtEventInterface::requestFuncCmd(FuncID_RET, m_pWin);
		}
	}
	closeWindow();
	return true;
}

void CtWindow_Common_Message::closeWindow()
{
	CtWindow* pWindow = NULL;
	if( m_pWin != NULL ){
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
	}
	
	return;
}

bool CtWindow_Common_Message::handleTouchEvent(const CtEventTouch& Touch)
{
	bool bRet = false;

	if( m_pContent == NULL ) {
		return bRet;
	}

	if( m_pContent->getMessageInfo()->bTouchErasable && m_pContent->getMessageInfo()->type ==  CtWindowContentsMessage::MessageType_Telop ){
		closeWindow();
		bRet = true;
	}
	return bRet;
}

CtLayout* CtWindow_Common_Message::createTelop()
{
	if( m_pContent == NULL ) {
		return new CtLayout();
	}
	CtFontSet fSet = MESSAGE_TEXT_FONT;
	fSet.setSize(36);

	CtWindowContentsMessage::MessageTelopParts parts = m_pContent->getMessageInfo()->t_parts;
	CtVLayout*	pAll = new CtVLayout( CtColor::Trans );
	m_pTelop = new CtHLayout( CtColor(ColorRGBA, MESSAGE_TELOP_BASE_COLOR, NULL) );
	
	pAll->addStretch(MESSAGE_TELOP_AREA_UP_SPACE);

	m_pTelop->addStretch(MESSAGE_DEFAULT_MARGIN);

	m_pTelopMsg = new CtLabel("", fSet);
	m_pTelop->addWidget(m_pTelopMsg,CtMargin(MESSAGE_DEFAULT_MARGIN,0),MESSAGE_TELOP_AREA_W);

	m_pTelop->addStretch(MESSAGE_DEFAULT_MARGIN);
	pAll->addWidget(m_pTelop,MESSAGE_TELOP_AREA_H);
	
	pAll->addStretch(MESSAGE_TELOP_AREA_BOTTOM_SPACE);
	return pAll;
}

bool CtWindow_Common_Message::handleTimerEvent(const CtEventTimer& Timer){

	closeWindow();
    return true;
}


bool CtWindow_Common_Message::setContents(const CtWindowContents* pContents)
{

    bool bRet = false;
	if( pContents != NULL && pContents->getType() == Window_CommonMessage ){
		if (m_pContent != NULL){
			delete m_pContent;
			m_pContent = NULL;
		}
        m_pContent = new CtWindowContentsMessage((CtWindowContentsMessage&)*pContents);
        return true;
	}
    return bRet;
}

void CtWindow_Common_Message::initMessage()
{
	if( m_pContent != NULL ){
		/* 表示内容を更新 */
		if( m_pContent->getMessageInfo()->type == CtWindowContentsMessage::MessageType_Dialog ){
			updateDialog();
			if( m_pTelopMainLayout != NULL ){
				m_pTelopMainLayout->setVisible(false);
			}
			if( m_pDialogMainLayout != NULL){
				m_pDialogMainLayout->setVisible(true);
			}
		} else if( m_pContent->getMessageInfo()->type ==  CtWindowContentsMessage::MessageType_Telop ){
			updateTelop();
			if( m_pTelopMainLayout != NULL ){
				m_pTelopMainLayout->setVisible(true);
			}
			if( m_pDialogMainLayout != NULL){
				m_pDialogMainLayout->setVisible(false);
			}
		} else {
			if( m_pTelopMainLayout != NULL ){
				m_pTelopMainLayout->setVisible(false);
			}
			if( m_pDialogMainLayout != NULL){
				m_pDialogMainLayout->setVisible(false);
			}
		}
		/* タイマーを更新 */
		if( m_pContent->getMessageInfo()->IndicationTime != WindowContentsMessage_IndicationTime_Invalid){
			CtTimer::getInstance()->cancelAlarm( CT_COMMON_MSG_TIMER_ID, this);
			CtTimer::getInstance()->setAlarm( CT_COMMON_MSG_TIMER_ID, m_pContent->getMessageInfo()->IndicationTime, this );
		} else {
			CtTimer::getInstance()->cancelAlarm( CT_COMMON_MSG_TIMER_ID, this);
		}
	}
}

void CtWindow_Common_Message::updateTelop()
{
	unsigned short *gdistr = NULL;
	int count_lf = 0;

	if( m_pTelopMsg == NULL ) return;
	if( m_pTelop == NULL ) return;

	if( m_pContent != NULL ) {
		CtWindowContentsMessage::MessageTelopParts parts = m_pContent->getMessageInfo()->t_parts;
		//m_pTelop->setBgColor( CtColor(ColorRGBA, m_pContent->getTelopColor(), NULL) );
		if( parts.msg_str_id != WindowContentsMessage_StrindId_Invalid){
			CtRegion region = m_pTelop->getRegion();
			gdistr = GDI_GetString( CtLanguage::getLanguageID(), (GDI_STRING_ID)parts.msg_str_id );
			if (gdistr != NULL) {
				for (int i = 0; gdistr[i]; i++) {
					if (gdistr[i] == 0xa) {
						count_lf++;
					}
				}
			}
			m_pTelop->setRegion(CtRegion(region.x,region.y,MESSAGE_WINDOW_SIZE_W,MESSAGE_TELOP_AREA_STR+(count_lf*50)));
			m_pTelop->setLayout();
			m_pTelopMsg->setStringID((GDI_STRING_ID)parts.msg_str_id);
		} else {
			m_pTelopMsg->setText(parts.msg_str);
		}
	}
}

void CtWindow_Common_Message::updateDialog()
{
	if( m_pDialogTitle == NULL ) return;
	if( m_pDialogMsg == NULL ) return;
	if( m_pSet == NULL ) return;
	if( m_pRet == NULL ) return;

	if( m_pContent != NULL ) {
		CtWindowContentsMessage::MessageDialogParts parts = m_pContent->getMessageInfo()->d_parts;
		/* Title */
		if( parts.title_str_id != WindowContentsMessage_StrindId_Invalid){
			m_pDialogTitle->setStringID((GDI_STRING_ID)parts.title_str_id);
		} else {
			m_pDialogTitle->setText(parts.title_str);
		}
		/* Message */
		if( parts.msg_str_id != WindowContentsMessage_StrindId_Invalid){
			m_pDialogMsg->setStringID((GDI_STRING_ID)parts.msg_str_id);
		} else {
			m_pDialogMsg->setText(parts.msg_str);
		}
		/* Button */
		if( parts.set == true ){
			m_pSet->setVisible(true);
		} else {
			m_pSet->setVisible(false);
		}
		if( parts.ret == true ){
			m_pRet->setVisible(true);
		} else {
			m_pRet->setVisible(false);
		}
		if( m_pRet != NULL && m_pRet->isVisible() ){
			m_pRet->cancelFocus();
		} else if( m_pSet != NULL && m_pSet->isVisible() ) {
			m_pSet->cancelFocus();
		}
	}
}

CtWindow_Wizard_Message::CtWindow_Wizard_Message(CtWindowContents *pContents) :CtWindow_Common_Message(pContents)
{
	if (pContents != NULL && pContents->getType() == Window_WizardMessage) {
		m_pContent = new CtWindowContentsWizardMessage((CtWindowContentsWizardMessage&)*pContents);
	}
}

CtWindow_Wizard_Message::~CtWindow_Wizard_Message()
{
	if (m_pContent != NULL) {
		delete m_pContent;
		m_pContent = NULL;
	}
}
void CtWindow_Wizard_Message::closeWindow() {
	// 親クラスの処理をさせない
	return;
}

