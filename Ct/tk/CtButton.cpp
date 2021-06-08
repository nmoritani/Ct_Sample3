/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtButton
 */

#include "CtDebugPrint.h"
#include "CtButton.h"
#include "CtStyle.h"
#include "CtEventInterface.h"

const unsigned long CtButton::LongPressTime_Default(1000);
const unsigned long CtButton::RepeatTime_Default(250);

void CtButton::ctor(const CtSize& Size, CtButton::Shape Shape)
{
	setClassType(CtClassType_Button);

	m_State = StateNormal;

	m_TimLvThreshold = LongPressTime_Default;
	m_LongPressTime = LongPressTime_Default;
	m_RepeatTime = RepeatTime_Default;
	m_IntervalCount = 0;

	m_bFocusable = true;
	m_DialIndex = 0;
	m_Shape = Shape;
	m_TimLv = CtEventButton::Level_Default;
	setProperty();
	if (Size.width == -1 && Size.height == -1) {
		setSize(CtStyle::getProperty().Button.Size);
	}
	setEventFilter((CtEventFilter)(EventKey + EventTouch));
	setTrans(true);
}

CtButton::CtButton()
{
	ctor(StyleSize, None);
}


CtButton::CtButton(CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
}

CtButton::CtButton(const CtSize& Size, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
}

CtButton::CtButton(const CtRegion& Region, CtButton::Shape Shape) :
	CtStackLabel(Region)
{
	ctor(CtSize(Region.width, Region.height), Shape);
}

CtButton::CtButton(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(ImageID, fillColor, edgeColor), 0);
}

CtButton::CtButton(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(ImageID, fillColor, CtColor::NoColor), 0);
}

CtButton::CtButton(const GDI_IMAGE_ID ImageID, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(ImageID, CtColor::NoColor, CtColor::NoColor), 0);
}

CtButton::CtButton(const GDI_HANDLER DrawableID, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(DrawableID), 0);
}

CtButton::CtButton(const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(StringID, FontSet), 0);
}

CtButton::CtButton(const GDI_STRING_ID StringID, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(StringID, CtStyle::getProperty().FontSet), 0);
}

CtButton::CtButton(const char *pStr, const CtFontSet& FontSet, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(pStr, FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(const char *pStr, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(pStr, CtStyle::getProperty().FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(const unsigned short *pStr, const CtFontSet& FontSet, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(pStr, FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(const unsigned short *pStr, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	addLabel(new CtLabel(pStr, CtStyle::getProperty().FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(CtLabel *pLabel, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	if ((pLabel != NULL) && (pLabel->isLabel() == true)) {
		addLabel(pLabel, 0);
	}
}

CtButton::CtButton(CtLayout *pLayout, CtButton::Shape Shape)
{
	ctor(StyleSize, Shape);
	if ((pLayout != NULL) && (pLayout->isLayout() == true)) {
		addLabel(pLayout, 0);
	}
}

CtButton::CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(ImageID, fillColor, edgeColor), 0);
}

CtButton::CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(ImageID, fillColor, CtColor::NoColor), 0);
}

CtButton::CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(ImageID, CtColor::NoColor, CtColor::NoColor), 0);
}

CtButton::CtButton(const CtSize& Size, const GDI_HANDLER DrawableID, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(DrawableID), 0);
}

CtButton::CtButton(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(StringID, FontSet), 0);
}

CtButton::CtButton(const CtSize& Size, const GDI_STRING_ID StringID, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(StringID), 0);
}

CtButton::CtButton(const CtSize& Size, const char *pStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(pStr, FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(const CtSize& Size, const char *pStr, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(pStr), 0);	/* pgr0541 */
}

CtButton::CtButton(const CtSize& Size, const unsigned short *pStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(pStr, FontSet), 0);	/* pgr0541 */
}

CtButton::CtButton(const CtSize& Size, const unsigned short *pStr, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(new CtLabel(pStr), 0);	/* pgr0541 */
}

CtButton::CtButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(pLabel, 0);
}

CtButton::CtButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape) :
	CtStackLabel(Size)
{
	ctor(Size, Shape);
	addLabel(pLayout, 0);
}


CtButton::~CtButton()
{
	CtWindow* pWin = NULL;

	if (isFocused() == true) {
		pWin = getWindow();
		if (pWin != NULL) pWin->clearFocusWidget(this);
	}

}

