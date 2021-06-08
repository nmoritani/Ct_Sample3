/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtLayout
 */


#include "CtLayout.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "CtGridLayout.h"
#include "CtWindow.h"
#include "CtWindowMain.h"

void CtLayout::ctor()
{
	setClassType(CtClassType_Layout);

	m_ElementsMargin = DefaultMargin;
	m_ElementsAlign = DefaultAlign;
	m_LayoutType = LayoutStack;
	m_pContainer = NULL;
	m_pBackground = NULL;
	m_bStretched = false;
	m_bFastDraw = false;

	m_Elements.resize(0);
}

CtLayout::CtLayout()
{
	ctor();
}

CtLayout::CtLayout(const CtColor& Color)
{
	ctor();
	if (Color != CtColor::NoColor) {
		m_pBackground = new CtRect(Color);
	}
}

CtLayout::CtLayout(const CtSize& Size, const CtColor& Color) :
	CtWidget(Size)
{
	ctor();
	if (Color != CtColor::NoColor) {
		m_pBackground = new CtRect(Color);
	}
}

CtLayout::CtLayout(const CtRegion& Region, const CtColor& Color) :
	CtWidget(Region)
{
	ctor();
	if (Color != CtColor::NoColor) {
		m_pBackground = new CtRect(Color);
	}
}

CtLayout::~CtLayout()
{
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	CtWindowMain* pMain = NULL;
	
	if (m_pContainer != NULL) {
		if ((pMain = getMain()) != NULL)
			pMain->removeContainer(m_pContainer);

		delete m_pContainer;
		m_pContainer = NULL;
	}

	if (m_pBackground != NULL)
		delete m_pBackground;
	
	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return;
		
	for (int i = 0; i< pElements->size(); i++) {
		if ((*pElements)[i] != NULL) {
			delete (*pElements)[i];
		}
	}
	pElements->clear();
}

CtLayout::SplitElement::SplitElement() :
	Element()
{
	setClassType(CtClassType_SplitElement);

	ScreenSel = ScreenNone;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		Stretch[i].Ratio = 0;
		Stretch[i].Size = AutoSize;
	}
}

CtLayout::SplitElement::SplitElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& _Stretch, CtScreenSel Sel) :
	Element(pWidget, Margin, Align)
{
	setClassType(CtClassType_SplitElement);

	ScreenSel = Sel;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (Sel & toSelScreen(i)) {
			Stretch[i].Ratio = 0;
			Stretch[i].Size = _Stretch;
		} else {
			Stretch[i].Ratio = 0;
			Stretch[i].Size = AutoSize;
		}
	}
}

CtLayout::SplitElement::SplitElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short _Stretch, CtScreenSel Sel) :
	Element(pWidget, Margin, Align)
{
	setClassType(CtClassType_SplitElement);

	ScreenSel = Sel;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (Sel & toSelScreen(i)) {
			Stretch[i].Ratio = _Stretch;
			Stretch[i].Size = AutoSize;
		} else {
			Stretch[i].Ratio = 0;
			Stretch[i].Size = AutoSize;
		}
	}
}

CtLayout::SplitElement::~SplitElement()
{
}

bool CtLayout::SplitElement::set(CtWidget* _pWidget, CtMargin _Margin, CtAlign _Align, const CtSize& _Stretch, CtScreenSel Sel)
{
	bool bRet = false;

	bRet = Element::set(_pWidget, _Margin, _Align);

	ScreenSel = (CtScreenSel)(ScreenSel | Sel);
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((Sel & toSelScreen(i)) && (Stretch[i].Size != _Stretch)) {
			Stretch[i].Size = _Stretch;
			bRet = true;
		}
	}
	return bRet;
}

bool CtLayout::SplitElement::set(CtWidget* _pWidget, CtMargin _Margin, CtAlign _Align, short _Stretch, CtScreenSel Sel)
{
	bool bRet = false;

	bRet = Element::set(_pWidget, _Margin, _Align);

	ScreenSel = (CtScreenSel)(ScreenSel | Sel);
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((Sel & toSelScreen(i)) &&  (Stretch[i].Ratio != _Stretch)) {
			Stretch[i].Ratio = _Stretch;
			bRet = true;
		}
	}
	return bRet;
}

bool CtLayout::SplitElement::setStretch(short _Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	
	ScreenSel = (CtScreenSel)(ScreenSel | Sel);
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((Sel & toSelScreen(i)) &&  (Stretch[i].Ratio != _Stretch)) {
			Stretch[i].Ratio = _Stretch;
			bRet = true;
		}
	}
	return bRet;
}

bool CtLayout::SplitElement::setStretch(const CtSize& _Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	
	ScreenSel = (CtScreenSel)(ScreenSel | Sel);
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((Sel & toSelScreen(i)) &&  (Stretch[i].Size != _Stretch)) {
			Stretch[i].Size = _Stretch;
			bRet = true;
		}
	}
	return bRet;
}


CtLayout::SpanElement::SpanElement() :
	Element(),
	RowSpan(0),
	ColumnSpan(0)
{
	setClassType(CtClassType_SpanElement);
}

CtLayout::SpanElement::SpanElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short _RowSpan, short _ColumnSpan) :
	Element(pWidget, Margin, Align),
	RowSpan(_RowSpan),
	ColumnSpan(_ColumnSpan)
{
	setClassType(CtClassType_SpanElement);
}

CtLayout::SpanElement::~SpanElement()
{
}

