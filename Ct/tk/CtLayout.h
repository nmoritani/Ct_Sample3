/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtLayout
 */


#ifndef __CtLayout_H__
#define __CtLayout_H__

#include <CtVector.h>
#include "CtLabel.h"
#include "CtEvent.h"
#include "CtContainer.h"
#include "CtDrawInfo.h"
#include "CtContainer.h"

class CtButton;

class CtLayout : public CtWidget {
protected:
	#define DefaultAlign	AlignInvalid
	#define DefaultMargin	CtMargin(0,0,0,0)

public :
	enum LayoutType {
		LayoutVertical,
		LayoutHolizontal,
		LayoutGrid,
		LayoutStack,
		LayoutFree,
		
		LayoutType_MAX
	};


	class SplitElement : public CtWidget::Element {
	public:
		SplitElement();
		SplitElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
		SplitElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll);
		virtual ~SplitElement();

		bool set(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
		bool set(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll);
		bool setStretch(short Stretch, CtScreenSel Sel = ScreenAll);
		bool setStretch(const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
		bool setIndex(short Index);

		CtScreenSel ScreenSel;
		struct {
			short		Ratio;
			CtSize		Size;
		} Stretch[CT_SCREEN_NUM];
	};
	
	class SpanElement : public CtWidget::Element {
	public:
		SpanElement();
		SpanElement(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan);
		virtual ~SpanElement();

		bool set(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan);
		bool setIndex(short Index);

		short		RowSpan;
		short		ColumnSpan;
	};
	
    CtLayout();
    CtLayout(const CtColor& Color);
    CtLayout(const CtSize& Size, const CtColor& Color = CtColor::NoColor);
    CtLayout(const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
    virtual ~CtLayout();
	
	virtual bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool addWidget(CtWidget* pWidget, CtMargin Margin, short Stretch = 1);		// ElementsAlignで配置
	virtual bool addWidget(CtWidget* pWidget, CtAlign Align, short Stretch = 1);		// ElementsMarginで配置
	virtual bool addWidget(CtWidget* pWidget, short Stretch = 1);						// ElementsMargin, ElementsAlignで配置
	virtual bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool addWidget(CtWidget* pWidget, CtMargin Margin, const CtSize& Stretch);
	virtual bool addWidget(CtWidget* pWidget, CtAlign Align, const CtSize& Stretch);
	virtual bool addWidget(CtWidget* pWidget, const CtSize& Stretch);
	
	virtual bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch = 1);		// ElementsAlignで配置
	virtual bool setWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch = 1);		// ElementsMarginで配置
	virtual bool setWidget(CtWidget* pWidget, short Index, short Stretch = 1);						// ElementsMargin, ElementsAlignで配置
	virtual bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch);
	virtual bool setWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch);
	virtual bool setWidget(CtWidget* pWidget, short Index, const CtSize& Stretch);
	
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch = 1);
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch = 1);
	virtual bool insertWidget(CtWidget* pWidget, short Index, short Stretch = 1);
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch);
	virtual bool insertWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch);
	virtual bool insertWidget(CtWidget* pWidget, short Index, const CtSize& Stretch);
	virtual bool removeWidget(short Index);
	virtual bool removeWidget(CtWidget* pWidget);
	
	virtual bool addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool addContainer(CtContainer* pContainer, CtMargin Margin, short Stretch = 1);
	virtual bool addContainer(CtContainer* pContainer, CtAlign Align, short Stretch = 1);
	virtual bool addContainer(CtContainer* pContainer, short Stretch = 1);
	virtual bool addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool addContainer(CtContainer* pContainer, CtMargin Margin, const CtSize& Stretch);
	virtual bool addContainer(CtContainer* pContainer, CtAlign Align, const CtSize& Stretch);
	virtual bool addContainer(CtContainer* pContainer, const CtSize& Stretch);
	
	virtual bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch = 1);
	virtual bool setContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch = 1);
	virtual bool setContainer(CtContainer* pContainer, short Index, short Stretch = 1);
	virtual bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch);
	virtual bool setContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch);
	virtual bool setContainer(CtContainer* pContainer, short Index, const CtSize& Stretch);
	
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch = 1);
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch = 1);
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch = 1);
	virtual bool insertContainer(CtContainer* pContainer, short Index, short Stretch = 1);
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch);
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch);
	virtual bool insertContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch);
	virtual bool insertContainer(CtContainer* pContainer, short Index, const CtSize& Stretch);
	virtual bool removeContainer(short Index);
	virtual bool removeContainer(CtContainer* pContainer);
	
	virtual bool setElementsMargin(CtMargin Margin);
	virtual bool setElementsMargin(CtMargin Margin, CtAlign Align);
	virtual bool setElementsColor(const CtColor& fillColor);
	virtual bool setElementsColor(const CtColor& fillColor, const CtColor& edgeColor);
	virtual bool setElementsParent(CtWidget* pParent);
	
	virtual bool addSpacing(const CtSize& Size, CtScreenSel Sel = ScreenAll);
	virtual bool insertSpacing(short Index, const CtSize& Size, CtScreenSel Sel = ScreenAll);
	
	virtual bool addStretch(short Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool addStretch(const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool insertStretch(short Index, short Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool insertStretch(short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(CtWidget* pWidget, short Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(CtWidget* pWidget, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(CtContainer* pContainer, short Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(CtContainer* pContainer, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(short Index, short Stretch, CtScreenSel Sel = ScreenAll);
	virtual bool setStretch(short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll);

	virtual bool updateVisibles();
	virtual bool setLayout(int Screen = 0);
	virtual bool setColor(const CtColor& fillColor);
	virtual bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	CtColor getColor() const;

    virtual bool getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
    virtual bool existWidget(SearchType SearchType, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
	virtual CtWidget* getNeary(const CtRegion& currentRegion, const CtWidgetType Type, const CtDirection Dir);
	virtual bool isRegistered(CtWidget *pWidget);

	virtual bool initialFocus(bool bSilent);
	
	CtLayout::LayoutType getLayoutType() const;
	
	bool setContainer(CtContainer *pContainer);
	
	bool isLabel() const;
	bool isLayout() const;
	bool haveContainer() const;
	
	CtContainer* getContainer() const;
	int getElementNum() const;

	virtual CtVector::Vector<CtWidget::Element*>* getElements() const;
	virtual CtVector::Vector<CtWidget::Element*>* getVisibles() const;

	virtual bool setDrawImage();
	virtual unsigned long getDrawKey();
	
	virtual CtDrawInfo* getDrawInfo(const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool draw(const CtRegion& Clip, int Screen = 0);
	virtual bool drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen = 0);

	virtual bool setFastDraw(bool bFast);
	virtual bool isFastDraw() const;
	virtual bool initialFastDraw();
	virtual bool cleanupFastDraw();
	
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	
	virtual void outputOutline(int depth, const char* header, int Screen = 0);

protected :
	void ctor();
	bool setLayoutType(CtLayout::LayoutType Type);
	
	bool setStackLayout(int Screen = 0);
	bool setVLayout(int Screen = 0);
	bool setHLayout(int Screen = 0);
	bool setGridLayout(short RowNum, short ColumnNum, int Screen = 0);

	bool isStretched() const;
	
	virtual void printElements(CtVector::Vector<CtWidget::Element*>* pElements, char* pTitle);

	// Elementの設定
	CtVector::Vector<CtLayout::SplitElement*> 	m_Elements;
	CtMargin  		m_ElementsMargin;
	CtAlign	  		m_ElementsAlign;
	
private:

	LayoutType		m_LayoutType;
	CtContainer*	m_pContainer;
	bool			m_bStretched;
	bool			m_bFastDraw;
	
	CtDrawInfo*		m_pBackground;
};

inline bool CtLayout::isLabel() const
{
	return false;
}

inline bool CtLayout::isLayout() const
{
	return true;
}

inline bool CtLayout::isStretched() const
{
	return m_bStretched;
}

inline bool CtLayout::haveContainer() const
{
	if (m_pContainer == NULL)	return false;
	return true;
}

inline CtContainer* CtLayout::getContainer() const
{
	return m_pContainer;
}

inline int CtLayout::getElementNum() const
{
	return m_Elements.size();
}

inline CtLayout::LayoutType CtLayout::getLayoutType() const
{
	return m_LayoutType;
}

inline bool CtLayout::setLayoutType(CtLayout::LayoutType Type)
{
	m_LayoutType = Type;
	return true;
}

inline bool CtLayout::updateVisibles()
{
	return false;
}

inline CtVector::Vector<CtWidget::Element*>* CtLayout::getElements() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_Elements;
}

inline CtVector::Vector<CtWidget::Element*>* CtLayout::getVisibles() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_Elements;
}


#endif