bool CtButton::setLayout(int Screen)
{
	bool bRet = false;

	if (setButtonShape(m_Shape) == true)
		bRet = true;

	if (CtStackLabel::setLayout(Screen) == true)
		bRet = true;

	return bRet;
}

bool CtButton::setButtonShape(CtButton::Shape Shape, short Width)
{
	bool bRet = false;
	bool isRegion = false;
	CtDrawType DrawType;

	m_Shape = Shape;
	if (Width > 0)
		BaseStrokeWidth = Width;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (m_Region[i].isValid() == true)
			isRegion = true;
	}

	if (isRegion != true)
		return bRet;

	if (m_pDrawInfo != NULL)
		DrawType = m_pDrawInfo->getDrawType();
	else
		DrawType = DrawType_None;

	switch (Shape) {
	case RoundRect:
		if (DrawType != DrawType_RoundRect) {
			if (setRoundRect(BaseArcWidth, BaseArcWidth, BaseColor, BaseStrokeWidth, StrokeColor) == true)
				bRet = true;
		}
		break;
	case Rect:
		if (DrawType != DrawType_Rect) {
			if (setRect(BaseColor, BaseStrokeWidth, StrokeColor) == true)
				bRet = true;
		}
		break;
	case Ellipse:
		if (DrawType != DrawType_Ellipse) {
			if (setEllipse(BaseColor, BaseStrokeWidth, StrokeColor) == true)
				bRet = true;
		}
		break;
	case Line:
		if (DrawType != DrawType_Line) {
			if (setLine(UnderLine, BaseStrokeWidth, StrokeColor) == true)
				bRet = true;
		}
		break;
	case None:
		if (DrawType != DrawType_Fill) {
			if (setFill(BaseColor) == true)
				bRet = true;
		}
		break;
	default:
		break;
	}

	if (m_pDrawInfo != NULL)
		m_pDrawInfo->setTrans(isTrans());

	switch (m_State) {
	case StateNormal:
	case StateSilentFocused:
		if (styleNormal() == true)
			bRet = true;
		break;
	case StateFocused:
		if (styleFocused() == true)
			bRet = true;
		break;
	case StatePressed:
		if (stylePressed() == true)
			bRet = true;
		break;
	case StateInvalid:
		if (styleInvalid() == true)
			bRet = true;
		break;
	default:
		break;
	}

	return bRet;
}

bool CtButton::setTop(CtLabel* pLabel, CtMargin Margin, CtAlign Align)
{
	bool bRet = false;

	if (pLabel == NULL)
		return bRet;

	bRet = addLabel(pLabel, Margin, Align, 0);

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}

bool CtButton::setTop(CtLabel* pLabel, CtAlign Align)
{
	return setTop(pLabel, DefaultMargin, Align);
}

bool CtButton::setTop(CtLayout* pLayout, CtMargin Margin, CtAlign Align)
{
	bool bRet = false;

	if (pLayout == NULL)
		return bRet;

	bRet = addLabel(pLayout, Margin, Align, 0);

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}

bool CtButton::setTop(CtLayout* pLayout, CtAlign Align)
{
	return setTop(pLayout, DefaultMargin, Align);
}

CtWidget* CtButton::getTop()
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if ((pElements == NULL) || (pElements->empty()))
		return NULL;

	return (*pElements)[0]->pWidget;
}


bool CtButton::setTopColor(const CtColor& fillColor)
{
	CtWidget* pWidget;

	if ((pWidget = getTop()) == NULL)
		return false;

	if (pWidget->isLabel() == true) {
		return pWidget->setColor(fillColor);

	}
	else if (pWidget->isLayout() == true) {
		return static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor);
	}
	return false;
}

bool CtButton::setTopColor(const CtColor& fillColor, const CtColor& strokeColor)
{
	CtWidget* pWidget = NULL;

	if ((pWidget = getTop()) == NULL)
		return false;

	if (pWidget->isLabel() == true) {
		return pWidget->setColor(fillColor, strokeColor);

	}
	else if (pWidget->isLayout() == true) {
		return static_cast<CtLayout*>(pWidget)->setElementsColor(fillColor, strokeColor);
	}
	return false;
}

bool CtButton::setBaseColor(const CtColor& fillColor)
{
	if (m_pDrawInfo == NULL)
		return false;

	return m_pDrawInfo->setColor(fillColor);
}

