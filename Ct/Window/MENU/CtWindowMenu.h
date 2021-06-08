#ifndef __CtWindowMenu_H__
#define __CtWindowMenu_H__

#include "CtWindowCommon.h"
#include "CtContainerMenu.h"


class CtWindowMenu : public CtWindowMain
{
public:
	CtWindowMenu(CtWindowContents *pContents);
	CtWindowMenu(CtWindowID id);
	CtWindowMenu();
	~CtWindowMenu();

	virtual CtWindow* createWindow();
	virtual bool destroyWindow();

//	CtWindow*       m_pWin;
//	CtContainer*    m_pContainer;

	CtRegion getListRegion(int Screen = 0) const;
	bool setBack(bool bBack);

private:


	CtWindowContents* m_Contents;
	CtContainerMenu* m_pContainer;




};



#endif // !__CtWindowMenu_H__





