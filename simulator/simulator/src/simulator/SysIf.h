/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   SYSブロック ヘッダーファイル (シミュレーター用)
 */
#ifndef _SIM_IF_H_
#define _SIM_IF_H_

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* 環境によってあったりなかったりするので */
	typedef int BOOL;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

/* キーイベント */
#define SYS_EVENT_KEY_STATUS_CHANGED	2000
#define SYS_EVENT_TPANEL_RELEASED		4000
#define SYS_EVENT_TPANEL_TOUCHED		4001
#define SYS_EVENT_TPANEL_DRAG			4002
#define SYS_EVENT_TPANEL_SLIDE			4009

#define SYS_POWER_INIT_MODE             0x00                  //!< 起動から電源モード判定完了までの期間
#define SYS_POWER_RESET_MODE            0x01                  //!< 再起動待ちモード
#define SYS_POWER_ON_MODE               0x02                  //!< 電源ONモード
#define SYS_POWER_ON_INIT_MODE          0x03                  //!< 電源ONモード(BE起動処理中)
#define SYS_POWER_ON_TERM_MODE          0x04                  //!< 電源ONモード(BE終了処理中)
#define SYS_POWER_OFF_MODE              0x05                  //!< 電源OFFモード
#define SYS_POWER_HALT_MODE             0x06                  //!< HALTモード
#define SYS_POWER_UPDATE_MODE           0x07                  //!< アップデートモード
#define SYS_PON_SYS_WATCH_MODE          0x00                  //!< シスコン監視モード
#define SYS_PON_APL_WATCH_MODE          0x01                  //!< アプリ監視モード
#define SYS_REMO_PON_NO_CHANGE          0x00                  //!< 設定変更なし
#define SYS_REMO_PON_MP                 0x01                  //!< マリンパックの電源ＳＷ有効
#define SYS_REMO_PON_MP_REMO            0x02                  //!< マリンパックとリモコンの電源ＳＷ有効
#define SYS_REMO_RELEASE                0x00FF                //!< キーリリース
#define SYS_REMO_STOP                   0x0800                //!< 停止
#define SYS_REMO_SEARCH_RWD             0x0802                //!< サーチ戻し
#define SYS_REMO_SEARCH_FWD             0x0803                //!< サーチ送り
#define SYS_REMO_PAUSE                  0x0806                //!< 一時停止
#define SYS_REMO_SLOW_RWD               0x0807                //!< スロー／コマ戻し
#define SYS_REMO_PLAY                   0x080A                //!< 再生
#define SYS_REMO_SLOW_FWD               0x080F                //!< スロー／コマ送り
#define SYS_REMO_POWER                  0x083C                //!< 電源
#define SYS_REMO_SKIP_RWD               0x0849                //!< スキップ戻し
#define SYS_REMO_SKIP_FWD               0x084A                //!< スキップ送り
#define SYS_REMO_MENU                   0x0856                //!< メニュー
#define SYS_REMO_DISPLAY                0x0857                //!< 表示出力
#define SYS_REMO_ENTER                  0x0858                //!< 決定
#define SYS_REMO_ZOOM_T                 0x0862                //!< ズームＴ
#define SYS_REMO_ZOOM_W                 0x0863                //!< ズームＷ
#define SYS_REMO_PHOTO                  0x0866                //!< フォトショット
#define SYS_REMO_DATE                   0x0867                //!< 年月日／時刻
#define SYS_REMO_DELETE                 0x0870                //!< 削除
#define SYS_REMO_S_S                    0x08CC                //!< 撮影記録/停止
#define SYS_REMO_FACE_DET               0x098B                //!< 顔検出
#define SYS_REMO_PRE_REC                0x098C                //!< PRE-REC
#define SYS_REMO_UP                     0x09D0                //!< 上
#define SYS_REMO_DOWN                   0x09D1                //!< 下
#define SYS_REMO_RIGHT                  0x09D2                //!< 右
#define SYS_REMO_LEFT                   0x09D3                //!< 左
#define SYS_REMO_MP_POWER               0x0873                //!< マリンパック 電源
#define SYS_REMO_MP_S_S                 0x0874                //!< マリンパック S/S
#define SYS_REMO_MP_PHOTO               0x0875                //!< マリンパック フォトショット
#define SYS_REMO_MP_ZOOM_T              0x0876                //!< マリンパック ズームＴ
#define SYS_REMO_MP_ZOOM_W              0x0877                //!< マリンパック ズームＷ
#define SYS_REMO_MP_WB_PLUS             0x0879                //!< マリンパック WB設定(B制御)
#define SYS_REMO_MP_WB_MINUS            0x0878                //!< マリンパック WB設定(R制御)
#define SYS_REMO_VCR1_MODE              0x00                  //!< VCR1
#define SYS_REMO_VCR2_MODE              0x02                  //!< VCR2
#define SYS_REMO_VCR3_MODE              0x04                  //!< VCR3
#define SYS_REMO_VCR4_MODE              0x08                  //!< VCR4
#define SYS_NTSC                        0x00                  //!< ＮＴＳＣ
#define SYS_PAL                         0x01                  //!< ＰＡＬ
#define SYS_POWER_RESET_STATUS_COLD     0x00                  //!< 電源断からの復帰
#define SYS_POWER_RESET_STATUS_HOT_ON   0x01                  //!< 電源断せずに再起動して電源ON
#define SYS_POWER_RESET_STATUS_HOT_OFF  0x02                  //!< 電源断せずに再起動して電源OFF
#define SYS_POWER_RESET_STATUS_BOOT     0x03                  //!< BLDR→BE/CHARGE
#define SYS_TEMP_HIGH_NO_DET            0x00                  //!< 未検出
#define SYS_TEMP_HIGH_B                 0x01                  //!< 温度異常B
#define SYS_TEMP_HIGH_A                 0x02                  //!< 温度異常A
#define SYS_USB_CC_NO_CHANGE            0x00                  //!< 要求なし
#define SYS_USB_CC_CANNOT_USE           0x01                  //!< USB使用禁止
#define SYS_USB_CC_CHRAGE_EXCLUSION     0x02                  //!< USB充電除外
#define SYS_USB_CC_MAX100mA             0x03                  //!< 100mA制限
#define SYS_USB_CC_MAX500mA             0x04                  //!< 500mA制限
#define SYS_USB_CC_MAX900mA             0x05                  //!< 900mA制限
#define SYS_USB_CC_MAX1500mA            0x06                  //!< 1500mA制限
#define SYS_USB_CC_UNLIMIT              0x07                  //!< 無制限
#define SYS_FAN_AUTO                    0x00                  //!< 自動
#define SYS_FAN_STOP                    0x01                  //!< 停止
#define SYS_FAN_MID_SPEED               0x02                  //!< 中速
#define SYS_FAN_HIGH_SPEED              0x03                  //!< 高速
#define SYS_FAN_FULL_ON                 0x04                  //!< フル回転
#define SYS_FAN_FULL_OFF                0x05                  //!< フル回転停止
#define SYS_EEP_OK                      0x00                  //!< リード成功
#define SYS_EEP_NG_MAIN                 0x01                  //!< メインリード失敗
#define SYS_EEP_NG_BACKUP               0x02                  //!< メイン/バックアップリード失敗
#define SYS_EEP_NG_INIT                 0x03                  //!< メイン/バックアップ/初期値リード失敗
#define SYS_LCD_CLOSE                   0x00                  //!< LCDを閉じた状態
#define SYS_LCD_OPEN                    0x01                  //!< LCDを開いた状態
#define SYS_LCD_REVERSE_OPEN            0x02                  //!< LCDを対面にした状態
#define SYS_LCD_REVERSE_CLOSE           0x03                  //!< LCDを反転収納した状態
#define SYS_LCD_OBVERSE_CLOSE           0x04                  //!< LCDを正転収納した状態(縦型モデル用)
#define SYS_MODELINFO_Z130              0x00                  //!< Z130
#define SYS_MODELINFO_Z134              0x01                  //!< Z134
#define SYS_MODELINFO_Z119K2            0x02                  //!< Z119K2
#define SYS_MODELINFO_Z143              0x03                  //!< Z143
#define SYS_MODELINFO_Z148              0x04                  //!< Z148
#define SYS_MODELINFO_Z152              0x05                  //!< Z152
#define SYS_MODELINFO_Z159              0x06                  //!< Z159
#define SYS_MODELINFO_Z143K             0x07                  //!< Z143K
#define SYS_MODELINFO_Z154              0x08                  //!< Z154
#define SYS_MODELINFO_Z143K2            0x09                  //!< Z143K2
#define SYS_MODELINFO_Z152K             0x0A                  //!< Z152K
#define SYS_MODELINFO_Z152K2            0x0B                  //!< Z152K2
#define SYS_MODELINFO_Z159K             0x0C                  //!< Z159K
#define SYS_MODELINFO_Z167              0x0D                  //!< Z167
#define SYS_MODELINFO_Z168              0x0E                  //!< Z168
#define SYS_MODELINFO_T3028             0x0F                  //!< T3028
#define SYS_MODELINFO_Z159K2            0x10                  //!< Z159K2
#define SYS_MODELINFO_T3029             0x11                  //!< T3029
#define SYS_MODELINFO_HPB1025           0x12                  //!< HPB1025
#define SYS_MODELINFO_11P1BA822A        0x13                  //!< 11P1BA822A
#define SYS_MODELINFO_Z198              0x14                  //!< Z198
#define SYS_MODELINFO_T3202             0x15                  //!< T3202
#define SYS_MODELINFO_Z198K2            0x16                  //!< Z198K2
#define SYS_MODELINFO_DF019N0010        0x17                  //!< DF019N0010
#define SYS_MODELINFO_Z213              0x18                  //!< Z213
#define SYS_MODELINFO_Z198K4            0x19                  //!< Z198K4
#define SYS_MODELINFO_A360              0x1A                  //!< A360
#define SYS_MODELINFO_Z242              0x1B                  //!< Z242
#define SYS_MODELINFO_CHANGE            0x1C                  //!< レンズ交換式
#define SYS_MODELINFO_Z268              0x1D                  //!< Z268
#define SYS_REMO_HDCOM_VIDEO_OUT        0x0001                //!< スクリーンスタンバイ
#define SYS_REMO_HDCOM_FULL_SCREEN      0x0002                //!< 表示
#define SYS_REMO_HDCOM_LAYOUT           0x0003                //!< レイアウト
#define SYS_REMO_HDCOM_PC               0x0004                //!< PC
#define SYS_REMO_HDCOM_CAM_SUB          0x0005                //!< サブカメラ
#define SYS_REMO_HDCOM_CAM_MAIN         0x0006                //!< 共有終了
#define SYS_REMO_HDCOM_START            0x0007                //!< 開始
#define SYS_REMO_HDCOM_MENU             0x0008                //!< メニュー
#define SYS_REMO_HDCOM_END              0x0009                //!< 終了
#define SYS_REMO_HDCOM_LEFT             0x000A                //!< 左
#define SYS_REMO_HDCOM_RIGHT            0x000B                //!< 右
#define SYS_REMO_HDCOM_UP               0x000C                //!< 上
#define SYS_REMO_HDCOM_DOWN             0x000D                //!< 下
#define SYS_REMO_HDCOM_ENTER            0x000E                //!< 決定
#define SYS_REMO_HDCOM_HOME             0x000F                //!< ホーム
#define SYS_REMO_HDCOM_BACK             0x0010                //!< 戻る
#define SYS_REMO_HDCOM_BULUE            0x0011                //!< 青
#define SYS_REMO_HDCOM_RED              0x0012                //!< 赤
#define SYS_REMO_HDCOM_GREEN            0x0013                //!< 緑
#define SYS_REMO_HDCOM_YELLOW           0x0014                //!< 黄
#define SYS_REMO_HDCOM_VOLUME_UP        0x0015                //!< 音量＋
#define SYS_REMO_HDCOM_VOLUME_DOWN      0x0016                //!< 音量－
#define SYS_REMO_HDCOM_TONE_UP          0x0017                //!< 音質上
#define SYS_REMO_HDCOM_TONE_DOWN        0x0018                //!< 音質下
#define SYS_REMO_HDCOM_CAM_CTRL         0x0019                //!< カメラ操作
#define SYS_REMO_HDCOM_STATUS           0x001A                //!< 状況表示
#define SYS_REMO_HDCOM_CONTACT          0x001B                //!< アドレス帳
#define SYS_REMO_HDCOM_MIC_MUTE         0x001C                //!< マイクオフ
#define SYS_REMO_HDCOM_1                0x001D                //!< 1
#define SYS_REMO_HDCOM_2                0x001E                //!< 2
#define SYS_REMO_HDCOM_3                0x001F                //!< 3
#define SYS_REMO_HDCOM_4                0x0020                //!< 4
#define SYS_REMO_HDCOM_5                0x0021                //!< 5
#define SYS_REMO_HDCOM_6                0x0022                //!< 6
#define SYS_REMO_HDCOM_7                0x0023                //!< 7
#define SYS_REMO_HDCOM_8                0x0024                //!< 8
#define SYS_REMO_HDCOM_9                0x0025                //!< 9
#define SYS_REMO_HDCOM_DOT              0x0026                //!< .
#define SYS_REMO_HDCOM_0                0x0027                //!< 0
#define SYS_REMO_HDCOM_SHARP            0x0028                //!< #
#define SYS_REMO_HDCOM_ID_SWITCHED      0x0000                //!< ID変更通知
#define SYS_REMO_HDCOM_ID_NOTIFY        0x002F                //!< ID通知
#define SYS_REMO_HDCOM_RELEASE          0xFFFF                //!< キーリリース
//////////////////////// AW ////////////////////////////////////
#define SYS_REMO_AW_ON_STANDBY          0x0000                //!< ON STANDBY
#define SYS_REMO_AW_MENU                0x0001                //!< MENU
#define SYS_REMO_AW_SET                 0x0002                //!< SET
#define SYS_REMO_AW_MODE                0x0003                //!< MODE
#define SYS_REMO_AW_OPT_ON              0x0004                //!< OPT ON
#define SYS_REMO_AW_OPT_OFF             0x0005                //!< OPT OFF
#define SYS_REMO_AW_GAIN_OFF            0x0006                //!< GAIN OFF
#define SYS_REMO_AW_GAIN_LOW            0x0007                //!< GAIN LOW
#define SYS_REMO_AW_GAIN_HI             0x0008                //!< GAIN HI
#define SYS_REMO_AW_GAIN_AUTO           0x0009                //!< GAIN AUTO
#define SYS_REMO_AW_CALL1               0x000A                //!< CALL1
#define SYS_REMO_AW_CALL2               0x000B                //!< CALL2
#define SYS_REMO_AW_CALL3               0x000C                //!< CALL3
#define SYS_REMO_AW_CALL4               0x000D                //!< CALL4
#define SYS_REMO_AW_CALL5               0x000E                //!< CALL5
#define SYS_REMO_AW_CALL6               0x000F                //!< CALL6
#define SYS_REMO_AW_CALL7               0x0010                //!< CALL7
#define SYS_REMO_AW_CALL8               0x0011                //!< CALL8
#define SYS_REMO_AW_CALL9               0x0012                //!< CALL9
#define SYS_REMO_AW_CALL10              0x0013                //!< CALL10
#define SYS_REMO_AW_CALL11              0x0014                //!< CALL11
#define SYS_REMO_AW_CALL12              0x0015                //!< CALL12
#define SYS_REMO_AW_UP                  0x0016                //!< ↑
#define SYS_REMO_AW_HOME                0x0017                //!< HOME
#define SYS_REMO_AW_LEFT                0x0018                //!< ←
#define SYS_REMO_AW_OK                  0x0019                //!< OK
#define SYS_REMO_AW_RIGHT               0x001A                //!< →
#define SYS_REMO_AW_HIDDEN_BUTTON1      0x001B                //!< HIDDEN BUTTON1
#define SYS_REMO_AW_DOWN                0x001C                //!< ↓
#define SYS_REMO_AW_HIDDEN_BUTTON2      0x001D                //!< HIDDEN BUTTON2
#define SYS_REMO_AW_FOCUS_FAR           0x001E                //!< FOCUS FAR
#define SYS_REMO_AW_FAST                0x001F                //!< FAST
#define SYS_REMO_AW_ZOOM_TELE           0x0020                //!< ZOOM TELE
#define SYS_REMO_AW_FOCUS_NEAR          0x0021                //!< FOCUS NEAR
#define SYS_REMO_AW_SLOW                0x0022                //!< SLOW
#define SYS_REMO_AW_ZOOM_WIDE           0x0023                //!< ZOOM WIDE
#define SYS_REMO_AW_AUTO_FOCUS          0x0024                //!< AUTO FOCUS
#define SYS_REMO_AW_AUTO_IRIS           0x0025                //!< AUTO IRIS
#define SYS_REMO_AW_IRIS_OPEN           0x0026                //!< IRIS OPEN
#define SYS_REMO_AW_MANUAL_FOCUS        0x0027                //!< MANUAL FOCUS
#define SYS_REMO_AW_MANUAL_IRIS         0x0028                //!< MANUAL IRIS
#define SYS_REMO_AW_IRIS_CLOSE          0x0029                //!< IRIS CLOSE
#define SYS_REMO_AW_LIMIT_UP            0x002A                //!< LIMIT+UP
#define SYS_REMO_AW_LIMIT_LEFT          0x002B                //!< LIMIT+LEFT
#define SYS_REMO_AW_LIMIT_RIGHT         0x002C                //!< LIMIT+RIGHT
#define SYS_REMO_AW_LIMIT_DOWN          0x002D                //!< LIMIT+DOWN
#define SYS_REMO_AW_reserve_2E          0x002E                //!< reserved
#define SYS_REMO_AW_reserve_2F          0x002F                //!< reserved
#define SYS_REMO_AW_PRESET_CALL1        0x0030                //!< PRESET CALL1
#define SYS_REMO_AW_PRESET_CALL2        0x0031                //!< PRESET CALL2
#define SYS_REMO_AW_PRESET_CALL3        0x0032                //!< PRESET CALL3
#define SYS_REMO_AW_PRESET_CALL4        0x0033                //!< PRESET CALL4
#define SYS_REMO_AW_PRESET_CALL5        0x0034                //!< PRESET CALL5
#define SYS_REMO_AW_PRESET_CALL6        0x0035                //!< PRESET CALL6
#define SYS_REMO_AW_PRESET_CALL7        0x0036                //!< PRESET CALL7
#define SYS_REMO_AW_PRESET_CALL8        0x0037                //!< PRESET CALL8
#define SYS_REMO_AW_PRESET_CALL9        0x0038                //!< PRESET CALL9
#define SYS_REMO_AW_PRESET_CALL10       0x0039                //!< PRESET CALL10
#define SYS_REMO_AW_PRESET_CALL11       0x003A                //!< PRESET CALL11
#define SYS_REMO_AW_PRESET_CALL12       0x003B                //!< PRESET CALL12
#define SYS_REMO_AW_UP_LEFT             0x003C                //!< UP+LEFT
#define SYS_REMO_AW_UP_RIGHT            0x003D                //!< UP+RIGHT
#define SYS_REMO_AW_DOWN_LEFT           0x003E                //!< DOWN+LEFT
#define SYS_REMO_AW_DOWN_RIGHT          0x003F                //!< DOWN+RIGHT
#define SYS_REMO_AW_RELEASE             0xFFFF                //!< キーリリース
#define SYS_KEYAW_RELEASE               0x00                  //!< キーリリース
#define SYS_KEYAW_ON_STANDBY            0x01                  //!< ON/STANDBY
#define SYS_KEYAW_MENU                  0x02                  //!< MENU
#define SYS_KEYAW_SET                   0x03                  //!< SET
#define SYS_KEYAW_MODE                  0x04                  //!< MODE
#define SYS_KEYAW_CALL1                 0x05                  //!< CALL1
#define SYS_KEYAW_CALL2                 0x06                  //!< CALL2
#define SYS_KEYAW_CALL3                 0x07                  //!< CALL3
#define SYS_KEYAW_CALL4                 0x08                  //!< CALL4
#define SYS_KEYAW_CALL5                 0x09                  //!< CALL5
#define SYS_KEYAW_CALL6                 0x0A                  //!< CALL6
#define SYS_KEYAW_CALL7                 0x0B                  //!< CALL7
#define SYS_KEYAW_CALL8                 0x0C                  //!< CALL8
#define SYS_KEYAW_CALL9                 0x0D                  //!< CALL9
#define SYS_KEYAW_HOME                  0x0E                  //!< HOME
#define SYS_KEYAW_OK                    0x0F                  //!< OK
#define SYS_KEYAW_UP                    0x10                  //!< ↑
#define SYS_KEYAW_LEFT                  0x11                  //!< ←
#define SYS_KEYAW_RIGHT                 0x12                  //!< →
#define SYS_KEYAW_DOWN                  0x13                  //!< ↓
#define SYS_KEYAW_FAST                  0x14                  //!< FAST
#define SYS_KEYAW_SLOW                  0x15                  //!< SLOW
#define SYS_KEYAW_ZOOM_TELE             0x16                  //!< ZOOM TELE
#define SYS_KEYAW_ZOOM_WIDE             0x17                  //!< ZOOM WIDE
#define SYS_KEYAW_PRESET_CALL1          0x18                  //!< PRESET+CALL1
#define SYS_KEYAW_PRESET_CALL2          0x19                  //!< PRESET+CALL2
#define SYS_KEYAW_PRESET_CALL3          0x1A                  //!< PRESET+CALL3
#define SYS_KEYAW_PRESET_CALL4          0x1B                  //!< PRESET+CALL4
#define SYS_KEYAW_PRESET_CALL5          0x1C                  //!< PRESET+CALL5
#define SYS_KEYAW_PRESET_CALL6          0x1D                  //!< PRESET+CALL6
#define SYS_KEYAW_PRESET_CALL7          0x1E                  //!< PRESET+CALL7
#define SYS_KEYAW_PRESET_CALL8          0x1F                  //!< PRESET+CALL8
#define SYS_KEYAW_PRESET_CALL9          0x20                  //!< PRESET+CALL9
#define SYS_KEYAW_UP_LEFT               0x21                  //!< ↑+ ←
#define SYS_KEYAW_UP_RIGHT              0x22                  //!< ↑+ →
#define SYS_KEYAW_DOWN_LEFT             0x23                  //!< ↓+ ←
#define SYS_KEYAW_DOWN_RIGHT            0x24                  //!< ↓+ →
#define SYS_KEYAW_OPT_ON                0x25                  //!< PinP Display
#define SYS_KEYAW_OPT_OFF               0x26                  //!< Control
#define SYS_KEYAW_AUTO_IRIS             0x27                  //!< A/IRIS
#define SYS_KEYAW_MANUAL_IRIS           0x28                  //!< M/IRIS
#define SYS_KEYAW_IRIS_OPEN             0x29                  //!< IRIS+
#define SYS_KEYAW_IRIS_CLOSE            0x2A                  //!< IRIS-

