/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtWidget
 */

#include "CtWidget.h"
#include "CtColor.h"
#include "CtLabel.h"

#include "CtWindow.h"
#include "CtDrawCache.h"

void CtWidget::ctor()
{
	setClassType(CtClassType_Widget);

	m_WidgetID = 0;
	m_pParent = NULL;
	m_ScreenSel = ScreenAll;
	m_bVisible = true;
	m_Invalidate = ScreenNone;
	m_bTrans = true;
	m_Size = AutoSize;
	m_FlashFrequency = CtEventFlash::Freq_Invalid;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_Region[i] = NoRegion;
		m_ClearRegion[i] = NoRegion;
	}
}

CtWidget::CtWidget()
{
	ctor();
}

CtWidget::CtWidget(const CtSize& Size)
{
	ctor();
	setSize(Size);
}

CtWidget::CtWidget(const CtRegion& Region)
{
	ctor();
	setRegion(Region);
}

bool CtWidget::handleTouchEvent(const CtEventTouch& Touch)
{
	return false;
}

bool CtWidget::handleKeyEvent(const CtEventKey& Key)
{
	return false;
}

bool CtWidget::handleParamEvent(const CtEventParam& Param)
{
	return false;
}

bool CtWidget::handleTimerEvent(const CtEventTimer& Timer)
{
	return false;
}

bool CtWidget::handleFlashEvent(const CtEventFlash& Flash)
{
	if (Flash.getFrequency() != m_FlashFrequency)
		return false;
	
#if 0	// Drawable化して速くなるかな！？
	GDI_HANDLER drawable_id;
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo()) == NULL)
		return false;
	
	if ((m_Region[0].isValid() == true) && (pDrawInfo->haveDrawable() != true)) {
		if ((drawable_id = CtDraw::getInstance()->convertDrawable(this, Format_Window)) != GDI_INVALID_ID) {
			pDrawInfo->setDrawable(drawable_id, true);
		}
	}
#endif

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (m_ScreenSel & toSelScreen(i))
			setInvalidate(i);
	}
	return true;
}

bool CtWidget::handleButtonEvent(const CtEventButton& Button)
{
	return false;
}

CtWidget::~CtWidget()
{
}

CtWidget::Element::Element() :
	pWidget(NULL),
	Margin(DefaultMargin),
	Align(DefaultAlign),
	Index(-1)
{
	setClassType(CtClassType_Element);
}

CtWidget::Element::Element(CtWidget* _pWidget, CtMargin _Margin, CtAlign _Align) :
	pWidget(_pWidget),
	Margin(_Margin),
	Align(_Align),
	Index(-1)
{
	setClassType(CtClassType_Element);
}

CtWidget::Element::~Element()
{
	if (pWidget != NULL)
		delete pWidget;
}

bool CtWidget::Element::set(CtWidget* _pWidget, CtMargin _Margin, CtAlign _Align)
{
	bool bRet = false;

	if (pWidget != _pWidget) {
		pWidget = _pWidget;
		bRet = true;
	}
	if (Margin != _Margin) {
		Margin = _Margin;
		bRet = true;
	}
	if (Align != _Align) {
		Align = _Align;
		bRet = true;
	}
	return bRet;
}

