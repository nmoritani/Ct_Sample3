/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_Message.h"
#include "string_api.h"
#include "CtLanguage.h"

#include "CtWindowContentsDialogParamSet.h"

CtWindow_Message::CtWindow_Message(CtWindowID id, CtWindowContents *pContents):
	m_Info(NULL),
	m_Param(AplParamIdMax),
	m_Value(0)
{
	if ((pContents != NULL) && (pContents->getClassType() == CtClassType_ContentsParamSet)) {
		m_Param = ((CtWindowContentsDialogParamSet*)pContents)->getParamId();
		m_Value = ((CtWindowContentsDialogParamSet*)pContents)->getValue();
	}

	if (CtInterface::getInstance()->checkWindowCategory(id, WindowMainCategory_Menu)) {
		setClassType(CtClassType_WindowDialog);
	}
	else {
		switch (CtMessageInfo::getMessageDesign(id)){
		case CtMessageInfo::Dialog:
			setClassType(CtClassType_WindowMessageDialog);
			break;
		case CtMessageInfo::Telop:
			setClassType(CtClassType_WindowMessageTelop);
			break;
		default:
			setClassType(CtClassType_WindowMain);
			break;
		}
	}
}

CtWindow_Message::~CtWindow_Message()
{
}

bool CtWindow_Message::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_Message::createWindow()
{
	CtWindow* pWin = new CtWindow();
	m_Info = CtMessageInfo::getMessageInfo(getWindowID());
	if (m_Info == NULL) {
		return pWin;
	}

	CtContainerMessage* pContainer = new CtContainerMessage(getWindowID());
	pContainer->setParam(m_Param, m_Value);

	pWin->addContainer(pContainer);

	return pWin;
}

