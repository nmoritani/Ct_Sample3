#include "CtDbgClipManager.h"
#include "CtWindow.h"
#include "CtInterface.h"
#include "CtWindowContentsClipInfo.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"

CtDbgClipManager::CtDbgClipManager()
{
}

CtDbgClipManager::~CtDbgClipManager()
{
}

typedef bool(*pfunc1)(ContentsThumbSelectInfo*);
typedef void(*pfunc2)(ContentsThumbInfo);
typedef void(*pfunc3)(int startIndex, int count);
typedef void(*pfunc4)(int index);

static void setclipInfo(CtWindowID id, int startIndex, int count)
{
	CtWindowContentsSelectClipInfo *pContent1 = new CtWindowContentsSelectClipInfo(id);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	CtInterface *ifce = CtInterface::getInstance();

	/* DummyThumb */
	CtClipInfo::ClipInfo clipList[50];
	CtClipInfo ClipInfo[50];

	memset(&clipList, 0x00, sizeof(CtClipInfo::ClipInfo));
	memset(&ClipInfo, 0x00, sizeof(ClipInfo));

	for (int i = 0; i<6; i++) {
		clipList[i].PlayValidFlag = true;
		clipList[i].DifferentFreqFlag = true;
		clipList[i].LockFlag = true;
		clipList[i].ResumeFlag = true;
		clipList[i].ClipNumber = i + 1;
		sprintf(clipList[i].ClipName, "%s%d", "A001C00", i);
		clipList[i].MediaType = (CtClipInfo::ClipInfoMediaType)(i % 2);

		clipList[i].StartTC.Hour = 15;
		clipList[i].StartTC.Min = 22;
		clipList[i].StartTC.Sec = 13;

		clipList[i].StartUB.First = 12;
		clipList[i].StartUB.Second = 13;
		clipList[i].StartUB.Third = 14;
		clipList[i].StartUB.Fourth = 15;

		clipList[i].Duration.Hour = 11;
		clipList[i].Duration.Min = 12;
		clipList[i].Duration.Sec = 13;

		clipList[i].TimeZone.Hour = 23;
		clipList[i].TimeZone.Min = 11;

		clipList[i].FPSvalue.fps = (float)11.55;

		ClipInfo[i].setClipInfo(clipList[i]);
	}

	clipList[0].PlayValidFlag = true;
	clipList[0].DifferentFreqFlag = false;
	clipList[0].LockFlag = true;
	clipList[0].ResumeFlag = true;

	clipList[1].PlayValidFlag = true;
	clipList[1].DifferentFreqFlag = false;
	clipList[1].LockFlag = true;
	clipList[1].ResumeFlag = false;

	clipList[2].PlayValidFlag = false;
	clipList[2].DifferentFreqFlag = false;
	clipList[2].LockFlag = false;
	clipList[2].ResumeFlag = true;

	clipList[8].PlayValidFlag = true;
	clipList[8].DifferentFreqFlag = false;
	clipList[8].LockFlag = true;
	clipList[8].ResumeFlag = false;

	clipList[10].PlayValidFlag = true;
	clipList[10].DifferentFreqFlag = false;
	clipList[10].LockFlag = true;
	clipList[10].ResumeFlag = true;

	clipList[11].PlayValidFlag = false;
	clipList[11].DifferentFreqFlag = false;
	clipList[11].LockFlag = true;
	clipList[11].ResumeFlag = false;

	clipList[12].PlayValidFlag = false;
	clipList[12].DifferentFreqFlag = true;
	clipList[12].LockFlag = false;
	clipList[12].ResumeFlag = true;

	clipList[13].PlayValidFlag = true;
	clipList[13].DifferentFreqFlag = false;
	clipList[13].LockFlag = true;
	clipList[13].ResumeFlag = false;

	clipList[0].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_PS_25M;
	clipList[0].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[0].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[1].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_PH_21M;
	clipList[1].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[1].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[2].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_PM_8M;
	clipList[2].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994i;
	clipList[2].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[3].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_HA_17M;
	clipList[3].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[3].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[4].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_PM_8M;
	clipList[4].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000i;
	clipList[4].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[5].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_PH_21M;
	clipList[5].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994i;
	clipList[5].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[6].CodecType = CtClipInfo::ClipInfoCodecType_Avchd_LongG_HA_17M;
	clipList[6].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000i;
	clipList[6].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[7].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[7].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[7].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[8].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M;
	clipList[8].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2400p;
	clipList[8].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[9].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[9].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[9].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[10].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[10].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[10].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[11].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M;
	clipList[11].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[11].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[12].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M;
	clipList[12].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[12].PixelType = CtClipInfo::ClipInfoPixelType_4096;

	clipList[13].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_50M;
	clipList[13].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[13].PixelType = CtClipInfo::ClipInfoPixelType_4096;


	clipList[14].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[14].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[14].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[15].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[15].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[15].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[16].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[16].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[16].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[17].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[17].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[17].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[18].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[18].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[18].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[19].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M;
	clipList[19].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[19].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[20].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M;
	clipList[20].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[20].PixelType = CtClipInfo::ClipInfoPixelType_3840;

	clipList[21].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[21].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[21].PixelType = CtClipInfo::ClipInfoPixelType_2048;

	clipList[22].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M;
	clipList[22].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2400p;
	clipList[22].PixelType = CtClipInfo::ClipInfoPixelType_2048;

	clipList[23].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[23].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[23].PixelType = CtClipInfo::ClipInfoPixelType_2048;

	clipList[24].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[24].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[24].PixelType = CtClipInfo::ClipInfoPixelType_2048;

	clipList[25].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M;
	clipList[25].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[25].PixelType = CtClipInfo::ClipInfoPixelType_2048;

	clipList[26].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M;
	clipList[26].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[26].PixelType = CtClipInfo::ClipInfoPixelType_2048;


	clipList[27].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[27].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[27].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[28].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M;
	clipList[28].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[28].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[29].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[29].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[29].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[30].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[30].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[30].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[31].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M;
	clipList[31].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[31].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[32].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M;
	clipList[32].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000i;
	clipList[32].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[33].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M;
	clipList[33].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994i;
	clipList[33].PixelType = CtClipInfo::ClipInfoPixelType_1920;

	clipList[34].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M;
	clipList[34].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[34].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[35].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M;
	clipList[35].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[35].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[36].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[36].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[36].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[37].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M;
	clipList[37].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[37].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[38].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422Intra_100M;
	clipList[38].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[38].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[39].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422Intra_200M;
	clipList[39].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000i;
	clipList[39].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[40].CodecType = CtClipInfo::ClipInfoCodecType_Mov_422Intra_400M;
	clipList[40].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994i;
	clipList[40].PixelType = CtClipInfo::ClipInfoPixelType_1280;

	clipList[41].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[41].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[41].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[42].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[42].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[42].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[43].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[43].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2400p;
	clipList[43].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[44].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M;
	clipList[44].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5000p;
	clipList[44].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[45].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M;
	clipList[45].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2500p;
	clipList[45].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[46].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M;
	clipList[46].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2398p;
	clipList[46].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[47].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[47].FrequencyType = CtClipInfo::ClipInfoFrequencyType_5994p;
	clipList[47].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[48].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[48].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2997p;
	clipList[48].PixelType = CtClipInfo::ClipInfoPixelType_None;

	clipList[49].CodecType = CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M;
	clipList[49].FrequencyType = CtClipInfo::ClipInfoFrequencyType_2400p;
	clipList[49].PixelType = CtClipInfo::ClipInfoPixelType_None;


	for (int i = startIndex - 1; i < ((startIndex + count) - 1); i++) {
		CtClipInfo *clip = new CtClipInfo();
		clip->setClipInfo(clipList[i]);
		pContent1->addClipInfoList(clip);
	}
	pContent1->setTopIndex(startIndex);

	ifce->setWindowContents(ScreenLCD, id, pContent1);
	ifce->returnWindow(ScreenLCD, id);
}

