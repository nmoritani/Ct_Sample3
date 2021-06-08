/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          Ct2ListView
 */


#include "CtWindow.h"
#include "Ct2ListView.h"

void Ct2ListView::ctor(short Row, short Column)
{
	setEventFilter(EventKey);
	setScroll(false);
	m_ViewColumn2 = 0;
	m_bScrollColumn = false;
	m_bDialPress = false;
	m_FocusPos = 1;
}

Ct2ListView::Ct2ListView() :
	CtListView()
{
	ctor(5);
}

Ct2ListView::Ct2ListView(short ViewRow) :
	CtListView(ViewRow)
{
	ctor(ViewRow);
}

Ct2ListView::Ct2ListView(short ViewRow, const CtColor& Color) :
	CtListView(ViewRow, Color)
{
	ctor(ViewRow);
}

Ct2ListView::Ct2ListView(short ViewRow, const CtSize& Size, const CtColor& Color) :
	CtListView(ViewRow, Size, Color)
{
	ctor(ViewRow);
}

Ct2ListView::Ct2ListView(short ViewRow, const CtRegion& Region, const CtColor& Color) :
	CtListView(ViewRow, Region, Color)
{
	ctor(ViewRow);
}

Ct2ListView::Ct2ListView(short ViewRow, short ViewColumn) :
	CtListView(ViewRow, ViewColumn)
{
	ctor(ViewRow, ViewColumn);
}

Ct2ListView::Ct2ListView(short ViewRow, short ViewColumn, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Color)
{
	ctor(ViewRow, ViewColumn);
}

Ct2ListView::Ct2ListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Size, Color)
{
	ctor(ViewRow, ViewColumn);
}

Ct2ListView::Ct2ListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Region, Color)
{
	ctor(ViewRow, ViewColumn);
}

Ct2ListView::~Ct2ListView()
{
}

CtWidget* Ct2ListView::getFocusWidget()
{
	// TODO
	return NULL;
}

bool Ct2ListView::setFocusInElement(CtWidget* pWidget, bool bEnd)
{
	CtWidget::List widget_list;

	if (pWidget == NULL)
		return false;

	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			CtButton* pButton = (CtButton*)(*Widget);
			if (pButton->isFocused() == true)	// Elementì‡ÇÃÇ«Ç±Ç©Ç…FocusÇ™Ç†ÇΩÇ¡ÇƒÇΩÇÁâΩÇ‡ÇµÇ»Ç¢
				return true;
		}
		
		int count = 0;
		CtButton* pButton = NULL;
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			count++;
			pButton = (CtButton*)(*Widget);
			if (pButton == NULL)
				continue;

			if (m_bScrollColumn == false) {
				if (count == m_FocusPos) {
					if (pButton->isFocusable() == true) {
						pButton->setFocus();	// Elementì‡ÇÃìØÇ∂óÒÇ…FocusÇìñÇƒÇÈ
						m_bScrollColumn = false;
						return true;
					}
				}
			}
			else {
				if (m_FocusPos == m_ViewColumn2) {
					if (pButton->isFocusable() == true) {
						pButton->setFocus();	// Elementì‡ÇÃêÊì™Ç…FocusÇìñÇƒÇÈ
						m_bScrollColumn = false;
						return true;
					}
				}
			}
		}
		if (pButton != NULL) {
			pButton->setFocus();			// Elementì‡ÇÃññîˆÇ…FocusÇìñÇƒÇÈ	/* pgr0689 */
			m_bScrollColumn = false;
			return true;
		}
	}
	return false;
}

bool Ct2ListView::cancelFocusInElement(CtWidget* pWidget)
{
	bool bRet = false;
	CtWidget::List widget_list;

	if (pWidget == NULL)
		return bRet;

	if (pWidget->getWidgets(CtLayout::Visible, &widget_list, WidgetButton) == true) {
		int count = 0;
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			count++;
			CtButton* pButton = (CtButton*)(*Widget);
			if (pButton->isFocused() == true) {
				pButton->cancelFocus();
				m_FocusPos = count;
				bRet = true;
			}
		}
	}
	return bRet;
}

