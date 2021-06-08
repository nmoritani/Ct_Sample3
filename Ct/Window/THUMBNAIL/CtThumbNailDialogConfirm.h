/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialogConfirm
 */

#ifndef __CtThumbNailDialogConfirm_H_
#define __CtThumbNailDialogConfirm_H_

#include "CtWindowCommon.h"
#include "CtWindowContentsThumbConfirm.h"

class CtThumbNailDialogConfirm : public CtWindowMain
{
public:
	CtThumbNailDialogConfirm( CtWindowContents *pContents );
	~CtThumbNailDialogConfirm();

	bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);

private:
	CtWindow* createWindow();
	bool destroyWindow();

	CtLayout* createMessage();
    CtLayout* createControl();
	CtLayout* createTitle();

	CtWindow* m_pWin;
	CtButton* m_pSetBtn;
	CtButton* m_pRetBtn;
	bool m_bButtonFirstPress;
};
#endif
