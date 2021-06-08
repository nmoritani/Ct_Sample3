/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetControl
 */


#ifndef __CtFastDrawContainerZoom_H__
#define __CtFastDrawContainerZoom_H__

#include "CtRecViewContainer.h"
#include "CtHLayout.h"
#include "CtICManager.h"

class CtFastDrawContainerZoom : public CtRecViewContainer
{
	#define ZoomDigit 8		/* iZ**.*mm(iZ***) */
public:
	
	typedef enum ZoomPartsNumber {
		ZoomPartsNumber_0,
		ZoomPartsNumber_1,
		ZoomPartsNumber_2,
		ZoomPartsNumber_3,
		ZoomPartsNumber_4,
		ZoomPartsNumber_5,
		ZoomPartsNumber_6,
		ZoomPartsNumber_7,
		ZoomPartsNumber_8,
		ZoomPartsNumber_9,
		ZoomPartsNumber_i,
		ZoomPartsNumber_IaAct,
		ZoomPartsNumber_Z,
		ZoomPartsNumber_FastAct,
		ZoomPartsNumber_m,
		ZoomPartsNumber_dot,
		ZoomPartsNumber_Space,
		ZoomPartsNumber_Max,
	}ZoomPartsNumber;

	typedef enum ZoomDispType {
		ZoomDispType_Pos,
		ZoomDispType_Mm,
		ZoomDispType_Nodisp,
		ZoomDispType_Max,
	}ZoomDispType;

public :
    CtFastDrawContainerZoom();
    virtual ~CtFastDrawContainerZoom();
	CtLayout* createContainer();
	
	virtual bool destroyContainer();
	virtual bool setStatusMode(bool bStatusMode) ;
	virtual bool startupContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool updateFastDraw();

	bool setIaActState();
	bool setFastActState(bool bAct);
private :
	CtHLayout* m_pAll;
	CtStackLabel*	m_pLabel[ZoomDigit];

	ZoomDispType   m_Type;
	
	bool m_bFastZoomAct;
	bool m_bIaMode;
	bool setDispMode();
	bool m_ZoomInvalidValue;
};


#endif