#define SYS_NO_REQ                      0x00                  //!< 要求なし
#define SYS_PON_REQ                     0x01                  //!< 電源ON要求
#define SYS_STANBY_REQ                  0x02                  //!< STANBY要求
#define SYS_DRAM_NORMAL                 0x00                  //!< 通常モード
#define SYS_DRAM_USTREAM                0x01                  //!< USTREAMモード
#define SYS_DRAM_DLNA                   0x02                  //!< DLNAモード
#define SYS_24_00P                      0x01                  //!< 24.00p
#define SYS_23_98P                      0x02                  //!< 23.98p
#define SYS_BATT_T_NO_DATA              0x00                  //!< BATT_Tデータなし
#define SYS_BATT_T_MIN                  0x01                  //!< BATT_Tデータ最小値
#define SYS_INIT                        0x00                  //!< 初期状態/検出中
#define SYS_STANBY                      0x01                  //!< スタンバイ
#define SYS_UNDETECT                    0x02                  //!< 非検出
#define SYS_DETECT                      0x03                  //!< 検出
#define SYS_DEVICE_ERROR                0x04                  //!< デバイスエラー
#define SYS_FPGA_INIT                   0x00                  //!< 初期状態
#define SYS_FPGA_BOOT                   0x01                  //!< ブート中
#define SYS_FPGA_OK                     0x02                  //!< ブート成功
#define SYS_FPGA_NG                     0x03                  //!< ブート失敗
#define SYS_POVCAM_CAMHEAD              0x00                  //!< カメラヘッド連携モード
#define SYS_POVCAM_RECORDER             0x01                  //!< レコーダモード
#define SYS_CAM_NORMAL_PROC             0x00                  //!< 通常処理
#define SYS_CAM_LOW_VOLTAGE_PROC        0x01                  //!< 低電圧用処理
#define SYS_DATE_NO_REQ                 0x00                  //!< 要求なし/要求の処理完了
#define SYS_DATE_ALARM_REQ              0x01                  //!< アラーム起動要求
#define SYS_DATE_CHANGE_REQ             0x02                  //!< 日時変更要求
#define SYS_DATE_STOP_REQ               0x03                  //!< 日時停止要求
#define SYS_KEY_REC_MODE                0x00                  //!< 動画撮影
#define SYS_KEY_STILL_REC_MODE          0x01                  //!< 静止画撮影
#define SYS_KEY_PLAY_MODE               0x02                  //!< 再生
#define SYS_MANUAL_SW_IA                0x00                  //!< iA
#define SYS_MANUAL_SW_MNL               0x01                  //!< MANUAL
#define SYS_MANUAL_SW_MF                0x02                  //!< FOCUS
#define SYS_AUDIO_SW_INT                0x00                  //!< INT(L)
#define SYS_AUDIO_SW_INPUT1             0x01                  //!< INPUT1
#define SYS_AUDIO_SW_INPUT2             0x02                  //!< INPUT2
#define SYS_WIRE_IRIS_SW_OFF            0x00                  //!< IRIS_SW_OFF
#define SYS_WIRE_IRIS_SW_ON             0x01                  //!< IRIS_SW_ON
#define SYS_WIRE_FOCUS_SW_OFF           0x00                  //!< FOCUS_SW_OFF
#define SYS_WIRE_FOCUS_SW_ON            0x01                  //!< FOCUS_SW_ON
#define SYS_DISP_SW_OFF                 0x00                  //!< DISP_SW_OFF
#define SYS_DISP_SW_ON                  0x01                  //!< DISP_SW_ON
#define SYS_DISP_SW_CHK                 0x02                  //!< DISP_SW_CHK
//////////////////////// KEY1 ////////////////////////////////////
#define SYS_KEY_POWER                   0x0000000000000001ULL //!< 電源
#define SYS_KEY_UP                      0x0000000000000002ULL //!< 上
#define SYS_KEY_DOWN                    0x0000000000000004ULL //!< 下
#define SYS_KEY_LEFT                    0x0000000000000008ULL //!< 左
#define SYS_KEY_RIGHT                   0x0000000000000010ULL //!< 右
#define SYS_KEY_ENTER                   0x0000000000000020ULL //!< 決定
#define SYS_KEY_PHOTO_HALF              0x0000000000000040ULL //!< フォトショット半押し
#define SYS_KEY_PHOTO                   0x0000000000000080ULL //!< フォトショット
#define SYS_KEY_S_S                     0x0000000000000100ULL //!< S/S
#define SYS_KEY_MODE                    0x0000000000000200ULL //!< 撮影/再生
#define SYS_KEY_PRE_REC                 0x0000000000000400ULL //!< PRE_REC
#define SYS_KEY_BALANCE                 0x0000000000000800ULL //!< 傾き補正
#define SYS_KEY_OIS                     0x0000000000001000ULL //!< OIS
#define SYS_KEY_IA                      0x0000000000002000ULL //!< iA
#define SYS_KEY_CAM_FUNC                0x0000000000004000ULL //!< カメラファンクション
#define SYS_KEY_LIGHT                   0x0000000000008000ULL //!< LEDライト
#define SYS_KEY_DELETE                  0x0000000000010000ULL //!< 削除
#define SYS_KEY_MENU                    0x0000000000020000ULL //!< メニュー1
#define SYS_KEY_P_ZOOM_T                0x0000000000040000ULL //!< ズームＴ(LCDパネル)
#define SYS_KEY_P_ZOOM_W                0x0000000000080000ULL //!< ズームＷ(LCDパネル)
#define SYS_KEY_P_S_S                   0x0000000000100000ULL //!< S/S(LCDパネル)
#define SYS_KEY_P_QMENU                 0x0000000000200000ULL //!< クイックメニュー(LCDパネル)
#define SYS_KEY_LONG_REC                0x0000000000400000ULL //!< LongRec
#define SYS_KEY_AF_AE                   0x0000000000800000ULL //!< AF/AE
#define SYS_KEY_LIGHT_DELETE            0x0000000001000000ULL //!< LEDライト/削除
#define SYS_KEY_60P                     0x0000000002000000ULL //!< 60P
#define SYS_KEY_MENU2                   0x0000000004000000ULL //!< メニュー2(MENUキーが2つ以上ある場合)
#define SYS_KEY_P_LCD                   0x0000000008000000ULL //!< PowerLCD
#define SYS_KEY_REC_CHECK               0x0000000010000000ULL //!< REC_CHECK
#define SYS_KEY_SHIFT                   0x0000000020000000ULL //!< SHIFT
#define SYS_KEY_AUDIO_PLUS              0x0000000040000000ULL //!< AUDIO(+)キー
#define SYS_KEY_AUDIO_MINUS             0x0000000080000000ULL //!< AUDIO(-)キー
#define SYS_KEY_MNL_RING_PLUS           0x0000000100000000ULL //!< MNLリング(+)
#define SYS_KEY_MNL_RING_MINUS          0x0000000200000000ULL //!< MNLリング(-)
#define SYS_KEY_PLAY                    0x0000000400000000ULL //!< 再生キー
#define SYS_KEY_STOP                    0x0000000800000000ULL //!< 停止キー
#define SYS_KEY_PAUSE                   0x0000001000000000ULL //!< 一時停止キー
#define SYS_KEY_SKIP_RWD                0x0000002000000000ULL //!< スキップ戻しキー
#define SYS_KEY_SKIP_FWD                0x0000004000000000ULL //!< スキップ送りキー
#define SYS_KEY_SLOW_RWD                0x0000008000000000ULL //!< スロー/コマ戻しキー
#define SYS_KEY_SLOW_FWD                0x0000010000000000ULL //!< スロー/コマ送りキー
#define SYS_KEY_SEARCH_RWD              0x0000020000000000ULL //!< サーチ戻しキー
#define SYS_KEY_SEARCH_FWD              0x0000040000000000ULL //!< サーチ送りキー
#define SYS_KEY_DISPLAY                 0x0000080000000000ULL //!< 表示出力キー
#define SYS_KEY_DATE_TIME               0x0000100000000000ULL //!< 年月日/時刻キー
#define SYS_KEY_WB_PLUS                 0x0000200000000000ULL //!< WB(+)キー
#define SYS_KEY_WB_MINUS                0x0000400000000000ULL //!< WB(-)キー
#define SYS_KEY_ZOOM_T                  0x0000800000000000ULL //!< ズームＴ(リモコン、ズームスライドキー)
#define SYS_KEY_ZOOM_W                  0x0001000000000000ULL //!< ズームＷ(リモコン、ズームスライドキー)
#define SYS_KEY_LIVE                    0x0002000000000000ULL //!< LIVE
#define SYS_KEY_INIT                    0x0004000000000000ULL //!< INIT
#define SYS_KEY_WIFI                    0x0008000000000000ULL //!< WiFi
#define SYS_KEY_HOLD                    0x0010000000000000ULL //!< HOLD
#define SYS_KEY_MOVIE_STILL             0x0020000000000000ULL //!< 動画/静止画
#define SYS_KEY_HDR                     0x0040000000000000ULL //!< HDR
#define SYS_KEY_AUTO_MNL                0x0100000000000000ULL //!< AUTO_MNL
#define SYS_KEY_CANCEL                  0x0200000000000000ULL //!< CANCEL/EXIT
//////////////////////// KEY2 ////////////////////////////////////
#define SYS_KEY2_IRIS                   0x0000000000000001ULL //!< IRIS AUTO/MNL
#define SYS_KEY2_WB                     0x0000000000000002ULL //!< WB
#define SYS_KEY2_3D_GUIDE               0x0000000000000004ULL //!< 3D GUIDE
#define SYS_KEY2_ZEBRA                  0x0000000000000008ULL //!< ZEBRA
#define SYS_KEY2_BARS                   0x0000000000000010ULL //!< BARS
#define SYS_KEY2_CHECK                  0x0000000000000020ULL //!< DISP/MODE_CHK
#define SYS_KEY2_COUNTER                0x0000000000000040ULL //!< COUNTER
#define SYS_KEY2_TC                     0x0000000000000080ULL //!< RESET/TC SET
#define SYS_KEY2_QSTART                 0x0000000000000800ULL //!< QUICK START
#define SYS_KEY2_SUB_S_S                0x0000000000001000ULL //!< SUB S/S
#define SYS_KEY2_SUB_ZOOM_T             0x0000000000002000ULL //!< SUB ZOOM T
#define SYS_KEY2_SUB_ZOOM_W             0x0000000000004000ULL //!< SUB ZOOM W
#define SYS_KEY2_IRIS_PLUS              0x0000000000008000ULL //!< IRISリング +方向
#define SYS_KEY2_IRIS_MINUS             0x0000000000010000ULL //!< IRISリング -方向
#define SYS_KEY2_CONV_PLUS              0x0000000000020000ULL //!< CONVリング +方向
#define SYS_KEY2_CONV_MINUS             0x0000000000040000ULL //!< CONVリング -方向
#define SYS_KEY2_FOCUS_PLUS             0x0000000000080000ULL //!< FOCUSリング +方向
#define SYS_KEY2_FOCUS_MINUS            0x0000000000100000ULL //!< FOCUSリング -方向
#define SYS_KEY2_ZOOM_PLUS              0x0000000000200000ULL //!< ZOOMリング +方向
#define SYS_KEY2_ZOOM_MINUS             0x0000000000400000ULL //!< ZOOMリング -方向
#define SYS_KEY2_FOCUS                  0x0000000000800000ULL //!< FOCUS AUTO/MNL/∞
#define SYS_KEY2_WIRE_SS                0x0000000001000000ULL //!< ワイヤードリモコン SS
#define SYS_KEY2_WIRE_CONV_PLUS         0x0000000002000000ULL //!< ワイヤードリモコン CONV +方向
#define SYS_KEY2_WIRE_CONV_MINUS        0x0000000004000000ULL //!< ワイヤードリモコン CONV -方向
#define SYS_KEY2_FA                     0x0000000008000000ULL //!< FA
#define SYS_KEY2_PUSH_AF                0x0000000020000000ULL //!< PUSH_AF
#define SYS_KEY2_GAIN                   0x0000000040000000ULL //!< GAIN
#define SYS_KEY2_SHUTTER                0x0000000080000000ULL //!< SHUTTER
#define SYS_KEY2_FRONT_S_S              0x0000000100000000ULL //!< FRONT S/S
#define SYS_KEY2_WFM                    0x0000000200000000ULL //!< WFM
#define SYS_KEY2_A_IRIS_LEVEL           0x0000000400000000ULL //!< A. IRIS LEVEL
#define SYS_KEY2_AWB                    0x0000000800000000ULL //!< AWB
#define SYS_KEY2_WB_AUTO_MNL            0x0000001000000000ULL //!< WB(AUTO/MNL切替)
#define SYS_KEY2_WB_A_B_PRST            0x0000002000000000ULL //!< WB(Ach/Bch/プリセット切替)
#define SYS_KEY2_USER1                  0x0000000000000100ULL //!< USER1
#define SYS_KEY2_USER2                  0x0000000000000200ULL //!< USER2
#define SYS_KEY2_USER3                  0x0000000000000400ULL //!< USER3
#define SYS_KEY2_USER4                  0x0000000010000000ULL //!< USER4
#define SYS_KEY2_USER5                  0x0000004000000000ULL //!< USER5
#define SYS_KEY2_USER6                  0x0000008000000000ULL //!< USER6
#define SYS_KEY2_USER7                  0x0000010000000000ULL //!< USER7
#define SYS_KEY2_USER8                  0x0000020000000000ULL //!< USER8
#define SYS_KEY2_USER9                  0x0000040000000000ULL //!< USER9
#define SYS_KEY2_ND_PLUS                0x0000080000000000ULL //!< ND(+)
#define SYS_KEY2_ND_MINUS               0x0000100000000000ULL //!< ND(-)
#define SYS_KEY2_IRIS_FUNC              0x0000200000000000ULL //!< IRIS Dial Set
#define SYS_KEY2_HOME                   0x0000400000000000ULL //!< HOME
#define SYS_KEY2_CANCEL                 0x0000800000000000ULL //!< CANCEL/EXIT
////////////////////////////////////////////////////////////
#define SYS_BATT_DISCONNECT             0x00                  //!< 未接続
#define SYS_BATT_NO_CHECK               0x01                  //!< 未認証
#define SYS_BATT_CHECKING               0x02                  //!< 認証中/残量計算中
#define SYS_BATT_OK_REM_ENABLE          0x03                  //!< 認証ＯＫ/残量計算ＯＫ(分表示有効->純正バッテリ)
#define SYS_BATT_OK_REM_DISABLE         0x04                  //!< 認証ＯＫ/残量計算ＯＫ(分表示無効->3rd Partyバッテリ)
#define SYS_BATT_ERR                    0x05                  //!< 通信エラー
#define SYS_BATT_NG                     0x06                  //!< 認証ＮＧ
#define SYS_BATT_TYPE_1P                0x00                  //!< 1パラ(または不明)
#define SYS_BATT_TYPE_2P                0x01                  //!< 2パラ
#define SYS_BATT_TYPE_4P                0x02                  //!< 4パラ
#define SYS_BATT_TYPE_6P                0x03                  //!< 6パラ
#define SYS_BATT_TYPE_4P_QI             0x04                  //!< 4パラ(Qi対応)
#define SYS_BATT_TYPE_3RD               0x06                  //!< 3rdパーティーバッテリー
#define SYS_BATT_TYPE_CHECKING_D        0x0D                  //!< 判定中[種別判定中]
#define SYS_BATT_TYPE_CHECKING_T        0x0E                  //!< 判定中[接続判定中]
#define SYS_BATT_TYPE_FORCE_CHANGE      0x0F                  //!< 上記以外の値(電池パラメータ強制Load用)<4bitの最大値>
#define SYS_FOCUS_SW_AUTO               0x00                  //!< AUTO
#define SYS_FOCUS_SW_MNL                0x01                  //!< MANUAL
#define SYS_FOCUS_SW_INF                0x02                  //!< INFINITE
#define SYS_INPUT_SEL_SW_LINE           0x00                  //!< LINE
#define SYS_INPUT_SEL_SW_MIC            0x01                  //!< MIC
#define SYS_INPUT_SEL_SW_48V            0x02                  //!< +48V
#define SYS_ND_SW_OFF                   0x00                  //!< OFF
#define SYS_ND_SW_1_4                   0x01                  //!< 1/4
#define SYS_ND_SW_1_16                  0x02                  //!< 1/16
#define SYS_ND_SW_1_64                  0x03                  //!< 1/64
#define SYS_GAIN_SW_LOW                 0x00                  //!< GAIN_SW_LOW
#define SYS_GAIN_SW_MID                 0x01                  //!< GAIN_SW_MID
#define SYS_GAIN_SW_HIGH                0x02                  //!< GAIN_SW_HIGH
#define SYS_WB_SW_PRST                  0x00                  //!< WB_SW_PRST
#define SYS_WB_SW_A                     0x01                  //!< WB_SW_A
#define SYS_WB_SW_B                     0x02                  //!< WB_SW_B
#define SYS_AUDIO_MODE_AUTO             0x00                  //!< AUDIO_MODE_AUTO
#define SYS_AUDIO_MODE_MANU             0x01                  //!< AUDIO_MODE_MANU
#define SYS_INOUT_SW_OUT                0x00                  //!< INOUT_SW_OUT
#define SYS_INOUT_SW_IN                 0x01                  //!< INOUT_SW_IN
#define SYS_LED_LIGHT_OFF               0x00                  //!< LED_LIGHT_OFF
#define SYS_LED_LIGHT_ON                0x01                  //!< LED_LIGHT_ON
#define SYS_LCD_SW_OFF                  0x00                  //!< OFF
#define SYS_LCD_SW_MIRROR               0x01                  //!< MIRROR(B/T)
#define SYS_LCD_SW_ROTATE               0x02                  //!< ROTATE
#define SYS_LCD_SW_DISCONNECT           0x03                  //!< DISCONNECT
#define SYS_USER_SW_WB                  0x00                  //!< WB
#define SYS_USER_SW_USER                0x01                  //!< USER
#define SYS_USER_SW_ISO                 0x02                  //!< ISO
#define SYS_LOCK_SW_OFF                 0x00                  //!< OFF
#define SYS_LOCK_SW_ON                  0x01                  //!< ON
#define SYS_BATT_TYPE2_VBR59            0x00                  //!< VBR59
#define SYS_BATT_TYPE2_VBR89            0x01                  //!< VBR89
#define SYS_BATT_TYPE2_VBR118           0x02                  //!< VBR118
#define SYS_BATT_TYPE2_UNKNOWN          0x03                  //!< 通信中 or 未接続 or VBRシリーズ以外
#define SYS_BATT_TYPE2_ERR              0x04                  //!< 通信エラー or 非対応バッテリ
////////////////////////////// LANC 2 //////////////////////////////
#define SYS_LANC_MENU                   0x0000000000000001ULL //!< MENU SW
#define SYS_LANC_DIAL_FUNC              0x0000000000000002ULL //!< DIAL SEL
#define SYS_LANC_DIAL_PLUS              0x0000000000000004ULL //!< DIAL(+)
#define SYS_LANC_DIAL_MINUS             0x0000000000000008ULL //!< DIAL(-)
#define SYS_LANC_S_S                    0x0000000000000010ULL //!< REC SW
#define SYS_LANC_USER1                  0x0000000000000100ULL //!< USER1
#define SYS_LANC_USER2                  0x0000000000000200ULL //!< USER2
#define SYS_LANC_USER3                  0x0000000000000400ULL //!< USER3
#define SYS_LANC_USER4                  0x0000000000000800ULL //!< USER4
#define SYS_LANC_USER5                  0x0000000000001000ULL //!< USER5
#define SYS_LANC_USER6                  0x0000000000002000ULL //!< USER6
#define SYS_LANC_USER7                  0x0000000000004000ULL //!< USER7
#define SYS_LANC_USER8                  0x0000000000008000ULL //!< USER8
#define SYS_LANC_USER9                  0x0000000000010000ULL //!< USER9
#define SYS_LANC_EXECUTE                0x0000000000020000ULL //!< EXECUTE
#define SYS_LANC_UP                     0x0000000000040000ULL //!< UP
#define SYS_LANC_DOWN                   0x0000000000080000ULL //!< DOWN
#define SYS_LANC_RIGHT                  0x0000000000100000ULL //!< RIGHT
#define SYS_LANC_LEFT                   0x0000000000200000ULL //!< LEFT
#define SYS_LANC_FOCUS_FAR              0x0000000000400000ULL //!< FOCUS FAR定速(LancFocusSwは0で通知)
#define SYS_LANC_FOCUS_NEAR             0x0000000000800000ULL //!< FOCUS NEAR定速(LancFocusSwは0で通知)
#define SYS_LANC_ZOOM_TELE              0x0000000001000000ULL //!< ZOOM TELE定速(LancZoomSwは0で通知)
#define SYS_LANC_ZOOM_WIDE              0x0000000002000000ULL //!< ZOOM WIDE定速(LancZoomSwは0で通知)

