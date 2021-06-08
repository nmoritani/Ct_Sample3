#include <itron.h>

#include "gui_timestamp_task.h"
#include "gui_timestamp_api.h"
#include "CtTimeStamp.h"

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/*
	�p�����[�^�F
	 GUI_TS_FORMAT			ts_format;	// �^�C���X�^���v�������
	 GUI_CALLBACK_FUNC		cbfunc;		// �����R�[���o�b�N�֐�
	 typedef void (*GUI_CALLBACK_FUNC)(UH id);
	�߂�l�F0�ȏ�:id�l, 0����:GUI_ER
	��ʁF�񓯊�
	�T�v�F
	ts_format�Ŏw�肳�ꂽ�T�C�Y�A�F�t�H�[�}�b�g�Ń^�C���X�^���v��`�悷��B
	�`�揀���������Ɉ����Ŏw�肳�ꂽ�R�[���o�b�Ncbfunc�����s����B
	�@�@�@����ȍ~�A�^�C���X�^���v����胁�����ɕ`�悷��B
	�@�@�@�i�������A�h���X�̎擾���@�͎��y�[�W�Q�Ɓj
	�^�C���X�^���v�͂Q��ނ̃T�C�Y�ō쐬����K�v������i�L�^�p�E�T���l�C���p�j�ׁA������id�ŋ�ʂ���B
*/
int GUI_CreateTimeStamp(GUI_TS_FORMAT ts_format, GUI_TS_CALLBACK cbfunc)
{
	GuiTsInfo info;
	memset(&info, 0, sizeof(info));

	// �����`�F�b�N�ƒ�`�l�ϊ�
	switch (ts_format.col_type) {
	case GUI_COLOR_TYPE_422: info.coloFormat = Format_YUV422;	break;
	case GUI_COLOR_TYPE_420: info.coloFormat = Format_YUV420;	break;
#ifdef WIN32_GUI_SIM
	case GUI_COLOR_TYPE_RGB4444: info.coloFormat = Format_RGBA4444;	break;
	case GUI_COLOR_TYPE_RGB8888: info.coloFormat = Format_RGBA8888;	break;
#endif
	default:
		return GUI_ER_BADARG;
	}

	switch(ts_format.col_depth) {
	case GUI_COLOR_DEPTH_8BIT:	info.colorDepth = 8;	break;
	case GUI_COLOR_DEPTH_10BIT: info.colorDepth = 10;	break;
	default:
		return GUI_ER_BADARG;
	}

	switch(ts_format.type) {
	case GUI_TS_TYPE_DATE:		info.DispMode = CtTimeStamp::CtTsDispDate;			break;
	case GUI_TS_TYPE_TIME:		info.DispMode = CtTimeStamp::CtTsDispTime;			break;
	case GUI_TS_TYPE_DATETIME:	info.DispMode = CtTimeStamp::CtTsDispDateTime;		break;
	default:
		return GUI_ER_BADARG;
	}

	if (cbfunc == NULL)	return GUI_ER_BADARG;

	info.Size.width = (short)ts_format.rect_w;
	info.Size.height = (short)ts_format.rect_h;

	int id = GUI_TS_Init(&info);
	if (id < 0) return GUI_ER_NOTREADY;

	int ret = GUI_TS_Create(id, cbfunc);
	if (ret != 0) {
		return GUI_ER_NOTREADY;
	}

	return id;
}

/*
	�p�����[�^�F
	 UH		id;	// ID (0�`1)
	 GUI_TIMESTAMP_INFO	*ts_info  	// �^�C���X�^���v�`��̈���
	�߂�l�F	GUI_ER
	��ʁF����
	�T�v�F
	id�Ŏw�肵���A�^�C���X�^���v���`�悳��Ă���̈�̐擪�A�h���XYaddr, Caddr��Ԃ��B
	ts_info�ɂ́A GUI_StartTimeStamp()�Ŏw�肳�ꂽ�u�^�C���X�^���v�������v��Ԃ��B�i�󂯎�葤�m�F�p�j
	�^�C���X�^���v�`�揀�����o���Ă��Ȃ���ԂŃR�[�������Ɩ߂�l��GUI_ERR_NOTREADY��Ԃ��B
*/
int GUI_GetTimeStamp(int id, GUI_TS_INFO  *ts_info)
{
	// �����`�F�b�N
	if (id >= GUI_TIMESTAMP_MAX)	return GUI_ER_BADARG;
	if (ts_info == NULL) return GUI_ER_BADARG;

	if (GUI_TS_Get(id, ts_info) != 0) {
		return GUI_ER_NOTREADY;
	}

	return GUI_ER_OK;
}

/*
	�p�����[�^�F
	 UH	id;	// ID (0�`1)
	�߂�l�F	GUI_ER
	��ʁF����
	�T�v�F
	id�Ŏw�肵���^�C���X�^���v�`����~����B
	�L�^�t�H�[�}�b�g���ς��ۂ���UStop���鎖�B
*/
int GUI_DestroyTimeStamp(int id)
{
	// �����`�F�b�N
	if (id >= GUI_TIMESTAMP_MAX)	return GUI_ER_BADARG;

	if (GUI_TS_Destroy(id) != 0) {
		return GUI_ER_NOTREADY;
	}

	return GUI_ER_OK;
}

#ifdef	__cplusplus
}
#endif	/* __cplusplus */
