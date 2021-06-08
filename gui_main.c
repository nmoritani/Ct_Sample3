# include "kernel.h"
# include "kernel_id.h"
#include "guiif_avc.h"
#include "gui_main.h"
#include <math.h>

unsigned long normal_lut_yuv[256];

unsigned long normal_lut[] = 
{
  0x00000000,    /* 0 使ってはダメ！ */
  0x000000FF,    /* 1 黒色 */
  0xB3B3B3FF,    /* 2 灰色 */
  0xFFFFFFFF,    /* 3 白色 */
  0xFF0000FF,    /* 4 */
  0xFFFF00FF,    /* 5 */
  0xD9D9D9D8,    /* 6 */
  0x64646480,    /* 7 */
  0xFBC734CC,    /* 8 */
  0xFFFFFFB4,    /* 9 */
  0xB9C4D4FF,    /* 10 */
  0xFFFFFF66,    /* 11 */
  0x000000DC,    /* 12 */
  0x0F1F2FFF,    /* 13 */ // 2016/03/07 T.Arakawa Spec Chenge
  0x00000090,    /* 14 */
  0x00FF00FF,    /* 15 */
  0x77B0CBFC,    /* 16 */
  0xCBCBCB59,    /* 17 */
  0x162835FF,    /* 18 */
  0x28DE64FF,    /* 19 */
  0xFE2362FF,    /* 20 */
  0xFE2362A0,    /* 21 */
  0x02095380,    /* 22 */
  0x195F55FF,    /* 23 */
  0xFBC734CC,    /* 24 */
  0x6D6D6D80,    /* 25 */
  0xFFFFFFD9,    /* 26 */
  0x3D5262FF,    /* 27 */
  0xEFCC32FF,    /* 28 */
  0x00052EFF,    /* 29 */
  0x5D5D5DFF,    /* 30 */
  0xD6D5D8FF,    /* 31 */
  0x00FF00FF,    /* 32 *//*緑色に変更*/
  0xFFB306FF,    /* 33 */
  0x5D5D5DFF,    /* 34 */
  0x000727CC,    /* 35 */
  0x007DFFFF,    /* 36 *//*青色に変更*/
  0x9D9D9DFF,    /* 37 */
  0x646464FF,    /* 38 */
  0xA6A3A1FF,    /* 39 */
  0x545252FF,    /* 40 */
  0x7B88BDFF,    /* 41 */
  0xFCC735FF,    /* 42 */
  0xADADADFF,    /* 43 */
  0x5F5F5FFF,    /* 44 *//*for黒モデル*/  // 2016/03/07 T.Arakawa Spec Chenge
  0x3E3E3DFF,    /* 45 */
  0x282828FF,    /* 46 */
  0x020526FF,    /* 47 */
  0xF5F5F5FF,    /* 48 */
  0xF0F0F0FF,    /* 49 */
  0xE7E5E5FF,    /* 50 */
  0xDCDCDCFF,    /* 51 */
  0xC23A91FF,    /* 52 */
  0xD1639BFF,    /* 53 */
  0xD286B2FF,    /* 54 */
  0xFABA3EFF,    /* 55 */
  0xF8C03FFF,    /* 56 */
  0xF6C745FF,    /* 57 */
  0xF1D24DFF,    /* 58 */
  0x111E29FF,    /* 59 */
  0x172B3AFF,    /* 60 */
  0x24274AFF,    /* 61 */
  0x132531FF,    /* 62 */
  0x00000000,    /* 63 透明色 */
  0x00000048,    /* 64 ここから空き */
  0x000000C8,    /* 65 */
  0x00000028,    /* 66 */
  0x00000088,    /* 67 */
  0x484848F8,    /* 68 */
  0x181818F8,    /* 69 */
  0x00000078,    /* 70 */
  0x00000058,    /* 71 */
  0x000000E8,    /* 72 */
  0xC8C8C8F8,    /* 73 */
  0x000000B8,    /* 74 */
  0x787878F8,    /* 75 */
  0x00000068,    /* 76 */
  0x000000A8,    /* 77 */
  0x00000038,    /* 78 */
  0x00000018,    /* 79 */
  0x888888F8,    /* 80 */
  0x00000000,    /* 81 */
  0x00000000,    /* 82 */
  0x00000000,    /* 83 */
  0x00000000,    /* 84 */
  0x00000000,    /* 85 */
  0x00000000,    /* 86 */
  0x00000000,    /* 87 */
  0x00000000,    /* 88 */
  0x00000000,    /* 89 */
  0x00000000,    /* 90 */
  0x00000000,    /* 91 */
  0x00000000,    /* 92 */
  0x00000000,    /* 93 */
  0x00000000,    /* 94 */
  0x00000000,    /* 95 */
  0x00000000,    /* 96 */
  0x00000000,    /* 97 */
  0x00000000,    /* 98 */
  0x00000000,    /* 99 */
  0x00000000,    /* 100 */
  0x00000000,    /* 101 */
  0x00000000,    /* 102 */
  0x00000000,    /* 103 */
  0x00000000,    /* 104 */
  0x00000000,    /* 105 */
  0x00000000,    /* 106 */
  0x00000000,    /* 107 */
  0x00000000,    /* 108 */
  0x00000000,    /* 109 */
  0x00000000,    /* 110 */
  0x00000000,    /* 111 */
  0x00000000,    /* 112 */
  0x00000000,    /* 113 */
  0x00000000,    /* 114 */
  0x00000000,    /* 115 */
  0x00000000,    /* 116 */
  0x00000000,    /* 117 */
  0x00000000,    /* 118 */
  0x00000000,    /* 119 */
  0x00000000,    /* 120 */
  0x00000000,    /* 121 */
  0x00000000,    /* 122 */
  0x00000000,    /* 123 */
  0x00000000,    /* 124 */
  0x00000000,    /* 125 */
  0x00000000,    /* 126 */
  0x00000000,    /* 127 */
  0x00000000,    /* 128 */
  0x00000000,    /* 129 */
  0x00000000,    /* 130 */
  0x00000000,    /* 131 */
  0x00000000,    /* 132 */
  0x00000000,    /* 133 */
  0x00000000,    /* 134 */
  0x00000000,    /* 135 */
  0x00000000,    /* 136 */
  0x00000000,    /* 137 */
  0x00000000,    /* 138 */
  0x00000000,    /* 139 */
  0x00000000,    /* 140 */
  0x00000000,    /* 141 */
  0x00000000,    /* 142 */
  0x00000000,    /* 143 */
  0x00000000,    /* 144 */
  0x00000000,    /* 145 */
  0x00000000,    /* 146 */
  0x00000000,    /* 147 */
  0x00000000,    /* 148 */
  0x00000000,    /* 149 */
  0x00000000,    /* 150 */
  0x00000000,    /* 151 */
  0x00000000,    /* 152 */
  0x00000000,    /* 153 */
  0x00000000,    /* 154 */
  0x00000000,    /* 155 */
  0x00000000,    /* 156 */
  0x00000000,    /* 157 */
  0x00000000,    /* 158 */
  0x00000000,    /* 159 */
  0x00000000,    /* 160 */
  0x00000000,    /* 161 */
  0x00000000,    /* 162 */
  0x00000000,    /* 163 */
  0x00000000,    /* 164 */
  0x00000000,    /* 165 */
  0x00000000,    /* 166 */
  0x00000000,    /* 167 */
  0x00000000,    /* 168 */
  0x00000000,    /* 169 */
  0x00000000,    /* 170 */
  0x00000000,    /* 171 */
  0x00000000,    /* 172 */
  0x00000000,    /* 173 */
  0x00000000,    /* 174 */
  0x00000000,    /* 175 */
  0x00000000,    /* 176 */
  0x00000000,    /* 177 */
  0x00000000,    /* 178 */
  0x00000000,    /* 179 */
  0x00000000,    /* 180 */
  0x00000000,    /* 181 */
  0x00000000,    /* 182 */
  0x00000000,    /* 183 */
  0x00000000,    /* 184 */
  0x00000000,    /* 185 */
  0x00000000,    /* 186 */
  0x00000000,    /* 187 */
  0x00000000,    /* 188 */
  0x00000000,    /* 189 */
  0x00000000,    /* 190 */
  0x00000000,    /* 191 */
  0x00000000,    /* 192 */
  0x00000000,    /* 193 */
  0x00000000,    /* 194 */
  0x00000000,    /* 195 */
  0x00000000,    /* 196 */
  0x00000000,    /* 197 */
  0x00000000,    /* 198 */
  0x00000000,    /* 199 */
  0x00000000,    /* 200 */
  0x00000000,    /* 201 */
  0x00000000,    /* 202 */
  0x00000000,    /* 203 */
  0x00000000,    /* 204 */
  0x00000000,    /* 205 */
  0x00000000,    /* 206 */
  0x00000000,    /* 207 */
  0x00000000,    /* 208 */
  0x00000000,    /* 209 */
  0x00000000,    /* 210 */
  0x00000000,    /* 211 */
  0x00000000,    /* 212 */
  0x00000000,    /* 213 */
  0x00000000,    /* 214 */
  0x00000000,    /* 215 */
  0x00000000,    /* 216 */
  0x00000000,    /* 217 */
  0x00000000,    /* 218 */
  0x00000000,    /* 219 */
  0x00000000,    /* 220 */
  0x00000000,    /* 221 */
  0x00000000,    /* 222 */
  0x00000000,    /* 223 */
  0x00000000,    /* 224 */
  0x00000000,    /* 225 */
  0x00000000,    /* 226 */
  0x00000000,    /* 227 */
  0x00000000,    /* 228 */
  0x00000000,    /* 229 */
  0x00000000,    /* 230 */
  0x00000000,    /* 231 */
  0x00000000,    /* 232 */
  0x00000000,    /* 233 */
  0x00000000,    /* 234 */
  0x00000000,    /* 235 */
  0x00000000,    /* 236 */
  0x00000000,    /* 237 */
  0x00000000,    /* 238 */
  0x00000000,    /* 239 */
  0x00000000,    /* 240 */
  0x00000000,    /* 241 */
  0x00000000,    /* 242 */
  0x00000000,    /* 243 */
  0x00000000,    /* 244 */
  0x00000000,    /* 245 */
  0x00000000,    /* 246 */
  0x00000000,    /* 247 */
  0x00000000,    /* 248 */
  0x00000000,    /* 249 */
  0x00000000,    /* 250 */
  0x00000000,    /* 251 */
  0x00000000,    /* 252 */
  0xFFAD33FF,    /* 253 */
  0x000000FF,    /* 254 */
  0xFFFFFF00    /* 255 */
};

