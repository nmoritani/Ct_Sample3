/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_TransitionTest
 */


#ifndef __CtWindow_TransitionTest_H__
#define __CtWindow_TransitionTest_H__

#include "CtWindowCommon.h"
class CtWindow_TransitionTest : public CtWindowMain
{
public:
	CtWindow_TransitionTest();
	~CtWindow_TransitionTest();

private:
	CtWindow* createWindow();
	bool destroyWindow();

	CtWindow* m_pWin;


// ===== Builder =====
private:
	typedef struct TransitionInfo {
		CtWindowID	WinId;
		char*       Str;
		int         Row;
		int         Column;
	}TransitionInfo;

	TransitionInfo* getInfo(CtWindowID id);
	CtLayout* createLayout();

	// ÉeÅ[ÉuÉãèÓïÒ
	static TransitionInfo Table[];


};

#endif
