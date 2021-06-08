/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtHLayout
 */


#include "CtMenuListView.h"
#include "CtEventInterface.h"

void CtMenuListView::ctor()
{
	setEventFilter(EventKey);
	m_bLeftKeyAction = true;
	setScroll(false);
}

CtMenuListView::CtMenuListView() :
	CtListView()
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow) :
	CtListView(ViewRow)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, const CtColor& Color) :
	CtListView(ViewRow, Color)
{
	ctor();
}
CtMenuListView::CtMenuListView(short ViewRow, const CtSize& Size, const CtColor& Color) :
	CtListView(ViewRow, Size, Color)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, const CtRegion& Region, const CtColor& Color) :
	CtListView(ViewRow, Region, Color)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, short ViewColumn) :
	CtListView(ViewRow, ViewColumn)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, short ViewColumn, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Color)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Size, Color)
{
	ctor();
}

CtMenuListView::CtMenuListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Region, Color)
{
	ctor();
}

CtMenuListView::~CtMenuListView()
{
}


bool CtMenuListView::isValidElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if (Element < 0 || pElements->size() <= Element)
		return false;
	if ((*pElements)[Element] == NULL)
		return false;
	if ((*pElements)[Element]->pWidget == NULL)
		return false;
	if ((*pElements)[Element]->pWidget->isVisible() != true)
		return false;
	
	return true;
}

bool CtMenuListView::isValidElement(CtWidget::Element* pElement)
{
	if (pElement == NULL)
		return false;
	if (pElement->pWidget == NULL)
		return false;
	if (pElement->pWidget->isVisible() != true)
		return false;
	
	return true;
}

int CtMenuListView::getValidElementsNum(int Element)
{
	int num = 0;
	
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	for (int i = 0; i < pElements->size(); i++) {
		if (isValidElement(i) != true)
			continue;
		num++;
		if (i == Element)
			break;
	}
	
	return num;
}

bool CtMenuListView::isSelectableElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	if (isValidElement(Element) != true)
		return false;

	if ((*pElements)[Element]->pWidget->isFocusable() != true)
		return false;

	return true;
}

bool CtMenuListView::isSelectableElement(CtWidget::Element* pElement)
{
	if (isValidElement(pElement) != true)
		return false;

	if (pElement->pWidget->isFocusable() != true)	/* pgr0541 */
		return false;

	return true;
}

bool CtMenuListView::nextElement()
{
	
	if (CtListView::nextElement() == true)
		return true;

	return setCurrentElement(0);
}

bool CtMenuListView::prevElement()
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	int Target = 0;
	
	if (CtListView::prevElement() == true)
		return true;
	
	for (int i = pElements->size() -1; i >= 0; i--) {
		if (isSelectableElement((*pElements)[i]->Index) == true) {
			Target = (*pElements)[i]->Index;
			break;
		}
	}
	setPage(getMaxPage());	
	return setCurrentElement(Target);
}

bool CtMenuListView::setCurrentElement(int _Target, bool bEnd)
{
	int Current = m_CurrentElement;
	int Target = _Target;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	int CurrentPage = (Current == -1) ? -1 : getPage(Current);
	int TargetPage = getPage(Target);

	if (Target == Current)
		return false;

	if (isValidElement(Target) != true) {	// ëŒè€ÇÃElementÇ™ñ≥å¯ÇÃèÍçáÇÕëOï˚Ç‡ÇµÇ≠ÇÕå„ï˚ÇÃElementÇ…
		if (((Target = getValidElement(_Target, CtListView::Prev)) < 0) && ((Target = getValidElement(_Target, CtListView::Next)) < 0))
			return false;
	}

	if (CurrentPage != TargetPage)
		if (setPage(TargetPage) == true)
			Current = m_CurrentElement;
#if 0
	if (pVisibles->find((*pElements)[Target]) != true) {
		int top = -1, bottom = -1;
		if ((*pVisibles)[0] != NULL)
			top = (*pVisibles)[0]->Index;
		if ((*pVisibles)[pVisibles->size() - 1] != NULL)
			bottom = (*pVisibles)[pVisibles->size() - 1]->Index;

		if (top < Target && Target < bottom) {
		}
		else if ((top > Target) || (top < 0)) {
			setTopElement(Target);
		}
		else if (bottom < Target) {
			setBottomElement(Target);
		}
	}
#endif
	unselectElement(Current);
	if (isSelectableElement(Target) != true) {
		if (((Target = getSelectableElement(_Target, CtListView::Prev)) < 0) && ((Target = getSelectableElement(_Target, CtListView::Next)) < 0))
			return true;
	}
	selectElement(Target, bEnd);
	m_CurrentElement = Target;

	return true;
}

bool CtMenuListView::handleKeyEvent(const CtEventKey& Key)
{
	bool bRet = false;

	if (CtLayout::handleKeyEvent(Key) == true)
		return true;

	if (m_bLeftKeyAction != true)
		if (Key.getKeyCode() == CtEventKey::KeyCode_Left)
			return bRet;
	
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Left:
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Press) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			bRet = true;
		}
		break;
	default:
		break;
	}

	return bRet;
}

bool CtMenuListView::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	int Top = -1;
	int Current = m_CurrentElement;
	
	if ((Button.getChangeState() & (CtEventButton::ChangeState)(CtEventButton::Valid + CtEventButton::Visible)) == 0)
		goto exit;
	
	if (((*pVisibles)[0] != NULL) && ((*pVisibles)[0]->pWidget != NULL)) {
		Top = (*pVisibles)[0]->Index;
	} else {
		bRet = setPage(0);
	}
	
	for (int i = 0; i < pElements->size(); i++) {
		if (((*pElements)[i] == NULL) || ((*pElements)[i]->pWidget == NULL))
			continue;

		if ((*pElements)[i]->pWidget == Button.getWidget())	{
			int element = (*pElements)[i]->Index;

			// topÇ™ïœâªÇµÇΩèÍçá Å® êVÇΩÇ»TOPÇíTÇµÇƒsetTopElement
			if (element == Top) {
				setTopElement(element);
				if (pVisibles->find((*pElements)[Current]) != true) {
					setCurrentElement((*pVisibles)[0]->Index);
				}
			
			// currentÇ™ïœâªÇµÇΩèÍçá Å® êVÇΩÇ»currentÇíTÇµÇƒsetCurrentElement
			} else if (element == m_CurrentElement) {
				setCurrentElement(element);

			} else {
				setTopElement(Top);
				if (pVisibles->find((*pElements)[Current]) != true) {
					setCurrentElement((*pVisibles)[0]->Index);
				}
			}
			bRet = true;
			break;
		}
	}
	
  exit:
	if (CtListView::handleButtonEvent(Button) == true)
		bRet = true;

	return bRet;
}

