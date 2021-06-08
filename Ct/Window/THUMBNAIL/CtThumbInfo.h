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
	unsigned short					m_ClipNo;		//�N���b�vNo.(�����l�F1)
	GDI_IMAGE_ID					m_FormatImageID;//FORMAT�̃A�C�R��
	GDI_IMAGE_ID					m_CodecImageID;	//CODEC�̃A�C�R��
	CtClipInfo::ClipInfoMediaType	m_MediaType;	//���f�B�A�^�C�v(SD�J�[�h�̃X���b�g)
	unsigned short					m_IconsFlag;		
													//		1bit		IsSetClipInfo;			//�N���b�v���Z�b�g�ς݃t���O
													//		2bit		bImpossiblePlayIcon;	//�Đ��s�A�C�R��
													//		3bit		bProtectIcon;			//�v���e�N�g�A�C�R��
													//		4bit		Reserve;				//
													//		5bit		IsSetYuvImage;			//YUV�C���[�W�̃Z�b�g���
													//		6bit		DeleteFlag
													//		7bit		CopyFlag
													//		8bit		ResumeFlag
													//		9�`16bit	Reserved;
	GDI_IMAGE_ID					m_P2StartImageID;//P2�N���b�v�X�e�[�^�X�A�C�R��
	bool							m_bReConnect;	//Reconnect�A�C�R��

	char							m_ClipName[14];	//12byte:�N���b�v��/StartTC
	char							m_ClipStartTc[14];
	GDI_HANDLER						m_Picture;

public:
	CtThumbInfo(int _clipNo);
	virtual ~CtThumbInfo();

	//bool requestClipInfo(int clipNo);
	void setClipInfo(int clipNo, const CtClipInfo::ClipInfo& ClipInfo);
	
	//�N���b�v�ԍ��擾
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
	
	//FORMAT�̃A�C�R����ImageID�擾
	GDI_IMAGE_ID selectFormatImageID(const CtClipInfo::ClipInfo &ClipInfo);
	GDI_IMAGE_ID getFormatImageID()	{return m_FormatImageID;}
	
	//CODEC�̃A�C�R����ImageID�擾
	GDI_IMAGE_ID selectCodecImageID(const CtClipInfo::ClipInfo &ClipInfo);
	GDI_IMAGE_ID getCodecImageID() {return m_CodecImageID;}
	
	//�N���b�v���Z�b�g��Ԏ擾
	bool isSetClipInfo() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_SETCLIPINFO));}

	//�Đ��s�N���b�v�̃A�C�R���\��/��\��
	bool isImpossiblePlay() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_DIFFERENTFREQ));}

	//�v���e�N�g�̃A�C�R���\��/��\��
	bool isProtect() {return (0 != (m_IconsFlag & CLIPINFO_FLGMSK_PROTECT));}

	//ReConnect�̃A�C�R���\��/��\��
	bool isReConnect() { return m_bReConnect; }

	//�v���e�N�g�̃A�C�R���\����Ԕ��]
	void invertProtectIcon() {m_IconsFlag ^= CLIPINFO_FLGMSK_PROTECT;}

	//RESUME/DELETE/COPY...etc.�̃A�C�R���\��/��\��
	bool isFunc(int _Type);

	//RESUME/DELETE/COPY...etc.�̃A�C�R���\����Ԕ��]
	void invertFuncIcon();

	//�N���b�v���擾
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

	//�T���l�C���摜�Z�b�g��Ԏ擾
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
