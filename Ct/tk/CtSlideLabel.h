/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtSlideLabel
*/


#ifndef __CtSlideLabel_H__
#define __CtSlideLabel_H__

#include "Ct.h"
#include "CtWidget.h"
#include "CtLabel.h"

class CtSlideLabel : public CtLabel {
public:

	CtSlideLabel();
	CtSlideLabel(const GDI_IMAGE_ID ImageID);
	CtSlideLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet);
	CtSlideLabel(const GDI_STRING_ID StringID);
	CtSlideLabel(const char* ucStr, const CtFontSet& FontSet);
	CtSlideLabel(const char* ucStr);
	
	CtSlideLabel(const CtSize& Size, const GDI_IMAGE_ID ImageID);
	CtSlideLabel(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet);
	CtSlideLabel(const CtSize& Size, const GDI_STRING_ID StringID);
	CtSlideLabel(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet);
	CtSlideLabel(const CtSize& Size, const char* ucStr);
	
	bool handleTouchEvent(const CtEventTouch& Touch);

protected:

private:
	void init();
	void TouchAction_Press(long _x, long _y);
	void TouchAction_Release();
	bool TouchAction_Slide(CtEventTouchSlide & _slide);

private:
	bool m_IsAction;

};


#endif
