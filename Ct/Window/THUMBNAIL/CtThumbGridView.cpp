/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbGridView
*/

#include "CtThumbGridView.h"
#include "CtThumbButton.h"

#include "CtWindow.h"

#include "CtWindowContentsClipInfo.h"
#include "CtThumbnailUtil.h"
#include "CtVector.h"
#include "CtContainerThumbnailTitleBar.h"

CtThumbGridView::CtThumbGridView(int ViewRow, int ViewColumn) :
	m_pThumbCache(NULL),
	m_SelectClip(NULL),
	m_SetFocus(NULL),
	m_NotifyDrawStart(NULL),
	m_NotifyDrawEnd(NULL),
	m_ViewType(Type_ThumbNormal),
	m_pScrollBar(NULL),
	m_pSdContainer(NULL),
	m_ClipCount(0),
	m_CurrentClip(1),
	m_pExecButton(NULL),
	CtGridView(ViewRow, ViewColumn)
{
	CtThumbButton* pButton = NULL;

	// サムネイルボタンの登録(空ボタン)
	int size = ViewRow * ViewColumn;
	for (int i = 0; i < size; i++) {
		addWidget(new CtThumbButton());
	}
}

CtThumbGridView::~CtThumbGridView()
{
	if (m_pThumbCache) {
		delete m_pThumbCache;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//グリッドの初期化情報設定
void CtThumbGridView::setInitInfo(CtWindowContentsThumbInit * pInfo, CtThumbGridView::ViewType Type)
{
	if (pInfo == NULL)
		return;
	
	m_ViewType = Type;

	// Clip 情報
	m_ClipCount = pInfo->getClipCount();
	m_CurrentClip = pInfo->getCurrentIndex();

	if (m_CurrentClip > m_ClipCount)
		m_CurrentClip = m_ClipCount;

	// APL I/F Callback
	m_SelectClip		= pInfo->getFuncSelectClip();
	m_SetFocus			= pInfo->getFuncSetFocus();
	m_NotifyDrawStart	= pInfo->getFuncNotifyDrawStart();
	m_NotifyDrawEnd		= pInfo->getFuncNotifyDrawEnd();

	unselectElement(m_CurrentElement);

	if (m_pThumbCache != NULL)
		delete m_pThumbCache;
		
	m_pThumbCache = new CtThumbCache();
	m_pThumbCache->init(m_ClipCount, pInfo);

	setListView(m_CurrentClip);
}

bool CtThumbGridView::setExecButton(CtButton* pExecButton) {
	if (m_pExecButton == NULL) {
		m_pExecButton = pExecButton;
		return true;
	}
	return false;
}

//サムネイル情報リストの作成
void CtThumbGridView::setListView(int clipNo)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	int clip = getClipPosition(clipNo);
	int page = getClipPage(clipNo);

	setPage(page);
	setCurrentElement(clip);
}

bool CtThumbGridView::setPage(int PageNo)
{
	bool bRet = false;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();

	if (m_pThumbCache != NULL)
		m_pThumbCache->cancelRequest();

	int start_clip = (PageNo == 0) ? (getViewSize() +1) : ((PageNo -1) * getViewSize() +1);
	for (int i = 0; i< pElements->size(); i++) {
		CtThumbButton* pButton = NULL;
		if ((pButton = getElementButton(i)) == NULL)
			continue;

		pButton->setThumbCache(m_pThumbCache);
		pButton->setFunction(m_SelectClip);
		pButton->setThumbInfo(NULL);
		switch (m_ViewType) {
		case Type_ThumbNormal:	pButton->setIconType(CtThumbButton::IconType_Resume);	break;
		case Type_ThumbDelete:	pButton->setIconType(CtThumbButton::IconType_Delete);	break;
		case Type_ThumbCopy:	pButton->setIconType(CtThumbButton::IconType_Copy);		break;
		case Type_ThumbProtect:	pButton->setIconType(CtThumbButton::IconType_Protect);	break;
		default:	break;
		}
		if ((start_clip + i) <= m_ClipCount) {
			pButton->readyGo(start_clip + i);
		}
		bRet = true;
	}
	
	return bRet;
}


//SDカードスロットのアイコンを設定
void CtThumbGridView::setSdSlot(CtContainerThumbnailTitleBar* _pContainer)
{
	m_pSdContainer = _pContainer;
	updateSD_Info();
}

//SDカードスロットのアイコンを更新
void CtThumbGridView::updateSD_Info()
{
	if (m_pSdContainer == NULL) return;

	if ((0 <= m_CurrentElement) && (m_CurrentElement <= getElements()->size())) {
		CtThumbInfo* pInfo = m_pThumbCache->getThumbInfo(getElementClipNo(m_CurrentElement));

		if (pInfo != NULL) {
			switch (pInfo->getMediaType()) {
			case CtClipInfo::ClipInfoMediaType_SD1:
				m_pSdContainer->updateMediaType(CtContainerThumbnailTitleBar::ClipMediaType_SD1);
				break;
			case CtClipInfo::ClipInfoMediaType_SD2:
				m_pSdContainer->updateMediaType(CtContainerThumbnailTitleBar::ClipMediaType_SD2);
				break;
			default:
				break;
			}
		}
	}
}

//スクロールバーを設定
void CtThumbGridView::setScrollBar(CtContainerIndicateFrame* pScrollBar)
{
	int curPage;
	
	if (pScrollBar == NULL)
		return;

	if ((curPage = getClipPage(m_CurrentClip)) < 0)
		return;
		
	m_pScrollBar = pScrollBar;
	m_pScrollBar->initScrollBar(curPage, getMaxPage());
	m_pScrollBar->setIndex(curPage);
}

//スクロールバーのインデックスを更新
void CtThumbGridView::updateScrollBarIndex()
{
	if ((m_pScrollBar == NULL) || (m_CurrentClip < 0))
		return;

	m_pScrollBar->setIndex(getClipPage(m_CurrentClip));
	return;
}

CtThumbButton* CtThumbGridView::getElementButton(int index)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	
	index %= (m_ViewRow * m_ViewColumn);

	if (pElements->size() > index) {
		return static_cast<CtThumbButton*>((*pElements)[index]->pWidget);
	}
	return NULL;
}

