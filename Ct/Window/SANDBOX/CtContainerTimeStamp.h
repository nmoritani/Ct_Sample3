/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtContainer
 */


#ifndef __CtContainerTimeStamp_H__
#define __CtContainerTimeStamp_H__

#include "CtContainer.h"
#include "SysIf.h"

class CtContainerTimeStamp : public CtContainer {
public :
    CtContainerTimeStamp(CtSize size, CtColorFormat colorFormat, int colorDepth);
    virtual ~CtContainerTimeStamp();

	virtual bool startupWindow();
	virtual bool updateFastDraw();

private :
	enum CtDateFormat {
		CtDateFormatYMD,
		CtDateFormatMDY,
		CtDateFormatDMY,
	};

	enum CtTsDisp {
		CtTsDispOff = 0,
		CtTsDispDate = (1 << 0),
		CtTsDispTime = (1 << 2),
		CtTsDispDateTime = CtTsDispDate | CtTsDispTime,
	};

	struct drawables {
		GDI_HANDLER Month[3];
		GDI_HANDLER Separator;
		GDI_HANDLER Dec[10];
		GDI_HANDLER Space;
	} m_Drawables;

	struct DateTimeDrawabales {
		GDI_HANDLER Year[4];
		GDI_HANDLER Month[3];
		GDI_HANDLER Day[2];
		GDI_HANDLER Hour[2];
		GDI_HANDLER Min[2];
		GDI_HANDLER Sec[2];
	} m_DateDrawables;

	CtSize m_Size;
	CtSize m_CharSize;
	CtColorFormat m_ColorFormat;
	int m_ColorDepth;

	CtDateFormat m_Format;
	CtTsDisp m_Disp;
	CtLabel *m_Label[4 + 3 + 2 + 8 + 1 * 3];	// 4:Year, 3:Month, 2:Day 8:HH:MM:SS, 1*3:Space

	int m_Month;	// 1-12

private:
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();
	CtSize getLabelSize();
	CtDateFormat getFormat();
	CtTsDisp getDispMode();
	int getTimeStampLength();

	CtLayout *createLayout();
	void createDrawables();
	void createDrawablesMonth();
	DateTimeDrawabales getDateTimeDrawables(const SYS_DATE_TIME &date);
};

#endif
