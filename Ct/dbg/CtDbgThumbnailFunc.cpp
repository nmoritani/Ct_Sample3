#include "CtDbgThumbnailFunc.h"
#include "CtInterface.h"
#include "AplParamService.h"

#include "itron.h"
//#define DRAW_CLIPNUM		// サムネイル画像へのクリップ番号重畳処理
#ifdef DRAW_CLIPNUM
#include "windows.h"
#endif

#define TEST_CLIP_COUNT		(90*2)

CtWindowID CtDbgThumbnailFunc::m_WindowID = WindowNone;
CtWindowContentsDrawThumb* CtDbgThumbnailFunc::m_ThumbContents = NULL;
CtWindowContentsSelectClipInfo* CtDbgThumbnailFunc::m_SelectClipInfo = NULL;
ID CtDbgThumbnailFunc::TestTsk = 0;
ID CtDbgThumbnailFunc::TestMbx = 0;
CtDbgThumbnailFunc* CtDbgThumbnailFunc::m_pInstance = NULL;

CtDbgThumbnailFunc::CtDbgThumbnailFunc() 
{
	T_CTSK ctsk = { TA_HLNG | TA_ACT, 0, Ct_ThumbnailTestTask, 90, 0x4000, 0 };
	T_CMBX cmbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	TestTsk = acre_tsk(&ctsk);
	TestMbx = acre_mbx(&cmbx);

}

CtDbgThumbnailFunc::~CtDbgThumbnailFunc()
{
	if (m_SelectClipInfo) delete m_SelectClipInfo;
	if (m_ThumbContents) delete m_ThumbContents;
}


CtDbgThumbnailFunc* CtDbgThumbnailFunc::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CtDbgThumbnailFunc();

	return m_pInstance;
}

void CtDbgThumbnailFunc::cbDrawStartCallback()
{
	printf("[CB] DrawStart()\n");
}

void CtDbgThumbnailFunc::cbDrawEndCallback()
{
	printf("[CB] DrawEnd()\n");
}

bool CtDbgThumbnailFunc::cbThumbSyncSelectCallback(ContentsThumbSelectInfo* pInfo)
{
	printf("[CB] SyncSelectCallback(ClipNum:%d)\n", pInfo->ClipNum);
	return true;
}

void CtDbgThumbnailFunc::cbThumbReqClipInfoCallback(int startIndex, int count)
{
	printf("[CB] ReqClipInfoCallback(start:%d, count:%d) ...window:%08X\n", startIndex, count, CtDbgThumbnailFunc::m_WindowID);
	CtDbgThumbnailFunc::getInstance()->setclipInfo(CtDbgThumbnailFunc::m_WindowID, startIndex, count);

	CtTestSendMessage(2);
}

void CtDbgThumbnailFunc::cbClipReqClipInfoCallback(int startIndex, int count)
{
	printf("[CB] ReqClipInfoCallback_2(start:%d, count:%d ...window:%08X)\n", startIndex, count, CtDbgThumbnailFunc::m_WindowID);
	CtDbgThumbnailFunc::getInstance()->setclipInfo(CtDbgThumbnailFunc::m_WindowID, startIndex, count);

	CtTestSendMessage(2);
}

void CtDbgThumbnailFunc::cbThumbSelectIndexCallback(int index) {
	printf("[CB] SelectIndexCallback(%d)\n", index);
	return;
}

