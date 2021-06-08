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
	CtThumbCache();		//�ŏ��ɍ쐬���郊�X�g�̃T�C�Y��ݒ�
	~CtThumbCache();

	bool init(int size, CtWindowContentsThumbInit* pInitInfo);
	int getSize();
	CtThumbInfo* getThumbInfo(int clipNo, CtThumbButton* pButton = NULL);

	bool notifyPicture(CtWindowContentsDrawThumb* pContents);
	bool notifyClipInfo(CtWindowContentsSelectClipInfo* pContents);
	bool cancelRequest(int ClipNo = -1);	// ���^�X�N�R���e�L�X�g������Ă΂���
	
private:
	bool startRequest();
	bool requestPicture();
	bool requestClipInfo();

	bool checkCache(int current);
	bool removeCache(int index);
	
private:
	// APL I/F
	ContentsThumbReqClipInfoCallback	m_RequestClipInfo;		//�N���b�v���Ǎ��p
	ContentsThumbStartDrawCallback		m_RequestPicture;		//�T���l�C���摜�Ǎ��p(��)
	ContentsThumbSyncSelectCallback		m_SelectClip;			//�N���b�v��񓯊��p
	ContentsThumbSelectIndexCallback	m_SetFocus;				//�I�𒆃N���b�v�ʒm�p
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//�T���l�C���`��J�n�ʒm�p(�S��)
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//�T���l�C���`��I���ʒm�p(�S��)

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
