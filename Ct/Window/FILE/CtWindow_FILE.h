/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_FILE
 */


#ifndef _CTWINDOW_FILE_H_
#define _CTWINDOW_FILE_H_

#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtContainerFile.h"
#include "CtWindowContentsFileInfo.h"
#include "CtMenuInfo.h"

class CtWindow_FILE : public CtWindowMain
{
public:
    CtWindow_FILE( CtWindowContents* pContents );

    ~CtWindow_FILE();

    bool destroyWindow();

    bool setContents(const CtWindowContents* pContents);

    virtual bool updateContents();

    CtWindow* createWindow();

private:

    CtWindow*           m_pWin;

    CtContainerFile*    m_pFile;

    CtLayout*           m_pPage;

    CtWindowContentsFileInfo*   m_pContentsFile;

};

#endif

