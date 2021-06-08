/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidget
 */


#ifndef __CtWidget_H__
#define __CtWidget_H__

#include "gdi.h"
#include "CtObject.h"
#include "CtList.h"
#include "CtVector.h"

#include "Ct.h"
#include "CtColor.h"
#include "CtDraw.h"
#include "CtEventHandler.h"
#include "CtTimer.h"
#include "CtFlash.h"

class CtWindow;
class CtListView;
class CtLayout;
class CtLayout;
class CtLabel;
class CtContainer;
class CtWindowMain;

enum CtWidgetType {
	WidgetNone,
	WidgetLabel,
	WidgetLayout,
	WidgetButton,
	WidgetMenuButton,
	WidgetListView,
	WidgetStackLabel,
	WidgetParamBox,
	WidgetParamLabel,
	WidgetWindow,
	WidgetRootWindow,
	
	Container,
	WindowMain,
	WidgetFocusable,
	WidgetFastDraw,

	WidgetAll,
	WidgetType_MAX
};

enum CtDirection {
	DirUp,
	DirDown,
	DirLeft,
	DirRight
};

class CtWidget : public CtEventHandler {
public :
	typedef CtVector::Vector<CtWidget*> WidgetArray;
	typedef CtVector::Vector<CtRegion> RegionArray;
	
    typedef CtList::list<CtWidget*> List;
    typedef CtList::list<CtWidget*>::iterator ListItr;
    typedef CtList::list<CtRegion> RegionList;
    typedef CtList::list<CtRegion>::iterator RegionItr;

	enum SearchType {
		Registered,
		RegisteredContains,
		RegisteredCollisions,
		Visible,
		VisibleContains,
		VisibleCollisions,
		Invalidated,
		Fastdraw,
	};

	class Element : public CtObject {
	public:
		Element();
		Element(CtWidget* pWidget, CtMargin Margin, CtAlign Align);
		virtual ~Element();

		bool set(CtWidget* pWidget, CtMargin Margin, CtAlign Align);
		CtRegion allocate(const CtRegion& Region, const CtSize& Size);

		bool setIndex(short Index);
		short getIndex() const;

		CtWidget* 	pWidget;
		CtMargin	Margin;
		CtAlign		Align;
		short		Index;
	};
	
protected :
    CtWidget();
    CtWidget(const CtSize& Size);
	CtWidget(const CtRegion& Region);
	void ctor();
	
public :
    virtual ~CtWidget();
    
	void setWidgetID(int WidgetID);
	unsigned long getWidgetID();
	
	virtual bool setTrans(bool bTrans);
	bool isTrans() const;
	
	CtDrawType getDrawType() const;

	virtual bool setRegion(const CtRegion& Region, int Screen = 0);
	virtual bool setRegion(short x, short y, short width, short height, int Screen = 0);
	virtual bool movePos(const CtPosition& Position, int Screen = 0);
	virtual bool movePos(short x, short y, int Screen = 0);
	virtual bool setPos(const CtPosition& Position, int Screen = 0);
	virtual bool setPos(short x, short y, int Screen = 0);
	virtual bool setLayout(int Screen = 0);
	
	const CtRegion getRegion(int Screen = 0) const;
	const CtPosition getCenterPosition(int Screen = 0) const;
	
	virtual bool setColor(const CtColor& fillColor);
	virtual bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	
	virtual bool setAlign(const CtAlign Align);
	virtual bool setAspectRatio(const CtAspectRatio Ratio);
	virtual bool setAutoAdjust(bool bAdjust);

	bool setSize(const CtSize& Size);
	const CtSize getSize() const;

