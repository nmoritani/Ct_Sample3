/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_007
 */


#ifndef __CtWindowHome_WBTop_H__
#define __CtWindowHome_WBTop_H__

#include "CtWindowCommon.h"

class CtWindowHome_WBTop : public CtWindowMain
{
public:
	CtWindowHome_WBTop();

private:
	CtWindow* createWindow();

	CtColor m_ImageColor;
	CtColor m_LabelColor;
	CtColor m_LineColor;
	
	CtWindow* m_pWin;
};

#endif
