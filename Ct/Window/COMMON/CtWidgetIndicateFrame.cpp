/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtWidgetIndicateFrame
 */

//#include "CtWidget.h"
#include "CtWidgetIndicateFrame.h"
#include "CtButton.h"
#include "CtStyle.h"

CtWidgetIndicateFrame::CtWidgetIndicateFrame(CtFrameType Type, const CtColor Color) :
    m_Percent(0),
    m_Type(Type),
    m_MaxNum(0),
    m_Index(0),
	m_pDrawInfo(NULL),
    CtWidget()
{
    setClassType(CtClassType_Label);
	setColor(Color);
	m_pDrawInfo = new CtRoundRect(CtRoundRect(CtColor::Blue, 1, CtColor::Blue));
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_DrawRegion[i] = CtRegion();
	}
}

CtWidgetIndicateFrame::CtWidgetIndicateFrame(CtFrameType Type, const CtRect& Rect) :
    m_Percent(0),
    m_Type(Type),
    m_MaxNum(0),
    m_Index(0),
	m_pDrawInfo(NULL),
	CtWidget()
{
    setClassType(CtClassType_Label);
	setColor(CtColor::Trans);
	m_pDrawInfo = new CtRect(Rect);
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_DrawRegion[i] = CtRegion();
	}
}


CtWidgetIndicateFrame::CtWidgetIndicateFrame(CtFrameType Type, const CtRoundRect& RoundRect) :
    m_Percent(0),
    m_Type(Type),
    m_MaxNum(0),
    m_Index(0),
	m_pDrawInfo(NULL),
    CtWidget()
{
    setClassType(CtClassType_Label);
	setColor(CtColor::Trans);
	m_pDrawInfo = new CtRoundRect(RoundRect);
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_DrawRegion[i] = CtRegion();
	}
}

CtWidgetIndicateFrame::CtWidgetIndicateFrame(CtFrameType Type, const CtEllipse& Ellipse) :
    m_Percent(0),
    m_Type(Type),
    m_MaxNum(0),
    m_Index(0),
	m_pDrawInfo(NULL),
	CtWidget()
{
    setClassType(CtClassType_Label);
	setColor(CtColor::Trans);
	m_pDrawInfo = new CtEllipse(Ellipse);
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_DrawRegion[i] = CtRegion();
	}
}

CtWidgetIndicateFrame::~CtWidgetIndicateFrame()
{
    if (m_pDrawInfo != NULL) {
        delete m_pDrawInfo;
    }
}

bool CtWidgetIndicateFrame::setColor(const CtColor& fillColor)
{
	if (!m_pDrawInfo) return false;
	
	m_pDrawInfo->setColor(fillColor);

    if (isVisible() == true)
        setInvalidate();

    return true;
}

bool CtWidgetIndicateFrame::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	if (!m_pDrawInfo) return false;
		
	m_pDrawInfo->setColor(fillColor, edgeColor);

    if (isVisible() == true)
        setInvalidate();

    return true;
}
#if 0
void CtWidgetIndicateFrame::updateDrawInfo()
{
	if (!m_pDrawInfo) return;

	m_pDrawInfo->setTrans(isTrans());
	
    if (isVisible()) setInvalidate();
}
#endif
CtDrawInfo* CtWidgetIndicateFrame::getDrawInfo()
{
	return m_pDrawInfo;
}

CtDrawInfo* CtWidgetIndicateFrame::getDrawInfo(const CtRegion& Clip, int Screen)
{
	if(m_pDrawInfo) {
		m_pDrawInfo->setRegion(m_DrawRegion[Screen]);
		m_pDrawInfo->setClip(Clip);
		m_pDrawInfo->setTrans(isTrans());
	}

	return m_pDrawInfo;
}

bool CtWidgetIndicateFrame::setVisible(const bool bVisible)
{
    if (isVisible() == bVisible)
        return false;

    return CtWidget::setVisible(bVisible);
}

void CtWidgetIndicateFrame::setPercent(int Percent)
{
    m_Percent = Percent;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		calculateHorizontalRegion(m_Region[i], i);
	}
}

void CtWidgetIndicateFrame::calculateHorizontalRegion(const CtRegion& Region, int Screen)
{
    CtRegion TempRegion;

	if (!m_pDrawInfo) return;

    switch(m_pDrawInfo->getDrawType()){
	case DrawType_RoundRect:
		TempRegion.x = Region.x;
		TempRegion.y = Region.y;
		if(m_Percent <= 1){
			TempRegion.width = 12;
		}else if(m_Percent >= 99){
			TempRegion.width = Region.width;
		}else{
			TempRegion.width = (Region.width - 12) * m_Percent; /* pgr0351 */
			if((TempRegion.width * 10 % 10) < 5 ){
				TempRegion.width = TempRegion.width / 100 + 12;/* pgr0351 */
			}else{
				TempRegion.width = TempRegion.width / 100 + 1 + 12;/* pgr0351 */
			}
		}
		TempRegion.height = Region.height;
		m_DrawRegion[Screen] = TempRegion;
		setInvalidate();
		break;
		
	case DrawType_Rect:
		TempRegion.x = Region.x;
		TempRegion.y = Region.y;
		if(m_Percent <= 1){
			TempRegion.width = 0;
		}else if(m_Percent >= 99){
			TempRegion.width = Region.width;
		}else{
			if((TempRegion.width * 10 % 10) < 5 ){
				TempRegion.width = Region.width * m_Percent / 100;/* pgr0351 */
			} else {
				TempRegion.width = Region.width * m_Percent / 100 +1;/* pgr0351 */
			}
		}
		TempRegion.height = Region.height;
		m_DrawRegion[Screen] = TempRegion;
		setInvalidate();
		break;
		
	case DrawType_Ellipse:
		TempRegion.width = Region.height;
		TempRegion.height = Region.height;
		TempRegion.y = Region.y;
		if(m_Percent <= 1){
			TempRegion.x = Region.x;
		}else if(m_Percent >= 99){
			TempRegion.x = Region.x + Region.width - Region.height;/* pgr0351 */
		}else{
			TempRegion.x = Region.x + (Region.width - Region.height) * m_Percent / 100;/* pgr0351 */
		}
		m_DrawRegion[Screen] = TempRegion;
		setInvalidate();
		break;
	default:
		return;
    }
}

