/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtListView
 */


#ifndef __CtGridView_H__
#define __CtGridView_H__

#include "CtListView.h"

class CtGridView : public CtListView {
public :

	CtGridView();
	CtGridView(int ViewRow, int ViewColumn);
	CtGridView(int ViewRow, int ViewColumn, const CtColor& Color);
	CtGridView(int ViewRow, int ViewColumn, const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtGridView(int ViewRow, int ViewColumn, const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~CtGridView();

	virtual bool moveFocus(const CtDirection Dir, bool Silent);

	inline virtual bool isListView() const;
	inline virtual bool isGridView() const;

	bool setViewColumn(short ViewColumn);
	int getViewColumn() const;

	bool setLayout(int Screen = 0);
	
protected :
	//	virtual void setProperty();

private:
	
public:
};

inline bool CtGridView::isListView() const
{
	return true;
}
inline bool CtGridView::isGridView() const
{
	return true;
}


#endif
