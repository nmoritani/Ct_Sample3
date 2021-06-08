/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbButton
*/

#include "CtThumbCache.h"
#include "CtDrawCache.h"
#include "CtThumbnailUtil.h"
#include "CtThumbButton.h"
#include "gdi.h"
#include "gdi_local.h"

CtThumbCache::CtThumbCache() :
	m_RequestClipInfo(NULL),
	m_RequestPicture(NULL),
	m_SelectClip(NULL),
	m_SetFocus(NULL),
	m_NotifyDrawStart(NULL),
	m_NotifyDrawEnd(NULL),
	m_pReading(NULL),
	m_CacheCount(0)
	
{
	m_list.clear();
}

CtThumbCache::~CtThumbCache()
{
	CtDrawCache *pCache = CtDrawCache::getInstance();
	
	for (int i = 0; i < m_list.size(); i++) {
		if (m_list[i] == NULL) continue;
		
		delete m_list[i];
		m_list[i] = NULL;
	}
	m_list.clear();
}

bool CtThumbCache::init(int size, CtWindowContentsThumbInit* pInitInfo)
{
	cancelRequest();
	
	if (m_list.size() > 0) {
		for (int i = 0; i < m_list.size(); i++) {
			if (m_list[i] == NULL) continue;

			delete m_list[i];
			m_list[i] = NULL;
		}
		m_list.clear();
	}
	
	if (pInitInfo == NULL) {
		m_RequestClipInfo = NULL;
		m_RequestPicture = NULL;
		m_SelectClip = NULL;
		m_SetFocus = NULL;
		m_NotifyDrawStart = NULL;
		m_NotifyDrawEnd = NULL;

	} else {
		m_RequestClipInfo = pInitInfo->getFuncRequestClipInfo();
		m_RequestPicture = pInitInfo->getFuncRequestPicture();
		m_SelectClip = pInitInfo->getFuncSelectClip();
		m_SetFocus = pInitInfo->getFuncSetFocus();
		m_NotifyDrawStart = pInitInfo->getFuncNotifyDrawStart();
		m_NotifyDrawEnd = pInitInfo->getFuncNotifyDrawEnd();
		
		m_list.resize(size +1);
		for (int i = 0; i < m_list.size(); i++) {
			if (m_list[i] == NULL) continue;
			
			delete m_list[i];
			m_list[i] = NULL;
		}
	}
	return true;
}


CtThumbInfo* CtThumbCache::getThumbInfo(int clipNo, CtThumbButton* pButton)
{
	if ((clipNo <= 0) || (m_list.size() < clipNo))
		return NULL;

	if (m_list[clipNo] != NULL)
		return m_list[clipNo];

	if (pButton == NULL)
		return NULL;
	
	ReadingInfo* pRequest = (ReadingInfo*)operator new(sizeof(ReadingInfo));
	if (pRequest == NULL)
		return NULL;
	
	CtThumbInfo* pThumbInfo = new CtThumbInfo(clipNo);
	if (pThumbInfo == NULL)
		return NULL;

	if ((m_RequestQueue.size() == 0) && (m_pReading == NULL)) {
		if (m_NotifyDrawStart != NULL) (*m_NotifyDrawStart)();
	}
	
	pRequest->m_State = State_RequestPicture;
	pRequest->m_ClipNo = clipNo;
	pRequest->m_pButton = pButton;
	pRequest->m_pThumbInfo = pThumbInfo;
	
	putRequestQueue(pRequest);

	startRequest();
	
	return NULL;
}

bool CtThumbCache::startRequest()
{
	if (m_pReading == NULL) {
		if ((m_pReading = getRequestQueue()) == NULL)
			return false;
	}

	switch (m_pReading->m_State) {
	case State_RequestPicture:
		requestPicture();
		break;
		
	case State_RequestClipInfo:
		requestClipInfo();
		break;
		
	case State_Complete:
		m_pReading = NULL;
		break;
		
	default:
		return false;
		break;
	}
	return true;
}

bool CtThumbCache::requestPicture()
{
	GDI_HANDLER pict;
	CtLabel* pLabel = NULL;
	ReadingInfo* pReading = NULL;

	if (m_pReading == NULL) {
		if ((m_pReading = getRequestQueue()) == NULL)
			return false;
	}

	if (m_RequestPicture == NULL)
		return false;

	if ((m_pReading->m_pThumbInfo == NULL) || (m_pReading->m_pButton == NULL))
		return false;
	
	if (/*m_pReading->m_ClipNo < 0 || (符号なし型を符号有か確認は不要)*/((unsigned int)m_list.size()) < m_pReading->m_ClipNo)
		return false;

	if ((pLabel = new CtLabel(m_pReading->m_pButton->getPictureSize())) == NULL)
		return false;
	
	// サムネイル描画領域取得
#ifndef WIN32_GUI_SIM
	CtColorFormat format = Format_YUV420;
#else
	CtColorFormat format = Format_RGBA8888;
#endif
	CtDraw *pDraw = CtDraw::getInstance();
	pDraw->getDrawing(true);
	pict = pDraw->convertDrawable(pLabel, format);
	pDraw->freeDrawing();

	delete pLabel;
	
	m_pReading->m_pThumbInfo->setPicture(pict);	//空のYUV Drawableを登録(PICT要求で直接YUVバッファに転送)
	
	gdi_pbuffer_context* pContext = (gdi_pbuffer_context *)pict;
	if (!pContext) return false;

	// サムネイル描画の要求
	ContentsThumbInfo PictInfo = {
		ContentsThumbResultType_OK,
		(unsigned long)m_pReading->m_ClipNo,	//クリップNo.
		{
			pContext->width,					//画像の幅
			pContext->height					//画像の高さ
		},
		pContext->color_buffer0,				//Yプレーンアドレス
		pContext->color_buffer1					//Cプレーンアドレス
	};

	// コールバックでサムネイル描画を要求
	(*m_RequestPicture)(PictInfo);
	m_pReading->m_State = State_ReceivePicture;
	
	// color_bufferへのサムネイル描画完了後
	// CtWindowMainのupdateContents経由でCtWindowContentsDrawThumbが届く
	return true;
}

