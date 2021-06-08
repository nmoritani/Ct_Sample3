#ifndef __GUI_TIMESTAMP_API_H__
#define __GUI_TIMESTAMP_API_H__

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/* �F�^�C�v */
typedef enum _GUI_COLOR_TYPE {
	GUI_COLOR_TYPE_422,   /* 4:2:2 */
	GUI_COLOR_TYPE_420,   /* 4:2:0 */
#ifdef WIN32_GUI_SIM
	GUI_COLOR_TYPE_RGB4444,
	GUI_COLOR_TYPE_RGB8888,
#endif
	GUI_COLOR_TYPE_MAX
} GUI_COLOR_TYPE;

/* �F�[�x */
typedef enum _GUI_COLOR_DEPTH {
	GUI_COLOR_DEPTH_8BIT,     /*  8 bit */
	GUI_COLOR_DEPTH_10BIT,    /* 10 bit */
	GUI_COLOR_DEPTH_MAX
} GUI_COLOR_DEPTH;

typedef enum _GUI_TS_TYPE {
	GUI_TS_TYPE_DATETIME,
	GUI_TS_TYPE_DATE,
	GUI_TS_TYPE_TIME
} GUI_TS_TYPE;


/* �^�C���X�^���v����Create����� */
#define GUI_TIMESTAMP_MAX	4

/* �^�C���X�^���v������� */
typedef struct _GUI_TS_FORMAT {
	UW  				rect_w;	/* �`��̈�̕� */
	UW  				rect_h;	/* �`��̈�̍��� */
	GUI_COLOR_TYPE		col_type;	/* �F��ԃ^�C�v */
	GUI_COLOR_DEPTH		col_depth;	/* �Fbit�� */
	GUI_TS_TYPE			type;		/* DATE/TIME/DATE&TIME */
} GUI_TS_FORMAT;

/* �߂�l */
typedef enum _GUI_TS_ER {
	GUI_ER_OK = 0,	//����
	GUI_ER_NOTREADY = -1,	//��t�s��
	GUI_ER_BADARG = -2,		//�����G���[
} GUI_TS_ER;

/* �^�C���X�^���v�`��̈� */
typedef struct _GUI_TS_MEMORY_INFO {
	UW		Yaddr;		// Y�̊J�n�A�h���X(128�̔{��)
	UW		Caddr;		// C�̊J�n�A�h���X(128�̔{��)
	UH		MemWidth;	// ���������iY/C���ʁj
} GUI_TS_MEMORY_INFO;

typedef struct _GUI_TS_INFO {
	GUI_TS_MEMORY_INFO	ts_meminfo;       // ���������
	GUI_TS_MEMORY_INFO	ts_meminfo_lower; // ���������(����bit�p) ��
	GUI_TS_FORMAT		ts_format;        // �^�C���X�^���v�������
} GUI_TS_INFO;

typedef void(*GUI_TS_CALLBACK)(int id);

extern int GUI_CreateTimeStamp(GUI_TS_FORMAT ts_format, GUI_TS_CALLBACK cbfunc);
extern int GUI_GetTimeStamp(int id, GUI_TS_INFO  *info);
extern int GUI_DestroyTimeStamp(int id);
extern void GUI_TsWakeup();

#ifdef	__cplusplus
}
#endif	/* __cplusplus */
	
#endif