bool CtButton::setBaseColor(const CtColor& fillColor, const CtColor& strokeColor)
{
	if (m_pDrawInfo == NULL)
		return false;

	return m_pDrawInfo->setColor(fillColor, strokeColor);
}

bool CtButton::setColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	bool bRet = false;

	if (m_pDrawInfo == NULL)
		return bRet;

	if (setBaseColor(Base, Stroke) == true)
		bRet = true;
	if (setTopColor(Label, LabelStroke) == true)
		bRet = true;

	return bRet;
}

bool CtButton::setStroke(short width)
{
	if (m_pDrawInfo == NULL)
		return false;

	switch (m_pDrawInfo->getDrawType()) {
	case DrawType_Line:
		return static_cast<CtLine*>(m_pDrawInfo)->setStrokeWidth(width);
	case DrawType_Rect:
		return static_cast<CtRect*>(m_pDrawInfo)->setStrokeWidth(width);
	case DrawType_RoundRect:
		return static_cast<CtRoundRect*>(m_pDrawInfo)->setStrokeWidth(width);
	case DrawType_Ellipse:
		return static_cast<CtEllipse*>(m_pDrawInfo)->setStrokeWidth(width);
	default:
		break;
	}
	return false;
}

bool CtButton::styleNormal()
{
	return setColors(BaseColor, StrokeColor, LabelColor);
}

bool CtButton::styleFocused()
{
	return setColors(FocusedBaseColor, FocusedStrokeColor, FocusedLabelColor);
}

bool CtButton::stylePressed()
{
	return setColors(PressedBaseColor, PressedStrokeColor, PressedLabelColor);
}

bool CtButton::styleInvalid()
{
	return setColors(InvalidBaseColor, InvalidStrokeColor, InvalidLabelColor);
}


// ボタンの見た目を変える
// 状態変化イベントを発行する
bool CtButton::setState(State _state)
{
	bool bRet = false;

	if (m_State == _state)
		return bRet;

	switch (_state) {
	case StateNormal:
		styleNormal();
		m_IntervalCount = 0;
		CtTimer::getInstance()->stopTimer(this);
		bRet = true;
		break;

	case StateSilentFocused:
		styleNormal();
		m_IntervalCount = 0;
		CtTimer::getInstance()->stopTimer(this);
		bRet = true;
		break;

	case StateFocused:
		styleFocused();
		m_IntervalCount = 0;
		CtTimer::getInstance()->stopTimer(this);
		bRet = true;
		break;

	case StatePressed:
		stylePressed();
		m_IntervalCount = 0;
		CtTimer::getInstance()->setAlarm(CT_BUTTON_LONG_TIMER_ID, m_LongPressTime, this);
		bRet = true;
		break;

	case StateInvalid:
		styleInvalid();
		m_IntervalCount = 0;
		CtTimer::getInstance()->stopTimer(this);
		bRet = true;
		break;

	default:
		return bRet;
	}
	m_State = _state;

	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}

	return bRet;
}

bool CtButton::sendStateEvent(CtEventButton::ChangeState State)
{
	CtEventInterface::requestButtonCmd(this, getMain(), State);
	return true;
}

bool CtButton::sendPressEvent(CtEventButton::PressType Type, CtEventButton::ButtonTimerLevel timLv)
{
	CtEventInterface::requestButtonCmd(this, getMain(), Type, timLv);

	return true;
}


bool CtButton::isFocused() const
{
	switch (m_State) {
	case StateSilentFocused:
	case StateFocused:
	case StatePressed:
		return true;
	default:
		break;
	}

	return false;
}

bool CtButton::setFocus(bool bSilent)
{
	bool bRet = false;

	if (isFocusable() == false)
		return bRet;

	if (bSilent == false)
		bRet = setState(StateFocused);
	else
		bRet = setState(StateSilentFocused);

	if (bRet == true) {
		CtRegion r = m_Region[0];
		sendStateEvent(CtEventButton::Focus);
		setInvalidate();
	}

	return bRet;
}

bool CtButton::cancelFocus()
{
	bool bRet = false;

	if (isFocused() != true)
		return false;

	bRet = setState(StateNormal);

	if (bRet == true) {
		CtRegion r = m_Region[0];
		sendStateEvent(CtEventButton::Focus);
		setInvalidate();
	}

	return  bRet;
}