void CtDbgThumbnailFunc::cbThumbStartDrawCallback(ContentsThumbInfo Info)
{
	// シミュレータはRGBA8888フォーマットで描画するためYaddrのみ有効
	// 実機ではYUV420フォーマットで描画するためYaddr, Caddrのアドレスが有効
	printf("[CB] Get Picture(ClipNum:%d, Addr:%p)  ...window:%08X\n", Info.ClipNum, Info.Yaddr, CtDbgThumbnailFunc::m_WindowID);

	if (!Info.Yaddr || !Info.Size.Width || !Info.Size.Height) return;

	// 適当にサムネイル描画
	for (int i = 0; i<Info.Size.Height; i++) {
		for (int j = 0; j<Info.Size.Width; j++) {
			unsigned char r = j;
			unsigned char g = i;
			unsigned char b = (Info.ClipNum * 40) % 256;
			unsigned char a = 0xff;

			int pixel = (r << 24) | (g << 16) | (b << 8) | a;

			memcpy(((int*)Info.Yaddr) + (Info.Size.Width * i + j), &pixel, sizeof(pixel));
		}
	}

#ifdef DRAW_CLIPNUM
	{
		BITMAPINFOHEADER header;
		WCHAR text[32] = { 0x00 };

		header.biSize = sizeof(header);
		header.biWidth = 32;
		header.biHeight = 18;
		header.biPlanes = 1;
		header.biBitCount = 32;
		header.biCompression = BI_RGB;
		header.biSizeImage = 0;
		header.biXPelsPerMeter = 0;
		header.biYPelsPerMeter = 0;
		header.biClrUsed = 0;
		header.biClrImportant = 0;

		int bytesize = header.biWidth * header.biHeight * 32 / 8;
		BYTE *Buffer = new BYTE[bytesize];

		HDC hDC = GetDC(NULL);
		HBITMAP hBmp = CreateCompatibleBitmap(hDC, header.biWidth, header.biHeight);
		ReleaseDC(NULL, hDC);

		HDC drawDC = CreateCompatibleDC(NULL);
		SelectObject(drawDC, hBmp);

		swprintf(text, __TEXT("%04d"), Info.ClipNum);

		TextOut(drawDC, 0, 0, text, lstrlen(text));
		DeleteDC(drawDC);

		hDC = GetDC(NULL);
		GetDIBits(hDC, hBmp, 0, header.biHeight, Buffer, (LPBITMAPINFO)&header, DIB_RGB_COLORS);
		ReleaseDC(NULL, hDC);
		DeleteObject(hBmp);

		// サムネイルのpos(60,20)付近にクリップ番号文字を描画
		for (int i = 0; i < header.biHeight; i++) {
			memcpy((int*)Info.Yaddr + (i + 60)  * Info.Size.Width + 20, (int*)(Buffer + bytesize) - (i + 1) * header.biWidth, header.biWidth * header.biBitCount / 8);
		}
		delete Buffer;
	}
#endif

	if (m_ThumbContents) delete m_ThumbContents;
	m_ThumbContents = new CtWindowContentsDrawThumb(CtDbgThumbnailFunc::m_WindowID);
	m_ThumbContents->setDrawThumbInfo(Info);

	// テストタスクにサムネイル描画完了を通知
	CtTestSendMessage(1);

	return;
}

void CtDbgThumbnailFunc::setThumbnailContent()
{
	CtWindowContentsThumbInit *pContent = new CtWindowContentsThumbInit(CtDbgThumbnailFunc::m_WindowID);
	pContent->setContentsThumbType(CtWindowContentsThumb::ContentsThumbType_Init);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);

	pContent->setFuncNotifyDrawStart(cbDrawStartCallback);
	pContent->setFuncNotifyDrawEnd(cbDrawEndCallback);

	pContent->setFuncRequestClipInfo(cbThumbReqClipInfoCallback);
	pContent->setFuncRequestPicture(cbThumbStartDrawCallback);
	pContent->setFuncSelectClip(cbThumbSyncSelectCallback);
	pContent->setFuncSetFocus(cbThumbSelectIndexCallback);

	pContent->setCurrentIndex(TEST_CLIP_COUNT);
	pContent->setClipCount(TEST_CLIP_COUNT);

	CtInterface::getInstance()->setWindowContents(ScreenLCD, CtDbgThumbnailFunc::m_WindowID, pContent);
	delete pContent;
}

void CtDbgThumbnailFunc::setThumbnailClip(int clip)
{
	m_WindowID = CtInterface::getInstance()->getCurrentWindowID(ScreenLCD);
	//	CtDebugPrint(CtDbg, "Windowid : %08X\n", CtDbgThumbnailFunc::m_WindowID);
	
	CtWindowContentsThumbInit *pContent = new CtWindowContentsThumbInit(CtDbgThumbnailFunc::m_WindowID);
	pContent->setContentsThumbType(CtWindowContentsThumb::ContentsThumbType_Init);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);

	pContent->setFuncNotifyDrawStart(cbDrawStartCallback);
	pContent->setFuncNotifyDrawEnd(cbDrawEndCallback);

	pContent->setFuncRequestClipInfo(cbThumbReqClipInfoCallback);
	pContent->setFuncRequestPicture(cbThumbStartDrawCallback);
	pContent->setFuncSelectClip(cbThumbSyncSelectCallback);
	pContent->setFuncSetFocus(cbThumbSelectIndexCallback);

	if (clip == 0) {
		pContent->setCurrentIndex(0);
		pContent->setClipCount(0);
	} else {
		pContent->setCurrentIndex(clip);
		pContent->setClipCount(TEST_CLIP_COUNT);
	}

	CtInterface::getInstance()->setWindowContents(ScreenLCD, CtDbgThumbnailFunc::m_WindowID, pContent);
	delete pContent;
}

