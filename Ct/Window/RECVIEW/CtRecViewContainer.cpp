/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtRecViewContainer
 */

#include "CtRecViewContainer.h"

CtRecViewContainer::CtRecViewContainer() :
	CtContainer(),
	m_bStatusMode(false)
{
}

CtRecViewContainer::CtRecViewContainer(CtScreenSel ScreenSel) :
	CtContainer(ScreenSel)
{
}

bool CtRecViewContainer::destroyContainer()
{
	return false;
}
CtRecViewContainer::~CtRecViewContainer()
{
}
