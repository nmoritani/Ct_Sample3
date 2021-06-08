/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtParamBox
 */

#include "CtParamBox.h"

void CtParamBox::ctor(int Data)
{
	setClassType(CtClassType_ParamBox);
	
	m_Original = Data;
	m_Value = Data;
	m_WriteType = Cache;
}

CtParamBox::CtParamBox() :
	CtParamLabel()
{
	ctor(APL_PARAM_INVALID);
}

CtParamBox::CtParamBox(int ParamID) :
	CtParamLabel(ParamID)
{
	ctor(APL_PARAM_INVALID);
}

CtParamBox::CtParamBox(CtSize& Size, int ParamID) : 
	CtParamLabel(Size, ParamID)
{
	ctor(APL_PARAM_INVALID);
}

CtParamBox::~CtParamBox()
{
}

bool CtParamBox::setLayout(int Screen)
{
	if (m_Value == APL_PARAM_INVALID) {
		m_Original = getValue();
		m_Value = m_Original;
	}
		
	return CtParamLabel::setLayout(Screen);
}

bool CtParamBox::handleParamEvent(const CtEventParam& Param)
{
	if (m_ParamId != Param.getParamId())
		return false;
	
	if (CtParamLabel::handleParamEvent(Param) == true) {
		m_Value = getValue();
		//Žæ“¾’l‚ª‚¨‚©‚µ‚¢		m_Original = APL_PARAM_GET_MASTER_DATA(m_ParamId);
		return true;
	}
	
	return false;
}

CtParamBox::WriteType CtParamBox::getWriteType()
{
	return m_WriteType;
}

bool CtParamBox::inc(int Step, bool bCheck)
{
	bool bRet = false;
	
	if (Step == 0)
		Step = m_Step;
	
	switch (m_Type) {
	case TypeNumeric:
		if (m_Value + Step <= getMax()) {
			if (!bCheck) { set(m_Value + Step); }
			bRet = true;
		} else if (m_Value < getMax()) {
			if (!bCheck) { set(getMax()); }
			bRet = true;
		}
		break;
	case TypeStacked:
		if (m_Stack.size() > 0) {
			if (m_Value == 0) 
				break;

			if (m_Value -1 <= 0) {
				if (!bCheck) { set(0); }
				bRet = true;

			} else {
				for (int i = m_Value -1; i >= 0; i--) {
					if (m_Stack[i] != NULL) {
						if (!bCheck) { set(i); }
						bRet = true;
						break;
					}
				}
			}
		} else {
		}
		break;
	default:
		break;
	}
	return bRet;
}

bool CtParamBox::dec(int Step, bool bCheck)
{
	bool bRet = false;
	
	if (Step == 0)
		Step = m_Step;
	
	switch (m_Type) {
	case TypeNumeric:
		if (m_Value - Step >= getMin()) {
			if (!bCheck) { set(m_Value - Step); }
			bRet = true;
		} else if (m_Value > getMin()) {
			if (!bCheck) { set(getMin()); }
			bRet = true;
		}
		break;
	case TypeStacked: {
		if (m_Stack.size() > 0) {
			if (m_Value == (m_Stack.size() -1))
				break;

			if (m_Value +1 > (m_Stack.size() -1)) {
				if (!bCheck) { set(m_Stack.size() - 1); }
				bRet = true;
				
			} else {
				for (int i = m_Value +1; i <= (m_Stack.size() -1); i++) {
					if (m_Stack[i] != NULL) {
						if (!bCheck) { set(i); }
						bRet = true;
						break;
					}
				}
			}
			
		}
		break;
	}
	default:
		break;
	}
	return bRet;
}

bool CtParamBox::isEdited()
{
	if (m_Original != m_Value)
		return true;
	
	return false;
}

bool CtParamBox::reset()
{
	set(m_Original);
	return true;
}

bool CtParamBox::set(int value, WriteType Type)
{
	switch (getAttribute(m_ParamId, getParam(value))) {
	case AttribInvalid:
	case AttribInvisible:
		return false;
	default:
		break;
	}
	
	m_Value = value;
	format(m_Value);

	setParam(getParam(), Type);
	return true;
}
	
int CtParamBox::getParam()
{
	return getParam(m_Value);
}

int CtParamBox::getParam(int Value)
{
	if ((m_DataStack.size() != 0) && (Value >= 0) && (Value < m_DataStack.size())) {
		return m_DataStack[Value] + m_Offset;
	} else {
		return Value + m_Offset;
	}
}

bool CtParamBox::setParam(int data, WriteType Type)
{
	int _dat = data;
	
	AplParamService::AplParamMainItem* Item = NULL;
	if ((Item = APL_PARAM()->getParamState(m_ParamId)) != NULL) {
		if (Item->size == 1) {
			_dat = (unsigned char)data;
		} else if (Item->size == 2) {
			_dat = (unsigned short)data;
		}
	}

	if ((Type & Master) && (Type & Cache)) {
		APL_PARAM_SET_DATA(m_ParamId, _dat);
	} else if (Type == Cache) {
		APL_PARAM_SET_CACHE_DATA(m_ParamId, _dat);
	} else if (Type == Master) {
		APL_PARAM_SET_MASTER_DATA(m_ParamId, _dat);
	} else {
		return false;
	}
	return true;
}

bool CtParamBox::setParam()
{
	return setParam(getParam(), All);
}

bool CtParamBox::setParam(WriteType Type)
{
	return setParam(getParam(), Type);
}

bool CtParamBox::resetParam()
{
	bool bRet = false;
	
	bRet = set(m_Original);
	
	return bRet;
}

int CtParamBox::getOriginalParam()
{
	if ((m_DataStack.size() != 0) && (m_Original >= 0) && (m_Original < m_DataStack.size())) {
		return m_DataStack[m_Original] + m_Offset;
	} else {
		return m_Original + m_Offset;
	}
}

