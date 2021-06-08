#ifndef __GUI_MAIN_H__
#define __GUI_MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "guiif_avc.h"
#include "gdi_config.h"

#include "AvcIf.h"
#include "AvcGuiIf.h"


/* �R�}���h�f�[�^�\���� */
typedef struct gui_cmd_data{
	UW			ComType;		/* API�֐��̃R�}���h�^�C�v */
	UW			Param1;			/* �p�����[�^1 */
	UW			Param2;			/* �p�����[�^2 */
	UW			Param3;			/* �p�����[�^3 */
	UW			Param4;			/* �p�����[�^4 */
	void*		pParam;			/* �|�C���^�p�p�����[�^ */
	void*		pParam2;		/* �|�C���^�p�p�����[�^2 */
} GUI_CMD_DATA;

/* �R�}���h�f�[�^���b�Z�[�W�\���� */
typedef struct hdci_cmd_data_msg {
	T_MSG			t_msg;
	GUI_CMD_DATA	CmdData;
} GUI_CMD_DATA_MSG;

#define COM_TYPE_GUI	0x10

typedef enum {
	GUI_COM_DISPREQ2AVC,
	GUI_COM_MAX,
} GUI_COM_TYPE;

BOOL GUIAVC_isUpdateEnable(GUIAVC_DISP_ID disp_id);

#if 0	//���g�p
////FPGA�ɂ��I�[�f�B�I���[�^�`��
//typedef struct{
//	unsigned short x;
//	unsigned short y;
//	unsigned short w;
//	unsigned short h;
//} GUI_POS_CH;
//
//extern void GUIAVC_setAudioLevelMeterPosSizeLcd(GUI_POS_CH Pos_ch1, GUI_POS_CH Pos_ch2 );
//extern void GUIAVC_setAudioLevelMeterDisplayLcd( BOOL onoff );
//extern void GUIAVC_setAudioLevelMeterInfoLcd(unsigned long base_col_rgba, unsigned long meter_col_rgba, unsigned long peak_col_rgb);
//
////VIEW:�I�[�f�B�I���[�^ ���W
//#define AUDIO_METER_POS_CH1_X	25
//#define AUDIO_METER_POS_CH1_Y	522
//#define AUDIO_METER_POS_CH1_W	144
//#define AUDIO_METER_POS_CH1_H	9
//#define AUDIO_METER_POS_CH2_X	AUDIO_METER_POS_CH1_X
//#define AUDIO_METER_POS_CH2_Y	(AUDIO_METER_POS_CH1_Y + AUDIO_METER_POS_CH1_H)
//#define AUDIO_METER_POS_CH2_W	AUDIO_METER_POS_CH1_W
//#define AUDIO_METER_POS_CH2_H	AUDIO_METER_POS_CH1_H
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
