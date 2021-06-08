#ifndef __CtWindow2ListMenu_H__
#define __CtWindow2ListMenu_H__

#include "CtWindowCommon.h"
#include "CtContainer2ListMenu.h"


class CtWindow2ListMenu : public CtWindowMain
{
public:
	CtWindow2ListMenu();
	~CtWindow2ListMenu();

	virtual CtWindow* createWindow();
	virtual bool destroyWindow();


private:
	CtContainer2ListMenu* m_pContainer;

};



#endif // !__CtWindow2ListMenu_H__





