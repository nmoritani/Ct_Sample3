/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbGridView
*/


#ifndef __CtThumbGridView_H__
#define __CtThumbGridView_H__

#include "gdi.h"
#include "CtWindowCommon.h"
#include "CtGridView.h"
#include "CtThumbCache.h"
#include "CtThumbButton.h"

#include "CtContainerIndicateFrame.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"
#include "CtWindowContentsDrawThumb.h"

class CtThumbButton;
class CtContainerThumbnailTitleBar;

class CtThumbGridView : public CtGridView {
public:
	enum ViewType {
		Type_ThumbNormal,
		Type_ThumbDelete,
		Type_ThumbCopy,
		Type_ThumbProtect
	};
	
	CtThumbGridView(int ViewRow, int ViewColumn);
	virtual ~CtThumbGridView();

	bool nextElement();
	bool prevElement();
	bool nextPage();
	bool prevPage();
	bool setPage(int PageNo);
	//	bool dialFocus(const bool bPlus, bool Silent);
	bool moveFocus(const CtDirection Dir, bool Silent);
	bool setCurrentElement(int Element, bool bEnd = false);
	bool handleButtonEvent(const CtEventButton& Button);
	
	bool isValidElement(int Element);
	bool isValidElement(CtWidget::Element* pElement);
	
	// CtWindowThumbnailから呼ばれる
	int getCurrentPage();
	int getMaxPage();
	void setScrollBar(CtContainerIndicateFrame * pScrollBar);
	
	void setInitInfo(CtWindowContentsThumbInit * info, CtThumbGridView::ViewType Type = Type_ThumbNormal);
	void setSdSlot(CtContainerThumbnailTitleBar* _pContainer);
	
	// Focus処理用(Copy,Delete実行ボタン)
	bool setExecButton(CtButton* pExecButton);

	bool notifyPicture(CtWindowContentsDrawThumb* pContents);
	bool notifyClipInfo(CtWindowContentsSelectClipInfo* pContents);
	
private:
	CtThumbCache*	m_pThumbCache;
	
	// CtWindow側のパーツ制御用(delete不要)
	CtContainerIndicateFrame* m_pScrollBar;
	CtContainerThumbnailTitleBar* m_pSdContainer;
	CtButton*		m_pExecButton;		// GridIndex 0番に割り当て
	ViewType 		m_ViewType;
	
	int m_ClipCount;					//クリップの数
	int m_CurrentClip;					//カレントのクリップ
	
	ContentsThumbSyncSelectCallback		m_SelectClip;			//クリップ情報同期用
	ContentsThumbSelectIndexCallback	m_SetFocus;				//選択中クリップ通知用
	
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//サムネイル描画開始通知用(全体)
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//サムネイル描画終了通知用(全体)
public:
	void updateSD_Info();
private:
	
	void updateScrollBarIndex();
	
	void clearListView();
	void setListView(int clipNo);
	CtThumbButton* getElementButton(int index);
	int getElementClipNo(int index);
	int getClipPosition(int ClipNo);
	int getClipPage(int ClipNo);
};

#endif
