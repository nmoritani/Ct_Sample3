#pragma once
#ifndef __CtWindowContentsFactHourMeter_H__
#define __CtWindowContentsFactHourMeter_H__

#include "CtWindowContents.h"
#include "CtVector.h"

class CtWindowContentsFactHourMeter : public CtWindowContents {
public:
	typedef struct _HourMeterInfo {
		char name[20];
		char data[20];
	} HourMeterInfo;

	typedef CtVector::Vector<HourMeterInfo> HourMeterList;
	typedef CtVector::Vector<HourMeterInfo>::iterator HourMeterListItr;

	CtWindowContentsFactHourMeter(const CtWindowID WindowID);
	CtWindowContentsFactHourMeter(CtWindowContentsFactHourMeter& contents);
	virtual ~CtWindowContentsFactHourMeter();

	HourMeterList& getHourMeterList();
	void setHourMeterInfo(HourMeterInfo info);

protected:

private:
	HourMeterList m_HourMeterList;

};

#endif

