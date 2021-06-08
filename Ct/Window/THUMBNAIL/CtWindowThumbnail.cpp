/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:            CtWindowThumbnail
*/


#include "CtWindowThumbnail.h"
#include "CtEventInterface.h"

#define WidgetIDUP (0xFFFF)
#define WidgetIDDW (0xFFFE)
#define WidgetIDDELETE (0xFFFD)
#define WidgetIDCOPY (0xFFFC)
#define WidgetIDRETURN (0xFFFB)

CtWindowThumbnail::CtWindowThumbnail(CtWindowContents *pContents) :
	m_pWin(NULL),
	m_pWcInit(NULL),
	m_pWcSelectClip(NULL),
	m_pWcThumb(NULL),
	m_pUpper(NULL),
	m_pExec(NULL),
	m_pUp(NULL),
	m_pDown(NULL),
	m_pRet(NULL),
	m_pScrollBar(NULL),
	m_pGridView(NULL),
	m_wcEvent(WC_NONE)
{
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
	setClassType(CtClassType_LayoutMain);
}

CtWindow* CtWindowThumbnail::createWindow()
{
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);

	m_pWin = new CtWindow();
	CtVLayout *pAll = new CtVLayout();

	m_pUpper = new CtContainerThumbnailTitleBar(getWindowID());

	pAll->addContainer(m_pUpper, 42);
	pAll->addWidget(new CtLabel(CtColor(134, 134, 134, 0xff)), 2);
	pAll->addWidget(createLower(), 596);

	m_pWin->addWidget(pAll);

	m_pWin->setColor(CtColor::Black);
	m_pWin->setVisible(true);
	return m_pWin;
}

void CtWindowThumbnail::clearContents()
{
	if (m_pWcInit != NULL) {
		delete m_pWcInit;
		m_pWcInit = NULL;
	}

	if (m_pWcThumb != NULL) {
		delete m_pWcThumb;
		m_pWcThumb = NULL;
	}

	if (m_pWcSelectClip != NULL) {
		delete m_pWcSelectClip;
		m_pWcSelectClip = NULL;
	}

	if (m_pGridView != NULL) {
		m_pGridView->updateSD_Info();
	}

	if (NULL != m_pScrollBar) {
		m_pScrollBar->initScrollBar(0, 0);
		m_pScrollBar->setIndex(0);
	}

	if (NULL != m_pUp) {
		m_pUp->setInvalid(false);
	}
	if (NULL != m_pDown) {
		m_pDown->setInvalid(false);
	}
}


bool CtWindowThumbnail::setContents(const CtWindowContents* pContents)
{
	//サムネイル画面の初期化
	if (pContents == NULL) {
		clearContents();
		return true;
	}

	switch (pContents->getType()) {
	case Window_ThumbNail:
	case Window_ThumbNail_Protect:
	case Window_ThumbNail_Delete:
	case Window_ThumbNail_Copy:
		setWindowID(pContents->getType());
		m_pUpper->updateOpratorSel(pContents->getType());
		break;
	default:
		return false;
	}

	const CtWindowContentsThumb* pThumb = static_cast<const CtWindowContentsThumb*>(pContents);
	if (pThumb == NULL) return false;

	switch (pThumb->getContentsThumbType()) {
	case CtWindowContentsThumb::ContentsThumbType_Init:
		// カレントクリップ、クリップ数、APLへの要求、通知関数群
		if (m_pWcInit) delete m_pWcInit;
		m_pWcInit = new CtWindowContentsThumbInit((CtWindowContentsThumbInit&)*pContents);
		m_wcEvent = WC_INIT;
		break;
	case CtWindowContentsThumb::ContentsThumbType_DrawThumb:
		// 写真データ取得完了通知
		if (m_pWcThumb) delete m_pWcThumb;
		m_pWcThumb = new CtWindowContentsDrawThumb((CtWindowContentsDrawThumb&)*pContents);
		m_wcEvent = WC_DRAW_THUMBNAIL;
		break;
	case CtWindowContentsThumb::ContentsThumbType_SelectClipInfo:
		// クリップ情報取得完了通知
		if (m_pWcSelectClip != NULL) delete m_pWcSelectClip;
		m_pWcSelectClip = new CtWindowContentsSelectClipInfo((CtWindowContentsSelectClipInfo&)*pContents);
		m_wcEvent = WC_SELECT_CLIPINFO;
		break;
	case CtWindowContentsThumb::ContentsThumbType_Thumb:
	default:
		return false;
	}

	return true;
}

