/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_SceneList
 */


#ifndef _CtWindow_SceneList_H_
#define _CtWindow_SceneList_H_

#include "CtWindowCommon.h"
#include "CtWindowContentsFileInfo.h"
#include "CtMenuInfo.h"
#include "CtWindowContentsSelectSceneInfo.h"
#include "CtMenuButton.h"
#include "CtMenuListView.h"
#include "CtContainerCtrlButton.h"
#include "CtContainerMenuTitle.h"


class CtWindow_SceneList : public CtWindowMain
{
public:
    CtWindow_SceneList();

    ~CtWindow_SceneList();

    bool destroyWindow();

    CtWindow* createWindow();

	bool handleButtonEvent(const CtEventButton& Button);

	bool handleKeyEvent(const CtEventKey& Key);

	bool handleParamEvent(const CtEventParam& Param);

private:

	void            update_SceneList(int int_Data);

private:

	CtWindow*           m_pWin;

    CtLayout*           m_pPage;

    CtWindowContentsFileInfo*   m_pContentsFile;

	CtButton*				m_pSceneBtn[7];

};

#endif

