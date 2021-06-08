/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetIndicateFrame
 */


#ifndef __CtWidgetIndicateFrame_H
#define __CtWidgetIndicateFrame_H

#include "gdi.h"
#include "Ct.h"
#include "CtWidget.h"
#include "CtColor.h"
#include "CtLabel.h"
#include "CtLayout.h"

typedef enum CtFrameType{
    CT_FRAME_TYPE_PROGRESS_BAR,
    CT_FRAME_TYPE_SCROLL_BAR
}CtFrameType;

class CtWidgetIndicateFrame : public CtWidget {
    ////    Constructors and destructors    ////
public :
    virtual ~CtWidgetIndicateFrame();

    CtWidgetIndicateFrame(CtFrameType Type, const CtColor Color = CtColor::Trans);
    CtWidgetIndicateFrame(CtFrameType Type, const CtRect& Rect);
    CtWidgetIndicateFrame(CtFrameType Type, const CtRoundRect& RoundRect);
    CtWidgetIndicateFrame(CtFrameType Type, const CtEllipse& Ellipse);

    bool setColor(const CtColor& fillColor);
    bool setColor(const CtColor& fillColor, const CtColor& edgeColor);

	//    virtual void updateDrawInfo();
	virtual CtDrawInfo* getDrawInfo();
	virtual CtDrawInfo* getDrawInfo(const CtRegion& Clip, int Screen = 0);

    virtual bool setVisible(bool bVisible);
    void setPercent(int Percent);
    void initScrollBar(unsigned int InitIndex, unsigned int MaxNum);
    void setIndex(unsigned int Index);
	inline int getMaxNum();
	inline int getIndex();
	inline int getPercent();

private:
    void calculateVerticalRegion(const CtRegion& Region, int Screen);
    void calculateHorizontalRegion(const CtRegion& Region, int Screen);

	CtDrawInfo      *m_pDrawInfo;
    int                m_Percent;
    CtFrameType        m_Type;
    unsigned int        m_MaxNum;
    unsigned int        m_Index;
	CtRegion			m_DrawRegion[CT_SCREEN_NUM];
};

inline int CtWidgetIndicateFrame::getIndex(){
    return m_Index;
}

inline int CtWidgetIndicateFrame::getMaxNum(){
    return m_MaxNum;
}

inline int CtWidgetIndicateFrame::getPercent(){
    return m_Percent;
}

#endif
