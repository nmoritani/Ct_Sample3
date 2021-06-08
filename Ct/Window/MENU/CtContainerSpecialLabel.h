/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:	CtButton
 */
 
#ifndef __CtContainerSpecialLabel_H_
#define __CtContainerSpecialLabel_H_

#include "CtWindowCommon.h"
#include "CtMenuInfo.h"
#include "CtParamBox.h"
#include "CtLanguage.h"

class CtContainerSpecialLabel : public CtContainer
{
public :
	CtContainerSpecialLabel(CtMenuInfo::CtMenuButtonInfo* pInfo);
	virtual ~CtContainerSpecialLabel();
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);

private:
	CtLayout* createLabel();
	bool updateLabel_Omit();
	bool updateLabel_Indicator();
	bool updateLabel_ChromaLevel();
	bool updateLabel_FileSelect();
	bool updateLabel_SynchroScan();

private:
	CtLayout* m_pLayout;
	CtLabel* m_pLabel;
	CtStackLabel* m_pStack;
	CtMenuInfo::CtMenuButtonInfo* m_pInfo;

};

#endif
