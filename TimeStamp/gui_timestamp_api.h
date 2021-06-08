#ifndef __GUI_TIMESTAMP_API_H__
#define __GUI_TIMESTAMP_API_H__

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/* 色タイプ */
typedef enum _GUI_COLOR_TYPE {
	GUI_COLOR_TYPE_422,   /* 4:2:2 */
	GUI_COLOR_TYPE_420,   /* 4:2:0 */
#ifdef WIN32_GUI_SIM
	GUI_COLOR_TYPE_RGB4444,
	GUI_COLOR_TYPE_RGB8888,
#endif
	GUI_COLOR_TYPE_MAX
} GUI_COLOR_TYPE;

/* 色深度 */
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


/* タイムスタンプ同時Create数上限 */
#define GUI_TIMESTAMP_MAX	4

/* タイムスタンプ書式情報 */
typedef struct _GUI_TS_FORMAT {
	UW  				rect_w;	/* 描画領域の幅 */
	UW  				rect_h;	/* 描画領域の高さ */
	GUI_COLOR_TYPE		col_type;	/* 色空間タイプ */
	GUI_COLOR_DEPTH		col_depth;	/* 色bit数 */
	GUI_TS_TYPE			type;		/* DATE/TIME/DATE&TIME */
} GUI_TS_FORMAT;

/* 戻り値 */
typedef enum _GUI_TS_ER {
	GUI_ER_OK = 0,	//成功
	GUI_ER_NOTREADY = -1,	//受付不可
	GUI_ER_BADARG = -2,		//引数エラー
} GUI_TS_ER;

/* タイムスタンプ描画領域 */
typedef struct _GUI_TS_MEMORY_INFO {
	UW		Yaddr;		// Yの開始アドレス(128の倍数)
	UW		Caddr;		// Cの開始アドレス(128の倍数)
	UH		MemWidth;	// メモリ幅（Y/C共通）
} GUI_TS_MEMORY_INFO;

typedef struct _GUI_TS_INFO {
	GUI_TS_MEMORY_INFO	ts_meminfo;       // メモリ情報
	GUI_TS_MEMORY_INFO	ts_meminfo_lower; // メモリ情報(下位bit用) ※
	GUI_TS_FORMAT		ts_format;        // タイムスタンプ書式情報
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

