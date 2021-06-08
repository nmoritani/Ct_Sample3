/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtListView
 */


#include "CtWindow.h"
#include "CtListView.h"

void CtListView::ctor(short Row, short Column)
{
	setClassType(CtClassType_ListView);
	setLayoutType(LayoutVertical);
	
	m_ViewRow = Row;
	m_ViewColumn = Column;
	m_CurrentElement = -1;
	m_bScroll = true;

	m_Visibles.resize(m_ViewRow * m_ViewColumn);
	m_Blanks.resize(m_ViewRow * m_ViewColumn);
	for (int i = 0; i< m_Visibles.size(); i++) {
		m_Blanks[i] = new CtLayout::SplitElement(new CtLabel(), DefaultMargin, DefaultAlign, 1);
		m_Blanks[i]->Index = -1;
		m_Blanks[i]->pWidget->setParent(this);
		m_Visibles[i] = m_Blanks[i];
	}
	m_pSelect = NULL;
	m_SelectMargin = DefaultMargin;
	
	setEventFilter((CtEventFilter)(EventButton));
}

CtListView::CtListView()
{
	ctor(5);
}

CtListView::CtListView(short ViewRow)
{
	ctor(ViewRow);
}

CtListView::CtListView(short ViewRow, const CtColor& Color) :
	CtLayout(Color)
{
	ctor(ViewRow);
}

CtListView::CtListView(short ViewRow, const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	ctor(ViewRow);
}

CtListView::CtListView(short ViewRow, const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	ctor(ViewRow);
}

CtListView::CtListView(short ViewRow, short ViewColumn)
{
	ctor(ViewRow, ViewColumn);
}

CtListView::CtListView(short ViewRow, short ViewColumn, const CtColor& Color) :
	CtLayout(Color)
{
	ctor(ViewRow, ViewColumn);
}

CtListView::CtListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	ctor(ViewRow, ViewColumn);
}

CtListView::CtListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	ctor(ViewRow, ViewColumn);
}

CtListView::~CtListView()
{
	for (int i = 0; i< m_Blanks.size(); i++) {
		if (m_Blanks[i] != NULL)
			delete m_Blanks[i];
	}
	if (m_pSelect != NULL)
		delete m_pSelect;
}

bool CtListView::clear()
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	Element* pElement = NULL;
	CtWidget* pWidget = NULL;

	if (pElements->size() == 0)
		return false;
	
	for (int i = 0; i < pElements->size(); i++) {
		if (((pElement = (*pElements)[i]) != NULL) && ((pWidget = pElement->pWidget) != NULL)) {
			if (pWidget->isButton() == true) {
				CtWindow *pWin = getWindow();
				if (pWin != NULL)
					pWin->clearFocusWidget(pWidget);
			}
			delete pElement;
		}
	}
	pElements->clear();
	setTopElement(0);
	return true;
}

bool CtListView::setSelectLabel(CtLabel* pLabel, CtMargin Margin)
{
	m_pSelect = pLabel;
	m_pSelect->setParent(this);
	m_pSelect->setTrans(true);
	m_pSelect->setVisible(false);
	
	m_SelectMargin = Margin;
	return true;
}

bool CtListView::updateVisibles()
{
	CtVector::Vector<Element*>* pVisibles = NULL;
	CtVector::Vector<Element*>* pElements = NULL;
	int top = -1;

	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return false;
	
	for (int i = 0; i < pVisibles->size(); i++) {
		if ((*pVisibles)[i] == NULL)
			continue;
		
		top = (*pVisibles)[i]->Index;
		break;
	}

	if (top < 0) top = 0;
	
	setTopElement(top);
	return true;
}

bool CtListView::setLayout(int Screen)
{
	return CtLayout::setLayout(Screen);
}