typedef struct _GDI_PALETTE {
	BOOL free;
	BOOL update;
	unsigned short color;
} GDI_PALETTE;

static GDI_PALETTE gdi_palette[256];
#define GDI_PALETTE_SIZE	(sizeof(gdi_palette)/sizeof(GDI_PALETTE))

void gdi_palette_set_freeid(unsigned int i)
{
	gdi_palette[i].free = TRUE;
	gdi_palette[i].update = FALSE;
	gdi_palette[i].color = 0;
}

void gdi_palette_initial(unsigned long *lut)
{
	unsigned int i;
	unsigned long color;
	
	if(lut == NULL)	return;

	for (i=0; i<GDI_PALETTE_SIZE; i++) {
		color = lut[i];
		gdi_palette[i].free = FALSE;
		gdi_palette[i].update = FALSE;
		gdi_palette[i].color = (unsigned short)(((color & 0xF0000000) >> 16)	+ ((color & 0x00F00000) >> 12)	+ ((color & 0x0000F000) >>  8)	+ ((color & 0x000000F0) >>  4) );		/* pgr0247 意図通りのキャスト */
	}
}

/* 例外値が出たときの丸め処理 */
static int check_over(int data)
{
    if (0 >= data) {
        return 1;
    } else if (255 <= data) {
        return 254;
    } else {
        return data;
    }
}

