/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerBattery_H_
#define __CtContainerBattery_H_

#include "Ct.h"
#include "CtWidget.h"
#include "AplParamService.h"
#include "CtWindowCommon.h"
#include "CtICManager.h"

typedef struct Battery_Res_Table{
	GDI_IMAGE_ID RecResID;
	GDI_IMAGE_ID HomeResID;
}Battery_Res_Table;

class CtContainerBattery : public CtRecViewContainer {
public :
    #define Bat_Res_Max_Num 8

	CtContainerBattery(CtWindowCommonType Type = CT_COMMON_TYPE_HOME);

	virtual ~CtContainerBattery();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();

	GDI_IMAGE_ID convertDataToImage(int int_Data);
	virtual CtScreenSel getDispIcModeSel();
	virtual bool handleParamEvent(const CtEventParam& Param);
	
private :
	void updateBattery();

	/**********************  attributes **********************/
	CtStackLabel*					m_pBattery;

	CtWindowCommonType				m_Type;

	bool							m_Flash;

	static const Battery_Res_Table	m_ImageRes[Bat_Res_Max_Num];
};

#endif
