#ifndef __CtWindowContentsClipInfo_H__
#define __CtWindowContentsClipInfo_H__

#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"
#include "CtVector.h"
class CtClipInfo : public CtObject {
public:
	typedef enum ClipInfoCodecType {
		ClipInfoCodecType_None,
		ClipInfoCodecType_Avchd_LongG_PS_25M,
		ClipInfoCodecType_Avchd_LongG_PH_21M,
		ClipInfoCodecType_Avchd_LongG_HA_17M,
		ClipInfoCodecType_Avchd_LongG_PM_8M,
		ClipInfoCodecType_Avchd_LongG_SA_9M,
		ClipInfoCodecType_Mov_420LongG_150M,
		ClipInfoCodecType_Mov_420LongG_100M,
		ClipInfoCodecType_Mov_420LongG_50M,
		ClipInfoCodecType_Mov_420LongG_12M,
		ClipInfoCodecType_Mov_420LongG_6M,
		ClipInfoCodecType_Mov_422LongG_150M,
		ClipInfoCodecType_Mov_422LongG_100M,
		ClipInfoCodecType_Mov_422LongG_50M,
		ClipInfoCodecType_Mov_422Intra_400M,
		ClipInfoCodecType_Mov_422Intra_200M,
		ClipInfoCodecType_Mov_422Intra_100M,
		ClipInfoCodecType_Mov_HEVC_LongG_200M,
		ClipInfoCodecType_Mov_HEVC_LongG_150M,
		// add
		ClipInfoCodecType_Mov_HEVC_LongG_100M,
		ClipInfoCodecType_Avc_Ultra_422Intra,
		ClipInfoCodecType_Avc_Ultra_LongG50,
		ClipInfoCodecType_Avc_Ultra_LongG25,
		ClipInfoCodecType_Avc_Ultra_LongG12,
	} ClipInfoCodecType;

	typedef enum ClipInfoFrequencyType {
		ClipInfoFrequencyType_None,
		ClipInfoFrequencyType_5994p,
		ClipInfoFrequencyType_5994i,
		ClipInfoFrequencyType_5000p,
		ClipInfoFrequencyType_5000i,
		ClipInfoFrequencyType_2997p,
		ClipInfoFrequencyType_2500p,
		ClipInfoFrequencyType_2400p,
		ClipInfoFrequencyType_2398p,
	} ClipInfoFrequencyType;

	typedef enum ClipInfoPixelType {
		ClipInfoPixelType_None,
		ClipInfoPixelType_720,
		ClipInfoPixelType_4096,
		ClipInfoPixelType_3840,
		ClipInfoPixelType_2048,
		ClipInfoPixelType_1920,
		ClipInfoPixelType_1280,
	} ClipInfoPixelType;

	typedef enum ClipInfoMediaType {
		ClipInfoMediaType_None,
		ClipInfoMediaType_SD1,
		ClipInfoMediaType_SD2,
	} ClipInfoMediaType;

	typedef enum ClipInfoDFType {
		ClipInfoDFType_DF,
		ClipInfoDFType_NDF,
	} ClipInfoDFType;

	typedef enum ClipInfoP2StartType {
		ClipInfoP2StartType_Normal,
		ClipInfoP2StartType_Repairable,
		ClipInfoP2StartType_Unrepairable,
		ClipInfoP2StartType_Unknown,
	}ClipInfoP2StartType;

	typedef struct ClipInfoTimeCode {
		bool			ValidFlag;
		ClipInfoDFType	DFType;
		unsigned char	Hour;
		unsigned char	Min;
		unsigned char	Sec;
		unsigned char	Frame;
	} ClipInfoTimeCode;

	typedef struct ClipInfoUB {
		bool			ValidFlag;
		unsigned char	First;
		unsigned char	Second;
		unsigned char	Third;
		unsigned char	Fourth;
	} ClipInfoUB;

	typedef struct ClipInfoFPS {
		bool	ValidFlag;
		float	fps;
	} ClipInfoFPS;

	typedef struct ClipInfoDate {
		bool			ValidFlag;
		unsigned short	Year;
		unsigned char	Month;
		unsigned char	Day;
	} ClipInfoDate;

	typedef struct ClipInfoTime {
		bool			ValidFlag;
		unsigned char	Hour;
		unsigned char	Min;
		unsigned char	Sec;
	} ClipInfoTime;

	typedef struct ClipInfoDateTime {
		ClipInfoDate Date;
		ClipInfoTime Time;
	} ClipInfoDateTime;

	typedef struct ClipInfoTimeZone {
		bool			ValidFlag;
		bool			SignFlag;
		unsigned char	Hour;
		unsigned char	Min;
	} ClipInfoTimeZone;

	typedef struct ClipInfo {
		bool PlayValidFlag;
		bool DifferentFreqFlag;
		bool LockFlag;
		bool ResumeFlag;
		bool SelectFlag;
		bool DeleteFlag;
		bool CopyFlag;
		bool ReConnectFlag;
		unsigned long ClipNumber;
		char ClipName[14];
		ClipInfoCodecType		CodecType;
		ClipInfoFrequencyType	FrequencyType;
		ClipInfoPixelType		PixelType;
		ClipInfoMediaType	MediaType;
		ClipInfoTimeCode	StartTC;
		ClipInfoUB			StartUB;
		ClipInfoDateTime	DateTime;
		ClipInfoTimeZone	TimeZone;
		ClipInfoTimeCode	Duration;
		ClipInfoFPS			FPSvalue;
		ClipInfoP2StartType P2Start;
		char CaptureGamma[32];
		ClipInfo() {
			memset(this, 0, sizeof(ClipInfo));
		}
	} ClipInfo;

	CtClipInfo();
	CtClipInfo(CtClipInfo& obj);  /*ïœêîÇ∆ä÷êîìØñºÇ≈Ç∑*/
	virtual ~CtClipInfo();

	ClipInfo getClipInfo();
	void setClipInfo(ClipInfo& info);

private:
	ClipInfo m_ClipInfo;
};
class CtWindowContentsClipInfo : public CtWindowContentsThumb {
public:
	typedef CtVector::Vector<CtClipInfo*> ClipInfoList;
	typedef CtVector::Vector<CtClipInfo*>::iterator ClipInfoListItr;

	CtWindowContentsClipInfo(const CtWindowID WindowID);
	CtWindowContentsClipInfo(CtWindowContentsClipInfo& ContentsClipInfo);
	~CtWindowContentsClipInfo();

	unsigned long getCurrentIndex();
	void setCurrentIndex(unsigned long Index);
	ClipInfoList& getClipInfoList();
	void setStartDrawCallback(ContentsThumbStartDrawCallback callback);
	ContentsThumbStartDrawCallback getStartDrawCallback();
	void setClipInfoList(CtClipInfo* pCtClipInfo);
	void setSyncSelectCallback(ContentsThumbSyncSelectCallback callback);
	ContentsThumbSyncSelectCallback getSyncSelectCallback();

	void setSelectIndexCallback(ContentsThumbSelectIndexCallback callback);
	ContentsThumbSelectIndexCallback getSelectIndexCallback();

private:
	void removeAllClipInfo();

	unsigned long m_CurrentIndex;
	ClipInfoList m_ClipInfoList;
	ContentsThumbStartDrawCallback m_StartDrawCallback;
	ContentsThumbSyncSelectCallback m_SyncSelectCallback;
	ContentsThumbSelectIndexCallback m_SelectIndexCallback;
};

#endif
