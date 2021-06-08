#include "mdmac.h"
#include "gui_dma_command.h"
#include "Mml.h"	/* for MML_LogicalMemAddr() */

#define	GUI_DMA_TRANS_END	0x00000001

extern UW gdi_fill_color;


extern GDI_DRAW_BUFFER *gdi_pixmap_draw_buffer_pointer;
extern GDI_DRAW_BUFFER	gdi_pixmap_draw_buffer;

GDI_DRAW_BUFFER	*gdi_pixmap_draw_buffer_pointer = NULL;
GDI_DRAW_BUFFER	 gdi_pixmap_draw_buffer;
static UW m_hDmac = 0;

/* 転送データ長決定 */
void gui_dma_GetTransferLength( UW srcadr, UW dstadr, UW size, UW *ptw, UW *ptu )
{
	UW tmptu, tmptw;

	if(ptw == NULL) return;
	if(ptu == NULL) return;

	/* 転送サイズから転送データ長を決定 */
	if (size % 64 == 0) {
		tmptu = MDMAC_TU_64B;		// 6
	} else if (size % 32 == 0) {
		tmptu = MDMAC_TU_32B;		// 5
	} else if (size % 16 == 0) {
		tmptu = MDMAC_TU_16B;		// 4
	} else if (size % 8 == 0) {
		tmptu = MDMAC_TU_8B;		// 3
	} else if (size % 4 == 0) {
		tmptu = MDMAC_TU_4B;		// 2
	} else if (size % 2 == 0) {
		tmptu = MDMAC_TU_2B;		// 1
	} else {
		tmptu = MDMAC_TU_1B;		// 0
	}

	/* 転送元、転送先アドレスから転送単位を決定 */
	if ((srcadr % 4 == 0) && (dstadr % 4 == 0)) {
		tmptw = MDMAC_TW_4B;		// 2
	} else if ((srcadr % 2 == 0) && (dstadr % 2 == 0)) {
		tmptw = MDMAC_TW_2B;		// 1
	} else {
		tmptw = MDMAC_TW_1B;		// 0
	}
	
	/* 転送単位が転送データ長より大きい場合は転送単位を転送データ長に合わせる */	
	if (tmptw > tmptu) {
		tmptw = tmptu;
	}

	// V9 PF依存仕様
	if( (tmptu == MDMAC_TU_64B) && (tmptw < MDMAC_TW_4B) ){
		tmptu = MDMAC_TU_32B;		// 5
	}
	if( (tmptu == MDMAC_TU_32B) && (tmptw < MDMAC_TW_2B) ){
		tmptu = MDMAC_TU_16B;		// 4
	}
	
	*ptu = tmptu;
	*ptw = tmptw;
}


static void endCallBackFunc(UW h_mdmac)
{
	if (h_mdmac == m_hDmac) {
		iset_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
	}
}

static void endErrCallBackFunc(UW h_mdmac)
{
	if (h_mdmac == m_hDmac) {
		iset_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
	}
}


//MDMAC転送単位補正処理
//パラメータ補正 転送サイズが転送単位で割り切れなければ、転送単位を補正する
static UW gd_mdmac_adj_tw(UW tw, UW rect_dst_data_size)
{
	UW ret_tw = tw;

	if( (MDMAC_TW_8B == ret_tw) && (rect_dst_data_size % 8) ){
		ret_tw = MDMAC_TW_4B;
	}
	if( (MDMAC_TW_4B == ret_tw) && (rect_dst_data_size % 4) ){
		ret_tw = MDMAC_TW_2B;
	}
	if( (MDMAC_TW_2B == ret_tw) && (rect_dst_data_size % 2) ){
		ret_tw = MDMAC_TW_1B;
	}

	return ret_tw;
}

// -------------------------------------------------------------------

