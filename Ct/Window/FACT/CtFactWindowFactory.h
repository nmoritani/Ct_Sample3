/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtFactWindowFactory
 */


#ifndef __CtFactWindowFactory_H__
#define __CtFactWindowFactory_H__

#include "Ct.h"
#include "CtObject.h"
#include "CtWidget.h"
#include "CtWindow.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtGridLayout.h"
#include "CtListView.h"
#include "CtWindowController.h"
#include "CtFactWindowKeyTest.h"
#include "CtFactWindowInitialResult.h"
#include "CtFactWindowDispMessage.h"
#include "CtWindow_FACT_DISTINATION.h"
#include "CtFactWindowDistResult.h"
#include "CtFactWindowDialog.h"
#include "CtFactWindowHourMeter.h"


class CtFactWindowFactory : public CtObject
{
public:
	static CtWindowMain* create(CtWindowID id,  CtWindowContents *pContents);

private:
	struct CtFactoryTable {
		CtWindowID id;
		const char* name;
	};

	static const CtFactoryTable m_Table[];
};

#endif
