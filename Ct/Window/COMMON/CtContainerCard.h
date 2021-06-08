/**
 *  Copyright (c) 2018 Person AVC Technology
 *  Element:	CtContainerCard
 */
 
#ifndef __CtContainerCard_H_
#define __CtContainerCard_H_

#include "Ct.h"
#include "CtWidget.h"
#include "AplParamService.h"
#include "CtWindowCommon.h"
#include "CtICManager.h"

class CtContainerCard : public CtRecViewContainer {
public :

	CtContainerCard(CtWindowCommonType Type);

	~CtContainerCard();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param) = 0;

protected :
	CtLayout* createRecMode();

	CtLayout* createHomeMode();

	// Slotの記録状態
	virtual void updateRecState(int int_Data) { return; };

	// Slotのカード状態
	virtual void updateCardState(int int_Data) { return; };

	// Slotの残量状態
	virtual void updateSlotRemain(int int_Data) = 0;

	virtual CtScreenSel getDispIcModeSel(int IcId);
	enum IconType{
		IconType_OSD_SD_OFF,
		IconType_OSD_SD_ON,
		IconType_SD_OFF,
		IconType_SD_ON,
	};
	virtual GDI_IMAGE_ID getIcon(IconType type) = 0;

protected:
	
	/**********************  attributes **********************/
	CtLayout*				m_pAll;

	CtStackLabel*			m_pState;

	CtLabel*				m_pHomeState;

	CtStackLabel*			m_pSlotNum;

	CtHLayout*				m_pRecCardStatus;// registWidget

	CtLabel*				m_pSlotTime;

	CtLabel*				m_pLabel_Min;

	CtStackLabel*			m_pSlotRemain;
	
	CtHLayout*				m_pSlotRemainMin;

	CtLayout*				m_pRemainStatus;// registWidget

	CtWindowCommonType		m_Type;

	bool					m_StateFlash;

	bool					m_CardStateFlash;

	bool					m_RemainFlash;

private:
	CtScreenSel checkRecCardStatusScrnSel();
	CtScreenSel checkRemainStatusScrnSel();
	bool		isRemainUnder2min();
};

#endif