/* RGB→Y 変換 */
unsigned char rgb2Y (unsigned char r, unsigned char g, unsigned char b)
{
  double Ey;
  int    Y;

  Ey = 0.2125 * r/(double)255 + 0.7154 * g/(double)255 + 0.0721 * b/(double)255;
  Y = check_over((int)floor( 219 * Ey + 16 + 0.5 ));	/* pgr0247 意図通りの丸め込み */

  return (unsigned char)Y;	/* pgr0247 意図通りの丸め込み */
}

/* RGB→Cb 変換 */
unsigned char rgb2Cb (unsigned char r, unsigned char g, unsigned char b)
{
  double Epb;
  int    Cb;
  Epb = -0.115 * r/(double)255 - 0.386 * g/(double)255 + 0.5000 * b/(double)255;
  Cb = check_over((int)floor( 224 * Epb + 128 + 0.5 ));	/* pgr0247 意図通りの丸め込み */

  return (unsigned char)Cb;	/* pgr0247 意図通りの丸め込み */
}

/* RGB→Cr 変換 */
unsigned char rgb2Cr (unsigned char r, unsigned char g, unsigned char b)
{
  double Epr;
  int    Cr;
  Epr = 0.5000 * r/(double)255 - 0.454 * g/(double)255 - 0.046 * b/(double)255;
  Cr = check_over((int)floor( 224 * Epr + 128 + 0.5 ));	/* pgr0247 意図通りの丸め込み */

  return (unsigned char)Cr;	/* pgr0247 意図通りの丸め込み */
}

