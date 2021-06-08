#include "CtContainerPlayViewProgress.h"
#include "CtHLayout.h"


CtContainerPlayViewProgress::CtContainerPlayViewProgress(CtFrameType Type) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
	m_pBarRect(NULL),
	m_pBarRoundRect(NULL),
    m_pBase(NULL),
    m_pScrollBar(NULL),
    m_pLayoutMain(NULL),
    m_bTouchAction(false),
    m_BaseMargin(CtMargin(0)),
    m_PbMargin(CtMargin(0)),
    m_ScrollBarMargin(CtMargin(0)),
    m_Type(Type)
{

}

CtContainerPlayViewProgress::CtContainerPlayViewProgress(CtFrameType Type, const CtRect& Base,const CtRect& ProgressBar,CtLabel* ScrollBar, CtMargin MarginBase, CtMargin MarginProgressBar) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
    m_pBarRect(NULL),
    m_pBarRoundRect(NULL),
    m_pBase(NULL),
    m_pScrollBar(NULL),
    m_pLayoutMain(NULL),
    m_ScrollBarMargin(CtMargin(0)),
    m_bTouchAction(false),
    m_Type(Type)
{
    m_pRect = new CtRect(Base);
    m_pBarRect = new CtRect(ProgressBar);
    m_pScrollBar = ScrollBar;

    m_BaseMargin = MarginBase;
    m_PbMargin = MarginProgressBar;
}

CtContainerPlayViewProgress::CtContainerPlayViewProgress(CtFrameType Type, const CtRoundRect& Base,const CtRoundRect& ProgressBar,CtLabel* ScrollBar, CtMargin MarginBase, CtMargin MarginProgressBar) :
    m_pProgressBar(NULL),
    m_pRect(NULL),
    m_pRoundRect(NULL),
	m_pBarRect(NULL),
	m_pBarRoundRect(NULL),
    m_pBase(NULL),
    m_pScrollBar(NULL),
    m_pLayoutMain(NULL),
    m_ScrollBarMargin(CtMargin(0)),
    m_bTouchAction(false),
    m_Type(Type)
{
    m_pRoundRect = new CtRoundRect(Base);
    m_pBarRoundRect = new CtRoundRect(ProgressBar);
    m_pScrollBar = ScrollBar;

    m_BaseMargin = MarginBase;
    m_PbMargin = MarginProgressBar;
}

CtContainerPlayViewProgress::~CtContainerPlayViewProgress(){
    if(m_pRect != NULL){
        delete m_pRect;
    	m_pRect = NULL;
    }

    if(m_pRoundRect != NULL){
        delete m_pRoundRect;
    	m_pRoundRect = NULL;
    }

    if(m_pBarRect != NULL){
        delete m_pBarRect;
    	m_pBarRect = NULL;
    }

    if(m_pBarRoundRect != NULL){
        delete m_pBarRoundRect;
    	m_pBarRoundRect = NULL;
    }

	if(m_pTouchArea != NULL){
		delete m_pTouchArea;
		m_pTouchArea = NULL;
	}
}

CtLayout* CtContainerPlayViewProgress::createContainer(){
    m_pLayoutMain = new CtLayout();
	m_pTouchArea = new  CtLayout();

    if(m_pRoundRect != NULL){
        m_pBase = new CtLabel(*m_pRoundRect);
    }else if(m_pRect != NULL){
        m_pBase = new CtLabel(*m_pRect);
    }else{
        m_pBase = new CtLabel(CtRoundRect(CtColor::Gray,1,CtColor::Gray));
    }

    m_pLayoutMain->addWidget(m_pBase);
	//m_pBase->setMargin(m_BaseMargin);

    CtHLayout *pLayoutProgressBar = new CtHLayout();
    if(m_pRoundRect != NULL){
        m_pProgressBar = new CtWidgetIndicateFrame(m_Type,*m_pBarRoundRect);
    }else if(m_pRect != NULL){
        m_pProgressBar = new CtWidgetIndicateFrame(m_Type,*m_pBarRect);
    }else{
        m_pProgressBar = new CtWidgetIndicateFrame(m_Type);
    }

    pLayoutProgressBar->addWidget(m_pProgressBar);
    //m_pProgressBar->setMargin(m_PbMargin);

    m_pLayoutMain->addWidget(pLayoutProgressBar);
    m_pLayoutMain->addWidget(m_pScrollBar,AlignLeft);

    m_pLayoutMain->setScreenSel(ScreenLCD);

    return m_pLayoutMain;
}

bool CtContainerPlayViewProgress::destroyContainer(){
    return true;
}

