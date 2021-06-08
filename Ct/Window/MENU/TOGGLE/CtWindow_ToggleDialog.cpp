#include "CtWindow_ToggleDialog.h"

#include "CtContainerToggleDialog_ClockSetting.h"
#include "CtContainerToggleDialog_Tc.h"
#include "CtContainerToggleDialog_Ub.h"
#include "CtContainerToggleDialog_TimeZonesetting.h"

CtWindow_ToggleDialog::CtWindow_ToggleDialog(CtWindowID id)
{
	setClassType(CtClassType_WindowToggleDialog);
}
CtWindow_ToggleDialog::CtWindow_ToggleDialog(CtWindowID id, CtWindowContents *pContents)
{
	setClassType(CtClassType_WindowToggleDialog);
}

CtWindow_ToggleDialog::~CtWindow_ToggleDialog()
{
	destroyWindow();
}
bool CtWindow_ToggleDialog::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_ToggleDialog::createWindow()
{
	CtWindowID  WindowID = getWindowID();
	CtWindow*          pWin         = new CtWindow();
	CtContainer*       pContainer = NULL;


	switch (WindowID){
	case WindowID_Menu_CLOCK_SETTING:
		pContainer = new CtContainerToggleDialog_ClockSetting(WindowID);
		break;
	case WindowID_Menu_TC:
		pContainer = new CtContainerToggleDialog_Tc(WindowID);
		break;
	case WindowID_Menu_UB:
		pContainer = new CtContainerToggleDialog_Ub(WindowID);
		break;
	case WindowID_Menu_TIME_ZONESETTING:
		pContainer = new CtContainerToggleDialog_TimeZonesetting(WindowID);
		break;
	default:
		pContainer = new CtContainerToggleDialog(WindowID);
		break;
	}

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(pContainer);

	pWin->addWidget(pAll);

	return pWin;
}
