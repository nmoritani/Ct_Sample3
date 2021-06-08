/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Rhapsody Version: 7.5.1
*  Element:          CtButton
*/

#include "CtSlideLabel.h"
#include "CtWindow.h"


CtSlideLabel::CtSlideLabel()
{
	init();
}

CtSlideLabel::CtSlideLabel(const GDI_IMAGE_ID ImageID) :
	CtLabel(ImageID)
{
	init();
}

CtSlideLabel::CtSlideLabel(const GDI_STRING_ID StringID, const CtFontSet & FontSet) :
	CtLabel(StringID, FontSet)
{
	init();
}

CtSlideLabel::CtSlideLabel(const char * ucStr, const CtFontSet & FontSet) :
	CtLabel(ucStr, FontSet)
{
	init();
}

CtSlideLabel::CtSlideLabel(const GDI_STRING_ID StringID) :
	CtLabel(StringID)
{
	init();
}

CtSlideLabel::CtSlideLabel(const char * ucStr) :
	CtLabel(ucStr)
{
	init();
}

CtSlideLabel::CtSlideLabel(const CtSize & Size, const GDI_IMAGE_ID ImageID) :
	CtLabel(Size, ImageID)
{
	init();
}

CtSlideLabel::CtSlideLabel(const CtSize & Size, const GDI_STRING_ID StringID, const CtFontSet & FontSet) :
	CtLabel(Size, StringID, FontSet)
{
	init();
}

CtSlideLabel::CtSlideLabel(const CtSize & Size, const GDI_STRING_ID StringID) :
	CtLabel(Size, StringID)
{
	init();
}

CtSlideLabel::CtSlideLabel(const CtSize & Size, const char * ucStr, const CtFontSet & FontSet) :
	CtLabel(Size, ucStr, FontSet)
{
	init();
}

CtSlideLabel::CtSlideLabel(const CtSize & Size, const char * ucStr) :
	CtLabel(Size, ucStr)
{
	init();
}

void CtSlideLabel::init()
{
	setClassType(CtClassType_SlideLabel);
	m_IsAction = false;
}

void CtSlideLabel::TouchAction_Press(long _x, long _y)
{
	if (((m_Region[0].x < _x) && (_x < (m_Region[0].x + m_Region[0].width)))
		&& ((m_Region[0].y < _y) && (_y < (m_Region[0].y + m_Region[0].height)))) {
		m_IsAction = true;
	}
}

void CtSlideLabel::TouchAction_Release()
{
	m_IsAction = false;
}

bool CtSlideLabel::TouchAction_Slide(CtEventTouchSlide &_slide)
{
	if (!m_IsAction) {
		return false;
	}

	CtEventTouch::TouchPosition pos = _slide.getPosition();

	if ((pos.m_X == m_Region[0].x) && (pos.m_Y == m_Region[0].y)) {
		return false;
	}

	//À•W‚ðXV
	CtWidget::setPos(pos.m_X - (short)(m_Region[0].width * 0.5f), pos.m_Y - (short)(m_Region[0].height * 0.5f), 0);	/* pgr0398 */
	CtWidget::setPos(pos.m_X - (short)(m_Region[1].width * 0.5f), pos.m_Y - (short)(m_Region[1].height * 0.5f), 1);	/* pgr0398 */
	return true;
}


bool CtSlideLabel::handleTouchEvent(const CtEventTouch & Event)
{
	CtEventTouch::TouchPosition pos = Event.getPosition();

	switch (Event.getAction()) {
	case CtEventTouch::Press:
		TouchAction_Press(pos.m_X, pos.m_Y);
		return false;

	case CtEventTouch::Release:
		TouchAction_Release();
		return false;

	case CtEventTouch::Move:
		return TouchAction_Slide((CtEventTouchSlide&)Event);

	default:
		break;
	}
	return false;
}