CtRegion CtWidget::Element::allocate(const CtRegion& Region, const CtSize& Size)
{
	CtRegion tmpRegion;

	if (Region.width < Size.width) {
		CtDebugPrint(CtDbg, "width size over.... %3d : %3d\n", Region.width, Size.width);
	}
	if (Region.height < Size.height) {
		CtDebugPrint(CtDbg, "height size over.... %3d : %3d\n", Region.height, Size.height);
	}

	// 縦方向レイアウト
	if (Size.height > 0) {
		switch (Align & AlignVMask) {
		case AlignTop:
			tmpRegion.y = (short)(Region.y + Margin.Top);
			tmpRegion.height = Size.height;
			break;
		case AlignBottom:
			tmpRegion.y = (short)(Region.y + (Region.height - Size.height) - Margin.Bottom);
			tmpRegion.height = Size.height;
			break;
		case AlignVCenter:
		default:
			tmpRegion.y = (short)(Region.y + (Region.height - Size.height) / 2);
			tmpRegion.height = Size.height;
			break;
		}
	}
	else {
		tmpRegion.y = (short)(Region.y + Margin.Top);
		tmpRegion.height = (short)(Region.height - (Margin.Top + Margin.Bottom));
	}

	// 横方向レイアウト
	if (Size.width > 0) {
		switch (Align & AlignHMask) {
		case AlignLeft:
			tmpRegion.x = (short)(Region.x + Margin.Left);
			tmpRegion.width = Size.width;
			break;
		case AlignRight:
			tmpRegion.x = (short)(Region.x + (Region.width - Size.width) - Margin.Right);
			tmpRegion.width = Size.width;
			break;
		case AlignHCenter:
		default:
			tmpRegion.x = (short)(Region.x + (Region.width - Size.width) / 2);
			tmpRegion.width = Size.width;
			break;
		}

	}
	else {
		tmpRegion.x = (short)(Region.x + Margin.Left);
		tmpRegion.width = (short)(Region.width - (Margin.Left + Margin.Right));
	}

	return tmpRegion;
}

bool CtWidget::Element::setIndex(short _Index)
{
	if (Index == _Index)	return false;

	Index = _Index;
	return true;
}

short CtWidget::Element::getIndex() const
{
	return Index;
}

bool CtWidget::setInvalidate()
{
	if (isVisible() != true)
		return false;
	
	if (m_Invalidate == m_ScreenSel)
		return false;

	m_Invalidate = m_ScreenSel;
	return true;
}

bool CtWidget::setInvalidate(int Screen)
{
	CtScreenSel Sel = toSelScreen(Screen);
	
	if (m_Invalidate & Sel)
		return false;
	
	m_Invalidate = (CtScreenSel)(m_Invalidate | Sel);
	return true;
}

bool CtWidget::clearInvalidate()
{
	if (m_Invalidate == ScreenNone)
		return false;
	
	m_Invalidate = ScreenNone;
	return true;
}

bool CtWidget::clearInvalidate(int Screen)
{
	CtScreenSel Sel = toSelScreen(Screen);
	
	if (!(m_Invalidate & Sel))
		return false;
	
	m_Invalidate = (CtScreenSel)(m_Invalidate & ~Sel);
	return true;
}

bool CtWidget::isInvalidate() const
{
	if (m_Invalidate & getScreenSel())
		return true;

	return false;
}

bool CtWidget::isInvalidate(int Screen) const
{
	CtScreenSel Sel = toSelScreen(Screen);
	
	if (m_Invalidate & Sel)
		return true;

	return false;
}

