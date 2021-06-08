/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerToggleDialog_ClockSetting_H__
#define __CtContainerToggleDialog_ClockSetting_H__

#include "CtContainerToggleDialog.h"

class CtContainerToggleDialog_ClockSetting : public CtContainerToggleDialog
{
/*** 定数 ***************************************/
public:

protected:
#define CLOCKSET_CHECK_LEAP_YEAR(year)	((!((year)%4) && (year)%100) || !((year)%400))

private:
	typedef enum DateFormat {
		DateFormat_YMD,
		DateFormat_MDY,
		DateFormat_DMY,
	}DateFormat;

	typedef enum ClockType {
		ClockType_Year,
		ClockType_Month,
		ClockType_Date,
		ClockType_Hour,
		ClockType_Min,

		ClockType_Max,
	}ClockType;

/*** メソッド ***********************************/
public:
	CtContainerToggleDialog_ClockSetting(CtWindowID id);
	virtual ~CtContainerToggleDialog_ClockSetting();

protected:
	virtual CtLayout* createToggle();

	virtual void executionUpdate();
	virtual bool executionSet();

private:
	CtLayout* createLayoutDate();
	CtLayout* createLayoutTime();
	void createYear();
	void createMonth();
	void createDate();
	void createHour();
	void createMin();

	DateFormat getClockType();

/*** メンバ   ***********************************/
public:

protected:

private:
	int m_Clock[ClockType_Max];

};

#endif
