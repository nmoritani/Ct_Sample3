#pragma once
/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbCache
*/

#ifndef __CtThumbCache_H__
#define __CtThumbCache_H__

#include "CtList.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsDrawThumb.h"
#include "CtWindowContentsSelectClipInfo.h"
#include "CtThumbInfo.h"

class CtThumbButton;

class CtThumbCache : public CtObject {
public:
	CtThumbCache();		//最初に作成するリストのサイズを設定
	~CtThumbCache();

	bool init(int size, CtWindowContentsThumbInit* pInitInfo);
	int getSize();
	CtThumbInfo* getThumbInfo(int clipNo, CtThumbButton* pButton = NULL);

	bool notifyPicture(CtWindowContentsDrawThumb* pContents);
	bool notifyClipInfo(CtWindowContentsSelectClipInfo* pContents);
	bool cancelRequest(int ClipNo = -1);	// 他タスクコンテキストからも呼ばれるよ
	
private:
	bool startRequest();
	bool requestPicture();
	bool requestClipInfo();

	bool checkCache(int current);
	bool removeCache(int index);
	
private:
	// APL I/F
	ContentsThumbReqClipInfoCallback	m_RequestClipInfo;		//クリップ情報読込用
	ContentsThumbStartDrawCallback		m_RequestPicture;		//サムネイル画像読込用(個別)
	ContentsThumbSyncSelectCallback		m_SelectClip;			//クリップ情報同期用
	ContentsThumbSelectIndexCallback	m_SetFocus;				//選択中クリップ通知用
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//サムネイル描画開始通知用(全体)
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//サムネイル描画終了通知用(全体)

	CtVector::Vector<CtThumbInfo*>		m_list;
	
	enum ReadingState {
		State_RequestPicture,
		State_ReceivePicture,
		State_RequestClipInfo,
		State_ReceiveClipInfo,
		State_Complete,
		State_Invalid
	};
	struct ReadingInfo {
		unsigned long	m_ClipNo;
		ReadingState	m_State;
		CtThumbInfo* 	m_pThumbInfo;
		CtThumbButton*	m_pButton;
	};
	
	ReadingInfo*		m_pReading;
	
	CtList::list<ReadingInfo*>	m_RequestQueue;
	
	int m_CacheCount;
	static const int MaxCacheCount = 100;

private:
	ReadingInfo* getRequestQueue();
	bool putRequestQueue(ReadingInfo* pRequest);
	
};

#endif
