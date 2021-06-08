/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element: CtWindow
 */


#include "CtWindow.h"
#include "CtWindowMain.h"
#include "CtListView.h"
#include "CtEvent.h"
#include "CtInterface.h"
#include "CtWindowController.h"

class CtWindowMain;

void CtWindow::ctor()
{
	setClassType(CtClassType_Window);
	
	m_WindowID = WindowNone;
	m_pWindowMain = NULL;
	m_pCurrentFocus = NULL;
	m_pDefaultFocus = NULL;
	m_DialIndexMax = 0;
	m_bRoundFocus = false;

	m_ScreenSel = ScreenNone;
}

CtWindow::CtWindow()
{
	ctor();
}

CtWindow::CtWindow(const CtColor& Color) :
	CtLayout(Color)
{
	ctor();
}

CtWindow::CtWindow(const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	ctor();
}

CtWindow::CtWindow(const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	ctor();
}

CtWindow::~CtWindow()
{
}

bool CtWindow::layoutWindow(int Screen)
{
	bool bRet = false;
	
	if (m_Region[Screen].isAuto() == true) {
		CtScreenInfo Info = CtDraw::getInstance()->getScreenInfo(Screen);
		if (setRegion(CtRegion(0, 0, Info.Size.width, Info.Size.height), Screen) == true)
			bRet = true;
	}
	return bRet;
}

CtWindowMain* CtWindow::getMain() const
{
	return m_pWindowMain;
}

bool CtWindow::setVisible(bool bVisible)
{
	if (CtWidget::setVisible(bVisible) != true)
		return false;
	
	if (m_pWindowMain != NULL) {
		m_pWindowMain->setVisible(bVisible);
	}
	return true;
}

bool CtWindow::putKeyEvent(const CtEventKey& Key)
{
	if (handleKeyEvent(Key) == true)
		return true;

	return CtLayout::handleKeyEvent(Key);
}

bool CtWindow::putTouchEvent(const CtEventTouch& Touch)
{
	if (handleTouchEvent(Touch) == true)
		return true;

	return CtLayout::handleTouchEvent(Touch);
}

bool CtWindow::putParamEvent(const CtEventParam& Param)
{
	handleParamEvent(Param);

	return CtLayout::handleParamEvent(Param);
}

bool CtWindow::putButtonEvent(const CtEventButton& Button)
{
	if (handleButtonEvent(Button) == true)
		return true;
		
	return CtLayout::handleButtonEvent(Button);
}

bool CtWindow::putWidgetEvent(const CtEventWidget& Widget)
{
	return false;
}

bool CtWindow::handleTouchEvent(const CtEventTouch& Touch)
{
	bool bRet = false;
	
	if ((bRet = CtLayout::handleTouchEvent(Touch)) == true)
		return bRet;
	
	switch (Touch.getAction()) {
	case CtEventTouch::Release:
	case CtEventTouch::Move:
		if (cancelPressing() == true)
			bRet = true;
		break;
	default:
		break;
	}

	return bRet;
}

bool CtWindow::handleKeyEvent(const CtEventKey& Key)
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
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	return false;
}
	
bool CtWindow::handleTimerEvent(const CtEventTimer& Timer)
{
	return false;
}

bool CtWindow::handleFlashEvent(const CtEventFlash& Flash)
{
	return false;
}

bool CtWindow::handleParamEvent(const CtEventParam& Param)
{
	return false;
}

bool CtWindow::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	
	int State = Button.getChangeState();
	CtButton* pButton = (CtButton*)Button.getWidget();

	if (!(State & CtEventButton::Focus))
		return bRet;
	
	if (pButton->isFocused()) {
		if (m_pCurrentFocus != pButton) {
			if (m_pCurrentFocus != NULL)
				static_cast<CtButton*>(m_pCurrentFocus)->cancelFocus();
			m_pCurrentFocus = pButton;
			bRet = true;
		}
	} else {
		if (m_pCurrentFocus == pButton) {
			m_pCurrentFocus = NULL;
			bRet = true;
		}
	}
	
	return bRet;
}

