/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtStackLabel
 */

#include "CtStackLabel.h"
#include "CtStyle.h"
#include "CtEventInterface.h"


void CtStackLabel::ctor()
{
	setClassType(CtClassType_StackLabel);
	
	m_Index = -1;

	m_Stack.resize(0);
	for (int i = 0; i < m_Stack.size(); i++) {
		m_Stack[i] = NULL;
	}
}

CtStackLabel::CtStackLabel() 
{
	ctor();
}

CtStackLabel::CtStackLabel(const CtSize& Size, const CtColor& Color) :
	CtLabel(Size, Color)
{
	ctor();
}

CtStackLabel::CtStackLabel(const CtRegion& Region, const CtColor& Color) :
	CtLabel(Region)
{
	ctor();
	setColor(Color);
}

CtStackLabel::~CtStackLabel()
{
	for (int i = 0; i< m_Stack.size(); i++) {
		if (m_Stack[i]) delete m_Stack[i];
	}
	m_Stack.clear();
}

CtStackLabel::Stack::Stack() :
	Element(NULL, DefaultMargin, DefaultAlign),
	m_Type(TypeMax),
	m_pDrawInfo(NULL)
{
}

CtStackLabel::Stack::Stack(CtDrawInfo* pDrawInfo) :
	Element(NULL, DefaultMargin, DefaultAlign),
	m_Type(TypeNormal),
	m_pDrawInfo(pDrawInfo)
{
}

CtStackLabel::Stack::Stack(CtLabel* pLabel, CtMargin Margin, CtAlign Align) :
	Element(pLabel, Margin, Align),
	m_Type(TypeLabel),
	m_pDrawInfo(NULL)
{
}

CtStackLabel::Stack::Stack(CtLayout* pLayout, CtMargin Margin, CtAlign Align) :
	Element(pLayout, Margin, Align),
	m_Type(TypeLayout),
	m_pDrawInfo(NULL)
{
}

CtStackLabel::Stack::~Stack()
{
	if (m_pDrawInfo != NULL)	delete m_pDrawInfo;
}


bool CtStackLabel::addLabel(Stack* pStack, int Index)
{
	if (pStack == NULL)
		return false;
	
	if (Index == -1) {
		m_Stack.push_back(pStack);
	} else {
		int size = m_Stack.size();
		if (m_Stack.size() <= Index) {
			m_Stack.resize(Index+1);
			for (int i = size; i < m_Stack.size(); i++) {
				m_Stack[size] = NULL;
			}
		}
		m_Stack[Index] = pStack;
	}

	return true;
}

bool CtStackLabel::addLabel(CtLabel* pLabel, CtMargin Margin, CtAlign Align, int Index)
{
	if (pLabel == NULL)
		return false;

	pLabel->setTrans(isTrans());
	pLabel->setParent(this);
	return addLabel(new Stack(pLabel, Margin, Align), Index);
}

bool CtStackLabel::addLabel(CtLabel* pLabel, int Index)
{
	return addLabel(pLabel, DefaultMargin, DefaultAlign, Index);
}

bool CtStackLabel::addLabel(CtLayout* pLayout, CtMargin Margin, CtAlign Align, int Index)
{
	if (pLayout == NULL)
		return false;

	pLayout->setTrans(isTrans());
	pLayout->setParent(this);
	return addLabel(new Stack(pLayout, Margin, Align), Index);
}

bool CtStackLabel::addLabel(CtLayout* pLayout, int Index)
{
	return addLabel(pLayout, DefaultMargin, DefaultAlign, Index);
}

bool CtStackLabel::addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, int Index)
{
	CtLayout* pLayout = NULL;
	
	if (pContainer == NULL)
		return false;

	if ((pLayout = pContainer->getLayout()) == NULL) {
		if ((pLayout = pContainer->create()) == NULL)
			return false;

		pLayout->setContainer(pContainer);
	}
	
	pLayout->setTrans(isTrans());
	pLayout->setParent(this);
	return addLabel(new Stack(pLayout, Margin, Align), Index);
}

