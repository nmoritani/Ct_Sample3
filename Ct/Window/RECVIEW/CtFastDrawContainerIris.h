/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetControl
 */


#ifndef __CtFastDrawContainerIris_H__
#define __CtFastDrawContainerIris_H__

#include "CtRecViewContainer.h"
#include "CtHLayout.h"
#include "CtICManager.h"

class CtFastDrawContainerIris : public CtRecViewContainer
{
	static const int IrisDigit = 7;		/* F00 *** / F0.0*** / */
	static const int OpenDigit = 4;		// OPEN
	static const int CloseDigit = 5;	// CLOSE
	
	typedef enum IrisPartsNumber {
		IrisParts_0,
		IrisParts_1,
		IrisParts_2,
		IrisParts_3,
		IrisParts_4,
		IrisParts_5,
		IrisParts_6,
		IrisParts_7,
		IrisParts_8,
		IrisParts_9,
		IrisParts_F,
		IrisParts_dot,
		IrisParts_Minus,
		IrisParts_Plus,
		IrisParts_Space,
		IrisParts_Close,
		IrisParts_Open,
		IrisParts_Max,
	}IrisPartsNumber;
	
	typedef enum IrisDispType {
		IrisDispType_Open,
		IrisDispType_Close,
		IrisDispType_Auto,
		IrisDispType_Manual,
		IrisDispType_Nodisp,
		IrisDispType_Max,
	}IrisDispType;

public :
    CtFastDrawContainerIris();
    virtual ~CtFastDrawContainerIris();
	virtual bool handleParamEvent(const CtEventParam& Param);
	CtLayout* createContainer();
	virtual bool destroyContainer();
	virtual bool startupContainer();

	bool updateFastDraw();
	bool updateAutoIrisIcon();
private :
	CtLayout*		m_pAll;
	CtLabel*		m_pAutoIris;
	bool			m_bAutoIrisDisp;
	char	m_AutoIrisLevel;
	CtStackLabel*	m_pLabel[IrisDigit];
	IrisDispType	getDispMode(void);
	IrisDispType	m_Type;
	static char m_pText[IrisParts_Max];
	bool			m_IrisLensValid;
};


#endif
