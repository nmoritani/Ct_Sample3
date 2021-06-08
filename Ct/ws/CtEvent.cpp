/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEvent
 */

#include "CtEvent.h"
#include "CtSysEventTranslator.h"
#include "CtWindowController.h"

CtEvent::CtEvent() : CtMsg() {
	setClassType(CtClassType_EventCommand);
}

void CtEvent::operationCmd() {
	CtWindowController::getInstance()->putEvent(*this);
}

void CtEventWindow::createWindow() {
	if (m_WindowArgs.pWindow == NULL) {
		switch (m_RequestCmdType) {
		case CtEventWindow::Change:
		case CtEventWindow::Popup:
		case CtEventWindow::Swap:
			m_WindowArgs.pWindow = CtWindowController::getInstance()->createWindow(m_WindowArgs.screen, m_WindowArgs.id, m_WindowArgs.pContents);
			break;
		default:
			break;
		}
	}
}

bool CtEventWindow::exec() {
	return CtWindowController::getInstance()->WindowEvent(*this);
}

bool CtEventWinInfoAccess::exec() {
	return CtWindowController::getInstance()->WinInfoEvent(*this);
}

bool CtEventSys::exec() {
	switch (m_Event) {
	case SYS_EVENT_KEY_STATUS_CHANGED:
		return CtSysEventTranslator::getInstance()->actionKey(m_Data.Key);
	case SYS_EVENT_TPANEL_TOUCHED:
		return CtEventTouch(CtEventTouch::Press, m_Data.TPanel.X, m_Data.TPanel.Y).exec();
	case SYS_EVENT_TPANEL_RELEASED:
		return CtEventTouch(CtEventTouch::Release, m_Data.TPanel.X, m_Data.TPanel.Y).exec();
	case SYS_EVENT_TPANEL_DRAG:
		return CtEventTouch(CtEventTouch::Move, m_Data.TPanel.X, m_Data.TPanel.Y).exec();
	case SYS_EVENT_TPANEL_SLIDE:
		return CtEventTouchSlide(m_Data.TPanel).exec();
	default:
		break;
	}
	return false;
}

bool CtEventKey::exec() {
	return CtWindowController::getInstance()->KeyEvent(*this);
}
bool CtEventTouch::exec() {
	return CtWindowController::getInstance()->TouchEvent(*this);
}

bool CtEventTouchSlide::exec() {
	return CtWindowController::getInstance()->TouchEvent(*this);
}

bool CtEventTimer::exec() {
	return CtWindowController::getInstance()->TimerEvent(*this);
}

bool CtEventParam::exec() {
	return CtWindowController::getInstance()->ParamEvent(*this);
}

bool CtEventFlash::exec() {
	return CtWindowController::getInstance()->FlashEvent(*this);
}

bool CtEventButton::exec() {
	return CtWindowController::getInstance()->ButtonEvent(*this);
}

bool CtEventWidget::exec() {
	return CtWindowController::getInstance()->WidgetEvent(*this);
}

bool CtEventFunc::exec() {
	return CtWindowController::getInstance()->FuncEvent(*this);
}
bool CtEventDrawResult::exec() {

	return CtWindowController::getInstance()->DrawResultEvent(*this);
}

bool CtEventRequest::exec() {
	return CtWindowController::getInstance()->RequestEvent(*this);
}
