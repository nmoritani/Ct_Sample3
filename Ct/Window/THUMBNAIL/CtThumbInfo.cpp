#include "CtThumbInfo.h"
#include "gdi.h"
#include "CtThumbButton.h"

typedef struct _IconSetRecordFormat {
	CtClipInfo::ClipInfoFrequencyType freqtype;
	CtClipInfo::ClipInfoPixelType pixeltype;
	GDI_IMAGE_ID ImageID;
} IconSetRecordFormat;

static const IconSetRecordFormat IconClipFormat[] = {
	{ CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_3840,		IC_THUMBNAIL_FORMAT_UHD_59P },
	{ CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_3840,		IC_THUMBNAIL_FORMAT_UHD_50P },
	{ CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_3840,		IC_THUMBNAIL_FORMAT_UHD_29P },
	{ CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_3840,		IC_THUMBNAIL_FORMAT_UHD_25P },
	{ CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_3840,		IC_THUMBNAIL_FORMAT_UHD_23P },
	{ CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_59P },
	{ CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_59I },
	{ CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_50P },
	{ CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_50I },
	{ CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_29P },
	{ CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_25P },
	{ CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_1920,		IC_THUMBNAIL_FORMAT_FHD_23P },
	{ CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_1280,		IC_THUMBNAIL_FORMAT_HD_59P },
	{ CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_1280,		IC_THUMBNAIL_FORMAT_HD_50P },
	{ CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_720,		IC_THUMBNAIL_FORMAT_SD_50I },
	{ CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_720,		IC_THUMBNAIL_FORMAT_SD_59I },
};

CtThumbInfo::CtThumbInfo(int _clipNo) :
	m_Picture(GDI_INVALID_ID),
	m_FormatImageID(IMAGE_ID_INVALID),
	m_CodecImageID(IMAGE_ID_INVALID),
	m_MediaType(CtClipInfo::ClipInfoMediaType_None),
	m_IconsFlag(0),
	m_P2StartImageID(IMAGE_ID_INVALID),
	m_bReConnect(false)
{
	setClipNo(_clipNo);
	memset(m_ClipName, 0, sizeof(m_ClipName));
	memset(m_ClipStartTc, 0, sizeof(m_ClipStartTc));
}

CtThumbInfo::~CtThumbInfo()
{
	if (m_Picture != GDI_INVALID_ID)
		GDI_DeleteDrawable(m_Picture);
}
bool CtThumbInfo::isFunc(int btnType) {
	CtThumbButton::IconType _Type = (CtThumbButton::IconType)btnType;

	if (_Type == CtThumbButton::IconType_Resume && m_IconsFlag & CLIPINFO_FLGMSK_RESUME) {
		return true;
	}

	if (_Type == CtThumbButton::IconType_Delete && m_IconsFlag & CLIPINFO_FLGMSK_DELETE) {
		return true;
	}

	if (_Type == CtThumbButton::IconType_Copy && m_IconsFlag & CLIPINFO_FLGMSK_COPY) {
		return true;
	}
	return false;
}
void CtThumbInfo::invertFuncIcon() {
	m_IconsFlag ^= (CLIPINFO_FLGMSK_RESUME | CLIPINFO_FLGMSK_DELETE | CLIPINFO_FLGMSK_COPY);
}

void CtThumbInfo::setFuncIcon(const CtClipInfo::ClipInfo &ClipInfoItem) {
	if (ClipInfoItem.ResumeFlag) {
		m_IconsFlag |= CLIPINFO_FLGMSK_RESUME;
	}
	else {
		m_IconsFlag &= ~CLIPINFO_FLGMSK_RESUME;
	}
	if (ClipInfoItem.DeleteFlag) {
		m_IconsFlag |= CLIPINFO_FLGMSK_DELETE;
	}
	else {
		m_IconsFlag &= ~CLIPINFO_FLGMSK_DELETE;
	}
	if (ClipInfoItem.CopyFlag) {
		m_IconsFlag |= CLIPINFO_FLGMSK_COPY;
	}
	else {
		m_IconsFlag &= ~CLIPINFO_FLGMSK_COPY;
	}


}


void CtThumbInfo::setClipInfo(int clipNo, const CtClipInfo::ClipInfo& ClipInfo)
{
	GDI_IMAGE_ID FormatICId = selectFormatImageID(ClipInfo);
	GDI_IMAGE_ID CodecICId = selectCodecImageID(ClipInfo);
	GDI_IMAGE_ID P2StartId = selectP2StartImageID(ClipInfo);

	unsigned short work_clipNo = (unsigned short)clipNo;
	if (m_ClipNo != work_clipNo) {
		return;
	}

	setTitle(ClipInfo);
	setImpossiblePlayIcon(ClipInfo.DifferentFreqFlag);
	setProtectIcon(ClipInfo.LockFlag);
	setFormatIcon(FormatICId);
	setCodecIcon(CodecICId);
	setFuncIcon(ClipInfo);
	setMediaType(ClipInfo.MediaType);
	setClipInfoFlag(true);
	setReConnectIcon(ClipInfo.ReConnectFlag);
	setP2StartIcon(P2StartId);
}

void CtThumbInfo::setTitle(CtClipInfo::ClipInfo _info)
{
	if (NULL == &_info) {
		if (_info.StartTC.DFType == CtClipInfo::ClipInfoDFType_DF) {
			sprintf(m_ClipStartTc, "%s", "--:-- : --.--");
		}
		else {
			sprintf(m_ClipStartTc, "%s", "--:-- : --:--");
		}
	}
	else {
		(_info.StartTC.DFType == CtClipInfo::ClipInfoDFType_DF) ?
			sprintf(m_ClipStartTc, "%02d:%02d:%02d.%02d",
				_info.StartTC.Hour,
				_info.StartTC.Min,
				_info.StartTC.Sec,
				_info.StartTC.Frame)
			:
			sprintf(m_ClipStartTc, "%02d:%02d:%02d:%02d",
				_info.StartTC.Hour,
				_info.StartTC.Min,
				_info.StartTC.Sec,
				_info.StartTC.Frame);
	}
	if (NULL == _info.ClipName) {
		memset(m_ClipName, 0, sizeof(m_ClipName));
	}
	else {
		memcpy(m_ClipName, _info.ClipName, sizeof(m_ClipName));
	}
}

