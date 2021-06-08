/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerIndicateFrame_H_
#define __CtContainerIndicateFrame_H_

#include "Ct.h"
#include "CtWidget.h"
#include "CtLabel.h"
#include "CtContainer.h"
#include "CtWidgetIndicateFrame.h"

class CtContainerIndicateFrame : public CtContainer {
public :
	CtContainerIndicateFrame(CtFrameType Type);
	CtContainerIndicateFrame(CtFrameType Type, const CtRect& Base,const CtRect& Bar,CtMargin Margin);
	CtContainerIndicateFrame(CtFrameType Type, const CtRoundRect& Base,const CtRoundRect& Bar,CtMargin Margin);


	virtual ~CtContainerIndicateFrame();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();

	void setPercent(int Pencent);

	void setBaseColor(const CtColor& fillColor,int edgeWidth, const CtColor& edgeColor);

	void setBarMargin(const CtMargin& Margin);

    void initScrollBar(unsigned int InitIndex, unsigned int MaxNum);
    
    void setIndex(unsigned int Index);

    void setDisable(bool Flag);

	inline int getMaxNum();

	inline int getIndex();

private :

	CtWidgetIndicateFrame*	m_pProgressBar;
	CtRect*					m_pRect;
  	CtRect*					m_pBarRect;
	CtRoundRect*			m_pRoundRect;
	CtRoundRect*			m_pBarRoundRect;
	CtLabel*				m_pLabel;
	CtFrameType				m_Type;
	CtMargin				m_BarMargin;
};

inline int CtContainerIndicateFrame::getIndex(){
    return m_pProgressBar->getIndex();
}

inline int CtContainerIndicateFrame::getMaxNum(){
    return m_pProgressBar->getMaxNum();
}

#endif