//#define DBG_MDMAC_TIME_MEASURE
//MDMAC FILL転送実行処理
// 引数 プロパティ設定
//　戻り値：Ret 転送成否　（1=成功, 0=失敗）
int gui_dma_fillrect_exec(mdmac_prop *p_prop, mdmac_prop3 *p_prop3)
{
	W 	MdmacErr,MdmacErr1,MdmacErr2;
	int Ret = 0;

	if(p_prop == NULL) return 0;
	if(p_prop3 == NULL) return 0;

	//DMACの使用権を取得
	if((MdmacErr = MDMAC_Open(MDMAC_CH_5, &m_hDmac)) == MDMAC_OK){
		MdmacErr1 = MDMAC_SetCB(m_hDmac, endCallBackFunc);		//DMAC転送完了通知コールバック関数を設定
		MdmacErr2 = MDMAC_SetECB(m_hDmac, endErrCallBackFunc);	//DMAC転送エラー通知コールバック関数を設定
		if( (MdmacErr1 == MDMAC_OK)&&(MdmacErr2 == MDMAC_OK) ){
			//転送単位補正
			p_prop->tw = gd_mdmac_adj_tw(p_prop->tw, p_prop3->rect_dst_data_size);

			/*--- for MDMAC_SetProp3---*/
			if ((MdmacErr = MDMAC_SetProp3(MDMAC_CH_5, p_prop3)) == MDMAC_OK) {
				/*--- for MDMAC_SetProp---*/
	 			if ((MdmacErr = MDMAC_SetProp(m_hDmac, p_prop)) == MDMAC_OK) {
					//MDMAC転送開始
					clr_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
					if((MdmacErr = MDMAC_Start(m_hDmac)) == MDMAC_OK) {
						FLGPTN FlgPtn;
						ER Err = twai_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END, TWF_ORW, &FlgPtn, 500);
						if (Err == E_OK) {
							Ret = 1;
						}
					}
				}
			}
		}
	    //DMACの使用権を開放
		MDMAC_Close(m_hDmac);
	}
	return Ret;	
}

/*
 *	DMA転送（フィル）
 *   (注意事項)2016.8.10
 *   引数のアドレスは「物理アドレス」を指定する事
 *    (param->dst_adr,param->src_adr)
 *   Remap設定による論理アドレスへの変換は、本関数内で実行する
 */
INT gui_dma_fillrect(gui_dma_fillrect_param *param, BOOL lock)
{
	mdmac_prop3 gd_prop3;
	mdmac_prop gd_prop;
	
	if(param == NULL) return 0;

	/*--- for MDMAC_SetProp3---*/
	gd_prop3.key_color_mode		= MDMAC_KC_OFF;	//通常
	gd_prop3.key_color_data		= 0;	//
	gd_prop3.rect_src_data_size	= 0;	//通常
	gd_prop3.rect_src_skip_size	= 0;	//通常
	
	gd_prop3.rect_dst_skip_size = param->skip_size;		//転送先の矩形転送のデータスキップサイズ
	//転送先のスキップサイズが0なら通常転送
	if (gd_prop3.rect_dst_skip_size == 0) { 
		gd_prop3.rect_dst_data_size = 0;				//通常転送
	} else {
		gd_prop3.rect_dst_data_size = param->data_size;	//矩形転送：データサイズ
	}
	/*--- for MDMAC_SetProp---*/
	{
		gdi_fill_color = param->color;			//色データをアンキャッシュ領域にコピー
		
		gd_prop.sam		= MDMAC_AM_FIX;			//FIX
		gd_prop.src_adr	= MML_LogicalMemAddr((UW)&gdi_fill_color);	//転送元はアンキャッシュ領域である事
		gd_prop.dst_adr	= MML_LogicalMemAddr(param->dst_adr);		//転送先

		gd_prop.dam		= MDMAC_AM_INC;			//INC
		gd_prop.size	= param->size;

		gui_dma_GetTransferLength(gd_prop.src_adr, gd_prop.dst_adr, gd_prop3.rect_dst_data_size, &gd_prop.tw, &gd_prop.tu);
		
		/* データ長が2バイトなので最低でも2バイト転送とする */
		if (gd_prop.tw <= MDMAC_TW_1B) {
			gd_prop.tw = MDMAC_TW_2B;
			gd_prop.tu = MDMAC_TU_2B;
		}
		
		gd_prop.tm = MDMAC_TM_BAT;
		gd_prop.start_trg = MDMAC_TRG_SOFT;
	}
	
	//MDMAC転送実行＆完了待ち
	if (gui_dma_fillrect_exec(&gd_prop, &gd_prop3) == 0) {
		return GDI_HW_BUSY_ERROR;
	}
	
	return GDI_NO_ERROR;
}


