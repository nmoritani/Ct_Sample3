/* このファイルはWindowID定義データ.xlsmからの自動生成です。 */

#ifndef __CtWindowID_H__
#define __CtWindowID_H__

#define WINDOWID_MAX_NUM 920

enum CtWindowID {
    /* None */
    WindowNone                                                            = 0x00000000,
    
    /* Message */
    WindowSubCategory_Message                                             = 0x02000000,
    WindowSubCategory_Telop                                               = 0x02010000,
    WindowSubCategory_Dialog                                              = 0x02020000,
    WindowSubCategory_SystemError                                         = 0x02100000,
    WindowSubCategory_Warning                                             = 0x02200000,
    WindowSubCategory_Alert                                               = 0x02300000,
    WindowSubCategory_Repair                                              = 0x02400000,
    WindowSubCategory_Other                                               = 0x02500000,
    
    /* Rec */
    WindowMainCategory_Rec                                                = 0x10000000,
    WindowCategory_RecView                                                = 0x11100000,
    Window_RecView,
    Window_TouchNavi,
    Window_RecView_Expand,
    WindowCategory_RecPlayBack                                            = 0x11200000,
    Window_PlayView_RecCheck,
    WindowCategory_RecInfo                                                = 0x11300000,
    Window_Rec_Mode_Check,
    /* Rec Message */
    WindowCategory_RecTelop                                               = 0x12010000,
    WindowCategory_RecDialog                                              = 0x12020000,
    WindowCategory_RecSystemError                                         = 0x12100000,
    WindowCategory_RecWarning                                             = 0x12200000,
    WindowCategory_RecAlert                                               = 0x12300000,
    WindowCategory_RecRepair                                              = 0x12400000,
    
    /* Play */
    WindowMainCategory_Play                                               = 0x20000000,
    WindowCategory_Thumbnail                                              = 0x21100000,
    Window_ThumbNail,
    Window_ThumbNail_Protect,
    Window_ThumbNail_Delete,
    Window_ThumbNail_Copy,
    Window_ThumbNail_Detail,
    Window_ThumbNail_ReConnect,
    WindowCategory_PlayBack                                               = 0x21200000,
    Window_PlayView,
    WindowCategory_ClipInfo                                               = 0x21300000,
    Window_ThumbNailClip,
    WindowCategory_ClipEdit                                               = 0x21400000,
    Window_Deleting,
    Window_Copying,
    Window_DeleteCanceled,
    Window_CopyCanceled,
    Window_CopyComplete,
    Window_DeleteComplete,
    Window_CopyConfirm,
    Window_DeleteConfirm,
    /* Play Message */
    WindowCategory_PlayTelop                                              = 0x22010000,
    WindowCategory_PlayDialog                                             = 0x22020000,
    WindowCategory_PlayWarning                                            = 0x22200000,
    WindowCategory_PlayAlert                                              = 0x22300000,
    
    /* Home */
    WindowMainCategory_Home                                               = 0x30000000,
    WindowCategory_HomeTop                                                = 0x31100000,
    Window_Home,
    WindowCategory_HomeInfo                                               = 0x31200000,
    Window_Info_Diagnostics,
    Window_Info_Switches,
    Window_Info_Version,
    Window_Info_Network,
    Window_Info_Audio,
    Window_Info_Media,
    WindowCategory_HomeFunction                                           = 0x31300000,
    Window_Home_Audio_Top,
    Window_Home_ColorTop,
    Window_Home_EI_TOP,
    Window_Home_Fps_Top,
    Window_Home_Shutter_Top,
    Window_Home_WB_Top,
    
