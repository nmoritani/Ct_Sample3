/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtDraw
 */


#include "CtDraw.h"
#include "CtWidget.h"
#include "CtLayout.h"
#include "CtDrawCache.h"
#include "CtWindowMain.h"

class CtWidget;

//#define DEBUG_PRINT	1

CtDraw* CtDraw::m_pInstance = NULL;

CtDraw::CtDraw() {
	setClassType(CtClassType_Draw);
	
	m_bUsing = false;
	m_bReady = false;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_ScreenInfo[i].Handler = GDI_INVALID_ID;
		m_ScreenInfo[i].Valid = false;
		m_ScreenInfo[i].Format = Format_None;
		m_ScreenInfo[i].Size.width = 0;
		m_ScreenInfo[i].Size.height = 0;
		m_isUpdate[i] = false;
	}

	syswrap_create_semaphore(&m_Semaphore, 1, THREAD_ATTR_FIFO);

	GDI_Init();

	createWorld(Format_RGBA4444);
	
#ifdef WIN32_GUI_SIM
#else
	GDI_DisplayOn();
#endif
}


CtDraw::~CtDraw(){
	// リスト内のWindowとリスト実体の破棄
	//スクリーンの削除
	deleteWorld();
	
	syswrap_destroy_semaphore(&m_Semaphore);
}


CtDraw* CtDraw::getInstance() {
	if (!m_pInstance) {
		m_pInstance = new CtDraw();
	}
	return m_pInstance;
}


CtColorFormat CtDraw::toCtFormat(GDI_COLOR_FORMAT gdi_format)
{
	CtColorFormat ct_format;
	
	switch (gdi_format) {
	case GDI_COLOR_FORMAT_RGBA8888:	ct_format = Format_RGBA8888;	break;
	case GDI_COLOR_FORMAT_RGBA4444:	ct_format = Format_RGBA4444;	break;
	case GDI_COLOR_FORMAT_YUV422SP:	ct_format = Format_YUV422;		break;
	case GDI_COLOR_FORMAT_YUV420SP:	ct_format = Format_YUV420;		break;
	default:						ct_format = Format_None;		break;
	}
	return ct_format;
}

GDI_COLOR_FORMAT CtDraw::toGdiFormat(CtColorFormat ct_format)
{
	GDI_COLOR_FORMAT gdi_format;

	switch (ct_format) {
	case Format_RGBA8888:	gdi_format = GDI_COLOR_FORMAT_RGBA8888;	break;
	case Format_RGBA4444:	gdi_format = GDI_COLOR_FORMAT_RGBA4444;	break;
	case Format_YUV422:		gdi_format = GDI_COLOR_FORMAT_YUV422SP;	break;
	case Format_YUV420:		gdi_format = GDI_COLOR_FORMAT_YUV420SP;	break;
	default:				gdi_format = GDI_COLOR_FORMAT_NONE;		break;
	}
	return gdi_format;
}



bool CtDraw::createWorld(const CtColorFormat Format)
{
	bool bRet = false;
	GDI_COLOR_FORMAT format;

	if ((format = toGdiFormat(Format)) == Format_None)
		return bRet;
	
	if (m_bReady == true) {
		deleteWorld();
	}

	if (GDI_CreateContext(format) != GDI_NO_ERROR)
		return bRet;
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (createScreen(ScreenConfig[i].Size, format, ScreenConfig[i].PlaneId, i) == true) {
			m_bReady = true;
			bRet = true;
		}
	}
	
	return bRet;
}

bool CtDraw::deleteWorld()
{
	if (m_bReady == false)
		return false;
	
	CtDrawCache *pDrawCache = CtDrawCache::getInstance();
	pDrawCache->deleteAll(CtDrawCache::Type_PathFont);
	pDrawCache->deleteAll(CtDrawCache::Type_PathSVG);
	pDrawCache->deleteAll(CtDrawCache::Type_Image);
	pDrawCache->deleteAll(CtDrawCache::Type_Drawable);
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (m_ScreenInfo[i].Handler != GDI_INVALID_ID) {
			deleteScreen(i);
		}
	}
	
	GDI_DeleteContext();
	m_bReady = false;

	return true;
}


