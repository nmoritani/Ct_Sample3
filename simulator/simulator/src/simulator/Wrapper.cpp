#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "Wrapper.h"
//#include "WinCommand.h"
extern "C"{
#include "egl.h"
}

CWrapper::CWrapper(bool isLcd) : 
m_isLcd(isLcd)
{
	m_drawDelegateLcd = nullptr;
	m_drawDelegateLout = nullptr;
}

CWrapper::~CWrapper(void)
{
	Delete();
	/*
	if( m_pWinCommand )
	{
		delete m_pWinCommand;
		m_pWinCommand = NULL;
	}
	*/
}

void EglCallback(int dpy, int w, int h, void* bmp_data)
{
	CWrapper::NotifyDraw(dpy, w, h, bmp_data);
}

void CWrapper::NotifyDraw(int dpy, int w, int h, void* data)
{
	DrawDelegate ^d = nullptr;

	if (dpy == 0) d = m_drawDelegateLcd;
	else if (dpy == 1)  d = m_drawDelegateLout;
	
	if (d != nullptr) d(w, h, data);
}

void CWrapper::SetDrawDelegate(DrawDelegate ^d)
{
	if (m_isLcd) {
		m_drawDelegateLcd = d;
	}
	else {
		m_drawDelegateLout = d;
	}
}

void CWrapper::Create()
{
	eglSetSwapCallback(EglCallback);
}

void CWrapper::Delete()
{
}

void CWrapper::Update()
{
}

void CWrapper::Clear()
{
}