bool CtWidget::getInvalidates(RegionArray& Array, int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

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

	if (isVisible(Screen) != true)	// 自身がVisibleで無ければ子供は不要
		return bRet;

	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		
		if (pWidget->getInvalidates(Array, Screen) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtWidget::clearInvalidates(int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	CtVector::Vector<CtWidget::Element*>* pVisibles = NULL;

	bRet = clearInvalidate(Screen);
	
	if (((pVisibles = getVisibles()) == NULL) || (pVisibles->empty() == true))
		return bRet;

	for (int i = 0; i < pVisibles->size(); i++) {
		if (((*pVisibles)[i] == NULL) || ((pWidget = (*pVisibles)[i]->pWidget) == NULL))
			continue;
		pWidget->clearInvalidates(Screen);
	}
	
	return bRet;
}

bool CtWidget::setVisible(bool bVisible)
{
	CtContainer* pContainer;
	
	if (m_bVisible == bVisible)
		return false;

	m_bVisible = bVisible;

	if ((pContainer = getContainer()) != NULL)
		pContainer->setVisible(bVisible);

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (m_ScreenSel & toSelScreen(i))
			setInvalidate(i);
	}
	
	return true;
}

bool CtWidget::isVisible()
{
	if (isFlashing() == true) {
		if (CtFlash::getInstance()->isShowing(this) != true) {
			return false;
		}
	}
		
	return m_bVisible;
}

bool CtWidget::isVisible(int Screen)
{
	if (!(m_ScreenSel & (1 << Screen)))
		return false;

	return isVisible();
}

bool CtWidget::isVisible(CtScreenSel Sel)
{
	if (!(m_ScreenSel & Sel))
		return false;

	return isVisible();
}

bool CtWidget::isVisible2(int Screen)
{
	CtWidget* pWidget = this;
	
	while (pWidget != NULL) {
		if (pWidget->isVisible(Screen) == false)
			return false;
		
		pWidget = pWidget->getParent();
	}

	return true;
}

bool CtWidget::isContains(const CtPosition& Pos, int i)
{
	return (m_Region[i] & Pos);
}

bool CtWidget::isContains(const CtPosition& Pos, CtScreenSel Sel)
{
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((toSelScreen(i) & Sel) && ((m_Region[i] & Pos) == true))
			return true;
	}
	return false;
}

bool CtWidget::isContains(const CtRegion& rhs, int i)
{
	return m_Region[i].isContains(rhs);
}

bool CtWidget::isContains(const CtRegion& rhs, CtScreenSel Sel)
{
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((toSelScreen(i) & Sel) && (m_Region[i].isContains(rhs) == true))
			return true;
	}
	return false;
}

bool CtWidget::isCollision(const CtRegion& rhs, int i)
{
	return (m_Region[i] & rhs);
}

bool CtWidget::isCollision(const CtRegion& rhs, CtScreenSel Sel)
{
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if ((toSelScreen(i) & Sel) && ((m_Region[i] & rhs) == true))
			return true;
	}
	return false;
}

bool CtWidget::setTrans(bool bTrans)
{
	if (m_bTrans == bTrans)
		return false;

	m_bTrans = bTrans;

	if (isVisible() == true)
		setInvalidate();

	return true;
}

bool CtWidget::setParent(CtWidget* pParent)
{
	m_pParent = pParent;
	return true;
}

bool CtWidget::setRegion(const CtRegion& Region, int Screen)
{
	if ((Region.width <= 0) || (Region.height <= 0))
		return false;

	if (m_Region[Screen] == Region)
		return false;

	m_Region[Screen] = Region;
	setLayout(Screen);

	if (isVisible() == true)
		setInvalidate();

	return true;
}

bool CtWidget::setRegion(short x, short y, short width, short height, int Screen)
{
	return setRegion(CtRegion(x, y, width, height), Screen);
}

bool CtWidget::movePos(const CtPosition& Position, int Screen)
{
	m_Region[Screen].x += Position.x;
	m_Region[Screen].y += Position.y;

	setLayout(Screen);

	if (isVisible() == true)
		setInvalidate();

	return true;
}

bool CtWidget::movePos(short x, short y, int Screen)
{
	return movePos(CtPosition(x, y), Screen);
}

bool CtWidget::setPos(const CtPosition& Position, int Screen)
{
	if ((m_Region[Screen].x == Position.x) &&
		(m_Region[Screen].y == Position.y)) {
		return false;
	}

	m_Region[Screen].x = Position.x;
	m_Region[Screen].y = Position.y;

	setLayout(Screen);

	if (isVisible() == true)
		setInvalidate();

	return true;
}

bool CtWidget::setPos(short x, short y, int Screen)
{
	return setPos(CtPosition(x, y), Screen);
}

