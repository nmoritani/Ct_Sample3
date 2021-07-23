/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   SYS�u���b�N �w�b�_�[�t�@�C�� (�V�~�����[�^�[�p)
 */
#ifndef _SIM_IF_H_
#define _SIM_IF_H_

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* ���ɂ���Ă�������Ȃ������肷��̂� */
	typedef int BOOL;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

/* �L�[�C�x���g */
#define SYS_EVENT_KEY_STATUS_CHANGED	2000
#define SYS_EVENT_TPANEL_RELEASED		4000
#define SYS_EVENT_TPANEL_TOUCHED		4001
#define SYS_EVENT_TPANEL_DRAG			4002
#define SYS_EVENT_TPANEL_SLIDE			4009

#define SYS_POWER_INIT_MODE             0x00                  //!< �N������d�����[�h���芮���܂ł̊���
#define SYS_POWER_RESET_MODE            0x01                  //!< �ċN���҂����[�h
#define SYS_POWER_ON_MODE               0x02                  //!< �d��ON���[�h
#define SYS_POWER_ON_INIT_MODE          0x03                  //!< �d��ON���[�h(BE�N��������)
#define SYS_POWER_ON_TERM_MODE          0x04                  //!< �d��ON���[�h(BE�I��������)
#define SYS_POWER_OFF_MODE              0x05                  //!< �d��OFF���[�h
#define SYS_POWER_HALT_MODE             0x06                  //!< HALT���[�h
#define SYS_POWER_UPDATE_MODE           0x07                  //!< �A�b�v�f�[�g���[�h
#define SYS_PON_SYS_WATCH_MODE          0x00                  //!< �V�X�R���Ď����[�h
#define SYS_PON_APL_WATCH_MODE          0x01                  //!< �A�v���Ď����[�h
#define SYS_REMO_PON_NO_CHANGE          0x00                  //!< �ݒ�ύX�Ȃ�
#define SYS_REMO_PON_MP                 0x01                  //!< �}�����p�b�N�̓d���r�v�L��
#define SYS_REMO_PON_MP_REMO            0x02                  //!< �}�����p�b�N�ƃ����R���̓d���r�v�L��
#define SYS_REMO_RELEASE                0x00FF                //!< �L�[�����[�X
#define SYS_REMO_STOP                   0x0800                //!< ��~
#define SYS_REMO_SEARCH_RWD             0x0802                //!< �T�[�`�߂�
#define SYS_REMO_SEARCH_FWD             0x0803                //!< �T�[�`����
#define SYS_REMO_PAUSE                  0x0806                //!< �ꎞ��~
#define SYS_REMO_SLOW_RWD               0x0807                //!< �X���[�^�R�}�߂�
#define SYS_REMO_PLAY                   0x080A                //!< �Đ�
#define SYS_REMO_SLOW_FWD               0x080F                //!< �X���[�^�R�}����
#define SYS_REMO_POWER                  0x083C                //!< �d��
#define SYS_REMO_SKIP_RWD               0x0849                //!< �X�L�b�v�߂�
#define SYS_REMO_SKIP_FWD               0x084A                //!< �X�L�b�v����
#define SYS_REMO_MENU                   0x0856                //!< ���j���[
#define SYS_REMO_DISPLAY                0x0857                //!< �\���o��
#define SYS_REMO_ENTER                  0x0858                //!< ����
#define SYS_REMO_ZOOM_T                 0x0862                //!< �Y�[���s
#define SYS_REMO_ZOOM_W                 0x0863                //!< �Y�[���v
#define SYS_REMO_PHOTO                  0x0866                //!< �t�H�g�V���b�g
#define SYS_REMO_DATE                   0x0867                //!< �N�����^����
#define SYS_REMO_DELETE                 0x0870                //!< �폜
#define SYS_REMO_S_S                    0x08CC                //!< �B�e�L�^/��~
#define SYS_REMO_FACE_DET               0x098B                //!< �猟�o
#define SYS_REMO_PRE_REC                0x098C                //!< PRE-REC
#define SYS_REMO_UP                     0x09D0                //!< ��
#define SYS_REMO_DOWN                   0x09D1                //!< ��
#define SYS_REMO_RIGHT                  0x09D2                //!< �E
#define SYS_REMO_LEFT                   0x09D3                //!< ��
#define SYS_REMO_MP_POWER               0x0873                //!< �}�����p�b�N �d��
#define SYS_REMO_MP_S_S                 0x0874                //!< �}�����p�b�N S/S
#define SYS_REMO_MP_PHOTO               0x0875                //!< �}�����p�b�N �t�H�g�V���b�g
#define SYS_REMO_MP_ZOOM_T              0x0876                //!< �}�����p�b�N �Y�[���s
#define SYS_REMO_MP_ZOOM_W              0x0877                //!< �}�����p�b�N �Y�[���v
#define SYS_REMO_MP_WB_PLUS             0x0879                //!< �}�����p�b�N WB�ݒ�(B����)
#define SYS_REMO_MP_WB_MINUS            0x0878                //!< �}�����p�b�N WB�ݒ�(R����)
#define SYS_REMO_VCR1_MODE              0x00                  //!< VCR1
#define SYS_REMO_VCR2_MODE              0x02                  //!< VCR2
#define SYS_REMO_VCR3_MODE              0x04                  //!< VCR3
#define SYS_REMO_VCR4_MODE              0x08                  //!< VCR4
#define SYS_NTSC                        0x00                  //!< �m�s�r�b
#define SYS_PAL                         0x01                  //!< �o�`�k
#define SYS_POWER_RESET_STATUS_COLD     0x00                  //!< �d���f����̕��A
#define SYS_POWER_RESET_STATUS_HOT_ON   0x01                  //!< �d���f�����ɍċN�����ēd��ON
#define SYS_POWER_RESET_STATUS_HOT_OFF  0x02                  //!< �d���f�����ɍċN�����ēd��OFF
#define SYS_POWER_RESET_STATUS_BOOT     0x03                  //!< BLDR��BE/CHARGE
#define SYS_TEMP_HIGH_NO_DET            0x00                  //!< �����o
#define SYS_TEMP_HIGH_B                 0x01                  //!< ���x�ُ�B
#define SYS_TEMP_HIGH_A                 0x02                  //!< ���x�ُ�A
#define SYS_USB_CC_NO_CHANGE            0x00                  //!< �v���Ȃ�
#define SYS_USB_CC_CANNOT_USE           0x01                  //!< USB�g�p�֎~
#define SYS_USB_CC_CHRAGE_EXCLUSION     0x02                  //!< USB�[�d���O
#define SYS_USB_CC_MAX100mA             0x03                  //!< 100mA����
#define SYS_USB_CC_MAX500mA             0x04                  //!< 500mA����
#define SYS_USB_CC_MAX900mA             0x05                  //!< 900mA����
#define SYS_USB_CC_MAX1500mA            0x06                  //!< 1500mA����
#define SYS_USB_CC_UNLIMIT              0x07                  //!< ������
#define SYS_FAN_AUTO                    0x00                  //!< ����
#define SYS_FAN_STOP                    0x01                  //!< ��~
#define SYS_FAN_MID_SPEED               0x02                  //!< ����
#define SYS_FAN_HIGH_SPEED              0x03                  //!< ����
#define SYS_FAN_FULL_ON                 0x04                  //!< �t����]
#define SYS_FAN_FULL_OFF                0x05                  //!< �t����]��~
#define SYS_EEP_OK                      0x00                  //!< ���[�h����
#define SYS_EEP_NG_MAIN                 0x01                  //!< ���C�����[�h���s
#define SYS_EEP_NG_BACKUP               0x02                  //!< ���C��/�o�b�N�A�b�v���[�h���s
#define SYS_EEP_NG_INIT                 0x03                  //!< ���C��/�o�b�N�A�b�v/�����l���[�h���s
#define SYS_LCD_CLOSE                   0x00                  //!< LCD��������
#define SYS_LCD_OPEN                    0x01                  //!< LCD���J�������
#define SYS_LCD_REVERSE_OPEN            0x02                  //!< LCD��Ζʂɂ������
#define SYS_LCD_REVERSE_CLOSE           0x03                  //!< LCD�𔽓]���[�������
#define SYS_LCD_OBVERSE_CLOSE           0x04                  //!< LCD�𐳓]���[�������(�c�^���f���p)
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
#define SYS_MODELINFO_CHANGE            0x1C                  //!< �����Y������
#define SYS_MODELINFO_Z268              0x1D                  //!< Z268
#define SYS_REMO_HDCOM_VIDEO_OUT        0x0001                //!< �X�N���[���X�^���o�C
#define SYS_REMO_HDCOM_FULL_SCREEN      0x0002                //!< �\��
#define SYS_REMO_HDCOM_LAYOUT           0x0003                //!< ���C�A�E�g
#define SYS_REMO_HDCOM_PC               0x0004                //!< PC
#define SYS_REMO_HDCOM_CAM_SUB          0x0005                //!< �T�u�J����
#define SYS_REMO_HDCOM_CAM_MAIN         0x0006                //!< ���L�I��
#define SYS_REMO_HDCOM_START            0x0007                //!< �J�n
#define SYS_REMO_HDCOM_MENU             0x0008                //!< ���j���[
#define SYS_REMO_HDCOM_END              0x0009                //!< �I��
#define SYS_REMO_HDCOM_LEFT             0x000A                //!< ��
#define SYS_REMO_HDCOM_RIGHT            0x000B                //!< �E
#define SYS_REMO_HDCOM_UP               0x000C                //!< ��
#define SYS_REMO_HDCOM_DOWN             0x000D                //!< ��
#define SYS_REMO_HDCOM_ENTER            0x000E                //!< ����
#define SYS_REMO_HDCOM_HOME             0x000F                //!< �z�[��
#define SYS_REMO_HDCOM_BACK             0x0010                //!< �߂�
#define SYS_REMO_HDCOM_BULUE            0x0011                //!< ��
#define SYS_REMO_HDCOM_RED              0x0012                //!< ��
#define SYS_REMO_HDCOM_GREEN            0x0013                //!< ��
#define SYS_REMO_HDCOM_YELLOW           0x0014                //!< ��
#define SYS_REMO_HDCOM_VOLUME_UP        0x0015                //!< ���ʁ{
#define SYS_REMO_HDCOM_VOLUME_DOWN      0x0016                //!< ���ʁ|
#define SYS_REMO_HDCOM_TONE_UP          0x0017                //!< ������
#define SYS_REMO_HDCOM_TONE_DOWN        0x0018                //!< ������
#define SYS_REMO_HDCOM_CAM_CTRL         0x0019                //!< �J��������
#define SYS_REMO_HDCOM_STATUS           0x001A                //!< �󋵕\��
#define SYS_REMO_HDCOM_CONTACT          0x001B                //!< �A�h���X��
#define SYS_REMO_HDCOM_MIC_MUTE         0x001C                //!< �}�C�N�I�t
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
#define SYS_REMO_HDCOM_ID_SWITCHED      0x0000                //!< ID�ύX�ʒm
#define SYS_REMO_HDCOM_ID_NOTIFY        0x002F                //!< ID�ʒm
#define SYS_REMO_HDCOM_RELEASE          0xFFFF                //!< �L�[�����[�X
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
#define SYS_REMO_AW_UP                  0x0016                //!< ��
#define SYS_REMO_AW_HOME                0x0017                //!< HOME
#define SYS_REMO_AW_LEFT                0x0018                //!< ��
#define SYS_REMO_AW_OK                  0x0019                //!< OK
#define SYS_REMO_AW_RIGHT               0x001A                //!< ��
#define SYS_REMO_AW_HIDDEN_BUTTON1      0x001B                //!< HIDDEN BUTTON1
#define SYS_REMO_AW_DOWN                0x001C                //!< ��
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
#define SYS_REMO_AW_RELEASE             0xFFFF                //!< �L�[�����[�X
#define SYS_KEYAW_RELEASE               0x00                  //!< �L�[�����[�X
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
#define SYS_KEYAW_UP                    0x10                  //!< ��
#define SYS_KEYAW_LEFT                  0x11                  //!< ��
#define SYS_KEYAW_RIGHT                 0x12                  //!< ��
#define SYS_KEYAW_DOWN                  0x13                  //!< ��
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
#define SYS_KEYAW_UP_LEFT               0x21                  //!< ��+ ��
#define SYS_KEYAW_UP_RIGHT              0x22                  //!< ��+ ��
#define SYS_KEYAW_DOWN_LEFT             0x23                  //!< ��+ ��
#define SYS_KEYAW_DOWN_RIGHT            0x24                  //!< ��+ ��
#define SYS_KEYAW_OPT_ON                0x25                  //!< PinP Display
#define SYS_KEYAW_OPT_OFF               0x26                  //!< Control
#define SYS_KEYAW_AUTO_IRIS             0x27                  //!< A/IRIS
#define SYS_KEYAW_MANUAL_IRIS           0x28                  //!< M/IRIS
#define SYS_KEYAW_IRIS_OPEN             0x29                  //!< IRIS+
#define SYS_KEYAW_IRIS_CLOSE            0x2A                  //!< IRIS-

#define SYS_NO_REQ                      0x00                  //!< �v���Ȃ�
#define SYS_PON_REQ                     0x01                  //!< �d��ON�v��
#define SYS_STANBY_REQ                  0x02                  //!< STANBY�v��
#define SYS_DRAM_NORMAL                 0x00                  //!< �ʏ탂�[�h
#define SYS_DRAM_USTREAM                0x01                  //!< USTREAM���[�h
#define SYS_DRAM_DLNA                   0x02                  //!< DLNA���[�h
#define SYS_24_00P                      0x01                  //!< 24.00p
#define SYS_23_98P                      0x02                  //!< 23.98p
#define SYS_BATT_T_NO_DATA              0x00                  //!< BATT_T�f�[�^�Ȃ�
#define SYS_BATT_T_MIN                  0x01                  //!< BATT_T�f�[�^�ŏ��l
#define SYS_INIT                        0x00                  //!< �������/���o��
#define SYS_STANBY                      0x01                  //!< �X�^���o�C
#define SYS_UNDETECT                    0x02                  //!< �񌟏o
#define SYS_DETECT                      0x03                  //!< ���o
#define SYS_DEVICE_ERROR                0x04                  //!< �f�o�C�X�G���[
#define SYS_FPGA_INIT                   0x00                  //!< �������
#define SYS_FPGA_BOOT                   0x01                  //!< �u�[�g��
#define SYS_FPGA_OK                     0x02                  //!< �u�[�g����
#define SYS_FPGA_NG                     0x03                  //!< �u�[�g���s
#define SYS_POVCAM_CAMHEAD              0x00                  //!< �J�����w�b�h�A�g���[�h
#define SYS_POVCAM_RECORDER             0x01                  //!< ���R�[�_���[�h
#define SYS_CAM_NORMAL_PROC             0x00                  //!< �ʏ폈��
#define SYS_CAM_LOW_VOLTAGE_PROC        0x01                  //!< ��d���p����
#define SYS_DATE_NO_REQ                 0x00                  //!< �v���Ȃ�/�v���̏�������
#define SYS_DATE_ALARM_REQ              0x01                  //!< �A���[���N���v��
#define SYS_DATE_CHANGE_REQ             0x02                  //!< �����ύX�v��
#define SYS_DATE_STOP_REQ               0x03                  //!< ������~�v��
#define SYS_KEY_REC_MODE                0x00                  //!< ����B�e
#define SYS_KEY_STILL_REC_MODE          0x01                  //!< �Î~��B�e
#define SYS_KEY_PLAY_MODE               0x02                  //!< �Đ�
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
#define SYS_KEY_POWER                   0x0000000000000001ULL //!< �d��
#define SYS_KEY_UP                      0x0000000000000002ULL //!< ��
#define SYS_KEY_DOWN                    0x0000000000000004ULL //!< ��
#define SYS_KEY_LEFT                    0x0000000000000008ULL //!< ��
#define SYS_KEY_RIGHT                   0x0000000000000010ULL //!< �E
#define SYS_KEY_ENTER                   0x0000000000000020ULL //!< ����
#define SYS_KEY_PHOTO_HALF              0x0000000000000040ULL //!< �t�H�g�V���b�g������
#define SYS_KEY_PHOTO                   0x0000000000000080ULL //!< �t�H�g�V���b�g
#define SYS_KEY_S_S                     0x0000000000000100ULL //!< S/S
#define SYS_KEY_MODE                    0x0000000000000200ULL //!< �B�e/�Đ�
#define SYS_KEY_PRE_REC                 0x0000000000000400ULL //!< PRE_REC
#define SYS_KEY_BALANCE                 0x0000000000000800ULL //!< �X���␳
#define SYS_KEY_OIS                     0x0000000000001000ULL //!< OIS
#define SYS_KEY_IA                      0x0000000000002000ULL //!< iA
#define SYS_KEY_CAM_FUNC                0x0000000000004000ULL //!< �J�����t�@���N�V����
#define SYS_KEY_LIGHT                   0x0000000000008000ULL //!< LED���C�g
#define SYS_KEY_DELETE                  0x0000000000010000ULL //!< �폜
#define SYS_KEY_MENU                    0x0000000000020000ULL //!< ���j���[1
#define SYS_KEY_P_ZOOM_T                0x0000000000040000ULL //!< �Y�[���s(LCD�p�l��)
#define SYS_KEY_P_ZOOM_W                0x0000000000080000ULL //!< �Y�[���v(LCD�p�l��)
#define SYS_KEY_P_S_S                   0x0000000000100000ULL //!< S/S(LCD�p�l��)
#define SYS_KEY_P_QMENU                 0x0000000000200000ULL //!< �N�C�b�N���j���[(LCD�p�l��)
#define SYS_KEY_LONG_REC                0x0000000000400000ULL //!< LongRec
#define SYS_KEY_AF_AE                   0x0000000000800000ULL //!< AF/AE
#define SYS_KEY_LIGHT_DELETE            0x0000000001000000ULL //!< LED���C�g/�폜
#define SYS_KEY_60P                     0x0000000002000000ULL //!< 60P
#define SYS_KEY_MENU2                   0x0000000004000000ULL //!< ���j���[2(MENU�L�[��2�ȏ゠��ꍇ)
#define SYS_KEY_P_LCD                   0x0000000008000000ULL //!< PowerLCD
#define SYS_KEY_REC_CHECK               0x0000000010000000ULL //!< REC_CHECK
#define SYS_KEY_SHIFT                   0x0000000020000000ULL //!< SHIFT
#define SYS_KEY_AUDIO_PLUS              0x0000000040000000ULL //!< AUDIO(+)�L�[
#define SYS_KEY_AUDIO_MINUS             0x0000000080000000ULL //!< AUDIO(-)�L�[
#define SYS_KEY_MNL_RING_PLUS           0x0000000100000000ULL //!< MNL�����O(+)
#define SYS_KEY_MNL_RING_MINUS          0x0000000200000000ULL //!< MNL�����O(-)
#define SYS_KEY_PLAY                    0x0000000400000000ULL //!< �Đ��L�[
#define SYS_KEY_STOP                    0x0000000800000000ULL //!< ��~�L�[
#define SYS_KEY_PAUSE                   0x0000001000000000ULL //!< �ꎞ��~�L�[
#define SYS_KEY_SKIP_RWD                0x0000002000000000ULL //!< �X�L�b�v�߂��L�[
#define SYS_KEY_SKIP_FWD                0x0000004000000000ULL //!< �X�L�b�v����L�[
#define SYS_KEY_SLOW_RWD                0x0000008000000000ULL //!< �X���[/�R�}�߂��L�[
#define SYS_KEY_SLOW_FWD                0x0000010000000000ULL //!< �X���[/�R�}����L�[
#define SYS_KEY_SEARCH_RWD              0x0000020000000000ULL //!< �T�[�`�߂��L�[
#define SYS_KEY_SEARCH_FWD              0x0000040000000000ULL //!< �T�[�`����L�[
#define SYS_KEY_DISPLAY                 0x0000080000000000ULL //!< �\���o�̓L�[
#define SYS_KEY_DATE_TIME               0x0000100000000000ULL //!< �N����/�����L�[
#define SYS_KEY_WB_PLUS                 0x0000200000000000ULL //!< WB(+)�L�[
#define SYS_KEY_WB_MINUS                0x0000400000000000ULL //!< WB(-)�L�[
#define SYS_KEY_ZOOM_T                  0x0000800000000000ULL //!< �Y�[���s(�����R���A�Y�[���X���C�h�L�[)
#define SYS_KEY_ZOOM_W                  0x0001000000000000ULL //!< �Y�[���v(�����R���A�Y�[���X���C�h�L�[)
#define SYS_KEY_LIVE                    0x0002000000000000ULL //!< LIVE
#define SYS_KEY_INIT                    0x0004000000000000ULL //!< INIT
#define SYS_KEY_WIFI                    0x0008000000000000ULL //!< WiFi
#define SYS_KEY_HOLD                    0x0010000000000000ULL //!< HOLD
#define SYS_KEY_MOVIE_STILL             0x0020000000000000ULL //!< ����/�Î~��
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
#define SYS_KEY2_IRIS_PLUS              0x0000000000008000ULL //!< IRIS�����O +����
#define SYS_KEY2_IRIS_MINUS             0x0000000000010000ULL //!< IRIS�����O -����
#define SYS_KEY2_CONV_PLUS              0x0000000000020000ULL //!< CONV�����O +����
#define SYS_KEY2_CONV_MINUS             0x0000000000040000ULL //!< CONV�����O -����
#define SYS_KEY2_FOCUS_PLUS             0x0000000000080000ULL //!< FOCUS�����O +����
#define SYS_KEY2_FOCUS_MINUS            0x0000000000100000ULL //!< FOCUS�����O -����
#define SYS_KEY2_ZOOM_PLUS              0x0000000000200000ULL //!< ZOOM�����O +����
#define SYS_KEY2_ZOOM_MINUS             0x0000000000400000ULL //!< ZOOM�����O -����
#define SYS_KEY2_FOCUS                  0x0000000000800000ULL //!< FOCUS AUTO/MNL/��
#define SYS_KEY2_WIRE_SS                0x0000000001000000ULL //!< ���C���[�h�����R�� SS
#define SYS_KEY2_WIRE_CONV_PLUS         0x0000000002000000ULL //!< ���C���[�h�����R�� CONV +����
#define SYS_KEY2_WIRE_CONV_MINUS        0x0000000004000000ULL //!< ���C���[�h�����R�� CONV -����
#define SYS_KEY2_FA                     0x0000000008000000ULL //!< FA
#define SYS_KEY2_PUSH_AF                0x0000000020000000ULL //!< PUSH_AF
#define SYS_KEY2_GAIN                   0x0000000040000000ULL //!< GAIN
#define SYS_KEY2_SHUTTER                0x0000000080000000ULL //!< SHUTTER
#define SYS_KEY2_FRONT_S_S              0x0000000100000000ULL //!< FRONT S/S
#define SYS_KEY2_WFM                    0x0000000200000000ULL //!< WFM
#define SYS_KEY2_A_IRIS_LEVEL           0x0000000400000000ULL //!< A. IRIS LEVEL
#define SYS_KEY2_AWB                    0x0000000800000000ULL //!< AWB
#define SYS_KEY2_WB_AUTO_MNL            0x0000001000000000ULL //!< WB(AUTO/MNL�ؑ�)
#define SYS_KEY2_WB_A_B_PRST            0x0000002000000000ULL //!< WB(Ach/Bch/�v���Z�b�g�ؑ�)
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
#define SYS_BATT_DISCONNECT             0x00                  //!< ���ڑ�
#define SYS_BATT_NO_CHECK               0x01                  //!< ���F��
#define SYS_BATT_CHECKING               0x02                  //!< �F�ؒ�/�c�ʌv�Z��
#define SYS_BATT_OK_REM_ENABLE          0x03                  //!< �F�؂n�j/�c�ʌv�Z�n�j(���\���L��->�����o�b�e��)
#define SYS_BATT_OK_REM_DISABLE         0x04                  //!< �F�؂n�j/�c�ʌv�Z�n�j(���\������->3rd Party�o�b�e��)
#define SYS_BATT_ERR                    0x05                  //!< �ʐM�G���[
#define SYS_BATT_NG                     0x06                  //!< �F�؂m�f
#define SYS_BATT_TYPE_1P                0x00                  //!< 1�p��(�܂��͕s��)
#define SYS_BATT_TYPE_2P                0x01                  //!< 2�p��
#define SYS_BATT_TYPE_4P                0x02                  //!< 4�p��
#define SYS_BATT_TYPE_6P                0x03                  //!< 6�p��
#define SYS_BATT_TYPE_4P_QI             0x04                  //!< 4�p��(Qi�Ή�)
#define SYS_BATT_TYPE_3RD               0x06                  //!< 3rd�p�[�e�B�[�o�b�e���[
#define SYS_BATT_TYPE_CHECKING_D        0x0D                  //!< ���蒆[��ʔ��蒆]
#define SYS_BATT_TYPE_CHECKING_T        0x0E                  //!< ���蒆[�ڑ����蒆]
#define SYS_BATT_TYPE_FORCE_CHANGE      0x0F                  //!< ��L�ȊO�̒l(�d�r�p�����[�^����Load�p)<4bit�̍ő�l>
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
#define SYS_BATT_TYPE2_UNKNOWN          0x03                  //!< �ʐM�� or ���ڑ� or VBR�V���[�Y�ȊO
#define SYS_BATT_TYPE2_ERR              0x04                  //!< �ʐM�G���[ or ��Ή��o�b�e��
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
#define SYS_LANC_FOCUS_FAR              0x0000000000400000ULL //!< FOCUS FAR�葬(LancFocusSw��0�Œʒm)
#define SYS_LANC_FOCUS_NEAR             0x0000000000800000ULL //!< FOCUS NEAR�葬(LancFocusSw��0�Œʒm)
#define SYS_LANC_ZOOM_TELE              0x0000000001000000ULL //!< ZOOM TELE�葬(LancZoomSw��0�Œʒm)
#define SYS_LANC_ZOOM_WIDE              0x0000000002000000ULL //!< ZOOM WIDE�葬(LancZoomSw��0�Œʒm)

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
/* �����������������I��(DB_Define)�������� */
#define SYS_KEY_NONE                    0x0000000000000000ULL //!< �����L�[�Ȃ�
#define SYS_KEY2_NONE                   0x0000000000000000ULL //!< �����L�[�Ȃ�    


typedef struct SYS_KEY_STATUS
{
	unsigned char Mode;				// �f�b�L�̃��[�h�_�C�����܂��̓��[�h�X�C�b�`�̏��(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	char		  Zoom;				// �f�b�L�̃Y�[���L�[�̏��(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	unsigned char MnlSw;			// �f�b�L�̃}�j���A��SW(iA/Mnl/MF�X���C�hSW)���(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	_int64		  Deck;				// �f�b�L�̃L�[���(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	_int64		  Remocon;			// ���[�r�[�����R���̃L�[���(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	_int64		  MarinePack;		// �}�����p�b�N�����R���̃L�[���(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	_int64		  AwRemocon;		// AW�����R���̃L�[���(�ڍׂ� @ref Key_Status "�L�[���"���Q��)
	_int64		  Deck2;			// �f�b�L�̃L�[���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char FocusSw;			// �f�b�L��FOCUS�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char GainSw;			// �f�b�L��GAIN�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char WbSw;				// �f�b�L��WB�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char NdSw;				// �f�b�L��ND FILTER�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char WireIrisSw;		// ���C���[�h�����R����IRIS�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char WireFocusSw;		// ���C���[�h�����R����FOCUS�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char DispSw;			// �f�b�L��DISP�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char InOutSw;			// �f�b�L��IN/OUT�ؑփX�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char Input1SelSw;		// �f�b�L��INPUT1 SELECT�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char Input2SelSw;		// �f�b�L��INPUT2 SELECT�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char AudioCh1Sw;		// �f�b�L��AUDIO CH1�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char AudioCh2Sw;		// �f�b�L��AUDIO CH2�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char AudioMode1Sw;		// �f�b�L��AUDIO CH1 AUTO/MANU�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char AudioMode2Sw;		// �f�b�L��AUDIO CH2 AUTO/MANU�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char LedLightSw;		// �f�b�L��LED_LIGHT�ؑփX�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char LcdSw;			// LCD��LCD_MIRROR/ROTATE�ؑփX�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char UserSw;			// �f�b�L�̃��[�U�[�g�O���X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char LockSw;			// �f�b�L�̃L�[���b�N�X�C�b�`���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	_int64	      LancSw;			//!< LANC�����R�� SW���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char LancFocusSw;		//!< LANC�����R�� Focus SW���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)
	unsigned char LancZoomSw;		//!< LANC�����R�� Zoom SW���(�ڍׂ� @ref Key_Status2 "�L�[���(PRO/SEMIPRO��p)"���Q��)

} SYS_KEY_STATUS;

/* --- �^�b�`�p�l����` --- */

/* �X���C�h���� */
#define SYS_TPANEL_SLIDE_UP				0		//!< �����
#define SYS_TPANEL_SLIDE_DOWN			1		//!< ������
#define SYS_TPANEL_SLIDE_LEFT			2		//!< ������
#define SYS_TPANEL_SLIDE_RIGHT			3		//!< �E����

typedef struct SYS_TPANEL
{
	unsigned int	Touched			:1; // �^�b�`���(TRUE:�^�b�`, FALSE:�����[�X)
	int				X				:13;// �^�b�`�w���W(�^�b�`���ĂȂ��ꍇ�͕s��)
	int				Y				:13;// �^�b�`�x���W(�^�b�`���ĂȂ��ꍇ�͕s��)

	int				SlideStartX		:13;// �X���C�h�J�n���̂����^�b�`�w���W
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	int				SlideStartY		:13;// �X���C�h�J�n���̃^�b�`�x���W
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	int				SlidePreX		:13;// �O��ʒm�����^�b�`�w���W
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	int				SlidePreY		:13;// �O��ʒm�����^�b�`�x���W
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	unsigned int	SlideSpeed		:5; // �X���C�h���x
										// ��̓I�ɂ͉��L�̒l���Ƃ�
										// =>8	   :�t���b�N(�f���������悤�Ƀ^�b�`���鑀��)
										// =>1�`7  :�X���C�h(7:�ő�)
										// =>0	   :�X���C�h��~
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	unsigned int	SlideDir		:2; // �X���C�h����
										// ��̓I�ɂ͉��L�̒l���Ƃ�
										// =>SYS_TPANEL_SLIDE_UP   :�����
										// =>SYS_TPANEL_SLIDE_DOWN :������
										// =>SYS_TPANEL_SLIDE_LEFT :������
										// =>SYS_TPANEL_SLIDE_RIGHT	   :�E����
										// SYS_EVENT_TPANEL_SLIDE�C�x���g�ȊO�̏ꍇ�͕s��

	unsigned int	Mode			:1; // �L�����u���[�V�����̃��[�h
										// ��̓I�ɂ͉��L�̒l���Ƃ�
										// =>SYS_TPANEL_POSI_NO_SAVE_MODE  :�^�b�`���W��EEPROM�ɕۑ����Ȃ����[�h
										// =>SYS_TPANEL_POSI_SAVE_MODE	   :�^�b�`���W��EEPROM�ɕۑ����郂�[�h(�H���p)

	unsigned int	Mark			:5; // �L�����u���[�V�����ŗL���ȃ}�[�N
										// ��̓I�ɂ͉��L�̃r�b�g�n�q�̒l���Ƃ�
										// =>SYS_TPANEL_LEFT_UP_MARK   :����}�[�N
										// =>SYS_TPANEL_LEFT_DOWN_MARK :�����}�[�N
										// =>SYS_TPANEL_RIGHT_UP_MARK  :�E��}�[�N
										// =>SYS_TPANEL_RIGHT_DOWN_MARK:�E���}�[�N
										// =>SYS_TPANEL_CENTER_MARK	   :�����}�[�N

	unsigned int	TouchedMark		:5; // �L�����u���[�V�����Ń^�b�`�����}�[�N
										// ��̓I�ɂ͉��L�̃r�b�g�n�q�̒l���Ƃ�
										// =>SYS_TPANEL_LEFT_UP_MARK   :����}�[�N
										// =>SYS_TPANEL_LEFT_DOWN_MARK :�����}�[�N
										// =>SYS_TPANEL_RIGHT_UP_MARK  :�E��}�[�N
										// =>SYS_TPANEL_RIGHT_DOWN_MARK:�E���}�[�N
										// =>SYS_TPANEL_CENTER_MARK	   :�����}�[�N
} SYS_TPANEL;

typedef union SYS_EVENT_DATA
{
	SYS_KEY_STATUS Key;			/* �L�[��� */
	SYS_TPANEL TPanel;			/* �^�b�`�p�l�� �^�b�`���/�L�����u���[�V������� */
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
