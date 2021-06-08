/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerPlayViewProgress_H_
#define __CtContainerPlayViewProgress_H_

#include "Ct.h"
#include "CtWindowCommon.h"
#include "CtWidgetIndicateFrame.h"
#include "AplParamService.h"
#include "CtWindowContentsPlayControlState.h"


class CtContainerPlayViewProgress : public CtContainer {
public :
	CtContainerPlayViewProgress(CtFrameType Type);
	CtContainerPlayViewProgress(CtFrameType Type, const CtRect& Base,const CtRect& ProgressBar,CtLabel* ScrollBar, CtMargin MarginBase = CtMargin(0), CtMargin MarginProgressBar = CtMargin(0));
	CtContainerPlayViewProgress(CtFrameType Type, const CtRoundRect& Base,const CtRoundRect& ProgressBar,CtLabel* ScrollBar, CtMargin MarginBase = CtMargin(0), CtMargin MarginProgressBar = CtMargin(0));


	virtual ~CtContainerPlayViewProgress();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();

	void setPercent(int Percent);

	//void setBaseColor(const CtColor& fillColor,int edgeWidth, const CtColor& edgeColor);

	//void setDisable(bool Flag);

	virtual bool handleTouchEvent(const CtEventTouch & Event);

	virtual bool handleParamEvent(const CtEventParam& Param);

	inline int getPercent();

	inline void setProgressBarMargin(CtMargin Margin);

	inline void setBaseMargin(CtMargin Margin);

	inline void setScrollBarMargin(CtMargin Margin);

	inline void setScrollBarSize(CtSize Size);

	inline bool isTouched();

	inline void setTouchAction(bool isTouch);

private :
	void caculateScrollBarRegion(int Percent);
  	void updateTouchMotion(const CtEventTouch & Event);
  	void updatePressMotion(const CtEventTouch & Event);
  	void updateReleaseMotion(const CtEventTouch & Event);

	CtWidgetIndicateFrame*	m_pProgressBar;
	CtRect*					m_pRect;
	CtRect*					m_pBarRect;
	CtRoundRect*			m_pRoundRect;
	CtRoundRect*			m_pBarRoundRect;
	CtLabel*				m_pBase;
	CtFrameType				m_Type;
	bool					m_bTouchAction;
	CtLabel*				m_pScrollBar;
	CtMargin				m_BaseMargin;
	CtMargin				m_PbMargin;
	CtMargin				m_ScrollBarMargin;
	CtLayout*				m_pLayoutMain;
	CtLayout*				m_pTouchArea;
	
};

inline int CtContainerPlayViewProgress::getPercent(){
    return m_pProgressBar->getPercent();
}

inline void CtContainerPlayViewProgress::setProgressBarMargin(CtMargin Margin){
    //m_pProgressBar->setMargin(Margin);
}

inline void CtContainerPlayViewProgress::setBaseMargin(CtMargin Margin){
	//    m_pBase->setMargin(Margin);
}

inline void CtContainerPlayViewProgress::setScrollBarMargin(CtMargin Margin){
	//m_ScrollBarMargin = Margin;
}

inline void CtContainerPlayViewProgress::setScrollBarSize(CtSize Size){
	//m_pScrollBar->setSize(Size);
}

inline bool CtContainerPlayViewProgress::isTouched(){
    return m_bTouchAction;
}

inline void CtContainerPlayViewProgress::setTouchAction(bool isTouch){
    m_bTouchAction = isTouch;
}

#endif
