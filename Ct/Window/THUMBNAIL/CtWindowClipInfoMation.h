/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowClipInfoMation
 */


#ifndef __CtWindowClipInfoMation_H__
#define __CtWindowClipInfoMation_H__

#include "CtWindowCommon.h"
#include "AplParamService.h"

#include "CtWindowContentsDrawThumb.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"

#include "CtContainerWifi.h"
#include "CtContainerBattery.h"
#include "CtContainerThumbnailTitleBar.h"

#include "CtThumbDesign.h"
#include "CtStackLabel.h"

#include "gdi.h"
#include "gdi_local.h"

class CtWindowClipInfoMation : public CtWindowMain
{
#define LeftFont  CtFontSet(FontTypeNormal, CtColor::White)
#define CenterFont  CtFontSet(FontTypeNormal_alignCenter, CtColor::White)
typedef enum WindowContentType {
	WC_DRAW_THUMNAIL,
	WC_DRAW_INIT,
	WC_SELECT_CLIPINFO,
	WC_NONE,
}WindowContentType;

typedef enum {
	S_READ_CLIP_IDLE = 0,
	S_READ_CLIP_WAIT,
	S_READ_THUM_IDLE,
	S_READ_THUM_WAIT,
	S_READ_CLIP_MAX,
} READ_CLIP_STATE;


typedef enum {
	E_READ_THUM_INIT,
	E_READ_THUM_REQ,
	E_READ_THUM_FINISH,
	E_READ_CLIP_REQ,
	E_READ_CLIP_FINISH,
	E_READ_CLIP_END,
} READ_CLIP_EVENT;

typedef enum {
	READ_THUM_NOT_SATRTED_YET,
	READ_THUM_SET_FINISH,
	READ_THUM_REROAD,
	READ_THUM_END,
} READ_THUM_YUV;

public:
	CtWindowClipInfoMation();
	virtual ~CtWindowClipInfoMation() {}

	void callback_setCurrentIndex(int index);

	virtual bool handleParamEvent(const CtEventParam& Param);
    virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);


	void initThumbnail();
	bool setContents(const CtWindowContents* pContents);
    void setClipCnt(unsigned long cnt);
    unsigned long getClipCnt(void);
	virtual bool updateContents();
	void updateThumbnailImage();
	void DeleteThumbnailDrawable(int index);
	unsigned long GetThumbNailDrawableID(int index);
	GDI_HANDLER GetImageDrawableHandle(int index);
	READ_THUM_YUV IsAlreadyReadYuv(int index);
	bool DrawRequestYuv(int clipNo);
	void setThumbNailImage(unsigned long ClipNo);
	void setDrawableYUV(int index);
	// コンテンツ更新通知
	void updatePicture();										// 画像情報を更新する

	void UpdateClipInfo();

private:
	// レイアウト生成
	virtual CtWindow* createWindow();
	CtLayout* createLayoutLeftButton();
	CtLayout* createLayoutOneItemIcon();
	CtLayout* createLayoutRightText();

	bool destroyWindow();                                      // ウィンドを消去する
	void setCurrentClipNo(unsigned long clipNo);
	unsigned long getCurrentNo();
	int getDetailPixelType(int nPixelTypeIndex, int nFrequencyIndex);

	// 表示更新
    void updateThumbnail(unsigned long index);
	void BlankClipInfomation(unsigned long index);
	bool updateClipNo(unsigned long index);							// クリップ番号
	bool updateNotPlayIcon(bool bVisible);							// 再生不可クリップ
	bool updateProtectIcon(bool bVisible);							// クリッププロテクト
	bool updateClipName(const char* name);							// クリップ名
	bool updateP2StartIcon(CtClipInfo::ClipInfoP2StartType Type);	// P2不良/不明クリップ
	bool updateReConnectIcon(bool bVisible);						// 不完全クリップ

	bool updateSd();												// SD

private:
	/* WindowContent受信状態 */
	WindowContentType	m_wcEvent;
	
	CtWindowContentsThumbInit*			m_pInitInfo;
	CtWindowContentsSelectClipInfo*		m_pSelectClipInfo;
	CtWindowContentsDrawThumb*			m_pDrawInfo;

	CtButton* m_pBtnUp;         // (ボタン)前ページ
    CtButton* m_pBtnDown;       // (ボタン)次ページ
	CtButton* m_pBtnReturn;		// 戻るボタン

	CtContainerThumbnailTitleBar* m_pTitleBar;	// タイトル

    CtLabel*   m_pLabeIcon[14];	//0:クリップ番号
								//1:再生不可クリップアイコン
								//2:クリッププロテクトアイコン
								//3:サムネイル画像
								//4:クリップ名
								//5:スタートTC
								//6:スタートUB
								//7:撮影日
								//8:撮影時刻
								//9:記録時間
								//10:記録解像度/&周波数
								//11:記録コーデック
								//12:記録フレームレート
								//13:Gamma
	CtLabel* m_pReConnect;
	CtStackLabel* m_pP2Start;

	CtLabel*   m_pPixel;
	CtLabel*   m_pSeparate;
	CtLabel*   m_pFreq;
	
	unsigned long m_Clipcnt;		// クリップ数
	unsigned long m_CurrentClipNo;	// クリップ番号
	unsigned long m_ReadClipNo;		// 情報読み込み中のクリップ番号


	typedef CtVector::Vector<CtClipInfo*> ClipInfoItemList;
	ClipInfoItemList m_list;

private:
	void SetReadClipInfoEvent(READ_CLIP_EVENT _event);
	READ_CLIP_EVENT State_ReadClipIdle(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadClipWait(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadThumIdle(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadThumWait(READ_CLIP_EVENT event);
	READ_CLIP_STATE m_read_clip_state;
};

#endif
