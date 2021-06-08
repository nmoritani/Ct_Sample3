/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK
 */


#ifndef _CTWINDOW_NETWORK_H_
#define _CTWINDOW_NETWORK_H_

#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtContainerNetwork.h"
#include "CtMenuInfo.h"
#include "CtWindowContentsApInfo.h"


class CtWindow_NETWORK : public CtWindowMain
{
public:
    CtWindow_NETWORK( CtWindowContents* pContents );

    ~CtWindow_NETWORK();

    bool destroyWindow();

    bool setContents(const CtWindowContents* pContents);

    CtWindow* createWindow();

private:   

    CtWindow*           m_pWin;

    CtContainerNetwork*    m_pNet;

    CtWindowContentsApInfo*   m_pContents;


};

#endif

