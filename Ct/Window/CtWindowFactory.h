/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#ifndef __CtWindowFactory_H__
#define __CtWindowFactory_H__

#include "Ct.h"
#include "CtObject.h"
#include "CtWidget.h"
#include "CtWindow.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtGridLayout.h"
#include "CtListView.h"
#include "CtWindowController.h"
//#include "CtWindow_SpinBoxMessage.h"

class CtWindowFactory : public CtObject
{
public:
	static CtWindowMain* create(CtScreenSel ScreenSel, CtWindowID id, CtWindowContents *pContents);

	static void Destroy();

private:
	struct CtFactoryTable {
		CtWindowID id;
		const char* name;
	};

	static const CtFactoryTable m_Table[];
};

#endif