bool CtButton::isPressed() const
{
	if (m_State == StatePressed)
		return true;

	return false;
}

bool CtButton::setPressed()
{
	bool bRet = false;

	switch (m_State) {
	case StateInvalid:
	case StatePressed:
		return bRet;
	case StateFocused:
	case StateNormal:
		bRet = setState(StatePressed);
		break;
	default:
		return bRet;
	}

	if ((bRet == true) && (isFocusable() == true))
		sendStateEvent(CtEventButton::Focus);

	return bRet;
}

bool CtButton::cancelPressed()
{
	bool bRet = false;

	if (m_State == StatePressed) {
		if (isFocusable() == true)
			bRet = setState(StateFocused);
		else
			bRet = setState(StateNormal);
	}

	if ((bRet == true) && (isFocusable() == true))
		sendStateEvent(CtEventButton::Focus);

	return bRet;
}

bool CtButton::isInvalid() const
{
	if (m_State == StateInvalid)
		return true;

	return false;
}

bool CtButton::setInvalid(bool bInvalid)
{
	bool bRet = false;

	if (bInvalid == true) {
		if (isInvalid() != true) {
			bRet = setState(StateInvalid);
		}
	}
	else {
		if (isInvalid() == true) {
			bRet = setState(StateNormal);
		}
	}

	if (bRet == true)
		sendStateEvent(CtEventButton::Valid);

	return bRet;
}

bool CtButton::setVisible(bool bVisible)
{
	bool bRet = false;

	if ((bRet = CtWidget::setVisible(bVisible)) == true) {
		sendStateEvent(CtEventButton::Visible);
	}

	return bRet;
}

bool CtButton::handleTouchEvent(const CtEventTouch& Touch)
{
	bool bRet = false;
	CtEventTouch::TouchPosition pos = Touch.getPosition();
	CtPosition Pos = CtPosition(pos.m_X, pos.m_Y);

	if ((isInvalid() == true) || (isVisible() != true))
		return false;

	if (isContains(Pos) != true)
		return false;


	switch (Touch.getAction()) {
	case CtEventTouch::Press:
		if (setPressed() == true) {
			onPress(CtEventButton::ShortPress);
		}
		bRet = true;
		break;

	case CtEventTouch::Release:
		if (cancelPressed() == true) {
			onRelease();
		}
		bRet = true;
		break;

	case CtEventTouch::Move:
		setPressed();
		bRet = true;
		break;

	case CtEventTouch::Slide:
	default:
		break;
	}
	return bRet;
}

bool CtButton::handleKeyEvent(const CtEventKey& Key)
{
	bool bRet = false;

	if (isFocused() != true) return false;
	if (isInvalid() == true) return false;

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		//センターキーとクルポン押し込みキー
		if ((CtEventKey::KeyCode_Enter != Key.getKeyCode()) &&
			(CtEventKey::KeyCode_ManualFunction != Key.getKeyCode())) {
			return false;
		}
		if (setPressed() == true) {
			onPress(CtEventButton::ShortPress);
		}
		bRet = true;
		break;

	case CtEventKey::Release:
		//センターキーとクルポン押し込みキー
		if ((CtEventKey::KeyCode_Enter != Key.getKeyCode()) &&
			(CtEventKey::KeyCode_ManualFunction != Key.getKeyCode())) {
			return bRet;
		}
		if (cancelPressed() == true) {
			onRelease();
		}
		bRet = true;
		break;

	case CtEventKey::LongPress:
		//センターキーとクルポン押し込みキー
		if ((CtEventKey::KeyCode_Enter != Key.getKeyCode()) &&
			(CtEventKey::KeyCode_ManualFunction != Key.getKeyCode())) {
			return bRet;
		}
		if (setPressed() == true) {
			onPress(CtEventButton::LongPress);
		}
		bRet = true;
		break;

	case CtEventKey::RepeatPress:
		if ((CtEventKey::KeyCode_Enter != Key.getKeyCode()) &&
			(CtEventKey::KeyCode_ManualFunction != Key.getKeyCode())) {
			return bRet;
		}
		if (setPressed() == true) {
			onPress(CtEventButton::RepeatPress);
		}
		bRet = true;
		break;

	default:
		return bRet;
	}
	return bRet;
}

