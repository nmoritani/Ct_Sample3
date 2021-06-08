#ifndef __GUI_DMA_CMD_H__
#define __GUI_DMA_CMD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <kernel.h>
#include "SysIf.h"
#include "mdmac.h"
#include    "smDebugSerial.h"
#include "../../../Include/gdi.h"


#define GUISYNCFLG_DMA_FINISHED					(1 << 1)

/* コマンドデータ構造体 */
typedef struct gui_dma_cmd_data{
	UW			ComType;		/* API関数のコマンドタイプ */
	UW			Param1;			/* パラメータ1 */
	UW			Param2;			/* パラメータ2 */
	UW			Param3;			/* パラメータ3 */
	UW			Param4;			/* パラメータ4 */
	void*		pParam;			/* ポインタ用パラメータ */
	void*		pParam2;		/* ポインタ用パラメータ2 */
} GUI_DMA_CMD_DATA;

/* コマンドデータメッセージ構造体 */
typedef struct hdci_dma_cmd_data_msg {
	T_MSG			t_msg;
	GUI_DMA_CMD_DATA	CmdData;
} GUI_DMA_CMD_DATA_MSG;

//#define COM_TYPE_GUI	0x10

typedef enum {
	GUI_DMA_COM_EXTREQ,
	GUI_DMA_COM_MAX,
} GUI_DMA_COM_TYPE;

typedef enum {
	GUI_DMA_COM_EXT_DRAW_FILLRECT_SIMPLE,
	GUI_DMA_COM_EXT_MAX,
} GUI_DMA_COM_EXT_TYPE;

typedef struct _gui_dma_fillrect_param
{
	UW		skip_size;
	UW		data_size;
	UW		size;
	UW		color;
	UW		dst_adr;
	
} gui_dma_fillrect_param;

typedef struct _gui_dma_pack
{
	GDI_DRAW_BUFFER	buffer;
	INT	result;
	
} gui_dma_pack;

typedef struct _gui_dma_pack_fillrect_simple
{
	GDI_DRAW_BUFFER	buffer;
	INT	result;
	
	GDI_REGION	region;
	UW	forecolor;
	
} gui_dma_pack_fillrect_simple;


extern void gui_dma_fillrect_simple(gui_dma_pack_fillrect_simple *pack);
extern INT GDI_DrawFillRectangleSimple(const GDI_DRAW_BUFFER *buffer, INT x, INT y, INT width, INT height, UW forecolor, UW *request);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