CtWindowThumbnail::~CtWindowThumbnail()
{
	if (m_pWcInit)
		delete m_pWcInit;
	
	if (m_pWcThumb)
		delete m_pWcThumb;
	
	if (m_pWcSelectClip)
		delete m_pWcSelectClip;
	
	if (m_pScrollBar)
		delete m_pScrollBar;
}

bool CtWindowThumbnail::destroyWindow()
{
	/* m_pWin以外はdeleteする必要は無い */
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
	
	if (m_pWcInit != NULL) {
		delete m_pWcInit;
		m_pWcInit = NULL;
	}
	if (m_pWcSelectClip != NULL) {
		delete m_pWcSelectClip;
		m_pWcSelectClip = NULL;
	}
	if (m_pWcThumb != NULL) {
		delete m_pWcThumb;
		m_pWcThumb = NULL;
	}
	return true;
}


bool CtWindowThumbnail::handleButtonEvent_UpKey(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if ((Button.getPressType() != CtEventButton::Release) &&
		(Button.getPressType() != CtEventButton::RepeatPress)) {
		return false;
	}
	m_pGridView->prevPage();
	return true;
}

bool CtWindowThumbnail::handleButtonEvent_DownKey(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if ((Button.getPressType() != CtEventButton::Release) &&
		(Button.getPressType() != CtEventButton::RepeatPress)) {
		return false;
	}

	m_pGridView->nextPage();
	return true;
}

bool CtWindowThumbnail::handleButtonEvent_DeleteKey(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	CtFuncID FuncId = FuncID_DELETE_EXECUTE;
	if (FuncId != FuncID_MAX) {
		CtEventInterface::requestFuncCmd(FuncId, m_pWin);
	}
	return true;
}

bool CtWindowThumbnail::handleButtonEvent_CopyKey(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	CtFuncID FuncId = FuncID_COPY_EXECUTE;
	if (FuncId != FuncID_MAX) {
		CtEventInterface::requestFuncCmd(FuncId, m_pWin);
	}
	return true;
}

bool CtWindowThumbnail::handleButtonEvent_ReturnKey(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	CtFuncID FuncId = FuncID_MAX;
	if (getWindowID() == Window_ThumbNail_Delete) {
		FuncId = FuncID_DELETE_CANCEL;
	}
	else if (getWindowID() == Window_ThumbNail_Copy) {
		FuncId = FuncID_COPY_CANCEL;
	}
	else if (getWindowID() == Window_ThumbNail_Protect) {
		FuncId = FuncID_PROTECT_CANCEL;
	}
	else {
		// 何もしない
	}

	if (FuncId != FuncID_MAX) {
		CtEventInterface::requestFuncCmd(FuncId, m_pWin);
	}

	return true;
}

