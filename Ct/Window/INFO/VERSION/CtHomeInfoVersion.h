/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */

#ifndef __CtHomeInfoVersion_H__
#define __CtHomeInfoVersion_H__

#include "CtWindowCommon.h"
#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtHomeInfoVersion : public CtWindowMain
{
public:
    CtHomeInfoVersion();

    ~CtHomeInfoVersion();

    virtual bool handleKeyEvent(const CtEventKey& Key);

    virtual bool handleTouchEvent(const CtEventTouch& Touch);

private:
    CtWindow* createWindow();
    bool destroyWindow();

    CtContainer *m_pInfoboxTop;
    CtContainer *m_pInfoboxBottom;
    CtContainer *m_pInfoboxMiddle;

    CtLayout *m_Middle;
    CtLayout *m_Bottom;
    CtVLayout *m_pAll;

    bool m_TouchPress;

    CtWindow *m_pWin;
};


#endif