bool CtStackLabel::addContainer(CtContainer* pContainer, int Index)
{
	return addContainer(pContainer, DefaultMargin, DefaultAlign, Index);
}


bool CtStackLabel::addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, int Index) {
	GDI_IMAGE_BASE* pBase = GDI_GetImage(ImageID);
	CtDrawInfo* pDraw = NULL;

	if (pBase == NULL)
		return false;
	
	switch (pBase->type) {
	case GDI_IMAGE_TYPE_SVG:
		pDraw = new CtSVG(ImageID, fillColor, edgeColor);
		break;
		
	case GDI_IMAGE_TYPE_16BPP:
	case GDI_IMAGE_TYPE_32BPP:
		pDraw = new CtBitmap(ImageID);
		break;
		
	default:
		return false;
	}

	return addLabel(new Stack(pDraw), Index);
}

bool CtStackLabel::addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, int Index)
{
	return addLabel(ImageID, fillColor, CtColor::NoColor, Index);
}

bool CtStackLabel::addLabel(const GDI_IMAGE_ID ImageID, int Index)
{
	return addLabel(ImageID, CtColor::NoColor, CtColor::NoColor, Index);
}

bool CtStackLabel::addLabel(const GDI_HANDLER DrawableID, int Index)
{
	return addLabel(new Stack(new CtDrawable(DrawableID)), Index);
}

bool CtStackLabel::addLabel(const GDI_STRING_ID StringID, int Index)
{
	return addLabel(new Stack(new CtString(StringID)), Index);
}

bool CtStackLabel::addLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet, int Index)
{
	return addLabel(new Stack(new CtString(StringID, FontSet)), Index);
}

