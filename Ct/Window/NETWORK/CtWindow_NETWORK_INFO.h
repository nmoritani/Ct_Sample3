/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_NETWORK_INFO
 */


#ifndef _CtWindow_NETWORK_INFO_H_
#define _CtWindow_NETWORK_INFO_H_

#include "CtWindowCommon.h"
#include "CtWindowContentsNetworkInformation.h"

#include "CtContainerMenuTitle.h"
#include "CtContainerCtrlButton.h"

#define LINE_NUM  13

class CtWindow_NETWORK_INFO : public CtWindowMain
{
public:
    CtWindow_NETWORK_INFO( CtWindowContents* pContents );

    ~CtWindow_NETWORK_INFO();

    bool destroyWindow();

    bool setContents(const CtWindowContents* pContents);

    CtWindow* createWindow();

	bool handleButtonEvent(const CtEventButton& Button);

    bool handleKeyEvent(const CtEventKey& Key);

protected:
	virtual bool executionUp();
	virtual bool executionDown();
	virtual bool executionRet();

	void updateWindow();
	bool updateContents();

private:
	CtLayout* createNetworkInfo();

private:

	CtWindowContentsNetworkInformation*   m_pContents;
	CtLabel*	m_pLabel[LINE_NUM];
	CtContainerCtrlButton*	m_pCtrl;
};

#endif

