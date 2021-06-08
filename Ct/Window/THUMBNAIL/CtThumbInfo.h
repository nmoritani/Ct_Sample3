#pragma once
/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbInfo
*/

#ifndef __CtThumbInfo_H__
#define __CtThumbInfo_H__

#include "Ct.h"
#include "AplParamService.h"
#include "CtWindowContentsClipInfo.h"

#define CLIPINFO_FLGMSK_SETCLIPINFO		(0x0001)
#define CLIPINFO_FLGMSK_DIFFERENTFREQ	(0x0002)
#define CLIPINFO_FLGMSK_PROTECT			(0x0004)
#define CLIPINFO_FLGMSK_YUVIMAGE		(0x0010)
#define CLIPINFO_FLGMSK_DELETE			(0x0020)
#define CLIPINFO_FLGMSK_COPY			(0x0040)
#define CLIPINFO_FLGMSK_RESUME			(0x0080)

struct CtThumbInfo : public CtObject {
private:
	unsigned short					m_ClipNo;		//クリップNo.(初期値：1)
	GDI_IMAGE_ID					m_FormatImageID;//FORMATのアイコン
	GDI_IMAGE_ID					m_CodecImageID;	//CODECのアイコン
	CtClipInfo::ClipInfoMediaType	m_MediaType;	//メディアタイプ(SDカードのスロット)
	unsigned short					m_IconsFlag;		
													//		1bit		IsSetClipInfo;			//クリップ情報セット済みフラグ
													//		2bit		bImpossiblePlayIcon;	//再生不可アイコン
													//		3bit		bProtectIcon;			//プロテクトアイコン
													//		4bit		Reserve;				//
													//		5bit		IsSetYuvImage;			//YUVイメージのセット状態
													//		6bit		DeleteFlag
													//		7bit		CopyFlag
													//		8bit		ResumeFlag
													//		9～16bit	Reserved;
	GDI_IMAGE_ID					m_P2StartImageID;//P2クリップステータスアイコン
	bool							m_bReConnect;	//Reconnectアイコン

	char							m_ClipName[14];	//12byte:クリップ名/StartTC
	char							m_ClipStartTc[14];
	GDI_HANDLER						m_Picture;

public:
	CtThumbInfo(int _clipNo);
	virtual ~CtThumbInfo();

	//bool requestClipInfo(int clipNo);
	void setClipInfo(int clipNo, const CtClipInfo::ClipInfo& ClipInfo);
	
	//クリップ番号取得
	int getClipNo()	{return m_ClipNo;}

	bool isValidPicture() {
		if (m_Picture == GDI_INVALID_ID)
			return false;
		return true;
	}

	bool isValidClipInfo() {
		if (m_MediaType == CtClipInfo::ClipInfoMediaType_None)
			return false;
		return true;
	}
	
	//FORMATのアイコンのImageID取得
	GDI_IMAGE_ID selectFormatImageID(const CtClipInfo::ClipInfo &ClipInfo);
	GDI_IMAGE_ID getFormatImageID()	{return m_FormatImageID;}
	
	//CODECのアイコンのImageID取得
	GDI_IMAGE_ID selectCodecImageID(const CtClipInfo::ClipInfo &ClipInfo);
	GDI_IMAGE_ID getCodecImageID() {return m_CodecImageID;}
	
	//クリップ情報セット状態取得
	bool isSetClipInfo() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_SETCLIPINFO));}

	//再生不可クリップのアイコン表示/非表示
	bool isImpossiblePlay() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_DIFFERENTFREQ));}

	//プロテクトのアイコン表示/非表示
	bool isProtect() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_PROTECT));}

	//ReConnectのアイコン表示/非表示
	bool isReConnect() { return m_bReConnect; }

	//プロテクトのアイコン表示状態反転
	void invertProtectIcon() {m_IconsFlag ^= CLIPINFO_FLGMSK_PROTECT;}

	//RESUME/DELETE/COPY...etc.のアイコン表示/非表示
	bool isFunc(int _Type);

	//RESUME/DELETE/COPY...etc.のアイコン表示状態反転
	void invertFuncIcon();

	//クリップ名取得
	const char* getClipName() {
		if (APL_PARAM_GET_DATA(AplParamDisplayData) == APL_SYS_PARAM_DISPLAY_DATA_START_TC) {
			return m_ClipStartTc;
		}
		else {
			return m_ClipName;
		}
	}

	CtClipInfo::ClipInfoMediaType getMediaType() {return m_MediaType;}

	GDI_IMAGE_ID selectP2StartImageID(const CtClipInfo::ClipInfo &ClipInfo);
	GDI_IMAGE_ID getP2StartImageID() { return m_P2StartImageID; }

	//サムネイル画像セット状態取得
	bool isSetImage() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_YUVIMAGE));}

	void setImageFlag(bool YuvImage) {
		if (YuvImage) {
			m_IconsFlag |= CLIPINFO_FLGMSK_YUVIMAGE;
		} else {
			m_IconsFlag &= ~CLIPINFO_FLGMSK_YUVIMAGE;
		}
	}

	void setPicture(GDI_HANDLER _id) {m_Picture = _id;}
	GDI_HANDLER getPicture() {return m_Picture;}
	
private:
	void setTitle(CtClipInfo::ClipInfo _info);
	
	void setClipNo(int _clipNo) {m_ClipNo = (unsigned short)_clipNo;}

	void setFormatIcon(GDI_IMAGE_ID imageId) {m_FormatImageID = imageId;}
	void setCodecIcon(GDI_IMAGE_ID imageId) {m_CodecImageID = imageId;}
	void setClipInfoFlag(bool ClipInfoFlag) {
		if (ClipInfoFlag) {
			m_IconsFlag |= CLIPINFO_FLGMSK_SETCLIPINFO;
		} else {
			m_IconsFlag &= ~CLIPINFO_FLGMSK_SETCLIPINFO;
		}
	}

	void setImpossiblePlayIcon(bool DifferentFreqFlag) {
		if (DifferentFreqFlag) {
			m_IconsFlag |= CLIPINFO_FLGMSK_DIFFERENTFREQ;
		} else {
			m_IconsFlag &= ~CLIPINFO_FLGMSK_DIFFERENTFREQ;
		}
	}
	
	void setProtectIcon(bool LockFlag) {
		if (LockFlag) {
			m_IconsFlag |= CLIPINFO_FLGMSK_PROTECT;
		} else {
			m_IconsFlag &= ~CLIPINFO_FLGMSK_PROTECT;
		}
	}

	void setP2StartIcon(GDI_IMAGE_ID imageId) { m_P2StartImageID = imageId; }
	void setReConnectIcon(bool _bReConnectFlag) { m_bReConnect = _bReConnectFlag; }

	void setFuncIcon(const CtClipInfo::ClipInfo &ClipInfoItem);

	void setMediaType(CtClipInfo::ClipInfoMediaType _mediaType) {m_MediaType = _mediaType;}

};

#endif