#define GripSw							LancSw
#define GripFocusSw						LancFocusSw
#define GripZoomSw						LancZoomSw

#define SYS_GRIP_MENU                   SYS_LANC_MENU        
#define SYS_GRIP_DIAL_FUNC              SYS_LANC_DIAL_FUNC   
#define SYS_GRIP_DIAL_PLUS              SYS_LANC_DIAL_PLUS   
#define SYS_GRIP_DIAL_MINUS             SYS_LANC_DIAL_MINUS  
#define SYS_GRIP_S_S                    SYS_LANC_S_S         
#define SYS_GRIP_USER1                  SYS_LANC_USER1       
#define SYS_GRIP_USER2                  SYS_LANC_USER2       
#define SYS_GRIP_USER3                  SYS_LANC_USER3       
#define SYS_GRIP_USER4                  SYS_LANC_USER4       
#define SYS_GRIP_USER5                  SYS_LANC_USER5       
#define SYS_GRIP_USER6                  SYS_LANC_USER6       
#define SYS_GRIP_USER7                  SYS_LANC_USER7       
#define SYS_GRIP_USER8                  SYS_LANC_USER8       
#define SYS_GRIP_USER9                  SYS_LANC_USER9       
#define SYS_GRIP_EXECUTE                SYS_LANC_EXECUTE     
#define SYS_GRIP_UP                     SYS_LANC_UP          
#define SYS_GRIP_DOWN                   SYS_LANC_DOWN        
#define SYS_GRIP_RIGHT                  SYS_LANC_RIGHT       
#define SYS_GRIP_LEFT                   SYS_LANC_LEFT        
#define SYS_GRIP_FOCUS_FAR              SYS_LANC_FOCUS_FAR   
#define SYS_GRIP_FOCUS_NEAR             SYS_LANC_FOCUS_NEAR  
#define SYS_GRIP_ZOOM_TELE              SYS_LANC_ZOOM_TELE   
#define SYS_GRIP_ZOOM_WIDE              SYS_LANC_ZOOM_WIDE   
/* ■■■■自動生成終了(DB_Define)■■■■ */
#define SYS_KEY_NONE                    0x0000000000000000ULL //!< 押下キーなし
#define SYS_KEY2_NONE                   0x0000000000000000ULL //!< 押下キーなし    