bool CtButton::handleTimerEvent(const CtEventTimer& Timer)
{
	bool bRet = false;

	if (isPressed() == false)
		return bRet;

	if (Timer.getTimeUid() == CT_BUTTON_LONG_TIMER_ID) {
		m_TimLv = (CtEventButton::ButtonTimerLevel)(m_TimLv + 1);
		onPress(CtEventButton::LongPress, m_TimLv);
		CtTimer::getInstance()->startCyclic(CT_BUTTON_REPEAT_TIMER_ID, m_RepeatTime, this);
		bRet = true;
	}
	else if (Timer.getTimeUid() == CT_BUTTON_REPEAT_TIMER_ID) {
		m_IntervalCount++;
		if ((m_IntervalCount * m_RepeatTime) / m_TimLvThreshold) {
			if (m_TimLv < CtEventButton::Level_Max) {
				m_TimLv = (CtEventButton::ButtonTimerLevel)(m_TimLv + 1);
				m_IntervalCount = 0;
			}
		}
		onPress(CtEventButton::RepeatPress, m_TimLv);
		bRet = true;
	}

	return bRet;
}

bool CtButton::onPress(const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv)
{
	sendPressEvent(Type, TimLv);
	return true;
}

bool CtButton::onRelease()
{
	m_TimLv = CtEventButton::Level_Default;
	sendPressEvent(CtEventButton::Release, m_TimLv);
	return true;
}

bool CtButton::setDialIndex(int Index)
{
	CtWindow *pWindow = NULL;

	m_DialIndex = Index;

	if ((pWindow = getWindow()) != NULL) {
		if (pWindow->getDialIndexMax() < Index) {
			pWindow->setDialIndexMax(Index);
		}
	}
	return true;
}

void CtButton::setProperty()
{
	const CtStyle::CtProperty& prop = CtStyle::getProperty();

	this->BaseStrokeWidth = prop.Button.StrokeWidth;/* pgr0351 */
	this->BaseArcWidth = prop.Button.ArcWidth;/* pgr0351 */

	this->BaseColor = prop.Button.Normal.Base;
	this->StrokeColor = prop.Button.Normal.Stroke;
	this->LabelColor = prop.Button.Normal.Label;

	this->FocusedBaseColor = prop.Button.Focused.Base;
	this->FocusedStrokeColor = prop.Button.Selected.Stroke;
	this->FocusedLabelColor = prop.Button.Focused.Label;

	this->PressedBaseColor = prop.Button.Selected.Base;
	this->PressedStrokeColor = prop.Button.Selected.Stroke;
	this->PressedLabelColor = prop.Button.Selected.Label;

	this->InvalidBaseColor = prop.Button.Invalid.Base;
	this->InvalidStrokeColor = prop.Button.Invalid.Stroke;
	this->InvalidLabelColor = prop.Button.Invalid.Label;
}

bool CtButton::setImage(const GDI_IMAGE_ID ImageID)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setImage(ImageID);
}

bool CtButton::setImage(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setImage(ImageID, fillColor, edgeColor);
}

bool CtButton::setImage(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setImage(Width, Height, BufWidth, BufHeight, Data, Type);
}

bool CtButton::setImage(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setImage(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
}

GDI_IMAGE_ID CtButton::getImageID()
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return IMAGE_ID_INVALID;

	return static_cast<CtLabel*>(pWidget)->getImageID();
}

bool CtButton::setDrawable(const GDI_HANDLER DrawableID)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setDrawable(DrawableID);
}

GDI_HANDLER CtButton::getDrawable()
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return GDI_INVALID_ID;

	return static_cast<CtLabel*>(pWidget)->getDrawable();
}

bool CtButton::setStringID(const GDI_STRING_ID StringID, const CtFontSet& FontSet)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setStringID(StringID, FontSet);
}

bool CtButton::setStringID(const GDI_STRING_ID StringID)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setStringID(StringID);
}

bool CtButton::setText(const char *ucStr)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setText(ucStr);
}

bool CtButton::setText(const char *ucStr, const CtFontSet& FontSet)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setText(ucStr, FontSet);
}

bool CtButton::setText(const unsigned short *ucStr)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setText(ucStr);
}

bool CtButton::setText(const unsigned short *ucStr, const CtFontSet& FontSet)
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->setText(ucStr, FontSet);
}