bool CtListView::setViewRow(short ViewRow)
{
	bool bRet = false;
	
	if (m_ViewRow == ViewRow)
		return bRet;

	if (m_ViewRow > ViewRow) {
		for (int i = ViewRow; i < m_Visibles.size(); i++) {
			m_Visibles[i] = NULL;
			if (m_Blanks[i] != NULL)
				delete m_Blanks[i];
		}
		m_ViewRow = ViewRow;
		m_Visibles.resize(m_ViewRow);
		m_Blanks.resize(m_ViewRow);
		bRet = true;
		
	} else if (m_ViewRow < ViewRow) {
		m_Visibles.resize(ViewRow);
		m_Blanks.resize(ViewRow);
		for (int i = m_ViewRow; i < m_Visibles.size(); i++) {
			m_Blanks[i] = new CtLayout::SplitElement(new CtLabel(), DefaultMargin, DefaultAlign, 1);
			m_Blanks[i]->Index = -1;
			m_Visibles[i] = m_Blanks[i];
		}
		m_ViewRow = ViewRow;
		bRet = true;
	}
	return bRet;
}

int CtListView::getViewRow() const
{
	return m_ViewRow;
}

bool CtListView::setViewColumn(short ViewColumn)
{
	return false;
}

int CtListView::getViewColumn() const
{
	return 1;
}

int CtListView::getViewSize() const
{
	return m_ViewRow * m_ViewColumn;
}

CtWidget* CtListView::getFocusWidget()
{
	return getWidget(m_CurrentElement);
}

CtWidget* CtListView::getWidget(int Index)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	if (0 > Index || Index >= pElements->size()) {
		return NULL;
	}
	
	return (*pElements)[Index]->pWidget;
}

bool CtListView::isValidElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if (Element < 0 || pElements->size() <= Element)
		return false;
	if ((*pElements)[Element] == NULL)
		return false;
	if ((*pElements)[Element]->Index < 0)
		return false;
	if ((*pElements)[Element]->pWidget == NULL)
		return false;
	
	return true;
}

bool CtListView::isValidElement(CtWidget::Element* pElement)
{
	if (pElement == NULL)
		return false;
	if (pElement->Index < 0)
		return false;
	if (pElement->pWidget == NULL)
		return false;
	
	return true;
}

int CtListView::getValidElement(int Element, CtListView::ElementDir Dir)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	int Max = pElements->size();

	if (Element < 0 || Max < Element)
		return -1;
	
	switch (Dir) {
	case Prev:
		for (int i = Element -1; i >= 0; i--) {
			if (isValidElement(i) == true)
				return i;
		}
		break;
	case Next:
		for (int i = Element +1; i < Max; i++) {
			if (isValidElement(i) == true)
				return i;
		}
		break;
	default:
		break;
	}
	
	return -1;
}

bool CtListView::isSelectableElement(int Element)
{
	return isValidElement(Element);
}

bool CtListView::isSelectableElement(CtWidget::Element* pElement)
{
	return isValidElement(pElement);
}

int CtListView::getSelectableElement(int Element, CtListView::ElementDir Dir)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	int Max = pElements->size();

	if (Element < 0 || Max < Element)
		return -1;
	
	switch (Dir) {
	case Prev:
		for (int i = Element -1; i >= 0; i--) {
			if (isSelectableElement(i) == true)
				return i;
		}
		break;
	case Next:
		for (int i = Element +1; i < Max; i++) {
			if (isSelectableElement(i) == true)
				return i;
		}
		break;
	default:
		break;
	}
	
	return -1;
}

bool CtListView::selectElement(int Element, bool bEnd)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	if (isValidElement(Element) != true)
		return bRet;

	if ((*pElements)[Element]->pWidget->isFocusable() == true) {
		if (static_cast<CtButton*>((*pElements)[Element]->pWidget)->setFocus() == true)
			bRet = true;
		
	} else if (m_pSelect != NULL) {
		CtWidget* pWidget = (*pElements)[Element]->pWidget;
		
		if (setFocusInElement(pWidget, bEnd) == true)
			bRet = true;
		
		for (int i = 0; i < CT_SCREEN_NUM; i++) {
			CtRegion r = pWidget->getRegion(i);
			CtRegion tmp = CtRegion(r.x + m_SelectMargin.Left,
									r.y + m_SelectMargin.Top,
									r.width  - (m_SelectMargin.Left + m_SelectMargin.Right),
									r.height - (m_SelectMargin.Top  + m_SelectMargin.Bottom));
			m_pSelect->setRegion(tmp, i);
			m_pSelect->setVisible(true);
			pWidget->setInvalidate();
		}
	}

	return bRet;
}

