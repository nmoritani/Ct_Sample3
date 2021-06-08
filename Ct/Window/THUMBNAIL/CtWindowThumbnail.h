/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtWindowThumbnail
*/


#ifndef __CtWindowThumbnail_H__
#define __CtWindowThumbnail_H__

#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtContainerIndicateFrame.h"
#include "CtWindowContentsClipInfo.h"
#include "CtWindowContentsDrawThumb.h"
#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"
#include "CtWindowID.h"
#include "CtThumbDesign.h"
#include "CtThumbGridView.h"
#include "str_id.h"
#include "CtScrollBar.h"
#include "gdi.h"
#include "gdi_local.h"
#include "CtContainerThumbnailTitleBar.h"

class CtWindowThumbnail : public CtWindowMain
{
#define RightFont  CtFontSet(FontTypeNormal_alignRight, CtColor::White)
#define LeftFont  CtFontSet(FontTypeNormal, CtColor::White)
#define CenterFont  CtFontSet(FontTypeNormal_alignCenter, CtColor::White)
	typedef enum WindowContentType {
		WC_INIT,
		WC_DRAW_THUMBNAIL,
		WC_CLIPINFO,
		WC_SELECT_CLIPINFO,
		WC_NONE,
	}WindowContentType;

public:

	CtWindowThumbnail(CtWindowContents *pContents);
	virtual ~CtWindowThumbnail();

	CtWindow* createWindow();
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleParamEvent(const CtEventParam& Param);
	bool setContents(const CtWindowContents* pContents);	   	// WindowContentのセット
	bool updateContents();

private:
	bool destroyWindow();                                      	// ウィンドを消去する

	CtLayout* createLower();									// Window下部の部品群
	CtLayout* createControl();									// Window下部の部品群
	CtLayout* createScroll();									// ScrollBar
	CtLayout* createThumbnailView();								// サムネイル

	bool handleButtonEvent_DeleteKey(const CtEventButton & Button);
	bool handleButtonEvent_CopyKey(const CtEventButton & Button);
	bool handleButtonEvent_ReturnKey(const CtEventButton & Button);
	bool handleButtonEvent_UpKey(const CtEventButton & Button);
	bool handleButtonEvent_DownKey(const CtEventButton & Button);

	void updateContents_InitInfo();
	void updateContents_Thumbnail();
	void updateContents_SelectClip();
	void clearContents();

private:
	CtWindow*							m_pWin;

	/* WindowContent受信状態 */
	WindowContentType	m_wcEvent;
	CtWindowContentsSelectClipInfo*		m_pWcSelectClip;
	CtWindowContentsDrawThumb*			m_pWcThumb;
	CtWindowContentsThumbInit*			m_pWcInit;

	/* Contorlデータ */
	CtButton*	m_pExec;
	
	CtButton*	m_pUp;
	CtButton*	m_pDown;
	CtButton*	m_pRet;

	/* Scroll */
	CtContainerIndicateFrame* m_pScrollBar;

	/* Upper */
	CtContainerThumbnailTitleBar* m_pUpper;

	/* Lower */
	CtThumbGridView*	m_pGridView;
};

#endif
