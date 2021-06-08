/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamMainValueCheck
 */


#ifndef Foundation_Manager_AplParamMainValueCheck_H
#define Foundation_Manager_AplParamMainValueCheck_H

#include <oxf.h>
#include "AplObject.h"
class AplIfSys;

class AplParamService;

//## package Foundation::Manager

//## class AplParamMainValueCheck
class AplParamMainValueCheck : public AplObject {
public :

    typedef enum AplParamItemState {
        AplParamItemState_VisibleValid,
        AplParamItemState_VisibleInvalid,
        AplParamItemState_Invisible,
        AplParamItemState_End
    } AplParamItemState;
    
    ////    Constructors and destructors    ////
    
    //## operation AplParamMainValueCheck()
    AplParamMainValueCheck();
    
    ~AplParamMainValueCheck();
    
    ////    Operations    ////
    
    //## operation valueCheck(int,int)
    AplParamItemState valueCheck(int id, int value);

private :

    //## operation checkAplParamPlayBackMenu(int)
    AplParamItemState checkAplParamPlayBackMenu(int value);
    
    //## operation checkAplParamClipMenu(int)
    AplParamItemState checkAplParamClipMenu(int value);
    
    //## operation checkAplParamThumbDisplayMenu(int)
    AplParamItemState checkAplParamThumbDisplayMenu(int value);
    
    //## operation checkAplParamAudioChSettingsMenu(int)
    AplParamItemState checkAplParamAudioChSettingsMenu(int value);
    
    //## operation checkAplParamSdiOutMenu(int)
    AplParamItemState checkAplParamSdiOutMenu(int value);
    
    //## operation checkAplParamHdmiOutMenu(int)
    AplParamItemState checkAplParamHdmiOutMenu(int value);
    
    //## operation checkAplParamRecordingMenu(int)
    AplParamItemState checkAplParamRecordingMenu(int value);
    
    //## operation checkAplParamRecFunctionMenu(int)
    AplParamItemState checkAplParamRecFunctionMenu(int value);
    
    //## operation checkAplParamTCUBMenu(int)
    AplParamItemState checkAplParamTCUBMenu(int value);
    
    //## operation checkAplParamSystemMenu(int)
    AplParamItemState checkAplParamSystemMenu(int value);
    
    //## operation checkAplParamPlaySlot(int)
    AplParamItemState checkAplParamPlaySlot(int value);
    
    //## operation checkAplParamRecFunctionMode(int)
    AplParamItemState checkAplParamRecFunctionMode(int value);
    
    //## operation checkAplParamRecFormat59Hz(int)
    AplParamItemState checkAplParamRecFormat59Hz(int value);
    
    //## operation checkAplParamRecFormat50Hz(int)
    AplParamItemState checkAplParamRecFormat50Hz(int value);
    
    //## operation checkAplParamSuperGain(int)
    AplParamItemState checkAplParamSuperGain(int value);
    
    //## operation checkAplParamOisMode(int)
    AplParamItemState checkAplParamOisMode(int value);
    
    //## operation checkAplParamAgcMax(int)
    AplParamItemState checkAplParamAgcMax(int value);
    
    //## operation checkAplParamAutoShutterLimit(int)
    AplParamItemState checkAplParamAutoShutterLimit(int value);
    
    //## operation checkAplParamSceneMatrix(int)
    AplParamItemState checkAplParamSceneMatrix(int value);
    
    //## operation checkAplParamSdiOutFormat(int)
    AplParamItemState checkAplParamSdiOutFormat(int value);
    
    //## operation checkAplParamHdmiOutFormat(int)
    AplParamItemState checkAplParamHdmiOutFormat(int value);
    
    //## operation checkAplParamLcdMarkerFrameMarker(int)
    AplParamItemState checkAplParamLcdMarkerFrameMarker(int value);
    
    //## operation checkAplParamLcdFocusExpandMonocrome(int)
    AplParamItemState checkAplParamLcdFocusExpandMonocrome(int value);
    
    //## operation checkAplParamRelayBackup(int)
    AplParamItemState checkAplParamRelayBackup(int value);
    
    //## operation checkAplParamColorbarType(int)
    AplParamItemState checkAplParamColorbarType(int value);
    
    //## operation checkAplParamLanguage(int)
    AplParamItemState checkAplParamLanguage(int value);
    
    //## operation checkAplParamUserButton(int)
    AplParamItemState checkAplParamUserButton(int value);
    
    //## operation checkAplParamFocusAssist(int)
    AplParamItemState checkAplParamFocusAssist(int value);
    
    //## operation checkAplParamFileMenu(int)
    AplParamItemState checkAplParamFileMenu(int value);
    
    //## operation inVisibleVerNoneK518()
    AplParamItemState inVisibleVerNoneK518();
    
    //## operation inVisibleVerNone()
    AplParamItemState inVisibleVerNone();
    
    //## operation inVisibleK518()
    AplParamItemState inVisibleK518();
};

#endif
