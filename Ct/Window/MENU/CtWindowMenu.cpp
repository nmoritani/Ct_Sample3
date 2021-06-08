#include "CtWindowMenu.h"

CtWindowMenu::CtWindowMenu(CtWindowContents *pContents):
	m_Contents(NULL)
{
	m_Contents = pContents;
	setClassType(CtClassType_WindowMenuList);
}
CtWindowMenu::CtWindowMenu(CtWindowID id) :
	m_Contents(NULL)
{
	setClassType(CtClassType_WindowMenuList);
}
CtWindowMenu::CtWindowMenu():
	m_Contents(NULL)
{
	setClassType(CtClassType_WindowMenuList);
}

CtWindowMenu::~CtWindowMenu()
{
	destroyWindow();
}

CtWindow* CtWindowMenu::createWindow()
{
	CtWindow* m_pWin = new CtWindow();

	m_pContainer = new CtContainerMenu(getWindowID(), m_Contents);

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(m_pContainer);

	m_pWin->addWidget(pAll);
//	m_pWin->setColor(CtColor::Trans);
//	m_pWin->setTransView(true);
	m_pWin->setTrans(true);

	return m_pWin;
}

bool CtWindowMenu::destroyWindow()
{
	return true;
}

CtRegion CtWindowMenu::getListRegion(int Screen) const
{
	CtListView* pView;
	
	if ((pView = m_pContainer->getMenuList()) == NULL)
		return CtRegion(0,0,0,0);

	return pView->getRegion(Screen);
}

bool CtWindowMenu::setBack(bool bBack)
{
	bool bRet = false;
	CtListView* pView;
	CtWidget::List Lists;
	
	if ((pView = m_pContainer->getMenuList()) == NULL)
		return bRet;

	if (pView->getWidgets(CtLayout::Registered, &Lists, WidgetButton, ScreenAll) != true)
		return bRet;
	
	for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
		if ((*Itr)->isMenuButton() == true) {
			static_cast<CtMenuButton*>(*Itr)->setBack(bBack);
			bRet = true;
		}
	}
	return bRet;
}