bool CtLayout::SpanElement::set(CtWidget* _pWidget, CtMargin _Margin, CtAlign _Align, short _RowSpan, short _ColumnSpan)
{
	bool bRet = false;

	bRet = Element::set(_pWidget, _Margin, _Align);
	
	if (RowSpan != _RowSpan) {
		RowSpan = _RowSpan;
		bRet = true;
	}
	if (ColumnSpan != _ColumnSpan) {
		ColumnSpan = _ColumnSpan;
		bRet = true;
	}
	return bRet;
}

bool CtLayout::setColor(const CtColor& fillColor)
{
	bool bRet = false;

	if (fillColor == CtColor::NoColor) {
		if (m_pBackground != NULL)
			delete m_pBackground;
		
	} else {
		if (m_pBackground == NULL) {
			m_pBackground = new CtRect(fillColor);
			bRet = true;
		
		} else {
			bRet = static_cast<CtRect*>(m_pBackground)->setRect(fillColor, 0, CtColor::NoColor);
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
		
	return bRet;
}

bool CtLayout::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	bool bRet = false;

	if ((fillColor == CtColor::NoColor) && (edgeColor == CtColor::NoColor)) {
		if (m_pBackground != NULL)
			delete m_pBackground;
		
	} else {
		if (m_pBackground == NULL) {
			m_pBackground = new CtRect(fillColor, 2, edgeColor);
			bRet = true;
		} else {
			bRet = static_cast<CtRect*>(m_pBackground)->setRect(fillColor, 2, edgeColor);
		}
	}
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
	return bRet;
}

CtColor CtLayout::getColor() const
{
	CtDrawInfo* pDrawInfo = NULL;
	
	if (m_pBackground == NULL)
		return CtColor::NoColor;

	return m_pBackground->getFillColor();
}

bool CtLayout::setElementsColor(const CtColor& fillColor)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
		
	for (int i = 0; i< pElements->size(); i++) {
		CtWidget* pWidget;
		if ((*pElements)[i] == NULL)						continue;
		if ((pWidget = (*pElements)[i]->pWidget) == NULL)	continue;

		if (pWidget->isLabel() == true) {
			if (pWidget->setColor(fillColor) == true)
				bRet = true;
			
		} else if (pWidget->isLayout() == true) {
			if (static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor) == true)
				bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
	return bRet;
}

bool CtLayout::setElementsColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
		
	for (int i = 0; i< pElements->size(); i++) {
		CtWidget* pWidget;
		if ((*pElements)[i] == NULL)						continue;
		if ((pWidget = (*pElements)[i]->pWidget) == NULL)	continue;
		
		if (pWidget->isLabel() == true) {
			if (pWidget->setColor(fillColor, edgeColor) == true)
				bRet = true;
			
		} else if (pWidget->isLayout() == true) {
			if (static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor, edgeColor) == true)
				bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
    return bRet;
}

bool CtLayout::setElementsParent(CtWidget* pParent)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;

	setParent(pParent);
	
	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
		
	for (int i = 0; i< pElements->size(); i++) {
		CtWidget* pWidget;
		if ((*pElements)[i] == NULL)						continue;
		if ((pWidget = (*pElements)[i]->pWidget) == NULL)	continue;

		if (pWidget->setParent(this) == true)
			bRet = true;

		if (pWidget->isLayout() == true)
			pWidget->setElementsParent(this);
		
	}

    return bRet;
}

bool CtLayout::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return false;
		
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
	if (Stretch != 0)
		m_bStretched = true;

    pElements->push_back(new SplitElement(pWidget, Margin, Align, Stretch));	/* pgr0541 */
	(*pElements)[pElements->size() -1]->Index = pElements->size() -1;

	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}

	return true;
}

bool CtLayout::addWidget(CtWidget* pWidget, CtMargin Margin, short Stretch)
{
	return addWidget(pWidget, Margin, DefaultAlign, Stretch);
}

bool CtLayout::addWidget(CtWidget* pWidget, CtAlign Align, short Stretch)
{
	return addWidget(pWidget, DefaultMargin, Align, Stretch);
}

