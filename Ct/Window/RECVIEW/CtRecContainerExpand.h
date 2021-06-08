/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtRecContainerExpand_H__
#define __CtRecContainerExpand_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtWindowMain.h"
#include "CtListView.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "CtGridLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"
#include "CtViewDesign.h"


class CtRecContainerExpand : public CtContainer
{
/*******************
  íËêî 
*******************/
public:
	
	typedef enum ExpandIndex{
		ExpandIndex_Up,
		ExpandIndex_Down,
		ExpandIndex_Left,
		ExpandIndex_Right,
	}ExpandIndex;
	
	typedef struct ExpandPos{
		int now;
		int next[4];
	}ExpandPos;

public:
	CtRecContainerExpand();
	~CtRecContainerExpand();
	CtLayout* createContainer();
	CtLayout* createExpandView();
	CtLayout* createExpandMarker();
	virtual bool destroyWindow();

	/* ÉCÉxÉìÉgèàóù */
	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);

private :
	int getExpandMarkerSizeW();
	int getExpandMarkerSizeH();
	void updateExpand();
	
	void getExpandCenterPos(int* x, int* y);
	int getExpandXPos();
	int getExpandYPos();
	void setNextPos(ExpandIndex next);
	
protected :
	

private :
	static ExpandPos Pos[];
	
    CtWindow *m_pWin;
    
	CtButton *m_pUp;
	CtButton *m_pDown;
	CtButton *m_pLeft;
	CtButton *m_pRight;
	
	CtLayout *m_pMarker;
	CtLabel *m_pMarkerRect;
	CtLayout *m_pAll;
	
protected :

};


#endif /* __CtMenuButtonList_H__ */

