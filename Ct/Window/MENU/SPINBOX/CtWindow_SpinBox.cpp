#include "CtWindow_SpinBox.h"

CtWindow_SpinBox::CtWindow_SpinBox()
{
	setTransView(true);
	setClassType(CtClassType_WindowSpinBox);
}
CtWindow_SpinBox::CtWindow_SpinBox(CtWindowID id)
{
	setTransView(true);
	setClassType(CtClassType_WindowSpinBox);
}
CtWindow_SpinBox::CtWindow_SpinBox(CtWindowContents *pContents)
{
	setTransView(true);
	setClassType(CtClassType_WindowSpinBox);
}

CtWindow_SpinBox::~CtWindow_SpinBox()
{
	destroyWindow();
}
bool CtWindow_SpinBox::destroyWindow()
{
	return true;
}

CtWindow* CtWindow_SpinBox::createWindow()
{
	CtWindow*          pWin       = new CtWindow();
	CtWindowID         WinID      = getWindowID();
	CtContainer*       pContainer = NULL;

	CtMenuInfoSpinBox::CtMenuSpinBoxInfo *Info = CtMenuInfoSpinBox::getSpinBoxInfo(WinID);
	if (Info == NULL) {
		CtDebugPrint(CtDbg, "%s --- That WindowID is invalid ---\n", __PRETTY_FUNCTION__);
		return NULL;
	}

	if (Info->action == CtMenuInfoSpinBox::SpinBoxActionType_Frequency) {
		//Žü”g”‚É‚æ‚éˆá‚¢‚ðC³‚·‚é
		if (APL_PARAM_GET_DATA(AplParamSystemFrequency) == APL_SYS_PARAM_SYSTEM_FREQUENCY_59HZ) {
			WinID = (CtWindowID)(WinID + 1);
			Info = CtMenuInfoSpinBox::getSpinBoxInfo(WinID);
		}
		else {
			WinID = (CtWindowID)(WinID + 2);
			Info = CtMenuInfoSpinBox::getSpinBoxInfo(WinID);
		}
	}

	switch (Info->action) {
	case CtMenuInfoSpinBox::SpinBoxActionType_Table:
	case CtMenuInfoSpinBox::SpinBoxActionType_Value:
		pContainer = new CtContainerSpinBox(WinID);
		break;
	case CtMenuInfoSpinBox::SpinBoxActionType_Special:
		pContainer = new CtContainerSpinBoxSpecial(WinID);
		break;
	case CtMenuInfoSpinBox::SpinBoxActionType_CallFunc:
	default:
		pContainer = new CtContainerSpinBoxFanc(WinID);
		break;
	}

	CtLayout *pAll = new CtLayout();
	pAll->addContainer(pContainer);

	pWin->addWidget(pAll);
	pWin->setColor(CtColor::Trans);
	setTransView(false);

	return pWin;
}