typedef struct SYS_KEY_STATUS
{
	unsigned char Mode;				// デッキのモードダイヤルまたはモードスイッチの状態(詳細は @ref Key_Status "キー状態"を参照)
	char		  Zoom;				// デッキのズームキーの状態(詳細は @ref Key_Status "キー状態"を参照)
	unsigned char MnlSw;			// デッキのマニュアルSW(iA/Mnl/MFスライドSW)状態(詳細は @ref Key_Status "キー状態"を参照)
	_int64		  Deck;				// デッキのキー状態(詳細は @ref Key_Status "キー状態"を参照)
	_int64		  Remocon;			// ムービーリモコンのキー状態(詳細は @ref Key_Status "キー状態"を参照)
	_int64		  MarinePack;		// マリンパックリモコンのキー状態(詳細は @ref Key_Status "キー状態"を参照)
	_int64		  AwRemocon;		// AWリモコンのキー状態(詳細は @ref Key_Status "キー状態"を参照)
	_int64		  Deck2;			// デッキのキー状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char FocusSw;			// デッキのFOCUSスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char GainSw;			// デッキのGAINスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char WbSw;				// デッキのWBスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char NdSw;				// デッキのND FILTERスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char WireIrisSw;		// ワイヤードリモコンのIRISスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char WireFocusSw;		// ワイヤードリモコンのFOCUSスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char DispSw;			// デッキのDISPスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char InOutSw;			// デッキのIN/OUT切替スイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char Input1SelSw;		// デッキのINPUT1 SELECTスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char Input2SelSw;		// デッキのINPUT2 SELECTスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char AudioCh1Sw;		// デッキのAUDIO CH1スイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char AudioCh2Sw;		// デッキのAUDIO CH2スイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char AudioMode1Sw;		// デッキのAUDIO CH1 AUTO/MANUスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char AudioMode2Sw;		// デッキのAUDIO CH2 AUTO/MANUスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char LedLightSw;		// デッキのLED_LIGHT切替スイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char LcdSw;			// LCDのLCD_MIRROR/ROTATE切替スイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char UserSw;			// デッキのユーザートグルスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char LockSw;			// デッキのキーロックスイッチ状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	_int64	      LancSw;			//!< LANCリモコン SW状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char LancFocusSw;		//!< LANCリモコン Focus SW状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)
	unsigned char LancZoomSw;		//!< LANCリモコン Zoom SW状態(詳細は @ref Key_Status2 "キー状態(PRO/SEMIPRO専用)"を参照)

} SYS_KEY_STATUS;

