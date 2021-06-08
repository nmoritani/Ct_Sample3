#include "CtWindow2ListMenu.h"

CtWindow2ListMenu::CtWindow2ListMenu()
{
	setClassType(CtClassType_WindowMenu2List);
}

CtWindow2ListMenu::~CtWindow2ListMenu()
{
	destroyWindow();
}

CtWindow* CtWindow2ListMenu::createWindow()
{
	CtWindow* m_pWin = new CtWindow();

	m_pContainer = new CtContainer2ListMenu(getWindowID());

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(m_pContainer);

	m_pWin->addWidget(pAll);

	return m_pWin;
}

bool CtWindow2ListMenu::destroyWindow()
{
	return true;
}