unsigned short* CtButton::getText()
{
	CtWidget* pWidget;

	if (((pWidget = getTop()) == NULL) || (pWidget->isLabel() != true))	return false;

	return static_cast<CtLabel*>(pWidget)->getText();
}

bool CtButton::setLine(const CtLine& _Line)
{
	return CtLabel::setLine(_Line);
}

bool CtButton::setLine(CtLineStyle Style, short lineWidth, const CtColor& lineColor)
{
	return CtLabel::setLine(Style, lineWidth, lineColor);
}

bool CtButton::setFill(const CtFill& _Fill)
{
	return CtLabel::setFill(_Fill);
}

bool CtButton::setRect(const CtRect& _Rect)
{
	return CtLabel::setRect(_Rect);
}

bool CtButton::setRect(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	return CtLabel::setRect(fillColor, edgeWidth, edgeColor);
}

bool CtButton::setRoundRect(const CtRoundRect& _RoundRect)
{
	return CtLabel::setRoundRect(_RoundRect);
}

bool CtButton::setRoundRect(short ArcWidth, short ArcHeight, const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	return CtLabel::setRoundRect(ArcWidth, ArcHeight, fillColor, edgeWidth, edgeColor);
}

bool CtButton::setEllipse(const CtEllipse& _Ellipse)
{
	return CtLabel::setEllipse(_Ellipse);
}

bool CtButton::setEllipse(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	return CtLabel::setEllipse(fillColor, edgeWidth, edgeColor);
}
bool CtButton::setButtonStyleChange() {
	const CtStyle::CtProperty& prop = CtStyle::getProperty();
	bool bRet = false;
	if (setButtonColors(prop.Button.Normal.Base, prop.Button.Normal.Stroke, prop.Button.Normal.Label)) bRet = true;
	if (setFocusedButtonColors(prop.Button.Selected.Base, prop.Button.Focused.Stroke, prop.Button.Selected.Label)) bRet = true;
	if (setPressedButtonColors(prop.Button.Selected.Base, prop.Button.Normal.Stroke, prop.Button.Selected.Label)) bRet = true;
	return bRet;
}
bool CtButton::setButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->BaseColor = Base;
	this->StrokeColor = Stroke;
	this->LabelColor = Label;
	return true;
}
bool CtButton::setFocusedButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->FocusedBaseColor = Base;
	this->FocusedStrokeColor = Stroke;
	this->FocusedLabelColor = Label;
	return true;
}
bool CtButton::setPressedButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->PressedBaseColor = Base;
	this->PressedStrokeColor = Stroke;
	this->PressedLabelColor = Label;
	return true;
}
bool CtButton::setInvalidButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->InvalidBaseColor = Base;
	this->InvalidStrokeColor = Stroke;
	this->InvalidLabelColor = Label;
	return true;
}

bool CtButton::setRepeatTime(unsigned long timRepeat) {
	if (timRepeat <= 0) return false;
	m_RepeatTime = timRepeat;
	if (CtTimer::getInstance()->isActTimerId(CT_BUTTON_REPEAT_TIMER_ID, this) == true) {
		CtTimer::getInstance()->startCyclic(CT_BUTTON_REPEAT_TIMER_ID, m_RepeatTime, this);
	}
	return true;
}

bool CtButton::setLongPressTime(unsigned long timLong) {
	if (timLong <= 0) return false;
	m_LongPressTime = timLong;

	return true;
}

bool CtButton::setTimLvThresholdTime(unsigned long timLvThreshold) {
	if (timLvThreshold <= 0) return false;
	m_TimLvThreshold = timLvThreshold;
	return true;
}

bool CtButton::resetRepeatTime() {
	if (RepeatTime_Default <= 0) return false;
	m_RepeatTime = RepeatTime_Default;
	if (CtTimer::getInstance()->isActTimerId(CT_BUTTON_REPEAT_TIMER_ID, this) == true) {
		CtTimer::getInstance()->startCyclic(CT_BUTTON_REPEAT_TIMER_ID, m_RepeatTime, this);
	}
	return true;
}

bool CtButton::resetLongPressTime() {
	if (LongPressTime_Default <= 0) return false;
	m_LongPressTime = LongPressTime_Default;
	return true;
}
bool CtButton::resetTimLvThresholdTime() {
	if (LongPressTime_Default <= 0) return false;
	m_TimLvThreshold = LongPressTime_Default;
	return true;

}