static bool testContentsThumbSyncSelectCallback(ContentsThumbSelectInfo* pInfo)
{
	return true;
}

static void testContentsThumbStartDrawCallback(ContentsThumbInfo Info)
{
	return;
}

static void testContentsThumbReqClipInfoCallback(int startIndex, int count)
{
	setclipInfo(Window_ThumbNail_Delete, startIndex, count);
}

static void testContentsClipReqClipInfoCallback(int startIndex, int count)
{
	setclipInfo(Window_ThumbNailClip, startIndex, count);
}

static void testContentsThumbSelectIndexCallback(int index) {
	return;
}
void CtDbgClipManager::updateInfoContents(int clipNum ) {
	// Contents/Clip/etc...
	CtInterface *ifce = CtInterface::getInstance();
	pfunc1 p1 = testContentsThumbSyncSelectCallback;
	pfunc2 p2 = testContentsThumbStartDrawCallback;
	pfunc3 p3 = testContentsThumbReqClipInfoCallback;
	pfunc3 p3_2 = testContentsClipReqClipInfoCallback;
	pfunc4 p4 = testContentsThumbSelectIndexCallback;
	CtWindowContentsClipInfo *pContent = new CtWindowContentsClipInfo(ifce->getCurrentWindowID(ScreenLCD));
	pContent->setContentsThumbType(CtWindowContentsThumb::ContentsThumbType_ClipInfo);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);

	//pContent->setReqClipInfoCallback(p3);
	pContent->setStartDrawCallback(p2);
	pContent->setSyncSelectCallback(p1);
	pContent->setSelectIndexCallback(p4);

	pContent->setCurrentIndex(clipNum);
	//pContent->setClipCount(clipNum);

	ifce->setWindowContents(ScreenLCD, ifce->getCurrentWindowID(ScreenLCD), pContent);
}

