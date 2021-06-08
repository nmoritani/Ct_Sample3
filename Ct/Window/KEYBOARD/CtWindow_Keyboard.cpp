#include "CtWindow_Keyboard.h"

CtWindow_Keyboard::CtWindow_Keyboard() :
	m_pContents(NULL)
{
	setClassType(CtClassType_WindowKeyboard);
}

CtWindow_Keyboard::CtWindow_Keyboard(CtWindowID id) :
	m_pContents(NULL)
{
	setClassType(CtClassType_WindowKeyboard);
}

CtWindow_Keyboard::CtWindow_Keyboard(CtWindowContents *pContents) :
	m_pContents(NULL)
{
	if (pContents != NULL) {
		m_pContents = new CtWindowContentsFileInfo((CtWindowContentsFileInfo&)*pContents);
	}
	setClassType(CtClassType_WindowKeyboard);
}

CtWindow_Keyboard::~CtWindow_Keyboard()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
	destroyWindow();
}

CtWindow* CtWindow_Keyboard::createWindow()
{
	CtWindow*          pWin       = new CtWindow();
	CtContainer*       pContainer = NULL;

	pContainer = new CtContainerKeyboard(getWindowID(), m_pContents);

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(pContainer);

	pWin->addWidget(pAll);
	pWin->setRoundFocus(true);
	return pWin;
}

bool CtWindow_Keyboard::startupWindow()
{
	restart();
	return true;
}
