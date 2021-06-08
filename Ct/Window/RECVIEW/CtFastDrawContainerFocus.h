/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtFastDrawContainerFocus
 */


#ifndef __CtFastDrawContainerFocus_H__
#define __CtFastDrawContainerFocus_H__

#include "CtRecViewContainer.h"
#include "CtHLayout.h"
#include "CtICManager.h"

class CtFastDrawContainerFocus : public CtRecViewContainer
{
private:
	enum {
		F_0,
		F_1,
		F_2,
		F_3,
		F_4,
		F_5,
		F_6,
		F_7,
		F_8,
		F_9,
		F_F,
		F_F_Macro,
		F_A,
		F_A_Macro,
		F_M,
		F_M_Macro,
		F_m,
		F_f,
		F_t,
		F_Dot,
		F_Space,
		F_Max
	}FocusValueId;

#define FOCUS_WORD_COUNT 10

public:
	CtFastDrawContainerFocus();
	virtual			~CtFastDrawContainerFocus();
	virtual bool	startupContainer();
	virtual bool	handleParamEvent(const CtEventParam& Param);
	virtual bool	setStatusMode(bool bStatusMode) ;

	CtLayout*		createContainer();
	bool			destroyContainer();
	bool			updateFastDraw();

private:
	bool			buildStringNumType(unsigned int FocusVal, int& PaddingNum);
	bool			buildStringMmType(unsigned int FocusVal, int valLen, bool bFocusInfi, int& PaddingNum);
	bool			buildStringFeetType(unsigned int FocusVal, int valLen, bool bFocusInfi, int& Num);
	bool			m_pFocusInvalidvalue;
	CtLayout*		m_pAll;

	CtStackLabel*	m_pMugenMacro;
	CtHLayout*		m_pNumberLayout;
	CtHLayout*		m_pMmLayout;
	CtHLayout*		m_pFeetLayout;
	CtLabel*		m_pNumMacro;
	CtLabel*		m_pMmMugen;
	CtLabel*		m_pMmMacro;
	CtLabel*		m_pFeetMugen;
	CtLabel*		m_pFeetMacro;
	
	CtStackLabel*	m_pFocusValue[FOCUS_WORD_COUNT];

	APL_SYS_PARAM_INDICATOR_ZOOMFOCUS m_FocusDispMode;
	bool			updateFocusDispMode(int int_Data = -1);
	bool			m_bMacroMode;		 // AplParamFocusMacro
	bool			updateMacroMode(int int_Data = -1);
	bool			m_bMnlMode;			 // AplParamFocusMode
	bool			updateMnlMode(int int_Data = -1);
	bool			m_bMfAutoAssistMode; // AplParamMfAutoAssist
	bool			updateMfAutoAstMode(int int_Data = -1);
	
};
#endif
