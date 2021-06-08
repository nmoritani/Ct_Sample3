/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtGridLayout
 */


#include "CtGridLayout.h"

void CtGridLayout::ctor(short Row, short Column)
{
	setLayoutType(LayoutGrid);
	
	m_RowNum = Row;
	m_ColumnNum = Column;
	
	m_Elements.resize(m_RowNum * m_ColumnNum);
	for (int i = 0; i< m_Elements.size(); i++) {
		m_Elements[i] = NULL;
	}
}

CtGridLayout::CtGridLayout()
{
	ctor(3, 3);
}

CtGridLayout::CtGridLayout(const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	ctor(3, 3);
}

CtGridLayout::CtGridLayout(const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	ctor(3, 3);
}

CtGridLayout::CtGridLayout(short Row, short Column)
{
	ctor(Row, Column);
}

CtGridLayout::CtGridLayout(short Row, short Column, const CtColor& Color) :
	CtLayout(Color)
{
	ctor(Row, Column);
}

CtGridLayout::CtGridLayout(short Row, short Column, const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	ctor(Row, Column);
}

CtGridLayout::CtGridLayout(short Row, short Column, const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	ctor(Row, Column);
}

CtGridLayout::~CtGridLayout()
{
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	
	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return;
		
	for (int i = 0; i< pElements->size(); i++) {
		if ((*pElements)[i] != NULL) {
			delete (*pElements)[i];
		}
	}
	pElements->clear();
}

bool CtGridLayout::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan)
{
	CtVector::Vector<CtLayout::Element*>* pElements = getElements();
	
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
    pElements->push_back(new SpanElement(pWidget, Margin, Align, RowSpan, ColumnSpan));/* pgr0541 */
	(*pElements)[pElements->size() -1]->Index = pElements->size() -1;
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}

	return true;
}

bool CtGridLayout::addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align)
{
	return addWidget(pWidget, Margin, Align, 1, 1);
}

bool CtGridLayout::addWidget(CtWidget* pWidget, CtMargin Margin)
{
	return addWidget(pWidget, Margin, AlignCenter, 1, 1);
}

bool CtGridLayout::addWidget(CtWidget* pWidget, CtAlign Align)
{
	return addWidget(pWidget, DefaultMargin, Align, 1, 1);
}

bool CtGridLayout::addWidget(CtWidget* pWidget)
{
	return addWidget(pWidget, DefaultMargin, AlignCenter, 1, 1);
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Index, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan)
{
	CtVector::Vector<CtLayout::Element*>* pElements = getElements();
	
	if (pWidget != NULL) {
		pWidget->setParent(this);
	}
	
	if (pElements->size() > Index) {
		if ((*pElements)[Index] != NULL) {
			if ((*pElements)[Index]->pWidget != pWidget) {
				delete (*pElements)[Index];
				(*pElements)[Index] = NULL;
			}
		}
	} else {
		pElements->resize(Index+1);
		for (int i = pElements->size(); i <= Index; i++) {
			(*pElements)[i] = NULL;
		}
	}

	if ((*pElements)[Index] == NULL) {
		(*pElements)[Index] = new SpanElement(pWidget, Margin, Align, RowSpan, ColumnSpan);	/* pgr0541 */
	}
	
	(*pElements)[Index]->Index = Index;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	
	return true;
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, CtAlign Align)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, Margin, Align, 1, 1);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, DefaultMargin, AlignCenter, 1, 1);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtAlign Align)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, DefaultMargin, Align, 1, 1);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, Margin, AlignCenter, 1, 1);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, short RowSpan, short ColumnSpan)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, DefaultMargin, AlignCenter, 1, 1);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtAlign Align, short RowSpan, short ColumnSpan)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, DefaultMargin, Align, RowSpan, ColumnSpan);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, short RowSpan, short ColumnSpan)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, Margin, AlignCenter, RowSpan, ColumnSpan);	/* pgr0397 */
}

bool CtGridLayout::setWidget(CtWidget* pWidget, short Row, short Column, CtMargin Margin, CtAlign Align, short RowSpan, short ColumnSpan)
{
	return setWidget(pWidget, (Row * m_ColumnNum) +Column, Margin, Align, RowSpan, ColumnSpan);	/* pgr0397 */
}

bool CtGridLayout::removeWidget(CtWidget* pWidget)
{
	return false;
}

bool CtGridLayout::removeWidget(short Row, short Column)
{
	return false;
}

bool CtGridLayout::setLayout(int Screen)
{
	return CtLayout::setGridLayout(m_RowNum, m_ColumnNum, Screen);
}