void convert_palette_rgba2yuv(unsigned long *yuv, unsigned long *rgba, int cnv_num)
{
	int i;
	unsigned char r, g, b, a;
	unsigned char y, cb, cr;

	if(rgba == NULL)	return;
	if((cnv_num < 1) || (256 < cnv_num) ) return;

	for (i=0; i<cnv_num; i++) {
		// b31:blink=0／ VENUSの透過率は0x00-0x40で表現
		a =	(unsigned char)((((rgba[i] >>  0) & 0xff) * 64/255) & 0x7F);	/* pgr0247 意図通りのキャスト */
		r =	(unsigned char)((rgba[i] >>  8) & 0xff);	/* pgr0247 意図通りのキャスト */
		g =	(unsigned char)((rgba[i] >> 16) & 0xff);	/* pgr0247 意図通りのキャスト */
		b =	(unsigned char)((rgba[i] >> 24) & 0xff);	/* pgr0247 意図通りのキャスト */

		y  = rgb2Y(r,g,b);
		cb = (unsigned char)(rgb2Cr(r,g,b) +0x80);	/* pgr0247 意図通りのキャスト */
		cr = (unsigned char)(rgb2Cb(r,g,b) +0x80);	/* pgr0247 意図通りのキャスト */
		
		if(yuv == NULL)	return;
		yuv[i] =
			(((unsigned long)a  << 24) & 0xff000000) |
			(((unsigned long)y  << 16) & 0x00ff0000) |
			(((unsigned long)cb <<  8) & 0x0000ff00) |
			(((unsigned long)cr      ) & 0x000000ff);
	}
}

void gui_display_init(void)
{
#if 1	/* カラーパレット未対応 */
	/* LUT書き換え(起動時はLOUT側の書き込みは行わない) */
	convert_palette_rgba2yuv(normal_lut_yuv, normal_lut, 256);
	gdi_palette_initial(normal_lut);
	int i;
	for (i=64; i<256; i++) {	// パレットの64から252までは空き
		gdi_palette_set_freeid(i);
	}

	AVC_ST_LUT_LCD	Lut;
	Lut.mIndex = 0;       						// 開始Index番号(0-255)
	Lut.mNum = 256;        						// 更新カラーパレット数(1-256)
	Lut.mpLut = (UW*)normal_lut_yuv;        	// 更新カラーパレットへのポインタ
	Lut.mOsd.mLcdEvf = (AVC_OUTPUT_LCDEVF)(AVC_OUTPUT_LCDEVF_LCD | AVC_OUTPUT_LCDEVF_EVF);         // LCD/EVF出力種別
	Lut.mOsd.mLayer = AVC_OSD_LAYER_1;     		// OSDレイヤー
	AVD_setLutLcd( &Lut );

	//LOUT対応
	AVC_ST_LUT_LOUT	LutLout;
	LutLout.mIndex = 0;       						// 開始Index番号(0-255)
	LutLout.mNum = 256;        						// 更新カラーパレット数(1-256)
	LutLout.mpLut = (UW*)normal_lut_yuv;        	// 更新カラーパレットへのポインタ
	LutLout.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)(AVC_OUTPUT_TERMINAL_HDMI | AVC_OUTPUT_TERMINAL_D | AVC_OUTPUT_TERMINAL_RCA | AVC_OUTPUT_TERMINAL_SDI);         // LCD/EVF用OSD情報
	LutLout.mOsd.mLayer = AVC_OSD_LAYER_1;     		// OSDレイヤー
	AVD_setLutLout( &LutLout );
	//LOUT対応
