/**
 *  Copyright (c) AVC Multimedia Soft
 *  Element:			CtParamBox
 */


#ifndef __CtParamBox_H__
#define __CtParamBox_H__

#include "CtParamLabel.h"

class CtButton;

class CtParamBox : public CtParamLabel {
public :
	enum WriteType {
		None = 0x00,
		Master = 0x01,
		Cache = 0x02,
		All = (Master|Cache)
	};
	
	CtParamBox();
	virtual ~CtParamBox();

    CtParamBox(int ParamID);
    CtParamBox(CtSize& Size, int ParamID);

	virtual bool setLayout(int Screen = 0);
	
	bool handleParamEvent(const CtEventParam& Param);
	
	bool isParamLabel() const;
	
	bool setWriteType(WriteType Type);
	CtParamBox::WriteType getWriteType();
	bool setStep(int step);
	bool isParamBox() const;
	
	bool inc(int step = 0, bool bCheck = false);
	bool dec(int step = 0, bool bCheck = false);

	int getParam();
	int getParam(int Value);
	
	bool setParam();
	bool setParam(WriteType Type);
	
	bool resetParam();
	int getOriginalParam();
	bool isEdited();

private:
	void ctor(int Data);
	bool setParam(int Data, WriteType Type);
	bool reset();
	bool set(int value, WriteType Type = Cache);
	
	// ëÆê´
private:
	int		m_Original;
	int		m_Value;
	
	WriteType m_WriteType;
};

inline bool CtParamBox::isParamLabel() const
{
	return false;
}

inline bool CtParamBox::setWriteType(WriteType Type)
{
	m_WriteType = Type;
	return true;
}

inline bool CtParamBox::setStep(int step)
{
	m_Step = step;
	return true;
}

inline bool CtParamBox::isParamBox() const
{
	return true;
}

#endif