bool CtWindowThumbnail::handleKeyEvent(const CtEventKey & Key)
{
	if (Key.getKeyAction() == CtEventKey::LongPress) {
		if (Key.getKeyCode() == CtEventKey::KeyCode_ManualFunction) {
			//Window_ThumbNail_Delete時はLongPressで削除を実行
			if (Window_ThumbNail_Delete == getWindowID()) {
				CtEventInterface::requestFuncCmd(FuncID_DELETE_EXECUTE, m_pWin);
				return true;
			}

			//Window_ThumbNail_Copy時はLongPressでコピーを実行
			if (Window_ThumbNail_Copy == getWindowID()) {
				CtEventInterface::requestFuncCmd(FuncID_COPY_EXECUTE, m_pWin);
				return true;
			}
		}
	}

	if (Key.getKeyAction() == CtEventKey::RepeatPress || Key.getKeyAction() == CtEventKey::Press) {
		if (Key.getKeyCode() == CtEventKey::KeyCode_AudioPlus) {
			if (m_pGridView != NULL) {
				m_pGridView->nextPage();
			}
			return true;
		}
		else if (Key.getKeyCode() == CtEventKey::KeyCode_AudioMinus) {
			if (m_pGridView != NULL) {
				m_pGridView->prevPage();
			}
			return true;
		}
	}
	if (m_pExec != NULL) {
		if (Key.getKeyCode() == CtEventKey::KeyCode_Up || Key.getKeyCode() == CtEventKey::KeyCode_Down) {
			if (m_pExec->isFocused()) {
				// 無効
				return true;
			}
		}
		if (Key.getKeyAction() == CtEventKey::RepeatPress || Key.getKeyAction() == CtEventKey::Press) {
			if ((m_pExec != NULL) && m_pGridView != NULL) {
				if (m_pExec->isFocused()) {
					if (Key.getKeyCode() == CtEventKey::KeyCode_Left || Key.getKeyCode() == CtEventKey::KeyCode_MmrPlus) {
						return m_pGridView->moveFocus(DirLeft, false);
					}
				}
			}
		}
		if (Key.getKeyAction() == CtEventKey::RepeatPress || Key.getKeyAction() == CtEventKey::Press) {
			if ((m_pExec != NULL) && m_pGridView != NULL) {
				if (m_pExec->isFocused()) {
					if (Key.getKeyCode() == CtEventKey::KeyCode_Right || Key.getKeyCode() == CtEventKey::KeyCode_MmrMinus) {
						return m_pGridView->moveFocus(DirRight, false);
					}
				}
			}
		}
	}
	return false;
}


bool CtWindowThumbnail::handleButtonEvent(const CtEventButton& Button)
{
	switch (Button.getWidgetID()) {
	case WidgetIDUP:
		return handleButtonEvent_UpKey(Button);
	case WidgetIDDW:
		return handleButtonEvent_DownKey(Button);
	case WidgetIDDELETE:
		return handleButtonEvent_DeleteKey(Button);
	case WidgetIDCOPY:
		return handleButtonEvent_CopyKey(Button);
	case WidgetIDRETURN:
		return handleButtonEvent_ReturnKey(Button);
	default:
		break;
	}
	return false;
}

bool CtWindowThumbnail::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id)
	{
	case AplParamDisplayData:
		if (m_pGridView) {
			//			m_pGridView->updateCurrentPage();	// StartTC/ClipName切り替え
		}
		return false;
	default:
		break;
	}
	return false;
}

bool CtWindowThumbnail::updateContents()
{
	WindowContentType event = m_wcEvent;
	m_wcEvent = WC_NONE;

	switch (event) {
	case WC_INIT:
		updateContents_InitInfo();
		return true;

	case WC_DRAW_THUMBNAIL:
		updateContents_Thumbnail();		//読み込んだサムネイル画像(YUV)をセット
		return true;

	case WC_SELECT_CLIPINFO:
		updateContents_SelectClip();
		return true;

	case WC_NONE:
	default:
		break;
	}

	return false;

}

CtLayout* CtWindowThumbnail::createLower()
{
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
	CtHLayout *pLower = new CtHLayout();

	pLower->addStretch(14);
	pLower->addWidget(createControl(), 78);      // Control
	pLower->addStretch(68);
	pLower->addWidget(createThumbnailView(), 718);   // Thumb
	pLower->addStretch(46);
	pLower->addWidget(createScroll(), 16);       // Scroll
	pLower->addStretch(20);

	return pLower;
}

