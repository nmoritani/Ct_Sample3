#ifndef __GUI_APLIF_H__
#define __GUI_APLIF_H__

# include "kernel.h"
# include "kernel_id.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


//OSD出力設定 定義
typedef enum _GUI_OUTPUT_LCDEVF_ {
 GUI_OUTPUT_LCDEVF_LCD = 0x00000001, // LCD
 GUI_OUTPUT_LCDEVF_EVF  = 0x00000002, // EVF[K519対応]
 GUI_OUTPUT_LCDEVF_NONE = 0 // NONE
} GUI_OUTPUT_LCDEVF;  // LCD/EVF出力種別

typedef enum _GUI_OUTPUT_TERMINAL_ {
 GUI_OUTPUT_TERMINAL_HDMI = 0x00000001, // HDMI
 GUI_OUTPUT_TERMINAL_RCA  = 0x00000004, // RCA(Avout)[K519対応]
 GUI_OUTPUT_TERMINAL_SDI  = 0x00000008, // SDI
 GUI_OUTPUT_TERMINAL_NONE = 0 // NONE
} GUI_OUTPUT_TERMINAL;  // 外部出力種別

typedef struct _GUI_ST_OSD_LCD_ {
 GUI_OUTPUT_LCDEVF    mLcdEvf;      // LCD/EVF出力種別
}GUI_ST_OSD_LCD; // LCD/EVF用OSD情報

typedef struct _GUI_ST_DISPLAY_LCD_ {
 BOOL                    mIsOn;        // 表示 / 非表示（TRUE / FALSE）
 GUI_ST_OSD_LCD          mOsd;         // LCD/EVF用OSD情報
}GUI_ST_DISPLAY_LCD;  // LCD/EVF用OSD表示情報


typedef struct _GUI_ST_OSD_LOUT_ {
 GUI_OUTPUT_TERMINAL  mTerminal;   // 外部出力種別
}GUI_ST_OSD_LOUT; // 外部出力用OSD情報

typedef struct _GUI_ST_DISPLAY_LOUT_ {
 BOOL                   mIsOn;        // 表示 / 非表示（TRUE / FALSE）
 GUI_ST_OSD_LOUT        mOsd;         // 外部出力用OSD情報
}GUI_ST_DISPLAY_LOUT;  // 外部出力用OSD表示情報



// OSD出力設定API
// EVFのOSD出力設定を機能的に指示する必要がない時、EVFの設定はされない。
// その際、EVFはGUIで設定を変えなければならないのでK519はGUIで管理に変更
void GUI_setDisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay );
void GUI_setDisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay );
//OSD表示アドレス設定(カラーフォーマット設定対応)
void GUI_DisplayOsdLcdWithColorFormat( UW addr );
void GUI_DisplayOsdLoutWithColorFormat( UW addr );
//OSD外部出力スケール設定
void GUI_OsdLoutScale(BOOL is90percent);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
