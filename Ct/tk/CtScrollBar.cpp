/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Rhapsody Version: 7.5.1
*  Element:          CtButton
*/

#include "CtScrollBar.h"
#include "CtWindow.h"
#include "CtDebugPrint.h"

#define REGION_RIGHT(a) (a.x+a.width)
#define REGION_BOTTOM(a) (a.y+a.height)

CtScrollBar::CtScrollBar(CtLabel* pBase, CtLabel* pSlider, int MinSliderSize) :
	CtLayout(),
	m_pBase(pBase),
	m_pSlider(pSlider),
	m_Margin(CtMargin(0)),
	m_MinSliderSize(MinSliderSize)
{
	init();
}

CtScrollBar::CtScrollBar(CtLabel* pBase, CtLabel* pSlider, CtMargin EdgeMargin, int MinSliderSize) :
	CtLayout(),
	m_pBase(pBase),
	m_pSlider(pSlider),
	m_Margin(EdgeMargin),
	m_MinSliderSize(MinSliderSize)
{
	init();
}

CtScrollBar::~CtScrollBar()
{
}

void CtScrollBar::init()
{
	setClassType(CtClassType_ScrollBar);

	m_IsAction = false;
	m_IsHorizontal = false;
	m_NeedChangeSliderSize = false;

	m_Minimum = 0;
	m_Maximum = 10;
	m_Value = 0;

	CtLayout::addWidget(m_pBase, AlignCenter);
	CtLayout::addWidget(m_pSlider, AlignCenter);
	CtLayout::setLayout();

	updateSlider();
}

bool CtScrollBar::isMaximum()
{
	return m_Value == m_Maximum;
}

bool CtScrollBar::isMinimum()
{
	return m_Value == m_Minimum;
}

int CtScrollBar::getMaximum()
{
	return m_Maximum;
};

int CtScrollBar::getMinimum()
{
	return m_Minimum;
};

int CtScrollBar::getValue()
{
	return m_Value;
}

void CtScrollBar::setMaximum(int Maximum)
{
	if (m_Minimum >= Maximum) return;

	m_Maximum = Maximum;

	if (m_Maximum < m_Value) {
		m_Value = m_Minimum;
	}

	m_NeedChangeSliderSize = true;
	updateSlider();
}

void CtScrollBar::setMinimum(int Minimum)
{
	if (Minimum >= m_Maximum) return;

	m_Minimum = Minimum;

	if (m_Minimum > m_Value) {
		m_Value = m_Minimum;
	}

	m_NeedChangeSliderSize = true;
	updateSlider();
}

void CtScrollBar::setValue(int Value)
{
	if (m_Minimum > Value || m_Maximum < Value) return;

	m_Value = Value;

	updateSlider();
}

void CtScrollBar::updateSlider()
{
	// Maximum, Minimum, Value からスライダー位置とサイズを計算
	CtRegion base = m_pBase->getRegion();
	CtRegion slider = m_pSlider->getRegion();
	int region_cnt = m_Maximum - m_Minimum + 1;
	int slider_size_diff = 0;
	int base_length = getEffectiveBaseLength();
	int base_length_difF = 0;

	// リージョンのマージン考慮
#if 0
	base.y += m_Margin.Top;
	base.x += m_Margin.Left;
	base.height -= (m_Margin.Top + m_Margin.Bottom);
	base.width -= (m_Margin.Left + m_Margin.Right);
#endif

	// スライダーサイズ変更
	{
		CtSize base_size = m_pBase->getSize();
		CtSize slider_size = m_pSlider->getSize();

		// サイズのマージン考慮
#if 0
		base_size.height -= (m_Margin.Top + m_Margin.Bottom);
		base_size.width -= (m_Margin.Left + m_Margin.Right);
#endif

		if (m_IsHorizontal) {
			slider_size.width = base_size.width / region_cnt;/* pgr0351 */

			// 最少サイズ考慮
			if (slider_size.width < m_MinSliderSize) {
				slider_size_diff = m_MinSliderSize - slider_size.width;
				slider_size.width = m_MinSliderSize;/* pgr0351 */
			}
		}
		else {
			slider_size.height = base_size.height / region_cnt;/* pgr0351 */

			// 最少サイズ考慮
			if (slider_size.height < m_MinSliderSize) {
				slider_size_diff = m_MinSliderSize - slider_size.height;
				slider_size.height = m_MinSliderSize;/* pgr0351 */
			}
		}
		
		if(m_NeedChangeSliderSize){
			m_pSlider->setSize(slider_size);
		}
	}

	// Value値からスライダ位置を計算
	if (m_IsHorizontal) {
		slider.x = (int)(base.x + (base.width - base_length) / 2.0f + (1.0f * base_length / region_cnt) * m_Value);/* pgr0351 */

		// サイズ補正
		if (slider_size_diff) slider.x -= (int)(slider_size_diff / 2.0f);/* pgr0351 */
	}
	else {
		slider.y = (int)(base.y + (base.height - base_length) / 2.0f + (1.0f * base_length / region_cnt) * m_Value);/* pgr0351 */

		// サイズ補正
		if (slider_size_diff) slider.y -= (int)(slider_size_diff / 2.0f);/* pgr0351 */
	}

	CtDebugPrint(CtDbg, "%s(Value:%d) => [%d,%d,%d,%d]\n",
		__FUNCTION__, m_Value, slider.x, slider.y, slider.width, slider.height);

	m_pSlider->setRegion(slider);
}