bool CtDraw::createScreen(const CtSize& Size, GDI_COLOR_FORMAT Format, GFX_PLANE_ID PlaneId, int Screen)
{
	bool bRet = false;
	CtColorFormat ctFormat;
	CtScreenInfo* pScreen = &m_ScreenInfo[Screen];

	if ((pScreen->Size == Size) && (pScreen->Format == Format))
		return bRet;

	if ((ctFormat = toCtFormat(Format)) == Format_None)
		return bRet;

	
	if (pScreen->Handler != GDI_INVALID_ID) {
		deleteScreen(Screen);
	}

	if ((pScreen->Handler = GDI_CreateScreen(Size.width, Size.height, Format, PlaneId)) != GDI_INVALID_ID) {
		pScreen->Valid = true;
		pScreen->Size = Size;
		pScreen->Format = ctFormat;
		bRet = true;
	}
	
	return bRet;
}

bool CtDraw::deleteScreen(int Screen)
{
	bool bRet = false;
	CtScreenInfo* pScreen = &m_ScreenInfo[Screen];

	if (pScreen->Handler == GDI_INVALID_ID)
		return bRet;

	if (GDI_DeleteScreen(pScreen->Handler) == GDI_NO_ERROR) {
		pScreen->Valid = false;
		pScreen->Handler = GDI_INVALID_ID;
		pScreen->Size = CtSize(0,0);
		pScreen->Format = Format_None;
		bRet = true;
	}
	
	return bRet;
}

bool CtDraw::switchScreen(int Screen)
{
	GDI_HANDLER handler;
	
	if ((handler = m_ScreenInfo[Screen].Handler) == GDI_INVALID_ID) {
#if DEBUG_PRINT
		if (m_bPrint)
			CtDebugPrint(CtDbg, "gdi invalid handler\n");
#endif
		return false;
	}
	if (GDI_SwitchScreen(handler) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint)
			CtDebugPrint(CtDbg, "                **** Switch Screen [%d] ****\n", Screen);
#endif
		m_CurrentHandler = handler;
		return true;
	}
	
	return false;
}

void CtDraw::requestUpdate(int Screen)
{
	m_isUpdate[Screen] = true;
	m_CurrentHandler = GDI_INVALID_ID;
}

bool CtDraw::updateScreen(int Screen)
{
	GDI_HANDLER handler;

	if (m_isUpdate[Screen] != true)
		return false;
	
	if ((handler = m_ScreenInfo[Screen].Handler) == GDI_INVALID_ID)
		return false;
	
	if (GDI_Update(handler) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint)
			CtDebugPrint(CtDbg, "  -------- Update[%d] <<%08x>> --------\n", Screen, m_ScreenInfo[Screen].Handler);
#endif
		m_isUpdate[Screen] = false;
		return true;
	}
	
	return false;
}

bool CtDraw::clearScreen(int Screen)
{
	bool bRet = false;
	CtScreenInfo ScreenInfo = m_ScreenInfo[Screen];

	if (switchScreen(Screen) != true) {
		return false;
	}
	
	if (GDI_Clear(0, 0, ScreenInfo.Size.width, ScreenInfo.Size.height, 0) == GDI_NO_ERROR) {
		bRet = true;
	}

	if (bRet == true)
		requestUpdate(Screen);
	
	return false;
}

bool CtDraw::draw(CtDrawInfo& Info)
{
	if (GDI_DrawImage(&Info.m_Base, Info.m_DrawImage) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Drawable      [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] DrawImage:%08X\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 Info.m_DrawImage);
		}
#endif
		return true;
	}
	
	return false;
}

bool CtDraw::draw(CtSVG& Info)
{
	
	if (GDI_DrawSVG(&Info.m_Base, &Info.m_Draw, Info.m_pCache) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- SVG           [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Blend:(%d) SVG:%08X\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 pBase->blend,
						 &Info.m_Draw.svg);
		}
#endif
		return true;
	}
	
	return false;
}

