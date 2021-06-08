/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			Ct2ListView
 */


#ifndef __Ct2ListView_H__
#define __Ct2ListView_H__

#include "CtListView.h"

class Ct2ListView : public CtListView {
public :
	Ct2ListView();
	Ct2ListView(short ViewRow);
	Ct2ListView(short ViewRow, const CtColor& Color);
	Ct2ListView(short ViewRow, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	Ct2ListView(short ViewRow, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~Ct2ListView();
	

	virtual bool nextElement();
	virtual bool prevElement();

	virtual bool setFocusInElement(CtWidget* pWidget, bool bEnd = false);
	virtual bool cancelFocusInElement(CtWidget* pWidget);
	virtual CtWidget* getFocusWidget();
	virtual bool moveFocus(const CtDirection Dir, bool Silent);
	virtual bool dialFocus(const bool bPlus, bool Silent);

	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);

	void setColumn(int column);

protected :
	Ct2ListView(short ViewRow, short ViewColumn);
	Ct2ListView(short ViewRow, short ViewColumn, const CtColor& Color);
	Ct2ListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	Ct2ListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	
	void ctor(short Row, short Column = 1);

private:
	int m_ViewColumn2;
	int m_FocusPos;
	bool m_bScrollColumn;
	bool m_bDialPress;

};

inline void Ct2ListView::setColumn(int column)
{
	m_ViewColumn2 = column;
}

#endif