bool CtStackLabel::addLabel(const char* pStr, int Index)
{
	return addLabel(new Stack(new CtString(pStr)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabel(const char* pStr, const CtFontSet& FontSet, int Index)
{
	return addLabel(new Stack(new CtString(pStr, FontSet)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabel(const unsigned short* pStr, int Index)
{
	return addLabel(new Stack(new CtString(pStr)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabel(const unsigned short* pStr, const CtFontSet& FontSet, int Index)
{
	return addLabel(new Stack(new CtString(pStr, FontSet)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabel(const CtLine& Line, int Index)
{
	CtDrawInfo* pDraw = new CtLine(Line);
	return addLabel(new Stack(pDraw), Index);
}

bool CtStackLabel::addLabel(const CtRect& Rect, int Index)
{
	CtDrawInfo* pDraw = new CtRect(Rect);
	return addLabel(new Stack(pDraw), Index);
}

bool CtStackLabel::addLabel(const CtRoundRect& RoundRect, int Index)
{
	CtDrawInfo* pDraw = new CtRoundRect(RoundRect);
	return addLabel(new Stack(pDraw), Index);
}

bool CtStackLabel::addLabel(const CtEllipse& Ellipse, int Index)
{
	CtDrawInfo* pDraw = new CtEllipse(Ellipse);
	return addLabel(new Stack(pDraw), Index);
}
	
bool CtStackLabel::addLabel(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type, int Index)
{
	return addLabel(new Stack(new CtBitmap(Width, Height, BufWidth, BufHeight, Data, Type)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabel(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type, int Index)
{
	return addLabel(new Stack(new CtYUV(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type)), Index);	/* pgr0541 */
}

bool CtStackLabel::addLabels(const char* pStr, const CtFontSet& FontSet)
{
	char tmp[2] = { 0 };
	const char* p = pStr;
	bool bRet = false;

	// 文字列pStrを文字単位でaddLabel
	while (*p) {
		tmp[0] = *p;
		if (addLabel(tmp, FontSet) == true)
			bRet = true;
		p++;
	}

	return bRet;
}


//!! ここでStackを返してしまうと、m_pDrawInfoの描画ができなくなる。。。
//   でも、ParamLabelはm_pDrawInfoをStackから作ってるからなんだか難しいね。
CtDrawInfo* CtStackLabel::getStackDrawInfo(const CtRegion& Clip, int Screen)
{
	CtRegion clip = Clip;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	if (isVisible(Screen) == false)
		return NULL;

	if (m_Index < 0)
		return NULL;
	
	clip &= m_Region[Screen];

	if (clip.isValid() != true)
		return NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return NULL;

	if (((*pVisibles)[m_Index] == NULL) || ((pDrawInfo = static_cast<Stack*>((*pVisibles)[m_Index])->m_pDrawInfo) == NULL))
		return NULL;

	pDrawInfo->setRegion(m_Region[Screen]);
	pDrawInfo->setClip(clip);
	pDrawInfo->setTrans(isTrans());
	
	return pDrawInfo;
}

bool CtStackLabel::getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtRegion clip = Clip;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isVisible(Screen) != true)
		return bRet;

	if (isCollision(Clip, Screen) != true)
		return bRet;
	
	clip &= m_Region[Screen];

	if (CtWidget::getDrawInfo(List, clip, Screen) == true)
		bRet = true;

	if ((pDrawInfo = getStackDrawInfo(clip, Screen)) != NULL) {
		List.push_back(pDrawInfo);
		bRet = true;
		
	} else if ((pWidget = getStackWidget()) != NULL) {
		if (pWidget->getDrawInfo(List, clip, Screen) == true)
			bRet = true;
	}

	return bRet;
}

bool CtStackLabel::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtRegion clip = Clip;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isCollision(Clip, Screen) != true)
		return bRet;
	
	clearInvalidate(Screen);
	
	if (isVisible(Screen) != true) 
		return bRet;

	clip &= m_Region[Screen];

	if (CtWidget::draw(clip, Screen) == true)
		bRet = true;
	
	if ((pDrawInfo = getStackDrawInfo(clip, Screen)) != NULL) {
		if (pDrawInfo->draw() == true)
			bRet = true;
		
	} else if ((pWidget = getStackWidget()) != NULL) {
		if (pWidget->draw(clip, Screen) == true)
			bRet = true;
	}

	return bRet;
}

bool CtStackLabel::drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isVisible(Screen) != true)
		return bRet;

	if (CtWidget::drawShift(shift_x, shift_y, Clip, Screen) == true)
		bRet = true;
	
	if ((pDrawInfo = getStackDrawInfo(Clip, Screen)) != NULL) {
		pDrawInfo->movePos(shift_x, shift_y);
		pDrawInfo->draw();
		
	} else 	if ((pWidget = getStackWidget()) != NULL) {
		if (pWidget->drawShift(shift_x, shift_y, Clip, Screen) == true)
			bRet = true;
	}
	return bRet;
}

bool CtStackLabel::getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	bool bRet = false;
	CtLayout* pLayout = getStackLayout();

	switch (SearchType) {
	case VisibleCollisions:
		if (isVisible(Screen) != true) break;/* pgr0007 */
	case RegisteredCollisions:
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if (pList != NULL) pList->push_back(this);
			bRet = true;
		}
		break;
	case VisibleContains:
		if (isVisible(Screen) != true) break;/* pgr0007 */
	case RegisteredContains:
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if (pList != NULL) pList->push_back(this);
			bRet = true;
		}
		break;
	default:
		if (checkWidgetType(WidgetType, this) == true) {
			if (pList != NULL) pList->push_back(this);
			bRet = true;
		}
		break;
	}
	
	if (pLayout == NULL)
		return bRet;

	if (pLayout->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
		bRet = true;
	
	return bRet;
}

bool CtStackLabel::existWidget(SearchType SearchType, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	bool bRet = false;
	CtLayout* pLayout = getStackLayout();

	switch (SearchType) {
	case VisibleCollisions:
		if (isVisible(Screen) != true) break;/*pgr0007*/
	case RegisteredCollisions:
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			return true;
		}
		break;
	case VisibleContains:
		if (isVisible(Screen) != true) break;/*pgr0007*/
	case RegisteredContains:
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			return true;
		}
		break;
	default:
		if (checkWidgetType(WidgetType, this) == true) {
			return true;
		}
		break;
	}
	
	if (pLayout == NULL)
		return bRet;

	if (pLayout->existWidget(SearchType, WidgetType, Screen, Region) == true)
		bRet = true;
	
	return bRet;
}

bool CtStackLabel::isRegistered(CtWidget* pWidget)
{
	CtLayout* pLayout = getStackLayout();

	if (pWidget == this)
		return true;
	
	if (pLayout == NULL)
		return false;

	return pLayout->isRegistered(pWidget);
}

bool CtStackLabel::setElementsParent(CtWidget* pParent)
{
	CtWidget* pWidget = getStackWidget();

	setParent(pParent);
	
	if (pWidget == NULL)
		return false;
	
	return pWidget->setElementsParent(this);
}

bool CtStackLabel::setColor(const CtColor& fillColor)
{
	bool bRet = false;
	CtWidget *pWidget;

	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;

		if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			if (pWidget->isLabel() == true) {
				if ((pWidget->setColor(fillColor) == true) && (i == m_Index))
					bRet = true;
			} else if (pWidget->isLayout() == true) {
				if ((static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor) == true) && (i == m_Index))
					bRet = true;
			}
			
		} else if (m_Stack[i]->m_pDrawInfo != NULL) {
			if ((m_Stack[i]->m_pDrawInfo->setColor(fillColor) == true) && (i == m_Index))
				bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}

	return bRet;
}

bool CtStackLabel::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	bool bRet = false;
	CtWidget *pWidget;

	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;

		if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			if (pWidget->isLabel() == true) {
				if ((pWidget->setColor(fillColor, edgeColor) == true) && (i == m_Index))
					bRet = true;
			} else if (pWidget->isLayout() == true) {
				if ((static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor, edgeColor) == true) && (i == m_Index))
					bRet = true;
			}
			
		} else if (m_Stack[i]->m_pDrawInfo != NULL) {
			if ((m_Stack[i]->m_pDrawInfo->setColor(fillColor, edgeColor) == true) && (i == m_Index))
				bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
    return bRet;
}

bool CtStackLabel::setTrans(bool bTrans)
{
	bool bRet = false;
	
	bRet = CtWidget::setTrans(bTrans);

	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;
		
		if (m_Stack[i]->pWidget != NULL) {
			if (m_Stack[i]->pWidget->setTrans(bTrans) == true)
				bRet = true;
		}
	}
			
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtStackLabel::setFontSet(const CtFontSet& FontSet)
{
	bool bRet = false;
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;
		
		if ((m_Stack[i]->pWidget != NULL) && (m_Stack[i]->pWidget->isLabel() == true)) {
			if (static_cast<CtLabel*>(m_Stack[i]->pWidget)->setFontSet(FontSet) == true)
				bRet = true;
		}
		if ((m_Stack[i]->m_pDrawInfo != NULL) && (m_Stack[i]->m_pDrawInfo->getDrawType() == DrawType_String)) {
			if (static_cast<CtString*>(m_Stack[i]->m_pDrawInfo)->setFontSet(FontSet) == true)
				bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}

	return true;
}

bool CtStackLabel::inc()
{
	int Index = m_Index;
	
	if ((Index +1) < m_Stack.size()) {
		Index++;
		return index(Index);
	}
	return false;
}

bool CtStackLabel::dec()
{
	int Index = m_Index;
	
	if (Index > 0) {
		Index--;
		return index(Index);
	}
	return false;
}

bool CtStackLabel::setLayout(int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	
	if (m_Region[Screen].isValid() == false)
		return bRet;

	if (m_Index < 0) {
		index(0);
	}
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if ((m_Stack[i] == NULL) || ((pWidget = m_Stack[i]->pWidget) == NULL))
			continue;
		
		pWidget->setRegion(m_Stack[i]->allocate(m_Region[Screen], pWidget->getSize()), Screen);
		pWidget->setAlign(m_Stack[i]->Align);
	}

	return bRet;
}

