#include "CtWindowContentsFactHourMeter.h"

CtWindowContentsFactHourMeter::CtWindowContentsFactHourMeter(const CtWindowID WindowID) :
	CtWindowContents(WindowID),
	m_HourMeterList(0)
{
}
CtWindowContentsFactHourMeter::CtWindowContentsFactHourMeter(CtWindowContentsFactHourMeter& contents) :
	CtWindowContents(contents.getType()),
	m_HourMeterList(0)
{
	HourMeterList& list = contents.getHourMeterList();

	for (HourMeterListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
		HourMeterInfo Info = *Itr;
		m_HourMeterList.push_back(Info);
	}
}

CtWindowContentsFactHourMeter::~CtWindowContentsFactHourMeter()
{
	m_HourMeterList.clear();
}

CtWindowContentsFactHourMeter::HourMeterList& CtWindowContentsFactHourMeter::getHourMeterList()
{
	return m_HourMeterList;
}
void CtWindowContentsFactHourMeter::setHourMeterInfo(HourMeterInfo info)
{
	m_HourMeterList.push_back(info);
}