	virtual bool setDrawImage();
	virtual bool setDrawImage(GDI_DRAWABLE_ID imageId);
	virtual bool setDrawImage(CtDrawInfo* pDrawInfo);
	virtual unsigned long getDrawKey();
	virtual CtDrawInfo* getDrawInfo(const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool getDrawInfo(CtList::list<CtDrawInfo*> &_List, const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool draw(const CtRegion& Clip, int Screen = 0);
	virtual bool drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen = 0);

	bool isContains(const CtPosition& Pos, int Screen = 0);
	bool isContains(const CtPosition& Pos, CtScreenSel Sel);
	bool isContains(const CtRegion& rhs, int Screen = 0);
	bool isContains(const CtRegion& rhs, CtScreenSel Sel);
	bool isCollision(const CtRegion& rhs, int Screen = 0);
	bool isCollision(const CtRegion& rhs, CtScreenSel Sel);
	
	virtual CtWidgetType getWidgetType() const;
	virtual bool checkWidgetType(const CtWidgetType Type, const CtWidget* pWidget);
	
	virtual bool isRootWindow() const;
	virtual bool isWindow() const;
	virtual bool isPageView() const;
	virtual bool isListView() const;
	virtual bool isLayout() const;
	virtual bool isFocusable() const;
	virtual bool isButton() const;
	virtual bool isMenuButton() const;
	virtual bool isStackLabel() const;
	virtual bool isParamLabel() const;
	virtual bool isParamBox() const;
	virtual bool isLabel() const;
	virtual bool haveContainer() const;

	virtual bool isFastDraw() const;
	virtual bool setFastDraw(bool bFast);
	virtual bool initialFastDraw();
	virtual bool cleanupFastDraw();
	
    virtual bool setInvalidate();
	virtual bool setInvalidate(int Screen);
	virtual bool clearInvalidate();
	virtual bool clearInvalidate(int Screen);
    virtual bool isInvalidate() const;
    virtual bool isInvalidate(int Screen) const;
	
	virtual bool getInvalidates(RegionArray& Array, int Screen);
	virtual bool clearInvalidates(int Screen = 0);
	
    virtual bool setVisible(bool bVisible);
    bool isVisible();
	bool isVisible(int Screen);
	bool isVisible(CtScreenSel Sel);
	bool isVisible2(int Screen);

	bool setParent(CtWidget* pParent);
	CtWidget* getParent() const;
	CtColor getParentColor() const;

	virtual CtWindow* getWindow() const;
	virtual CtListView* getListView() const;
	virtual CtContainer* getContainer() const;
	virtual CtWindowMain* getMain() const;
	
	virtual bool startFlash(CtEventFlash::Frequency Freq);
	virtual bool stopFlash();
	virtual bool isFlashing();

	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleFlashEvent(const CtEventFlash& Flash);
	virtual bool handleButtonEvent(const CtEventButton& Button);

	virtual CtVector::Vector<CtWidget::Element*>* getElements() const;
	virtual CtVector::Vector<CtWidget::Element*>* getVisibles() const;
    virtual bool getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
    virtual bool existWidget(SearchType SearchType, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
	virtual CtWidget* getNeary(const CtRegion& currentRegion, const CtWidgetType Type, const CtDirection Dir);
	virtual bool isRegistered(CtWidget *pWidget);
	virtual bool setElementsParent(CtWidget* pParent);
	
	virtual bool setScreenSel(const CtScreenSel ScreenSel);
	CtScreenSel getScreenSel() const;

	bool putRegionList(RegionArray& Array, CtRegion& Region);
	bool mergeRegionList(RegionArray& Array);

	virtual void outputOutline(int depth, const char* header, int Screen = 0);

	void setName(const char* str);
	const char* getName();
	
protected:
    CtRegion 		m_Region[CT_SCREEN_NUM];
	CtRegion		m_ClearRegion[CT_SCREEN_NUM];
	CtSize			m_Size;
	bool			m_bTrans;
	CtScreenSel		m_Invalidate;	// invalidate領域は、変化のある領域(以前の領域と、今回の領域)を管理しないとダメ
	CtScreenSel		m_ScreenSel;
	
private :
	unsigned long	m_WidgetID;
	bool 			m_bVisible;
	CtEventFlash::Frequency m_FlashFrequency;

	CtWidget* 		m_pParent;
	
#ifdef CT_DEBUG
	char			m_Name[32];
#endif
};

inline void CtWidget::setWidgetID(int WidgetID)
{
	m_WidgetID = WidgetID;
}

inline unsigned long CtWidget::getWidgetID()
{
	if (m_WidgetID == 0)
		return (unsigned long)this;
	
	return m_WidgetID;
}
	
inline int getScreenNo(CtScreenSel Sel)
{
	int i;
	for (i = ScreenMaster; i < ScreenAll; i = i <<1) {
		if (i & Sel)
			return i -1;
	}
	return -1;
}

inline bool CtWidget::isTrans() const
{
	return m_bTrans;
}

inline bool CtWidget::setLayout(int Screen)
{
	return false;
}

inline const CtRegion CtWidget::getRegion(int Screen) const
{
	return m_Region[Screen];
}

inline const CtPosition CtWidget::getCenterPosition(int Screen) const
{
	CtPosition Pos;
	
	if ((Screen < 0) || (Screen >= CT_SCREEN_NUM))
		return Pos;

	Pos.x = (short)(m_Region[Screen].x + m_Region[Screen].width/2);
	Pos.y = (short)(m_Region[Screen].y + m_Region[Screen].height/2);
		
    return Pos;
}

inline bool CtWidget::setColor(const CtColor& fillColor)
{
    return false;
}

inline bool CtWidget::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
    return false;
}

inline const CtSize CtWidget::getSize() const
{
    return m_Size;
}

inline CtWidget* CtWidget::getParent() const
{
    return m_pParent;
}

inline bool CtWidget::isRootWindow() const
{
	return false;
}

inline bool CtWidget::isWindow() const
{
	return false;
}

inline bool CtWidget::isLayout() const
{
	return false;
}

inline bool CtWidget::isListView() const
{
	return false;
}

inline bool CtWidget::isPageView() const
{
	return false;
}

inline bool CtWidget::isFocusable() const
{
	return false;
}

inline bool CtWidget::isButton() const
{
	return false;
}

inline bool CtWidget::isMenuButton() const
{
	return false;
}

inline bool CtWidget::isParamLabel() const
{
	return false;
}

inline bool CtWidget::isParamBox() const
{
	return false;
}

inline bool CtWidget::isLabel() const
{
	return false;
}

inline bool CtWidget::isStackLabel() const
{
	return false;
}

inline bool CtWidget::initialFastDraw()
{
	return false;
}

inline bool CtWidget::cleanupFastDraw()
{
	return false;
}

inline bool CtWidget::isFastDraw() const
{
	return false;
}

inline bool CtWidget::setFastDraw(bool bFast)
{
	return false;
}

inline bool CtWidget::haveContainer() const
{
	return false;
}

inline CtContainer* CtWidget::getContainer() const
{
	return NULL;
}

inline CtVector::Vector<CtWidget::Element*>* CtWidget::getElements() const
{
	return NULL;
}

inline CtVector::Vector<CtWidget::Element*>* CtWidget::getVisibles() const
{
	return NULL;
}

inline bool CtWidget::getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	return false;
}
inline bool CtWidget::existWidget(SearchType SearchType, const CtWidgetType WidgetType, int Screen, const CtRegion& Region)
{
	return false;
}
inline CtWidget* CtWidget::getNeary(const CtRegion& currentRegion, const CtWidgetType Type, const CtDirection Dir)
{
	return NULL;
}
inline bool CtWidget::isRegistered(CtWidget* pWidget)
{
	return false;
}

inline bool CtWidget::setElementsParent(CtWidget* pParent)
{
	return false;
}

#endif