bool CtListView::unselectElement(int Element)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	if (isValidElement(Element) != true)
		return bRet;
	
	if ((*pElements)[Element]->pWidget->isFocusable() == true) {
		if (static_cast<CtButton*>((*pElements)[Element]->pWidget)->cancelFocus() == true)
			bRet = true;

	} else if (m_pSelect != NULL) {
		CtWidget* pWidget = (*pElements)[Element]->pWidget;
		
		if (cancelFocusInElement(pWidget) == true)
			bRet = true;
		m_pSelect->setVisible(false);
		pWidget->setInvalidate();
	}
	
	return bRet;
}

bool CtListView::setFocusInElement(CtWidget* pWidget, bool bEnd)
{
	CtWidget::List widget_list;
	CtButton* pButton = NULL;

	if (pWidget == NULL)
		return false;
	
	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if (((pButton = (CtButton*)(*Widget)) != NULL) && (pButton->isFocused() == true))	// Element内のどこかにFocusがあたってたら何もしない
				return true;
		}
		
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if ((pButton = (CtButton*)(*Widget)) != NULL) {
				if (bEnd == false) {
					if (pButton->isFocusable() == true) {	/* pgr0689 */
						pButton->setFocus();	// Element内の先頭にFocusを当てる
						return true;
					}
				}
			}
		}
		if (pButton != NULL) {
			pButton->setFocus();			// Element内の末尾にFocusを当てる	/* pgr0689 */
			return true;
		}
	}
	return false;
}

bool CtListView::cancelFocusInElement(CtWidget* pWidget)
{
	bool bRet = false;
	CtWidget::List widget_list;
	CtButton* pButton = NULL;
	
	if (pWidget == NULL)
		return bRet;
	
	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if (((pButton = (CtButton*)(*Widget)) != NULL) && (pButton->isFocused() == true)) {
				pButton->cancelFocus();
				bRet = true;
			}
		}
	}
	return bRet;
}

bool CtListView::isFocusedInElement(CtWidget* pWidget)
{
	CtWidget::List widget_list;
	CtButton *pButton = NULL;
	
	if (pWidget == NULL)
		return false;
	
	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if (((pButton = (CtButton*)(*Widget)) != NULL) && (pButton->isFocused() == true)) {
				return true;
			}
		}
	}
	return false;
}


bool CtListView::nextFocusInElement()
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtWidget* pWidget = NULL;
	CtButton* pFocus = NULL;
	CtButton* pButton = NULL;
	CtWidget::List widget_list;

	if (isValidElement(m_CurrentElement) != true)
		return false;

	pWidget = (*pElements)[m_CurrentElement]->pWidget;
	if (pWidget->isButton() == true)
		return false;
	
	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if ((pButton = (CtButton*)(*Widget)) == NULL)
				continue;
			
			if ((pFocus != NULL) && (pButton->isFocusable() == true)) {
				pFocus->cancelFocus();
				pButton->setFocus();
				return true;
			}
			if ((pButton->isFocusable() == true) && (pButton->isFocused() == true))
				pFocus = pButton;
		}
	}
	return false;
}

bool CtListView::prevFocusInElement()
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtWidget* pWidget = NULL;
	CtButton* pFocus = NULL;
	CtButton* pButton = NULL;
	CtWidget::List widget_list;

	if (isValidElement(m_CurrentElement) != true)
		return false;

	pWidget = (*pElements)[m_CurrentElement]->pWidget;
	if (pWidget->isButton() == true)
		return false;
	
	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			if ((pButton = (CtButton*)(*Widget)) == NULL)
				continue;

			if ((pButton->isFocusable() == true) && (pButton->isFocused() == true)) {
				if (pFocus == NULL)
					return false;
				
				pButton->cancelFocus();
				pFocus->setFocus();
				return true;
			}
			
			if (pButton->isFocusable() == true) {
				pFocus = pButton;
			}
		}
	}
	return false;
}

