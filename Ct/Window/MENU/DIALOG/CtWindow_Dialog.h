#ifndef __CtWindow_Dialog_H__
#define __CtWindow_Dialog_H__

#include "CtWindowCommon.h"
#include "CtContainerDialog.h"
#include "CtWindowContentsVersionDisp.h"

class CtWindow_Dialog : public CtWindowMain
{
public:
	CtWindow_Dialog(CtWindowID id);
	CtWindow_Dialog(CtWindowID id, CtWindowContents *pContents);
	~CtWindow_Dialog();
	
private:
	virtual CtWindow* createWindow();
	virtual bool destroyWindow();

	CtWindowID        m_WindowID;
	CtWindowContentsVersionDisp* m_pContents;
};

#endif // !__CtWindow_Dialog_H__
