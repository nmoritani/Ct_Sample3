/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListView
 */


#ifndef __CtListView_H__
#define __CtListView_H__

#include "CtVLayout.h"
#include "CtStyle.h"

class CtButton;

class CtListView : public CtLayout {
public :
	CtListView();
	CtListView(short ViewRow);
	CtListView(short ViewRow, const CtColor& Color);
	CtListView(short ViewRow, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtListView(short ViewRow, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~CtListView();

	virtual bool clear();
	virtual bool setSelectLabel(CtLabel* pLabel, CtMargin Margin = DefaultMargin);
	virtual bool updateVisibles();
	virtual bool setLayout(int Screen = 0);
	
	virtual bool setViewRow(short ViewRow);
	virtual int getViewRow() const;

	virtual bool setViewColumn(short ViewColumn);
	virtual int getViewColumn() const;

	virtual int getViewSize() const;
	
	virtual CtWidget* getFocusWidget();
	virtual CtWidget* getWidget(int Index);
	virtual int getCurrentIndex();

	virtual bool setCurrentElement(int Element, bool bEnd = false);
	virtual int getElementNo(CtWidget::Element* pElement);
	virtual bool setTopElement(int Element);
	virtual bool setBottomElement(int Element);
	virtual bool nextElement();
	virtual bool prevElement();
	virtual bool setInitialFocus(int Element);
	
	virtual bool setPage(int PageNum);
	virtual bool nextPage();
	virtual bool prevPage();

	int getCurrentPage();
	int getMaxPage();
	int getPage(int Element);

	bool isFocusedInElement(CtWidget* pWidget);
	virtual bool setFocusInElement(CtWidget* pWidget, bool bEnd = false);
	virtual bool cancelFocusInElement(CtWidget* pWidget);
	bool nextFocusInElement();
	bool prevFocusInElement();
	
	virtual bool getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool draw(const CtRegion& Clip, int Screen = 0);
	virtual bool drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen = 0);

	virtual bool initialFocus(bool bSilent);
	virtual bool moveFocus(const CtDirection Dir, bool Silent);
	virtual bool setDialIndex();
	virtual bool dialFocus(const bool bPlus, bool Silent);

	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleTouchEvent(const CtEventTouch& Touch);

	bool setScroll(bool bScroll);
	bool isScroll() const;

	inline virtual bool isListView() const;
	
protected :
	CtListView(short ViewRow, short ViewColumn);
	CtListView(short ViewRow, short ViewColumn, const CtColor& Color);
	CtListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	
	void ctor(short Row, short Column = 1);

	virtual CtVector::Vector<CtWidget::Element*>* getVisibles() const;
	
	enum ElementDir {
		Prev,
		Next
	};
	virtual bool isSelectableElement(int Element);
	virtual bool isSelectableElement(CtWidget::Element* pElement);
	virtual int getSelectableElement(int Element, ElementDir Dir = Prev);
	virtual bool selectElement(int Element, bool bEnd = false);
	virtual bool unselectElement(int Element);
	
	virtual bool isValidElement(int Element);
	virtual bool isValidElement(CtWidget::Element* pElement);
	virtual int getValidElement(int Element, ElementDir Dir = Prev);
	virtual int getValidElementsNum(int Element = -1);

	short 		m_ViewRow;
	short 		m_ViewColumn;
	int 		m_CurrentElement;
	bool		m_bScroll;
	CtLabel* 	m_pSelect;
	CtMargin 	m_SelectMargin;

	CtVector::Vector<CtLayout::SplitElement*> 	m_Visibles;
	CtVector::Vector<CtLayout::SplitElement*> 	m_Blanks;
};

inline bool CtListView::isListView() const
{
	return true;
}

inline CtVector::Vector<CtWidget::Element*>* CtListView::getVisibles() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_Visibles;
}

inline bool CtListView::setScroll(bool bScroll)
{
	if (m_bScroll == bScroll)
		return false;

	m_bScroll = bScroll;
	return true;
}

inline bool CtListView::isScroll() const
{
	return m_bScroll;
}


#endif
