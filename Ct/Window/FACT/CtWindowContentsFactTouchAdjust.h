#pragma once
#ifndef __CtWindowContentsFactTouchAdjust_H__
#define __CtWindowContentsFactTouchAdjust_H__

#include "CtWindowContents.h"

class CtWindowContentsFactTouchAdjust : public CtWindowContents {
public:
	typedef enum _FACT_TOUCH_POS {
		FACT_TOUCH__POS_LEFT_TOP = 0,
		FACT_TOUCH__POS_LEFT_BOTTOM,
		FACT_TOUCH__POS_RIGHT_TOP,
		FACT_TOUCH__POS_RIGHT_BOTTOM,
		FACT_TOUCH__POS_CENTER,
		FACT_TOUCH__POS_MAX,
	} FACT_TOUCH_POS;

	typedef struct _FactTouchPos {
		FACT_TOUCH_POS Pos;
		int x;
		int y;
	} FactTouchPos;

	CtWindowContentsFactTouchAdjust(const CtWindowID WindowID);
	virtual ~CtWindowContentsFactTouchAdjust();
	virtual void setContentsFactTouchPos(FACT_TOUCH_POS pos, int x, int y);
	virtual FactTouchPos getContentsFactTouchPos();
	virtual void setFactTouchTestPos(FACT_TOUCH_POS type, bool value);
	virtual FACT_TOUCH_POS getFactTouchTestPos();

protected:

private:
	FactTouchPos m_TouchPos;

	FACT_TOUCH_POS m_touchPos;
};

#endif

