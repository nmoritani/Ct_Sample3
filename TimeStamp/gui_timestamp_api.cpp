#include <itron.h>

#include "gui_timestamp_task.h"
#include "gui_timestamp_api.h"
#include "CtTimeStamp.h"

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/*
	パラメータ：
	 GUI_TS_FORMAT			ts_format;	// タイムスタンプ書式情報
	 GUI_CALLBACK_FUNC		cbfunc;		// 完了コールバック関数
	 typedef void (*GUI_CALLBACK_FUNC)(UH id);
	戻り値：0以上:id値, 0未満:GUI_ER
	種別：非同期
	概要：
	ts_formatで指定されたサイズ、色フォーマットでタイムスタンプを描画する。
	描画準備完了時に引数で指定されたコールバックcbfuncを実行する。
	　　　これ以降、タイムスタンプを特定メモリに描画する。
	　　　（メモリアドレスの取得方法は次ページ参照）
	タイムスタンプは２種類のサイズで作成する必要がある（記録用・サムネイル用）為、引数のidで区別する。
*/
int GUI_CreateTimeStamp(GUI_TS_FORMAT ts_format, GUI_TS_CALLBACK cbfunc)
{
	GuiTsInfo info;
	memset(&info, 0, sizeof(info));

	// 引数チェックと定義値変換
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
	パラメータ：
	 UH		id;	// ID (0～1)
	 GUI_TIMESTAMP_INFO	*ts_info  	// タイムスタンプ描画領域情報
	戻り値：	GUI_ER
	種別：同期
	概要：
	idで指定した、タイムスタンプが描画されている領域の先頭アドレスYaddr, Caddrを返す。
	ts_infoには、 GUI_StartTimeStamp()で指定された「タイムスタンプ書式情報」を返す。（受け取り側確認用）
	タイムスタンプ描画準備が出来ていない区間でコールされると戻り値でGUI_ERR_NOTREADYを返す。
*/
int GUI_GetTimeStamp(int id, GUI_TS_INFO  *ts_info)
{
	// 引数チェック
	if (id >= GUI_TIMESTAMP_MAX)	return GUI_ER_BADARG;
	if (ts_info == NULL) return GUI_ER_BADARG;

	if (GUI_TS_Get(id, ts_info) != 0) {
		return GUI_ER_NOTREADY;
	}

	return GUI_ER_OK;
}

/*
	パラメータ：
	 UH	id;	// ID (0～1)
	戻り値：	GUI_ER
	種別：同期
	概要：
	idで指定したタイムスタンプ描画を停止する。
	記録フォーマットが変わる際も一旦Stopする事。
*/
int GUI_DestroyTimeStamp(int id)
{
	// 引数チェック
	if (id >= GUI_TIMESTAMP_MAX)	return GUI_ER_BADARG;

	if (GUI_TS_Destroy(id) != 0) {
		return GUI_ER_NOTREADY;
	}

	return GUI_ER_OK;
}

#ifdef	__cplusplus
}
#endif	/* __cplusplus */