bool Ct2ListView::nextElement()
{
	int Target = 0;
	int Current = m_CurrentElement;

	if (Current < 0)	Target = getSelectableElement(0, CtListView::Next);
	else				Target = getSelectableElement(Current, CtListView::Next);

	if (!((Target < 0) || (Target == Current))) {
		if (m_bScroll != true) {
			if ((Current / m_ViewRow + 1) != (Target / m_ViewRow + 1)) {
				nextPage();
				return true;
			}
		}
		if (setCurrentElement(Target) == true)
			return true;
	}

	return setCurrentElement(0);
}

bool Ct2ListView::prevElement()
{
	int Target = 0;
	int Current = m_CurrentElement;

	if (Current < 0)	Target = getSelectableElement(0, CtListView::Prev);
	else				Target = getSelectableElement(Current, CtListView::Prev);

	if (!((Target < 0) || (Target == Current))) {
		if (m_bScroll != true) {
			if ((Current / m_ViewRow + 1) != (Target / m_ViewRow + 1)) {
				prevPage();
				return true;
			}
		}

		if (setCurrentElement(Target, true) == true)
			return true;
	}

	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	for (int i = pElements->size() - 1; i >= 0; i--) {
		if (isSelectableElement((*pElements)[i]->Index) == true) {
			Target = (*pElements)[i]->Index;
			break;
		}
	}
	setPage(getMaxPage());
	return setCurrentElement(Target);
}

bool Ct2ListView::moveFocus(const CtDirection Dir, bool Silent)
{
	switch (Dir) {
	case DirUp:
		m_bScrollColumn = false;
		if (prevElement() == true) {
			return true;
		}
		break;
	case DirDown:
		m_bScrollColumn = false;
		if (nextElement() == true) {
			return true;
		}
		break;
	case DirLeft:
		m_bScrollColumn = true;
		if (prevFocusInElement() == true) {
			return true;
		}
		if (prevElement() == true) {
			return true;
		}
		break;
	case DirRight:
		m_bScrollColumn = true;
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

bool Ct2ListView::dialFocus(const bool bPlus, bool Silent)
{
	if (bPlus == true) {
		m_bScrollColumn = true;
		if (nextFocusInElement() == true) {
			return true;
		}
		if (nextElement() == true) {
			return true;
		}
	}
	else {
		m_bScrollColumn = true;
		if (prevFocusInElement() == true) {
			return true;
		}
		if (prevElement() == true) {
			return true;
		}
	}
	return false;
}

bool Ct2ListView::handleTouchEvent(const CtEventTouch& Touch)
{
	CtWidget* pWidget = NULL;
	int Index;
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	CtEventTouch::TouchPosition pos = Touch.getPosition();
	CtPosition Pos = CtPosition(pos.m_X, pos.m_Y);

	if (CtLayout::handleTouchEvent(Touch) == true)
		return true;

	//if (Touch.getAction() != CtEventTouch::Press)
	//	return false;

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

bool Ct2ListView::handleKeyEvent(const CtEventKey& Key)
{

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
	case CtEventKey::RepeatPress:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Up:
			return moveFocus(DirUp, false);
		case CtEventKey::KeyCode_Down:
			return moveFocus(DirDown, false);
		case CtEventKey::KeyCode_Left:
			return moveFocus(DirLeft, false);
		case CtEventKey::KeyCode_Right:
			return moveFocus(DirRight, false);
		case CtEventKey::KeyCode_MmrPlus:
			return dialFocus(false, false);
		case CtEventKey::KeyCode_MmrMinus:
			return dialFocus(true, false);

		case CtEventKey::KeyCode_DialPressUp:
			m_bDialPress = true;
			if (Key.getKeyAction() == CtEventKey::RepeatPress) {
				return dialFocus(false, false);
			}
			break;
		case CtEventKey::KeyCode_DialPressDown:
			m_bDialPress = true;
			if (Key.getKeyAction() == CtEventKey::RepeatPress) {
				return dialFocus(true, false);
			}
			break;
		default:
			break;
		}
		break;
	case CtEventKey::Release:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_DialPressUp:
		case CtEventKey::KeyCode_DialPressDown:
		case CtEventKey::KeyCode_ManualFunction:
			if (m_bDialPress == true) {
				m_bDialPress = false;
				return false;
			}
			break;
		default:
			break;
		}
	}

	/* Buttonèàóù */
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
