#include "gui_dma_command.h"
#include "smDebugSerial.h"


extern INT gui_dma_fillrect(gui_dma_fillrect_param *param, BOOL lock);

void resfree(void *ptr)
{
	rel_mpl(GFX_RESMPL_ID, ptr);
}

void *resmalloc(size_t size)
{
	void *mem;

	if (tget_mpl(GFX_RESMPL_ID, size, &mem,  500) != E_OK) {
		return NULL;
	}
	return mem;
}

void gui_dma_mem_free(void *ptr)
{
	resfree(ptr);
}

void *gui_dma_mem_alloc(int size)
{
	return resmalloc(size);
}

void gui_dma_return(gui_dma_pack *pack, INT result)
{
	if(pack == NULL)	return;

	GDI_DRAW_BUFFER *buffer = &pack->buffer;
	
	if (buffer->callback != NULL) {
		GDI_DRAW_CALLBACK callback = buffer->callback;
		//smDebugPrintf(1, "[%s](%d)callback=0x%x/result=%d\n",__func__,__LINE__,callback,result);
		callback((UW)pack, result);
		gui_dma_mem_free(pack);

	} else {
		pack->result = result;
		set_flg(GUI_DMA_SYNC_FLGID, GUISYNCFLG_DMA_FINISHED);
	}
}

static void gui_dma_fillrect_yuv_simple(gui_dma_pack_fillrect_simple *pack)
{
	if(pack == NULL){
		return;
	}

	GDI_DRAW_BUFFER	*buffer = &pack->buffer;
	GDI_REGION *region = &pack->region;
	gui_dma_fillrect_param param;
	INT result = GDI_NO_ERROR;
	UW colorCb = 0;
	UW colorCr = 0;
	UW colorCbCr = 0;

	INT width = region->x + region->width;
	width = (buffer->width < width) ? buffer->width : width;
	width = width - region->x;
	
	INT height = region->y + region->height;
	height = (buffer->height < height) ? buffer->height : height;
	height = height - region->y;
	
	param.data_size = width;
	param.skip_size = buffer->width - param.data_size;
	param.size = width * height;
	
	//COLORBUFFER 0 転送
	UW offset = buffer->width * region->y + region->x;
	param.dst_adr = (UW)buffer->color_buffer0 + offset;
	
	UB colorY = pack->forecolor >> 16;
	param.color = (colorY << 24) | (colorY << 16) | (colorY << 8) | colorY;
	
	if ((result = gui_dma_fillrect(&param, FALSE)) != GDI_NO_ERROR) {
		goto process_exit;
	}
	
	//COLORBUFFER 1 転送
	if (buffer->format == GDI_COLOR_FORMAT_YUV422SP) {
		param.size = width * height;
		offset = buffer->width * region->y + region->x;
	} else {
		param.size = width * height / 2;
		offset = buffer->width * region->y / 2 + region->x;
	}
	
	param.dst_adr = (UW)buffer->color_buffer1 + offset;
	
	colorCb = ((pack->forecolor >> 8) & 0x000000FF);
	colorCr = (pack->forecolor & 0x000000FF);
	colorCbCr = (colorCr << 8) | colorCb;
	param.color = (colorCbCr << 16) | colorCbCr;
	
	if ((result = gui_dma_fillrect(&param, FALSE)) != GDI_NO_ERROR) {
		goto process_exit;
	}
	
process_exit:
	gui_dma_return((gui_dma_pack *)pack, result);
}

void gui_dma_fillrect_simple(gui_dma_pack_fillrect_simple *pack)
{
	if(pack == NULL)	return;
	GDI_DRAW_BUFFER	*buffer = &pack->buffer;

	if(buffer == NULL)	return;
	if ((buffer->format == GDI_COLOR_FORMAT_YUV422SP) ||
		(buffer->format == GDI_COLOR_FORMAT_YUV420SP)) {
		gui_dma_fillrect_yuv_simple(pack);
	} else {
		gui_dma_return((gui_dma_pack *)pack, GDI_ILLEGAL_ARGUMENT_ERROR);
	}
}