int CtThumbGridView::getElementClipNo(int index)
{
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();
	
	CtThumbButton* pButton = static_cast<CtThumbButton*>((*pVisibles)[m_CurrentElement]->pWidget);
	return pButton->getClipNo();
}

int CtThumbGridView::getClipPosition(int clipNo)
{
	if (clipNo <= 0)
		return 0;
	
	return (clipNo -1) % getViewSize();
}

int CtThumbGridView::getClipPage(int clipNo)
{
	if (clipNo <= 0)
		return 0;

	return ((clipNo -1) / getViewSize()) +1;
}

int CtThumbGridView::getCurrentPage()
{
	return getClipPage(m_CurrentClip);
}

int CtThumbGridView::getMaxPage()
{
	if (m_ClipCount == 0) return 0;
	return (m_ClipCount -1) / getViewSize() +1;
}

//次要素への移動
bool CtThumbGridView::nextElement()
{
	if (m_pExecButton != NULL) {
		if (m_pExecButton->isFocused() != true) {
			if ((m_CurrentElement == (getViewSize() -1)) || (m_CurrentClip == m_ClipCount)) {
				if (nextPage() == true)
					return m_pExecButton->setFocus();
			}
			
		} else {
			m_pExecButton->cancelFocus();
			return setCurrentElement(0);
		}
		
	} else {
		if ((m_CurrentElement == (getViewSize() -1)) || (m_CurrentClip == m_ClipCount)) {
			if (nextPage() == true)
				return setCurrentElement(0);
		}
	}
	
	return CtGridView::nextElement();
}

//前要素への移動
bool CtThumbGridView::prevElement()
{
	// Execボタンがある場合
	if (m_pExecButton != NULL) {
		if (m_pExecButton->isFocused() != true) {
			if (m_CurrentElement == 0)
				return m_pExecButton->setFocus();
		} else {
			m_pExecButton->cancelFocus();
			if (prevPage() == true) {
				int pos = (getCurrentPage() == getMaxPage()) ? getClipPosition(m_ClipCount) : getViewSize() -1;
				return setCurrentElement(pos);
			}
		}

	} else {
		if (m_CurrentElement == 0) {
			if (prevPage() == true) {
				int pos = (getCurrentPage() == getMaxPage()) ? getClipPosition(m_ClipCount) : getViewSize() -1;
				return setCurrentElement(pos);
			}
		}
	}
	
	return CtGridView::prevElement();
}

//次ページ移動
bool CtThumbGridView::nextPage()
{
	if (m_CurrentClip <= 0) return false;
	
	int page = getClipPage(m_CurrentClip);
	if (page < getMaxPage())
		setPage(page +1);
	else
		setPage(1);
	
	if ((m_pExecButton != NULL) && (m_pExecButton->isFocused() == true)) {
		m_CurrentClip = getElementClipNo(m_CurrentElement);
	} else {
		int pos = (isValidElement(m_CurrentElement) == true) ? m_CurrentElement : getClipPosition(m_ClipCount);
		setCurrentElement(pos);
	}
	
	return true;
}


