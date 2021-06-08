/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtDraw
*/

#ifndef __CtWindwoDecorate_H__
#define __CtWindwoDecorate_H__

#include "CtObject.h"
#include "CtVector.h"

#include "CtWindowMain.h"
#include "CtWindowMenu.h"


class CtWindowDecorate : public CtObject
{
private:
	typedef CtVector::Vector<CtWindowMain*> WindowArray;

public:
	CtWindowDecorate() {};
	virtual ~CtWindowDecorate() {};

	static bool requestDecorate(WindowArray* pWindows, int Screen = 0);

	static bool isThumbnail(int Screen = 0);

private:
	static bool decorateInvisible(WindowArray* pWindows, int Screen = 0);
	static bool decorateMenu(WindowArray* pWindows, int Screen = 0);

	static bool setVisible(CtWindowMain* pWin, bool bVisible);
	static bool isInvisibleCheck_RecView(CtWindowMain* pNext);
	static bool isInvisibleCheck_Menu(CtWindowMain* pNext);

private:

};

#endif