#endif

	/* 入力プレーンサイズの通知 */
	/*--------------------------------------------------------------
		LCD :ZOM1(OSD1)/ZOM2(GFX) いずれも960*540
		LOUT:ZOM1(OSD1)/ZOM2(GFX) いずれも960*540
	---------------------------------------------------------------*/
	// LCD --------------------------
	GUIAVC_setOsdPlaneSizeLcd();
	
	// AVIOへ表示更新要求
	//smDebugPrintf(1, "#%d[%s]\n",Ascii_get_time(),__func__);
	GUIAVC_updateOsd(GUIAVC_DISP_LCD, GUIAVC_UPDATE_NORMAL);

	// LOUT --------------------------
	GUIAVC_setOsdPlaneSizeLout();
}

/*
 まずは空関数
*/

void
Gui_Main (void)
{
	ER err;
	T_MSG *pTMsg = NULL;
	GUI_CMD_DATA_MSG	*pCmdMsg;		/* 送受信メッセージ */
	GUI_CMD_DATA		*pCmdData;

	gui_display_init();

//	gui_draw_lock();
	
	/* メインループ */
	while (1) {
//		gui_draw_unlock();
		/* メッセージ受信 */
		err = rcv_mbx(GUI_MBXID_CMD, &pTMsg);
		if (err != E_OK) {
			break;
		}
		
//		gui_draw_lock();
		
		pCmdMsg	= (GUI_CMD_DATA_MSG *)pTMsg;
		pCmdData = (GUI_CMD_DATA *)&pCmdMsg->CmdData;
		
		switch (pCmdData->ComType){
		case COM_TYPE_GUI:
			switch (pCmdData->Param1) {
			case GUI_COM_DISPREQ2AVC:
				//smDebugPrintf(1, "#%d[%s]GUI_COM_DISPREQ2AVC\n",Ascii_get_time(),__func__);
				GUIAVC_updateOsd((GUIAVC_DISP_ID)pCmdData->Param2, GUIAVC_UPDATE_RETRY);
				break;
			default:
				break;
			}
			gfx_free_mpf(pCmdMsg);
			break;
		default:
			break;
		}	
	}


}

#ifdef	OLD_VOUIF		/* 旧VOU-IF */
#else


void GUI_DipsReq2Avc(GUIAVC_DISP_ID id)
{
#if 1	/* 暫定：旧GFXタスク相当をを用意しないと実現できないので、あとまわし*/
	ER err;
	GUI_CMD_DATA_MSG *pMsg;
	
	if ((err = get_mpf(GUI_MPFID_CMD, (VP)&pMsg)) != E_OK) {
		return;
	}
	
	/* メッセージパラメータ設定 */
	pMsg->CmdData.ComType	= COM_TYPE_GUI;
	pMsg->CmdData.Param1	= GUI_COM_DISPREQ2AVC;
	pMsg->CmdData.Param2	= (UW)id;
	
	/* メッセージ送信 */
	err = snd_mbx(GUI_MBXID_CMD, (T_MSG *)pMsg);
	if( err != E_OK ){
		/* メモリ開放 */
		rel_mpf(GUI_MPFID_CMD, pMsg);
	}
#endif
}
#endif

