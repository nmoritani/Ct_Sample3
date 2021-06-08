/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtHLayout
 */


#include "CtGridView.h"
#include "CtLayout.h"

CtGridView::CtGridView() :
	CtListView(3, 3)
{
	setClassType(CtClassType_GridView);
	setLayoutType(LayoutGrid);
}

CtGridView::CtGridView(int ViewRow, int ViewColumn) :
	CtListView(ViewRow, ViewColumn)
{
	setClassType(CtClassType_GridView);
	setLayoutType(LayoutGrid);
}

CtGridView::CtGridView(int ViewRow, int ViewColumn, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Color)
{
	setClassType(CtClassType_GridView);
	setLayoutType(LayoutGrid);
}

CtGridView::CtGridView(int ViewRow, int ViewColumn, const CtSize& Size, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Size, Color)
{
	setClassType(CtClassType_GridView);
	setLayoutType(LayoutGrid);
}

CtGridView::CtGridView(int ViewRow, int ViewColumn, const CtRegion& Region, const CtColor& Color) :
	CtListView(ViewRow, ViewColumn, Region, Color)
{
	setClassType(CtClassType_GridView);
	setLayoutType(LayoutGrid);
}

CtGridView::~CtGridView()
{
}

bool CtGridView::setViewColumn(short ViewColumn)
{
	bool bRet = false;
	
	if (m_ViewColumn == ViewColumn)
		return bRet;

	if (m_ViewColumn > ViewColumn) {
		for (int i = m_ViewRow * m_ViewColumn; i < m_Visibles.size(); i++) {
			m_Visibles[i] = NULL;
			if (m_Blanks[i] != NULL)
				delete m_Blanks[i];
		}
		m_ViewColumn = ViewColumn;
		m_Visibles.resize(m_ViewRow * m_ViewColumn);
		m_Blanks.resize(m_ViewRow * m_ViewColumn);
		bRet = true;
		
	} else if (m_ViewColumn < ViewColumn) {
		m_Visibles.resize(m_ViewRow * ViewColumn);
		m_Blanks.resize(m_ViewRow * ViewColumn);
		for (int i = m_ViewRow * m_ViewColumn; i < m_Visibles.size(); i++) {
			m_Blanks[i] = new CtLayout::SplitElement(new CtLabel(), DefaultMargin, DefaultAlign, 1);
			m_Blanks[i]->Index = -1;
			m_Visibles[i] = m_Blanks[i];
		}
		m_ViewColumn = ViewColumn;
		bRet = true;
	}
	return bRet;
}

int CtGridView::getViewColumn() const
{
	return m_ViewColumn;
}

bool CtGridView::moveFocus(const CtDirection Dir, bool Silent)
{
	int element = 0;
	
	switch (Dir) {
	case DirUp:
		if (isValidElement(m_CurrentElement - m_ViewColumn) == true)
			return setCurrentElement(m_CurrentElement - m_ViewColumn);
		break;
	case DirDown:
		if (isValidElement(m_CurrentElement + m_ViewColumn) == true)
			return setCurrentElement(m_CurrentElement + m_ViewColumn);
		break;
	case DirRight:
		return nextElement();
	case DirLeft:
		return prevElement();
	default:
		break;
	}
	return false;
}

bool CtGridView::setLayout(int Screen)
{
	return setGridLayout(m_ViewRow, m_ViewColumn, Screen);
}
