/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMenuBuilder
 */


#ifndef __CtMenuBuilder_H__
#define __CtMenuBuilder_H__

#include "CtWindow.h"
#include "CtWindowCommon.h"
#include "CtMenuInfo.h"

//#include "CtMenuInfoWindow.h"

//#include "CtContainerMenu.h"
//#include "CtMenuInfoDesign.h"
//#include "AplParamService.h"
//#include "CtWindowContentsDialogParamSet.h"
//#include "CtContainerMenuCheck.h"

#include "CtMenuButton.h"
#include "CtMenuCheckButton.h"
#include "CtParamIcon.h"
#include "CtMenuListView.h"

#include "CtWindowContentsMenuPos.h"
#include "CtWindowContentsDialogParamSet.h"

#include "CtContainerSpecialLabel.h"

class CtMenuBuilder : public CtObject
{
public:
	CtMenuBuilder();
	~CtMenuBuilder();
	inline void setWindowID(CtWindowID id);

	CtListView* createMenuList(int num, bool bExit);

	CtButton* createExitButton();
	CtButton* createMenuButton(CtMenuInfo::CtMenuButtonInfo* pButtonInfo);
	CtLayout* createMenuButtonLayout(CtMenuInfo::CtMenuButtonInfo* pButtonInfo);
	CtLayout* createMenuButtonLayout_Value(CtMenuInfo::CtMenuButtonInfo* pInfo);

	inline short getTotalWidth();
	inline void setOldWidth(int width);
private:
	void setWidthSize();



private:

	CtWindowID			    m_WindowId;
	int m_OldWidth;
	short m_TotalWidth;
	short m_LabelWidth;
	short m_ValueWidth;

	bool m_bArrow;
};

inline void CtMenuBuilder::setWindowID(CtWindowID Id) {
	m_WindowId = Id;
}

inline void CtMenuBuilder::setOldWidth(int width) {
	m_OldWidth = width;
}

inline short CtMenuBuilder::getTotalWidth() {
	return m_TotalWidth;
}


#endif
