/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbButton
*/


#ifndef __CtThumbButton_H__
#define __CtThumbButton_H__

#include "gdi.h"
#include "CtWindowCommon.h"
#include "CtThumbInfo.h"
#include "CtThumbGridView.h"

#include "CtWindowContentsClipInfo.h"

class CtThumblGridView;

class CtThumbButton : public CtButton {
public:
	enum IconType {
		IconType_Resume,
		IconType_Delete,
		IconType_Copy,
		IconType_Protect
	};
	
	CtThumbButton();
	virtual ~CtThumbButton();

	bool setThumbInfo(CtThumbInfo* pInfo);
	bool setFunction(ContentsThumbSyncSelectCallback m_SelectClip);
	bool setIconType(CtThumbButton::IconType _Type);
	void readyGo(int clipNo);
	unsigned long getClipNo() { return m_ClipNo; }
	CtSize getPictureSize() { return m_pPicture->getSize(); }

	bool styleNormal();
	bool styleFocused();
	bool stylePressed();
	bool styleInvalid();

private:
	void initLayout();

	void setClipNo(int ClipNo);
	void setTitle(const char * str);
	void setImpossiblePlayIcon(bool bVisible);
	void setProtectIcon(bool bVisible);
	void setReConnectIcon(bool bVisible);
	void setP2StartIcon(GDI_IMAGE_ID imageID);
	void setCodecIcon(GDI_IMAGE_ID imageID);
	void setInfoIcon(CtThumbButton::IconType type, bool bVisible);
	void setFormatIcon(GDI_IMAGE_ID imageID);
	void setPicture(GDI_HANDLER hPicture);

	bool handleParamEvent(const CtEventParam & Param);
	bool onRelease();

private:
	IconType	m_IconType;
	unsigned long  		m_ClipNo;
	CtThumbCache* m_pThumbCache;
	ContentsThumbSyncSelectCallback m_SelectClip;
	bool		m_bFunc;
	//上段部分
	CtLabel* m_pClipNumber;				//クリップNo.
	CtLabel* m_pMultiIcon;				//ResumePlay or Copy or Delete
	CtLabel* m_pFormatIcon;				//RecFormat

	//中段部分①
	CtLabel* m_pImpossiblePlayIcon;		//再生不可Clip
	CtLabel* m_pCodecIcon;				//RecCodec
	
	//中段部分②
	CtLabel* m_pProtectIcon;			//プロテクト
	CtLabel* m_pP2StartIcon;			//P2不良/不明クリップ
	CtLabel* m_pReConnectIcon;			//P2不完全クリップ

	//下段部分
	CtLabel* m_pTitle;					//クリップ

	//背面
	CtLabel* m_pPicture;				//サムネイル画像

public:
	void setThumbCache(CtThumbCache* pThumbCache) {m_pThumbCache = pThumbCache;}
	
};
#endif