bool CtDraw::draw(CtBitmap& Info)
{
	if (GDI_DrawBitmap(&Info.m_Base, &Info.m_Draw, NULL) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Bitmap        [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Bitmap:%p\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 Info.m_Draw.bitmap);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtYUV& Info)
{
	if (GDI_DrawYUV(&Info.m_Base, &Info.m_Draw) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- YUV           [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] YUV:%p\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 Info.m_Draw.yuv);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtDrawable& Info)
{
	if (GDI_DrawDrawable(&Info.m_Base, &Info.m_Draw) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Drawable      [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Drawable:%08X\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 Info.m_Draw.drawable);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtLine& Info)
{
	if (GDI_DrawLine(&Info.m_Base, &Info.m_Line) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Line          [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] <%3d,%3d,%3d,%3d> Blend:(%d) Color:%08x\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 Info.m_Line.x0,
						 Info.m_Line.y0,
						 Info.m_Line.x1,
						 Info.m_Line.y1,
						 pBase->blend,
						 Info.m_Line.line_color.color);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtFill& Info)
{
	
	if ((Info.m_Base.blend == GDI_BLEND_MODE_SRC) ||		/* parasoft-suppress BD-PB-NP */
		((Info.m_Color.type == VG_PAINT_TYPE_COLOR) &&
		 (Info.m_Color.color & 0xff) == 0xff)) {
		if (GDI_Clear(Info.m_Base.clip_area.x, Info.m_Base.clip_area.y, Info.m_Base.clip_area.width, Info.m_Base.clip_area.height, Info.m_Color.color) == GDI_NO_ERROR) {
			return true;
		}
	} else {
		if (GDI_DrawFill(&Info.m_Base, Info.m_Color) == GDI_NO_ERROR) {
#if DEBUG_PRINT
			if (m_bPrint) {
				GDI_DRAW_BASE* pBase = &Info.m_Base;
				CtDebugPrint(CtDbg, "--- Fill          [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Color:%08x\n",
							 pBase->draw_area.x,
							 pBase->draw_area.y,
							 pBase->draw_area.width,
							 pBase->draw_area.height,
							 pBase->clip_area.x,
							 pBase->clip_area.y,
							 pBase->clip_area.width,
							 pBase->clip_area.height,
							 Info.m_Color.color);
			}
#endif
			return true;
		}
	}
	
	return false;
}

bool CtDraw::draw(CtRect& Info)
{
	if (GDI_DrawRectangle(&Info.m_Base, &Info.m_Rect) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Rect          [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Blend:%d Color:%08x/%08x\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 pBase->blend,
						 Info.m_Rect.fill_color.color,
						 Info.m_Rect.stroke_color.color);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtRoundRect& Info)
{
	if (GDI_DrawRoundRect(&Info.m_Base, &Info.m_RRect) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- RoundRect     [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Blend:%d Color:%08x/%08x\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 pBase->blend,
						 Info.m_RRect.fill_color.color,
						 Info.m_RRect.stroke_color.color);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtEllipse& Info)
{
	if (GDI_DrawEllipse(&Info.m_Base, &Info.m_Ellipse) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			CtDebugPrint(CtDbg, "--- Ellipse       [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Blend:%d Color:%08x/%08x\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 pBase->blend,
						 Info.m_Ellipse.fill_color.color,
						 Info.m_Ellipse.stroke_color.color);
		}
#endif
		return true;
	}

	return false;
}

bool CtDraw::draw(CtString& Info)
{
	
	if (draw((CtDrawInfo&)Info) == true)
		return true;
	
	if (GDI_DrawFont(&Info.m_Base, &Info.m_String, Info.m_pCache) == GDI_NO_ERROR) {
#if DEBUG_PRINT
		if (m_bPrint) {
			GDI_DRAW_BASE* pBase = &Info.m_Base;
			char string[64];
			convert_ushort_str_to_char_str(string, Info.m_String.str);
			CtDebugPrint(CtDbg, "--- Font          [%3d, %3d, %3d, %3d]/[%3d, %3d, %3d, %3d] Blend:%d <<%s>> Color:%08x\n",
						 pBase->draw_area.x,
						 pBase->draw_area.y,
						 pBase->draw_area.width,
						 pBase->draw_area.height,
						 pBase->clip_area.x,
						 pBase->clip_area.y,
						 pBase->clip_area.width,
						 pBase->clip_area.height,
						 pBase->blend,
						 string,
						 Info.m_String.fill_color.color);
		}
#endif
		return true;
	}

	return false;
}
//@@@@

CtScreenInfo CtDraw::getScreenInfo(CtScreenSel ScreenSel)
{
	return m_ScreenInfo[toNoScreen(ScreenSel)];/* parasoft-suppress BD-PB-NOTINIT */
}

CtScreenInfo CtDraw::getScreenInfo(int Screen)
{
	return m_ScreenInfo[Screen];/* parasoft-suppress BD-PB-NOTINIT */
}

GDI_HANDLER CtDraw::createDrawable(const int width, int height, CtColorFormat format)
{
	GDI_COLOR_FORMAT gdiformat;
	
	if (width <= 0 || height <= 0) {
		return GDI_INVALID_ID;
	}

	if (format == Format_Window) {
		gdiformat = toGdiFormat(m_ScreenInfo[0].Format);
	} else {
		gdiformat = toGdiFormat(format);
	}

	if (gdiformat == GDI_COLOR_FORMAT_NONE)
		return GDI_INVALID_ID;

	return GDI_CreateDrawable(width, height, gdiformat);
}

bool CtDraw::switchDrawable(GDI_HANDLER hdr)
{
	if (GDI_SwitchDrawable(hdr, GDI_DIR_DRAW) == GDI_NO_ERROR) {
		m_CurrentHandler = hdr;
		//		CtDebugPrint(CtDbg, "  ======== SWITCH Drawable   <<%8x>> ========\n", hdr);
		return true;
	}
	
	return false;
}


bool CtDraw::deleteDrawable(GDI_HANDLER hdr)
{
	if (hdr == GDI_INVALID_ID)
		return false;
	
	if (GDI_DeleteDrawable(hdr) != GDI_NO_ERROR) {
		return false;
	}
		
	return true;
}

bool CtDraw::updateDrawable(GDI_HANDLER hdr)
{
	if (hdr == GDI_INVALID_ID)
		return false;

	m_CurrentHandler = GDI_INVALID_ID;
	if (GDI_Update(hdr) != GDI_NO_ERROR) {
		//		CtDebugPrint(CtDbg, "  -------- Drawable Update <<%08x>> --------\n", hdr);
		return false;
	}
	if (GDI_SwitchDrawable(hdr, GDI_DIR_READ) != GDI_NO_ERROR) {
		//		CtDebugPrint(CtDbg, "  ======== SWITCH Drawable   <<%8x>> ========\n", hdr);
		return false;
	}
	
	return true;
}

bool CtDraw::getDrawing(bool bBlock)
{
	SYSWRAP_ERROR err;
	
	if (bBlock == true) {
		//		while (1) {
			if ((err = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_FOREVER)) == SYSWRAP_ERR_OK) {
				m_bUsing = true;
				return true;
			}
			//		}
#if 0
	} else {
		//			CtDebugPrint(CtDbg, "failed getDrawing[%08X]\n", err);
		return false;
	}
#endif
		
	} else {
		if ((err = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_POLLING)) == SYSWRAP_ERR_OK) {
			m_bUsing = true;
			return true;
		}
		return false;
	}
	CtDebugPrint(CtDbg, ">>>>> orz <<<<<\n");
	return false;
}

