/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMenuWindowFactory
 */


#ifndef __CtMenuWindowFactory_H__
#define __CtMenuWindowFactory_H__

#include "CtMenuInfo.h"

#include "CtWindowMenu.h"
#include "CtWindow_Keyboard.h"
#include "CtWindow_SpinBox.h"
#include "CtWindow_Dialog.h"
#include "CtWindow_ToggleDialog.h"
#include "CtWindow_FILE.h"
#include "CtWindow2ListMenu.h"
#include "CtAreaSetting.h"

class CtMenuWindowFactory : public CtObject
{
public:
	static CtWindowMain* create(CtWindowID id,  CtWindowContents *pContents);

private:

};

#endif
