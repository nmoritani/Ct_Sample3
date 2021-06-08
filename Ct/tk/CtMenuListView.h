/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMenuListView
 */


#ifndef __CtMenuListView_H__
#define __CtMenuListView_H__

#include "CtListView.h"

class CtMenuListView : public CtListView {
public :
	CtMenuListView();
	CtMenuListView(short ViewRow);
	CtMenuListView(short ViewRow, const CtColor& Color);
	CtMenuListView(short ViewRow, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtMenuListView(short ViewRow, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~CtMenuListView();
	
	void setLeftKeyAction(bool bValid);
	
	virtual bool setCurrentElement(int Element, bool bEnd = false);
	virtual bool nextElement();
	virtual bool prevElement();
	
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	
protected :
	CtMenuListView(short ViewRow, short ViewColumn);
	CtMenuListView(short ViewRow, short ViewColumn, const CtColor& Color);
	CtMenuListView(short ViewRow, short ViewColumn, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtMenuListView(short ViewRow, short ViewColumn, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	
	virtual bool isValidElement(int Element);
	virtual bool isValidElement(CtWidget::Element* pElement);
	virtual bool isSelectableElement(int Element);
	virtual bool isSelectableElement(CtWidget::Element* pElement);
	virtual int getValidElementsNum(int Element = -1);
	
private:
	void ctor();
	
	bool		m_bLeftKeyAction;
};
	
inline void CtMenuListView::setLeftKeyAction(bool bValid)
{
	m_bLeftKeyAction = bValid;
}

#endif
