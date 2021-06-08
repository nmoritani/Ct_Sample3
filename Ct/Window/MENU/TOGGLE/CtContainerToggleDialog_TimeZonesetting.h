/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerToggleDialog_TimeZonesetting_H__
#define __CtContainerToggleDialog_TimeZonesetting_H__

#include "CtContainerToggleDialog.h"

class CtContainerToggleDialog_TimeZonesetting : public CtContainerToggleDialog
{
/*** �萔 ***************************************/
public:

protected:

private:
	typedef struct TimeZoneTable {
		int id;
		char* str;
	}TimeZoneTable;

/*** ���\�b�h ***********************************/
public:
	CtContainerToggleDialog_TimeZonesetting(CtWindowID id);
	virtual ~CtContainerToggleDialog_TimeZonesetting();

protected:
	virtual CtLayout* createToggle();

	virtual bool executionSet();

private:

/*** �����o   ***********************************/
public:

protected:

private:
	static TimeZoneTable TimeZone[];

};

#endif
