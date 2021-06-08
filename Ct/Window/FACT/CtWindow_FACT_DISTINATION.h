/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_FACT_DISTINATION
 */


#ifndef _CtWindow_FACT_DISTINATION_H_
#define _CtWindow_FACT_DISTINATION_H_

#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtContainerFactDistination.h"
#include "CtMenuInfo.h"
#include "CtWindowContentsFactDistination.h"

class CtWindow_FACT_DISTINATION : public CtWindowMain
{
public:
    CtWindow_FACT_DISTINATION( CtWindowContents* pContents );

    ~CtWindow_FACT_DISTINATION();

    bool destroyWindow();

    bool setContents(const CtWindowContents* pContents);

    virtual bool updateContents();

    CtWindow* createWindow();

private:   

    CtWindow*           m_pWin;

    CtContainerFactDistination*    m_pNet;

    CtWindowContentsFactDistination*   m_pContents;

};

#endif