    /* Menu */
    WindowMainCategory_Menu                                               = 0x40000000,
    WindowCategory_Keyboard                                               = 0x41100000,
    #ifdef WIN32_GUI_SIM
        #include "KeyboardWindowId.def"
    #else
        #include "../Window/KEYBOARD/KeyboardWindowId.def"
    #endif
    WindowCategory_Dialog                                                 = 0x41200000,
    #ifdef WIN32_GUI_SIM
        #include "DialogWindowId.def"
    #else
        #include "../Window/MENU/DIALOG/DialogWindowId.def"
    #endif
    WindowCategory_Toggle                                                 = 0x41300000,
    WindowID_Menu_CLOCK_SETTING,
    WindowID_Menu_TC,
    WindowID_Menu_UB,
    WindowID_Menu_TIME_ZONESETTING,
    WindowCategory_SpinBox                                                = 0x41400000,
    #ifdef WIN32_GUI_SIM
        #include "SpinBoxWindowId.def"
    #else
        #include "../Window/MENU/SPINBOX/SpinBoxWindowId.def"
    #endif
    WindowCategory_MenuFile                                               = 0x41500000,
    WindowID_Menu_SCENE_FILE_LOAD,
    WindowID_Menu_SETUP_FILE_LOAD,
    WindowID_Menu_SETUP_FILE_LOAD_MEMORY,
    WindowID_Menu_SCENE_FILE_SAVE,
    WindowID_Menu_SETUP_FILE_SAVE,
    WindowID_Menu_SETUP_FILE_SAVE_MEMORY,
    Window_Menu_SCENE_FILE_LOAD_SCENELIST,
    Window_Menu_SCENE_FILE_LOAD_OVERWRITE,
    Window_Menu_SETUP_FILE_LOAD_OVERWRITE,
    WindowCategory_MenuAreaSetting                                        = 0x41600000,
    WindowID_Menu_AREA_SETTING,
    WindowID_Menu_Area_Setting_Confirm,
    WindowCategory_NetWork                                                = 0x41700000,
    WindowID_Menu_USER_ACCOUNT_DELETE,
    WindowID_Menu_NETWORK_INFRA_SELECT,
    WindowID_Menu_NETWORK_INFO_STATUS,
    WindowID_Menu_NETWORK_INFO_LOG,
    WindowCategory_2List                                                  = 0x41800000,
    WindowID_Menu_COLOR_CORRECTION,
    WindowCategory_OldMenu                                                = 0x41900000,
    WindowID_Menu_NETWORK_SETTINGS,
    WindowID_Menu_USER_ACCOUNT_ENTRY,
    WindowID_Menu_NETWORK_CONNECT_HISTORY,
    WindowID_Menu_NETWORK_TYPE,
    WindowID_Menu_NETWORK_PROPERTY,
    WindowID_Menu_NETWORK_CONNECTION_HISTORY,
    WindowID_Menu_MONITOR_VOL,
    WindowID_Menu_COLOR_SETTING_MAIN,
    WindowID_Menu_FPS_VALUE,
    WindowID_Menu_SHUTTER_DEG_VALUE,
    WindowID_Menu_SHUTTER_SEC_VALUE,
    WindowID_Menu_ISO_SELECT,
    WindowID_Menu_NATIVE_ISO,
    WindowID_Menu_800BASE_ISO,
    WindowID_Menu_3200BASE_ISO,
    WindowID_Menu_GAIN_MODE,
    WindowID_Menu_GAIN_SELECT,
    WindowID_Menu_WHITE_VALUE,
    WindowCategory_MenuOther                                              = 0x41A00000,
    WindowSubCategory_MenuList                                            = 0x41B00000,
    #ifdef WIN32_GUI_SIM
        #include "MenuWindowId.def"
    #else
        #include "../Window/MENU/MenuWindowId.def"
    #endif
    WindowCateogry_MenuMessage                                            = 0x41C00000,
    
    /* Fact */
    WindowMainCategory_Fact                                               = 0x50000000,
    #ifdef WIN32_GUI_SIM
        #include "FactWindowId.def"
    #else
        #include "../Window/FACT/FactWindowId.def"
    #endif
    WindowCategory_FactList                                               = 0x51100000,
    WindowCategory_FactDialog                                             = 0x51200000,
    WindowCategory_KeyTest                                                = 0x51300000,
    WindowCategory_FactTest                                               = 0x51400000,
    WindowCategory_FactOther                                              = 0x51500000,
    
    /* Other */
    WindowMainCategory_Other                                              = 0x60000000,
    WindowCategory_Common                                                 = 0x61100000,
    Window_NULL,
    WindowCategory_AreaSetting                                            = 0x61200000,
    Window_Area_Setting,
    Window_Area_Setting_Confirm,
    WindowCategory_Other                                                  = 0x61300000,
    Window_View_Play_Message,
    Window_CommonMessage,
    Window_WizardMessage,
    WindowID_Menu_UPDATE_COMPLETE,
    WindowCategory_USB                                                    = 0x61400000,
    /* Other Message */
    WindowCategory_OtherTelop                                             = 0x62010000,
    WindowCategory_OtherDialog                                            = 0x62020000,
    
    /* Work */
    WindowMainCategory_Work                                               = 0x70000000,
    WindowCategory_SandBox                                                = 0x71100000,
    Window_001,
    Window_002,
    Window_003,
    Window_004,
    Window_005,
    Window_006,
    Window_007,
    Window_008,
    Window_009,
    Window_010,
    WindowCategory_TransitionA                                            = 0x71200000,
    Window_Test_A_1_1,
    Window_Test_A_1_2,
    Window_Test_A_1_3,
    Window_Test_A_2_1,
    Window_Test_A_2_2,
    Window_Test_A_2_3,
    Window_Test_A_3_1,
    Window_Test_A_3_2,
    Window_Test_A_3_3,
    WindowCategory_TransitionB                                            = 0x71300000,
    Window_Test_B_1_1,
    Window_Test_B_1_2,
    Window_Test_B_1_3,
    Window_Test_B_2_1,
    Window_Test_B_2_2,
    Window_Test_B_2_3,
    Window_Test_B_3_1,
    Window_Test_B_3_2,
    Window_Test_B_3_3,
    WindowCategory_TestMessage                                            = 0x72000000,
    
    /* Message */
    #ifdef WIN32_GUI_SIM
        #include "MessageWindowId.def"
    #else
        #include "../Window/MESSAGE/MessageWindowId.def"
    #endif

    /* MAX */
    WindowID_MAX                                                          = 0xFFFFFFFF,
};

#endif