int CtListView::getValidElementsNum(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if (Element < 0)
		return pElements->size();
	else
		return Element;
}

bool CtListView::setCurrentElement(int _Target, bool bEnd)
{
	int Current = m_CurrentElement;
	int Target = _Target;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();

	if (Target == Current)
		return false;
	
	if (isValidElement(Target) != true) {	// 対象のElementが無効の場合は前方もしくは後方のElementに
		if (((Target = getValidElement(_Target, CtListView::Prev)) < 0) && ((Target = getValidElement(_Target, CtListView::Next)) < 0))
			return false;
	}

	if (pVisibles->find((*pElements)[Target]) != true) {
		int top = -1, bottom = -1;
		if ((*pVisibles)[0] != NULL)
			top = (*pVisibles)[0]->Index;
		if ((*pVisibles)[pVisibles->size() -1] != NULL)
			bottom = (*pVisibles)[pVisibles->size() -1]->Index;

		if (top < Target && Target < bottom) {
		} else if ((top > Target) || (top < 0)) {
			setTopElement(Target);
		} else if (bottom < Target) {
			setBottomElement(Target);
		}
	}

	unselectElement(Current);
	if (isSelectableElement(Target) != true) {
		if (((Target = getSelectableElement(_Target, CtListView::Prev)) < 0) && ((Target = getSelectableElement(_Target, CtListView::Next)) < 0))
			return true;
	}
	selectElement(Target, bEnd);
	m_CurrentElement = Target;

	return true;
}

int CtListView::getElementNo(CtWidget::Element* pElement)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	for (int i = 0; i < pElements->size(); i++) {
		if ((*pElements)[i] == NULL)
			continue;
		
		if ((*pElements)[i] == pElement)
			return i;
	}
	return -1;
}

bool CtListView::setTopElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	int Max = pElements->size() -1;
	int element = Element;
	
	if ((element < 0) || ((0 < Max) && (Max < element)))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		
		if ((element < 0) || (Max < element)) {
			if ((*pVisibles)[i] != m_Blanks[i]) {
				(*pVisibles)[i] = m_Blanks[i];
				(*pVisibles)[i]->pWidget->setInvalidate();
			}
			
		} else {
			if ((*pVisibles)[i] != (*pElements)[element]) {
				(*pVisibles)[i] = (*pElements)[element];
				(*pVisibles)[i]->pWidget->setInvalidate();
			}
		}
		element = getValidElement(element, CtListView::Next);
	}

	selectElement(m_CurrentElement);

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}

	//	printElements(pVisibles, "set Top");
	
	return true;
}

bool CtListView::setBottomElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	int element = Element;
	
	if ((element < 0) || (pElements->size() <= element))
		return false;
	
	for (int i = pVisibles->size()-1; i >= 0; i--) {
		if (element < 0) {
			if ((*pVisibles)[i] != m_Blanks[i]) {
				(*pVisibles)[i] = m_Blanks[i];
				(*pVisibles)[i]->pWidget->setInvalidate();
			}
			
		} else {
			if ((*pVisibles)[i] != (*pElements)[element]) {
				(*pVisibles)[i] = (*pElements)[element];
				(*pVisibles)[i]->pWidget->setInvalidate();
			}
		}
		element = getValidElement(element, CtListView::Prev);
	}
	
	selectElement(m_CurrentElement);
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}

	//	printElements(pVisibles, "set Bottom");
	
	return true;
}

int CtListView::getCurrentIndex()
{
	return m_CurrentElement;
}


