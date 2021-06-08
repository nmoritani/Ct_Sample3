//#pragma once
#include "Ct.h"
#include "CtObject.h"
#include "CtWindowID.h"

#include "CtWindowContentsClipInfo.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsDrawThumb.h"
#include "CtWindowContentsThumbConfirm.h"
#include "CtWindowContentsThumbCommon.h"

/*
	コミット不要ファイル!!
	各自のローカルで編集すること
	→Templateな処理は後日追加するつもり(OKB)
*/
class CtDbgThumbnailFunc :	public CtObject
{
public:
	static CtDbgThumbnailFunc* getInstance();
	~CtDbgThumbnailFunc();
	
	void setThumbnailContent();
	void setThumbnailClip(int clip);
	void testDeleteProgressBar(int total = 100);
	void testCopyProgressBar(int total = 100);
	//	void setclipInfo(CtWindowID id, int startIndex, int count);
	
	
private:
	CtDbgThumbnailFunc();
	
	static void cbDrawStartCallback();
	static void cbDrawEndCallback();
	static bool cbThumbSyncSelectCallback(ContentsThumbSelectInfo* pInfo);
	static void cbThumbReqClipInfoCallback(int startIndex, int count);
	static void cbClipReqClipInfoCallback(int startIndex, int count);
	static void cbThumbSelectIndexCallback(int index);
	static void cbThumbStartDrawCallback(ContentsThumbInfo Info);

	static void Ct_ThumbnailTestTask();
	static void CtTestSendMessage(int type);
	static int CtTestRecvMessage();
	static void setclipInfo(CtWindowID id, int startIndex, int count);
	
	static ID TestTsk;
	static ID TestMbx;
	static CtWindowContentsDrawThumb *m_ThumbContents;
	static CtWindowContentsSelectClipInfo *m_SelectClipInfo;
	
	static CtDbgThumbnailFunc* 	m_pInstance;
	static CtWindowID			m_WindowID;
};

