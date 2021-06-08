/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element: CtMenuCheckButton
*/
#include "CtMenuCheckButton.h"
#include "CtParamContents.h"
#include "CtEventInterface.h"
#include "CtHLayout.h"

void CtMenuCheckButton::ctor()
{
}

CtMenuCheckButton::CtMenuCheckButton(CtButton::Shape Shape) :
	CtMenuButton(Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(const CtSize& Size, CtButton::Shape Shape) :
	CtMenuButton(Size, Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(const CtRegion& Region, CtButton::Shape Shape) :
	CtMenuButton(Region, Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(CtLabel * pLabel, CtButton::Shape Shape) :
	CtMenuButton(pLabel, Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(CtLayout * pLayout, CtButton::Shape Shape) :
	CtMenuButton(pLayout, Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(const CtSize & Size, CtLabel * pLabel, CtButton::Shape Shape) :
	CtMenuButton(Size, pLabel, Shape)
{
	ctor();
}

CtMenuCheckButton::CtMenuCheckButton(const CtSize & Size, CtLayout * pLayout, CtButton::Shape Shape) :
	CtMenuButton(Size, pLayout, Shape)
{
	ctor();
}

CtMenuCheckButton::~CtMenuCheckButton()
{
}

void CtMenuCheckButton::setParamAction(ParamAction Action, const int ParamID)
{
	m_ParamAction = Action;
	m_SetParamId = ParamID;
}

bool CtMenuCheckButton::actionParam()
{
	int Data;
	
	if (m_ParamAction == DontWrite)
		return false;

	if (APL_PARAM_GET_DATA(m_SetParamId) != 0) {
		Data = 0;
	} else {
		Data = 1;
	}
	
	if ((m_ParamAction & EnterWrite) && (m_ParamAction & EnterCacheWrite)) {
		APL_PARAM_SET_DATA(m_SetParamId, Data);
	} else if (m_ParamAction & EnterCacheWrite) {
		APL_PARAM_SET_CACHE_DATA(m_SetParamId, Data);
	} else if (m_ParamAction & EnterMasterWrite) {
		APL_PARAM_SET_MASTER_DATA(m_SetParamId, Data);
	} else {
		return false;
	}

	return true;
}

