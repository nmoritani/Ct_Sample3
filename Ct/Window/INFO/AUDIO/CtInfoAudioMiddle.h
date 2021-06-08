/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoAudioMiddle_H__
#define __CtInfoAudioMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoAudioMiddle : public CtContainer {
public :
    CtInfoAudioMiddle();

    virtual ~CtInfoAudioMiddle();

    CtLayout* createContainer();
	bool destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :

    void createInfoAudioStackLabel();

    void updateCH1Selet();
    void updateCH2Selet();
    void updateCH1Level();
    void updateCH2Level();
    void updateHeadRoom();
    void updateMonitor();

    CtLayout *m_pBox;
    CtStackLabel *m_pSLabelSelectCH1;
    CtStackLabel *m_pSLabelInput1;
    CtStackLabel *m_pSLabelMicPower1;
    CtStackLabel *m_pSLabelMicGain1;
    CtStackLabel *m_pSLabelLowCut1;
    CtStackLabel *m_pSLabelInputCH1;
    CtStackLabel *m_pSLabelSelectCH2;
    CtStackLabel *m_pSLabelInput2;
    CtStackLabel *m_pSLabelMicPower2;
    CtStackLabel *m_pSLabelMicGain2;
    CtStackLabel *m_pSLabelLowCut2;
    CtStackLabel *m_pSLabelInputCH2;
    CtStackLabel *m_pSLabelCh1Adjust;
    CtStackLabel *m_pSLabelLimiterCH1;
    CtStackLabel *m_pSLabelCh2Adjust;
    CtStackLabel *m_pSLabelLimiterCH2;
    CtStackLabel *m_pSLabelHeadRoom;
    CtStackLabel *m_pSLabelHpOut;
    CtStackLabel *m_pSLabelHpMode;
    CtStackLabel *m_pSLabelVolume;

    CtHLayout *m_pCH1Selet;
    CtLayout *m_pCH1SeletMicOrLine;
    CtHLayout *m_pCH1SeletMic;
    CtHLayout *m_pCH1SeletLowCut;

    CtHLayout *m_pCH2Selet;
    CtLayout *m_pCH2SeletMicOrLine;
    CtHLayout *m_pCH2SeletMic;
    CtHLayout *m_pCH2SeletLowCut;

    CtHLayout *m_pCH1Level;
    CtHLayout *m_pCH1LevelManual;

    CtHLayout *m_pCH2Level;
    CtHLayout *m_pCH2LevelManual;

    CtHLayout *m_pHeadRoom;

    CtLabel *m_pVolume;

};


#endif