bool CtStackLabel::setAlign(const CtAlign Align)
{
	bool bRet = false;
	CtDrawInfo* pDrawInfo = NULL;
	CtWidget* pWidget = NULL;
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;
		
		if ((pDrawInfo = m_Stack[i]->m_pDrawInfo) != NULL) {
			if (pDrawInfo->setAlign(Align) == true)
				bRet = true;

		} else if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			if (pWidget->setAlign(Align) == true)
				bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtStackLabel::setAspectRatio(const CtAspectRatio Ratio)
{
	bool bRet = false;
	CtDrawInfo* pDrawInfo = NULL;
	CtWidget* pWidget = NULL;
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;
		
		if ((pDrawInfo = m_Stack[i]->m_pDrawInfo) != NULL) {
			if (pDrawInfo->setAspectRatio(Ratio) == true)
					bRet = true;
			
		} else if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			if (pWidget->setAspectRatio(Ratio) == true)
				bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtStackLabel::setAutoAdjust(bool bAdjust)
{
	bool bRet = false;
	CtDrawInfo* pDrawInfo = NULL;
	CtWidget* pWidget = NULL;
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)	continue;
		
		if ((pDrawInfo = m_Stack[i]->m_pDrawInfo) != NULL) {
			if (pDrawInfo->setAutoAdjust(bAdjust) == true)
				bRet = true;
			
		} else if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			if (pWidget->setAutoAdjust(bAdjust) == true)
				bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtStackLabel::index(int Index)
{
	CtWidget* pWidget = NULL;
	CtLayout* pLayout = NULL;
	CtWidget::List list;
	
	if (m_Index == Index)
		return false;
		
	if (Index < 0 || m_Stack.size() <= Index)
		return false;
	
	if (m_Stack[Index] == NULL)
		return false;

	if ((isFastDraw() != true) && ((pWidget = getStackWidget(Index)) != NULL)) {
		if ((includeEventHandler(Index) == true) || (includeEventHandler(m_Index) == true)) {
			CtEventInterface::requestWidgetCmd(getWidgetID(), pWidget, CtEventWidget::RestartWindow);
		}

		if ((pLayout = getStackLayout(m_Index)) != NULL) {
			for (int i = 0; i < CT_SCREEN_NUM; i++) {
				pLayout->getWidgets(CtLayout::Visible, &list, WidgetLayout, i);
			}

			for (CtWidget::ListItr Widget = list.begin(); Widget != list.end(); ++Widget) {
				if((*Widget)->isLayout() != true)
					continue;
				
				CtContainer* pContainer = (*Widget)->getContainer();
				if (pContainer == NULL)
					continue;
				pContainer->setViewing(false);
				for (int i = 0; i < CT_SCREEN_NUM; i++) {
					(*Widget)->clearInvalidates(i);
				}
			}
		}
		
		for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
			pWidget->setLayout(Screen);
		}
		if ((pLayout = getStackLayout(Index)) != NULL) {
			pLayout->setElementsParent(this);
		}
	}
			
	m_Index = Index;
	
	if (isVisible() == true) {
		setInvalidate();
	}
	
	return true;
}

bool CtStackLabel::includeEventHandler(int Index)
{
	CtLayout* pLayout = NULL;
	
	int screen = toNoScreen(getScreenSel());
	if ((pLayout = getStackLayout(Index)) == NULL)
		return false;
	
	if ((pLayout->existWidget(CtLayout::Registered, WidgetButton, screen) == true) ||
		(pLayout->existWidget(CtLayout::Registered, Container, screen) == true)) {
		return true;
	}
	return false;
}

int CtStackLabel::getIndex() const
{
	return m_Index;
}

int CtStackLabel::getIndexMax() const
{
	return m_Stack.size() -1;
}

bool CtStackLabel::initialFastDraw()
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;

	if (isFastDraw() != true) {
		// StackInStack時の高速描画初期化
		for (int i = 0; i < m_Stack.size(); i++) {
			if ((pWidget = getStackWidget(i)) != NULL) {
				if (pWidget->initialFastDraw() == true)
					bRet = true;
			}
		}
		return bRet;
	}
	
	if ((m_Region[0].isValid() != true) && (m_Size.isValid() != true))
		return false;

	if (m_Region[0].isValid() != true)
		m_Region[0] = CtRegion(0, 0, m_Size.width, m_Size.height);
	
	for (int i = 0; i < m_Stack.size(); i++) {
		if (m_Stack[i] == NULL)
			continue;

		if ((pWidget = m_Stack[i]->pWidget) != NULL) {
			pWidget->setSize(m_Size);
			if (pWidget->setDrawImage() == true)
				bRet = true;
			
		} else if ((pDrawInfo = m_Stack[i]->m_pDrawInfo) != NULL) {
			pDrawInfo->setRegion(m_Region[0]);
			if (setDrawImage(pDrawInfo) == true)
				bRet = true;
		}
	}
	
	return bRet;
}