void CtContainerPlayViewProgress::setPercent(int Percent){
    if(m_bTouchAction){
        return;
    }

    if(Percent > 100){
        Percent = 100;
    }else if(Percent < 0){
        Percent = 0;
    }

    m_pProgressBar->setPercent(Percent);
    caculateScrollBarRegion(Percent);
}


bool CtContainerPlayViewProgress::handleTouchEvent(const CtEventTouch & Event){
    int Percent = m_pProgressBar->getPercent();
    bool isRedraw = false;
    CtWindowContentsPlayControlState::PressType type = CtWindowContentsPlayControlState::Invalid;

    CtEventTouch::TouchPosition pos = Event.getPosition();
    CtPosition Pos;

    Pos.x = pos.m_X;
    Pos.y = pos.m_Y;

    if(!m_pLayoutMain->isVisible()){
        return isRedraw;
    }

	m_pTouchArea->setRegion(CtRegion( m_pLayoutMain->getRegion().x,
									  m_pLayoutMain->getRegion().y - 60,
									  m_pLayoutMain->getRegion().width,
									  m_pLayoutMain->getRegion().height + 90 ));

    if(false == m_pTouchArea->isContains(Pos)){
        if(m_bTouchAction){
        	updateReleaseMotion(Event);
        	{
			    CtWindowContentsPlayControlState Content = CtWindowContentsPlayControlState(Window_PlayView);
			    Content.setProgress(Percent);
			    Content.setPressType(CtWindowContentsPlayControlState::Release);
				CtEventInterface::requestFuncCmd(FuncID_PLAYSEEK, m_pLayout->getWindow(), &Content);
        	}
        }
        return isRedraw;
    }

    Percent = m_pProgressBar->getPercent();

    switch(Event.getAction()){
	case CtEventTouch::Press:
		updatePressMotion(Event);
		type = CtWindowContentsPlayControlState::Press;
		break;
	case CtEventTouch::Move:
		if( m_bTouchAction ){
			updateTouchMotion(Event);
			type = CtWindowContentsPlayControlState::Repeat;
		} else {
			updatePressMotion(Event);
			type = CtWindowContentsPlayControlState::Press;
		}
		break;
	case CtEventTouch::Release:
		updateReleaseMotion(Event);
		type = CtWindowContentsPlayControlState::Release;
		break;
	default:
		break;
    }

	if ((type == CtWindowContentsPlayControlState::Press) ||
		(type == CtWindowContentsPlayControlState::Release) ||
		((type == CtWindowContentsPlayControlState::Repeat) && (Percent != m_pProgressBar->getPercent()))) {
		CtWindowContentsPlayControlState Content = CtWindowContentsPlayControlState(Window_PlayView);
		Content.setProgress(Percent);
		Content.setPressType(type);
		CtEventInterface::requestFuncCmd(FuncID_PLAYSEEK, m_pLayout->getWindow(), &Content);
        isRedraw = true;
	}

    return isRedraw;
}

void CtContainerPlayViewProgress::caculateScrollBarRegion(int Percent){
    CtRegion TempRegion;
    CtRegion Region = m_pLayoutMain->getRegion();

    TempRegion.y = Region.y;
    TempRegion.width = Region.height;
    TempRegion.height = Region.height;

    TempRegion.x = Region.x + m_ScrollBarMargin.Left + (Region.width - Region.height - m_ScrollBarMargin.Left - m_ScrollBarMargin.Right) * Percent / 100;/* pgr0351 */


    m_pScrollBar->setRegion(TempRegion);
}

void CtContainerPlayViewProgress::updateTouchMotion(const CtEventTouch & Event){
    int Percent = 0;

    CtEventTouch::TouchPosition pos = Event.getPosition();
    CtRegion Region = m_pBase->getRegion();
    CtPosition Pos;

    Pos.x = pos.m_X;

        if(Pos.x >= Region.x + Region.width){
            Percent = 100;
        }else if(Pos.x <= Region.x){
            Percent = 0;
        }else{
            Percent = ((Pos.x - Region.x) * 100) / Region.width;
    }

    m_pProgressBar->setPercent(Percent);
    caculateScrollBarRegion(Percent);
}

void CtContainerPlayViewProgress::updatePressMotion(const CtEventTouch & Event){
    m_bTouchAction = true;

    updateTouchMotion(Event);
}

void CtContainerPlayViewProgress::updateReleaseMotion(const CtEventTouch & Event){
    m_bTouchAction = false;
}

bool CtContainerPlayViewProgress::handleParamEvent(const CtEventParam& Param){
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    if(AplParamStatusPlaySeekBar != t_Id){
        return false;
    }

    setPercent(int_Data);

    return true;
}