bool CtWindow::handleWidgetEvent(const CtEventWidget& Widget)
{
	return false;
}

bool CtWindow::cancelPressing()
{
	CtWidget::List widget_list;
	bool bRet = false;
	
	if (getWidgets(CtLayout::Visible, &widget_list, WidgetButton, 0) == true) {
		for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
			CtButton* pButton = (CtButton*)(*Widget);
			if (pButton->isPressed() == true) {
				pButton->cancelPressed();
				bRet = true;
			}
		}
	}
	return bRet;
}

bool CtWindow::setDefaultFocus(CtWidget* pWidget)
{
	m_pDefaultFocus = pWidget;
	return true;
}

CtWidget* CtWindow::getFocusWidget()
{
	return m_pCurrentFocus;
}

bool CtWindow::setFocusWidget(CtWidget* pWidget)
{
	if (m_pCurrentFocus == pWidget)
		return false;
	
	m_pCurrentFocus = pWidget;
	return true;
}

bool CtWindow::clearFocusWidget(CtWidget* pWidget)
{
	if ((m_pCurrentFocus == NULL) || (pWidget != m_pCurrentFocus))
		return false;

	m_pCurrentFocus = NULL;
	return true;
}


bool CtWindow::initialFocus(bool bSilent)
{
	CtWidget* pFocus = NULL;
	CtLayout* pLayout = NULL;
	CtWidget::List Lists;
	CtRegion Region(0,0,10,10);

	if (m_pDefaultFocus != NULL) {
		if (m_pDefaultFocus->isFocusable() == true) {
			((CtButton*)m_pDefaultFocus)->setFocus();
		}
	}

	if (m_pCurrentFocus != NULL)	return true;

	if (getWidgets(CtLayout::Visible, &Lists, WidgetListView, 0) == true) {
		CtWidget::ListItr Itr = Lists.begin();
		if (((CtListView*)*Itr)->initialFocus(false) == true) {
			m_pCurrentFocus = ((CtListView*)*Itr)->getFocusWidget();
			return true;
		}
	}

	if (m_pCurrentFocus != NULL)	return true;

	if (getWidgets(CtLayout::Visible, &Lists, WidgetFocusable, 0) == true) {
		for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
			if (((CtButton*)*Itr)->isFocused() == true) {
				m_pCurrentFocus = (*Itr);
				return true;
			}
		}
	}

	for (int i = 0; i< m_Elements.size(); i++) {
		CtWidget* pWidget;
		if (m_Elements[i] == NULL)						continue;
		if ((pWidget = m_Elements[i]->pWidget) == NULL)	continue;

		if (pWidget->isLayout() == true) {
			if ((pFocus = ((CtLayout*)(pWidget))->getNeary(Region, WidgetFocusable, DirDown)) != NULL) {
				((CtButton*)pFocus)->setFocus();
				break;
			}
		}
	}

	if (m_pCurrentFocus != NULL)	return true;
	
	return false;
}

bool CtWindow::setDialIndex()
{
	CtWidget::List Lists;
	int index = 0;
	bool user = false;
	
	if (getWidgets(CtLayout::Registered, &Lists, WidgetButton, 0) == true) {
		for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
			if (((index = ((CtButton*)*Itr)->getDialIndex()) != 0) && index > getDialIndexMax()) {
				setDialIndexMax(index);
				user = true;
			}
		}
		if (user == true) {
			return false;
		}
	}

	index = 0;
	Lists.clear();
	if (getWidgets(CtLayout::Registered, &Lists, WidgetButton, 0) == true) {
		for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
			((CtButton*)*Itr)->setDialIndex(index++);
		}
		return true;
	}

	return false;
}