void CtDbgThumbnailFunc::testDeleteProgressBar(int total/*Default : 100*/) {
	CtWindowContentsThumbConfirm* pc = new CtWindowContentsThumbConfirm(CtDbgThumbnailFunc::m_WindowID);
	for (int i = 0; i <= total; i++) {
		ContentsThumbConfirmInfo cntInfo = { (unsigned long)i, true, (unsigned long)total };
		pc->setContentsThumbConfirmInfo(cntInfo);
		CtInterface::getInstance()->setWindowContents(ScreenAll, CtDbgThumbnailFunc::m_WindowID, pc);
		dly_tsk(100);
	}
	delete pc;
}

void CtDbgThumbnailFunc::testCopyProgressBar(int total/*Default : 100*/) {
	for (int i = 0; i <= total; i++) {
		APL_PARAM_SET_DATA(AplParamPlayGeneralProgressBar, i);
		dly_tsk(100);
	}
}

void CtDbgThumbnailFunc::setclipInfo(CtWindowID id, int startIndex, int count)
{
	// 古いコンテンツを削除
	if (m_SelectClipInfo) delete m_SelectClipInfo;
	m_SelectClipInfo = new CtWindowContentsSelectClipInfo(id);

	APL_PARAM_SET_DATA(AplParamPlayMovIcon, APL_SYS_PARAM_PLAY_MOV_ICON_SELECT);
	APL_PARAM_SET_DATA(AplParamSlot2InOutStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSlot1InOutStatus, APL_SYS_PARAM_SWITCH_ON);

	/* DummyThumb */
	CtClipInfo::ClipInfo clipList[TEST_CLIP_COUNT];
	CtClipInfo clipInfos[TEST_CLIP_COUNT];

	const struct DbgClipInfo {
		CtClipInfo::ClipInfoCodecType CodecType;
		CtClipInfo::ClipInfoFrequencyType FreqType;
		CtClipInfo::ClipInfoPixelType PixelType;
	} dummyInfos[] = {
		// CodecType											// FreqType										// PixelType
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_PS_25M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_1920 },	// 00
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_PH_21M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_PM_8M,		CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_HA_17M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_PM_8M,		CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_PH_21M,		CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Avchd_LongG_HA_17M,		CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M,		CtClipInfo::ClipInfoFrequencyType_2400p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_4096 },	// 10
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_50M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_4096 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_3840 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_3840 },	// 20
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M,		CtClipInfo::ClipInfoFrequencyType_2400p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_2048 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_1920 },	// 30
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_150M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M,		CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422LongG_100M,		CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_1920 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_150M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_100M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_50M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422Intra_100M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422Intra_200M,		CtClipInfo::ClipInfoFrequencyType_5000i,		CtClipInfo::ClipInfoPixelType_1280 },
		{ CtClipInfo::ClipInfoCodecType_Mov_422Intra_400M,		CtClipInfo::ClipInfoFrequencyType_5994i,		CtClipInfo::ClipInfoPixelType_1280 },	// 40
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_2400p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M,		CtClipInfo::ClipInfoFrequencyType_5000p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M,		CtClipInfo::ClipInfoFrequencyType_2500p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_6M,		CtClipInfo::ClipInfoFrequencyType_2398p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_5994p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_2997p,		CtClipInfo::ClipInfoPixelType_None },
		{ CtClipInfo::ClipInfoCodecType_Mov_420LongG_12M,		CtClipInfo::ClipInfoFrequencyType_2400p,		CtClipInfo::ClipInfoPixelType_None },
	};

	memset(clipList, 0x00, sizeof(clipList));
	memset(clipInfos, 0x00, sizeof(clipInfos));

	for (int i = 0; i<TEST_CLIP_COUNT; i++) {
		clipList[i].PlayValidFlag = true;
		clipList[i].DifferentFreqFlag = true;
		{
			switch (i % 4) {
			default:
			case 0:
				clipList[i].LockFlag = true;
				clipList[i].ReConnectFlag = false;
				clipList[i].P2Start = CtClipInfo::ClipInfoP2StartType_Normal;
				break;
			case 1:
				clipList[i].LockFlag = false;
				clipList[i].ReConnectFlag = true;
				clipList[i].P2Start = CtClipInfo::ClipInfoP2StartType_Repairable;
				break;
			case 2:
				clipList[i].LockFlag = false;
				clipList[i].ReConnectFlag = true;
				clipList[i].P2Start = CtClipInfo::ClipInfoP2StartType_Unrepairable;
				break;
			case 3:
				clipList[i].LockFlag = false;
				clipList[i].ReConnectFlag = true;
				clipList[i].P2Start = CtClipInfo::ClipInfoP2StartType_Unknown;
				break;
			}
		}
		clipList[i].ResumeFlag = true;
		clipList[i].ClipNumber = i + 1;
		sprintf(clipList[i].ClipName, "%s%d", "A001C00", i);
		
		CtClipInfo::ClipInfoMediaType type;
		if (i % 2)	type = CtClipInfo::ClipInfoMediaType_SD2;
		else		type = CtClipInfo::ClipInfoMediaType_SD1;
		clipList[i].MediaType = (type);

		clipList[i].StartTC.Hour = 15;
		clipList[i].StartTC.Min = 22;
		clipList[i].StartTC.Sec = 13;
		clipList[i].StartTC.Frame = i % 100;

		clipList[i].StartUB.First = 12;
		clipList[i].StartUB.Second = 13;
		clipList[i].StartUB.Third = 14;
		clipList[i].StartUB.Fourth = 15;

		clipList[i].Duration.Hour = 11;
		clipList[i].Duration.Min = 12;
		clipList[i].Duration.Sec = 13;

		clipList[i].TimeZone.Hour = 23;
		clipList[i].TimeZone.Min = 11;

		clipList[i].CodecType     = dummyInfos[i % (sizeof(dummyInfos) / sizeof(dummyInfos[0]))].CodecType;
		clipList[i].FrequencyType = dummyInfos[i % (sizeof(dummyInfos) / sizeof(dummyInfos[0]))].FreqType;
		clipList[i].PixelType     = dummyInfos[i % (sizeof(dummyInfos) / sizeof(dummyInfos[0]))].PixelType;

		clipInfos[i].setClipInfo(clipList[i]);
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
	clipList[2].ResumeFlag = false;
	clipList[2].DeleteFlag = true;

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

	for (int i = 0; i < count; i++) {
		CtClipInfo *clip = new CtClipInfo();
		clip->setClipInfo(clipList[i + (startIndex - 1)]);
		m_SelectClipInfo->addClipInfoList(clip);
	}
	m_SelectClipInfo->setTopIndex(startIndex);
}

void CtDbgThumbnailFunc::Ct_ThumbnailTestTask()
{
	while (1) {
		int type = CtTestRecvMessage();

		switch (type) {
		case 1:
		{
			// サムネイル描画完了
			if (m_ThumbContents) {
				CtInterface::getInstance()->setWindowContents(ScreenLCD, CtDbgThumbnailFunc::m_WindowID, m_ThumbContents);
			}
		}
		break;
		case 2:
		{
			// クリップ情報取得完了
			if (m_SelectClipInfo) {
				CtInterface::getInstance()->setWindowContents(ScreenLCD, m_SelectClipInfo->getType(), m_SelectClipInfo);
			}
		}
		break;
		default:
			break;
		}
	}
}

static struct TestMessage {
	T_MSG msg;
	int type;
} test_msg;

void CtDbgThumbnailFunc::CtTestSendMessage(int type)
{
	memset(&test_msg, 0, sizeof(test_msg));
	test_msg.type = type;

	snd_mbx(TestMbx, (T_MSG*)&test_msg);
}

int CtDbgThumbnailFunc::CtTestRecvMessage()
{
	TestMessage *msg = NULL;
	rcv_mbx(TestMbx, (T_MSG**)&msg);
	return msg->type;
}