bool CtStackLabel::cleanupFastDraw()
{
	return false;
}

CtWidget* CtStackLabel::getStackWidget(int _Index) const
{
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	int Index = _Index;

	if (Index < 0)
		Index = m_Index;
	
	if (Index < 0)
		return NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return NULL;

	if (((*pVisibles)[Index] == NULL) || ((pWidget = (*pVisibles)[Index]->pWidget) == NULL))
		return NULL;

	return pWidget;
}

CtLayout* CtStackLabel::getStackLayout(int _Index) const
{
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	int Index = _Index;
	
	if (Index < 0)
		Index = m_Index;
	
	if (Index < 0)
		return NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return NULL;

	if (((*pVisibles)[Index] == NULL) || ((pWidget = (*pVisibles)[Index]->pWidget) == NULL))
		return NULL;

	if (pWidget->isLayout() != true)
		return NULL;
	
	return (CtLayout*)pWidget;
}

bool CtStackLabel::handleTouchEvent(const CtEventTouch& Touch)
{
	CtWidget* pWidget = getStackWidget();

	if (pWidget == NULL)
		return false;
	
	return pWidget->handleTouchEvent(Touch);
}

bool CtStackLabel::handleKeyEvent(const CtEventKey& Key)
{
	CtWidget* pWidget = getStackWidget();

	if (pWidget == NULL)
		return false;
	
	return pWidget->handleKeyEvent(Key);
}

