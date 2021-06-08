/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtFastContainerTimeCode_H_
#define __CtFastContainerTimeCode_H_

#include "Ct.h"
#include "CtWidget.h"
#include "CtLabel.h"
#include "CtRecViewContainer.h"
#include "CtWindowCommon.h"
#include "CtICManager.h"

class CtFastContainerTimeCode : public CtRecViewContainer
{
private:
	static const int SeparatorNum = 3;	/* [:. ] */
	static const int CounterNum = 8;	/* [0123456789ABCDEF-] */
	static const int DigitNum = (SeparatorNum + CounterNum);

public :
	CtFastContainerTimeCode(bool bUserSuffix,CtWindowCommonType Type = CT_COMMON_TYPE_HOME);
	virtual ~CtFastContainerTimeCode();
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();
	virtual bool startupContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool setStatusMode(bool bStatusMode) ;

	void setWindowID(CtWindowID winId);

	bool updateFastDraw();
private :
	CtFontSet getFontSet();
	int getModeStr(int counter_mode);

	int getCharIndex(char c, const char* str);
	bool isSeparator(int idx);

	CtStackLabel* createSuffix();
	CtStackLabel* createCounter(bool isSeparator);
	void buildString( int t_Id, char *Str );

	CtWindowCommonType			m_Type;
	bool						m_bUseSuffix;
	bool						m_bSlaveState;
	bool updateSuffix();

	CtStackLabel*   m_pSuffixLout;
	CtStackLabel*   m_pSuffixLcd;
	CtLayout*		m_pSuffLayout;
	
	CtWindowID		m_WindowID;
	
	CtStackLabel*	m_pLabel[DigitNum];
	CtHLayout*		m_pLayoutAll;

	bool updateCounterMode(int int_Data = -1);
	
	int m_Mode;
};

#endif
