/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_008.h"
#include "CtContainerTimeStamp.h"
#include "CtTsInterface.h"

CtWindow* CtWindow_008::createWindow()
{
	CtWindow *pWin = new CtWindow();
	CtLayout *pLayout = new CtVLayout();
	pLayout->setColor(CtColor::white);

	// フォントカラーのみを指定してCtFontSetのインスタンスを作成
	CtFontSet font_set = CtFontSet( CtColor::Black );
	
	// 条件確認結果に応じてsetAlign( CtAlign align )でAlignを指定
	font_set.setAlign( AlignCenter );

	CtLabel *pLabel = new CtLabel("MORITANI", font_set );
	
	pLayout->addStretch(3);
	pLayout->addWidget(pLabel);
	pLayout->addStretch(3);
	
	pWin->addWidget(pLayout);

	return pWin;
}

bool CtWindow_008::handleTouchEvent(const CtEventTouch& Touch)
{
	if (Touch.getAction() != CtEventTouch::Release) return false;
	
	return true;
}

CtWindow_008::CtWindow_008(CtWindowContents *pContents)
{
}

CtWindow_008::~CtWindow_008()
{
}

bool CtWindow_008::destroyWindow()
{
	return true;
}