bool CtWidget::setSize(const CtSize& Size)
{
	CtWidget* pParent = NULL;
	
	if (m_Size == Size)
		return false;

	m_Size = Size;

	if ((pParent = getParent()) != NULL) {
		for (int i = 0; i < CT_SCREEN_NUM; i++) {
			pParent->setLayout(i);
		}
	}
	
	if (isVisible() == true)
		setInvalidate();

	return true;
}

bool CtWidget::setAlign(const CtAlign Align)
{
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo()) == NULL)
		return false;

	if ((pDrawInfo->setAlign(Align) == true) && (isVisible() == true)) {
		setInvalidate();
		return true;
	}

	return false;
}

bool CtWidget::setAspectRatio(const CtAspectRatio Ratio)
{
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo()) == NULL)
		return false;

	if ((pDrawInfo->setAspectRatio(Ratio) == true) && (isVisible() == true)) {
		setInvalidate();
		return true;
	}

	return false;
}

bool CtWidget::setAutoAdjust(bool bAdjust)
{
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo()) == NULL)
		return false;

	if ((pDrawInfo->setAutoAdjust(bAdjust) == true) && (isVisible() == true)) {
		setInvalidate();
		return true;
	}

	return false;
}


CtListView* CtWidget::getListView() const
{
	if (isListView() == true) {
		return (CtListView*)this;

	}
	else {
		CtWidget* pWidget = m_pParent;

		while (pWidget != NULL) {
			if (pWidget->isListView() == true) {
				return (CtListView *)pWidget;
			}
			pWidget = pWidget->getParent();
		}
	}
	return NULL;
}

bool CtWidget::setScreenSel(const CtScreenSel ScreenSel)
{
	CtContainer* pContainer;
	CtScreenSel Sel = m_ScreenSel;
	CtScreenSel ChangeSel = (CtScreenSel)(m_ScreenSel | ScreenSel);

	if (m_ScreenSel == ScreenSel)
		return false;

	m_ScreenSel = ScreenSel;

	if ((pContainer = getContainer()) != NULL)
		pContainer->setScreenSel(ScreenSel);

	if (isVisible() == true) {
		for (int i = 0; i < CT_SCREEN_NUM; i++) {
			if (ChangeSel & toSelScreen(i))
				setInvalidate(i);
		}
	}
	
	return true;
}

CtScreenSel CtWidget::getScreenSel() const
{
	return m_ScreenSel;

}

CtWindow* CtWidget::getWindow() const
{
	if (isWindow() == true) {
		return (CtWindow*)this;

	}
	else {
		CtWidget* pWidget = m_pParent;

		while (pWidget != NULL) {
			if (pWidget->isWindow() == true) {
				return (CtWindow *)pWidget;
			}
			pWidget = pWidget->getParent();
		}
	}
	return NULL;
}

CtWindowMain* CtWidget::getMain() const
{
	CtWindow* pWindow;

	if (isWindow() == true) {
		pWindow = (CtWindow*)this;
		return pWindow->getMain();

	}
	else {
		CtWidget* pWidget = m_pParent;

		while (pWidget != NULL) {
			if (pWidget->isWindow() == true) {
				pWindow = (CtWindow*)pWidget;
				return pWindow->getMain();
			}
			pWidget = pWidget->getParent();
		}
	}
	return NULL;
}

CtColor CtWidget::getParentColor() const
{
	CtWidget *pParent = getParent();
	CtColor Color = CtColor::NoColor;

	while (pParent != NULL) {
		if ((pParent->isStackLabel() != true) && (pParent->isLayout() == true)) {
			Color = static_cast<CtLayout*>(pParent)->getColor();
			if ((Color.isNoColor() != true) && (Color.RGBA != 0x00000000))
				break;
		}
		pParent = pParent->getParent();
	}
	return Color;
}

bool CtWidget::startFlash(CtEventFlash::Frequency Freq)
{
	m_FlashFrequency = Freq;
		
	CtFlash::getInstance()->startFlash(Freq, this);
	return true;
}