/* --- タッチパネル定義 --- */

/* スライド方向 */
#define SYS_TPANEL_SLIDE_UP				0		//!< 上方向
#define SYS_TPANEL_SLIDE_DOWN			1		//!< 下方向
#define SYS_TPANEL_SLIDE_LEFT			2		//!< 左方向
#define SYS_TPANEL_SLIDE_RIGHT			3		//!< 右方向

typedef struct SYS_TPANEL
{
	unsigned int	Touched			:1; // タッチ状態(TRUE:タッチ, FALSE:リリース)
	int				X				:13;// タッチＸ座標(タッチしてない場合は不定)
	int				Y				:13;// タッチＹ座標(タッチしてない場合は不定)

	int				SlideStartX		:13;// スライド開始時のしたタッチＸ座標
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	int				SlideStartY		:13;// スライド開始時のタッチＹ座標
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	int				SlidePreX		:13;// 前回通知したタッチＸ座標
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	int				SlidePreY		:13;// 前回通知したタッチＹ座標
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	unsigned int	SlideSpeed		:5; // スライド速度
										// 具体的には下記の値をとる
										// =>8	   :フリック(素早く払うようにタッチする操作)
										// =>1～7  :スライド(7:最速)
										// =>0	   :スライド停止
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	unsigned int	SlideDir		:2; // スライド方向
										// 具体的には下記の値をとる
										// =>SYS_TPANEL_SLIDE_UP   :上方向
										// =>SYS_TPANEL_SLIDE_DOWN :下方向
										// =>SYS_TPANEL_SLIDE_LEFT :左方向
										// =>SYS_TPANEL_SLIDE_RIGHT	   :右方向
										// SYS_EVENT_TPANEL_SLIDEイベント以外の場合は不定

	unsigned int	Mode			:1; // キャリブレーションのモード
										// 具体的には下記の値をとる
										// =>SYS_TPANEL_POSI_NO_SAVE_MODE  :タッチ座標をEEPROMに保存しないモード
										// =>SYS_TPANEL_POSI_SAVE_MODE	   :タッチ座標をEEPROMに保存するモード(工程用)

	unsigned int	Mark			:5; // キャリブレーションで有効なマーク
										// 具体的には下記のビットＯＲの値をとる
										// =>SYS_TPANEL_LEFT_UP_MARK   :左上マーク
										// =>SYS_TPANEL_LEFT_DOWN_MARK :左下マーク
										// =>SYS_TPANEL_RIGHT_UP_MARK  :右上マーク
										// =>SYS_TPANEL_RIGHT_DOWN_MARK:右下マーク
										// =>SYS_TPANEL_CENTER_MARK	   :中央マーク

	unsigned int	TouchedMark		:5; // キャリブレーションでタッチしたマーク
										// 具体的には下記のビットＯＲの値をとる
										// =>SYS_TPANEL_LEFT_UP_MARK   :左上マーク
										// =>SYS_TPANEL_LEFT_DOWN_MARK :左下マーク
										// =>SYS_TPANEL_RIGHT_UP_MARK  :右上マーク
										// =>SYS_TPANEL_RIGHT_DOWN_MARK:右下マーク
										// =>SYS_TPANEL_CENTER_MARK	   :中央マーク
} SYS_TPANEL;

