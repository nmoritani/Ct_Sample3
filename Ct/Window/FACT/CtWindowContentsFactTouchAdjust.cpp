#include "CtWindowContentsFactTouchAdjust.h"

CtWindowContentsFactTouchAdjust::CtWindowContentsFactTouchAdjust(const CtWindowID WindowID) :
	CtWindowContents(WindowID)
{
}

CtWindowContentsFactTouchAdjust::~CtWindowContentsFactTouchAdjust()
{
}

void CtWindowContentsFactTouchAdjust::setContentsFactTouchPos(FACT_TOUCH_POS pos, int x, int y)
{
	m_TouchPos.Pos = pos;
	m_TouchPos.x = x;
	m_TouchPos.y = y;
}

CtWindowContentsFactTouchAdjust::FactTouchPos CtWindowContentsFactTouchAdjust::getContentsFactTouchPos()
{
	return m_TouchPos;
}

void CtWindowContentsFactTouchAdjust::setFactTouchTestPos(FACT_TOUCH_POS type, bool value)
{
	m_touchPos = type;
}


CtWindowContentsFactTouchAdjust::FACT_TOUCH_POS CtWindowContentsFactTouchAdjust::getFactTouchTestPos()
{
	return m_touchPos;
}
