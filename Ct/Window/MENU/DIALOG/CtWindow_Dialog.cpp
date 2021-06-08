#include "CtWindow_Dialog.h"

CtWindow_Dialog::CtWindow_Dialog(CtWindowID id) :
	m_WindowID(id),
	m_pContents(NULL)
{
	setClassType(CtClassType_WindowDialog);
}
CtWindow_Dialog::CtWindow_Dialog(CtWindowID id, CtWindowContents *pContents):
	m_WindowID(id),
	m_pContents(NULL)
{
	if (pContents != NULL) {
		m_pContents = new CtWindowContentsVersionDisp((CtWindowContentsVersionDisp&)*pContents);
	}

	setClassType(CtClassType_WindowDialog);
}

CtWindow_Dialog::~CtWindow_Dialog()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
	destroyWindow();
}
bool CtWindow_Dialog::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_Dialog::createWindow()
{
	CtWindow* pWin = new CtWindow();

	CtContainerDialog* pContainer = new CtContainerDialog(m_WindowID, m_pContents);

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(pContainer);

	pWin->addWidget(pAll);

	return pWin;
}
