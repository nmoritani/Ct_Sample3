/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtDraw
 */


#ifndef __CtDraw_H__
#define __CtDraw_H__

#include "gdi.h"

#include "Ct.h"
#include "CtDrawInfo.h"
#include "CtList.h"
#include "CtVector.h"
#include "CtObject.h"

#include <CtPlatforms.h>

class CtWindowList;
class CtWidget;


class CtDraw : public CtObject
{
public:
	typedef CtList::list<CtDrawInfo*> DrawList;
	typedef CtList::list<CtDrawInfo*>::iterator DrawItr;

	typedef CtVector::Vector<CtWindowMain*> WindowArray;
	typedef CtVector::Vector<CtRegion> RegionArray;
	
	virtual ~CtDraw();
	static CtDraw* getInstance();

	bool createWorld(const CtColorFormat Format);
	bool deleteWorld();
	bool createScreen(const CtSize& Size, GDI_COLOR_FORMAT Format, GFX_PLANE_ID PlaneId, int Screen = 0);
	bool deleteScreen(int Screen = 0);
	
	GDI_HANDLER createScreen(const CtScreenInfo& ScreenInfo, GFX_PLANE_ID PlaneID);
	bool switchScreen(int Screen);
	bool updateScreen(int Screen);
	bool clearScreen(int Screen);
	CtScreenInfo getScreenInfo(CtScreenSel ScreenSel);
	CtScreenInfo getScreenInfo(int Screen = 0);

	bool getDrawing(bool bBlock = false);
	bool freeDrawing(bool bBlock = false);
	bool isDrawing();
	bool drawScreen(const CtVector::Vector<CtWindowMain*>* Windows, RegionArray* Regions, int Screen = 0);
	bool drawScreenFast(const CtVector::Vector<CtWindowMain*>* Windows, RegionArray* Regions, int Screen = 0);
	GDI_HANDLER convertDrawable(CtWidget* Widget, CtColorFormat Format, int Screen = 0);
	GDI_HANDLER convertDrawable(CtDrawInfo* pDrawInfo, CtColorFormat Format);
	
	GDI_HANDLER createDrawable(int width, int height, CtColorFormat Format);
	bool switchDrawable(GDI_HANDLER hdr);
	bool deleteDrawable(GDI_HANDLER hdr);
	bool updateDrawable(GDI_HANDLER hdr);
	void requestUpdate(int Screen);

	bool draw(CtDrawInfo& DrawInfo);
	bool draw(CtSVG& DrawInfo);
	bool draw(CtBitmap& DrawInfo);
	bool draw(CtYUV& DrawInfo);
	bool draw(CtDrawable& DrawInfo);
	bool draw(CtLine& DrawInfo);
	bool draw(CtFill& DrawInfo);
	bool draw(CtRect& DrawInfo);
	bool draw(CtRoundRect& DrawInfo);
	bool draw(CtEllipse& DrawInfo);
	bool draw(CtString& DrawInfo);

	void printLog(bool bPrint);
	
private:
	CtDraw();

	bool createContext(const CtColorFormat Format);
	void deleteContext();
	CtColorFormat toCtFormat(GDI_COLOR_FORMAT _format);
	GDI_COLOR_FORMAT toGdiFormat(CtColorFormat _format);
	
	static CtDraw* m_pInstance;

	bool			m_bReady;
	bool			m_bDrawing;
	int				m_Semapho;
	CtScreenInfo 	m_ScreenInfo[CT_SCREEN_NUM];
	GDI_HANDLER		m_CurrentHandler;
	
	bool m_isUpdate[CT_SCREEN_NUM];
	bool m_bUsing;
	bool m_bPrint;
	syswrap_semaphore_t m_Semaphore;
};

#endif