bool CtWidget::stopFlash()
{
	m_FlashFrequency = CtEventFlash::Freq_Invalid;
	CtFlash::getInstance()->stopFlash(this);

	setInvalidate();
	
	return true;
}

bool CtWidget::isFlashing()
{
	if (CtEventFlash::Freq_Invalid == m_FlashFrequency) {
		return false;
	}
	return CtFlash::getInstance()->isFlashing(this);
}

unsigned long CtWidget::getDrawKey()
{
	CtDrawInfo* pDrawInfo = getDrawInfo();
	
	if (pDrawInfo == NULL)
		return 0;

	return pDrawInfo->getDrawKey();
}

bool CtWidget::setDrawImage(const GDI_DRAWABLE_ID imageId)
{
	CtDrawInfo* pDrawInfo = getDrawInfo();

	if (pDrawInfo == NULL)
		return false;
	
	return pDrawInfo->setDrawImage(imageId);
}

bool CtWidget::setDrawImage()
{
	CtDrawInfo* pDrawInfo = getDrawInfo();
	GDI_DRAWABLE_ID image_id = GDI_INVALID_ID;
	unsigned long key = getDrawKey();
	
	if (pDrawInfo == NULL)
		return false;
		
	if ((image_id = CtDrawCache::getInstance()->referCache(*pDrawInfo, key)) != GDI_INVALID_ID) {
		pDrawInfo->setDrawImage(image_id);
		return true;
		
	} else {
		if ((image_id = CtDraw::getInstance()->convertDrawable(this, Format_Window)) != GDI_INVALID_ID) {
			CtDrawCache::getInstance()->setCache(*pDrawInfo, key, image_id);
			pDrawInfo->setDrawImage(image_id);
			return true;
		}
	}
	return false;
}

bool CtWidget::setDrawImage(CtDrawInfo* pDrawInfo)
{
	GDI_DRAWABLE_ID image_id = GDI_INVALID_ID;
	unsigned long key = 0;
	
	if (pDrawInfo == NULL)
		return false;
	
	key = pDrawInfo->getDrawKey();

	if ((image_id = CtDrawCache::getInstance()->referCache(*pDrawInfo, key)) != GDI_INVALID_ID) {
		pDrawInfo->setDrawImage(image_id);
		return true;
		
	} else {
		if ((image_id = CtDraw::getInstance()->convertDrawable(pDrawInfo, Format_Window)) != GDI_INVALID_ID) {
			CtDrawCache::getInstance()->setCache(*pDrawInfo, key, image_id);
			pDrawInfo->setDrawImage(image_id);
			return true;
		}
	}
	return false;
}

CtDrawInfo* CtWidget::getDrawInfo(const CtRegion& Clip, int Screen)
{
	return NULL;
}

bool CtWidget::getDrawInfo(CtList::list<CtDrawInfo*> &_List, const CtRegion& Clip, int Screen)
{
	return false;
}

bool CtWidget::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtDrawInfo* pDrawInfo = NULL;
	CtRegion clip = Clip;

	if (isCollision(Clip, Screen) != true)
		return bRet;
	
	clearInvalidate(Screen);
	
	if (isVisible(Screen) != true)
		return bRet;

	clip &= m_Region[Screen];
	
	if ((pDrawInfo = getDrawInfo(clip, Screen)) != NULL)
		bRet = pDrawInfo->draw();

	return bRet;
}

bool CtWidget::drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen)
{
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo(Clip, Screen)) == NULL)
		return false;

	pDrawInfo->movePos(shift_x, shift_y);

	return pDrawInfo->draw();
}

bool CtWidget::putRegionList(RegionArray& Array, CtRegion& Region)
{
	CtRegion Tmp = Region;
	
	Tmp.x--;
	Tmp.y--;
	Tmp.width += 2;
	Tmp.height += 2;

	// 含まれていたらorを取る
	// 隣り合っていたら合体させる
	
	for (int i = 0; i < Array.size(); i++) {
		if (Array[i] & Tmp) {
			Array[i] |= Region;

			mergeRegionList(Array);

			return true;
		}
	}
	Array.push_back(Region);
	return true;
}

