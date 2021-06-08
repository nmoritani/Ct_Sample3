#ifndef __CtWindow_Keyboard_H__
#define __CtWindow_Keyboard_H__

#include "CtWindowCommon.h"
//#include "CtWindowContentsFileInfo.h"
#include "CtContainerKeyboard.h"

class CtWindow_Keyboard : public CtWindowMain
{
public:
	CtWindow_Keyboard();
	CtWindow_Keyboard(CtWindowID id);
	CtWindow_Keyboard(CtWindowContents *pContents);
	~CtWindow_Keyboard();

private:
	virtual CtWindow* createWindow();
	virtual bool destroyWindow() { return true; }
	virtual bool startupWindow();

	CtWindowContents* m_pContents;

};

#endif // !__CtWindow_Keyboard_H__
