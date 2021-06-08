#pragma once

#include <openvg.h>
#include <vgu.h>
#include <egl.h>
#include <windows.h>
//#include "WinCommand.h"

class CWinCommand;

delegate void DrawDelegate(int, int, void*);

ref class CWrapper
{
public:
	CWrapper(bool isLcd);
	virtual ~CWrapper(void);

	void Create();
	void Delete(void);
	void Update(void);
	void Clear(void);

	typedef void(*DRAWCALLBACK)(int, int, void*);
	void SetDrawDelegate(DrawDelegate ^d);
	static void NotifyDraw(int dpy, int w, int h, void* data);

protected:
	//CWinCommand* m_pWinCommand;
	HWND m_hwnd;
	HWND m_hwndFG;
	bool m_start_window;
	bool m_isLcd;

	static DrawDelegate ^m_drawDelegateLcd;
	static DrawDelegate ^m_drawDelegateLout;
};

//TODO:èoóÕêÊÇï°êîópà”Ç∑ÇÈëŒâû
ref class CWrapperLcd : public CWrapper
{
public:
	CWrapperLcd() : CWrapper(true)
	{
	}
};


ref class CWrapperLout : public CWrapper
{
public:
	CWrapperLout() : CWrapper(false)
	{
	}
};
