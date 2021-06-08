/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtGridLayout
 */


#ifndef __CtGridLayout_H__
#define __CtGridLayout_H__

#include "Ct.h"
#include "CtLayout.h"

class CtGridLayout : public CtLayout {
public :
    CtGridLayout();
	CtGridLayout(const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtGridLayout(const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
    CtGridLayout(short Row, short Column);
    CtGridLayout(short Row, short Column, const CtColor& Color);
    CtGridLayout(short Row, short Column, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
    CtGridLayout(short Row, short Column, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~CtGridLayout();
	
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align);
	bool addWidget(CtWidget* pWidget, CtMargin Margin);
	bool addWidget(CtWidget* pWidget, CtAlign Align);
	bool addWidget(CtWidget* pWidget);
	
	bool setWidget(CtWidget* pWidget, short Row, short Column);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtAlign Align);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, CtAlign Align);
	bool setWidget(CtWidget* pWidget, short Row, short Column, short RowSpan, short ColumnSpan);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtAlign Align, short RowSpan, short ColumnSpan);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, short RowSpan, short ColumnSpan);
	bool setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan);

	bool removeWidget(CtWidget* pWidget);
	bool removeWidget(short Row, short Column);

	CtVector::Vector<CtWidget::Element*>* getElements() const;
	CtVector::Vector<CtWidget::Element*>* getVisibles() const;
	
	int columnCount() const;
	int rowCount() const;
	bool setSpan(short RowSpan, short Column, int Index);
	
	bool setLayout(int Screen = 0);
	
protected:
	void ctor(short Row, short Column);
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan);
	bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan);

private:
	short m_RowNum;
	short m_ColumnNum;
	CtVector::Vector<CtLayout::SpanElement*>	m_SpanElements;

public:
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addWidget(CtWidget* pWidget, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	
	bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setWidget(CtWidget* pWidget, short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	
	bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertWidget(CtWidget* pWidget, short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool removeWidget(short Index) {return false;}
	
	bool addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool addContainer(CtContainer* pContainer, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	
	bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool setContainer(CtContainer* pContainer, short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	
	bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, CtAlign Align, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, short Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, CtMargin Margin, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, CtAlign Align, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool insertContainer(CtContainer* pContainer, short Index, const CtSize& Stretch, CtScreenSel Sel = ScreenAll) {return false;}
	bool removeContainer(short Index) {return false;}
	bool removeContainer(CtContainer* pContainer) {return false;}
};

inline CtVector::Vector<CtWidget::Element*>* CtGridLayout::getElements() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_SpanElements;
}

inline CtVector::Vector<CtWidget::Element*>* CtGridLayout::getVisibles() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_SpanElements;
}

#endif