void CtWidgetIndicateFrame::calculateVerticalRegion(const CtRegion& Region, int Screen)
{
	CtRegion TmpRegion;
	int height = 0;

	if (!m_pDrawInfo) return;

	switch (m_pDrawInfo->getDrawType()) {
	case DrawType_RoundRect:
		if (m_MaxNum < 2) {
			TmpRegion.x = Region.x;
			TmpRegion.y = Region.y;
			TmpRegion.width = Region.width;
			TmpRegion.height = 0;
		}
		else {
			if (m_MaxNum <= 47) {
				TmpRegion.y = Region.y + Region.height * (m_Index - 1) / m_MaxNum;/* pgr0351 */
			}
			else {
				TmpRegion.y = Region.y + (Region.height - Region.height / m_MaxNum) * (m_Index - 1) / (m_MaxNum - 1);/* pgr0351 */
			}

			height = Region.height / m_MaxNum;
			if (height < 4) {
				height = 4;
			}

			if (m_Index < 1) {
				TmpRegion.x = Region.x;
				TmpRegion.y = Region.y;
				TmpRegion.width = Region.width;
				TmpRegion.height = Region.height / m_MaxNum;/* pgr0351 */
			}
			else if ((m_Index >= 1) && (m_Index < m_MaxNum)) {
				TmpRegion.x = Region.x;
				TmpRegion.width = Region.width;
				TmpRegion.height = height;/* pgr0351 */
			}
			else {
				TmpRegion.x = Region.x;
				TmpRegion.width = Region.width;
				TmpRegion.height = height;/* pgr0351 */
			}
		}
		m_DrawRegion[Screen] = TmpRegion;
		setInvalidate();
		break;
	case DrawType_Rect:
		if (m_MaxNum < 2) {
			TmpRegion.x = Region.x;
			TmpRegion.y = Region.y;
			TmpRegion.width = Region.width;
			TmpRegion.height = 0;
		}
		else {
			if (m_MaxNum <= 47) {
				TmpRegion.y = Region.y + Region.height * (m_Index - 1) / m_MaxNum;/* pgr0351 */
				height = Region.height / m_MaxNum;
			}
			else {
				height = 4;
				TmpRegion.y = Region.y + (Region.height - Region.height / m_MaxNum) * (m_Index - 1) / (m_MaxNum - 1);/* pgr0351 */
			}
			if (m_Index < 1) {
				TmpRegion.x = Region.x;
				TmpRegion.y = Region.y;
				TmpRegion.width = Region.width;
				TmpRegion.height = Region.height / m_MaxNum;/* pgr0351 */
			}
			else if ((m_Index >= 1) && (m_Index <= m_MaxNum)) {
				TmpRegion.x = Region.x;
				TmpRegion.width = Region.width;
				TmpRegion.height = height;/* pgr0351 */
			}
			else {
				TmpRegion.x = Region.x;
				TmpRegion.width = Region.width;
				TmpRegion.height = height;/* pgr0351 */
			}
		}
		m_DrawRegion[Screen] = TmpRegion;
		setInvalidate();
		break;
	case DrawType_Ellipse:
		TmpRegion.width = Region.width;
		TmpRegion.height = Region.width;
		TmpRegion.x = Region.x;
		if (m_Percent <= 0) {
			TmpRegion.y = Region.y;
		}
		else if (m_Percent >= 100) {
			TmpRegion.y = Region.y + Region.height - Region.width;/* pgr0351 */
		}
		else {
			TmpRegion.y = Region.y + (Region.height - Region.width) * m_Percent / 100;/* pgr0351 */
		}
		m_DrawRegion[Screen] = TmpRegion;
		setInvalidate();
		break;
	default:
		return;
	}
}

void CtWidgetIndicateFrame::initScrollBar(unsigned int InitIndex, unsigned int MaxNum)
{
    m_Index = InitIndex;
    m_MaxNum = MaxNum;
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		calculateVerticalRegion(m_Region[i], i);
	}
}

void CtWidgetIndicateFrame::setIndex(unsigned int Index)
{
	if (m_Index == Index)
		return;
	
    m_Index = Index;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		calculateVerticalRegion(m_Region[i], i);
	}
}

