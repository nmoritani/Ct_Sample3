#ifndef __CtWindow_ToggleDialog_H__
#define __CtWindow_ToggleDialog_H__

#include "CtWindowCommon.h"

class CtWindow_ToggleDialog : public CtWindowMain
{
public:
	CtWindow_ToggleDialog(CtWindowID id);
	CtWindow_ToggleDialog(CtWindowID id, CtWindowContents *pContents);
	~CtWindow_ToggleDialog();

private:
	virtual CtWindow* createWindow();
	virtual bool destroyWindow();

};

#endif // !__CtWindow_ToggleDialog_H__
