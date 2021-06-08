/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK_USER
 */


#ifndef _CtWindow_NETWORK_USER_H_
#define _CtWindow_NETWORK_USER_H_

#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtContainerNetworkUser.h"
#include "CtMenuInfo.h"
#include "CtWindowContentsUserInfo.h"

class CtWindow_NETWORK_USER : public CtWindowMain
{
public:
    CtWindow_NETWORK_USER( CtWindowContents* pContents );

    ~CtWindow_NETWORK_USER();

    bool destroyWindow();

	virtual bool setContents(const CtWindowContents* pContents);
	virtual bool updateContents();

    CtWindow* createWindow();

private:   

    CtWindow*           m_pWin;

    CtContainerNetworkUser*    m_pNet;

    CtLayout*           m_pPage;

    CtWindowContentsUserInfo*   m_pContents;

};

#endif