bool CtLayout::addWidget(CtWidget* pWidget, short Stretch)
{
	return addWidget(pWidget, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return false;
	
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
    pElements->push_back(new SplitElement(pWidget, Margin, Align, Stretch));	/* pgr0541 */
	(*pElements)[pElements->size() -1]->Index = pElements->size() -1;

	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	
	return true;
}

bool CtLayout::addWidget(CtWidget* pWidget, CtMargin Margin, const CtSize& Stretch)
{
	return addWidget(pWidget, Margin, DefaultAlign, Stretch);
}

bool CtLayout::addWidget(CtWidget* pWidget, CtAlign Align, const CtSize& Stretch)
{
	return addWidget(pWidget, DefaultMargin, Align, Stretch);
}

bool CtLayout::addWidget(CtWidget* pWidget, const CtSize& Stretch)
{
	return addWidget(pWidget, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::setWidget(CtWidget* _pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtVector::Vector<Element*>* pElements = NULL;
	CtWidget* pWidget = NULL;
	
	if ((pElements = getElements()) == NULL)
		return false;
	
	if (_pWidget != NULL) {
		_pWidget->setParent(this);
	}
	
	if (Stretch != 0)
		m_bStretched = true;

	if (pElements->size() > Index) {
		if ((*pElements)[Index] != NULL) {
			if ((pWidget = (*pElements)[Index]->pWidget) != _pWidget) {
				if (pWidget->isButton() == true) {
					CtWindow *pWin = getWindow();
					if (pWin != NULL) pWin->clearFocusWidget(pWidget);
				}
				delete (*pElements)[Index];
				(*pElements)[Index] = NULL;
			}
		}
	} else {
		pElements->resize(Index+1);
		for (int i = pElements->size(); i <= Index; i++) {
			(*pElements)[i] = NULL;
		}
	}

	if ((*pElements)[Index] == NULL) {
		(*pElements)[Index] = new SplitElement(_pWidget, Margin, Align, Stretch);	/* pgr0541 */
	}
	
	(*pElements)[Index]->Index = Index;
	updateVisibles();

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	
	return true;
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch)
{
	return setWidget(pWidget, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch)
{
	return setWidget(pWidget, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, short Stretch)
{
	return setWidget(pWidget, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	return setWidget(pWidget, Index, Margin, Align, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch)
{
	return setWidget(pWidget, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch)
{
	return setWidget(pWidget, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::setWidget(CtWidget* pWidget, short Index, const CtSize& Stretch)
{
	return setWidget(pWidget, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return false;
		
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
	if (Stretch != 0)
		m_bStretched = true;
	
	pElements->insert(Index, new SplitElement(pWidget, Margin, Align, Stretch));	/* pgr0541 */
	for (int i = Index; i < pElements->size(); i++) {
		(*pElements)[Index]->Index = i;
	}

	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	
	return true;
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch)
{
	return insertWidget(pWidget, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch)
{
	return insertWidget(pWidget, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, short Stretch)
{
	return insertWidget(pWidget, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return false;
		
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
	pElements->insert(Index, new SplitElement(pWidget, Margin, Align, Stretch));	/* pgr0541 */
	for (int i = Index; i < pElements->size(); i++) {
		(*pElements)[Index]->Index = i;
	}

	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	
	return true;
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch)
{
	return insertWidget(pWidget, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch)
{
	return insertWidget(pWidget, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::insertWidget(CtWidget* pWidget, short Index, const CtSize& Stretch)
{
	return insertWidget(pWidget, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::removeWidget(CtWidget* pWidget)
{
	bool bDeleted = false;
	Element* pElement = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return false;
	
	if (pWidget == NULL)
		return false;
	
    // ÉäÉXÉgÇ©ÇÁçÌèú
	for (int i = 0; i< pElements->size(); i++) {
		if (((pElement = (*pElements)[i]) != NULL) && (pWidget == pElement->pWidget)) {
			if (pWidget->isButton() == true) {
				CtWindow *pWin = getWindow();
				if (pWin != NULL) pWin->clearFocusWidget(pWidget);
			}
			pElements->erase(i);
			delete pElement;
			bDeleted = true;
			break;
		}
	}

	if (bDeleted == false)
		return false;
	
	for (int i = 0; i < pElements->size(); i++) {
		if ((*pElements)[i] != NULL)
			(*pElements)[i]->Index = i;
	}
	
	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return true;
}

bool CtLayout::removeWidget(short Index)
{
	bool bDeleted = false;
	Element* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return false;
	
	if (((pElement = (*pElements)[Index]) != NULL) && ((pWidget = pElement->pWidget) != NULL)) {
		if (pWidget->isButton() == true) {
			CtWindow *pWin = getWindow();
			if (pWin != NULL) pWin->clearFocusWidget(pWidget);
		}
		pElements->erase(Index);
		delete pElement;
		bDeleted = true;
	}

	if (bDeleted == false)
		return false;

	for (int i = 0; i < pElements->size(); i++) {
		if ((*pElements)[i] != NULL)
			(*pElements)[i]->Index = i;
	}

	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return true;
}

bool CtLayout::setContainer(CtContainer *pContainer)
{
	if (pContainer == NULL)	return false;

	m_pContainer = pContainer;
	return true;
}

bool CtLayout::addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if (pContainer == NULL)
		return false;
	
	if ((pLayout = pContainer->getLayout()) == NULL) {
		if ((pLayout = pContainer->create()) == NULL)
			return false;

		pLayout->setContainer(pContainer);
	}

	if ((pMain = getMain()) != NULL)
		pMain->addContainer(pContainer);
		
	return addWidget(pLayout, Margin, Align, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, CtMargin Margin, short Stretch)
{
	return addContainer(pContainer, Margin, DefaultAlign, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, CtAlign Align, short Stretch)
{
	return addContainer(pContainer, DefaultMargin, Align, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, short Stretch)
{
	return addContainer(pContainer, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if (pContainer == NULL)
		return false;

	if ((pLayout = pContainer->getLayout()) == NULL) {
		if ((pLayout = pContainer->create()) == NULL)
			return false;

		pLayout->setContainer(pContainer);
	}
		
	if ((pMain = getMain()) != NULL)
		pMain->addContainer(pContainer);
		
	return addWidget(pLayout, Margin, Align, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, CtMargin Margin, const CtSize& Stretch)
{
	return addContainer(pContainer, Margin, DefaultAlign, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, CtAlign Align, const CtSize& Stretch)
{
	return addContainer(pContainer, DefaultMargin, Align, Stretch);
}

bool CtLayout::addContainer(CtContainer* pContainer, const CtSize& Stretch)
{
	return addContainer(pContainer, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if ((pContainer == NULL) || ((pLayout = pContainer->getLayout()) == NULL))
		return false;
	if (pLayout->getContainer() != pContainer)
		return false;

	if ((pMain = getMain()) != NULL)
		pMain->addContainer(pContainer);
		
	return setWidget(pLayout, Index, Margin, Align, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch)
{
	return setContainer(pContainer, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch)
{
	return setContainer(pContainer, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, short Stretch)
{
	return setContainer(pContainer, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	return setContainer(pContainer, Index, Margin, Align, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch)
{
	return setContainer(pContainer, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch)
{
	return setContainer(pContainer, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::setContainer(CtContainer* pContainer, short Index, const CtSize& Stretch)
{
	return setContainer(pContainer, Index, DefaultMargin, DefaultAlign, Stretch);
}
	
bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch)
{
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if ((pContainer == NULL) || ((pLayout = pContainer->getLayout()) == NULL))
		return false;
	if (pLayout->getContainer() != pContainer)
		return false;

	if ((pMain = getMain()) != NULL)
		pMain->addContainer(pContainer);
		
	return insertWidget(pLayout, Index, Margin, Align, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch)
{
	return insertContainer(pContainer, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch)
{
	return insertContainer(pContainer, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, short Stretch)
{
	return insertContainer(pContainer, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch)
{
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if ((pContainer == NULL) || ((pLayout = pContainer->getLayout()) == NULL))
		return false;
	if (pLayout->getContainer() != pContainer)
		return false;

	if ((pMain = getMain()) != NULL)
		pMain->addContainer(pContainer);
		
	return insertWidget(pLayout, Index, Margin, Align, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch)
{
	return insertContainer(pContainer, Index, Margin, DefaultAlign, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch)
{
	return insertContainer(pContainer, Index, DefaultMargin, Align, Stretch);
}

bool CtLayout::insertContainer(CtContainer* pContainer, short Index, const CtSize& Stretch)
{
	return insertContainer(pContainer, Index, DefaultMargin, DefaultAlign, Stretch);
}

bool CtLayout::removeContainer(CtContainer* pContainer)
{
	bool bRet = false;
	CtLayout* pLayout;
	CtWindowMain* pMain;
	
	if (pContainer == NULL)
		return false;

	if ((pLayout = pContainer->getLayout()) != NULL) {
		if (removeWidget(pLayout) == true)
			bRet = true;
		
	} else if ((pMain = getMain()) != NULL) {
		if (pMain->removeContainer(pContainer) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::removeContainer(short Index)
{
	bool bRet = false;
	CtLayout* pLayout = NULL;
	CtWindowMain* pMain = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;

	if (((pLayout = (CtLayout*)(*pElements)[Index]->pWidget) == NULL) || (pLayout->isLayout() != true))
		return bRet;

	if (pLayout->getContainer() == NULL)
		return bRet;

	if (removeWidget(Index) == true) {
		bRet = true;

	} else if ((pMain = getMain()) != NULL) {
		if (pMain->removeContainer(pLayout->getContainer()) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::setElementsMargin(CtMargin Margin)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	m_ElementsMargin = Margin;
	
	for (int i = 0; i< pElements->size(); i++) {
		if ((*pElements)[i] == NULL)
			continue;

		(*pElements)[i]->Margin = m_ElementsMargin;
    }
	
	updateVisibles();
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::setElementsMargin(CtMargin Margin, CtAlign Align)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	m_ElementsMargin = Margin;
	m_ElementsAlign = Align;
	
	for (int i = 0; i< pElements->size(); i++) {
		if ((*pElements)[i] == NULL)
			continue;

		(*pElements)[i]->Margin = m_ElementsMargin;
		(*pElements)[i]->Align = m_ElementsAlign;
    }
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::addSpacing(const CtSize&  Size, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	pElements->push_back(new SplitElement(NULL, DefaultMargin, DefaultAlign, Size));
	(*pElements)[pElements->size() -1]->Index = pElements->size() -1;
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::insertSpacing(short Index, const CtSize&  Size, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	pElements->insert(Index, new SplitElement(NULL, DefaultMargin, DefaultAlign, Size));
	(*pElements)[Index]->Index = Index;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::addStretch(short Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return bRet;

	if (Stretch <= 0)
		return bRet;
	
	pElements->push_back(new SplitElement(NULL, DefaultMargin, DefaultAlign, Stretch, Sel));
	(*pElements)[m_Elements.size() -1]->Index = m_Elements.size() -1;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::addStretch(const CtSize& Size, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return bRet;

	pElements->push_back(new SplitElement(NULL, DefaultMargin, DefaultAlign, Size, Sel));
	(*pElements)[m_Elements.size() -1]->Index = m_Elements.size() -1;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::insertStretch(short Index, short Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return bRet;
	
	if (Stretch <= 0)
		return bRet;
	
	pElements->insert(Index, new SplitElement(NULL, DefaultMargin, DefaultAlign, Stretch, Sel));
	(*pElements)[Index]->Index = Index;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::insertStretch(short Index, const CtSize& Size, CtScreenSel Sel)
{
	bool bRet = false;
	CtVector::Vector<Element*>* pElements = NULL;

	if ((pElements = getElements()) == NULL)
		return bRet;
	
	if (Size.width <= 0 || Size.height <= 0)
		return bRet;
	
	pElements->insert(Index, new SplitElement(NULL, DefaultMargin, DefaultAlign, Size, Sel));
	(*pElements)[Index]->Index = Index;
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (setLayout(i) == true)
			bRet = true;
	}
	return bRet;
}

bool CtLayout::setStretch(CtWidget* _pWidget, short Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if (_pWidget == NULL)
		return bRet;
	
	for (int i = 0; i< pElements->size(); i++) {
		if (((pElement = (SplitElement*)(*pElements)[i]) == NULL) || ((pWidget = pElement->pWidget) == NULL)) continue;

		if (pWidget == _pWidget) {
			pElement->setStretch(Stretch, Sel);
			bRet = true;
			break;
		}
	}

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setStretch(CtWidget* _pWidget, const CtSize& Size, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if (_pWidget == NULL)
		return bRet;
	
	for (int i = 0; i< pElements->size(); i++) {
		if (((pElement = (SplitElement*)(*pElements)[i]) == NULL) || ((pWidget = pElement->pWidget) == NULL)) continue;

		if (pWidget == _pWidget) {
			pElement->setStretch(Size, Sel);
			bRet = true;
			break;
		}
	}

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setStretch(CtContainer* pContainer, short Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if (pContainer == NULL)
		return bRet;
	
	for (int i = 0; i< pElements->size(); i++) {
		if (((pElement = (SplitElement*)(*pElements)[i]) == NULL) || ((pWidget = pElement->pWidget) == NULL)) continue;

		if (pWidget->getContainer() == pContainer) {
			pElement->setStretch(Stretch, Sel);
			bRet = true;
			break;
		}
	}

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setStretch(CtContainer* pContainer, const CtSize& Size, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if (pContainer == NULL)
		return bRet;
	
	for (int i = 0; i< pElements->size(); i++) {
		if (((pElement = (SplitElement*)(*pElements)[i]) == NULL) || ((pWidget = pElement->pWidget) == NULL)) continue;

		if (pWidget->getContainer() == pContainer) {
			pElement->setStretch(Size, Sel);
			bRet = true;
			break;
		}
	}

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setStretch(short Index, short Stretch, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if ((Index < 0) || (pElements->size() <= Index))
		return bRet;

	if (((pElement = (SplitElement*)(*pElements)[Index]) == NULL) || ((pWidget = pElement->pWidget) == NULL))
		return false;

	pElement->setStretch(Stretch, Sel);

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setStretch(short Index, const CtSize& Size, CtScreenSel Sel)
{
	bool bRet = false;
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pElements = NULL;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return bRet;
	
	if ((Index < 0) || (pElements->size() <= Index))
		return bRet;

	if (((pElement = (SplitElement*)(*pElements)[Index]) == NULL) || ((pWidget = pElement->pWidget) == NULL))
		return bRet;

	pElement->setStretch(Size, Sel);
	bRet = true;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return bRet;
}

bool CtLayout::setLayout(int Screen)
{
	if (m_Region[Screen].isValid() != true) 
		return false;

	switch (getLayoutType()) {
	case LayoutVertical:		return setVLayout(Screen);
	case LayoutHolizontal:		return setHLayout(Screen);
	case LayoutGrid:			return false;
	default:					return setStackLayout(Screen);
	}
	return false;
}

bool CtLayout::setStackLayout(int Screen)
{
	bool bRet = false;
	Element* pElement = NULL;
	CtWidget* pWidget;
	CtVector::Vector<Element*>* pVisibles = NULL;

	if (m_Region[Screen].isValid() == false)
		return bRet;

	if (((pVisibles = getElements()) == NULL) || (pVisibles->empty() == true))
		return bRet;
	
	for (int i = 0; i < pVisibles->size(); i++) {
		if (((pElement = (*pVisibles)[i]) == NULL) || ((pWidget = pElement->pWidget) == NULL))
			continue;

		(*pVisibles)[i]->Index = i;
		pWidget->setRegion(pElement->allocate(m_Region[Screen], pWidget->getSize()), Screen);
		pWidget->setAlign(pElement->Align);
	}
	
    return bRet;	
}

bool CtLayout::setVLayout(int Screen)
{
	bool bRet = false;
	int stretch_total = 0, stretchsize_total = 0, verifi_total = 0, remain = 0, autosize_count = 0;
	int size = 0, size_total = 0;
	CtRegion section = m_Region[Screen];
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pVisibles = NULL;

    if (section.isValid() == false)
        return bRet;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
			continue;
		
		if (pElement->Stretch[Screen].Size.height > 0) {
			stretchsize_total += pElement->Stretch[Screen].Size.height;
		} else {
			stretch_total += pElement->Stretch[Screen].Ratio;
			autosize_count++;
		}
	}

	if (isStretched()) {
		float size_one = 0.0f;

		if (stretch_total <= 0) return bRet;
	
		size_total = m_Region[Screen].height;
		size_one = ((float)size_total - (float)stretchsize_total) / (float)stretch_total;

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;

			verifi_total += (int)(size_one * pElement->Stretch[Screen].Ratio);
		}
		remain = size_total - stretchsize_total - verifi_total;

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;

			if (pElement->Stretch[Screen].Size.height > 0) {
				size = pElement->Stretch[Screen].Size.height;

			}
			else {
				int stretch = pElement->Stretch[Screen].Ratio;
				size = (int)(size_one * stretch);
				if (remain > 0) {
					remain--;
					size++;
				}
			}
			section.height = size;/* pgr0351 */
			if ((pWidget = pElement->pWidget) != NULL) {
				if (pWidget->setRegion(pElement->allocate(section, pWidget->getSize()), Screen) == true)
					bRet = true;
				pWidget->setAlign(pElement->Align);
			}
			section.y += size;/* pgr0351 */
		}
	}
	else {
		int size_one = 0;
		if (autosize_count > 0) {
			size_one = (int)((m_Region[Screen].height - stretchsize_total) / autosize_count);
			remain = (m_Region[Screen].height - stretchsize_total) - (autosize_count * (int)size_one);
		}

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;

			if (pElement->Stretch[Screen].Size.height > 0) {
				size = pElement->Stretch[Screen].Size.height;
			}
			else if (pElement->pWidget && pElement->pWidget->getSize().height > 0) {
				size = pElement->pWidget->getSize().height;
			}
			else {
				size = (int)size_one;
				if (remain > 0) {
					remain--;
					size++;
				}
			}

			section.height = size;/* pgr0351 */
			if ((pWidget = pElement->pWidget) != NULL) {
				if (pWidget->setRegion(pElement->allocate(section, pWidget->getSize()), Screen) == true)
					bRet = true;
				pWidget->setAlign(pElement->Align);
			}
			section.y += size;/* pgr0351 */
		}
	}
		
	return bRet;

}

bool CtLayout::setHLayout(int Screen)
{
	bool bRet = false;
	int stretch_total = 0, stretchsize_total = 0, verifi_total = 0, remain = 0, autosize_count = 0;
	int size = 0, size_total = 0;
	CtRegion section = m_Region[Screen];
	SplitElement* pElement = NULL;
	CtWidget* pWidget = NULL;
	CtVector::Vector<Element*>* pVisibles = NULL;

	if (section.isValid() == false)
		return bRet;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;
	
	for (int i = 0; i < pVisibles->size(); i++) {
		if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
			continue;

		if (pElement->Stretch[Screen].Size.width > 0) {
			stretchsize_total += pElement->Stretch[Screen].Size.width;
		} else {
			stretch_total += pElement->Stretch[Screen].Ratio;
			autosize_count++;
		}
	}
	
	if (isStretched()) {
		float size_one = 0.0f;
		if (stretch_total <= 0) return bRet;

		size_total = m_Region[Screen].width;
		size_one = ((float)(size_total - stretchsize_total) / (float)stretch_total);

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;

			verifi_total += (int)(size_one * pElement->Stretch[Screen].Ratio);
		}
		remain = size_total - stretchsize_total - verifi_total;

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;

			if (pElement->Stretch[Screen].Size.width > 0) {
				size = pElement->Stretch[Screen].Size.width;
			}
			else {
				int stretch = pElement->Stretch[Screen].Ratio;
				size = (int)(size_one * stretch);
				if (remain > 0) {
					remain--;
					size++;
				}
			}
			section.width = size;/* pgr0351 */
			if ((pWidget = pElement->pWidget) != NULL) {
				if (pWidget->setRegion(pElement->allocate(section, pWidget->getSize()), Screen) == true)
					bRet = true;
				pWidget->setAlign(pElement->Align);
			}
			section.x += size;/* pgr0351 */
		}
	}
	else {
		int size_one = 0;
		if (autosize_count > 0) {
			size_one = (m_Region[Screen].width - stretchsize_total) / autosize_count;
			remain = (m_Region[Screen].width - stretchsize_total) - (autosize_count * (int)size_one);
		}

		for (int i = 0; i < pVisibles->size(); i++) {
			if (((pElement = (SplitElement*)(*pVisibles)[i]) == NULL) || !(pElement->ScreenSel & toSelScreen(Screen)))
				continue;
			
			if (pElement->Stretch[Screen].Size.width > 0) {
				size = pElement->Stretch[Screen].Size.width;
			}
			else if (pElement->pWidget && pElement->pWidget->getSize().width > 0) {
				size = pElement->pWidget->getSize().width;
			}
			else {
				size = (int)(size_one);
				if (remain > 0) {
					remain--;
					size++;
				}
			}
			section.width = size;/* pgr0351 */
			if ((pWidget = pElement->pWidget) != NULL) {
				if (pWidget->setRegion(pElement->allocate(section, pWidget->getSize()), Screen) == true)
					bRet = true;
				pWidget->setAlign(pElement->Align);
			}
			section.x += size;/* pgr0351 */
		}
	}
	
	return bRet;;
}

bool CtLayout::setGridLayout(short RowNum, short ColumnNum, int Screen)
{
	bool bRet = false;
	CtRegion section = m_Region[Screen];
	int i, j;
	int remain_v = 0, remain_h = 0;
	int size_v = 0, size_h = 0;
	Element* pElement = NULL;
	CtVector::Vector<Element*>* pVisibles = NULL;

	if (section.isValid() == false)
		return bRet;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;
	
	if (ColumnNum < 0 || RowNum < 0)
		return bRet;
	
	remain_v = m_Region[Screen].height % RowNum;
	for (i = 0; i < RowNum; i++) {
		if ((size_v = m_Region[Screen].height / RowNum) <= 1)
			return bRet;
		
		if (remain_v > 0) {
			remain_v--;
			size_v++;
		}
		section.height = size_v;/* pgr0351 */
		section.x = m_Region[Screen].x;/* pgr0351 */
		remain_h = m_Region[Screen].width % ColumnNum;
		for (j = 0; j < ColumnNum; j++) {
			if (pVisibles->size() < (i * ColumnNum +j +1 ))
				break;
			
			CtWidget* pWidget = NULL;
			if ((size_h = m_Region[Screen].width / ColumnNum) <= 1)
				return bRet;
			
			if (remain_h > 0) {
				remain_h--;
				size_h++;
			}
			section.width = size_h;/* pgr0351 */

			
			if ((pElement = (*pVisibles)[(i * ColumnNum) +j]) != NULL) {
				if ((pWidget = pElement->pWidget) != NULL) {
					if (pWidget->setRegion(pElement->allocate(section, pWidget->getSize()), Screen) == true)
						bRet = true;
					pWidget->setAlign(pElement->Align);
				}
			}
			section.x += size_h;/* pgr0351 */
		}
		section.y += size_v;/* pgr0351 */
	}

	return bRet;
}

bool CtLayout::isRegistered(CtWidget *_pWidget)
{
	if (_pWidget == NULL)
		return false;

	if (_pWidget == this)
		return true;
	
	for (int i = 0; i< m_Elements.size(); i++) {
		CtWidget* pWidget = NULL;
		if (m_Elements[i] == NULL)						continue;
		if ((pWidget = m_Elements[i]->pWidget) == NULL)	continue;
		
		if (pWidget == _pWidget)
			return true;
		
		if (pWidget->isLayout() == true) {
			if (static_cast<CtLayout*>(pWidget)->isRegistered(pWidget) == true) {
				return true;
			}
		}
    }
	
    return false;
}

unsigned long CtLayout::getDrawKey()
{
	unsigned long key = 0;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if ((pDrawInfo = getDrawInfo()) != NULL) {
		key = pDrawInfo->getDrawKey();
	}

	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return key;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		key = CtDrawInfo::calcKey(key, pWidget->getDrawKey());
	}
	
	return key;
}

bool CtLayout::setDrawImage()
{
	if (m_pBackground == NULL) {
		m_pBackground = new CtRect(CtColor::Trans);
	}
	
	return CtWidget::setDrawImage();
}

CtDrawInfo* CtLayout::getDrawInfo(const CtRegion& Clip, int Screen)
{
	CtRegion clip = Clip;

	if (m_pBackground == NULL)
		return NULL;

	if (clip == NoRegion)
		return m_pBackground;

	clip &= m_Region[Screen];

	if (clip.isValid() != true)
		return NULL;

	m_ClearRegion[Screen] = m_Region[Screen];

	m_pBackground->setRegion(m_Region[Screen]);
	m_pBackground->setClip(clip);
	m_pBackground->setTrans(isTrans());
	
	return m_pBackground;
}

bool CtLayout::getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtRegion clip = Clip;
	CtWidget* pWidget = NULL;
	CtDrawInfo* pDrawInfo = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isVisible(Screen) != true)
		return bRet;

	if (isCollision(clip, Screen) != true)
		return bRet;
	
	if ((pDrawInfo = getDrawInfo(Clip, Screen)) != NULL) {
		List.push_back(pDrawInfo);
		bRet = true;
	}

	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		if (pWidget->isCollision(clip, Screen) == false)
			continue;

		if (pWidget->getDrawInfo(List, clip, Screen) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtRegion clip = Clip;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isCollision(clip, Screen) != true)
		return bRet;
	
	clearInvalidate(Screen);
	
	if (isVisible(Screen) != true)
		return bRet;

	clip &= m_Region[Screen];

	if (CtWidget::draw(clip, Screen) == true)
		bRet = true;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;

		if (pWidget->draw(clip, Screen) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if (isVisible(Screen) == false)
		return bRet;
	
	bRet = CtWidget::drawShift(shift_x, shift_y, Clip, Screen);
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		if (pWidget->isCollision(Clip, Screen) == false)
			continue;
		
		if (pWidget->drawShift(shift_x, shift_y, Clip, Screen) == true)
			bRet = true;
	}

	return bRet;
}

bool CtLayout::isFastDraw() const
{
	return m_bFastDraw;
}

bool CtLayout::setFastDraw(bool bFast)
{
	if (m_bFastDraw == bFast)
		return false;
	
	m_bFastDraw = bFast;

	return true;
}

bool CtLayout::initialFastDraw()
{
	bool bRet = false;
	CtWidget* pWidget;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	if ((m_Region[0].isValid() != true) && (m_Size.isValid() != true))
		return false;
	
	if (m_Region[0].isValid() != true)
		m_Region[0] = CtRegion(0, 0, m_Size.width, m_Size.height);
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->initialFastDraw() == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::cleanupFastDraw()
{
	return false;
}

bool CtLayout::getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	
	switch (SearchType) {
	case Fastdraw: {
		if (checkWidgetType(WidgetType, this) == true) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
			break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			if (pWidget->isVisible(Screen) != true)
				continue;

			if (pWidget->isLayout() == true) {
				bRet = static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region);
			} else if (pWidget->isFastDraw() == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
		
	case Invalidated:
		if (checkWidgetType(WidgetType, this) == true) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
			break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			if ((pWidget->isVisible(Screen) == true) && (pWidget->isInvalidate() == true)) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;

	case Registered:
		if (checkWidgetType(WidgetType, this) == true) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
			break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;
				
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
		
	case RegisteredContains:
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
			break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			
			if (pWidget->isContains(Region, Screen) != true)
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;
				
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
		
	case RegisteredCollisions:
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
			break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			
			if (pWidget->isCollision(Region, Screen) != true)
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;
				
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
		
	case Visible:
		if (isVisible(Screen) != true) break;
		
		if (checkWidgetType(WidgetType, this) == true) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true))
			break;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			if (pWidget->isVisible(Screen) != true)
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;

			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;

	case VisibleContains:
		if (isVisible(Screen) != true) break;
		
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true))
			break;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			if ((pWidget->isVisible(Screen) != true) || (pWidget->isContains(Region, Screen) != true))
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;
				
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
		
	case VisibleCollisions:
		if (isVisible(Screen) != true) break;
		
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) {
			if ((pList != NULL) && (pList->find(this) != true))  pList->push_back(this);
			bRet = true;
		}
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true))
			break;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
				continue;
			if ((pWidget->isVisible(Screen) != true) || (pWidget->isCollision(Region, Screen) != true))
				continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->getWidgets(SearchType, pList, WidgetType, Screen, Region) == true)
					bRet = true;
				
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				if ((pList != NULL) && (pList->find(pWidget) != true))  pList->push_back(pWidget);
				bRet = true;
			}
		}
		break;
	}
	default:
		break;
    }
	
    return bRet;
}

bool CtLayout::existWidget(SearchType SearchType, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	
	switch (SearchType) {
	case Fastdraw: {
		if (checkWidgetType(WidgetType, this) == true) return true;
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true)) return false;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if (pWidget->isVisible(Screen) != true) continue;

			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (pWidget->isFastDraw() == true) {
				return true;
			}
		}
		break;
		
	case Invalidated:
		if (checkWidgetType(WidgetType, this) == true) return true;
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true)) return false;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if ((pWidget->isVisible(Screen) == true) && (pWidget->isInvalidate() == true))
				return true;
		}
		break;

	case Registered:
		if (checkWidgetType(WidgetType, this) == true) return true;
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true)) break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;
		
	case RegisteredContains:
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) return true;
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true)) break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if (pWidget->isContains(Region, Screen) != true) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;
		
	case RegisteredCollisions:
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) return true;
		if (((pElements = getElements()) == NULL) || (pElements->empty() == true)) break;
		
		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if (pWidget->isCollision(Region, Screen) != true) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;
		
	case Visible:
		if ((isVisible(Screen) == true) && (checkWidgetType(WidgetType, this) == true)) return true;
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true)) return false;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if (pWidget->isVisible(Screen) != true) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;

	case VisibleContains:
		if ((isContains(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) return true;
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true)) return false;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if ((pWidget->isVisible(Screen) != true) || (pWidget->isContains(Region, Screen) != true)) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;
		
	case VisibleCollisions:
		if ((isCollision(Region, Screen) == true) && (checkWidgetType(WidgetType, this) == true)) return true;
		if (((pElements = getVisibles()) == NULL) || (pElements->empty() == true)) return false;

		for (int i = 0; i < pElements->size(); i++) {
			if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL)) continue;
			if ((pWidget->isVisible(Screen) != true) || (pWidget->isCollision(Region, Screen) != true)) continue;
			
			if (pWidget->isLayout() == true) {
				if (static_cast<CtLayout*>(pWidget)->existWidget(SearchType, WidgetType, Screen, Region) == true)
					return true;
			} else if (checkWidgetType(WidgetType, pWidget) == true) {
				return true;
			}
		}
		break;
	}
	default:
		break;
    }
	
    return false;
}

bool CtLayout::initialFocus(bool bSilent)
{
	return false;
}

CtWidget* CtLayout::getNeary(const CtRegion& currentRegion, const CtWidgetType Type, const CtDirection Dir)
{
	CtWidget::List List;
	CtRegion myRegion = getRegion();
	CtRegion cRegion = currentRegion;
	CtRegion tRegion = myRegion;
	CtPosition cPos;
	cPos.x = cRegion.x + cRegion.width/2;/* pgr0351 */
	cPos.y = cRegion.y + cRegion.height/2;/* pgr0351 */
	
	CtWidget* nearyWidget = NULL;
	int nearyDistans = 0;

	switch (Dir) {
	case DirUp:
		tRegion.height = cRegion.y - myRegion.y;/* pgr0351 */
		break;
	case DirDown:
		tRegion.y = cRegion.y + cRegion.height;/* pgr0351 */
		tRegion.height = (myRegion.y + myRegion.height) - tRegion.y;/* pgr0351 */
		break;
	case DirLeft:
		tRegion.width = cRegion.x - myRegion.x;/* pgr0351 */
		break;
	case DirRight:
		tRegion.x = cRegion.x + cRegion.width;/* pgr0351 */
		tRegion.width = (myRegion.x + myRegion.width) - tRegion.x;/* pgr0351 */
		break;
	default:
		return NULL;
	}

	if (getWidgets(VisibleCollisions, &List, Type, 0, tRegion) != true)
		return NULL;

    for (CtWidget::ListItr Itr = List.begin(); Itr != List.end(); ++Itr) {
		if ((*Itr) == NULL) continue;
		
		CtPosition tmpPos = (*Itr)->getCenterPosition();
		int distans = (tmpPos.x - cPos.x)*(tmpPos.x - cPos.x) + (tmpPos.y - cPos.y)*(tmpPos.y - cPos.y);

		if ((nearyDistans == 0) || (distans < nearyDistans)) {
			nearyWidget = *Itr;
			nearyDistans = distans;
			
		} else if ((nearyWidget != NULL) && (nearyDistans == distans)) {
			if ((*Itr)->getCenterPosition().x <= nearyWidget->getCenterPosition().x) {
				nearyWidget = (*Itr);
			}
		}
	}
	
	return nearyWidget;
}

bool CtLayout::handleTouchEvent(const CtEventTouch& Touch)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->handleTouchEvent(Touch) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::handleKeyEvent(const CtEventKey& Key)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->handleKeyEvent(Key) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	
	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return false;

	for (int i = 0; i < pElements->size(); i++) {
		if (((*pElements)[i] == NULL) || ((pWidget = (*pElements)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->handleParamEvent(Param) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->handleButtonEvent(Button) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtLayout::handleWidgetEvent(const CtEventWidget& Widget)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->handleWidgetEvent(Widget) == true)
			bRet = true;
	}
	
	return bRet;
}


void CtLayout::outputOutline(int depth, const char* header, int Screen) 
{
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;
	
	CtWidget::outputOutline(depth, header, Screen);
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return;
	
	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((*pVisibles)[i]->pWidget == NULL)) continue;
		(*pVisibles)[i]->pWidget->outputOutline(depth + 1, (i != pVisibles->size()-1 ? "Ñ•" : "Ñ§"), Screen);
	}
}

void CtLayout::printElements(CtVector::Vector<CtWidget::Element*>* pElements, char* pTitle)
{
	if (pElements == NULL)
		return;
	
	CtDebugPrint(CtDbg, "======== [%p] %s print Elements ========\n", this, pTitle);
	for (int i = 0; i < pElements->size(); i++) {
		CtDebugPrint(CtDbg, "    %2d)  Index:%2d    Widget:%p\n", i, (*pElements)[i]->Index, (*pElements)[i]->pWidget);

	}
	CtDebugPrint(CtDbg, "==\n");
}