bool CtDraw::freeDrawing(bool bBlock)
{
	SYSWRAP_ERROR err;

	if ((err = syswrap_post_semaphore(&m_Semaphore)) == SYSWRAP_ERR_OK) {
		m_bUsing = false;
		return true;
	}
	
	return false;
}

bool CtDraw::isDrawing()
{
	return m_bUsing;
}

#include "CtTimeMesure.h"

bool CtDraw::drawScreen(const CtVector::Vector<CtWindowMain*>* Windows, RegionArray* Regions, int Screen)
{
	bool bRet = false;
	CtWindowMain* pWindow = NULL;
#if 0
	unsigned long tim1, tim2;
	tim1 = CtGetTime();
#endif
	
	if ((Windows == NULL) || (Regions == NULL))
		return false;
	
	if (switchScreen(Screen) != true) {
		return false;
	}

#if DEBUG_PRINT
	if (m_bPrint) {
		for (int j = 0; j < Regions->size(); j++) {
			CtRegion r = (*Regions)[j];
			if (r == NoRegion)	continue;
			CtDebugPrint(CtDbg, "#### drawScreen Invalidate Region is %3d, %3d, %3d, %3d\n", r.x, r.y, r.width, r.height);
		}
	}
#endif
	
	for (int i = 0; i < Windows->size(); i++) {
		if (((pWindow = (*Windows)[i]) == NULL)	|| (pWindow->isAlive() != true)) continue;

		for (int j = 0; j < Regions->size(); j++) {
			CtRegion r = (*Regions)[j];
			if (r == NoRegion)	continue;
			if (i == 0) {	// 一番始めのWindowを描くときには、先にClearする
				GDI_Clear(r.x, r.y, r.width, r.height, 0);
			}
#if DEBUG_PRINT
			if (m_bPrint)
				CtDebugPrint(CtDbg, "---- WindowMain draw:%p (%3d, %3d, %3d, %3d)\n", pWindow, r.x, r.y, r.width, r.height);
#endif			
			if (pWindow->draw(r, Screen) == true) {
				bRet = true;
			}
			pWindow->clearInvalidates(Screen);
		}
	}
	// DrawタスクへUpdateを要求
	if (bRet == true)
		requestUpdate(Screen);
#if 0
	tim2 = CtGetTime();
	CtDebugPrint(CtDbg, "******** draw Screen %d time is %3dms ********\n", Screen, tim2 -tim1);
#endif

	return true;
}