bool CtWidget::mergeRegionList(RegionArray& Array)
{
	bool bRet = false;
	int ArrayMax = Array.size();

	if (ArrayMax <= 1)
		return bRet;

	for (int i = 0; i < ArrayMax; i++) {
		if (Array[i].isValid() != true)
			continue;
		for (int j = 0; j < ArrayMax; j++) {
			if (i == j) continue;

			if (Array[i] & Array[j]) {
				Array[i] |= Array[j];
				Array[j] = NoRegion;
				bRet = true;
			}
		}
	}
	return bRet;
}


CtWidgetType CtWidget::getWidgetType() const
{
	if (isRootWindow() == true)		return WidgetRootWindow;
	if (isWindow() == true)			return WidgetWindow;
	if (isListView() == true)		return WidgetListView;
	if (isMenuButton() == true)		return WidgetMenuButton;
	if (isButton() == true)			return WidgetButton;
	if (isParamBox() == true)		return WidgetParamBox;
	if (isParamLabel() == true)		return WidgetParamLabel;
	if (isStackLabel() == true)		return WidgetStackLabel;
	if (isLayout() == true)			return WidgetLayout;
	if (isLabel() == true)			return WidgetLabel;

	return WidgetNone;
}

bool CtWidget::checkWidgetType(const CtWidgetType Type, const CtWidget* pWidget)
{
	bool bRet = false;

	if (pWidget == NULL)
		return bRet;

	if (Type == WidgetAll)
		return true;

	switch (Type) {
	case WidgetFastDraw:	if (pWidget->isFastDraw() == true)		bRet = true;	break;
	case WidgetRootWindow:	if (pWidget->isRootWindow() == true)	bRet = true;	break;
	case WidgetWindow:		if (pWidget->isWindow() == true)		bRet = true;	break;
	case WidgetMenuButton:	if (pWidget->isMenuButton() == true)	bRet = true;	break;
	case WidgetFocusable:	if (pWidget->isFocusable() == true) 	bRet = true;	break;
	case WidgetButton:		if (pWidget->isButton() == true)		bRet = true;	break;
	case WidgetListView:	if (pWidget->isListView() == true)		bRet = true;	break;
	case WidgetParamBox:	if (pWidget->isParamBox() == true)		bRet = true;	break;
	case WidgetParamLabel:	if (pWidget->isParamLabel() == true)	bRet = true;	break;
	case WidgetStackLabel:	if (pWidget->isStackLabel() == true)	bRet = true;	break;
	case WidgetLayout:		if (pWidget->isLayout() == true)		bRet = true;	break;
	case WidgetLabel:		if (pWidget->isLabel() == true)			bRet = true;	break;
	case Container:			if (pWidget->haveContainer() == true)	bRet = true;	break;
	default:		break;
	}
	return bRet;
}

void CtWidget::setName(const char* str)
{
#ifdef CT_DEBUG
	if (str == NULL)
		return;

	unsigned int len = get_char_string_length(str);

	if (len >= sizeof(m_Name) - 1) {
		len = sizeof(m_Name) - 1;
	}
	memcpy(m_Name, str, len);
	m_Name[len] = NULL;
	return;
#else
	return;
#endif
}

char* getName()
{
#ifdef CT_DEBUG
	return &m_Name;
#else
	return NULL;
#endif
}

#ifdef WIN32_GUI_SIM
#include <typeinfo.h>
#else
#include "CtLayout.h"
#endif

#if defined CT_DBG_TSK_ACT || WIN32_GUI_SIM
#include "CtDbgWidgetTree.h"
#endif