bool CtListView::nextElement()
{
	int Target = 0;
	int Current = m_CurrentElement;

	if (Current < 0)	Target = getSelectableElement(0, CtListView::Next);
	else				Target = getSelectableElement(Current, CtListView::Next);

	if ((Target < 0) || (Target == Current))
		return false;

	if (m_bScroll != true) {
		if (getPage(Current) != getPage(Target)) {
			nextPage();
			return true;
		}
	}

	return setCurrentElement(Target);
}

bool CtListView::prevElement()
{
	int Target = 0;
	int Current = m_CurrentElement;
	
	if (Current < 0)	Target = getSelectableElement(0, CtListView::Prev);
	else				Target = getSelectableElement(Current, CtListView::Prev);

	if ((Target < 0) || (Target == Current))
		return false;

	if (m_bScroll != true) {
		if (getPage(Current) != getPage(Target)) {
			prevPage();
			return true;
		}
	}
	
	return setCurrentElement(Target, true);
}

bool CtListView::setInitialFocus(int Element)
{
	bool bRet = false;
	CtButton *pButton = NULL;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if (pElements->size() == 0)
		return bRet;

	if (Element < 0) {
		for (int i = 0; i < pElements->size(); i++) {
			if ((*pElements)[i] == NULL) continue;
			if ((pButton = (CtButton*)(*pElements)[i]->pWidget) == NULL)
				continue;
			
			if (pButton->isFocusable() == true) {
				bRet = setCurrentElement(i);
			}
		}
		
	} else {
		bRet = setCurrentElement(Element);
	}
	
	return bRet;
}

bool CtListView::setPage(int PageNo)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	int top = 0, element = 0, cnt = 0;

	if ((PageNo <= 0) || (getMaxPage() < PageNo))
		return false;
	
	top = (PageNo -1) * (m_ViewRow * m_ViewColumn);
	
	for (int i = 0;  i < pElements->size(); i++) {
		if (isValidElement(i) != true)
			continue;

		if (cnt == top) {
			element = (*pElements)[i]->Index;
			break;
		}
		cnt++;
	}

	setTopElement(element);

	int Target = 0, Current = m_CurrentElement;
	if (pVisibles->find((*pElements)[Current]) != true) {
		for (int i = 0; i < pVisibles->size(); i++) {
			if (isValidElement((*pVisibles)[i]) == true) {
				Target = (*pVisibles)[i]->Index;
				if (Target > Current)
					break;
			}
		}

		unselectElement(Current);
		if (isSelectableElement(Target) != true) {
			int tmp = Target;
			if (((Target = getSelectableElement(tmp, CtListView::Prev)) < 0) && ((Target = getSelectableElement(tmp, CtListView::Next)) < 0))
				return true;
		}
		selectElement(Target);
		m_CurrentElement = Target;
	}

	return true;
}

bool CtListView::nextPage()
{
	int page = getCurrentPage();
	
	if (page >= getMaxPage())
		return false;

	return setPage(page +1);
}

bool CtListView::prevPage()
{
	int page = getCurrentPage();
	
	if (page <= 1)
		return false;

	return setPage(page -1);
}

int CtListView::getCurrentPage()
{
	int index = 0;
	int top = -1;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();


	for (int i = 0; i< pVisibles->size(); i++) {
		if (isValidElement((*pVisibles)[i]) != true)
			continue;
		
		top = (*pVisibles)[i]->Index;
		break;
	}
		
	for (int i = 0; i< pElements->size(); i++) {
		if (isValidElement(i) != true)
			continue;
			
		if (i == top)
			break;
		index++;
	}

	return (index / (m_ViewRow * m_ViewColumn)) + 1;
}

int CtListView::getPage(int Index)
{
	int size = getValidElementsNum(Index);

	return ((size -1) / (m_ViewRow * m_ViewColumn)) + 1;
}

int CtListView::getMaxPage()
{
	int size = getValidElementsNum();
	
	return ((size -1) / (m_ViewRow * m_ViewColumn)) + 1;
}

bool CtListView::initialFocus(bool bSilent)
{
	if (m_CurrentElement < 0) {
		return setCurrentElement(0);
	}
	else {
		return setCurrentElement(m_CurrentElement);
	}
	
	return false;
}