typedef union SYS_EVENT_DATA
{
	SYS_KEY_STATUS Key;			/* キー状態 */
	SYS_TPANEL TPanel;			/* タッチパネル タッチ状態/キャリブレーション状態 */
} SYS_EVENT_DATA;

typedef struct SYS_DATE_TIME
{
	unsigned short Year;	// 2000-2099
	unsigned char Month;	// 1-12
	unsigned char Day;		// 1-31
	unsigned char Hour;		// 0-23
	unsigned char Min;		// 0-59
	unsigned char Sec;		// 0-59
} SYS_DATE_TIME;

typedef struct SYS_DATE_TIME_DATA
{
	SYS_DATE_TIME Value;
	BOOL Enabled;
} SYS_DATE_TIME_DATA;

typedef enum SYS_RET
{
	SYS_OK,
	SYS_NG,
} SYS_RET;

typedef void (*SYS_EVENT_CALLBACK)(unsigned long event, SYS_EVENT_DATA data);
void SYS_Event_AddCallback(SYS_EVENT_CALLBACK Callback);
void SYS_TPanel_SetSlideEventEnable(BOOL flag);
SYS_KEY_STATUS 		SYS_Key_GetStatus(void);
SYS_DATE_TIME SYS_DateTime_GetValue();
SYS_DATE_TIME_DATA SYS_DateTime_GetValueData();
SYS_RET SYS_DateTime_GetAddSec(SYS_DATE_TIME *Dst, const SYS_DATE_TIME *DateTime, long long Sec);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* _SIM_IF_H_ */