CtLayout* CtWindowThumbnail::createControl()
{
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
	CtVLayout* pWin = new CtVLayout();
	bool exec = false, del = false, ret = false;

	switch (getWindowID()) {
	case Window_ThumbNail:
		break;
	case Window_ThumbNail_Protect:
		exec = false;
		del = false;
		ret = true;
		break;
	case Window_ThumbNail_Delete:
		exec = false;
		del = true;
		ret = true;
		break;
	case Window_ThumbNail_Copy:
		exec = true;
		del = false;
		ret = true;
		break;
	default:    break;
	}

	pWin->addStretch(14);   // Space
	if (exec || del) {
		GDI_IMAGE_ID ImageId = GDI_IMAGE_ID_MAX;
		int WidgetId = 0;
		if (exec) {
			ImageId = IC_THUMBNAIL_KEYTOP_COPY;
			WidgetId = WidgetIDCOPY;
		}
		else {
			ImageId = IC_THUMBNAIL_DEL;
			WidgetId = WidgetIDDELETE;
		}
		m_pExec = new CtButton(CtSize(78, 66), ImageId);
		m_pExec->setWidgetID(WidgetId);
		pWin->addWidget(m_pExec, 66);
	}
	else {
		pWin->addStretch(66);
	}


	pWin->addStretch(72);   // Space
	m_pUp = new CtButton(CtSize(78, 66), IC_MENU_UP);
	{
		m_pUp->setWidgetID(WidgetIDUP);
		m_pUp->setInvalid(true);
		m_pUp->setFocusable(false);
		pWin->addWidget(m_pUp, 66);
	}
	pWin->addStretch(62);   // Space
	m_pDown = new CtButton(CtSize(78, 66), IC_MENU_DOWN);
	{
		m_pDown->setWidgetID(WidgetIDDW);
		m_pDown->setInvalid(true);
		m_pDown->setFocusable(false);
		pWin->addWidget(m_pDown, 66);
	}
	pWin->addStretch(72);   // Space
	if (ret) {
		m_pRet = new CtButton(CtSize(78, 66), IC_MENU_RETURN);
		m_pRet->setWidgetID(WidgetIDRETURN);
		m_pRet->setFocusable(false);
		pWin->addWidget(m_pRet, 66);
	}
	else {
		pWin->addStretch(66);
	}
	pWin->addStretch(14);   // Space

	return pWin;
}

CtLayout* CtWindowThumbnail::createScroll()
{
	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
	CtRect BaseRect = CtRect(CtColor(0, 0, 0, 0xff), 2, CtColor(51, 51, 51, 0xff));
	CtRect BarRect = CtRect(CtColor(134, 134, 134, 0xff), 0, CtColor(51, 51, 51, 0xff));
	CtMargin PbMargin = CtMargin(4);
	m_pScrollBar = new CtContainerIndicateFrame(CT_FRAME_TYPE_SCROLL_BAR, BaseRect, BarRect, PbMargin);

	return m_pScrollBar->createContainer();
}

CtLayout* CtWindowThumbnail::createThumbnailView()
{
	m_pGridView = new CtThumbGridView(THUMB_ROW, THUMB_COL);

	// 実行ボタン登録
	if (m_pExec != NULL) {
		m_pGridView->setExecButton(m_pExec);
	}
	return m_pGridView;
}

void CtWindowThumbnail::updateContents_InitInfo()
{
	if (m_pGridView == NULL) return;

	CtThumbGridView::ViewType Type;

	switch (getWindowID()) {
	case Window_ThumbNail:			Type = CtThumbGridView::Type_ThumbNormal;	break;
	case Window_ThumbNail_Protect:	Type = CtThumbGridView::Type_ThumbProtect;	break;
	case Window_ThumbNail_Delete:	Type = CtThumbGridView::Type_ThumbDelete;	break;
	case Window_ThumbNail_Copy:		Type = CtThumbGridView::Type_ThumbCopy;		break;
	default:
		Type = CtThumbGridView::Type_ThumbNormal;
	}
	
	/* サムネイルリストにコンテンツ情報セット */
	m_pGridView->setInitInfo(m_pWcInit, Type);

	//スクロールバーの初期化
	m_pGridView->setScrollBar(m_pScrollBar);

	//SDカード情報の初期化
	m_pGridView->setSdSlot(m_pUpper);

	bool bIsUpDownInvalid = (m_pGridView->getMaxPage() <= 1);
	m_pUp->setInvalid(bIsUpDownInvalid);
	m_pDown->setInvalid(bIsUpDownInvalid);
}

void CtWindowThumbnail::updateContents_SelectClip()
{
	if (!m_pGridView || !m_pWcSelectClip) return;

	// クリップ情報を通知
	m_pGridView->notifyClipInfo(m_pWcSelectClip);
}

void CtWindowThumbnail::updateContents_Thumbnail()
{
	if (!m_pGridView || !m_pWcThumb) return;

	// サムネイル描画完了を通知
	m_pGridView->notifyPicture(m_pWcThumb);
}

