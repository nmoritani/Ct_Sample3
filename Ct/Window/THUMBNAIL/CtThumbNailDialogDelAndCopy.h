/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialog_DelAndCopy
 */


#ifndef __CtThumbNailDialog_DelAndCopy_H__
#define __CtThumbNailDialog_DelAndCopy_H__

#include "CtButton.h"
#include "CtWindowCommon.h"
#include "CtContainerBattery.h"
#include "CtContainerIndicateFrame.h"
#include "CtWindowContentsClipInfo.h"
#include "CtWindowContentsThumbConfirm.h"


class CtThumbNailDialog_DelAndCopy : public CtWindowMain 
{
public:


    CtThumbNailDialog_DelAndCopy( CtWindowContents* pContents);
    ~CtThumbNailDialog_DelAndCopy();
    bool handleButtonEvent(const CtEventButton& Button);
    bool setContents(const CtWindowContents* pContents);
	virtual bool handleParamEvent(const CtEventParam& Param);  // パラメーター更新通知
	virtual bool updateContents();
private:   
    CtWindow* createWindow();
    bool destroyWindow();
    CtLayout* createTitle();
    CtLayout* createMessage();
    CtLayout* createProgressBar();
    CtLayout* createControl();
    void updateProgressBar();

    int m_totalValue;
    int m_changeValue;
    int m_percent;

    CtButton *m_pCancel;

    CtLabel *m_pLabel;
    CtLabel *m_pUp;
    CtLabel *m_pDown;

    CtContainerIndicateFrame *m_pProgressBar;

    CtContainerBattery*	m_pBatt;
    CtWindowContentsThumbConfirm* m_pThumb;

    CtWindow *m_pWin;
};

#endif
