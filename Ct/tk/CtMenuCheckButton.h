/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtMenuCheckButton
*/


#ifndef __CtMenuCheckButton_H__
#define __CtMenuCheckButton_H__

#include "CtMenuButton.h"

class CtMenuCheckButton : public CtMenuButton {
public:
	CtMenuCheckButton(CtButton::Shape Shape);
	CtMenuCheckButton(const CtSize& Size, CtButton::Shape Shape = RoundRect);
	CtMenuCheckButton(const CtRegion& Region, CtButton::Shape Shape = RoundRect);
	CtMenuCheckButton(CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtMenuCheckButton(CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	CtMenuCheckButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtMenuCheckButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	virtual ~CtMenuCheckButton();
	
	void setParamAction(ParamAction Action, const int ParamID);
	
protected:
	void ctor();
	
private:
	bool actionParam();
	
private:
};

#endif