bool CtWindow::moveFocus(const CtDirection Dir, bool silent)
{
	CtWidget::List Lists;
	CtListView *pListView = NULL;
	CtWidget* pFocus = NULL;
	bool bRet = false;

	if (m_pCurrentFocus == NULL) {
		if (getWidgets(CtLayout::Visible, &Lists, WidgetListView, 0) == true) {
			for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
				if ((pListView = (CtListView*)(*Itr)) != NULL) {
					if (pListView->moveFocus(Dir, silent) == true)
						bRet = true;
				}
			}
		}
		return bRet;;
	}
	
	// リストの場合は、まかせる
	if ((pListView = m_pCurrentFocus->getListView()) != NULL) {
		bRet = pListView->moveFocus(Dir, silent);
		return bRet;
	}
#if 0	
	// 現在のフォーカスボタンが光ってなかったら光らせて抜ける
	if ((m_pCurrentFocus->isButton() == true) && (((CtButton*)m_pCurrentFocus)->isFocusSilent() == true)) {
		((CtButton*)m_pCurrentFocus)->setFocus();
		return true;
	}
#endif	
	CtWidget *pParent = m_pCurrentFocus->getParent();
	CtRegion cRegion = m_pCurrentFocus->getRegion();

	if (pParent == NULL)
		return false;
	
	while (pParent != this) {
		if ((pFocus = ((CtLayout*)pParent)->getNeary(cRegion, WidgetFocusable, Dir)) != NULL) {
			((CtButton*)pFocus)->setFocus();
			return true;
		}
		pParent = pParent->getParent();
	}
	if (m_bRoundFocus) {
		switch (Dir) {
		case DirUp:
			cRegion.y = 640;
			cRegion.height = 1;
			break;
		case DirDown:
			cRegion.y = 0;
			cRegion.height = 1;
			break;
		case DirLeft:
			cRegion.x = 939;
			cRegion.width = 1;
			break;
		case DirRight:
			cRegion.x = 0;
			cRegion.width = 1;
			break;
		default:
			break;
		}
		if ((pFocus = ((CtLayout*)pParent)->getNeary(cRegion, WidgetFocusable, Dir)) != NULL) {
			((CtButton*)pFocus)->setFocus();
			return true;
		}
	}
	return false;
}

bool CtWindow::dialFocus(const bool bPlus, bool silent)
{	
	CtWidget::List Lists;
	CtListView *pListView = NULL;
	int index = 0, i = 0;
	bool bRet = false;

	if (m_pCurrentFocus == NULL) {
		if (getWidgets(CtLayout::Visible, &Lists, WidgetListView, 0) == true) {
			for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
				if ((pListView = (CtListView*)(*Itr)) != NULL) {
					if (pListView->dialFocus(bPlus, silent) == true)
						bRet = true;
				}
			}
		}
		return bRet;
	}

	// リストの場合は、まかせる
	if ((pListView = m_pCurrentFocus->getListView()) != NULL) {
		bRet = pListView->dialFocus(bPlus, silent);
		return bRet;
	}
#if 0
	// 現在のフォーカスボタンが光ってなかったら光らせて抜ける
	if ((m_pCurrentFocus->isButton() == true) && (((CtButton*)m_pCurrentFocus)->isFocusSilent() == true)) {
		((CtButton*)m_pCurrentFocus)->setFocus();
		return true;
	}
#endif	
	index = ((CtButton*)m_pCurrentFocus)->getDialIndex();
	i = index;

	while (1) {
		if (bPlus == true) {
			if (m_DialIndexMax >= index +1) 	index++;
			else if (m_bRoundFocus == true)		index = 0;
			else	return false;
		} else {
			if (0 <= index -1) 					index--;
			else if (m_bRoundFocus == true)		index = m_DialIndexMax;
			else	return false;
		}
		
		if (getWidgets(CtLayout::Visible, &Lists, WidgetFocusable, 0) == true) {
			for (CtWidget::ListItr Itr = Lists.begin(); Itr != Lists.end(); ++Itr) {
				CtButton *pButton = (CtButton*)(*Itr);
				if (index == pButton->getDialIndex()) {
					if (pButton->isFocusable()) {	
						pButton->setFocus();
						return true;
					} else {
						break;
					}
				}
			}
		}
		else {
			return false;
		}
	}
	
	return false;
}