bool CtDraw::drawScreenFast(const CtVector::Vector<CtWindowMain*>* Windows, RegionArray* Regions, int Screen)
{
	bool bRet = false;
	CtWindowMain* pWindow = NULL;
#if 0
	unsigned long tim1, tim2;
	tim1 = CtGetTime();
#endif
	
	if ((Windows == NULL) || (Regions == NULL))
		return false;
	
	if (switchScreen(Screen) != true) {
		return false;
	}
	for (int i = 0; i < Windows->size(); i++) {
		if (((pWindow = (*Windows)[i]) == NULL) || (pWindow->isAlive() != true)) continue;

		for (int j = 0; j < Regions->size(); j++) {
			CtRegion r = (*Regions)[j];
			if (r == NoRegion)	continue;
			if (i == 0) {	// 一番始めのWindowを描くときには、先にClearする
				GDI_Clear(r.x, r.y, r.width, r.height, 0);
			}
			if (pWindow->drawFast((*Regions)[j], Screen) == true) {
				bRet = true;
			}
		}
	}
	// DrawタスクへUpdateを要求
	if (bRet == true)
		requestUpdate(Screen);
#if 0
	tim2 = CtGetTime();
	CtDebugPrint(CtDbg, "** Fast draw Screen %d Window count:%d, Invalidate:%3d time is %3dms **\n", Screen, Windows->size(), Regions->size(), tim2 -tim1);
#endif
	
	return false;
}

GDI_HANDLER CtDraw::convertDrawable(CtWidget* pWidget, CtColorFormat Format, int Screen)
{
	GDI_HANDLER hdr = GDI_INVALID_ID;
	CtRegion Clip;
	short shift_x = 0, shift_y = 0;

	if (pWidget == NULL)
		return hdr;
	
	CtSize Size = pWidget->getSize();
	Clip = pWidget->getRegion(Screen);

	if (Clip.isValid() == true) {
		shift_x = (short)(Clip.x * -1);
		shift_y = (short)(Clip.y * -1);
	} else {
		if (Size.isValid() == false) {
			return hdr;
		} else {
			Clip = CtRegion(0, 0, Size.width, Size.height);
		}
	}

	if ((hdr = createDrawable(Clip.width, Clip.height, Format)) == GDI_INVALID_ID) {
		return hdr;
	}
	if (switchDrawable(hdr) == true) {
		CtRegion r = pWidget->getRegion(Screen);
		if (r.isValid() != true) {
			pWidget->setRegion(Clip, Screen);
		}
		pWidget->drawShift(shift_x, shift_y, Clip, Screen);
		updateDrawable(hdr);
	} else {
		deleteDrawable(hdr);
		hdr = GDI_INVALID_ID;
	}
	
	return hdr;
}


GDI_HANDLER CtDraw::convertDrawable(CtDrawInfo* pDrawInfo, CtColorFormat Format)
{
	GDI_HANDLER hdr = GDI_INVALID_ID;
	CtRegion _region, _clip;
	CtRegion Region;

	if (pDrawInfo == NULL)
		return hdr;

	pDrawInfo->getRegion(_region);
	if (_region.isValid() != true)
		return hdr;
	
	pDrawInfo->getClip(_clip);
	
	Region = CtRegion(0, 0, _region.width, _region.height);

	if ((hdr = createDrawable(_region.width, _region.height, Format)) == GDI_INVALID_ID) {
		return hdr;
	}
	if (switchDrawable(hdr) == true) {
		pDrawInfo->setRegion(Region);
		pDrawInfo->setClip(Region);
		pDrawInfo->draw();
		updateDrawable(hdr);
		pDrawInfo->setRegion(_region);
		pDrawInfo->setClip(_clip);
	} else {
		deleteDrawable(hdr);
		hdr = GDI_INVALID_ID;
	}
	
	return hdr;
}


void CtDraw::printLog(bool bPrint)
{
	m_bPrint = bPrint;
}