bool CtListView::moveFocus(const CtDirection Dir, bool Silent)
{
	switch (Dir) {
	case DirUp:
		if (prevFocusInElement() == true) {
			return true;
		}
		if (prevElement() == true) {
			return true;
		}
		break;
	case DirDown:
		if (nextFocusInElement() == true) {
			return true;
		}
		if (nextElement() == true) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool CtListView::setDialIndex()
{
	return false;
}

bool CtListView::dialFocus(const bool bPlus, bool Silent)
{
	if (bPlus == true) {
		if (nextFocusInElement() == true) {
			return true;
		}
		if (nextElement() == true) {
			return true;
		}
	} else {
		if (prevFocusInElement() == true) {
			return true;
		}
		if (prevElement() == true) {
			return true;
		}
	}
	return false;
}

bool CtListView::getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip, int Screen)
{
	bool bRet = false;

	if (((bRet = CtLayout::getDrawInfo(List, Clip, Screen)) == true) && (m_pSelect != NULL)) {
		m_pSelect->getDrawInfo(List, m_Region[Screen], Screen);
	}
	clearInvalidate(Screen);
	
	return bRet;
}

bool CtListView::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;

	if (((bRet = CtLayout::draw(Clip, Screen)) == true) && (m_pSelect != NULL)) {
		m_pSelect->draw(m_Region[Screen], Screen);
	}
	clearInvalidate(Screen);
	
	return bRet;
}

bool CtListView::drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	
	if (((bRet = CtLayout::drawShift(shift_x, shift_y, Clip, Screen)) == true) && (m_pSelect != NULL)) {
		m_pSelect->drawShift(shift_x, shift_y, m_Region[Screen], Screen);
		return bRet;
	}
	
	return bRet;
}

bool CtListView::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();

	// リスト制御以外にフォーカスを当てられた場合、そのButtonをカレントにする
	if (Button.isChangeState() != true)
		return bRet;
	if ((Button.getChangeState() & CtEventButton::Focus) == 0)
		return bRet;
	if ((pWidget = Button.getWidget()) == NULL)
		return bRet;
	if (static_cast<CtButton*>(pWidget)->isFocused() != true)
		return bRet;
	
	for (int i = 0; i < pVisibles->size(); i++) {
		if (isSelectableElement((*pVisibles)[i]) != true)
			continue;

		if (((*pVisibles)[i]->pWidget == pWidget) && ((*pVisibles)[i]->Index != m_CurrentElement)) {
			unselectElement(m_CurrentElement);
			m_CurrentElement = (*pVisibles)[i]->Index;
			bRet = true;
		}

		else if ((isFocusedInElement((*pVisibles)[i]->pWidget) == true) && ((*pVisibles)[i]->Index != m_CurrentElement)) {
			unselectElement(m_CurrentElement);
			m_CurrentElement = (*pVisibles)[i]->Index;
			selectElement(m_CurrentElement);
			bRet = true;
		}
	}

	return bRet;
}

bool CtListView::handleTouchEvent(const CtEventTouch& Touch)
{
	CtWidget* pWidget = NULL;
	int Index;
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	CtEventTouch::TouchPosition pos = Touch.getPosition();
	CtPosition Pos = CtPosition(pos.m_X, pos.m_Y);

	if (CtLayout::handleTouchEvent(Touch) == true)
		return true;

	if (Touch.getAction() != CtEventTouch::Press)
		return false;
		
	for (int i = 0; i < pVisibles->size(); i++) {
		if ((*pVisibles)[i] == NULL) 						continue;
		if ((Index = (*pVisibles)[i]->Index) < 0)			continue;
		if ((pWidget = (*pVisibles)[i]->pWidget) == NULL)	continue;

		if (pWidget->isContains(Pos) == true) {
			if (pWidget->isButton() == true)	return pWidget->handleTouchEvent(Touch);
			else								return setCurrentElement(Index);
		}
	}
	return false;
}
