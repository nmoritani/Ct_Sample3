#ifndef __GUI_APLIF_H__
#define __GUI_APLIF_H__

# include "kernel.h"
# include "kernel_id.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


//OSD�o�͐ݒ� ��`
typedef enum _GUI_OUTPUT_LCDEVF_ {
 GUI_OUTPUT_LCDEVF_LCD = 0x00000001, // LCD
 GUI_OUTPUT_LCDEVF_EVF  = 0x00000002, // EVF[K519�Ή�]
 GUI_OUTPUT_LCDEVF_NONE = 0 // NONE
} GUI_OUTPUT_LCDEVF;  // LCD/EVF�o�͎��

typedef enum _GUI_OUTPUT_TERMINAL_ {
 GUI_OUTPUT_TERMINAL_HDMI = 0x00000001, // HDMI
 GUI_OUTPUT_TERMINAL_RCA  = 0x00000004, // RCA(Avout)[K519�Ή�]
 GUI_OUTPUT_TERMINAL_SDI  = 0x00000008, // SDI
 GUI_OUTPUT_TERMINAL_NONE = 0 // NONE
} GUI_OUTPUT_TERMINAL;  // �O���o�͎��

typedef struct _GUI_ST_OSD_LCD_ {
 GUI_OUTPUT_LCDEVF    mLcdEvf;      // LCD/EVF�o�͎��
}GUI_ST_OSD_LCD; // LCD/EVF�pOSD���

typedef struct _GUI_ST_DISPLAY_LCD_ {
 BOOL                    mIsOn;        // �\�� / ��\���iTRUE / FALSE�j
 GUI_ST_OSD_LCD          mOsd;         // LCD/EVF�pOSD���
}GUI_ST_DISPLAY_LCD;  // LCD/EVF�pOSD�\�����


typedef struct _GUI_ST_OSD_LOUT_ {
 GUI_OUTPUT_TERMINAL  mTerminal;   // �O���o�͎��
}GUI_ST_OSD_LOUT; // �O���o�͗pOSD���

typedef struct _GUI_ST_DISPLAY_LOUT_ {
 BOOL                   mIsOn;        // �\�� / ��\���iTRUE / FALSE�j
 GUI_ST_OSD_LOUT        mOsd;         // �O���o�͗pOSD���
}GUI_ST_DISPLAY_LOUT;  // �O���o�͗pOSD�\�����



// OSD�o�͐ݒ�API
// EVF��OSD�o�͐ݒ���@�\�I�Ɏw������K�v���Ȃ����AEVF�̐ݒ�͂���Ȃ��B
// ���̍ہAEVF��GUI�Őݒ��ς��Ȃ���΂Ȃ�Ȃ��̂�K519��GUI�ŊǗ��ɕύX
void GUI_setDisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay );
void GUI_setDisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay );
//OSD�\���A�h���X�ݒ�(�J���[�t�H�[�}�b�g�ݒ�Ή�)
void GUI_DisplayOsdLcdWithColorFormat( UW addr );
void GUI_DisplayOsdLoutWithColorFormat( UW addr );
//OSD�O���o�̓X�P�[���ݒ�
void GUI_OsdLoutScale(BOOL is90percent);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