bool CtStackLabel::handleParamEvent(const CtEventParam& Param)
{
	CtWidget* pWidget = getStackWidget();

	if (pWidget == NULL)
		return false;
	
	return pWidget->handleParamEvent(Param);
}

bool CtStackLabel::handleButtonEvent(const CtEventButton& Button)
{
	CtWidget* pWidget = getStackWidget();

	if (pWidget == NULL)
		return false;
	
	return pWidget->handleButtonEvent(Button);
}

bool CtStackLabel::handleWidgetEvent(const CtEventWidget& Widget)
{
	CtWidget* pWidget = getStackWidget();

	if (pWidget == NULL)
		return false;
	
	return pWidget->handleWidgetEvent(Widget);
}

bool CtStackLabel::isLayout() const
{
	CtLayout* pLayout = getStackLayout();

	if (pLayout == NULL)
		return false;

	return true;
}

bool CtStackLabel::getInvalidates(RegionArray& Array, int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	
	if (isInvalidate(Screen) == true) {
		if (m_ClearRegion[Screen].isValid() == true) {
			putRegionList(Array, m_ClearRegion[Screen]);
			bRet = true;
		}
		if ((m_Region[Screen].isValid() == true) &&
			(m_Region[Screen] != m_ClearRegion[Screen])) {
			putRegionList(Array, m_Region[Screen]);
			bRet = true;
		}
		return bRet;
	}

	if (isVisible(Screen) != true)
		return bRet;
	
	if ((pWidget = getStackWidget()) != NULL) {
		if (pWidget->getInvalidates(Array, Screen) == true)
			bRet = true;
	}

	return bRet;
}

bool CtStackLabel::clearInvalidate(int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;

	bRet = CtWidget::clearInvalidate(Screen);

	if ((pWidget = getStackWidget()) != NULL) {
		if (pWidget->clearInvalidate(Screen) == true)
			bRet = true;
	}
	
	return bRet;
}

void CtStackLabel::outputOutline(int depth, const char* header, int Screen) 
{
	CtWidget* pWidget = getStackWidget();
	
	CtWidget::outputOutline(depth, header, Screen);

	if (pWidget != NULL) {
		pWidget->outputOutline(depth + 1, "└", Screen);
	}
}

