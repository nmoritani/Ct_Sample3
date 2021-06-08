/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtContainerMml_H__
#define __CtContainerMml_H__

#include "Ct.h"
#include "AplParamService.h"
#include "CtRecViewContainer.h"
#include "CtMmlLayout.h"
#include "CtStackLabel.h"

class CtContainerMml : public CtRecViewContainer
{
private:
	enum {
		CT_TIMER_ID_MML_ACT,
	};
	enum MODE {
		SELECT,
		CONFIG
	};
	enum CHECKBOX {
		ICONS,
		WHITE,
		
		SHUTTER,
		VFR,
		AREA,
		AF_AREA,
		CHECKBOX_MAX,
		SYNCRO,
	};
public:

	CtContainerMml();
	virtual bool destroyWindow();
	virtual CtLayout* createContainer();
protected:
	~CtContainerMml();
public:
	virtual bool handleParamEvent(const CtEventParam& Param);
	bool setConfigMode(CHECKBOX configId = CHECKBOX_MAX);
	bool setSelectMode(CHECKBOX selectMode = CHECKBOX_MAX);
	bool isValidMmlFunc(CtContainerMml::CHECKBOX MmrCheckBox = ICONS);
	CHECKBOX getNextMmlCheckBoxItem(bool bNext = true/* false = Prev */);

	virtual bool handleKeyEvent(const CtEventKey& Key);
private:
	bool exec();
	bool inc(const CtEventKey::KeyTimerLevel _lv = CtEventKey::Level_Invalid);
	bool dec(const CtEventKey::KeyTimerLevel _lv = CtEventKey::Level_Invalid);
	bool cancel();
	bool areaPos(CtEventKey::KeyCode KeyCode);
public:
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
private:
	bool setActionMode(bool bAction);

public:
	virtual bool linkAct() { return false; };
	virtual bool registLinkLabels(CtMmlLayout* pWb, CtMmlLayout* pShutter, CtMmlLayout* pFrameRate);

private:		
	bool setMmlString(CHECKBOX selectMode = CHECKBOX_MAX);
	bool m_bMmrExec;
	bool m_bFastPress;
	MODE m_MmlMode;
	CHECKBOX m_MmlCheckBox;

	CtLayout *m_pAll;
	CtRecViewFontSet m_fset;

	CtMmlLayout* m_pCrntConfig;

	CtLabel*	m_pMmlIcon;
	CtLabel*	m_pMml;
	CtMmlLayout* m_pWb;
	CtMmlLayout* m_pShutter;
	CtMmlLayout* m_pFrameRate;
};
#endif /* __CtContainerMml_H__ */

