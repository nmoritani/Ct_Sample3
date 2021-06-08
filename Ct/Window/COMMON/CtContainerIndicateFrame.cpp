#include "CtContainerIndicateFrame.h"
#include "CtHLayout.h"


CtContainerIndicateFrame::CtContainerIndicateFrame(CtFrameType Type) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
    m_pLabel(NULL),
    m_Type(Type),
	m_pBarRect(NULL),
	m_pBarRoundRect(NULL)
{

}

CtContainerIndicateFrame::CtContainerIndicateFrame(CtFrameType Type, const CtRect& Base,const CtRect& Bar,CtMargin Margin) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
    m_pLabel(NULL),
    m_Type(Type),
	m_pBarRect(NULL),
	m_pBarRoundRect(NULL)
{
    m_pRect = new CtRect(Base);
    m_pBarRect = new CtRect(Bar);

    m_BarMargin = Margin;
}

CtContainerIndicateFrame::CtContainerIndicateFrame(CtFrameType Type, const CtRoundRect& Base,const CtRoundRect& Bar,CtMargin Margin) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
    m_pLabel(NULL),
    m_Type(Type),
	m_pBarRect(NULL),
	m_pBarRoundRect(NULL)
{
    m_pRoundRect = new CtRoundRect(Base);
    m_pBarRoundRect = new CtRoundRect(Bar);

    m_BarMargin = Margin;
}

CtContainerIndicateFrame::~CtContainerIndicateFrame(){
    if(m_pRect != NULL){
        delete m_pRect;
        m_pRect = NULL;
    }

    if(m_pBarRect != NULL){
        delete m_pBarRect;
        m_pBarRect = NULL;
    }

    if(m_pRoundRect != NULL){
        delete m_pRoundRect;
        m_pRoundRect = NULL;
    }
    
    
    if(m_pBarRoundRect != NULL){
        delete m_pBarRoundRect;
        m_pBarRoundRect = NULL;
    }
}

CtLayout* CtContainerIndicateFrame::createContainer(){
    CtLayout *pLayoutMain = new CtLayout();

    if(m_pRoundRect != NULL){
        m_pLabel = new CtLabel(*m_pRoundRect);
    }else if(m_pRect != NULL){
        m_pLabel = new CtLabel(*m_pRect);
    }else{
        m_pLabel = new CtLabel(CtRoundRect(CtColor::Gray,1,CtColor::Gray));
    }

    pLayoutMain->addWidget(m_pLabel);

    CtHLayout *pLayoutProgressBar = new CtHLayout();
    if(m_pRoundRect != NULL){
		m_pProgressBar = new CtWidgetIndicateFrame(m_Type, *m_pBarRoundRect);
    }else if(m_pRect != NULL){
        m_pProgressBar = new CtWidgetIndicateFrame(m_Type,*m_pBarRect);
    }else{
        m_pProgressBar = new CtWidgetIndicateFrame(m_Type);
    }

    pLayoutProgressBar->addWidget(m_pProgressBar);

    pLayoutMain->addWidget(pLayoutProgressBar, m_BarMargin);

    return pLayoutMain;
}

bool CtContainerIndicateFrame::destroyContainer(){
    return true;
}

void CtContainerIndicateFrame::setPercent(int Pencent){
    m_pProgressBar->setPercent(Pencent);
}

void CtContainerIndicateFrame::setBaseColor(const CtColor& fillColor,int edgeWidth, const CtColor& edgeColor){
    m_pLabel->setColor(fillColor, edgeColor);
#if 0 //@salvage
    m_pLabel->setWidth(edgeWidth);
#endif
}

void CtContainerIndicateFrame::setBarMargin(const CtMargin& Margin){
#if 0 //@salvage
    m_pProgressBar->setMargin(Margin);
#endif
}

void CtContainerIndicateFrame::initScrollBar(unsigned int InitIndex, unsigned int MaxNum){
    m_pProgressBar->initScrollBar(InitIndex,MaxNum);
}

void CtContainerIndicateFrame::setIndex(unsigned int Index){
    m_pProgressBar->setIndex(Index);
}

void CtContainerIndicateFrame::setDisable(bool Flag){
    if(m_Type == CT_FRAME_TYPE_SCROLL_BAR){
        if(m_pProgressBar != NULL){
            if(Flag){
               m_pLabel->setColor(CtColor(ColorRGBA, 0x000000ff, NULL),CtColor(ColorRGBA, 0x464646ff, NULL));
            }else{
               m_pLabel->setColor(CtColor(ColorRGBA, 0x000000ff, NULL),CtColor(ColorRGBA, 0x333333ff, NULL));
            }
            m_pProgressBar->setVisible(Flag);
        }
    }
}