void CtWidget::outputOutline(int depth, const char* header, int Screen)
{
	char indent[64] = { 0x00 };
	char size_str[32] = { 0x00 };
	char region_str[32] = { 0x00 };
	const char *widget_type = NULL;
	CtRegion region = this->getRegion(Screen);
	CtSize   size = this->getSize();

	// インデント文字列
	for (int i = 0; i < depth; i++) strcat(indent, "    ");

	// ウィジットタイプ文字列
#ifndef WIN32_GUI_SIM
	// armcc環境でtypeid使用可否が不明のため従来通りの処理
	switch(getWidgetType()){
	case WidgetNone:		widget_type = "None";			break;
	case WidgetLabel:		widget_type = "Label";			break;
	case WidgetParamLabel:	widget_type = "ParamLabel";		break;
	case WidgetParamBox:	widget_type = "ParamBox";		break;
	case WidgetButton:		widget_type = "Button";			break;
	case WidgetMenuButton:	widget_type = "MenuButton";		break;
	case WidgetStackLabel:	widget_type = "StackLabel";		break;
	case WidgetLayout:
	{
		CtLayout::LayoutType type = static_cast<CtLayout*>(this)->getLayoutType();
		switch (type) {
		case CtLayout::LayoutVertical:		widget_type = "VLayout";	break;
		case CtLayout::LayoutHolizontal:	widget_type = "HLayout"; 	break;
		case CtLayout::LayoutGrid:			widget_type = "GLayout";	break;
		case CtLayout::LayoutStack:			widget_type = "Slayout";	break;
		default:	break;
		}
	}
		break;
	case WidgetListView:	widget_type = "ListView";	break;
	case WidgetWindow:		widget_type = "Window";		break;
	case WidgetRootWindow:	widget_type = "RootWindow";	break;
	default:				widget_type = "Unknown";	break;
	}
#else
	widget_type = typeid(*this).name() + strlen("class ");	// "class hogehoge"の "class "は捨てる
#endif

	// サイズ文字列
	if (size.width == 0 && size.height == 0) sprintf(size_str, "Size[Auto]");
	else sprintf(size_str, "Size[%3d, %3d]", size.width, size.height);

	// リージョン文字列
	sprintf(region_str, "Region[%3d, %3d, %3d, %3d]", region.x, region.y, region.width, region.height);

#if defined CT_DBG_TSK_ACT || WIN32_GUI_SIM
	CtDbgWidgetTree::CtDbgWidgetTreeData node;
	memcpy( node.WidgetType, widget_type, sizeof(node.WidgetType)/sizeof(char));
	node.depth = depth;
	node.widgetAdr = (int)this;
	node.screen = m_ScreenSel;
	node.Size_x = size.width;
	node.Size_y = size.height;
	node.region_x = region.x;
	node.region_y = region.y;
	node.region_w = region.width;
	node.region_h = region.height;
	node.visible = m_bVisible;
	node.trans = isTrans();
	node.ParentWidgetAdr = (int)getParent();
	CtDbgWidgetTree::getInstance()->setTreeData(node);
#else
	// 出力
	//	CtDebugPrint(CtDbg, "%s%s[%s] %p %s %s Sel(%d) V(%d) Tr(%d) EF(%08X)\n", indent, (header ? header : ""), widget_type, this, size_str, region_str, m_ScreenSel, m_bVisible, isTrans(), getEventFilter());
	CtDebugPrint(CtDbg, "%s%s[%s] %p %s %s Sel(%d) V(%d) Tr(%d) P(%p)\n", indent, (header ? header : ""), widget_type, this, size_str, region_str, m_ScreenSel, m_bVisible, isTrans(), getParent());
#endif
	CtDebugPrint(CtDbg, "%s%s[%s] %p %s %s Sel(%d) V(%d) Tr(%d) P(%p)\n", indent, (header ? header : ""), widget_type, this, size_str, region_str, m_ScreenSel, m_bVisible, isTrans(), getParent());
	
}