GDI_IMAGE_ID CtThumbInfo::selectCodecImageID(const CtClipInfo::ClipInfo &ClipInfo) {
	GDI_IMAGE_ID imageID = GDI_IMAGE_ID_MAX;
	switch (ClipInfo.CodecType) {
	case CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M:
		return IC_THUMBNAIL_FORMAT_420_150M;
	case CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M:
		return IC_THUMBNAIL_FORMAT_420_100M;
	case CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M:
		return IC_THUMBNAIL_FORMAT_420_50M;
	case CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M:
		return IC_THUMBNAIL_FORMAT_422_150M;
	case CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M:
		return IC_THUMBNAIL_FORMAT_422_100M;
	case CtClipInfo::ClipInfoCodecType_Mov_422LongG_50M:
		return IC_THUMBNAIL_FORMAT_422_50M;
	case CtClipInfo::ClipInfoCodecType_Mov_422Intra_400M:
		return IC_THUMBNAIL_FORMAT_ALLI_400M;
	case CtClipInfo::ClipInfoCodecType_Mov_422Intra_200M:
		return IC_THUMBNAIL_FORMAT_ALLI_200M;
	case CtClipInfo::ClipInfoCodecType_Mov_422Intra_100M:
		return IC_THUMBNAIL_FORMAT_ALLI_100M;
	case CtClipInfo::ClipInfoCodecType_Mov_HEVC_LongG_150M:
		return IC_THUMBNAIL_FORMAT_HEVC_150M;
	case CtClipInfo::ClipInfoCodecType_Mov_HEVC_LongG_200M:
		return IC_THUMBNAIL_FORMAT_HEVC_200M;
	case CtClipInfo::ClipInfoCodecType_Avchd_LongG_PS_25M:
		return IC_THUMBNAIL_FORMAT_AVCHD_PS;
	case CtClipInfo::ClipInfoCodecType_Avchd_LongG_PH_21M:
		return IC_THUMBNAIL_FORMAT_AVCHD_PH;
	case CtClipInfo::ClipInfoCodecType_Avchd_LongG_HA_17M:
		return IC_THUMBNAIL_FORMAT_AVCHD_HA;
	case CtClipInfo::ClipInfoCodecType_Avchd_LongG_PM_8M:
		return IC_THUMBNAIL_FORMAT_AVCHD_PM;
	case CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M:
		return IC_THUMBNAIL_FORMAT_420_150M;
	case CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M:
		return IC_THUMBNAIL_FORMAT_420_150M;
	case CtClipInfo::ClipInfoCodecType_Avchd_LongG_SA_9M:
		return IC_THUMBNAIL_FORMAT_AVCHD_SA;

	case CtClipInfo::ClipInfoCodecType_Mov_HEVC_LongG_100M:
		return IC_THUMBNAIL_FORMAT_HEVC_100M;
	case CtClipInfo::ClipInfoCodecType_Avc_Ultra_422Intra:
		return IC_THUMBNAIL_FORMAT_AVCHD_SA;
	case CtClipInfo::ClipInfoCodecType_Avc_Ultra_LongG50:
		return IC_THUMBNAIL_FORMAT_AVCHD_SA;
	case CtClipInfo::ClipInfoCodecType_Avc_Ultra_LongG25:
		return IC_THUMBNAIL_FORMAT_AVCHD_SA;
	case CtClipInfo::ClipInfoCodecType_Avc_Ultra_LongG12:
		return IC_THUMBNAIL_FORMAT_AVCHD_SA;
		break;
	}
	return imageID;
}

GDI_IMAGE_ID CtThumbInfo::selectFormatImageID(const CtClipInfo::ClipInfo &ClipInfo)
{
	GDI_IMAGE_ID imageID = GDI_IMAGE_ID_MAX;

	int size = 0;
	//CtDebugPrint(CtDbg, "FreqType [%d], PixelType [%d]\n", ClipInfo.FrequencyType, ClipInfo.PixelType);
	size = sizeof(IconClipFormat) / sizeof(IconClipFormat[0]);
	for (int i = 0; i < size; i++) {
		if ((ClipInfo.FrequencyType == IconClipFormat[i].freqtype) &&
			(ClipInfo.PixelType == IconClipFormat[i].pixeltype)) {
			imageID = IconClipFormat[i].ImageID;
			break;
		}
	}
	return imageID;
}

GDI_IMAGE_ID CtThumbInfo::selectP2StartImageID(const CtClipInfo::ClipInfo &ClipInfo)
{
	GDI_IMAGE_ID imageID = GDI_IMAGE_ID_MAX;

	switch (ClipInfo.P2Start){
	case CtClipInfo::ClipInfoP2StartType_Repairable:
		imageID = IC_THUMBNAIL_P2_CLIP_REPAIRABLE;
		break;
	case CtClipInfo::ClipInfoP2StartType_Unrepairable:
		imageID = IC_THUMBNAIL_P2_CLIP_UNREPAIRABLE;
		break;
	case CtClipInfo::ClipInfoP2StartType_Unknown:
		imageID = IC_THUMBNAIL_P2_CLIP_UNKNOWN;
		break;
	default:
		break;
	}
	return imageID;
}