void CtScrollBar::setOrientation(bool isHorizontal)
{
	m_IsHorizontal = isHorizontal;

	updateSlider();
}

bool CtScrollBar::TouchAction_Press(short _x, short _y)
{
	CtPosition p;
	p.x = _x;
	p.y = _y;

	if (m_pSlider->isContains(p) || m_pBase->isContains(p))		{
		m_IsAction = true;
	}
	else {
		m_IsAction = false;
	}

	return false;
}

void CtScrollBar::TouchAction_Release()
{
	m_IsAction = false;
}

int CtScrollBar::getValueByPos(short x, short y)
{
	int region_cnt = m_Maximum - m_Minimum + 1;
	CtRegion base_region = m_pBase->getRegion();
	int base_length = getEffectiveBaseLength();
	int i;

	// @todo base_regionのMargin考慮

	// 座標からValue値を計算
	for (i = 0; i < region_cnt - 1; i++) {
		if (m_IsHorizontal) {
			if (base_region.x + (1.0f * base_length / region_cnt) * (i + 1) > x) {
				break;
			}
		}
		else {
			if (base_region.y + (1.0f * base_length/ region_cnt) * (i + 1) > y) {
				break;
			}
		}
	}

	//if (i != m_Value) CtDebugPrint(CtDbg, "%s(%d, %d) => %d\n", __FUNCTION__, x, y, i);

	return i;
}

bool CtScrollBar::TouchAction_Slide(CtEventTouchSlide &_slide)
{
	if (!m_IsAction) {
		return false;
	}

	CtEventTouch::TouchPosition pos = _slide.getPosition();
	int new_value = getValueByPos(pos.m_X, pos.m_Y);

	// スライダ位置更新
	if (new_value != m_Value) {
		m_Value = new_value;

		updateSlider();
	}

	return true;
}

bool CtScrollBar::setRegion(const CtRegion& Region)
{
	// setLayoutでregionが決まるので
	// スライダーサイズ更新
	m_NeedChangeSliderSize = true;
	updateSlider();

	return true;
}

bool CtScrollBar::handleTouchEvent(const CtEventTouch & Event)
{
	CtEventTouch::TouchPosition pos = Event.getPosition();

	switch (Event.getAction()) {
	case CtEventTouch::Press:
		return TouchAction_Press(pos.m_X, pos.m_Y);

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

// スライダベースの有効長を算出
// 有効帳を分割数で割って、スライダ位置等に使用する
int CtScrollBar::getEffectiveBaseLength()
{
	CtRegion base = m_pBase->getRegion();
	CtRegion slider = m_pSlider->getRegion();
	int div_cnt = m_Maximum - m_Minimum + 1;	//!< ベースの分割数

	int base_length = m_IsHorizontal ? base.width : base.height;
	int slider_length = base_length / div_cnt;
	int slider_size_diff = 0;					//!< ベース長と分割数から算出したスライダーサイズと最小スライダサイズの差(最小スライダサイズ > 算出スライダサイズ)

	// スライダ最少サイズ考慮
	if (slider_length < m_MinSliderSize) {
		slider_size_diff = m_MinSliderSize - slider_length;
	}
	
	return base_length - slider_size_diff;
}

bool CtScrollBar::addWidget(CtWidget* pWidget, CtAlign Align) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, int Stretch) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, CtAlign Align, int Stretch) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, CtMargin Margin, int Stretch) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, int Stretch) { return false; }
bool CtScrollBar::addWidget(CtWidget* pWidget, CtSize Size, CtAlign Align) { return false; }
bool CtScrollBar::swapWidget(CtWidget* pWidget, int Index, CtAlign Align) { return false; }
bool CtScrollBar::swapWidget(CtWidget* pWidget, int Index, CtMargin Margin, CtAlign Align) { return false; }
bool CtScrollBar::swapWidget(CtWidget* pWidget, CtWidget* dst_pWidget, CtAlign Align) { return false; }
bool CtScrollBar::swapWidget(CtWidget* pWidget, CtWidget* dst_pWidget, CtMargin Margin, CtAlign Align) { return false; }

#if 0
void CtScrollBar::adjustSliderPos(CtRegion &slider, CtRegion &base)
{
	// マージンをベースのregionから引く
	base.y += m_Margin.Top;
	base.x += m_Margin.Left;
	base.height -= (m_Margin.Top + m_Margin.Bottom);
	base.width -= (m_Margin.Left + m_Margin.Right);

	// Minimum, Maximumを考慮してslider位置を補正


	// ベースの範囲を超えないようにslider位置を補正
	if (m_IsHorizontal) {
		if (base.x > slider.x) {
			slider.x = base.x;
		}
		else if (REGION_RIGHT(base) < REGION_RIGHT(slider)) {
			slider.x = REGION_RIGHT(base) - slider.width;
		}
	}
	else {
		if (base.y > slider.y) {
			slider.y = base.y;
		}
		else if (REGION_BOTTOM(base) < REGION_BOTTOM(slider)) {
			slider.y = REGION_BOTTOM(base) - slider.height;
		}
	}
}
#endif
