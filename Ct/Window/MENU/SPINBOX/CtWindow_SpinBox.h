#ifndef __CtWindow_SpinBox_H__
#define __CtWindow_SpinBox_H__

#include "CtWindowCommon.h"
#include "CtMenuInfoSpinBox.h"
#include "CtContainerSpinBox.h"
#include "CtContainerSpinBoxFanc.h"
#include "CtContainerSpinBoxSpecial.h"

class CtWindow_SpinBox : public CtWindowMain
{
public:
	CtWindow_SpinBox();
	CtWindow_SpinBox(CtWindowID id);
	CtWindow_SpinBox(CtWindowContents *pContents);
	~CtWindow_SpinBox();

private:
	virtual CtWindow* createWindow();
	virtual bool destroyWindow();

};

#endif // !__CtWindow_SpinBox_H__