//前ページ移動
bool CtThumbGridView::prevPage()
{
	int current = m_CurrentElement;
	
	if (m_CurrentClip <= 0)	return false;
	
	int page = getClipPage(m_CurrentClip);
	if (page > 1)
		setPage(page -1);
	else
		setPage(getMaxPage());

	if ((m_pExecButton != NULL) && (m_pExecButton->isFocused() == true)) {
		m_CurrentClip = getElementClipNo(current);
	} else {
		int pos = (isValidElement(current) == true) ? current : getClipPosition(m_ClipCount);
		setCurrentElement(pos);
	}
	return true;
}

//上下左右キー動作イベント
bool CtThumbGridView::moveFocus(const CtDirection Dir, bool Silent)
{
	int current = m_CurrentElement;
	int pos = 0, max = 0;
	
	if ((current < 0) || (getElements()->size() <= current))
		return false;
	
	switch (Dir) {
	case DirUp:
		if (current < getViewColumn()) {
			prevPage();
			pos = getViewColumn() * (getViewRow() -1) + current;
		} else {
			pos = current - getViewColumn();
		}
		if (isValidElement(pos) != true) {
			if (current > getClipPosition(m_ClipCount) % getViewColumn())
				pos = getClipPosition(m_ClipCount);
			else
				pos = getClipPosition(m_ClipCount) - (getClipPosition(m_ClipCount) % getViewColumn() - current);
		}
		setCurrentElement(pos);
		return true;
		
	case DirDown:
		if ((current >= getViewColumn() * (getViewRow() -1)) ||
			(isValidElement(getViewColumn() * (current / getViewColumn() +1)) != true)) {
			nextPage();
			pos = current % getViewColumn();
		} else {
			pos = current + getViewColumn();
		}
		if (isValidElement(pos) != true) {
			pos = getClipPosition(m_ClipCount);
		}
		setCurrentElement(pos);
		return true;
		
	default:
		break;
	}
	return CtGridView::moveFocus(Dir, Silent);
}

bool CtThumbGridView::setCurrentElement(int _Target, bool bEnd)
{
	int Current = m_CurrentElement;
	int Target = _Target;
	CtVector::Vector<CtWidget::Element*>* pElements = getElements();
	CtVector::Vector<CtWidget::Element*>* pVisibles = getVisibles();

	if ((Target < 0) || (pElements->size() <= Target))
		return false;

	for (int i = 0; i < pVisibles->size(); i++) {
		if ((*pVisibles)[i] != (*pElements)[i]) {
			(*pVisibles)[i] = (*pElements)[i];
			(*pVisibles)[i]->pWidget->setInvalidate();
		}
	}

	unselectElement(Current);
	selectElement(Target, bEnd);
	m_CurrentElement = Target;

	m_CurrentClip = getElementClipNo(Target);
	if (m_SetFocus != NULL) (*m_SetFocus)(m_CurrentClip);
	
	updateScrollBarIndex();
	updateSD_Info();
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setLayout(i);
	}
	return true;
}

bool CtThumbGridView::isValidElement(int Element)
{
	CtVector::Vector<CtWidget::Element*>* pElements = getVisibles();
	CtThumbButton* pButton = NULL;
	
	if (Element < 0 || pElements->size() <= Element)
		return false;
	if ((*pElements)[Element] == NULL)
		return false;
	if ((*pElements)[Element]->Index < 0)
		return false;
	if ((*pElements)[Element]->pWidget == NULL)
		return false;
	if ((*pElements)[Element]->pWidget->isVisible() != true)
		return false;
	
	return true;
}

bool CtThumbGridView::isValidElement(CtWidget::Element* pElement)
{
	if (pElement == NULL)
		return false;
	if (pElement->Index < 0)
		return false;
	if (pElement->pWidget == NULL)
		return false;
	if (pElement->pWidget->isVisible() != true)
		return false;
	
	return true;
}

bool CtThumbGridView::notifyPicture(CtWindowContentsDrawThumb* pContents)
{
	if (m_pThumbCache == NULL) return false;

	return m_pThumbCache->notifyPicture(pContents);
}

bool CtThumbGridView::notifyClipInfo(CtWindowContentsSelectClipInfo* pContents)
{
	bool bRet = false;
	if (m_pThumbCache == NULL) return false;

	bRet = m_pThumbCache->notifyClipInfo(pContents);
	updateSD_Info();
	return bRet;
}

bool CtThumbGridView::handleButtonEvent(const CtEventButton& Button)
{
	if (CtListView::handleButtonEvent(Button) == true) {
		setCurrentElement(m_CurrentElement);
		return true;
	}
	return false;
}

