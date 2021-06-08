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
	
	// CtWindowThumbnail����Ă΂��
	int getCurrentPage();
	int getMaxPage();
	void setScrollBar(CtContainerIndicateFrame * pScrollBar);
	
	void setInitInfo(CtWindowContentsThumbInit * info, CtThumbGridView::ViewType Type = Type_ThumbNormal);
	void setSdSlot(CtContainerThumbnailTitleBar* _pContainer);
	
	// Focus�����p(Copy,Delete���s�{�^��)
	bool setExecButton(CtButton* pExecButton);

	bool notifyPicture(CtWindowContentsDrawThumb* pContents);
	bool notifyClipInfo(CtWindowContentsSelectClipInfo* pContents);
	
private:
	CtThumbCache*	m_pThumbCache;
	
	// CtWindow���̃p�[�c����p(delete�s�v)
	CtContainerIndicateFrame* m_pScrollBar;
	CtContainerThumbnailTitleBar* m_pSdContainer;
	CtButton*		m_pExecButton;		// GridIndex 0�ԂɊ��蓖��
	ViewType 		m_ViewType;
	
	int m_ClipCount;					//�N���b�v�̐�
	int m_CurrentClip;					//�J�����g�̃N���b�v
	
	ContentsThumbSyncSelectCallback		m_SelectClip;			//�N���b�v��񓯊��p
	ContentsThumbSelectIndexCallback	m_SetFocus;				//�I�𒆃N���b�v�ʒm�p
	
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//�T���l�C���`��J�n�ʒm�p(�S��)
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//�T���l�C���`��I���ʒm�p(�S��)
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
