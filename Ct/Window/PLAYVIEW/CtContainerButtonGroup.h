/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerButtonGroup_H_
#define __CtContainerButtonGroup_H_

#include "Ct.h"
#include "CtWidget.h"
#include "AplParamService.h"
#include "CtWindowCommon.h"
#include "CtContainerButtonGroup.h"
#include "CtWindowContentsPlayControlState.h"

typedef enum KeyTimerUid{
	KeyTimer_FastForward,
	KeyTimer_Rewind,
	KeyTimer_Stop,
	KeyTimer_PlayPause,
	KeyTimer_Navi,
	KeyTimer_Max
}KeyTimerUid;

class CtContainerButtonGroup : public CtContainer {
public :
	CtContainerButtonGroup();

	virtual ~CtContainerButtonGroup();

	virtual CtLayout* createContainer();
	virtual bool startupContainer();
	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);

	virtual bool handleButtonEvent(const CtEventButton& Button);

	virtual bool handleKeyEvent(const CtEventKey& Key);

	virtual bool isBtnsContain(const CtPosition& Pos);

	CtWidget*	getDefaultFocusWidget();

private :

	void updateStatusPlay();
	bool updateCapState(int int_Data);
	/**********************  attributes **********************/
	CtVLayout*						m_pBtnGroup;
	CtToggleButton*						m_pFastForward;

	CtStackLabel*					m_pFFStackLabel;

	CtToggleButton*						m_pRewind;

	CtStackLabel*					m_pRwStackLabel;

	CtToggleButton*						m_pCapture;

	CtToggleButton*						m_pStop;

	CtToggleButton*						m_pPlayPause;

	CtWindowContentsPlayControlState *m_pContents;
};

#endif
