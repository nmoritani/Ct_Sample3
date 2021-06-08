/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */

#ifndef __CtHomeInfoDiagnostics_H__
#define __CtHomeInfoDiagnostics_H__

#include "CtWindowCommon.h"
#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"

class CtHomeInfoDiagnostics : public CtWindowMain
{
public:
    CtHomeInfoDiagnostics();

    ~CtHomeInfoDiagnostics();

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
