/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:	CtButton
 */
 
#ifndef __CtContainerMenuTitle_H_
#define __CtContainerMenuTitle_H_

#include "CtWindowCommon.h"
#include "CtMenuInfo.h"


#define TITLE_STRING_MAX 300
#define TITLE_DEFAULT_MAX 841
#define TITLE_SETPHASE_MAX 646

class CtContainerMenuTitle : public CtContainer
{
public:
	enum TitleType{
		Default,
		SetPhase,
	};



public:

	CtContainerMenuTitle(CtWindowID Windowid);
	virtual ~CtContainerMenuTitle();
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);

	void setColor(CtColor color);
	void setPage(CtLabel* pLabel);

private:
	void updateTitle();
	unsigned short* getString(int id);

private:
	CtWindowID m_WindowID;
	CtMenuInfo::CtMenuWindowInfo* m_pInfo;
	CtLabel* m_pTitle;
	CtLabel* m_pPage;
	CtColor m_Color;

};

#endif
