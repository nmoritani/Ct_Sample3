/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerWifi_H_
#define __CtContainerWifi_H_

#include "Ct.h"
#include "CtWidget.h"
#include "AplParamService.h"
#include "CtWindowCommon.h"
#include "CtICManager.h"

typedef struct Wifi_Res_Table{
	GDI_IMAGE_ID RecResID;
	GDI_IMAGE_ID HomeResID;
}Wifi_Res_Table;

class CtContainerWifi : public CtRecViewContainer {
public :
	CtContainerWifi(CtWindowCommonType Type = CT_COMMON_TYPE_HOME);

	virtual ~CtContainerWifi();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);

private :

	void updateWifiDisp();

	void updateWifiIcon(int int_Data);

	void initDisplay();

	/**********************  attributes **********************/
	CtStackLabel*					m_pWifi;

	CtWindowCommonType				m_Type;

	static const Wifi_Res_Table m_ImageRes[APL_SYS_PARAM_WLAN_DISABLE];

};

#endif