bool CtThumbCache::notifyPicture(CtWindowContentsDrawThumb* pContents)
{
	if (pContents == NULL) return false;
	if (m_pReading == NULL) return false;

	ContentsThumbInfo Info = pContents->getDrawThumbInfo();

	if (Info.Result != ContentsThumbResultType_OK)
		return false;

	if ((m_pReading->m_pThumbInfo == NULL) || (m_pReading->m_pButton == NULL))
		return false;

	if (m_pReading->m_ClipNo != Info.ClipNum)
		return false;
	
	m_pReading->m_State = State_RequestClipInfo;
	requestClipInfo();
	
	return true;
}

bool CtThumbCache::requestClipInfo()
{
	if (m_RequestClipInfo == NULL) return false;
	if (m_pReading == NULL) return false;
	
	(*m_RequestClipInfo)(m_pReading->m_ClipNo, 1);
	
	return true;
}

bool CtThumbCache::notifyClipInfo(CtWindowContentsSelectClipInfo* pContents)
{
	if (pContents == NULL) return false;
	if (m_pReading == NULL) return false;
	
	CtWindowContentsClipInfo::ClipInfoList& clip_list = pContents->getClipInfoList();
	unsigned long clipNo = pContents->getTopIndex();
	
	if (m_pReading->m_ClipNo != clipNo)
		return false;

	if (m_pReading->m_pThumbInfo == NULL)
		return false;

	if (clipNo >= (unsigned long)m_list.size())
		return false;
	
	m_pReading->m_pThumbInfo->setClipInfo(clipNo, clip_list[0]->getClipInfo());

	m_list[clipNo] = m_pReading->m_pThumbInfo;
	m_CacheCount++;
	checkCache(clipNo);

	CtThumbButton* pButton = m_pReading->m_pButton;
	if ((pButton != NULL) && (pButton->getClipNo() == m_pReading->m_ClipNo)) {
		pButton->setThumbInfo(m_pReading->m_pThumbInfo);
	}
	
	operator delete(m_pReading);
	m_pReading = NULL;
	
	if ((m_pReading = getRequestQueue()) != NULL) {
		startRequest();
		
	} else {
		if (m_NotifyDrawEnd != NULL) (*m_NotifyDrawEnd)();
	}
	
	return true;
}


int CtThumbCache::getSize()
{
	return m_list.size();
}

bool CtThumbCache::checkCache(int current)
{
	if (m_CacheCount < MaxCacheCount)
		return false;
	
	int start = (current + m_list.size()/2) % m_list.size();
	int size = m_list.size();
	int loop = size/2;
	
	for (int i = 0; i < loop; i++) {
		if ((removeCache((size + start + i)%size) == true) || (removeCache((size + start - i)%size) == true))
			return true;
	}
	return false;
}	

bool CtThumbCache::removeCache(int index)
{
	if ((index < 0) || (m_list.size() <= index))
		return false;

	if (m_list[index] == NULL)
		return false;

	delete m_list[index];
	m_list[index] = NULL;
	m_CacheCount--;
	
	return true;
}

CtThumbCache::ReadingInfo* CtThumbCache::getRequestQueue()
{
	ReadingInfo *pRequest = NULL;
	
	if (m_RequestQueue.size() == 0)
		return NULL;
	
	CtList::list<ReadingInfo*>::iterator Itr = m_RequestQueue.begin();
	while (Itr != m_RequestQueue.end()) {
		pRequest = (*Itr);
		Itr = m_RequestQueue.erase(Itr);
		
		if ((pRequest != NULL) && (pRequest->m_State != State_Invalid))
			break;

		if (pRequest != NULL) {
			if (pRequest->m_pThumbInfo != NULL)
				delete pRequest->m_pThumbInfo;
			operator delete(pRequest);
		}
		pRequest = NULL;
	}
	return pRequest;
}

bool CtThumbCache::putRequestQueue(ReadingInfo* pRequest)
{
	if (pRequest == NULL)
		return false;
	
	m_RequestQueue.push_back(pRequest);
	return true;
}

bool CtThumbCache::cancelRequest(int ClipNo)
{
	ReadingInfo* pRequest = NULL;
	
	if (m_RequestQueue.size() == 0)
		return false;

	if (ClipNo == -1) {
		CtList::list<ReadingInfo*>::iterator Itr = m_RequestQueue.begin();
		while (Itr != m_RequestQueue.end()) {
			pRequest = (*Itr);
			++Itr;
			
			if (pRequest->m_pThumbInfo != NULL)
				delete pRequest->m_pThumbInfo;
			operator delete(pRequest);
		}
		m_RequestQueue.clear();
		return true;
		
	} else {
		CtList::list<ReadingInfo*>::iterator Itr = m_RequestQueue.begin();
		while (Itr != m_RequestQueue.end()) {
			pRequest = (*Itr);
			if (pRequest->m_ClipNo == (unsigned long)ClipNo) {
				if (pRequest->m_pThumbInfo != NULL)
					delete pRequest->m_pThumbInfo;
				operator delete(pRequest);
				Itr = m_RequestQueue.erase(Itr);
			}
			else {	++Itr;	}
		}
		return true;
	}
}