void CtDbgClipManager::updateClipContents(int clipNum) {
	// Contents/Clip/etc...
	CtInterface *ifce = CtInterface::getInstance();
	pfunc1 p1 = testContentsThumbSyncSelectCallback;
	pfunc2 p2 = testContentsThumbStartDrawCallback;
	pfunc3 p3 = testContentsThumbReqClipInfoCallback;
	pfunc3 p3_2 = testContentsClipReqClipInfoCallback;
	pfunc4 p4 = testContentsThumbSelectIndexCallback;
	CtWindowContentsThumbInit *pContent = new CtWindowContentsThumbInit(ifce->getCurrentWindowID(ScreenLCD));
	pContent->setContentsThumbType(CtWindowContentsThumb::ContentsThumbType_Init);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);

	pContent->setFuncRequestClipInfo(p3);
	pContent->setFuncRequestPicture(p2);
	pContent->setFuncSelectClip(p1);
	pContent->setFuncSetFocus(p4);

	pContent->setCurrentIndex(clipNum);
	pContent->setClipCount(clipNum);

	ifce->setWindowContents(ScreenLCD, ifce->getCurrentWindowID(ScreenLCD), pContent);
}

#include "CtWindowContentsThumbConfirm.h"
void CtDbgClipManager::updateClipDelCopinfo(int selectNum, int totalNum){
	// Contents/Clip/etc...
	CtInterface *ifce = CtInterface::getInstance();
	CtWindowID winId = ifce->getCurrentWindowID(ScreenLCD);
	CtWindowContentsThumbConfirm* pWinCnts = new CtWindowContentsThumbConfirm(winId);

	ContentsThumbConfirmInfo ConfirmInfo = {0};

	ConfirmInfo.ClipNum = selectNum;
	ConfirmInfo.cnt = totalNum;

	if (winId == Window_Copying) {
		pWinCnts->setContentsThumbConfirmType(CtWindowContentsThumbConfirm::ContentsThumbType_Thumb_Copy);
	}
	else if(winId == Window_Deleting){
		pWinCnts->setContentsThumbConfirmType(CtWindowContentsThumbConfirm::ContentsThumbType_Thumb_Delete);
	}
	else {
		delete pWinCnts;
	}

	pWinCnts->setContentsThumbConfirmInfo(ConfirmInfo);

	ifce->setWindowContents(ScreenLCD, winId, pWinCnts);
	delete pWinCnts;
}