INT gui_dma_checkDrawBuffer(const GDI_DRAW_BUFFER *buffer)
{
	if (buffer == NULL) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	if ((buffer->width % 2 != 0) || (buffer->height % 2 != 0)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	switch (buffer->format) {
	case GDI_COLOR_FORMAT_RGBA8888:
	case GDI_COLOR_FORMAT_INDEX:
	case GDI_COLOR_FORMAT_YUV422SP:
	case GDI_COLOR_FORMAT_YUV420SP:
		break;
	default:
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	if (buffer->color_buffer0 == NULL) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	if ((buffer->format == GDI_COLOR_FORMAT_YUV422SP) || (buffer->format == GDI_COLOR_FORMAT_YUV420SP)) {
		if (buffer->color_buffer1 == NULL) {
			return GDI_ILLEGAL_ARGUMENT_ERROR;
		}
	}
	
	return GDI_NO_ERROR;
}

/*
 *	概要：指定した矩形範囲を、指定した色で塗り潰す
 *   (注意事項)2016.8.10
 *   引数のアドレスは「物理アドレス」を指定する事
 *   Remap設定による論理アドレスへの変換は、gdi内部関数で実行する
 */
INT GDI_DrawFillRectangleSimple(const GDI_DRAW_BUFFER *buffer, INT x, INT y, INT width, INT height, UW forecolor, UW *request)
{
	ER err;
	FLGPTN FlgPtn;
	GUI_DMA_CMD_DATA_MSG *pMsg;
	gui_dma_pack_fillrect_simple *pack;
	INT result = GDI_NO_ERROR;

#ifdef FILL_TIME
	UW time1;
	GET_TIM(time1);
#endif
	if ((result = gui_dma_checkDrawBuffer(buffer)) != GDI_NO_ERROR) {
		return result;
	}
	
	if (buffer->callback != NULL && request == NULL) {	/* pgr0541 bufferのNULLチェックはgui_dma_checkDrawBuffer()でチェック済 */
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	if ((pack = (gui_dma_pack_fillrect_simple *)gui_dma_mem_alloc(sizeof(*pack))) == NULL) {
		return GDI_OUT_OF_MEMORY_ERROR;
	}
	
	memcpy(&pack->buffer, buffer, sizeof(*buffer));
	pack->forecolor = forecolor;
	
	GDI_REGION *region = &pack->region;
	region->x = x;
	region->y = y;
	region->width = width;
	region->height = height;

	if (get_mpf(GUI_DMA_MPFID_CMD, (VP)&pMsg) != E_OK) {
		gui_dma_mem_free(pack);
		return GDI_OUT_OF_MEMORY_ERROR;
	}
	
	pMsg->CmdData.ComType	= GUI_DMA_COM_EXTREQ;
	pMsg->CmdData.Param1	= GUI_DMA_COM_EXT_DRAW_FILLRECT_SIMPLE;
	pMsg->CmdData.pParam	= pack;
	
	clr_flg(GUI_DMA_SYNC_FLGID, GUISYNCFLG_DMA_FINISHED);
	
	/* メッセージ送信 */
	if (snd_mbx(GUI_DMA_MBXID_CMD, (T_MSG *)pMsg) != E_OK) {
		/* メモリ開放 */
		rel_mpf(GUI_DMA_MPFID_CMD, pMsg);
		gui_dma_mem_free(pack);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

	if (buffer->callback == NULL) {	// callback指定ではないので、DMA転送完了するまでベタ待ち
		err = twai_flg(GUI_DMA_SYNC_FLGID, GUISYNCFLG_DMA_FINISHED, TWF_ORW, &FlgPtn, 1000);
		result = pack->result;
		gui_dma_mem_free(pack);
		if (err != E_OK) {
			result = GDI_CONTEXT_ERROR;
		}
		
	} else {
		*request = (UW)pack;	/* pgr0541 条件判定済の為、ここに来るケースでrequestはNULLではない */
	}
	
#ifdef FILL_TIME
	UW time2;
	GET_TIM(time2);
	smDebugPrintf(1 , "  GDI_DrawFillRectangleSimple [%dms]  ***[%dms]\n", time2, time2 - time2 );
#endif
	
	return result;
}
