/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: __CtFuncID_H__
 */


#ifndef __CtFuncID_H__
#define __CtFuncID_H__

enum CtFuncID {
	FuncID_001,                                      // Common
	FuncID_002,                                      // Common
	FuncID_003,                                      // Common
	FuncID_004,                                      // Common
	FuncID_005,                                      // Common
	FuncID_EXP_UP,                                   // Common
	FuncID_EXP_DOWN,                                 // Common
	FuncID_EXP_LEFT,                                 // Common
	FuncID_EXP_RIGHT,                                // Common
	FuncID_FORMAT_START_SLOT1,                       // Common
	FuncID_FORMAT_START_SLOT2,                       // Common
	FuncID_UPDATE_START,                             // Common
	FuncID_FORMAT_CANCEL,                            // Common
	FuncID_UPDATE_CANCEL,                            // Common
	FuncID_DELETE_EXECUTE,                           // Common
	FuncID_DELETE_CANCEL,                            // Common
	FuncID_ABB_EXECUTE,                              // Common
	FuncID_PROTECT_CANCEL,                           // Common
	FuncID_COPY_EXECUTE,                             // Common
	FuncID_COPY_CANCEL,                              // Common
	FuncID_CLIPINFO_RETURN,                          // Common
	FuncID_FPS_SET,                                  // Common
	FuncID_FPS_EXIT,                                 // Common
	FuncID_DEG_SET,                                  // Common
	FuncID_SEC_SET,                                  // Common
	FuncID_DEG_EXIT,                                 // Common
	FuncID_SEC_EXIT,                                 // Common
	FuncID_WHITE_SET,                                // Common
	FuncID_WHITE_EXIT,                               // Common
	FuncID_WINDOW_CLOSE,                             // Common
	FuncID_SCENE_FILE_SAVE_CONFIRM,                  // Common
	FuncID_SCENE_FILE_SAVE_AS_CONFIRM,               // Common
	FuncID_SCENE_FILE_LOAD_CONFIRM,                  // Common
	FuncID_SETUP_FILE_SAVE_CONFIRM,                  // Common
	FuncID_SETUP_FILE_SAVE_AS_CONFIRM,               // Common
	FuncID_SETUP_FILE_LOAD_CONFIRM,                  // Common
	FuncID_SCENE_FILE_SAVE_OVERWRITE,                // Common
	FuncID_SCENE_FILE_SAVE_AS_OVERWRITE,             // Common
	FuncID_SCENE_FILE_LOAD_OVERWRITE,                // Common
	FuncID_SETUP_FILE_SAVE_OVERWRITE,                // Common
	FuncID_SETUP_FILE_SAVE_AS_OVERWRITE,             // Common
	FuncID_SETUP_FILE_LOAD_OVERWRITE,                // Common
	FuncID_SELECT_FILE_NUMBER,                       // Common
	FuncID_SELECT_SCENE_NUMBER,                      // Common
	FuncID_SET,                                      // Common
	FuncID_UP,                                       // Common
	FuncID_DOWN,                                     // Common
	FuncID_RET,                                      // Common
	FuncID_FORWARD,                                  // Common
	FuncID_BACKWARD,                                 // Common
	FuncID_STOP,                                     // Common
	FuncID_PLAYPAUSE,                                // Common
	FuncID_PLAYNEXT,                                 // Common
	FuncID_PLAYPREV,                                 // Common
	FuncID_PLAYSEEK,                                 // Common
	FuncID_CLIP_COPY_ALL,                            // Common
	FuncID_CLIP_COPY_SELECT,                         // Common
	FuncID_WLANMODE_DIRECT,                          // Common
	FuncID_WLANMODE_INFRA_SELECT,                    // Common
	FuncID_WLANMODE_INFRA_MANUAL,                    // Common
	FuncID_SELECT_AP_NUMBER,                         // Common
	FuncID_SELECT_USER_ACCOUNT_NUMBER,               // Common
	FuncID_USB_RET,                                  // Common
	FuncID_USER8_Press,                              // TouchNavi
	FuncID_USER9_Press,                              // TouchNavi
	FuncID_USER10_Press,                             // TouchNavi
	FuncID_USER11_Press,                             // TouchNavi
	FuncID_USER12_Press,                             // TouchNavi
	FuncID_USER8_Release,                            // TouchNavi
	FuncID_USER9_Release,                            // TouchNavi
	FuncID_USER10_Release,                           // TouchNavi
	FuncID_USER11_Release,                           // TouchNavi
	FuncID_USER12_Release,                           // TouchNavi
	FuncID_WB_MML_DECIDE,                            // MMR
	FuncID_WB_MML_CANCEL,                            // MMR
	FuncID_WB_MML_UP,                                // MMR
	FuncID_WB_MML_DOWN,                              // MMR
	FuncID_WB_MML_UP_LV_2,                           // MMR
	FuncID_WB_MML_DOWN_LV_2,                         // MMR
	FuncID_WB_MML_UP_LV_5,                           // MMR
	FuncID_WB_MML_DOWN_LV_5,                         // MMR
	FuncID_WB_MML_UP_LV_10,                          // MMR
	FuncID_WB_MML_DOWN_LV_10,                        // MMR
	FuncID_SHUTTER_MML_DECIDE,                       // MMR
	FuncID_SHUTTER_MML_CANCEL,                       // MMR
	FuncID_SHUTTER_MML_UP,                           // MMR
	FuncID_SHUTTER_MML_DOWN,                         // MMR
	FuncID_SYNCRO_MML_DECIDE,                        // MMR
	FuncID_SYNCRO_MML_CANCEL,                        // MMR
	FuncID_SYNCRO_MML_UP,                            // MMR
	FuncID_SYNCRO_MML_DOWN,                          // MMR
	FuncID_SYNCRO_MML_UP_LV_2,                       // MMR
	FuncID_SYNCRO_MML_DOWN_LV_2,                     // MMR
	FuncID_SYNCRO_MML_UP_LV_5,                       // MMR
	FuncID_SYNCRO_MML_DOWN_LV_5,                     // MMR
	FuncID_SYNCRO_MML_UP_LV_10,                      // MMR
	FuncID_SYNCRO_MML_DOWN_LV_10,                    // MMR
	FuncID_VFR_MML_DECIDE,                           // MMR
	FuncID_VFR_MML_CANCEL,                           // MMR
	FuncID_VFR_MML_UP,                               // MMR
	FuncID_VFR_MML_DOWN,                             // MMR
	FuncID_AF_AREA_MML_DECIDE,                       // MMR
	FuncID_AF_AREA_MML_CANCEL,                       // MMR
	FuncID_AF_AREA_MML_UP,                           // MMR
	FuncID_AF_AREA_MML_DOWN,                         // MMR
	FuncID_AF_AREA_MML_EXEC,                         // MMR
	FuncID_AREA_MML_UP,                              // MMR
	FuncID_AREA_MML_DOWN,                            // MMR
	FuncID_AREA_MML_DECIDE,                          // MMR
	FuncID_AREA_MML_CANCEL,                          // MMR
	FuncID_AREA_MML_EXEC,                            // MMR
	FuncID_ModeCheckDispPreOn,                       // (ModeCheck画面表示開始事前通知)
	FuncID_ModeCheckDispOn,                          // (ModeCheck画面表示開始通知)
	FuncID_ModeCheckDispOff,                         // (ModeCheck画面非表示開始通知)
	FuncID_TouchNaviDispOn,                          // TouchNavi表示中
	FuncID_TouchNaviDispOff,                         // TouchNavi表示中
	FuncID_Exit_Press,                               // Common
	FuncID_Exit_Release,                             // Common
	FuncID_CLIP_PROTECT,                             // Menu
	FuncID_CLIP_DELETE_ALL,                          // Menu
	FuncID_CLIP_DELETE_SELECT,                       // Menu
	FuncID_CLIP_COPY_ALL_1_2,                        // Menu
	FuncID_CLIP_COPY_ALL_2_1,                        // Menu
	FuncID_CLIP_COPY_SELECT_1_2,                     // Menu
	FuncID_CLIP_COPY_SELECT_2_1,                     // Menu
	FuncID_CLIP_INFO,                                // Menu
	FuncID_UPDATE_CHECK,                             // Menu
	FuncID_LOAD_FACTORY_DATA_START,                  // Menu
	FuncID_DELETE_FPS_VALUE,                         // Menu
	FuncID_DELETE_SHUTTER_DEG_VALUE,                 // Menu
	FuncID_DELETE_SHUTTER_SEC_VALUE,                 // Menu
	FuncID_AWB_EXECUTE,                              // Menu
	FuncID_DELETE_WHITE_VALUE,                       // Menu
	FuncID_SCENE_DATA_LOAD,                          // Menu
	FuncID_SCENE_DATA_SAVE,                          // Menu
	FuncID_SCENE_DATA_INIT,                          // Menu
	FuncID_FORMAT_CHECK_SLOT1,                       // Menu
	FuncID_FORMAT_CHECK_SLOT2,                       // Menu
	FuncID_LEVEL_GAUGE_RESET,                        // Menu
	FuncID_NET_USER_ADD,                             // Menu
	FuncID_NETWORK_CONNECTION_HISTORY,               // Menu
	FuncID_NETWORK_CONNECTION_HISTORY_SELECT,        // Menu
	FuncID_NETWORK_CONNECTION_HISTORY_DELETE,        // Menu
	FuncID_NETWORK_INIT,                             // Menu
	FuncID_FPS_UP,                                   // Menu
	FuncID_FPS_DOWN,                                 // Menu
	FuncID_DEG_UP,                                   // Menu
	FuncID_DEG_DOWN,                                 // Menu
	FuncID_SEC_UP,                                   // Menu
	FuncID_SEC_DOWN,                                 // Menu
	FuncID_WHITE_UP,                                 // Menu
	FuncID_WHITE_DOWN,                               // Menu
	FuncID_WHITE_GMG_UP,                             // Menu
	FuncID_WHITE_GMG_DOWN,                           // Menu
	FuncID_FPS_UP_SKIP,                              // Menu
	FuncID_FPS_DOWN_SKIP,                            // Menu
	FuncID_DEG_UP_SKIP,                              // Menu
	FuncID_DEG_DOWN_SKIP,                            // Menu
	FuncID_SEC_UP_SKIP,                              // Menu
	FuncID_SEC_DOWN_SKIP,                            // Menu
	FuncID_WHITE_UP_SKIP,                            // Menu
	FuncID_WHITE_DOWN_SKIP,                          // Menu
	FuncID_WHITE_GMG_UP_SKIP,                        // Menu
	FuncID_WHITE_GMG_DOWN_SKIP,                      // Menu
	FuncID_SCENE_FILE_SAVE_AS_PUSH_ENTER,            // Menu
	FuncID_SETUP_FILE_SAVE_AS_PUSH_ENTER,            // Menu
	FuncID_REPAIR,                                   // Menu
	FuncID_RE_CONNECT,                               // Menu
	FuncID_USB_MASS_STORAGE,                         // Menu
	FuncID_USB_SERVICE_MODE,                         // Menu
	FuncID_NET_USER_DELETE,                          // Menu
	FuncID_FILE_INITALIZE,                           // MENI > FILE > SETUP FILE(MEMORY) > INITIALIZE 押下時
	FuncID_SETUP_DATA_INIT,                          // OTHERS > FILE > SETUP FILE(MEMORY) > INITIALIZE 押下時
	FuncID_STREAM_DATA_INIT,                         // NETWORK > STREAMING > CLEAR (MEMORY) >YES押下時
	FuncID_NETWORK_ACTIVATE_INIT,                    // NETWORK > NDI|HX > CLEAR ACTIVATION >YES押下時
	FuncID_SETUP_DATA_LOAD,                          // OTHERS > FILE > SETUP FILE(MEMORY) > LOAD 確認画面でSETボタン押下時
	FuncID_SETUP_DATA_SAVE,                          // OTHERS > FILE > SETUP FILE(MEMORY) > SAVE 押下時
	FuncID_STREAM_DATA_LOAD,                         // NETWORK > STREAMING > LOAD (SD CARD) > YES 押下時
	FuncID_STREAM_DATA_SAVE,                         // NETWORK > STREAMING > SAVE (SD CARD) > YES 押下時
	FuncID_NETWORK_DATA_SAVE,                        // NETWORK > INFORMATION > SAVE LOG (SD CARD) 押下時（まだ仕様が固まっていないが）
	FuncID_NET_SSID,                                 // NETWORK > WLAN PROPERTY > SSID 押下時
	FuncID_NET_INFO_STATUS,                          // NETWORK > INFORMATION> STATUS 押下時
	FuncID_NET_INFO_LOG,                             // NETWORK > INFORMATION> LOG 押下時
	FuncID_Window_Close,                             // 画面を閉じたことを通知する
	FuncID_Exit,                                     // Message系WindowでExit押下の通知
	FuncID_NET_LAN_IPv4_DHCP_OFF,                    // NETWORK > LAN PROPERTY > IPv4 SETTING > DHCP
	FuncID_NET_LAN_IPv4_DHCP_CLIENT,                 // NETWORK > LAN PROPERTY > IPv4 SETTING > DHCP
	FuncID_NET_LAN_IPv4_DHCP_SERVER,                 // NETWORK > LAN PROPERTY > IPv4 SETTING > DHCP
	FuncID_NET_LAN_IPv6_DHCP_OFF,                    // NETWORK > LAN PROPERTY > IPv6 SETTING > DHCP
	FuncID_NET_LAN_IPv6_DHCP_CLIENT,                 // NETWORK > LAN PROPERTY > IPv6 SETTING > DHCP
	FuncID_NET_LAN_IPv6_DHCP_SERVER,                 // NETWORK > LAN PROPERTY > IPv6 SETTING > DHCP
	FuncID_NETWORK_DEVICE_SEL_LAN,                   // NETWORK > DEVICE SEL
	FuncID_NETWORK_DEVICE_SEL_WLAN,                  // NETWORK > DEVICE SEL
	FuncID_NETWORK_DEVICE_SEL_CELLULAR,              // NETWORK > DEVICE SEL
	FuncID_NETWORK_DEVICE_SEL_OFF,                   // NETWORK > DEVICE SEL
	FuncID_HOUR_METERS,                              // 
	FuncID_AREA_UP,                                  // AREA操作
	FuncID_AREA_DOWN,                                // AREA操作
	FuncID_AREA_LEFT,                                // AREA操作
	FuncID_AREA_RIGHT,                               // AREA操作
	FuncID_TOUCH_NAVI_SCENE1,                        // 操作アイコン画面 SceneFile1
	FuncID_TOUCH_NAVI_SCENE2,                        // 操作アイコン画面 SceneFile2
	FuncID_TOUCH_NAVI_SCENE3,                        // 操作アイコン画面 SceneFile3
	FuncID_TOUCH_NAVI_SCENE4,                        // 操作アイコン画面 SceneFile4
	FuncID_TOUCH_NAVI_SCENE5,                        // 操作アイコン画面 SceneFile5
	FuncID_TOUCH_NAVI_SCENE6,                        // 操作アイコン画面 SceneFile6
	FuncID_NETWORK_FUNC_FTP_CLIENT,                  // NETWORK > NETWORK FUNC
	FuncID_NETWORK_FUNC_STREAMING,                   // NETWORK > NETWORK FUNC
	FuncID_NETWORK_FUNC_NDI_HX,                      // NETWORK > NETWORK FUNC
	FuncID_NETWORK_FUNC_OFF,                         // NETWORK > NETWORK FUNC
	FuncID_CAPTURE,                                  // PB画面CAPTURE押下
	FuncID_ICONS,                                    // 操作アイコン画面の表示要求
	FuncID_NETWORK_LAN_IP_ADDRESS_V6,                // NETWORK > LAN PROPERTY > IPv6 SETTING > IP ADDRESS
	FuncID_NETWORK_LAN_DEFAULT_GATEWAY_V6,           // NETWORK > LAN PROPERTY > IPv6 SETTING > DEFAULT GATEWAY
	FuncID_NETWORK_LAN_PRIMARY_DNS_V6,               // NETWORK > LAN PROPERTY > IPv6 SETTING > PRIMARY DNS
	FuncID_NETWORK_LAN_SECONDARY_DNS_V6,             // NETWORK > LAN PROPERTY > IPv6 SETTING > SECONDARY DNS
	FuncID_NETWORK_WLAN_IP_ADDRESS_V6,               // NETWORK > WLAN PROPERTY > IPv6 SETTING > IP ADDRESS
	FuncID_NETWORK_WLAN_DEFAULT_GATEWAY_V6,          // NETWORK > WLAN PROPERTY > IPv6 SETTING > DEFAULT GATEWAY
	FuncID_NETWORK_WLAN_PRIMARY_DNS_V6,              // NETWORK > WLAN PROPERTY > IPv6 SETTING > PRIMARY DNS
	FuncID_NETWORK_WLAN_SECONDARY_DNS_V6,            // NETWORK > WLAN PROPERTY > IPv6 SETTING > SECONDARY DNS
#ifdef WIN32_GUI_SIM
	#include "FactFuncId.def"
#else
	#include "../Window/FACT/FactFuncId.def"
#endif
	FuncID_ALL,
	FuncID_MAX
};

#endif