#if 0 //#ifdef ALLOPT_SEMIPRO
static BOOL loutScale90percent = TRUE;
#else // K460
static BOOL loutScale90percent = FALSE;
#endif // ALLOPT_SEMIPRO
// 外部出力を90％表示するか
// 戻り値: loutScale90percent  TRUE:する＝90％ /FALSE:しない＝100%
BOOL GD_isLoutScale90Percent(void)
{
	return loutScale90percent;
}

// 外部出力を90％表示する
// 引数: b_on  TRUE:90％/FALSE:100%
void GD_LoutScale90PercentOn(BOOL b_on)
{
	loutScale90percent = b_on;
}

/*---------------------------------------------
	2017 VOU IF
---------------------------------------------*/
BOOL gui_avc_is_updating[GUIAVC_DISP_MAX] = {FALSE,FALSE,FALSE};		//AVCへのVOU更新要求。TRUE:AVC要求実行～コールバック完了通知、FALSE：それ以外
BOOL gui_avc_reserve_update[GUIAVC_DISP_MAX] = {FALSE,FALSE,FALSE};		//VOU更新中の為、次の更新要求が保留中の状態
BOOL gui_avc_is_retry_requested[GUIAVC_DISP_MAX] = {FALSE,FALSE,FALSE};		//保留した更新要求が再要求中か


void cb_updateOsd(GUIAVC_DISP_ID disp_id)
{
	// AVCへの更新要求が保留になっていた時だけ実行
	if(gui_avc_reserve_update[disp_id]==TRUE){
		// AVC BUSY中に保留した要求が未実行なら、要求は不要（最後の更新を1回実行すれば最終状態になる為。メッセージを積み過ぎるとリソース枯渇する）
		if(gui_avc_is_retry_requested[disp_id] == FALSE){
			GUI_DipsReq2Avc(disp_id);			//GFXコンテキストで実行
			gui_avc_is_retry_requested[disp_id] = TRUE;
		}else{
		}
		gui_avc_reserve_update[disp_id] = FALSE;		//Msgに積んだので、予約なしに設定
	}else{
	}
	gui_avc_is_updating[disp_id] = FALSE;			// 更新要求が完了したのでクリアする	
}
//AVCからのUPDATE完了コールバック
void GUI_CallBack_updateOsdLcd(void)
{
	cb_updateOsd(GUIAVC_DISP_LCD);
}
void GUI_CallBack_updateOsdLout(void)
{
	cb_updateOsd(GUIAVC_DISP_LOUT);
}
void GUI_CallBack_updateOsdRec(void)
{
	cb_updateOsd(GUIAVC_DISP_REC);
}

void GUIAVC_updateOsd(GUIAVC_DISP_ID disp_id, GUIAVC_UPDATE_ID id )
{
	if(disp_id >= GUIAVC_DISP_MAX)	return;


	//AVC BUSY中に保留した要求の再実行が来た事を保持する
	if(GUIAVC_UPDATE_RETRY == id){
		gui_avc_is_retry_requested[disp_id] = FALSE;
	}

	if(gui_avc_is_updating[disp_id]){
		gui_avc_reserve_update[disp_id] = TRUE;				//UPDATE完了コールバックが返ってないので、予約だけして終了。
		return;
	}
	gui_avc_is_updating[disp_id] = TRUE;


	switch(disp_id){
	case GUIAVC_DISP_LCD:
		AVD_updateOsdLcd(id,(AVC_CALLBACK)GUI_CallBack_updateOsdLcd);
		break;
	case GUIAVC_DISP_LOUT:
		AVD_updateOsdLout(id,(AVC_CALLBACK)GUI_CallBack_updateOsdLout);
		break;
	case GUIAVC_DISP_REC:
		AVD_updateOsdRec(id,(AVC_CALLBACK)GUI_CallBack_updateOsdRec);
		break;
	default:
		break;
	}
}

BOOL GUIAVC_isUpdateEnable(GUIAVC_DISP_ID disp_id)
{
	BOOL enable = TRUE;

	if(gui_avc_is_updating[disp_id] == TRUE){
		enable = FALSE;
	}
	if(gui_avc_reserve_update[disp_id] == TRUE){
		enable = FALSE;
	}
	return enable;
}

